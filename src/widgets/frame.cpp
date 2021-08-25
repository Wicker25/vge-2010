/* 
    Title --- frame.cpp

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


#ifndef VGE_FRAME_CPP
#define VGE_FRAME_CPP

#include "vge/widgets/frame.hpp"

#include "vge/color.hpp"
#include "vge/inline/color-inl.hpp"

#include "vge/interfaces/i-resizable.hpp"
#include "vge/interfaces/inline/i-resizable-inl.hpp"

#include "vge/entity.hpp"
#include "vge/inline/entity-inl.hpp"

#include "vge/engine.hpp"
#include "vge/inline/engine-inl.hpp"

#include "vge/widgets/box.hpp"
#include "vge/widgets/inline/box-inl.hpp"

#include "vge/widgets/font.hpp"
#include "vge/widgets/inline/font-inl.hpp"

#include "vge/widgets/widget.hpp"
#include "vge/widgets/inline/widget-inl.hpp"

#include "vge/widgets/inline/frame-inl.hpp"

namespace VGE { // Namespace di VGE

namespace Gui { // Namespace dell'interfaccia grafica

Frame::Frame( const Types::Point3D &position ) : Widget( position ) {

	// Imposto il riquadro
	this->GetBox().SetColor( Color::Make( 0, 0, 0, 0 ) );
	this->GetBox().SetBorderColor( Color::Make( 0, 0, 0, 0 ) );
	this->GetBox().SetBorderWidth( 0 );
}

Frame::~Frame() {

}

void
Frame::Draw( const Types::Point2D &offset, Color::RGBA8 blend ) const {

	// Funzione di disegno del testo
	Widget::Draw( offset, blend );

	// Disegno il riquadro della finestra
	this->GetBox().Draw(	this->GetEngine()->GetDesigner(),
							this->GetPosition() - this->GetCenter() + offset, this->GetSize(), blend );
}

}; // Chiudo il namespace dell'interfaccia grafica

}; // Chiudo il namespace di VGE

#endif
