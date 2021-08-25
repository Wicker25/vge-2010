/* 
    Title --- object-inl.hpp

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


#ifndef VGE_OBJECT_INL_HPP
#define VGE_OBJECT_INL_HPP

#include "vge/object.hpp"

namespace VGE { // Namespace di VGE

inline void
Object::UpdateDepth() {

	// Aggiorno la profondità dello sprite
	this->position.z = VGE::Layer::SHADOW + this->position.y;
}

inline void
Object::SetDirection( Object::Direction value ) {

	// Imposto la direzione dell'oggetto
	this->direction = value;

	// Invio il segnale di cambio della direzione
	this->SendSignal( SignalType::CHANGE_DIRECTION, NULL );
}

inline Object::Direction
Object::GetDirection() const {

	// Ritorno la direzione dell'oggetto
	return this->direction;
}

inline void
Object::SetSpeed( Types::Float value ) {

	// Imposto la velocità dell'oggetto
	this->speed = value;

	// Invio il segnale di cambio della velocità
	this->SendSignal( SignalType::CHANGE_SPEED, NULL );
}

inline Types::Float
Object::GetSpeed() const {

	// Ritorno la velocità dell'oggetto
	return this->speed;
}

inline void
Object::MovePosition( Types::Float x, Types::Float y ) {

	// Muovo l'oggetto
	this->MovePosition( x, y, true );
}

inline void
Object::MoveLeft() {

	// Muove l'oggetto a sinistra
	Sprite::MovePosition( -this->GetSpeed(), 0, 0 );

	// Imposto il fattore di velocità dell'animazione
	this->SetAnimationSpeedFactor( this->GetSpeed() );

	// Modifico la direzione dell'oggetto
	this->SetDirection( DIRECTION_LEFT );
}

inline void
Object::MoveLeft( Types::Float value ) {

	// Muove l'oggetto a sinistra
	Sprite::MovePosition( -this->GetSpeed() * value, 0, 0 );

	// Imposto il fattore di velocità dell'animazione
	this->SetAnimationSpeedFactor( this->GetSpeed() * value );

	// Modifico la direzione dell'oggetto
	this->SetDirection( DIRECTION_LEFT );
}

inline void
Object::MoveUp() {

	// Muove l'oggetto in alto
	Sprite::MovePosition( 0, -this->GetSpeed(), 0 );

	// Imposto il fattore di velocità dell'animazione
	this->SetAnimationSpeedFactor( this->GetSpeed() );

	// Modifico la direzione dell'oggetto
	this->SetDirection( DIRECTION_UP );
}

inline void
Object::MoveUp( Types::Float value ) {

	// Muove l'oggetto in alto
	Sprite::MovePosition( 0, -this->GetSpeed() * value, 0 );

	// Imposto il fattore di velocità dell'animazione
	this->SetAnimationSpeedFactor( this->GetSpeed() * value );

	// Modifico la direzione dell'oggetto
	this->SetDirection( DIRECTION_UP );
}

inline void
Object::MoveRight() {

	// Muove l'oggetto a destra
	Sprite::MovePosition( this->GetSpeed(), 0, 0 );

	// Imposto il fattore di velocità dell'animazione
	this->SetAnimationSpeedFactor( this->GetSpeed() );

	// Modifico la direzione dell'oggetto
	this->SetDirection( DIRECTION_RIGHT );
}

inline void
Object::MoveRight( Types::Float value ) {

	// Muove l'oggetto a destra
	Sprite::MovePosition( this->GetSpeed() * value, 0, 0 );

	// Imposto il fattore di velocità dell'animazione
	this->SetAnimationSpeedFactor( this->GetSpeed() * value );
	
	// Modifico la direzione dell'oggetto
	this->SetDirection( DIRECTION_RIGHT );
}

inline void
Object::MoveDown() {

	// Muove l'oggetto in basso
	Sprite::MovePosition( 0, this->GetSpeed(), 0 );

	// Imposto il fattore di velocità dell'animazione
	this->SetAnimationSpeedFactor( this->GetSpeed() );

	// Modifico la direzione dell'oggetto
	this->SetDirection( DIRECTION_DOWN );
}

inline void
Object::MoveDown( Types::Float value ) {

	// Muove l'oggetto in basso
	Sprite::MovePosition( 0, this->GetSpeed() * value, 0 );

	// Imposto il fattore di velocità dell'animazione
	this->SetAnimationSpeedFactor( this->GetSpeed() * value );

	// Modifico la direzione dell'oggetto
	this->SetDirection( DIRECTION_DOWN );
}

inline void
Object::SetIdle() {

	// Memorizza le posizioni attuali
	this->StorePosition( true, true, false );
}

inline void
Object::SetMessage( const std::wstring &string ) {

	// Imposto il messaggio dell'oggetto
	this->message = string;
}

inline const std::wstring &
Object::GetMessage() const {

	// Ritorno il messaggio dell'oggetto
	return this->message;
}

inline void
Object::SetFace( Image *image ) {

	// Imposto l'immagine faccia dell'oggetto
	this->face = image;
}

inline Image *
Object::GetFace() const {

	// Ritorno l'immagine faccia dell'oggetto
	return this->face;
}

inline void
Object::SetShadow( Image *image ) {

	// Assegno un'ombra al personaggio
	this->shadow = image;
}

inline Image *
Object::GetShadow() const {

	// Ritorno il messaggio dell'oggetto
	return this->shadow;
}

inline sigc::signal< void, Object::Direction, Object * > &
Object::SignalDirection() {

	// Ritorno l'istanza del segnale di cambio della direzione
	return this->signal_direction;
}

inline sigc::signal< void, Types::Float, Object * > &
Object::SignalSpeed() {

	// Ritorno l'istanza del segnale di cambio della velocità
	return this->signal_speed;
}

inline sigc::signal< void, Object::Direction, Types::Float, Object * > &
Object::SignalStep() {

	// Ritorno l'istanza del segnale di movimento per passo
	return this->signal_step;
}

}; // Chiudo il namespace di VGE

#endif
