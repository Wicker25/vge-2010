/* 
    Title --- i-orientable.hpp

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


#ifndef VGE_INTERFACE_ORIENTABLE_HPP
#define VGE_INTERFACE_ORIENTABLE_HPP

#include <iostream>
#include <list>

#include "vge/consts.hpp"
#include "vge/types.hpp"
#include "vge/error.hpp"
#include "vge/math.hpp"

namespace VGE { // Namespace di VGE

class InterfaceOrientable {

	/* INTERFACCIA ORIENTABILE */

public:

	// Orientamento dell'entità
	typedef enum {

		ORIENTATION_HORIZONTAL,	// Orientamento orizzontale
		ORIENTATION_VERTICAL,	// Orientamento verticale

	} Orientation;

	// Metodi costruttore e distruttore
	InterfaceOrientable( Orientation orientation_ );
	virtual ~InterfaceOrientable();

	// Imposta l'orientamento dell'entità
	virtual void SetOrientation( Orientation orientation_ );
	// Ritorna l'orientamento dell'entità
	virtual const Orientation &GetOrientation() const;

protected:

	// Orientamento dell'entità
	Orientation orientation;
};

}; // Chiudo il namespace di VGE

#endif
