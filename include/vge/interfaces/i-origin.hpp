/* 
    Title --- i-origin.hpp

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


#ifndef VGE_INTERFACE_ORIGIN_HPP
#define VGE_INTERFACE_ORIGIN_HPP

#include <iostream>
#include <list>

#include "vge/consts.hpp"
#include "vge/types.hpp"
#include "vge/error.hpp"
#include "vge/math.hpp"

namespace VGE { // Namespace di VGE

class InterfaceOrigin {

	/* INTERFACCIA CON UN PUNTO DI ORIGINE */

public:

	// Punto di origine dell'entità
	typedef enum {

		ORIGIN_LEFT,	// Origine da sinistra
		ORIGIN_TOP,		// Origine dall'alto
		ORIGIN_RIGHT,	// Origine da destra
		ORIGIN_BOTTOM	// Origine dal basso

	} Origin;

	// Metodi costruttore e distruttore
	InterfaceOrigin( Origin origin_ );
	virtual ~InterfaceOrigin();

	// Imposta il punto di origine dell'entità
	virtual void SetOrigin( Origin origin_ );
	// Ritorna il punto di origine dell'entità
	virtual const Origin &GetOrigin() const;

protected:

	// Origine della barra del caricamento
	Origin origin;
};

}; // Chiudo il namespace di VGE

#endif
