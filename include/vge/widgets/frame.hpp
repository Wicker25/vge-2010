/* 
    Title --- frame.hpp

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


#ifndef VGE_FRAME_HPP
#define VGE_FRAME_HPP

#include <iostream>
#include <vector>
#include <list>

#include "vge/consts.hpp"
#include "vge/types.hpp"
#include "vge/math.hpp"
#include "vge/global.hpp"

#include "vge/color.hpp"

#include "vge/interfaces/i-resizable.hpp"

#include "vge/entity.hpp"

#include "vge/widgets/box.hpp"
#include "vge/widgets/font.hpp"

#include "vge/widgets/widget.hpp"

namespace VGE { // Namespace di VGE

namespace Gui { // Namespace dell'interfaccia grafica

class Frame : public Widget {

	/* WIDGET CON CORNICE */

public:

	// Metodi costruttori e distruttori
	Frame( const Types::Point3D &position );
	virtual ~Frame();

	// Ritorna il riquadro del contenitore
	Box &GetBox();
	const Box &GetBox() const;

	// Disegna il testo sullo schermo
	virtual void Draw( const Types::Point2D &offset, Color::RGBA8 blend ) const;

protected:

	// Riquadro del widget
	Box box;
};

}; // Chiudo il namespace dell'interfaccia grafica

}; // Chiudo il namespace di VGE

#endif
