/* 
    Title --- sprite.cpp

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


#ifndef VGE_SPRITE_CPP
#define VGE_SPRITE_CPP

#include "vge/sprite.hpp"

#include "vge/input-manager.hpp"
#include "vge/inline/input-manager-inl.hpp"

#include "vge/interfaces/i-programmable.hpp"
#include "vge/interfaces/inline/i-programmable-inl.hpp"

#include "vge/interfaces/i-colorable.hpp"
#include "vge/interfaces/inline/i-colorable-inl.hpp"

#include "vge/interfaces/i-ruotable.hpp"
#include "vge/interfaces/inline/i-ruotable-inl.hpp"

#include "vge/interfaces/i-scalable.hpp"
#include "vge/interfaces/inline/i-scalable-inl.hpp"

#include "vge/interfaces/i-image.hpp"
#include "vge/interfaces/inline/i-image-inl.hpp"

#include "vge/interfaces/i-clickable.hpp"
#include "vge/interfaces/inline/i-clickable-inl.hpp"

#include "vge/entity.hpp"
#include "vge/inline/entity-inl.hpp"

#include "vge/image.hpp"
#include "vge/inline/image-inl.hpp"

#include "vge/viewer.hpp"
#include "vge/inline/viewer-inl.hpp"

#include "vge/scene.hpp"
#include "vge/inline/scene-inl.hpp"

#include "vge/player.hpp"
#include "vge/inline/player-inl.hpp"

#include "vge/engine.hpp"
#include "vge/inline/engine-inl.hpp"

#include "vge/inline/sprite-inl.hpp"

namespace VGE { // Namespace di VGE

Sprite::Sprite( const std::string &path ) : Image( path ) {

	// Imposto l'identificativo del tipo di entità
	this->SetMask( SPRITE_MASK );

	// Memorizzo la posizione
	this->StorePosition( true, true, false );

	// Imposto i flags predefiniti dell'oggetto
	this->SetSolid( true );
}

Sprite::Sprite( const std::string &path, const Types::Size2D_u size_ ) : Image( path, size_ ) {

	// Imposto l'identificativo del tipo di entità
	this->SetMask( SPRITE_MASK );

	// Memorizzo la posizione
	this->StorePosition( true, true, false );

	// Imposto i flags predefiniti dell'oggetto
	this->SetSolid( true );
}

Sprite::Sprite( const Image &image ) : Image( image ) {

	// Imposto l'identificativo del tipo di entità
	this->SetMask( SPRITE_MASK );

	// Memorizzo la posizione
	this->StorePosition( true, true, false );

	// Imposto i flags predefiniti dell'oggetto
	this->SetSolid( true );
}

Sprite::Sprite( const Image &image, const Types::Size2D_u size_ ) : Image( image ) {

	// Imposto l'identificativo del tipo di entità
	this->SetMask( SPRITE_MASK );

	// Imposto la porzione dell'immagine
	this->SetClipSize( size_ );

	// Memorizzo la posizione
	this->StorePosition( true, true, false );

	// Imposto i flags predefiniti dell'oggetto
	this->SetSolid( true );
}

Sprite::~Sprite() {

}

void
Sprite::SendSignal( Types::Int type, Entity *other ) {

	// Chiamo il gestore dei segnali
	Image::SendSignal( type, other );

	// Controlla il tipo di segnale
	switch ( type ) {

		// Gestisco il segnale di movimento
		case SignalType::MOTION: { 

			// Aggiorno la posizione dell'area di collisione
			this->GetCollisionArea().SetPosition( this->position );
			break;
		}

		// Gestisco il segnale di modifica della scala
		case SignalType::RESIZING: { 

			// Aggiorno la dimensione dell'area di collisione
			this->GetCollisionArea().SetRectangle( this->size, this->center );
			break;
		}

		// Gestisco il segnale di modifica della scala
		case SignalType::SCALING: { 

			// Aggiorno la scala dell'area di collisione
			this->GetCollisionArea().SetScale( this->scale );
			break;
		}

		// Gestisco il segnale di rotazione
		case SignalType::ROTATION: { 

			// Aggiorno la rotazione dell'area di collisione
			this->GetCollisionArea().SetRotation( this->GetRotation() );
			break;
		}

		// Gestisco il segnale di cambio della solidità
		case SignalType::CHANGE_SOLIDITY: { 

			// Emetto il segnale di cambio della solidità
			this->SignalSolidity().emit( this->GetSolid(), this );
			break;
		}

		// Gestisco il segnale della collisione
		case SignalType::COLLISION: { 

			// Emetto il segnale di collisione
			this->SignalCollision().emit( this, VGE_SPRITE( other ) );

			// Ripristina la posizione
			this->RestorePosition( true, true, false );

			// Controlla che ci sia almeno un elemento in coda
			if ( !this->event_list.empty() ) {

				// Ricavo il primo elemento della coda
				Event *event = this->event_list.front();

				if ( event->type == EventType::WAIT_COLLISION ) {

					// Rimuovo il primo evento della coda
					this->PopEvent( event );
				}
			}

			break;
		}

		// Gestisco il segnale dell'interazione
		case SignalType::INTERACTION: { 

			// Emetto il segnale di interazione
			this->SignalInteration().emit( VGE_PLAYER( other ), this );

			// Controlla che ci sia almeno un elemento in coda
			if ( !this->event_list.empty() ) {

				// Ricavo il primo elemento della coda
				Event *event = this->event_list.front();

				if ( event->type == EventType::WAIT_INTERACTION ) {

					// Rimuovo il primo evento della coda
					this->PopEvent( event );

					break;
				}
			}

			break;
		}

		// Gestisco il segnale di pressione con il tasto sinistro del mouse
		case SignalType::MOUSE_LEFT_PRESSED: {

			// Controllo se il mouse è stato assegnato ad un giocatore
			if ( this->GetEngine()->GetMousePlayer() != NULL )

				this->GetEngine()->GetMousePlayer()->SendSignal( SignalType::CHECK_MOUSE_INTERACTION, this );

			break;
		}

		default: break;
	}

	// Aggiorno l'area di collisione nello spazio 2D
	this->GetCollisionArea().Update();
}

Types::Bool
Sprite::SendEvent( Event *event, Entity *other ) {

	// Flag di controllo
	Types::Bool end_event = false;

	/*
	// Controlla il tipo di evento
	switch ( event->type ) {

		// Imposto
		case 0: { 

			end_event = true;
			break;
		}

		default: break;
	}
	*/

	// Avvia il gestore degli eventi
	if ( !end_event )
		end_event = Image::SendEvent( event, other );

	return end_event;
}

void
Sprite::Update( Viewer *viewer, Player *player ) {

	// Avvio la funzione di lavoro superiore
	Image::Update( viewer, player );

	// Aggiorno l'area di collisione nello spazio 2D
	this->GetCollisionArea().Update();
}

void
Sprite::DrawCollisionRectangle( const Types::Point2D &offset ) const {

	// Ricavo il disegnatore principale
	const Designer &designer = this->GetEngine()->GetDesigner();

	// Imposto il colore del bordo del riquadro
	designer.SetColor( Color::Make( 0, 255, 0, 255 ) );

	// Imposto lo spessore della linea
	designer.SetLineWidth( 1 );

	// Disegno l'area di collisione
	designer.DrawPolygon( this->GetCollisionArea().GetPolygon(), offset );
}

void
Sprite::Draw( const Types::Point2D &offset, Color::RGBA8 blend ) const {

	// Disegno l'immagine sullo schermo
	Image::Draw( offset, blend );

	// Controllo se la modalità di debug è attiva
	if ( this->GetDebugMode() ) {

		// Disegna il rettangolo di collisione
		this->DrawCollisionRectangle( offset );
	}
}

}; // Chiudo il namespace di VGE

#endif
