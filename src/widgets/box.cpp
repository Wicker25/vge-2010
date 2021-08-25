/* 
    Title --- box.cpp

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


#ifndef VGE_BOX_CPP
#define VGE_BOX_CPP

#include "vge/widgets/box.hpp"

#include "vge/color.hpp"
#include "vge/inline/color-inl.hpp"

#include "vge/designer.hpp"
#include "vge/inline/designer-inl.hpp"

#include "vge/interfaces/i-colorable.hpp"
#include "vge/interfaces/inline/i-colorable-inl.hpp"

#include "vge/widgets/inline/box-inl.hpp"

namespace VGE { // Namespace di VGE

namespace Gui { // Namespace dell'interfaccia grafica

Box::Box() {

	// Disabilito il color blending per le luci ambientali
	this->SetColorBlending( false );

	// Imposto lo spessore della cornice
	this->SetBorderWidth( 1 );

	// Imposto il colore della cornice
	this->SetBorderColor( Color::Make( 0, 0, 0, 255 ) );

	// Modifico il flag del riempimento
	this->SetFilled( true );

	// Imposto l'opacità del riquadra
	this->SetOpacity( 255 );
}

Box::~Box() {

}

void
Box::Draw( const Designer &designer, const Types::Point2D &position, const Types::Size2D_u &size, Color::RGBA8 blend ) const {

	// Calcolo i vertici del riquadro
	Types::Rect_f frame( position, size );

	// Controllo il flag di riempimento
	if ( this->GetFilled() && ( this->GetOpacity() * Color::Split( this->GetColor(), Color::CH_ALPHA ) ) ) {

		// Imposto il colore del riquadro
		designer.SetColor( this->GetColor(), this->GetOpacity() );

		// Disegno il riquadro
		designer.DrawFillRectangle( frame );
	}

	// Controllo lo spessore del contorno
	if ( this->GetBorderWidth() > 0 && ( this->GetOpacity() * Color::Split( this->GetBorderColor(), Color::CH_ALPHA ) ) ) {

		// Imposto il colore del bordo del riquadro
		designer.SetColor( this->GetBorderColor(), this->GetOpacity() );

		// Imposto lo spessore della linea
		designer.SetLineWidth( this->GetBorderWidth() );

		// Disegno il bordo del riquadro
		designer.DrawRectangle( frame );
	}
}

}; // Chiudo il namespace dell'interfaccia grafica

}; // Chiudo il namespace di VGE

#endif
