/* 
    Title --- entity-inl.hpp

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


#ifndef VGE_ENTITY_INL_HPP
#define VGE_ENTITY_INL_HPP

#include "vge/entity.hpp"

namespace VGE { // Namespace di VGE

inline void
Entity::SetMask( Entity::MaskType mask ) {

	// Imposto l'identificativo del tipo di entità
	this->mask = mask;
}

inline Entity::MaskType
Entity::GetMask() const {

	// Ritorno l'identificativo del tipo di entità
	return this->mask;
}

inline void
Entity::SetEngine( Engine *engine ) {

	// Collego l'istanza al gestore del gioco
	this->parent_engine = engine;
}

inline Engine *
Entity::GetEngine() const {

	// Ritorno il puntatore al gestore del gioco
	return this->parent_engine;
}

inline void
Entity::SetScene( Scene *scene ) {

	// Collego l'istanza al gestore della scena
	this->parent_scene = scene;
}

inline Scene *
Entity::GetScene() const {

	// Ritorno il puntatore al gestore della scena
	return this->parent_scene;
}

inline void
Entity::SetName( const std::wstring &name ) {

	// Imposto il nome dell'entità
	this->e_name = name;
}

inline std::wstring
Entity::GetName() const {

	// Ritorno il nome dell'entità
	return this->e_name;
}

inline void
Entity::SetPosition( const Types::Point2D &point ) {

	// Modifico la posizione dell'entità (assoluta)
	this->position = Types::Point3D( point );

	// Invio il segnale di movimento
	this->SendSignal( SignalType::MOTION, NULL );
}

inline void
Entity::SetPosition( const Types::Point3D &point ) {

	// Modifico la posizione dell'entità (assoluta)
	this->position = point;

	// Invio il segnale di movimento
	this->SendSignal( SignalType::MOTION, NULL );
}

inline void
Entity::MovePosition( Types::Float x, Types::Float y, Types::Float z ) {

	// Modifico la posizione dell'entità (relativa)
	this->position = this->position + Types::Point3D( x, y, z );

	// Invio il segnale di movimento
	this->SendSignal( SignalType::MOTION, NULL );
}

inline const Types::Point3D &
Entity::GetPosition() const {

	// Ritorno la posizione dell'entità (assoluta)
	return this->position;
}

inline void
Entity::SetCenter( const Types::Point2D &point ) {

	// Modifico il centro dell'entità
	this->center = point;
}

inline const Types::Point2D &
Entity::GetCenter() const {

	// Ritorno il centro dell'entità
	return this->center;
}

inline BoundingArea &
Entity::GetVisibilityArea() {

	// Ritorna l'area di visibilità
	return this->visibility_area;
}

inline const BoundingArea &
Entity::GetVisibilityArea() const {

	// Ritorna l'area di visibilità
	return this->visibility_area;
}

inline void
Entity::SetVisible( Types::Bool state ) {

	// Modifico la visibilità dell'entità
	this->visible = state;

	// Invio il segnale di cambio della visibilità
	this->SendSignal( SignalType::CHANGE_VISIBILITY, NULL );
}

inline Types::Bool
Entity::GetVisible() const {

	// Controllo la visibilità dell'entità
	return this->visible;
}

inline void
Entity::SetFixed( Types::Bool state ) {

	// Imposto la posizione dell'entità rispetto alla camera
	this->fixed = state;
}

inline Types::Bool
Entity::GetFixed() const {

	// Ritorno la posizione dell'entità rispetto alla camera
	return this->fixed;
}

inline void
Entity::SetSensible( Types::Bool state ) {

	// Imposto la sensibilità dell'entità
	this->sensibility = state;
}

inline Types::Bool
Entity::GetSensible() const {

	// Ritorno la sensibilità dell'entità
	return this->sensibility;
}

inline void
Entity::SetDebugMode( Types::Bool state ) {

	// Imposta la modalità di debug
	this->debug_mode = state;
}

inline Types::Bool
Entity::GetDebugMode() const {

	// Ritorna lo stato della modalità di debug
	return this->debug_mode;
}

inline sigc::signal< void, Types::Bool, Entity * > &
Entity::SignalVisibility() {

	// Ritorno l'istanza del segnale di cambio della visibilità
	return this->signal_visibility;
}

inline sigc::signal< void, Types::Bool, Entity * > &
Entity::SignalFixing() {

	// Ritorno l'istanza del segnale di cambio della posizione rispetto alla camera
	return this->signal_fixing;
}

inline sigc::signal< void, Types::Bool, Entity * > &
Entity::SignalSensibility() {

	// Ritorno l'istanza del segnale di cambio della sensibilità
	return this->signal_sensibility;
}

inline sigc::signal< void, Types::Point3D, Entity * > &
Entity::SignalMotion() {

	// Ritorno l'istanza del segnale di movimento
	return this->signal_motion;
}

}; // Chiudo il namespace di VGE

#endif
