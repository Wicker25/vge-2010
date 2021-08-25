/* 
    Title --- i-ruotable-inl.hpp

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


#ifndef VGE_INTERFACE_RUOTABLE_INL_HPP
#define VGE_INTERFACE_RUOTABLE_INL_HPP

#include "vge/interfaces/i-ruotable.hpp"

namespace VGE { // Namespace di VGE

inline void
InterfaceRuotable::SetRotation( Types::Float value ) {

	// Calcolo il nuovo angolo
	value = fmod( (float) value, 360.0f );

	// Modifico l'angolo di rotazione
	this->angle = ( value >= 0.0f ) ? value : ( 360.0f + value );
}

inline Types::Float
InterfaceRuotable::GetRotation() const {

	// Ritorno l'angolo di rotazione
	return this->angle;
}

}; // Chiudo il namespace di VGE

#endif
