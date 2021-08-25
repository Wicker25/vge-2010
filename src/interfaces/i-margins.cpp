/* 
    Title --- i-margins.cpp

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


#ifndef VGE_INTERFACE_MARGINS_CPP
#define VGE_INTERFACE_MARGINS_CPP

#include "vge/interfaces/i-margins.hpp"
#include "vge/interfaces/inline/i-margins-inl.hpp"

namespace VGE { // Namespace di VGE

InterfaceMargins::InterfaceMargins() {

	// Imposto i margini iniziali
	this->SetMargins( Types::Size2D_u( 5, 5 ) );
}

InterfaceMargins::~InterfaceMargins() {

}

}; // Chiudo il namespace di VGE

#endif
