/* 
    Title --- message-box.cpp

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


#ifndef VGE_MESSAGE_BOX_CPP
#define VGE_MESSAGE_BOX_CPP

#include "vge/widgets/message-box.hpp"

#include "vge/interfaces/i-programmable.hpp"
#include "vge/interfaces/inline/i-programmable-inl.hpp"

#include "vge/entity.hpp"
#include "vge/inline/entity-inl.hpp"

#include "vge/image.hpp"
#include "vge/inline/image-inl.hpp"

#include "vge/widgets/box.hpp"
#include "vge/widgets/inline/box-inl.hpp"

#include "vge/widgets/font.hpp"
#include "vge/widgets/inline/font-inl.hpp"

#include "vge/widgets/window.hpp"
#include "vge/widgets/inline/window-inl.hpp"

#include "vge/widgets/text-box.hpp"
#include "vge/widgets/inline/text-box-inl.hpp"

#include "vge/widgets/inline/message-box-inl.hpp"

namespace VGE { // Namespace di VGE

namespace Gui { // Namespace dell'interfaccia grafica

MessageBox::MessageBox( const Types::Size2D_u size_ ) :

	Window( size_ ),
	container( Container::ORIENTATION_HORIZONTAL ),
	text_box( L"" ) {

	// Aggiungo il contenitore principale
	this->AddChild( &this->container );

	// Aggiungo gli elementi del dialogo
	this->container.AddChild( NULL, Gui::Container::PACKING_COLLAPSE, 10.0f, 0.5f );
	this->container.AddChild( &this->GetTextBox(), Gui::Container::PACKING_FILL );
}

MessageBox::MessageBox( const std::wstring &string, const Types::Size2D_u size_ ) :

	Window( size_ ),
	container( Container::ORIENTATION_HORIZONTAL ),
	text_box( string ) {

	// Aggiungo il contenitore principale
	this->AddChild( &this->container );

	// Aggiungo gli elementi del dialogo
	this->container.AddChild( NULL, Gui::Container::PACKING_COLLAPSE, 10.0f, 0.5f );
	this->container.AddChild( &this->GetTextBox(), Gui::Container::PACKING_FILL );
}

MessageBox::~MessageBox() {

}

Types::Bool
MessageBox::SendEvent( Event *event, Entity *other ) {

	// Flag di controllo
	Types::Bool end_event = false;

	// Controlla il tipo di evento
	/*
	switch ( event->type ) {

		// Cambia l'immagine della finestra del dialogo
		case EventType::SET_IMAGE: { 

			this->SetImage( static_cast< Image * >( event->entity ) );
			end_event = true;
			break;
		}

		default: break;
	}
	*/

	// Avvia il gestore degli eventi
	if ( !end_event )
		end_event = Window::SendEvent( event, other );

	return end_event;
}

}; // Chiudo il namespace dell'interfaccia grafica

}; // Chiudo il namespace di VGE

#endif
