/* 
    Title --- i-colorable.cpp

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


#ifndef VGE_INTERFACE_COLORABLE_CPP
#define VGE_INTERFACE_COLORABLE_CPP

#include "vge/interfaces/i-colorable.hpp"

#include "vge/color.hpp"
#include "vge/inline/color-inl.hpp"

#include "vge/interfaces/inline/i-colorable-inl.hpp"

namespace VGE { // Namespace di VGE

InterfaceColorable::InterfaceColorable() {

	// Abilito il color blending per i toni ambientali
	this->SetColorBlending( true );

	// Scelgo i colori iniziali iniziale
	this->SetColor( Color::Make( 255, 255, 255, 255 ) );
}

InterfaceColorable::~InterfaceColorable() {

}

}; // Chiudo il namespace di VGE

#endif
