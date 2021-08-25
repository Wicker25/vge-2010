/* 
    Title --- i-clickable.hpp

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


#ifndef VGE_INTERFACE_CLICKABLE_HPP
#define VGE_INTERFACE_CLICKABLE_HPP

#include <iostream>
#include <list>
#include <cmath>

#include "vge/consts.hpp"
#include "vge/types.hpp"
#include "vge/error.hpp"
#include "vge/math.hpp"

#include "vge/bounding-area.hpp"
#include "vge/input-manager.hpp"

namespace VGE { // Namespace di VGE

namespace SignalType { // Namespace del tipo di segnale

// Tipo del segnale
enum {

	MOUSE_NO_EVENT = 50,	// SEGNALE DI NESSUN EVENTO DEL MOUSE
	MOUSE_SELECTION,		// SEGNALE DI SELEZIONE CON IL MOUSE
	MOUSE_LEFT_PRESSED,		// SEGNALE DI PRESSIONE DEL TASTO SINISTRO DEL MOUSE
	MOUSE_MIDDLE_PRESSED,	// SEGNALE DI PRESSIONE DEL TASTO CENTRALE DEL MOUSE
	MOUSE_RIGHT_PRESSED,	// SEGNALE DI PRESSIONE DEL TASTO DESTRO DEL MOUSE
	MOUSE_LEFT_RELEASED,	// SEGNALE DI RILASCIO DEL TASTO SINISTRO DEL MOUSE
	MOUSE_MIDDLE_RELEASED,	// SEGNALE DI RILASCIO DEL TASTO CENTRALE DEL MOUSE
	MOUSE_RIGHT_RELEASED,	// SEGNALE DI RILASCIO DEL TASTO DESTRO DEL MOUSE
};

}; // Chiudo il namespace del tipo di segnale


// Prototipi
class Player;
class Viewer;

class InterfaceClickable {

	/* INTERFACCIA CLICCABILE */

public:

	// Metodi costruttore e distruttore
	InterfaceClickable();
	virtual ~InterfaceClickable();

protected:

	// Cerca un evento del mouse
	virtual Types::Uint CheckMouseEvent(	InputManager *input_manager,
											BoundingArea *area, Viewer *viewer );

	virtual Types::Uint CheckMouseEvent(	InputManager *input_manager,
											BoundingArea *area, Viewer *viewer, Types::Bool fixed );
};

}; // Chiudo il namespace di VGE

#endif
