/* 
    Title --- character.cpp

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


#ifndef VGE_CHARACTER_CPP
#define VGE_CHARACTER_CPP

#include "vge/character.hpp"

#include "vge/interfaces/i-image.hpp"
#include "vge/interfaces/inline/i-image-inl.hpp"

#include "vge/interfaces/i-animation.hpp"
#include "vge/interfaces/inline/i-animation-inl.hpp"

#include "vge/entity.hpp"
#include "vge/inline/entity-inl.hpp"

#include "vge/image.hpp"
#include "vge/inline/image-inl.hpp"

#include "vge/object.hpp"
#include "vge/inline/object-inl.hpp"

#include "vge/inline/character-inl.hpp"

namespace VGE { // Namespace di VGE

Character::Character( const std::string &path, const Types::Size2D_u size_, Types::Uint n_frames ) :

	Object( path, size_ ) {

	// Imposto l'identificativo del tipo di entità
	this->SetMask( CHARACTER_MASK );

	// Imposto il numero di frame
	this->SetAnimationRange( 1, n_frames );

	// Metto il personaggio nello stato inattivo
	this->SetIdle();
}

Character::Character( const Image &image, const Types::Size2D_u size_, Types::Uint n_frames ) :

	Object( image, size_ ) {

	// Imposto l'identificativo del tipo di entità
	this->SetMask( CHARACTER_MASK );

	// Imposto il numero di frame
	this->SetAnimationRange( 1, n_frames );

	// Metto il personaggio nello stato inattivo
	this->SetIdle();
}

Character::~Character() {

}

void
Character::SetIdle() {

	// Chiamo la funzione originaria
	Object::SetIdle();

	// Cambio lo stato dell'animazione
	this->SetAnimationStatus( Animation::STOP );

	// Imposto il fotogramma del personaggio inattivo
	this->SetAnimationFrame( 0.0f );
}

void
Character::SendSignal( Types::Int type, Entity *other ) {

	// Chiamo il gestore dei segnali
	Object::SendSignal( type, other );

	// Controlla il tipo di segnale
	switch ( type ) {

		// Gestisco il segnale di cambio della direzione
		case SignalType::CHANGE_DIRECTION: {

			// Modifico l'animazione del personaggio
			this->SetAnimationSeries( this->GetDirection() );
			// Cambio lo stato dell'animazione
			this->SetAnimationStatus( Animation::PLAY );
			break;
		}

		default: break;
	}
}

void
Character::Update( Viewer *viewer, Player *player ) {

	// Controllo se c'è stato un movimento
	if (	this->position.x != this->store.x ||
			this->position.y != this->store.y	) {

		// Cambio lo stato dell'animazione
		this->SetAnimationStatus( Animation::PLAY );

	// Metto il personaggio nello stato inattivo
	} else this->SetIdle();

	// Avvio la funzione di lavoro superiore
	Object::Update( viewer, player );

	// Aggiorno l'area di collisione nello spazio 2D
	this->GetCollisionArea().Update();
}

}; // Chiudo il namespace di VGE

#endif
