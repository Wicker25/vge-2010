/* 
    Title --- box-inl.hpp

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


#ifndef VGE_BOX_INL_HPP
#define VGE_BOX_INL_HPP

#include "vge/widgets/box.hpp"

namespace VGE { // Namespace di VGE

namespace Gui { // Namespace dell'interfaccia grafica

inline void
Box::SetBorderColor( Color::RGBA8 value ) {

	// Modifico i colori della cornice
	this->border_color = value;
}

inline Color::RGBA8
Box::GetBorderColor() const {

	// Ritorno i colori della cornice
	return this->border_color;
}

inline void
Box::SetBorderWidth( Types::Uint8 width ) {

	// Modifico lo spessore della cornice
	this->border_width = width;
}

inline Types::Uint8
Box::GetBorderWidth() const {

	// Ritorno lo spessore della cornice
	return this->border_width;
}

inline void
Box::SetFilled( Types::Bool state ) {

	// Modifico il flag del riempimento
	this->filled = state;
}

inline Types::Bool
Box::GetFilled() const {

	// Ritorno il flag del riempimento
	return this->filled;
}

inline void
Box::SetOpacity( Types::Uint8 value ) {

	// Imposto la opacità del widget
	this->opacity = value;
}

inline Types::Uint8
Box::GetOpacity() const {

	// Ritorno la opacità del widget
	return this->opacity;
}

}; // Chiudo il namespace dell'interfaccia grafica

}; // Chiudo il namespace di VGE

#endif
