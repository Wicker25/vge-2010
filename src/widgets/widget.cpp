/* 
    Title --- widget.cpp

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


#ifndef VGE_WIDGET_CPP
#define VGE_WIDGET_CPP

#include "vge/widgets/widget.hpp"

#include "vge/interfaces/i-resizable.hpp"
#include "vge/interfaces/inline/i-resizable-inl.hpp"

#include "vge/interfaces/i-clickable.hpp"
#include "vge/interfaces/inline/i-clickable-inl.hpp"

#include "vge/entity.hpp"
#include "vge/inline/entity-inl.hpp"

#include "vge/image.hpp"
#include "vge/inline/image-inl.hpp"

#include "vge/input-manager.hpp"
#include "vge/inline/input-manager-inl.hpp"

#include "vge/engine.hpp"
#include "vge/inline/engine-inl.hpp"

#include "vge/widgets/container.hpp"
#include "vge/widgets/inline/container-inl.hpp"

#include "vge/widgets/inline/widget-inl.hpp"

namespace VGE { // Namespace di VGE

namespace Gui { // Namespace dell'interfaccia grafica

Widget::Widget( const Types::Point3D &position ) : Entity( position ) {

	// Imposto l'identificativo del tipo di entità
	this->SetMask( WIDGET_MASK );

	// Collego il widget ad un contenitore
	this->SetContainer( NULL );

	// Imposto l'opacità del widget
	this->SetOpacity( 255 );

	// Disabilito la capacità di prendere il focus
	this->SetFocusable( false );
}

Widget::~Widget() {

}

Types::Bool
Widget::GetFocus() const {

	// Controllo se il widget ha il focus
	return ( this->GetVisible() && ( this->GetEngine() != NULL && this->GetEngine()->GetWidgetFocus() == this ) );
}

void
Widget::SendSignal( Types::Int type, Entity *other ) {

	// Chiamo il gestore dei segnali
	Entity::SendSignal( type, other );

	// Controlla il tipo di segnale
	switch ( type ) {

		// Gestisco il segnale di movimento
		case SignalType::MOTION:

		// Gestisco il segnale di modifica della scala
		case SignalType::SCALING: {

			// Invio il segnale di aggiornamento dell'impacchettamento al contenitore
			if ( this->GetMask() != Entity::CONTAINER_MASK && this->GetContainer() != NULL )

				this->GetContainer()->SendSignal( SignalType::UPDATE_PACKING, NULL );

			break;
		}

		// Gestisco il segnale di ridimensionamento
		case SignalType::RESIZING: { 

			// Emetto il segnale di ridimensionamento
			this->SignalResizing().emit( this->GetSize(), this );

			// Invio il segnale di aggiornamento dell'impacchettamento al contenitore
			if (	this->GetMask() != Entity::CONTAINER_MASK &&
					this->GetMask() != Entity::CONTAINER_DERIVED_MASK && this->GetContainer() != NULL ) {

				this->GetContainer()->SendSignal( SignalType::UPDATE_PACKING, NULL );
			}

			// Aggiorno la dimensione dell'area di interazione
			this->GetVisibilityArea().SetRectangle( this->GetSize(), this->GetCenter() );
			break;
		}

		// Gestisco il segnale del cambio del focus
		case SignalType::CHANGE_FOCUS: { 

			// Emetto il segnale del cambio del focus
			this->SignalFocus().emit( this->GetFocus(), this );
			break;
		}

		// Gestisco il segnale di pressione con il tasto sinistro del mouse
		case SignalType::MOUSE_LEFT_PRESSED:

		// Gestisco il segnale di pressione con il tasto medio del mouse
		case SignalType::MOUSE_MIDDLE_PRESSED:

		// Gestisco il segnale di pressione con il tasto destro del mouse
		case SignalType::MOUSE_RIGHT_PRESSED: {

			// Controllo sia stato collegato l'engine
			if ( this->GetVisible() && this->GetEngine() != NULL ) {

				// Controllo se il widget è predisposto a prendere il focus
				if ( this->GetFocusable() ) {

					// Muovo il focus sul widget
					this->GetEngine()->SetWidgetFocus( this );
				}
			 }
		}

		default: break;
	}
}

void
Widget::Update( Viewer *viewer, Player *player ) {

	// Avvio la funzione di lavoro superiore
	Entity::Update( viewer, player );

	// Interazione con il mouse
	if ( viewer != NULL ) {

		// Cerco un evento del mouse
		Types::Uint type = this->CheckMouseEvent(	&this->GetEngine()->GetInputManager(),
													&this->GetVisibilityArea(), viewer, this->GetFixed() );

		// Gestisco i segnali del mouse
		if ( type != SignalType::MOUSE_NO_EVENT ) {

			this->SendSignal( type, NULL );
		}
	}
}

void
Widget::Draw( const Types::Point2D &offset, Color::RGBA8 blend ) const {

	// Chiamo la funzione di disegno superiore
	Entity::Draw( offset, blend );

	// Controllo che sia stata definita l'area di visibilità
	if ( this->GetFocus() ) {

		// Ricavo il disegnatore principale
		const Designer &designer = this->GetEngine()->GetDesigner();

		// Imposto il colore del bordo del riquadro
		designer.SetColor( Color::Make( 255, 0, 0, 255 ) );

		// Imposto lo spessore della linea
		designer.SetLineWidth( 3 );

		// Disegno l'area di selezione
		designer.DrawPolygon( this->GetVisibilityArea().GetPolygon(), offset );
	}
}

}; // Chiudo il namespace dell'interfaccia grafica

}; // Chiudo il namespace di VGE

#endif
