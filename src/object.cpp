/* 
    Title --- object.cpp

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


#ifndef VGE_OBJECT_CPP
#define VGE_OBJECT_CPP

#include "vge/object.hpp"

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

#include "vge/interfaces/i-animation.hpp"
#include "vge/interfaces/inline/i-animation-inl.hpp"

#include "vge/entity.hpp"
#include "vge/inline/entity-inl.hpp"

#include "vge/image.hpp"
#include "vge/inline/image-inl.hpp"

#include "vge/sprite.hpp"
#include "vge/inline/sprite-inl.hpp"

#include "vge/viewer.hpp"
#include "vge/inline/viewer-inl.hpp"

#include "vge/scene.hpp"
#include "vge/inline/scene-inl.hpp"

#include "vge/input-manager.hpp"
#include "vge/inline/input-manager-inl.hpp"

#include "vge/engine.hpp"
#include "vge/inline/engine-inl.hpp"

#include "vge/inline/object-inl.hpp"

namespace VGE { // Namespace di VGE

Object::Object( const std::string &path ) : Sprite( path ) {

	// Imposto l'identificativo del tipo di entità
	this->SetMask( OBJECT_MASK );

	// Imposto la direzione iniziale
	this->SetDirection( DIRECTION_DOWN );

	// Imposto la velocità iniziale
	this->SetSpeed( 1.0f );

	// Imposto l'immagine faccia dell'oggetto
	this->SetFace( NULL );

	// Imposto l'indirizzo dell'ombra iniziale
	this->SetShadow( NULL );

	// Disabilità la ciclicità degli eventi
	this->SetEventLoop( false );

	// Aggiorno la profondità
	this->UpdateDepth();
}

Object::Object( const std::string &path, const Types::Size2D_u size_ ) : Sprite( path, size_ ) {

	// Imposto l'identificativo del tipo di entità
	this->SetMask( OBJECT_MASK );

	// Imposto la direzione iniziale
	this->SetDirection( DIRECTION_DOWN );

	// Imposto la velocità iniziale
	this->SetSpeed( 1.0f );

	// Imposto l'immagine faccia dell'oggetto
	this->SetFace( NULL );

	// Imposto l'indirizzo dell'ombra iniziale
	this->SetShadow( NULL );

	// Disabilità la ciclicità degli eventi
	this->SetEventLoop( false );

	// Aggiorno la profondità
	this->UpdateDepth();
}

Object::Object( const Image &image ) : Sprite( image ) {

	// Imposto l'identificativo del tipo di entità
	this->SetMask( OBJECT_MASK );

	// Imposto la direzione iniziale
	this->SetDirection( DIRECTION_DOWN );

	// Imposto la velocità iniziale
	this->SetSpeed( 1.0f );

	// Imposto l'immagine faccia dell'oggetto
	this->SetFace( NULL );

	// Imposto l'indirizzo dell'ombra iniziale
	this->SetShadow( NULL );

	// Disabilità la ciclicità degli eventi
	this->SetEventLoop( false );

	// Aggiorno la profondità
	this->UpdateDepth();
}

Object::Object( const Image &image, const Types::Size2D_u size_ ) : Sprite( image, size_ ) {

	// Imposto l'identificativo del tipo di entità
	this->SetMask( OBJECT_MASK );

	// Imposto la direzione iniziale
	this->SetDirection( DIRECTION_DOWN );

	// Imposto la velocità iniziale
	this->SetSpeed( 1.0f );

	// Imposto l'immagine faccia dell'oggetto
	this->SetFace( NULL );

	// Imposto l'indirizzo dell'ombra iniziale
	this->SetShadow( NULL );

	// Disabilità la ciclicità degli eventi
	this->SetEventLoop( false );

	// Aggiorno la profondità
	this->UpdateDepth();
}

Object::~Object() {

	// Libero la memoria
	while ( !this->event_list.empty() ) {

		// Ricavo il primo elemento della coda
		Event *event = this->event_list.front();

		// Elimino la struttura dell'evento
		free( event );

		// Elimino l'elemento dalla coda
		this->event_list.pop_front();
	}
}

void
Object::MovePosition( Types::Float x, Types::Float y, Types::Bool single_direction ) {

	// Controllo se il movimento non dev'essere fatto su un unica direzione
	if ( !single_direction )

		// Muovo l'oggetto
		Sprite::MovePosition( x * this->GetSpeed(), y * this->GetSpeed(), 0 );

	// Gestisco l'animazione dei movimenti
	if ( VABS( x ) > VABS( y ) ) {

		// Modico il fattore di velocità
		this->SetAnimationSpeedFactor( VABS( x ) * this->GetSpeed() );

		// Modifico la direzione dell'oggetto
		if ( x < 0.0f )

			this->SetDirection( DIRECTION_LEFT );
		else
			this->SetDirection( DIRECTION_RIGHT );

		// Controllo se il movimento dev'essere fatto su un unica direzione
		if ( single_direction )

			// Muovo l'oggetto orizzontalmente
			Sprite::MovePosition( x * this->GetSpeed(), 0, 0 );

	} else {

		// Modico il fattore di velocità
		this->SetAnimationSpeedFactor( VABS( y ) * this->GetSpeed() );

		// Modifico la direzione dell'oggetto
		if ( y < 0.0f )

			this->SetDirection( DIRECTION_UP );
		else
			this->SetDirection( DIRECTION_DOWN );

		// Controllo se il movimento dev'essere fatto su un unica direzione
		if ( single_direction )

			// Muovo l'oggetto orizzontalmente
			Sprite::MovePosition( 0, y * this->GetSpeed(), 0 );
	}
}

void
Object::SendSignal( Types::Int type, Entity *other ) {

	// Chiamo il gestore dei segnali
	Sprite::SendSignal( type, other );

	// Controlla il tipo di segnale
	switch ( type ) {

		// Gestisco il segnale di movimento
		case SignalType::MOTION: {

			// Emetto il segnale di movimento per passo
			this->SignalStep().emit( this->GetDirection(), this->GetSpeed(), this );

			// Aggiorna la profondità dell'oggetto
			this->UpdateDepth();
			break;
		}

		// Gestisco il segnale di cambio della direzione
		case SignalType::CHANGE_DIRECTION: {

			// Emetto il segnale di cambio della direzione
			this->SignalDirection().emit( this->GetDirection(), this );
			break;
		}

		// Gestisco il segnale di cambio della velocità
		case SignalType::CHANGE_SPEED: {

			// Emetto il segnale di cambio della velocità
			this->SignalSpeed().emit( this->GetSpeed(), this );
			break;
		}

		// Gestisco il segnale di collisione
		case SignalType::COLLISION: {

			// Controlla che ci sia almeno un elemento in coda
			if ( !this->event_list.empty() ) {

				// Ricavo il primo elemento della coda
				Event *event = this->event_list.front();

				// Controlla se l'oggetto è in movimento
				if ( event->type >= EventType::MOVE_LEFT && event->type <= EventType::MOVE_DOWN ) {

					// Inserisco l'evento di attesa della chiusura del dialogo
					this->InserEvent( EventType::WAIT_SECONDS, false )->arg0[0] = 1.0f;
				}
			}

			// Mette il personaggio nello stato inattivo
			this->SetIdle();

			break;
		}

		// Gestisco il segnale dell'interazione
		case SignalType::INTERACTION: {

			// Mostra il messaggio dell'oggetto
			if ( !this->GetMessage().empty() ) {

				this->GetEngine()->ShowSystemDialog( this->GetMessage(), this->GetFace() );

				// Metto l'oggetto nello stato inattivo
				this->SetIdle();

				// Inserisco l'evento di attesa della chiusura del dialogo
				this->InserEvent( EventType::WAIT_SECONDS, false )->arg0[0] = 1.0f;
				this->InserEvent( EventType::WAIT_DIALOG, false );
			}

			break;
		}

		default: break;
	}
}

inline Types::Bool
Object::SendEvent( Event *event, Entity *other ) {

	// Flag di controllo
	Types::Bool end_event = false;

	// Controlla il tipo di evento
	switch ( event->type ) {

		// Muovo l'oggetto a sinistra
		case EventType::MOVE_LEFT: { 

			if ( event->arg0[0] > 0.0f ) {

				this->MoveLeft();
				event->arg0[0] -= this->speed;

			} else {

				this->SetDirection( DIRECTION_LEFT );
				this->SetIdle();
				end_event = true;
			}

			break;
		}

		// Muovo l'oggetto in alto
		case EventType::MOVE_UP: { 

			if ( event->arg0[0] > 0.0f ) {

				this->MoveUp();
				event->arg0[0] -= this->speed;

			} else {

				this->SetDirection( DIRECTION_UP );
				this->SetIdle();
				end_event = true;
			}

			break;
		}

		// Muovo l'oggetto a destra
		case EventType::MOVE_RIGHT: { 

			if ( event->arg0[0] > 0.0f ) {

				this->MoveRight();
				event->arg0[0] -= this->speed;

			} else {

				this->SetDirection( DIRECTION_RIGHT );
				this->SetIdle();
				end_event = true;
			}

			break;
		}

		// Muovo l'oggetto in basso
		case EventType::MOVE_DOWN: { 

			if ( event->arg0[0] > 0.0f ) {

				this->MoveDown();
				event->arg0[0] -= this->speed;

			} else {

				this->SetDirection( DIRECTION_DOWN );
				this->SetIdle();
				end_event = true;
			}

			break;
		}

		// Cambio la velocità dell'oggetto
		case EventType::SET_SPEED: { 

			this->SetSpeed( event->arg0[0] );
			end_event = true;
			break;
		}

		// Mostro il dialogo di sistema
		case EventType::SHOW_OBJ_MESSAGE: {

			this->GetEngine()->ShowSystemDialog( event->string, this->face );
			end_event = true;
			break;
		}

		default: break;
	}

	// Avvia il gestore degli eventi
	if ( !end_event )
		end_event = Sprite::SendEvent( event, other );

	return end_event;
}

void
Object::DrawDirection( const Types::Point2D &offset ) const {

	// Ricavo il disegnatore principale
	const Designer &designer = this->GetEngine()->GetDesigner();

	// Imposto il colore del bordo del riquadro
	designer.SetColor( Color::Make( 255, 120, 0, 255 ) );

	// Imposto lo spessore della linea
	designer.SetLineWidth( 1 );

	// Disegno il centro dell'entità
	designer.DrawLine(	Types::Point2D( 0.0f, 0.0f ), 
						Types::Point2D(	-cos( VTORAD( 90.0f * this->GetDirection() ) ) * 15.0f, 
										-sin( VTORAD( 90.0f * this->GetDirection() ) ) * 15.0f ),
						this->GetPosition() + offset );
}

void
Object::DrawShadow( const Types::Point2D &offset, Color::RGBA8 blend ) const {

	// Adatto la dimensione alla scala dell'oggetto
	this->GetShadow()->SetScale( this->scale );

	// Muovo l'ombra sotto l'oggetto
	this->GetShadow()->SetPosition( Types::Point3D( this->position.x, this->position.y, VGE::Layer::SHADOW ) );

	// Disegna l'ombra dell'oggetto
	if ( !this->GetFixed() )

		this->GetShadow()->Draw( offset, blend );
	else
		this->GetShadow()->Draw( Types::Point2D(), blend );
}

void
Object::Draw( const Types::Point2D &offset, Color::RGBA8 blend ) const {

	// Disegno l'ombra dell'oggetto
	if ( this->GetShadow() != NULL )

		this->DrawShadow( offset, blend );

	// Disegno l'oggetto sullo schermo
	Sprite::Draw( offset, blend );

	// Controllo se la modalità di debug è attiva
	if ( this->GetDebugMode() ) {

		// Disegno la direzione dell'oggetto
		this->DrawDirection( offset );
	}
}

}; // Chiudo il namespace di VGE

#endif
