/* 
    Title --- text-button.hpp

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


#ifndef VGE_TEXT_BUTTON_HPP
#define VGE_TEXT_BUTTON_HPP

#include <iostream>
#include <vector>
#include <cmath>

#include <sigc++/sigc++.h>

#include "vge/consts.hpp"
#include "vge/types.hpp"
#include "vge/error.hpp"
#include "vge/math.hpp"

#include "vge/widgets/label.hpp"
#include "vge/widgets/button.hpp"

namespace VGE { // Namespace di VGE

namespace Gui { // Namespace dell'interfaccia grafica

class TextButton : public Button {

	/* PULSANTE CON TESTO */

public:

	// Metodi costruttore e distruttore
	TextButton( const std::wstring &string );
	virtual ~TextButton();

	// Ritorna l'etichetta della finestra
	Label &GetLabel();
	const Label &GetLabel() const;

protected:

	// Etichetta del pulsante
	Label label;

	// Aggiorna la dimensione del pulsante
	void UpdateSize( const Types::Size2D_u &, Widget * );
};

}; // Chiudo il namespace dell'interfaccia grafica

}; // Chiudo il namespace di VGE

#endif
