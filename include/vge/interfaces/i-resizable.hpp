/* 
    Title --- i-resizable.hpp

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


#ifndef VGE_INTERFACE_RESIZABLE_HPP
#define VGE_INTERFACE_RESIZABLE_HPP

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

	RESIZING = 150, // SEGNALE DI RIDIMENSIONAMENTO
};

}; // Chiudo il namespace del tipo di segnale

class InterfaceResizable {

	/* INTERFACCIA RIDIMENSIONABILE */

public:

	// Metodi costruttore e distruttore
	InterfaceResizable();
	virtual ~InterfaceResizable();

	// Imposta la dimensione
	virtual void SetSize( const Types::Size2D_u &size_ );
	// Ritorna dimensione
	virtual Types::Size2D_u GetSize() const;

protected:

	// Dimensione
	Types::Size2D_u size;
};

}; // Chiudo il namespace di VGE

#endif
