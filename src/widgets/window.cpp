/* 
    Title --- window.cpp

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


#ifndef VGE_WINDOW_CPP
#define VGE_WINDOW_CPP

#include "vge/widgets/window.hpp"

#include "vge/color.hpp"
#include "vge/inline/color-inl.hpp"

#include "vge/entity.hpp"
#include "vge/inline/entity-inl.hpp"

#include "vge/widgets/container.hpp"
#include "vge/widgets/inline/container-inl.hpp"

#include "vge/widgets/label.hpp"
#include "vge/widgets/inline/label-inl.hpp"

#include "vge/widgets/inline/window-inl.hpp"

namespace VGE { // Namespace di VGE

namespace Gui { // Namespace dell'interfaccia grafica

Window::Window( const Types::Size2D_u &size_ ) :

	Container( Container::ORIENTATION_VERTICAL ),
	l_title( L"" ) {

	// Imposto le dimensioni della finestra
	this->SetSize( size_ );

	// Imposto l'opacità della finestra
	this->SetOpacity( 255 );

	// Aggiungo gli elementi alla finestra
	this->AddChild( &this->GetTitle(), Container::PACKING_COLLAPSE, 0.5f, 0.0f );

	// Imposto il riquadro della finestra
	this->GetBox().SetColor( Color::Make( 0, 0, 0, 80 ) );
	this->GetBox().SetBorderColor( Color::Make( 0, 0, 0, 200 ) );
	this->GetBox().SetBorderWidth( 1 );

	// Imposto il titolo
	this->GetTitle().SetVisible( false );
}

Window::Window( const std::wstring &title, const Types::Size2D_u &size_ ) :

	Container( Container::ORIENTATION_VERTICAL ),
	l_title( title ) {

	// Imposto le dimensioni della finestra
	this->SetSize( size_ );

	// Imposto l'opacità della finestra
	this->SetOpacity( 255 );

	// Aggiungo gli elementi alla finestra
	this->AddChild( &this->GetTitle(), Container::PACKING_COLLAPSE, 0.5f, 5.0f );

	// Imposto il riquadro della finestra
	this->GetBox().SetColor( Color::Make( 0, 0, 0, 80 ) );
	this->GetBox().SetBorderColor( Color::Make( 0, 0, 0, 200 ) );
	this->GetBox().SetBorderWidth( 1 );
}

Window::~Window() {

}

void
Window::SendSignal( Types::Int type, Entity *other ) {

	// Chiamo il gestore dei segnali
	Container::SendSignal( type, other );

	// Controlla il tipo di segnale
	switch ( type ) {

		/*
		// Gestisco il segnale della collisione
		case SignalType::LAST_PAGE: { 

			break;
		}
		*/

		default: break;
	}
}

Types::Bool
Window::SendEvent( Event *event, Entity *other ) {

	// Flag di controllo
	Types::Bool end_event = false;

	// Controlla il tipo di evento
	switch ( event->type ) {

		// Apparizione con dissolvenza
		case EventType::FADING_IN: { 

			// Ricavo l'opacità della finestra
			Types::Uint8 alpha = this->GetOpacity();

			// Controllo i progressi
			if ( 255 - (Types::Int) alpha < event->arg0[0] )

				end_event = true;

			else {

				// Modifico l'opacità della finestra
				this->SetOpacity( alpha + (Types::Uint8) event->arg0[0] );
			}

			break;
		}

		// Scomparsa con dissolvenza
		case EventType::FADING_OUT: { 

			// Ricavo l'opacità della finestra
			Types::Uint8 alpha = this->GetOpacity();

			// Controllo i progressi
			if ( alpha < event->arg0[0] )

				end_event = true;

			else {

				// Modifico l'opacità della finestra
				this->SetOpacity( alpha - (Types::Uint8) event->arg0[0] );
			}

			break;
		}

		default: break;
	}

	// Avvia il gestore degli eventi
	if ( !end_event )
		end_event = Container::SendEvent( event, other );

	return end_event;
}

void
Window::Draw( const Types::Point2D &offset, Color::RGBA8 blend ) const {

	// Disegno i widget della finestra
	Container::Draw( offset, blend );
}

}; // Chiudo il namespace dell'interfaccia grafica

}; // Chiudo il namespace di VGE

#endif
