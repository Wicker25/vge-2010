/* 
    Title --- player.cpp

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


#ifndef VGE_PLAYER_CPP
#define VGE_PLAYER_CPP

#include "vge/player.hpp"

#include "vge/mixer.hpp"
#include "vge/inline/mixer-inl.hpp"

#include "vge/entity.hpp"
#include "vge/inline/entity-inl.hpp"

#include "vge/sprite.hpp"
#include "vge/inline/sprite-inl.hpp"

#include "vge/object.hpp"
#include "vge/inline/object-inl.hpp"

#include "vge/character.hpp"
#include "vge/inline/character-inl.hpp"

#include "vge/viewer.hpp"
#include "vge/inline/viewer-inl.hpp"

#include "vge/scene.hpp"
#include "vge/inline/scene-inl.hpp"

#include "vge/input-manager.hpp"
#include "vge/inline/input-manager-inl.hpp"

#include "vge/engine.hpp"
#include "vge/inline/engine-inl.hpp"

#include "vge/widgets/message-box.hpp"
#include "vge/widgets/inline/message-box-inl.hpp"

#include "vge/inline/player-inl.hpp"

namespace VGE { // Namespace di VGE

Player::Player( const std::string &path, const Types::Size2D_u size_, Types::Uint n_frames ) :

	Character( path, size_, n_frames ) {

	// Imposto l'identificativo del tipo di entità
	this->SetMask( PLAYER_MASK );

	// Inizializzo le strutture
	this->interaction = false;

	// Invio il segnale di cambio di direzione
	this->SendSignal( SignalType::CHANGE_DIRECTION, NULL );
}

Player::Player( const Image &image, const Types::Size2D_u size_, Types::Uint n_frames ) :

	Character( image, size_, n_frames ) {

	// Imposto l'identificativo del tipo di entità
	this->SetMask( PLAYER_MASK );

	// Inizializzo le strutture
	this->interaction = false;

	// Invio il segnale di cambio di direzione
	this->SendSignal( SignalType::CHANGE_DIRECTION, NULL );
}

Player::~Player() {

}

void
Player::SendSignal( Types::Int type, Entity *other ) {

	// Chiamo il gestore dei segnali
	Character::SendSignal( type, other );

	// Controlla il tipo di segnale
	switch ( type ) {

		// Gestisco il segnale di movimento
		case SignalType::MOTION: { 

			// Aggiorno la posizione dell'ascoltatore del mixer
			if ( this->GetEngine() != NULL )
				this->GetEngine()->GetMixer().SetListenerPosition( this->position );

			// Aggiorno la posizione dell'area di interazione
			this->GetInteractionArea().SetPosition( this->position );
			break;
		}

		// Gestisco il segnale di modifica della scala
		case SignalType::RESIZING: { 

			// Aggiorno la dimensione dell'area di interazione
			this->GetInteractionArea().SetRectangle( this->size, this->center );
			break;
		}

		// Gestisco il segnale di modifica della scala
		case SignalType::SCALING: { 

			// Aggiorno la scala dell'area di interazione
			this->GetInteractionArea().SetScale( this->scale );
			break;
		}

		// Gestisco il segnale di cambio di direzione
		case SignalType::CHANGE_DIRECTION: { 

			// Aggiorno la rotazione dell'area di interazione
			this->GetInteractionArea().SetRotation( 90.0f * this->GetDirection() );
			break;
		}

		// Gestisco il segnale di interazione
		case SignalType::CHECK_INTERACTION:
		// Gestisco il segnale di interazione attraverso il mouse
		case SignalType::CHECK_MOUSE_INTERACTION: {

			// Controllo se si è attiva l'interazione
			if ( this->interaction || type == SignalType::CHECK_MOUSE_INTERACTION ) {

				// Emetto il segnale di ricerca dell'interazione
				this->SignalCheckInteration().emit( VGE_PLAYER( this ), VGE_SPRITE( other ) );

				// Controllo che il dialogo di sistema non sia già stato aperto
				if ( !this->GetEngine()->SystemDialogIsOpen() ) {

					// Invio il segnale di interazione
					VGE_ENTITY( other )->SendSignal( SignalType::INTERACTION, this );

				} else {

					// Ricavo il puntatore al dialogo di sistema
					Gui::MessageBox &dialog = this->GetEngine()->GetSystemDialog();

					// Controllo che non si sia arrivati all'ultima pagina
					if ( !dialog.GetTextBox().IsLastPage() )

						// Vado alla pagina successiva
						dialog.GetTextBox().NextPage();
					else
						// Nascondo il dialogo di sistema
						this->GetEngine()->HideSystemDialog();
				}
			}

			break;
		}

		default: break;
	}

	// Aggiorno l'area di interazione nello spazio 2D
	this->GetInteractionArea().Update();
}

void
Player::Update( Viewer *viewer, Player *player ) {

	// Avvio la funzione di lavoro superiore
	Character::Update( viewer, player );

	// Ricavo il gestore degli eventi in ingresso
	InputManager &events = this->GetEngine()->GetInputManager();

	// Collego l'interazione al tasto invio
	this->interaction = (	events.GetKeyState( SDLK_RETURN, true ) ||
							events.GetJoystickButtonState(	InputManager::JOYSTICK_0,
															InputManager::JOY_BUTTON_0, true ) );

	// Controllo che il dialogo di sistema sia stato aperto
	if ( this->GetEngine()->SystemDialogIsOpen() ) {

		// Controllo si stia cercando una nuova interazione
		if ( this->interaction ) {

			// Ricavo il puntatore al dialogo di sistema
			Gui::MessageBox &dialog = this->GetEngine()->GetSystemDialog();

			// Controllo che non si sia arrivati all'ultima pagina
			if ( !dialog.GetTextBox().IsLastPage() )

				// Vado alla pagina successiva
				dialog.GetTextBox().NextPage();
			else
				// Nascondo il dialogo di sistema
				this->GetEngine()->HideSystemDialog();

			// Sopprimo le altre interazioni
			this->interaction = false;
		}

		// Metto il personaggio nello stato inattivo
		this->SetIdle();
	}
	
	// Controllo che il dialogo di sistema non sia stato aperto
	if ( !this->GetEngine()->SystemDialogIsOpen() ) {

		// Ricava lo stato degli assi del joystick
		Types::Float ax = events.GetJoystickAxis( InputManager::JOYSTICK_0, InputManager::JOY_AXIS_X );
		Types::Float ay = events.GetJoystickAxis( InputManager::JOYSTICK_0, InputManager::JOY_AXIS_Y );

		// Gestisco i movimenti del giocatore
		if ( events.GetKeyState( SDLK_LEFT ) )

			this->MoveLeft();

		else if ( events.GetKeyState( SDLK_UP ) )

			this->MoveUp();

		else if ( events.GetKeyState( SDLK_RIGHT ) )

			this->MoveRight();

		else if ( events.GetKeyState( SDLK_DOWN ) )

			this->MoveDown();

		else if ( VABS( ax ) + VABS( ay ) > 0.1f ) {

			this->MovePosition( ax, ay );

		} else
			// Imposto lo stato inativo
			this->SetIdle();
	};

	// Aggiorno l'area di interazione nello spazio 2D
	this->GetInteractionArea().Update();
}

void
Player::DrawInteractionRectangle( const Types::Point2D &offset ) const {

	// Ricavo il disegnatore principale
	const Designer &designer = this->GetEngine()->GetDesigner();

	// Imposto il colore del bordo del riquadro
	designer.SetColor( Color::Make( 0, 0, 255, 255 ) );

	// Imposto lo spessore della linea
	designer.SetLineWidth( 1 );

	// Disegno l'area di interazione
	designer.DrawPolygon( this->GetInteractionArea().GetPolygon(), offset );
}

void
Player::Draw( const Types::Point2D &offset, Color::RGBA8 blend ) const {

	// Controllo se la modalità di debug è attiva
	if ( this->GetDebugMode() ) {

		// Disegno il rettangolo di interazione
		this->DrawInteractionRectangle( offset );
	}

	// Disegno l'immagine sullo schermo
	Character::Draw( offset, blend );
}

}; // Chiudo il namespace di VGE

#endif
