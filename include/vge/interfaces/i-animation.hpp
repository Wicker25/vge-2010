/* 
    Title --- i-animation.hpp

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


#ifndef VGE_INTERFACE_ANIMATION_HPP
#define VGE_INTERFACE_ANIMATION_HPP

#include <iostream>
#include <cmath>

#include "vge/consts.hpp"
#include "vge/types.hpp"
#include "vge/error.hpp"
#include "vge/math.hpp"

#include "vge/interfaces/i-image.hpp"

namespace VGE { // Namespace di VGE

namespace Animation { // Namespace dello stato dell'animazione

// Stato dell'animazione
typedef enum {

	PLAY,	// RIPRODUCI
	PAUSE,	// PAUSA
	STOP,	// FERMA

} Status;

}; // Chiudo il namespace dello stato dell'animazione

class InterfaceAnimation : public InterfaceImage {

	/* INTERFACCIA DELL'ANIMAZIONE */

public:

	// Metodi costruttore e distruttore
	InterfaceAnimation( const std::string &path );
	InterfaceAnimation( const std::string &path, const Types::Size2D_u &size_ );
	virtual ~InterfaceAnimation();

	// Imposta lo stato dell'animazione
	void SetAnimationStatus( Animation::Status state );
	// Ritorna lo stato dell'animazione
	Animation::Status GetAnimationStatus() const;

	// Imposta la velocità dell'animazione (in millisecondi)
	void SetAnimationSpeed( Types::Float value );
	// Ritorna la velocità dell'animazione (in millisecondi)
	Types::Float GetAnimationSpeed() const;

	// Imposta la serie di immagini per l'animazione
	void SetAnimationSeries( Types::Uint value );
	// Ritorna la serie di immagini per l'animazione
	Types::Uint GetAnimationSeries() const;

	// Imposta l'intervallo di fotogrammi per l'animazione
	void SetAnimationRange( Types::Uint start, Types::Uint end );
	// Ritorna l'intervallo di fotogrammi per l'animazione
	void GetAnimationRange( Types::Uint *start, Types::Uint *end ) const;

	// Imposta il fotogramma corrente dell'animazione
	void SetAnimationFrame( Types::Uint value );
	// Ritorna il fotogramma corrente dell'animazione
	Types::Uint GetAnimationFrame() const;

	// Aggiorna l'animazione
	virtual void UpdateAnimation( Types::Float eps );

protected:

	// Stato dell'animazione
	Animation::Status animation_status;

	// Velocità dell'animazione
	Types::Float animation_speed;

	// Fattore della velocità dell'animazione
	Types::Float animation_speed_factor;

	// Serie di immagini dell'animazione
	Types::Uint animation_series;

	// Numero dei fotogrammi dell'animazione
	Types::Uint animation_range[2];

	// Fotogramma corrente dell'animazione
	Types::Float animation_frame;

	// Imposta il fattore della velocità dell'animazione
	void SetAnimationSpeedFactor( Types::Float value );
	// Ritorna il fattore della velocità dell'animazione
	Types::Float GetAnimationSpeedFactor() const;
};

}; // Chiudo il namespace di VGE

#endif
