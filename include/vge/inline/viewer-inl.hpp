/* 
    Title --- viewer-inl.hpp

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


#ifndef VGE_VIEWER_INL_HPP
#define VGE_VIEWER_INL_HPP

#include "vge/viewer.hpp"

namespace VGE { // Namespace di VGE

inline void
Viewer::SetEngine( Engine *engine ) {

	// Collego l'istanza al gestore del gioco
	this->parent_engine = engine;
}

inline Engine *
Viewer::GetEngine() const {

	// Ritorno il puntatore al gestore del gioco
	return this->parent_engine;
}

inline void
Viewer::SetPosition( const Types::Point3D &point ) {

	// Modifico la posizione del visualizzatore (assoluta)
	this->pos_r			= point;
	this->position.z	= point.z;
}

inline const Types::Point3D &
Viewer::GetPosition() const {

	// Ritorno la posizione del visualizzatore (assoluta)
	return this->position;
}

inline void
Viewer::SetCameraSize( const Types::Size2D_f &scale_ ) {

	// Imposto la dimensione della telecamera 
	this->size_r = scale_;
}

inline void
Viewer::SetCameraPosition( const Types::Point2D &point ) {

	// Modifico la posizione della camera (assoluta)
	this->cam_pos = point;
}

inline void
Viewer::MoveCameraPosition( Types::Float x, Types::Float y ) {

	// Modifico la posizione della camera (relativa)
	this->cam_pos = this->cam_pos.Translate( Types::Point2D( x, y ) );
}

inline const Types::Point2D &
Viewer::GetCameraPosition() const {

	// Ritorno la posizione della camera (assoluta)
	return this->cam_pos;
}

inline Types::Rect_f
Viewer::GetCameraRectangle() const {

	// Ritorna il rettangolo dell'immagine nella scena (assoluto)
	return Types::Rect_f(	this->cam_pos.x,
							this->cam_pos.y,
							this->cam_pos.x + this->size.w,
							this->cam_pos.y + this->size.h );
}

inline void
Viewer::SetTarget( Entity *new_target, Types::Float elasticity_value = 15.0f ) {

	// Imposto un obbiettivo da seguire con la camera
	this->target = new_target;

	// Imposto l'elasticità della camera
	this->SetElasticity( elasticity_value );
}

inline void
Viewer::RemoveTarget() {

	// Rimuovo l'obbiettivo da seguire con la camera
	this->target = NULL;
}

inline void
Viewer::GetTarget( Entity *new_target ) const {

	// Ritorno l'obbiettivo da seguire con la camera
	new_target = this->target;
}

inline void
Viewer::SetElasticity( Types::Float value ) {

	// Imposto l'elasticità della camera
	this->elasticity = value;
}

inline void
Viewer::GetElasticity( Types::Float *value ) {

	// Ritorno l'elasticità della camera
	if ( value != NULL ) *value = this->elasticity;
}

inline void
Viewer::SetMaxSpeed( Types::Float value ) {

	// Imposto l'elasticità della camera
	this->max_speed = value;
}

inline void
Viewer::GetMaxSpeed( Types::Float *value ) {

	// Ritorno l'elasticità della camera
	if ( value != NULL ) *value = this->max_speed;
}

inline Gui::Box &
Viewer::GetBox() {

	// Ritorno la cornice del visualizzatore
	return this->frame;
}

}; // Chiudo il namespace di VGE

#endif
