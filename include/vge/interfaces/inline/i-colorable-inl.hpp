/* 
    Title --- i-colorable-inl.hpp

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


#ifndef VGE_INTERFACE_COLORABLE_INL_HPP
#define VGE_INTERFACE_COLORABLE_INL_HPP

#include "vge/interfaces/i-colorable.hpp"

namespace VGE { // Namespace di VGE

inline void
InterfaceColorable::SetColorBlending( Types::Bool state = true ) {

	// Abilito/Disabilito il color blending per i toni ambientali
	this->color_blending = state;
}

inline Types::Bool
InterfaceColorable::GetColorBlending() const {

	// Ritorno lo stato del color blending
	return this->color_blending;
}

inline void
InterfaceColorable::SetColor( Color::RGBA8 value ) {

	// Imposto il colore
	this->color = value;
}

inline Color::RGBA8
InterfaceColorable::GetColor() const {

	// Ritorno il colore
	return this->color;
}

}; // Chiudo il namespace di VGE

#endif
