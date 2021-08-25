/* 
    Title --- i-origin-inl.hpp

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


#ifndef VGE_INTERFACE_ORIGIN_INL_HPP
#define VGE_INTERFACE_ORIGIN_INL_HPP

#include "vge/interfaces/i-origin.hpp"

namespace VGE { // Namespace di VGE

inline void
InterfaceOrigin::SetOrigin( Origin origin_ ) {

	// Imposto il punto di origine dell'entità
	this->origin = origin_;
}

inline const InterfaceOrigin::Origin &
InterfaceOrigin::GetOrigin() const {

	// Ritorno il punto di origine dell'entità
	return this->origin;
}

}; // Chiudo il namespace di VGE

#endif
