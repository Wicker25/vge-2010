/* 
    Title --- input-manager.cpp

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


#ifndef VGE_INPUT_MANAGERS_CPP
#define VGE_INPUT_MANAGERS_CPP

#include "vge/input-manager.hpp"
#include "vge/inline/input-manager-inl.hpp"

namespace VGE { // Namespace di VGE

void
InputManager::Init() {

	// Log di lavoro
	printf( "<Devices>\n" );

	// Inizializzo la gestione del Joystick
	if ( SDL_InitSubSystem( SDL_INIT_JOYSTICK ) != 0 ) {

		fprintf( stderr, "(!) Could not initialize Joystick: %s\n", SDL_GetError() );
		exit(1);
	}

	// Inizializzo il mouse
	this->InitMouse();

	// Inizializzo la tastiera
	this->InitKeyboard();

	// Inizializzo i joystick collegati
	this->InitJoystick();

	// Log di lavoro
	printf( "</Devices>\n" );
}

void
InputManager::InitMouse() {

	// Log di lavoro
	printf( " Loading mouse... " );

	// Inizializzo le strutture del mouse
	this->mouse_event	= NO_EVENT;
	this->mouse_button	= 0;

	// Mostro il cursore del mouse
	this->SetVisibleCursor( true );

	// Log di lavoro
	printf( "done\n" );
}

void
InputManager::InitKeyboard() {

	// Log di lavoro
	printf( " Loading keyboard... " );

	// Imposto il formato unicode per i dati in ingresso
	SDL_EnableUNICODE( SDL_ENABLE );

	// Imposta la ripetizione della tastiera
	this->SetKeyRepeat( 400, 30 );

	// Inizializzo la tastiera
	this->keys = SDL_GetKeyState( &this->n_keys );

	// Log di lavoro
	printf( "done\n" );
}

void
InputManager::InitJoystick() {

	// Disabilito il flag di ripetizione del joystick
	this->joyrepeat_flag = false;

	// Imposta la ripetizione del joystick
	this->SetJoystickRepeat( 400, 30 );

	// Numero dei joystick collegati
	const Types::Uint size = SDL_NumJoysticks();

	// Iteratore
	Types::Uint i = 0;

	// Inizializzo tutti i joystick collegati
	for ( ; i < size; i++ ) {

		// Creo la struttura del nuovo joystick
		Joystick joystick;

		// Inizializzo il joystick
		joystick.ptr = SDL_JoystickOpen( i );

		// Log di lavoro
		printf( " Loading \"%s\"... ", SDL_JoystickName( i ) );

		// Verifico che il joystick sia compatibile
		if ( !SDL_JoystickNumAxes( joystick.ptr ) < JOY_N_AXIS ) {

			// Aggiungo il joystick alla lista
			this->joystick_list.push_back( joystick );

			// Log di lavoro
			printf( "done\n" );

		} else {

			// Deinizializzo il joystick
			SDL_JoystickClose( joystick.ptr );

			// Log di lavoro
			printf( "failed\n" );
		}
	}
}

void
InputManager::Close() {

	// Numero dei joystick collegati
	const Types::Uint size = SDL_NumJoysticks();

	// Iteratore
	Types::Uint i = 0;

	// Deinizializzo tutti i joystick collegati
	for ( ; i < size; i++ ) {

		// Deinizializzo il joystick
		SDL_JoystickClose( this->joystick_list[i].ptr );
	}

	// Deinizializzo la gestione del Joystick
	SDL_QuitSubSystem( SDL_INIT_JOYSTICK );
}
  
Types::Bool
InputManager::GetKeyState( Types::Uint key, Types::Bool blocking ) const {

	// Flag di stato
	Types::Bool state = false;

	// Controllo l'esistenza del carattere
	if ( (Types::Int) key < this->n_keys ) {

		// Controllo se si vuole attendere il rilascio del tasto
		if ( blocking ) {

			// Iteratori
			KeyList::const_iterator iter = this->GetKeyList().begin();
			KeyList::const_iterator end = this->GetKeyList().end();

			// Applico i nuovi caratteri alla stringa
			for ( ; iter != end && !state; iter++ )
				if ( iter->sym == (Types::Int) key ) state = true;

		} else state = this->keys[key];
	}

	// Ritorno lo stato del tasto
	return state;
}

Types::Bool
InputManager::GetJoystickButtonState( Types::Uint joy, Types::Uint button, Types::Bool blocking ) {

	// Stato del pulsante del mouse
	Types::Bool state = false;

	// Verifico l'esistenza del joystick
	if (	joy < this->joystick_list.size() &&
			button < (Types::Uint) SDL_JoystickNumButtons( this->joystick_list[joy].ptr ) ) {

		// Controllo se si vuole attendere il rilascio del pulsante
		if ( blocking ) {

			// Calcolo il tempo passato
			Types::Int time = SDL_GetTicks() - this->joytime;

			// Gestisco la ripetizione del pulsante
			if (	time >= this->joyrepeat[0] &&
					SDL_JoystickGetButton( this->joystick_list[joy].ptr, button ) ) {

				state = true;

				// Modifico il momento della pressione
				this->joytime = SDL_GetTicks() - this->joyrepeat[0];

				// Imposto il flag di ripetizione del joystick
				this->joyrepeat_flag = true;

			} else {

				// Iteratori
				JoyButtonList::const_iterator iter = this->joystick_list[joy].button_list.begin();
				JoyButtonList::const_iterator end = this->joystick_list[joy].button_list.end();

				// Applico i nuovi caratteri alla stringa
				for ( ; iter != end && !state; iter++ )
					if ( (*iter) == button ) state = true;
			}

		// Controllo lo stato del pulsante
		} else state = SDL_JoystickGetButton( this->joystick_list[joy].ptr, button );
	}

	// Ritorno lo stato del pulsante del joystick
	return state;
}

Types::Float
InputManager::GetJoystickAxis( Types::Uint joy, Types::Uint axis, Types::Bool blocking ) {

	// Asse del joystick
	Types::Float value = 0.0f;

	// Verifico l'esistenza del joystick
	if ( joy < this->joystick_list.size() && (Types::Int) axis < JOY_N_AXIS ) {

		// Controllo se si deve attendere il ripristino dell'asse
		if ( blocking ) {

			// Calcolo il tempo passato
			Types::Int time = SDL_GetTicks() - this->joytime;

			// Gestisco la ripetizione del pulsante
			if (	time >= this->joyrepeat[0] &&
					SDL_JoystickGetAxis( this->joystick_list[joy].ptr, axis ) ) {

				value = ( (Types::Float) SDL_JoystickGetAxis( this->joystick_list[joy].ptr, axis ) \
																/ JOY_AXIS_CONST );

				// Modifico il momento della pressione
				this->joytime = SDL_GetTicks() - this->joyrepeat[0];

				// Imposto il flag di ripetizione del joystick
				this->joyrepeat_flag = true;

			} else {

				// Ritorno lo stato di un asse di un joystick
				value = ( this->joystick_list[joy].axis[axis] / JOY_AXIS_CONST );
			}

		} else {

			// Ritorno lo stato di un asse di un joystick
			value = ( (Types::Float) SDL_JoystickGetAxis( this->joystick_list[joy].ptr, axis ) \
															/ JOY_AXIS_CONST );
		}
	}

	// Ritorno lo stato di un asse di un joystick
	return value;
}

Types::Bool
InputManager::Update() {

	// Gestisco gli eventi in ingresso
	Types::Bool end_game = this->ManageEvents();

	return end_game;
}

void
InputManager::ClearEvents() {

	// Pulisco la lista degli eventi da tastiera
	this->key_list.clear();

	// Numero dei joystick collegati
	const Types::Uint size = this->joystick_list.size();

	// Iteratore
	Types::Uint i = 0;

	// Pulisco la lista degli eventi dal joystick
	for ( ; i < size; i++ ) {

		this->joystick_list[i].button_list.clear();
		this->joystick_list[i].axis[JOY_AXIS_X] = 0.0f;
		this->joystick_list[i].axis[JOY_AXIS_Y] = 0.0f;
	}
}

Types::Bool
InputManager::ManageEvents() {

	// Flag di uscita
	Types::Bool end_game = false;

	// Pulisco i vecchi eventi in ingresso
	this->ClearEvents();

	/* MOUSE */

	// Azzero gli eventi del mouse
	this->mouse_event = NO_EVENT;

	/* TASTIERA E JOYSTICK */

	// Controllo se il flag di ripetizione del joystick è impostato
	if ( this->joyrepeat_flag ) {

		// Aggiungo una piccola pausa tra una ripetizione e l'altra
		this->joytime += this->joyrepeat[1];

		// Disabilito il flag di ripetizione del joystick
		this->joyrepeat_flag = false;
	}


	// Eventi della finestra
	SDL_Event event;

	// Analizzo la lista dei nuovi eventi
	while ( SDL_PollEvent( &event ) ) {

		switch ( event.type ) {

			// Gestisco il movimento del puntatore del mouse
			case SDL_MOUSEMOTION: {

				// Aggiorno la posizione del puntatore del mouse
				this->mouse_pos.x = event.motion.x;
				this->mouse_pos.y = event.motion.y;

				break;
			}

			// Gestisco la pressione dei pulsanti del mouse
			case SDL_MOUSEBUTTONDOWN: {

				// Aggiorno lo stato del mouse
				this->mouse_event = BUTTON_PRESS_EVENT;

				// Memorizzo il pulsante premuto
				this->mouse_button = event.button.button;

				break;
			}

			// Gestisco il rilascio dei pulsanti del mouse
			case SDL_MOUSEBUTTONUP: {

				// Aggiorno lo stato del mouse
				this->mouse_event = BUTTON_RELEASE_EVENT;

				// Memorizzo il pulsante premuto
				this->mouse_button = event.button.button;

				break;
			}

			// Memorizzo i nuovi eventi della tastiera
			case SDL_KEYDOWN: {

				// Creo la struttura del nuovo evento della tastiera
				Key chr = { (wchar_t) event.key.keysym.unicode, event.key.keysym.sym };

				// Aggiungo l'evento della tastiera alla lista
				this->key_list.push_back( chr );

				break;
			}

			// Memorizzo i nuovi eventi dal joystick (assi)
			case SDL_JOYAXISMOTION: {

				Joystick &joy_ev = this->joystick_list[event.jbutton.which];
				joy_ev.axis[event.jaxis.axis] = ( (Types::Float) event.jaxis.value / JOY_AXIS_CONST );

				// Memorizzo il momento della pressione
				this->joytime = SDL_GetTicks();

				break;
			}

			// Memorizzo i nuovi eventi dal joystick (pulsanti)
			case SDL_JOYBUTTONDOWN: {

				// Ricavo la lista degli eventi del joystick
				JoyButtonList &button_list = this->joystick_list[event.jbutton.which].button_list;

				// Aggiungo l'evento della tastiera alla lista
				button_list.push_back( event.jbutton.button );

				// Memorizzo il momento della pressione
				this->joytime = SDL_GetTicks();

				break;
			}

			// Memorizzo l'evento di uscita
			case SDL_QUIT: {

				end_game = true;
				break;
			}
		}
	}

	return end_game;
}

}; // Chiudo il namespace di VGE

#endif
