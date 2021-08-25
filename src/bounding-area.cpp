/* 
    Title --- bounding-area.cpp

    Copyright (C) 2010 Giacomo Trudu - wicker25[at]gmail[dot]com

    This file is part of VGE.

    VGE is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation version 3 of the License.

    VGE is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with VGE. If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef VGE_BOUNDING_AREA_CPP
#define VGE_BOUNDING_AREA_CPP

#include "vge/bounding-area.hpp"

#include "vge/interfaces/i-ruotable.hpp"
#include "vge/interfaces/inline/i-ruotable-inl.hpp"

#include "vge/interfaces/i-scalable.hpp"
#include "vge/interfaces/inline/i-scalable-inl.hpp"

#include "vge/inline/bounding-area-inl.hpp"

namespace VGE { // Namespace di VGE

BoundingArea::BoundingArea() {

	// Inizializzo le strutture
	this->update = true;
}

BoundingArea::~BoundingArea() {

}

void
BoundingArea::SetRectangle(	const Types::Rect_f &rectangle_ ) {

	// Imposto un'area rettangolare
	this->Clear();

	this->AddVertex( Types::Point2D( rectangle_.right, rectangle_.top ) );
	this->AddVertex( Types::Point2D( rectangle_.left, rectangle_.top ) );
	this->AddVertex( Types::Point2D( rectangle_.left, rectangle_.bottom ) );
	this->AddVertex( Types::Point2D( rectangle_.right, rectangle_.bottom ) );

	// Imposto il flag di aggiornamento
	this->update = true;
}


void
BoundingArea::SetRectangle( Types::Size2D_u size, Types::Point2D center ) {

	// Imposto un'area rettangolare
	Types::Float w = (Types::Float) size.w - center.x;
	Types::Float h = (Types::Float) size.h - center.y;

	this->Clear();

	this->AddVertex( Types::Point2D( w, -center.y ) );
	this->AddVertex( Types::Point2D( -center.x, -center.y ) );	
	this->AddVertex( Types::Point2D( -center.x, h ) );
	this->AddVertex( Types::Point2D( w, h ) );

	// Imposto il flag di aggiornamento
	this->update = true;
}

void
BoundingArea::Update() {

	// Controllo il flag di aggiornamento
	if ( this->update ) {

		// Inizializzo il rettangolo contenente l'area
		this->area_rectangle.left	= INFINITY;
		this->area_rectangle.top	= INFINITY;
		this->area_rectangle.right	= -INFINITY;
		this->area_rectangle.bottom	= -INFINITY;

		// Pulisco la lista dell'area nello spazio 2D
		this->e_vertex_list.clear();

		// Iteratore
		Types::Uint i = 0;

		// Numero dei punti
		Types::Uint size = this->vertex_list.size();

		for ( ; i < size; i++ ) {

			// Ricavo il punto
			Types::Point2D point = this->vertex_list[i];

			// Posizione dell'area
			Types::Float x = this->position.x;
			Types::Float y = this->position.y;

			// Calcolo la posizione del punto dell'area scalata e ruotata
			x +=	( point.x * this->scale.w ) * cos( VTORAD( this->angle ) ) - \
					( point.y * this->scale.h ) * sin( VTORAD( this->angle ) );

			y +=	( point.x * this->scale.w ) * sin( VTORAD( this->angle ) ) + \
					( point.y * this->scale.h ) * cos( VTORAD( this->angle ) );

			point.x = x;
			point.y	= y;

			// Memorizzo il rettangolo contenente l'area
			if ( this->area_rectangle.left		> point.x ) this->area_rectangle.left	= point.x;
			if ( this->area_rectangle.top		> point.y ) this->area_rectangle.top	= point.y;
			if ( this->area_rectangle.right		< point.x ) this->area_rectangle.right	= point.x;
			if ( this->area_rectangle.bottom	< point.y ) this->area_rectangle.bottom	= point.y;

			// Aggiungo il punto alla nuova lista
			this->e_vertex_list.push_back( point );
		} 

		// Cambio il flag di aggiornamento
		this->update = false;
	}
}

Types::Bool
BoundingArea::PointInArea( const Types::Point2D &point ) const {

	// Ricavo i vertici dell'area
	const Types::Point2DList &list = this->GetPolygon();

	// Intersezioni
	Types::Uint intersections = 0;

	// Numero dei punti
	const Types::Uint size = list.size();

	// Iteratore
	Types::Uint j = (size - 1), i = 0;

	// Utilizzo il teorema della curva di Jordan per controllare se il punto è interno al poligono
	for ( ; i < size; j = i++ ) {

		// Controllo se il punto è in prossimità della retta
		if (	( point.x >= list[j].x ) != ( point.x >= list[i].x ) &&
				( point.y < list[j].y || point.y < list[i].y ) ) {

			// Ricavo il coefficiente angolare
			Types::Float m = ( list[i].y - list[j].y ) / ( list[i].x - list[j].x );

			// Ricavo il parametro "q"
			Types::Float q = list[j].y - m * list[j].x;

			// Calcolo l'ordinata del punto nella retta
			Types::Float y = m * point.x + q;

			// Verifico l'intersezione
			if ( point.y <= y ) intersections++;
		}
	}

	// Se le intersezioni sono dispari, il punto si trova all'interno del poligono
	return ( intersections % 2 == 1 );
}

/*
inline int
ccw( Types::Point2D a, Types::Point2D b, Types::Point2D c ) {

	return (c.y - a.y) * (b.x - a.x) > (b.y - a.y) * (c.x - a.x);
}

collision = ccw(list1->at(j],list2->at(k],list2->at(t]) != ccw(list1->at(i],list2->at(k],list2->at(t]) \
			&& ccw(list1->at(j],list1->at(i],list2->at(k]) != ccw(list1->at(j],list1->at(i],list2->at(t]);
*/

Types::Bool
BoundingArea::CollideRectangularArea( const Types::Rect_f &rectangle ) const {

	// Flag di collisione
	Types::Bool collision = false;

	// Ricavo il rettangolo contenente quest'area
	const Types::Rect_f &rect = this->GetRectangle();

	// Cerca la collisione con il rettangolo assoluto
	if ( rectangle.left		<= rect.right )
	if ( rectangle.top		<= rect.bottom )
	if ( rectangle.right	>= rect.left )
	if ( rectangle.bottom	>= rect.top )

		collision = true;

	// Comunico la collisione
	return collision;
}

Types::Bool
BoundingArea::CollideBoundingArea( const BoundingArea &area ) const {

	// Flag di collisione
	Types::Bool collision = false;

	// Controllo se le aree sono abbastanza vicine
	if ( this->CollideRectangularArea( area.GetRectangle() ) ) {

		// Constante di scarto
		static const Types::Float eps = 0.001f;

		// Ricavo i vertici di quest'area
		const Types::Point2DList &list1 = this->GetPolygon();

		// Ricavo i vertici della seconda area
		const Types::Point2DList &list2 = area.GetPolygon();

		// Numero dei punti
		const Types::Uint size1 = list1.size();
		const Types::Uint size2 = list2.size();

		// Iteratori
		Types::Uint j = (size1 - 1), i = 0;
		Types::Uint k, t;

		// Cerca l'intersezione tra i poligoni
		for ( ; i < size1 && !collision; j = i++ ) {

			// Ricavo il coefficienti angolare del segmento del primo poligono
			Types::Float m1 = ( list1[i].y - list1[j].y ) / ( list1[i].x - list1[j].x );

			// Ricavo il parametro "q" del segmento del primo poligono
			Types::Float q1 = list1[i].y - m1 * list1[i].x;

			for ( k = (size2 - 1), t = 0; t < size2 && !collision; k = t++ ) {

				// Controllo se i due segmenti sono paralleli e verticali
				if ( list1[j].x == list1[i].x && list2[k].x == list2[t].x ) {

					// Controllo se i segmenti si incontrano vericalmente
					if (	( list1[j].y >= list2[k].y ) != ( list1[i].y >= list2[k].y ) || 
							( list1[j].y >= list2[t].y ) != ( list1[i].y >= list2[t].y ) )

					// Controllo la distanza, tenendo conto dello spostamento orizzontale
					if ( VABS( list1[j].x - list2[k].x ) >= 1.0 ) {

						// Comunico la collisione
						collision = true;
					}

				} else {

					// Ricavo il coefficienti angolare del segmento del secondo poligono
					Types::Float m2 = ( list2[t].y - list2[k].y ) / ( list2[t].x - list2[k].x );

					// Ricavo il parametro "q" del segmento del secondo poligono
					Types::Float q2 = list2[t].y - m2 * list2[t].x;

					// Punto di intersezione
					Types::Point2D p;

					// Ricavo il punto di intersezione tra le rette dei due segmenti
					if ( list1[j].x == list1[i].x ) {

						p.x = list1[i].x;
						p.y = m2 * list1[i].y + q2;

					} else if ( list2[k].x == list2[t].x ) {

						p.x = list2[t].x;
						p.y = m1 * list2[t].y + q1;

					} else {

						p.x = (q1 - q2) / (m2 - m1);
						p.y = m1 * p.x + q1;
					}

					// Controllo se il punto è in prossimità dei segmenti
					if (	( p.x >= list1[j].x - eps ) != ( p.x >= list1[i].x + eps ) &&
							( p.y >= list1[j].y - eps ) != ( p.y >= list1[i].y + eps ) )

					if (	( p.x >= list2[k].x - eps ) != ( p.x >= list2[t].x + eps ) &&
							( p.y >= list2[k].y - eps ) != ( p.y >= list2[t].y + eps ) ) {

						// Comunico la collisione
						collision = true;
					}
				}
			}
		}
	}

	// Comunico la collisione
	return collision;
}

}; // Chiudo il namespace di VGE

#endif
