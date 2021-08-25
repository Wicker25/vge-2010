/* 
    Title --- bounding-area-inl.hpp

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


#ifndef VGE_BOUNDING_AREA_INL_HPP
#define VGE_BOUNDING_AREA_INL_HPP

#include "vge/bounding-area.hpp"

namespace VGE { // Namespace di VGE

inline void
BoundingArea::SetPosition( const Types::Point2D &point ) {

	// Modifico la posizione dello entità (assoluta)
	this->position = point;

	// Imposto il flag di aggiornamento
	this->update = true;
}

inline void
BoundingArea::GetPosition( Types::Point2D &point ) const {

	// Ritorno la posizione dello entità (assoluta)
	point = this->position;
}

inline void
BoundingArea::SetScale( const Types::Size2D_f &scale_ ) {

	// Modifico la proporzione
	InterfaceScalable::SetScale( scale_ );

	// Imposto il flag di aggiornamento
	this->update = true;
}

inline void
BoundingArea::SetRotation( Types::Float a ) {

	// Modifico l'angolo di rotazione dell'immagine
	InterfaceRuotable::SetRotation( a );

	// Imposto il flag di aggiornamento
	this->update = true;
}

inline void
BoundingArea::AddVertex( const Types::Point2D &point ) {

	// Aggiungo il punto all'area
	this->vertex_list.push_back( point );
}

inline const Types::Point2DList &
BoundingArea::GetVertices() const {

	// Ritorno la lista dei vertici dell'area
	return this->vertex_list;
}

inline Types::Bool
BoundingArea::Empty() const {

	// Controllo se la lista dei punti è vuota
	return this->e_vertex_list.empty();
}

inline void
BoundingArea::Clear() {

	// Pulisco la lista dei punti
	this->vertex_list.clear();
}

inline const Types::Point2DList &
BoundingArea::GetPolygon() const {

	// Ritorno il poligono dell'area nello spazio
	return this->e_vertex_list;
}

inline const Types::Rect_f &
BoundingArea::GetRectangle() const {

	// Ritorno il rettangolo contenente l'area
	return this->area_rectangle;
}

inline void
BoundingArea::GetRectangleSize( Types::Size2D_u &size_ ) const {

	// Ritorno le dimensioni del rettangolo contenente l'area
	size_.w = ( this->area_rectangle.right - this->area_rectangle.left );
	size_.h = ( this->area_rectangle.bottom - this->area_rectangle.top );
}

inline void
BoundingArea::ForceUpdate() {

	// Imposto il flag di aggiornamento
	this->update = true;

	// Aggiorno l'area nello spazio 2D (ruotata e scalata)
	this->Update();
}

}; // Chiudo il namespace di VGE

#endif
