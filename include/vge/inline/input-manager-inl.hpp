/* 
    Title --- input-manager-inl.hpp

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


#ifndef VGE_INPUT_MANAGER_INL_HPP
#define VGE_INPUT_MANAGER_INL_HPP

#include "vge/input-manager.hpp"

namespace VGE { // Namespace di VGE

inline Types::Int
InputManager::GetWindowEvents( Types::Uint8 *type ) const {

	// Eventi della finestra
	SDL_Event w_event;

	// Leggo un evento della finestra
	Types::Int tot = SDL_PollEvent( &w_event );

	// Ritorno il tipo dell'evento
	if ( type != NULL ) *type = w_event.type;

	return tot;
}

inline const Types::Point2D &
InputManager::GetMousePosition() const {

	// Ritorno la dimensione dell'immagine
	return this->mouse_pos;
}

inline Types::Bool
InputManager::GetMouseButtonPress( MouseButton button ) const {

	// Stato del pulsante del mouse
	Types::Bool state;

	// Controllo la pressione di un tasto del mouse
	state = ( this->mouse_event == BUTTON_PRESS_EVENT ) && ( this->mouse_button & SDL_BUTTON( (int) button ) );

	// Ritorno lo stato del pulsante del mouse
	return state;
}

inline Types::Bool
InputManager::GetMouseButtonRelease( MouseButton button ) const {

	// Stato del pulsante del mouse
	Types::Bool state;

	// Controllo il rilascio di un tasto del mouse
	state = ( this->mouse_event == BUTTON_RELEASE_EVENT ) && ( this->mouse_button & SDL_BUTTON( (int) button ) );

	// Ritorno lo stato del pulsante del mouse
	return state;
}

inline void
InputManager::ClearMouseButtonState() {

	// Pulisce lo stato dei pulsanti del mouse
	this->mouse_button = 0;
}

inline void
InputManager::SetVisibleCursor( Types::Bool state ) {

	// Imposto la visibilità del cursore del mouse
	SDL_ShowCursor( state );

	// Modifico il flag di visibilità del cursore del mouse
	this->visible_cursor = state;
}

inline Types::Bool
InputManager::GetVisibleCursor() const {

	// Ritorno la visibilità del cursore del mouse
	return this->visible_cursor;
}

inline void
InputManager::SetKeyRepeat( Types::Uint delay, Types::Uint interval ) {

	// Imposta la ripetizione della tastiera
	SDL_EnableKeyRepeat( delay, interval );
}

inline Types::Bool
InputManager::GetKeyState( Types::Uint key ) const {

	// Ritorno lo stato del tasto
	return ( (Types::Int) key < this->n_keys ) && this->keys[key];
}

inline const InputManager::KeyList &
InputManager::GetKeyList() const {

	// Ritorno la stringa presa in ingresso
	return this->key_list;
}

inline void
InputManager::SetJoystickRepeat( Types::Uint delay, Types::Uint interval ) {

	// Imposto la ripetizione del joystick
	this->joyrepeat[0] = delay;
	this->joyrepeat[1] = interval;
}

inline Types::Bool
InputManager::GetJoystickButtonState( Types::Uint joy, Types::Uint button ) {

	// Ritorno lo stato del pulsante del joystick
	return this->GetJoystickButtonState( joy, button, false );
}

inline Types::Float
InputManager::GetJoystickAxis( Types::Uint joy, Types::Uint axis ) {

	// Ritorno lo stato di un asse di un joystick
	return this->GetJoystickAxis( joy, axis, false );
}

}; // Chiudo il namespace di VGE

#endif
