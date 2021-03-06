/* 
    Title --- i-scalable-inl.hpp

    Copyright (C) 2010 Giacomo Trudu - wicker25[at]gmail[dot]com

    This file is part of Valentine.

    Valentine is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation version 3 of the License.

    Valentine is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with Valentine. If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef VGE_INTERFACE_SCALABLE_INL_HPP
#define VGE_INTERFACE_SCALABLE_INL_HPP

#include "vge/interfaces/i-scalable.hpp"

namespace VGE { // Namespace di VGE

inline void
InterfaceScalable::SetScale( const Types::Size2D_f &scale_ ) {

	// Modifico la proporzione
	this->scale = scale_;
}

inline void
InterfaceScalable::GetScale( Types::Size2D_f &scale_ ) const {

	// Ritorno la proporzione
	scale_ = this->scale;
}


inline const Types::Size2D_f &
InterfaceScalable::GetScale() const {

	// Ritorno la proporzione
	return this->scale;
}

}; // Chiudo il namespace di VGE

#endif
