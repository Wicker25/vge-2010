/* 
    Title --- i-scalable.hpp

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


#ifndef VGE_INTERFACE_SCALABLE_HPP
#define VGE_INTERFACE_SCALABLE_HPP

#include <iostream>
#include <list>

#include "vge/consts.hpp"
#include "vge/types.hpp"
#include "vge/error.hpp"
#include "vge/math.hpp"

namespace VGE { // Namespace di VGE

namespace SignalType { // Namespace del tipo di segnale

// Tipo del segnale
enum {

	SCALING = 200, // SEGNALE DI MODIFICA DELLA SCALA
};

}; // Chiudo il namespace del tipo di segnale

class InterfaceScalable {

	/* INTERFACCIA SCALABILE */

public:

	// Metodi costruttore e distruttore
	InterfaceScalable();
	virtual ~InterfaceScalable();

	// Modifica la proporzione
	virtual void SetScale( const Types::Size2D_f &scale_ );
	// Ritorna la proporzione
	virtual void GetScale( Types::Size2D_f &scale_ ) const;
	virtual const Types::Size2D_f &GetScale() const;

protected:

	// Rotazione
	Types::Size2D_f scale;
};

}; // Chiudo il namespace di VGE

#endif
