/* 
    Title --- i-animation-inl.hpp

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


#ifndef VGE_INTERFACE_ANIMATION_INL_HPP
#define VGE_INTERFACE_ANIMATION_INL_HPP

#include "vge/interfaces/i-animation.hpp"

namespace VGE { // Namespace di VGE

inline void
InterfaceAnimation::SetAnimationStatus( Animation::Status state ) {

	// Imposto la serie di immagini per l'animazione
	this->animation_status = state;

	// Eventualmente torno al primo fotogramma
	if ( state == Animation::STOP )

		this->SetAnimationFrame( this->animation_range[0] );
}

inline Animation::Status
InterfaceAnimation::GetAnimationStatus() const {

	// Ritorno la serie di immagini per l'animazione
	return this->animation_status;
}

inline void
InterfaceAnimation::SetAnimationSpeed( Types::Float value ) {

	// Imposto la velocità dell'animazione (in millisecondi)
	this->animation_speed = value;
}

inline Types::Float
InterfaceAnimation::GetAnimationSpeed() const {

	// Ritorno la velocità dell'animazione (in millisecondi)
	return this->animation_speed;
}

inline void
InterfaceAnimation::SetAnimationSpeedFactor( Types::Float value ) {

	// Imposto il fattore della velocità dell'animazione
	this->animation_speed_factor = value;
}

inline Types::Float
InterfaceAnimation::GetAnimationSpeedFactor() const {

	// Ritorno il fattore della velocità dell'animazione
	return this->animation_speed_factor;
}

inline void
InterfaceAnimation::SetAnimationSeries( Types::Uint value ) {

	// Se la serie è cambiata torno al primo fotogramma
	if ( value != this->GetAnimationSeries() )

		this->SetAnimationFrame( this->animation_range[0] );

	// Imposto la serie di immagini per l'animazione
	this->animation_series = value;
}

inline Types::Uint
InterfaceAnimation::GetAnimationSeries() const {

	// Ritorno la serie di immagini per l'animazione
	return this->animation_series;
}

inline void
InterfaceAnimation::SetAnimationRange( Types::Uint start, Types::Uint end ) {

	// Imposto l'intervallo di fotogrammi per l'animazione
	this->animation_range[0] = start;
	this->animation_range[1] = end;

	// Vado al primo fotogramma
	this->SetAnimationFrame( (Types::Float) start );
}

inline void
InterfaceAnimation::GetAnimationRange( Types::Uint *start, Types::Uint *end ) const {

	// Ritorno l'intervallo di fotogrammi per l'animazione
	if ( start != NULL ) *start = this->animation_range[0];
	if ( end != NULL ) *end = this->animation_range[1];
}

inline void
InterfaceAnimation::SetAnimationFrame( Types::Uint value ) {

	// Imposto il fotogramma corrente dell'animazione
	this->animation_frame = (Types::Float) value;
}

inline Types::Uint
InterfaceAnimation::GetAnimationFrame() const {

	// Ritorno il fotogramma corrente dell'animazione
	return (Types::Uint) this->animation_frame;
}

}; // Chiudo il namespace di VGE

#endif
