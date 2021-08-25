/* 
    Title --- i-scalable.cpp

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


#ifndef VGE_INTERFACE_SCALABLE_CPP
#define VGE_INTERFACE_SCALABLE_CPP

#include "vge/interfaces/i-scalable.hpp"
#include "vge/interfaces/inline/i-scalable-inl.hpp"

namespace VGE { // Namespace di VGE

InterfaceScalable::InterfaceScalable() {

	// Scelgo la dimensione iniziale
	this->SetScale( Types::Size2D_f( 1.0f, 1.0f ) );
}

InterfaceScalable::~InterfaceScalable() {

}

}; // Chiudo il namespace di VGE

#endif
