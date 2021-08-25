/* 
    Title --- image-button.cpp

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


#ifndef VGE_IMAGE_BUTTON_CPP
#define VGE_IMAGE_BUTTON_CPP

#include "vge/widgets/image-button.hpp"

#include "vge/image.hpp"
#include "vge/inline/image-inl.hpp"

#include "vge/input-manager.hpp"
#include "vge/inline/input-manager-inl.hpp"

#include "vge/engine.hpp"
#include "vge/inline/engine-inl.hpp"

#include "vge/widgets/widget.hpp"
#include "vge/widgets/inline/widget-inl.hpp"

#include "vge/widgets/container.hpp"
#include "vge/widgets/inline/container-inl.hpp"

#include "vge/widgets/button.hpp"
#include "vge/widgets/inline/button-inl.hpp"

#include "vge/widgets/inline/image-button-inl.hpp"

namespace VGE { // Namespace di VGE

namespace Gui { // Namespace dell'interfaccia grafica

ImageButton::ImageButton( const std::string &path ) :

	icon( path ) {

	// Aggiungo l'etichetta al contenitore
	this->AddChild( &this->GetIcon() );

	// Imposto la dimensione del pulsante
	this->SetSize( this->GetIcon().GetSize() + this->GetMargins() );

	// Collego la dimensione del pulsante a quella dell'immagine
	this->GetIcon().SignalResizing().connect( sigc::mem_fun( *this, &ImageButton::UpdateSize ) );
}

ImageButton::ImageButton( const Image &image ) :

	icon( image ) {

	// Aggiungo l'etichetta al contenitore
	this->AddChild( &this->GetIcon() );

	// Imposto la dimensione del pulsante
	this->SetSize( this->GetIcon().GetSize() + this->GetMargins() );

	// Collego la dimensione del pulsante a quella dell'immagine
	this->GetIcon().SignalResizing().connect( sigc::mem_fun( *this, &ImageButton::UpdateSize ) );
}

ImageButton::~ImageButton() {

}

void
ImageButton::UpdateSize( const Types::Size2D_u &size, Widget *widget ) {

	// Aggiorno la dimensione del pulsante
	this->SetSize( this->GetIcon().GetSize() + this->GetMargins() );
}

}; // Chiudo il namespace dell'interfaccia grafica

}; // Chiudo il namespace di VGE

#endif
