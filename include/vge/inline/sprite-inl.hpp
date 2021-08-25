/* 
    Title --- sprite-inl.hpp

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


#ifndef VGE_SPRITE_INL_HPP
#define VGE_SPRITE_INL_HPP

#include "vge/sprite.hpp"

namespace VGE { // Namespace di VGE

inline void
Sprite::SetPosition( const Types::Point2D &point ) {

	// Modifica la posizione dell'oggetto
	Entity::SetPosition( point );

	// Memorizza la vecchia posizione
	this->StorePosition( true, true, false );
}

inline void
Sprite::SetPosition( const Types::Point3D &point ) {

	// Modifica la posizione dell'oggetto
	Entity::SetPosition( point );

	// Memorizza la vecchia posizione
	this->StorePosition( true, true, false );
}

inline void
Sprite::MovePosition( Types::Float x, Types::Float y, Types::Float z ) {

	// Memorizza la vecchia posizione
	this->StorePosition( true, true, false );

	// Modifica la posizione dell'oggetto
	Entity::MovePosition( x, y, z );
}

inline void
Sprite::StorePosition( Types::Bool x = true, Types::Bool y = true, Types::Bool z = true ) {

	// Modifico la vecchia posizione dell'oggetto
	this->store.x = this->position.x;
	this->store.y = this->position.y;
	this->store.z = this->position.z;
}

inline void
Sprite::RestorePosition( Types::Bool x = true, Types::Bool y = true, Types::Bool z = true ) {

	// Riporto l'oggetto alla vecchia posizione
	if (x) this->position.x = this->store.x;
	if (y) this->position.y = this->store.y;
	if (z) this->position.z = this->store.z;

	// Invia il segnale di movimento
	this->SendSignal( SignalType::MOTION, NULL );
}

inline void
Sprite::GetStoredPosition( Types::Float *x, Types::Float *y, Types::Float *z ) const {

	// Ritorno la vecchia posizione dell'oggetto (assoluta)
	if ( x != NULL ) *x = this->store.x;
	if ( y != NULL ) *y = this->store.y;
	if ( z != NULL ) *z = this->store.z;
}

inline BoundingArea &
Sprite::GetCollisionArea() {

	// Ritorna l'area di collisione
	return this->collision_area;
}

inline const BoundingArea &
Sprite::GetCollisionArea() const {

	// Ritorna l'area di collisione
	return this->collision_area;
}

inline void
Sprite::SetSolid( Types::Bool state ) {

	// Modifico la solidità dell'oggetto
	this->solid = state;
}

inline Types::Bool
Sprite::GetSolid() const {

	// Controlla la solidità dell'oggetto
	return this->solid;
}

inline sigc::signal< void, Types::Bool, Sprite * > &
Sprite::SignalSolidity() {

	// Ritorno l'istanza del segnale di collisione
	return this->signal_solidity;
}

inline sigc::signal< void, Sprite *, Sprite * > &
Sprite::SignalCollision() {

	// Ritorno l'istanza del segnale di collisione
	return this->signal_collision;
}

inline sigc::signal< void, Player *, Sprite * > &
Sprite::SignalInteration() {

	// Ritorno l'istanza del segnale di interazione
	return this->signal_interation;
}

}; // Chiudo il namespace di VGE

#endif
