/* 
    Title --- i-animation.cpp

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


#ifndef VGE_INTERFACE_ANIMATION_CPP
#define VGE_INTERFACE_ANIMATION_CPP

#include "vge/interfaces/i-animation.hpp"

#include "vge/interfaces/i-image.hpp"
#include "vge/interfaces/inline/i-image-inl.hpp"

#include "vge/interfaces/inline/i-animation-inl.hpp"

namespace VGE { // Namespace di VGE

InterfaceAnimation::InterfaceAnimation( const std::string &path ) :

	InterfaceImage( path ) {

	// Imposto lo stato iniziale dell'animazione
	this->SetAnimationStatus( Animation::STOP );

	// Imposto la velocità dell'animazione
	this->SetAnimationSpeed( 0.2f );

	// Imposto il fattore della velocità dell'animazione
	this->SetAnimationSpeedFactor( 1.0f );

	// Imposto la serie di immagini per l'animazione
	this->SetAnimationSeries( 0 );

	// Imposto l'intervallo di fotogrammi per l'animazione
	this->SetAnimationRange( 0, 0 );

	// Imposto il fotogramma corrente dell'animazione
	this->SetAnimationFrame( 0.0f );
}

InterfaceAnimation::InterfaceAnimation( const std::string &path, const Types::Size2D_u &size_ ) :

	InterfaceImage( path, size_ ) {

	// Imposto lo stato iniziale dell'animazione
	this->SetAnimationStatus( Animation::STOP );

	// Imposto la velocità dell'animazione
	this->SetAnimationSpeed( 0.2f );

	// Imposto il fattore della velocità dell'animazione
	this->SetAnimationSpeedFactor( 1.0f );

	// Imposto la serie di immagini per l'animazione
	this->SetAnimationSeries( 0 );

	// Imposto l'intervallo di fotogrammi per l'animazione
	this->SetAnimationRange( 0, 0 );

	// Imposto il fotogramma corrente dell'animazione
	this->SetAnimationFrame( 0.0f );
}

InterfaceAnimation::~InterfaceAnimation() {

}

void
InterfaceAnimation::UpdateAnimation( Types::Float eps ) {

	// Controllo se l'animazione è stata definita
	if ( this->animation_range[0] != this->animation_range[1] ) {

		// Controllo se la riproduzione è attiva
		if ( this->GetAnimationStatus() == Animation::PLAY )

			// Scorro i frame dell'animazione
			this->animation_frame +=	this->animation_speed_factor * \
										( ( 1000.0f / this->animation_speed ) / eps );

		// Quando finiscono i frame torno al primo
		if ( this->animation_frame > (Types::Float) this->animation_range[1] )

			this->animation_frame = this->animation_range[0];

		// Imposto l'immagine del frame corrente
		this->SetClipOffset( Types::Size2D_u( (Types::Uint) this->animation_frame,
															this->animation_series ) );
	}
}

}; // Chiudo il namespace di VGE

#endif
