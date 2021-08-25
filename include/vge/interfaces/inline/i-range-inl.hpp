/* 
    Title --- i-range-inl.hpp

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


#ifndef VGE_INTERFACE_RANGE_INL_HPP
#define VGE_INTERFACE_RANGE_INL_HPP

#include "vge/interfaces/i-range.hpp"

namespace VGE { // Namespace di VGE

inline void
InterfaceRange::SetRange( const Types::Size2D_f &range_ ) {

	// Imposto l'intervallo di valori
	this->range = range_;
}

inline Types::Size2D_f
InterfaceRange::GetRange() const {

	// Ritorno l'intervallo di valori
	return this->range;
}

inline void
InterfaceRange::SetFraction( Types::Float value ) {

	// Imposto la frazione corrente
	this->fraction = VMAX( 0.0f, VMIN( value, 1.0f ) );
}

inline Types::Float
InterfaceRange::GetFraction() const {

	// Ritorno la frazione corrente
	return this->fraction;
}

inline void
InterfaceRange::SetValue( Types::Float value ) {

	// Imposto il valore del cursore
	this->SetFraction( ( this->GetRange().a - value ) / ( this->GetRange().a - this->GetRange().b ) );
}

inline Types::Float
InterfaceRange::GetValue() const {

	// Ritorno il valore del cursore
	return ( this->GetFraction() * ( this->GetRange().b - this->GetRange().a ) + this->GetRange().a );
}

inline void
InterfaceRange::SetStep( Types::Float value ) {

	// Imposto il valore del passo
	this->step = value;
}

inline Types::Float
InterfaceRange::GetStep() const {

	// Ritorno il valore del passo
	return this->step;
}

}; // Chiudo il namespace di VGE

#endif
