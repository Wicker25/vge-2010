/* 
    Title --- image-button.hpp

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


#ifndef VGE_IMAGE_BUTTON_HPP
#define VGE_IMAGE_BUTTON_HPP

#include <iostream>
#include <vector>
#include <cmath>

#include <sigc++/sigc++.h>

#include "vge/consts.hpp"
#include "vge/types.hpp"
#include "vge/error.hpp"
#include "vge/math.hpp"

#include "vge/image.hpp"

#include "vge/widgets/button.hpp"

namespace VGE { // Namespace di VGE

namespace Gui { // Namespace dell'interfaccia grafica

class ImageButton : public Button {

	/* PULSANTE CON IMMAGINE */

public:

	// Metodi costruttore e distruttore
	ImageButton( const std::string &path );
	ImageButton( const Image &image );
	virtual ~ImageButton();

	// Ritorna l'etichetta della finestra
	Image &GetIcon();
	const Image &GetIcon() const;

protected:

	// Aggiorna la dimensione del pulsante
	void UpdateSize( const Types::Size2D_u &, Widget * );

	// Etichetta del pulsante
	Image icon;
};

}; // Chiudo il namespace dell'interfaccia grafica

}; // Chiudo il namespace di VGE

#endif
