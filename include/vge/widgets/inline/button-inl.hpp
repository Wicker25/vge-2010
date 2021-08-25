/* 
    Title --- button-inl.hpp

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


#ifndef VGE_BUTTON_INL_HPP
#define VGE_BUTTON_INL_HPP

#include "vge/widgets/button.hpp"

namespace VGE { // Namespace di VGE

namespace Gui { // Namespace dell'interfaccia grafica

inline void
Button::SetPressed( Types::Bool state ) {

	// Imposto lo stato del pulsante
	this->pressed = state;
}

inline Types::Bool
Button::GetPressed() const {

	// Ritorno lo stato del pulsante
	return this->pressed;
}

inline sigc::signal< void, Button * > &
Button::SignalPressed() {

	// Ritorno l'istanza del segnale di pressione
	return this->signal_pressed;
}

inline sigc::signal< void, Button * > &
Button::SignalReleased() {

	// Ritorno l'istanza del segnale di rilascio
	return this->signal_released;
}

}; // Chiudo il namespace dell'interfaccia grafica

}; // Chiudo il namespace di VGE

#endif
