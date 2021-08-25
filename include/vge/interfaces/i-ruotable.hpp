/* 
    Title --- i-ruotable.hpp

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


#ifndef VGE_INTERFACE_RUOTABLE_HPP
#define VGE_INTERFACE_RUOTABLE_HPP

#include <iostream>
#include <list>
#include <cmath>

#include "vge/consts.hpp"
#include "vge/types.hpp"
#include "vge/error.hpp"
#include "vge/math.hpp"

namespace VGE { // Namespace di VGE

namespace SignalType { // Namespace del tipo di segnale

// Tipo del segnale
enum {

	ROTATION = 100, // SEGNALE DI ROTAZIONE
};

}; // Chiudo il namespace del tipo di segnale

class InterfaceRuotable {

	/* INTERFACCIA ROTANTE */

public:

	// Metodi costruttore e distruttore
	InterfaceRuotable();
	virtual ~InterfaceRuotable();

	// Modifica l'angolo di rotazione dell'immagine
	virtual void SetRotation( Types::Float value );
	// Ritorna l'angolo di rotazione dell'immagine
	virtual Types::Float GetRotation() const;

protected:

	// Angolo di rotazione
	Types::Float angle;
};

}; // Chiudo il namespace di VGE

#endif
