/* 
    Title --- bounding-area.hpp

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


#ifndef VGE_BOUNDING_AREA_HPP
#define VGE_BOUNDING_AREA_HPP

#include <iostream>
#include <vector>
#include <cmath>
#include <cfloat>

#include "vge/consts.hpp"
#include "vge/types.hpp"
#include "vge/error.hpp"
#include "vge/math.hpp"

#include "vge/interfaces/i-ruotable.hpp"
#include "vge/interfaces/i-scalable.hpp"

namespace VGE { // Namespace di VGE

class BoundingArea : public InterfaceScalable, public InterfaceRuotable {

	/* AREA DI DELIMITAZIONE */

public:

	// Metodi costruttore e distruttore
	BoundingArea();
	virtual ~BoundingArea();

	// Modifica la posizione dello entità (assoluta)
	virtual void SetPosition( const Types::Point2D &point );
	// Ritorna la posizione dello entità (assoluta)
	virtual void GetPosition( Types::Point2D &point ) const;

	// Modifica la proporzione
	virtual void SetScale( const Types::Size2D_f &scale_ );

	// Modifico l'angolo di rotazione dell'immagine
	virtual void SetRotation( Types::Float a );

	// Aggiunge un punto all'area
	virtual void AddVertex( const Types::Point2D &point );

	// Imposta un'area rettangolare
	virtual void SetRectangle( const Types::Rect_f &rectangle_ );
	virtual void SetRectangle( Types::Size2D_u size, Types::Point2D center );

	// Ritorna la lista dei vertici dell'area
	virtual const Types::Point2DList &GetVertices() const;

	// Controlla se la lista dei punti è vuota
	virtual Types::Bool Empty() const;

	// Pulisce la lista dei punti
	virtual void Clear();

	// Ritorna il poligono dell'area nello spazio
	virtual const Types::Point2DList &GetPolygon() const;

	// Ritorna il rettangolo contenente l'area
	virtual const Types::Rect_f &GetRectangle() const;

	// Ritorna le dimensioni del rettangolo contenente l'area
	virtual void GetRectangleSize( Types::Size2D_u &size_ ) const;

	// Cerca la collisione con un punto nello spazio (Jordan Curve Theorem)
	virtual Types::Bool PointInArea( const Types::Point2D &point ) const;

	// Cerca la collisione con un rettangolo assoluto
	virtual Types::Bool CollideRectangularArea( const Types::Rect_f &rectangle ) const;

	// Cerca la collisione con un altra area
	virtual Types::Bool CollideBoundingArea( const BoundingArea &area ) const;

	// Forza l'aggiornamento dell'area nello spazio 2D (ruotata e scalata)
	virtual void ForceUpdate();

	// Aggiorna l'area nello spazio 2D (ruotata e scalata)
	virtual void Update();

protected:

	// Posizione di riferimento dell'area
	Types::Point2D position;

	// Lista dei punti che delimitano l'area
	Types::Point2DList vertex_list;

	// Lista dei punti che delimitano l'area nello spazio 2D
	Types::Point2DList e_vertex_list;

	// Rettangolo massimo dell'area
	Types::Rect_f area_rectangle;

	// Flag di aggiornamento
	Types::Bool update;
};

}; // Chiudo il namespace di VGE

#endif
