/* 
    Title --- box.hpp

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


#ifndef VGE_BOX_HPP
#define VGE_BOX_HPP

#include <iostream>
#include <list>

#include <SDL/SDL.h>
//#include <SDL/SDL_opengl.h>
#include <GL/glew.h> 

#include "vge/consts.hpp"
#include "vge/types.hpp"
#include "vge/error.hpp"
#include "vge/math.hpp"

#include "vge/color.hpp"

#include "vge/designer.hpp"

#include "vge/interfaces/i-colorable.hpp"

namespace VGE { // Namespace di VGE

namespace Gui { // Namespace dell'interfaccia grafica

class Box : public InterfaceColorable {

	/* RIQUADRO */

public:

	// Metodi costruttore e distruttore
	Box();
	virtual ~Box();

	// Modifica i colori della cornice
	virtual void SetBorderColor( Color::RGBA8 value );
	// Ritorna i colori della cornice
	virtual Color::RGBA8 GetBorderColor() const;

	// Modifico lo spessore della cornice
	virtual void SetBorderWidth( Types::Uint8 width );
	// Ritorno lo spessore della cornice
	virtual Types::Uint8 GetBorderWidth() const;

	// Modifica il flag del riempimento
	virtual void SetFilled( Types::Bool state );
	// Ritorna il flag del riempimento
	virtual Types::Bool GetFilled() const;

	// Imposta l'opacità della finestra
	virtual void SetOpacity( Types::Uint8 value );
	// Ritorna la opacità della finestra
	virtual Types::Uint8 GetOpacity() const;

	// Disegna il riquadro sullo schermo
	virtual void Draw(	const Designer &designer, const Types::Point2D &position, 
						const Types::Size2D_u &size, Color::RGBA8 blend ) const;

protected:

	// Spessore della cornice
	Types::Uint8 border_width;

	// Colore della cornice
	Color::RGBA8 border_color;

	// Flag di riempimento
	Types::Bool filled;

	// Trasparenza del testo
	Types::Uint8 opacity;
};

}; // Chiudo il namespace dell'interfaccia grafica

}; // Chiudo il namespace di VGE

#endif
