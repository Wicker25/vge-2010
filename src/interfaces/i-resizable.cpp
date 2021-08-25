/* 
    Title --- i-resizable.cpp

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


#ifndef VGE_INTERFACE_RESIZABLE_CPP
#define VGE_INTERFACE_RESIZABLE_CPP

#include "vge/interfaces/i-resizable.hpp"
#include "vge/interfaces/inline/i-resizable-inl.hpp"

namespace VGE { // Namespace di VGE

InterfaceResizable::InterfaceResizable() {

	// Imposto la dimensione iniziale
	this->SetSize( Types::Size2D_u( 0, 0 ) );
}

InterfaceResizable::~InterfaceResizable() {

}

}; // Chiudo il namespace di VGE

#endif
