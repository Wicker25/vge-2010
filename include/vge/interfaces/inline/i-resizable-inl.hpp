/* 
    Title --- i-resizable-inl.hpp

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


#ifndef VGE_INTERFACE_RESIZABLE_INL_HPP
#define VGE_INTERFACE_RESIZABLE_INL_HPP

#include "vge/interfaces/i-resizable.hpp"

namespace VGE { // Namespace di VGE

inline void
InterfaceResizable::SetSize( const Types::Size2D_u &size_ ) {

	// Imposto la dimensione
	this->size = size_;
}

inline Types::Size2D_u
InterfaceResizable::GetSize() const {

	// Ritorno la dimensione
	return this->size;
}

}; // Chiudo il namespace di VGE

#endif
