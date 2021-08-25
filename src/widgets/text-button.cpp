/* 
    Title --- text-button.cpp

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


#ifndef VGE_TEXT_BUTTON_CPP
#define VGE_TEXT_BUTTON_CPP

#include "vge/widgets/text-button.hpp"

#include "vge/input-manager.hpp"
#include "vge/inline/input-manager-inl.hpp"

#include "vge/engine.hpp"
#include "vge/inline/engine-inl.hpp"

#include "vge/widgets/label.hpp"
#include "vge/widgets/inline/label-inl.hpp"

#include "vge/widgets/widget.hpp"
#include "vge/widgets/inline/widget-inl.hpp"

#include "vge/widgets/container.hpp"
#include "vge/widgets/inline/container-inl.hpp"

#include "vge/widgets/text-button.hpp"
#include "vge/widgets/inline/text-button-inl.hpp"

#include "vge/widgets/inline/text-button-inl.hpp"

namespace VGE { // Namespace di VGE

namespace Gui { // Namespace dell'interfaccia grafica

TextButton::TextButton( const std::wstring &string ) :

	label( string ) {

	// Aggiungo l'etichetta al contenitore
	this->AddChild( &this->GetLabel() );

	// Imposto la dimensione del pulsante
	this->SetSize( this->GetLabel().GetSize() + this->GetMargins() );

	// Collego la dimensione del pulsante a quella del testo
	this->GetLabel().SignalResizing().connect( sigc::mem_fun( *this, &TextButton::UpdateSize ) );
}

TextButton::~TextButton() {

}

void
TextButton::UpdateSize( const Types::Size2D_u &size, Widget *widget ) {

	// Aggiorno la dimensione del pulsante
	this->SetSize( this->GetLabel().GetSize() + this->GetMargins() );
}

}; // Chiudo il namespace dell'interfaccia grafica

}; // Chiudo il namespace di VGE

#endif
