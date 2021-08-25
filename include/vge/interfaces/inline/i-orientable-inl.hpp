/* 
    Title --- i-orientable-inl.hpp

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


#ifndef VGE_INTERFACE_ORIENTABLE_INL_HPP
#define VGE_INTERFACE_ORIENTABLE_INL_HPP

#include "vge/interfaces/i-orientable.hpp"

namespace VGE { // Namespace di VGE

inline void
InterfaceOrientable::SetOrientation( Orientation orientation_ ) {

	// Imposto l'orientamento dell'entità
	this->orientation = orientation_;
}

inline const InterfaceOrientable::Orientation &
InterfaceOrientable::GetOrientation() const {

	// Ritorno l'orientamento dell'entità
	return this->orientation;
}

}; // Chiudo il namespace di VGE

#endif
