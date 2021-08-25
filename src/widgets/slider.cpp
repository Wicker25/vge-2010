/* 
    Title --- slider.cpp

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


#ifndef VGE_SLIDER_CPP
#define VGE_SLIDER_CPP

#include "vge/widgets/slider.hpp"

#include "vge/designer.hpp"
#include "vge/inline/designer-inl.hpp"

#include "vge/color.hpp"
#include "vge/inline/color-inl.hpp"

#include "vge/input-manager.hpp"
#include "vge/inline/input-manager-inl.hpp"

#include "vge/interfaces/i-orientable.hpp"
#include "vge/interfaces/inline/i-orientable-inl.hpp"

#include "vge/interfaces/i-range.hpp"
#include "vge/interfaces/inline/i-range-inl.hpp"

#include "vge/engine.hpp"
#include "vge/inline/engine-inl.hpp"

#include "vge/widgets/widget.hpp"
#include "vge/widgets/inline/widget-inl.hpp"

#include "vge/widgets/container.hpp"
#include "vge/widgets/inline/container-inl.hpp"

#include "vge/widgets/button.hpp"
#include "vge/widgets/inline/button-inl.hpp"

#include "vge/widgets/inline/slider-inl.hpp"

namespace VGE { // Namespace di VGE

namespace Gui { // Namespace dell'interfaccia grafica

Slider::Slider( const Types::Size2D_u size_, Orientation orientation_ ) :

	Container( orientation_ ) {

	// Imposto l'identificativo del tipo di oggetto
	this->SetMask( CONTAINER_DERIVED_MASK );

	// Imposto la dimensione dello scorritore
	this->SetSize( size_ );

	// Imposto l'intervallo di valori
	this->SetRange( Types::Size2D_u( 0, 100 ) );

	// Imposto la formattazione dell'etichetta
	this->SetLabelFormat( L"%.0f" );

	// Imposto la visibilità del righello
	this->SetRulerVisible( true );

	// Aggiungo il pulsante alla barra dello scorritore
	this->AddChild( &this->GetBarButton(), Gui::Container::PACKING_EXPAND, 0.0f, 0.0f );

	// Collego la dimensione del pulsante a quella dello scorritore
	this->GetBarButton().SignalResizing().connect( sigc::mem_fun( *this, &Slider::UpdateSize ) );

	// Collego il pulsante allo scorritore
	this->GetBarButton().SignalPressed().connect( sigc::bind( sigc::mem_fun( *this, &Slider::UpdateButton ), true ) );
	this->GetBarButton().SignalReleased().connect( sigc::bind( sigc::mem_fun( *this, &Slider::UpdateButton ), false ) );

	// Controllo l'orientamento dello scorritore
	if ( this->GetOrientation() == ORIENTATION_HORIZONTAL )

		// Imposto la dimensione del pulsante della barra dello scorritore
		this->GetBarButton().SetSize( Types::Size2D_u( size_.w * 0.15, size_.h ) );
	else
		// Imposto la dimensione del pulsante della barra dello scorritore
		this->GetBarButton().SetSize( Types::Size2D_u( size_.w, size_.h * 0.15 ) );


	// Imposto il font
	this->SetFont( NULL );

	// Imposto il flag di scorrimento
	this->scrolling = false;

	// Inizializzo le strutture
	this->old_fraction = this->GetFraction();

	// Imposto la barra dello scorritore
	this->GetBox().SetColor( Color::Make( 255, 255, 255, 150 ) );
	this->GetBox().SetBorderColor( Color::Make( 255, 255, 255, 200 ) );
	this->GetBox().SetBorderWidth( 1 );
}

Slider::~Slider() {

}

void
Slider::SetFraction( Types::Float value ) {

	// Imposto la frazione corrente
	InterfaceRange::SetFraction( value );

	// Controllo l'orientamento dello scorritore
	if ( this->GetOrientation() == ORIENTATION_HORIZONTAL ) {

		// Aggiorno la posizione del pulsate del cursore
		this->SetChildPosition( 0, this->GetFraction(), 0.5f );

	} else {

		// Aggiorno la posizione del pulsate del cursore
		this->SetChildPosition( 0, 0.5f, this->GetFraction() );
	}

	// Invio il segnale di impacchettamento del contenitore
	this->SendSignal( SignalType::UPDATE_PACKING, NULL );
}

void
Slider::UpdateSize( const Types::Size2D_u &size, Widget *widget ) {

	// Controllo l'orientamento dello scorritore
	if ( this->GetOrientation() == ORIENTATION_HORIZONTAL )

		// Aggiorno la dimensione del pulsante
		this->SetSize( Types::Size2D_u( VMAX( this->GetSize().w, this->GetBarButton().GetSize().w ),
										this->GetBarButton().GetSize().h ) );
	else
		// Aggiorno la dimensione del pulsante
		this->SetSize( Types::Size2D_u( this->GetBarButton().GetSize().w,
										VMAX( this->GetSize().h, this->GetBarButton().GetSize().h ) ) );
}

void
Slider::UpdateButton( Button *, Types::Bool pressed ) {

	// Aggiorno il valore dello scorritore
	if ( pressed ) {

		// Imposto il flag di scorrimento
		this->scrolling = true;

		// Memorizzo la posizione del mouse al momento della pressione
		this->mouse_pos = this->GetEngine()->GetInputManager().GetMousePosition();

		// Memorizzo la frazione prima della pressione
		this->old_fraction = this->GetFraction();

	} else {

		// Disabilito il flag di scorrimento
		this->scrolling = false;

		// Invia il segnale di modifica della frazione
		this->SendSignal( SignalType::CHANGE_FRACTION, NULL );
	}
}

void
Slider::ReadKeyboard() {

	// Ricavo il gestore degli eventi in ingresso
	InputManager &input_manager = this->GetEngine()->GetInputManager();

	// Ricavo la lista dei caratteri premuti
	const InputManager::KeyList keys = input_manager.GetKeyList();

	// Iteratori
	InputManager::KeyList::const_iterator iter = keys.begin();
	InputManager::KeyList::const_iterator end = keys.end();

	// Applico i nuovi caratteri alla stringa
	for ( ; iter != end; iter++ ) {

		// Gestisco la freccia sinistra
		if ( iter->sym == SDLK_LEFT ) {

			// Decremento il valore dello scorritore
			this->SetValue( this->GetValue() - this->GetStep() );

		// Gestisco la freccia destra
		} else if ( iter->sym == SDLK_RIGHT ) {

			// Incremento il valore dello scorritore
			this->SetValue( this->GetValue() + this->GetStep() );
		}
	}
}

void
Slider::ReadJoystick() {

	// Ricavo il gestore degli eventi in ingresso
	InputManager &input_manager = this->GetEngine()->GetInputManager();

	// Ricavo l'asse orizzontale del joystick
	Types::Float axis_x = input_manager.GetJoystickAxis( InputManager::JOYSTICK_0, InputManager::JOY_AXIS_X, true );

	// Gestisco la freccia sinistra del joystick
	if ( axis_x < 0.0f ) {

		// Decremento il valore dello scorritore
		this->SetValue( this->GetValue() - this->GetStep() );

	// Gestisco la freccia destra del joystick
	} else if ( axis_x > 0.0f ) {

		// Incremento il valore dello scorritore
		this->SetValue( this->GetValue() + this->GetStep() );
	}
}

void
Slider::SendSignal( Types::Int type, Entity *other ) {

	// Chiamo il gestore dei segnali
	Container::SendSignal( type, other );

	// Controlla il tipo di segnale
	switch ( type ) {

		// Gestisco il segnale di pressione con il tasto sinistro del mouse
		case SignalType::MOUSE_LEFT_PRESSED: {

			// Imposto il flag di scorrimento
			this->scrolling = true;

			// Memorizzo la posizione del mouse al momento della pressione
			this->mouse_pos = this->GetPosition() + Types::Point2D(	(Types::Float) this->GetBarButton().GetSize().w / 2.0f,
																	(Types::Float) this->GetBarButton().GetSize().h / 2.0f );

			// Attivo il pulsante dello scorritore
			this->GetBarButton().SetPressed( true );

			// Memorizzo la frazione prima della pressione
			this->old_fraction = 0.0f;

			break;
		}

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
Slider::Update( Viewer *viewer, Player *player ) {

	// Controllo se il widget ha il focus
	if ( this->GetFocus() ) {

		// Legge l'input da tastiera
		this->ReadKeyboard();

		// Legge l'input del joystick
		this->ReadJoystick();
	}

	// Controllo se è impostato il flag di scorrimento
	if ( this->scrolling ) {

		// Ricavo il gestore degli eventi in ingresso
		InputManager &input_manager = this->GetEngine()->GetInputManager();

		// Controllo l'orientamento dello scorritore
		if ( this->GetOrientation() == ORIENTATION_HORIZONTAL ) {

			// Aggiorno la posizione del cursore
			Types::Float new_fraction =	this->old_fraction + ( input_manager.GetMousePosition().x - this->mouse_pos.x ) / \
										(Types::Float) ( this->GetSize().w - this->GetBarButton().GetSize().w );

			// Imposto la frazione del cursore
			this->SetFraction( new_fraction );

		} else {

			// Aggiorno la posizione del cursore
			Types::Float new_fraction =	this->old_fraction + ( input_manager.GetMousePosition().y - this->mouse_pos.y ) / \
										(Types::Float) ( this->GetSize().h - this->GetBarButton().GetSize().h );

			// Imposto la frazione del cursore
			this->SetFraction( new_fraction );
		}
	}

	// Chiamo la funzione di aggiornamento
	Container::Update( viewer, player );
}

void
Slider::DrawRuler( const Types::Point2D &offset, Color::RGBA8 blend ) const {

	// Ricavo il disegnatore principale
	const Designer &designer = this->GetEngine()->GetDesigner();

	// Iteratore
	Types::Uint i = 0;

	for ( ; i <= 10; i++ ) {

		// Imposto il colore della barra dello scorritore
		designer.SetColor( this->GetBox().GetBorderColor(), this->GetOpacity() );

		// Controllo l'orientamento dello scorritore
		if ( this->GetOrientation() == ORIENTATION_HORIZONTAL ) {

			// Calcolo il punto del segmento del righello
			Types::Point2D point(	(Types::Float) this->GetBarButton().GetSize().w / 2.0f + \
									i * ( (Types::Float) this->GetSize().w - (Types::Float) this->GetBarButton().GetSize().w ) / 10.0f, 0.0f );

			// Disegno le "tacche" dello scorritore
			designer.DrawLine(	this->GetPosition() + point,
								this->GetPosition() + point + Types::Point2D( 0, -5.0f ) );

		} else {

			// Calcolo il punto del segmento del righello
			Types::Point2D point(	0.0f, (Types::Float) this->GetBarButton().GetSize().h / 2.0f + \
									i * ( (Types::Float) this->GetSize().h - (Types::Float) this->GetBarButton().GetSize().h ) / 10.0f );

			// Disegno le "tacche" dello scorritore
			designer.DrawLine(	this->GetPosition() + point,
								this->GetPosition() + point + Types::Point2D( -5.0f, 0 ) );
		}
	}


	// Dimensione del buffer di lavoro
	Types::Uint size = wcslen( this->GetLabelFormat() ) + 10;

	// Strutture di lavoro
	wchar_t buffer[ size ];

	// Converto il numero in carattere
	swprintf( buffer, size, this->GetLabelFormat(), this->GetValue() );

	// Imposto il colore
	this->GetFont()->SetColor( this->GetColor() );

	// Controllo l'orientamento dello scorritore
	if ( this->GetOrientation() == ORIENTATION_HORIZONTAL ) {

		// Disegno l'etichetta
		this->GetFont()->Draw(	this->GetEngine()->GetDesigner(), buffer,
								this->GetBarButton().GetPosition() + \
								Types::Point2D(	(Types::Float) this->GetBarButton().GetSize().w / 2.0f - \
												(Types::Float) this->GetFont()->GetStringWidth( buffer ) / 2.0f,
												- (Types::Float) this->GetFont()->GetClipSize().h - 5.0f ), blend );

	} else {

		// Disegno l'etichetta
		this->GetFont()->Draw(	this->GetEngine()->GetDesigner(), buffer,
								this->GetBarButton().GetPosition() + 
								Types::Point2D(	- (Types::Float) this->GetFont()->GetStringWidth( buffer ) - 10.0f,
												(Types::Float) this->GetBarButton().GetSize().h / 2.0f - \
												(Types::Float) this->GetFont()->GetClipSize().h / 2.0f ), blend );
	}
}

void
Slider::Draw( const Types::Point2D &offset, Color::RGBA8 blend ) const {

	// Funzione di disegno del testo
	Frame::Draw( offset, blend );

	// Controllo la visibilità del righello
	if ( this->GetRulerVisible() && this->GetBarButton().GetPressed() ) {

		// Disegno il righello dello scorritore
		this->DrawRuler( offset, blend );
	}

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
