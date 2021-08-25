/* 
    Title --- button.cpp

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


#ifndef VGE_BUTTON_CPP
#define VGE_BUTTON_CPP

#include "vge/widgets/button.hpp"

#include "vge/color.hpp"
#include "vge/inline/color-inl.hpp"

#include "vge/input-manager.hpp"
#include "vge/inline/input-manager-inl.hpp"

#include "vge/interfaces/i-margins.hpp"
#include "vge/interfaces/inline/i-margins-inl.hpp"

#include "vge/engine.hpp"
#include "vge/inline/engine-inl.hpp"

#include "vge/widgets/widget.hpp"
#include "vge/widgets/inline/widget-inl.hpp"

#include "vge/widgets/container.hpp"
#include "vge/widgets/inline/container-inl.hpp"

#include "vge/widgets/inline/button-inl.hpp"

namespace VGE { // Namespace di VGE

namespace Gui { // Namespace dell'interfaccia grafica

Button::Button() : Container( Container::ORIENTATION_VERTICAL ) {

	// Imposto l'identificativo del tipo di oggetto
	this->SetMask( CONTAINER_DERIVED_MASK );

	// Imposto lo stato iniziale del pulsate
	this->SetPressed( false );

	// Imposto il riquadro del pulsante
	this->GetBox().SetColor( Color::Make( 0, 0, 0, 80 ) );
	this->GetBox().SetBorderColor( Color::Make( 0, 0, 0, 200 ) );
	this->GetBox().SetBorderWidth( 1 );
}

Button::Button( const Types::Size2D_u size_ ) :

	Container( Container::ORIENTATION_VERTICAL ) {

	// Imposto l'identificativo del tipo di oggetto
	this->SetMask( CONTAINER_DERIVED_MASK );

	// Imposto la dimensione del pulsante
	this->SetSize( size_ );

	// Imposto lo stato del pulsante
	this->SetPressed( false );

	// Imposto il riquadro del pulsante
	this->GetBox().SetColor( Color::Make( 0, 0, 0, 80 ) );
	this->GetBox().SetBorderColor( Color::Make( 0, 0, 0, 200 ) );
	this->GetBox().SetBorderWidth( 1 );
}

Button::~Button() {

}

void
Button::SendSignal( Types::Int type, Entity *other ) {

	// Chiamo il gestore dei segnali
	Container::SendSignal( type, other );

	// Controlla il tipo di segnale
	switch ( type ) {

		// Gestisco il segnale di pressione con il tasto sinistro del mouse
		case SignalType::MOUSE_LEFT_PRESSED: {

			// Invio il segnale di pressione del pulsante
			this->SendSignal( SignalType::BUTTON_PRESSED, NULL );

			break;
		}

		// Gestisco il segnale di pressione con il tasto sinistro del mouse
		case SignalType::MOUSE_LEFT_RELEASED: {

			// Invio il segnale di rilascio del pulsante
			this->SendSignal( SignalType::BUTTON_RELEASED, NULL );

			break;
		}

		// Gestisco il segnale di pressione del pulsante
		case SignalType::BUTTON_PRESSED: {

			// Imposto lo stato del pulsante
			this->SetPressed( true );

			// Emetto il segnale di pressione del pulsante
			this->SignalPressed().emit( this );

			break;
		}

		// Gestisco il segnale di rilascio del pulsante
		case SignalType::BUTTON_RELEASED: {

			// Imposto lo stato del pulsante
			this->SetPressed( false );

			// Emetto il segnale di rilascio del pulsante
			this->SignalReleased().emit( this );

			break;
		}

		default: break;
	}
}

void
Button::Update( Viewer *viewer, Player *player ) {

	// Chiamo la funzione di aggiornamento
	Container::Update( viewer, player );

	// Ricavo il gestore degli eventi in ingresso
	InputManager &input_manager = this->GetEngine()->GetInputManager();

	// Gestisco la pressione del pulsante
	if ( this->GetFocus() ) {

		// Controllo che sia stato premuto sul pulsante
		if (	input_manager.GetKeyState( SDLK_RETURN, true ) ||
				input_manager.GetJoystickButtonState(	InputManager::JOYSTICK_0,
														InputManager::JOY_BUTTON_0, true ) ) {

			// Invio il segnale di pressione del pulsante
			this->SendSignal( SignalType::BUTTON_PRESSED, NULL );

			// Invio il segnale di rilascio del pulsante
			this->SendSignal( SignalType::BUTTON_RELEASED, NULL );
		}
	}

	// Controllo se sia stato rilasciato il pulsante del mouse
	if ( this->GetPressed() && input_manager.GetMouseButtonRelease( InputManager::MOUSE_LEFT_BUTTON ) ) {

		// Invio il segnale di rilascio del pulsante
		this->SendSignal( SignalType::BUTTON_RELEASED, NULL );
	}
}

}; // Chiudo il namespace dell'interfaccia grafica

}; // Chiudo il namespace di VGE

#endif
