/* 
    Title --- i-clickable-inl.hpp

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


#ifndef VGE_INTERFACE_CLICKABLE_INL_HPP
#define VGE_INTERFACE_CLICKABLE_INL_HPP

#include "vge/interfaces/i-clickable.hpp"

namespace VGE { // Namespace di VGE

inline Types::Uint
InterfaceClickable::CheckMouseEvent( InputManager *input_manager, BoundingArea *area, Viewer *viewer ) {

	return InterfaceClickable::CheckMouseEvent( input_manager, area, viewer, false );
}

}; // Chiudo il namespace di VGE

#endif
