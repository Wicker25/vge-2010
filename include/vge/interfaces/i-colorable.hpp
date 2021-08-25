/* 
    Title --- i-colorable.hpp

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


#ifndef VGE_INTERFACE_COLORABLE_HPP
#define VGE_INTERFACE_COLORABLE_HPP

#include <iostream>
#include <list>

#include "vge/consts.hpp"
#include "vge/types.hpp"
#include "vge/error.hpp"
#include "vge/math.hpp"

#include "vge/color.hpp"

namespace VGE { // Namespace di VGE

class InterfaceColorable {

	/* INTERFACCIA COLORABILE */

public:

	// Metodi costruttore e distruttore
	InterfaceColorable();
	virtual ~InterfaceColorable();

	// Abilita/Disabilita il color blending per i toni ambientali
	virtual void SetColorBlending( Types::Bool state );
	// Ritorna lo stato del color blending
	virtual Types::Bool GetColorBlending() const;

	// Imposta il colore
	virtual void SetColor( Color::RGBA8 value );
	// Ritorna il colore
	virtual Color::RGBA8 GetColor() const;

protected:

	// Filtro del colore
	Types::Bool color_blending;

	// Colore dell'oggetto
	Color::RGBA8 color;
};

}; // Chiudo il namespace di VGE

#endif
