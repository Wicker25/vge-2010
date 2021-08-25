/* 
    Title --- i-ruotable.cpp

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


#ifndef VGE_INTERFACE_RUOTABLE_CPP
#define VGE_INTERFACE_RUOTABLE_CPP

#include "vge/interfaces/i-ruotable.hpp"
#include "vge/interfaces/inline/i-ruotable-inl.hpp"

namespace VGE { // Namespace di VGE

InterfaceRuotable::InterfaceRuotable() {

	// Scelgo l'angolo di rotazione
	this->SetRotation( 0.0f );
}

InterfaceRuotable::~InterfaceRuotable() {

}

}; // Chiudo il namespace di VGE

#endif
