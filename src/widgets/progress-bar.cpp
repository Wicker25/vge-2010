/* 
    Title --- progress-bar.cpp

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


#ifndef VGE_PROGRESS_BAR_CPP
#define VGE_PROGRESS_BAR_CPP

#include "vge/widgets/progress-bar.hpp"

#include "vge/designer.hpp"
#include "vge/inline/designer-inl.hpp"

#include "vge/interfaces/i-resizable.hpp"
#include "vge/interfaces/inline/i-resizable-inl.hpp"

#include "vge/interfaces/i-colorable.hpp"
#include "vge/interfaces/inline/i-colorable-inl.hpp"

#include "vge/interfaces/i-orientable.hpp"
#include "vge/interfaces/inline/i-orientable-inl.hpp"

#include "vge/interfaces/i-range.hpp"
#include "vge/interfaces/inline/i-range-inl.hpp"

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

#include "vge/widgets/frame.hpp"
#include "vge/widgets/inline/frame-inl.hpp"

#include "vge/widgets/container.hpp"
#include "vge/widgets/inline/container-inl.hpp"

#include "vge/widgets/label.hpp"
#include "vge/widgets/inline/label-inl.hpp"

#include "vge/widgets/inline/progress-bar-inl.hpp"

namespace VGE { // Namespace di VGE

namespace Gui { // Namespace dell'interfaccia grafica

ProgressBar::ProgressBar( const Types::Size2D_u &size_, Origin origin_ ) :

	Container( Container::ORIENTATION_VERTICAL ),
	InterfaceOrigin( origin_ ),
	label( L"..." ) {

	// Imposto l'identificativo del tipo di oggetto
	this->SetMask( CONTAINER_DERIVED_MASK );

	// Aggiungo gli elementi alla finestra
	this->AddChild( &this->GetLabel(), Container::PACKING_EXPAND, 0.5f, 0.5f );

	// Imposto la dimensione della barra dei progressi
	this->SetSize( size_ );

	// Imposto il colore della barra del progresso
	this->SetBarColor( Color::Make( 0, 255, 0, 150 ) );

	// Imposto la formattazione dell'etichetta
	this->SetLabelFormat( L"%.1f" );

	// Imposto il colore dell'etichetta
	this->SetColor( Color::Make( 255, 255, 255, 255 ) );

	// Disabilito la capacità di prendere il focus
	this->SetFocusable( false );

	// Imposto il riquadro della barra del progresso
	this->GetBox().SetColor( Color::Make( 0, 0, 0, 0 ) );
	this->GetBox().SetBorderColor( Color::Make( 255, 255, 255, 200 ) );
	this->GetBox().SetBorderWidth( 1 );

	// Imposto il flag di aggiornamento
	this->update = true;
}

ProgressBar::~ProgressBar() {

}

void
ProgressBar::UpdateLabel() {

	// Calcolo la dimensione massima dell'etichetta
	Types::Uint size = wcslen( this->GetLabelFormat() ) + 10;

	// Strutture di lavoro
	wchar_t buffer[ size ];

	// Costruisco la stringa dell'etichetta
	swprintf( buffer, size, this->GetLabelFormat(), this->GetValue() );

	// Aggiorno la stringa dell'etichetta
	this->GetLabel().SetString( buffer );
}

void
ProgressBar::SendSignal( Types::Int type, Entity *other ) {

	// Chiamo il gestore dei segnali
	Container::SendSignal( type, other );

	// Controlla il tipo di segnale
	switch ( type ) {

		// Gestisco il segnale di modifica della frazione
		case SignalType::CHANGE_FRACTION: { 

			// Emetto il segnale di modifica della frazione
			this->SignalChangeFraction().emit( this->GetFraction(), this->GetValue(), this );

			break;
		}

		default: break;
	}
}

void
ProgressBar::Update( Viewer *viewer, Player *player ) {

	// Controllo se è abilitato il flag di aggiornamento
	if ( this->update ) {

		// Aggiorno l'etichetta della barra di caricamento
		this->UpdateLabel();

		// Disabilito il flag di aggiornamento
		this->update = false;
	}

	// Avvio la funzione di lavoro superiore
	Container::Update( viewer, player );

	// Incremento continuo (test)
	//this->SetFraction( this->GetFraction() + 0.0005f );
}

void
ProgressBar::Draw( const Types::Point2D &offset, Color::RGBA8 blend ) const {

	// Funzione di disegno del frame
	Frame::Draw( offset, blend );

	// Rettangolo della barra di caricamento completata
	Types::Rect_f progress_rect;

	// Controllo l'origine della barra
	switch ( this->GetOrigin() ) {

		// Origine da sinistra
		case ORIGIN_LEFT: {

			progress_rect = Types::Rect_f(	this->GetPosition().x + 1,
											this->GetPosition().y,
											this->GetPosition().x + this->GetSize().w * this->GetFraction(),
											this->GetPosition().y + this->GetSize().h - 1 );
			break;
		}

		// Origine dall'alto
		case ORIGIN_TOP: {

			progress_rect = Types::Rect_f(	this->GetPosition().x + 1,
											this->GetPosition().y,
											this->GetPosition().x + this->GetSize().w,
											this->GetPosition().y + this->GetSize().h * this->GetFraction() - 1 );
			break;
		}

		// Origine da destra
		case ORIGIN_RIGHT: {

			progress_rect = Types::Rect_f(	this->GetPosition().x + this->GetSize().w - this->GetSize().w * this->GetFraction() + 1,
											this->GetPosition().y,
											this->GetPosition().x + this->GetSize().w,
											this->GetPosition().y + this->GetSize().h - 1 );
			break;
		}

		// Origine dal basso
		case ORIGIN_BOTTOM: {

			progress_rect = Types::Rect_f(	this->GetPosition().x + 1,
											this->GetPosition().y + this->GetSize().h - this->GetSize().h * this->GetFraction(),
											this->GetPosition().x + this->GetSize().w,
											this->GetPosition().y + this->GetSize().h - 1 );
			break;
		}
	}


	// Ricavo il disegnatore principale
	const Designer &designer = this->GetEngine()->GetDesigner();

	// Imposto il colore della barra del progresso
	designer.SetColor( this->GetBarColor(), this->GetOpacity() );

	// Disegno il bordo del riquadro
	designer.DrawFillRectangle( progress_rect );


	// Numero di widget figli
	const Types::Uint n_widgets = this->GetNumberOfChilds();

	// Iteratore
	Types::Uint i = 0;

	// Disegno gli elementi del contenitore
	for ( ; i < n_widgets; i++ ) {

		if ( this->child_list[i].widget != NULL && this->child_list[i].widget ) {

			this->child_list[i].widget->Draw( offset, blend );
		}
	}
}

}; // Chiudo il namespace dell'interfaccia grafica

}; // Chiudo il namespace di VGE

#endif
