/* 
    Title --- input-manager.hpp

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


#ifndef VGE_INPUT_MANAGER_HPP
#define VGE_INPUT_MANAGER_HPP

#include <iostream>
#include <vector>
#include <list>

#include <SDL/SDL.h>

#include "vge/consts.hpp"
#include "vge/types.hpp"
#include "vge/error.hpp"
#include "vge/math.hpp"

#define JOY_AXIS_CONST	32768.0f

namespace VGE { // Namespace di VGE

class InputManager {

	/* GESTORE DEGLI EVENTI IN INGRESSO */

public:

	// Pulsanti del mouse
	typedef enum {

		MOUSE_LEFT_BUTTON = 1,	// TASTO SINISTRO DEL MOUSE
		MOUSE_MIDDLE_BUTTON,	// TASTO CENTRALE DEL MOUSE
		MOUSE_RIGHT_BUTTON,		// TASTO DESTRO DEL MOUSE

	} MouseButton;

	// Eventi del mouse
	typedef enum {

		NO_EVENT,				// NESSUN EVENTO DEL MOUSE
		BUTTON_PRESS_EVENT,		// PRESSIONE DEL PULSANTE
		BUTTON_RELEASE_EVENT,	// RILASCIO DEL PULSANTE

	} MouseEvent;

	// Lista dei joystick
	enum {

		JOYSTICK_0,
		JOYSTICK_1,
		JOYSTICK_2,
		JOYSTICK_3,
		JOYSTICK_4,
		JOYSTICK_5,
		JOYSTICK_6,
		JOYSTICK_7,
		JOYSTICK_8,
		JOYSTICK_9,
	};

	// Lista dei pulsanti del joystick
	enum {

		JOY_BUTTON_0,
		JOY_BUTTON_1,
		JOY_BUTTON_2,
		JOY_BUTTON_3,
		JOY_BUTTON_4,
		JOY_BUTTON_5,
		JOY_BUTTON_6,
		JOY_BUTTON_7,
		JOY_BUTTON_8,
		JOY_BUTTON_9,
	};

	// Lista degli assi del joystick
	enum {

		JOY_AXIS_X,
		JOY_AXIS_Y,
		JOY_N_AXIS,
	};

	// Struttura di un carattere della tastiera
	typedef struct {

		const wchar_t wchar;	// Carattere unicode del tipo "wide-character"
		const Types::Int sym;	// Simbolo del carattere

	} Key;

	// Lista dei nuovi eventi da tastiera
	typedef std::list< Key > KeyList;

	// Lista dei nuovi eventi dal joystick (pulsanti)
	typedef std::list< Types::Uint8 > JoyButtonList;

	// Struttura di un joystick
	typedef struct {

		// Puntatore al joystick
		SDL_Joystick *ptr;

		// Lista dei nuovi eventi dal joystick
		JoyButtonList button_list;

		// Stato degli assi
		Types::Float axis[2];

	} Joystick;

	// Lista dei joystick collegati
	typedef std::vector< Joystick > JoystickList;

	// Inizializza il gestore degli eventi in ingresso
	void Init();

	// Deinizializza il gestore degli eventi in ingresso
	void Close();

	// Ritorna un evento della finestra
	Types::Int GetWindowEvents( Types::Uint8 *type ) const;

	// Ritorna la dimensione dell'immagine
	const Types::Point2D &GetMousePosition() const;
	// Controlla la pressione di un tasto del mouse
	Types::Bool GetMouseButtonPress( MouseButton button ) const;
	// Controlla il rilascio di un tasto del mouse
	Types::Bool GetMouseButtonRelease( MouseButton button ) const;
	// Pulisce lo stato dei pulsanti del mouse
	void ClearMouseButtonState();

	// Imposta la visibilità del cursore del mouse
	void SetVisibleCursor( Types::Bool state );

	// Ritorna la visibilità del cursore del mouse
	Types::Bool GetVisibleCursor() const;

	// Imposta la ripetizione della tastiera
	void SetKeyRepeat( Types::Uint delay, Types::Uint interval );

	// Ritorna lo stato del tasto
	Types::Bool GetKeyState( Types::Uint key, Types::Bool blocking ) const;
	Types::Bool GetKeyState( Types::Uint key ) const;

	// Imposta la ripetizione del joystick
	void SetJoystickRepeat( Types::Uint delay, Types::Uint interval );

	// Ritorna lo stato di un pulsante di un joystick
	Types::Bool GetJoystickButtonState( Types::Uint joy, Types::Uint button );
	Types::Bool GetJoystickButtonState( Types::Uint joy, Types::Uint button, Types::Bool blocking );

	// Ritorna lo stato di un asse di un joystick
	Types::Float GetJoystickAxis( Types::Uint joy, Types::Uint axis );
	Types::Float GetJoystickAxis( Types::Uint joy, Types::Uint axis, Types::Bool blocking );

	// Ritorna la lista dei tasti premuti
	const KeyList &GetKeyList() const;

	// Aggiorna lo stato degli eventi in ingresso
	Types::Bool Update();

protected:

	// Gestisce gli eventi in ingresso
	Types::Bool ManageEvents();

	// Eventi del mouse
	MouseEvent mouse_event;
	Types::Point2D mouse_pos;
	Types::Uint8 mouse_button;

	// Flag di visibilità del cursore
	Types::Bool visible_cursor;

	// Eventi della tastiera
	Types::Uint8 *keys; Types::Int n_keys;

	// Buffer dei tasti premuti
	KeyList key_list;

	// Lista dei joystick collegati
	JoystickList joystick_list;

	// Tempo di ripetizione del joystick
	Types::Int joyrepeat[2];

	// Tempo dall'ultima pressione
	Types::Int joytime;

	// Flag di ripetizione del joystick
	Types::Bool joyrepeat_flag;

	// Inizializza il mouse
	void InitMouse();

	// Inizializza la tastiera
	void InitKeyboard();

	// Inizializza i joystick collegati
	void InitJoystick();

	// Pulisco i vecchi eventi in ingresso
	void ClearEvents();
};

}; // Chiudo il namespace di VGE

#endif
