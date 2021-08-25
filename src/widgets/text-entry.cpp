/* 
    Title --- text-entry.cpp

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


#ifndef VGE_TEXT_ENTRY_CPP
#define VGE_TEXT_ENTRY_CPP

#include "vge/widgets/text-entry.hpp"

#include "vge/input-manager.hpp"
#include "vge/inline/input-manager-inl.hpp"

#include "vge/interfaces/i-resizable.hpp"
#include "vge/interfaces/inline/i-resizable-inl.hpp"

#include "vge/interfaces/i-colorable.hpp"
#include "vge/interfaces/inline/i-colorable-inl.hpp"

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

#include "vge/widgets/inline/text-entry-inl.hpp"

namespace VGE { // Namespace di VGE

namespace Gui { // Namespace dell'interfaccia grafica

TextEntry::TextEntry( const std::wstring &string ) : Frame( Types::Point3D( 0.0f, 0.0f, 0.0f ) ) {

	// Inizializzo le strutture
	this->scrollx = 0.0f;

	// Imposto il font
	this->SetFont( NULL );

	// Imposto la stringa
	this->SetString( string );

	// Imposto il numero massimo di caratteri
	this->SetMaxChars( 128 );

	// Imposto il colore dell'etichetta
	this->SetColor( Color::Make( 255, 255, 255, 255 ) );

	// Imposto il carattere del cursore
	this->SetCursorChar( L'\x0A' );

	// Imposto il colore del cursore
	this->SetCursorColor( Color::Make( 255, 255, 150, 255 ) );

	// Imposto l'opacità del testo
	this->SetOpacity( 255 );

	// Abilito la capacità di prendere il focus
	this->SetFocusable( true );

	// Nascondo il riquadro della casella di testo
	this->GetBox().SetColor( Color::Make( 255, 255, 255, 50 ) );
	this->GetBox().SetBorderColor( Color::Make( 255, 255, 255, 255 ) );
	this->GetBox().SetBorderWidth( 1 );
}

TextEntry::TextEntry( const std::wstring &string, Font *font ) : Frame( Types::Point3D( 0.0f, 0.0f, 0.0f ) ) {

	// Inizializzo le strutture
	this->scrollx = 0.0f;

	// Imposto il font
	this->SetFont( font );

	// Imposto la stringa
	this->SetString( string );

	// Imposto il numero massimo di caratteri
	this->SetMaxChars( 128 );

	// Imposto il colore dell'etichetta
	this->SetColor( Color::Make( 255, 255, 255, 255 ) );

	// Imposto il carattere del cursore
	this->SetCursorChar( L'\x0A' );

	// Imposto il colore del cursore
	this->SetCursorColor( Color::Make( 255, 255, 150, 255 ) );

	// Imposto l'opacità del testo
	this->SetOpacity( 255 );

	// Nascondo il riquadro della casella di testo
	this->GetBox().SetColor( Color::Make( 255, 255, 255, 50 ) );
	this->GetBox().SetBorderColor( Color::Make( 255, 255, 255, 255 ) );
	this->GetBox().SetBorderWidth( 1 );
}

TextEntry::~TextEntry() {

}

void
TextEntry::ReadKeyboard() {

	// Ricavo il gestore degli eventi in ingresso
	InputManager &input_manager = this->GetEngine()->GetInputManager();

	// Ricavo la lista dei caratteri premuti
	const InputManager::KeyList keys = input_manager.GetKeyList();

	// Iteratori
	InputManager::KeyList::const_iterator iter = keys.begin();
	InputManager::KeyList::const_iterator end = keys.end();

	// Applico i nuovi caratteri alla stringa
	for ( ; iter != end; iter++ ) {

		// Gestisco il tasto "home"
		if ( iter->sym == SDLK_HOME ) {

			// Sposto il cursore all'inizio del testo
			this->SetCursorPosition( 0 );

			// Visualizzo la stringa dal primo carattere
			this->scrollx = 0.0f;

		// Gestisco il tasto "end"
		} else if ( iter->sym == SDLK_END ) {

			// Sposto il cursore alla fine del testo
			this->SetCursorPosition( this->GetString().length() );

		// Gestisco la freccia sinistra
		} else if ( iter->sym == SDLK_LEFT ) {

			// Sposto il cursore sul carattere precedente
			this->MoveCursorPosition( -1 );

		// Gestisco la freccia destra
		} else if ( iter->sym == SDLK_RIGHT ) {

			// Sposto il cursore sul carattere successivo
			this->MoveCursorPosition( 1 );

		// Gestisco il tasto "delete"
		} else if ( iter->wchar == SDLK_DELETE ) {

			// Controllo che ci sia almeno un carattere
			if ( this->GetCursorPosition() != this->GetString().length() )

				// Cancello il carattere sul cursore
				this->t_string.erase( this->t_string.begin() + this->GetCursorPosition() );

		// Gestisco il tasto "backslash"
		} else if ( iter->wchar == SDLK_BACKSPACE ) {

			// Controllo se esiste un carattere precedente il cursore
			if ( this->GetCursorPosition() > 0 ) {

				// Elimino il carattere precedente il cursore
				this->t_string.erase( this->t_string.begin() + this->GetCursorPosition() - 1 );

				// Sposto il cursore sul carattere precedente
				this->MoveCursorPosition( -1 );
			}

		// Gestisco i caratteri leggibili
		} else if ( iter->wchar >= L' ' && this->GetString().length() < this->GetMaxChars() ) {

			// Inserisco un nuovo carattere alla posizione del cursore
			this->t_string.insert( this->t_string.begin() + this->GetCursorPosition(), iter->wchar );

			// Sposto il cursore sul carattere successivo
			this->MoveCursorPosition( 1 );
		}
	}
}

void
TextEntry::ReadJoystick() {

	// Ricavo il gestore degli eventi in ingresso
	InputManager &input_manager = this->GetEngine()->GetInputManager();

	// Ricavo l'asse orizzontale del joystick
	Types::Float axis_x = input_manager.GetJoystickAxis( InputManager::JOYSTICK_0, InputManager::JOY_AXIS_X, true );

	// Gestisco la freccia sinistra del joystick
	if ( axis_x < 0.0f ) {

		// Sposto il cursore sul carattere precedente
		this->MoveCursorPosition( -1 );

	// Gestisco la freccia destra del joystick
	} else if ( axis_x > 0.0f ) {

		// Sposto il cursore sul carattere successivo
		this->MoveCursorPosition( 1 );

	// Gestisco il tasto "delete" del joystick
	} else if ( input_manager.GetJoystickButtonState(	InputManager::JOYSTICK_0,
														InputManager::JOY_BUTTON_1, true ) ) {

		// Controllo che ci sia almeno un carattere
		if ( this->GetCursorPosition() != this->GetString().length() )

			// Cancello il carattere sul cursore
			this->t_string.erase( this->t_string.begin() + this->GetCursorPosition() );

	// Gestisco il tasto "backspace" del joystick
	} else if ( input_manager.GetJoystickButtonState(	InputManager::JOYSTICK_0,
														InputManager::JOY_BUTTON_3, true ) ) {

		// Controllo se esiste un carattere precedente il cursore
		if ( this->GetCursorPosition() > 0 ) {

			// Elimino il carattere precedente il cursore
			this->t_string.erase( this->t_string.begin() + this->GetCursorPosition() - 1 );

			// Sposto il cursore sul carattere precedente
			this->MoveCursorPosition( -1 );
		}
	}
}

void
TextEntry::AdjustScroll() {

	// Aggiusta lo scorrimento orizzontale della casella di testo
	Types::Float cursor_x = this->GetFont()->GetStringWidth(

								this->GetString().substr( 0, this->GetCursorPosition() )
							);

	if ( cursor_x - scrollx > this->GetSize().w )

		this->scrollx = cursor_x - this->GetSize().w;

	else if ( cursor_x - scrollx < 0.0f )

		this->scrollx = cursor_x;
}

void
TextEntry::SendSignal( Types::Int type, Entity *other ) {

	// Chiamo il gestore dei segnali
	Widget::SendSignal( type, other );

	// Controlla il tipo di segnale
	switch ( type ) {

		// Gestisco il segnale di pressione con il tasto sinistro del mouse
		case SignalType::MOUSE_LEFT_PRESSED: {

			// Ricavo il gestore degli eventi in ingresso
			InputManager &events = this->GetEngine()->GetInputManager();

			// Controllo che sia stato definito un font
			if ( this->GetFont() != NULL ) {

				// Posizione del mouse all'interno della casella di testo
				Types::Float pos_x = events.GetMousePosition().x - this->GetPosition().x + this->scrollx;

				// Calcolo la nuova posizione del cursore
				Types::Uint cur = this->GetFont()->GetStringIndexAt( this->GetString(), pos_x );

				// Imposto la posizione del cursore
				this->SetCursorPosition( cur );
			}

			break;
		}

		default: break;
	}
}

void
TextEntry::Update( Viewer *viewer, Player *player ) {

	// Avvio la funzione di lavoro superiore
	Widget::Update( viewer, player );

	// Controllo se il widget ha il focus
	if ( this->GetFocus() ) {

		// Legge l'input da tastiera
		this->ReadKeyboard();

		// Legge l'input del joystick
		this->ReadJoystick();
	}

	// Controllo i parametri del testo
	if ( this->GetFont() != NULL ) {

		// Aggiusto lo scorrimento della casella di testo
		this->AdjustScroll();
	}
}

void
TextEntry::Draw( const Types::Point2D &offset, Color::RGBA8 blend ) const {

	// Funzione di disegno del testo
	Frame::Draw( offset, blend );

	// Controllo che il testo sia realmente visibile
	if ( this->GetFont() != NULL && this->GetOpacity() > 0 ) {

		// Calcolo la posizione
		Types::Point2D pos = this->GetPosition() + offset;

		// Imposto il colore
		this->GetFont()->SetColor( this->GetColor() );

		// Offset del carattere
		Types::Float tmp, off_char = -this->scrollx;

		// Iteratore
		Types::Uint i = 0;

		// Imposto l'area disegnabile sullo schermo
		this->GetEngine()->GetDesigner().PushDrawableArea(

					Types::Rect_u(	offset.x + this->GetPosition().x + 1,
									offset.y + this->GetPosition().y + 1,
									offset.x + this->GetPosition().x + this->GetSize().w - 1,
									offset.y + this->GetPosition().y + this->GetSize().h - 1 )
		);

		// Disegno la stringa nella casella di testo
		for ( ;	i < this->GetString().length() && off_char <= (Types::Float) this->GetSize().w; i++ ) {

			// Stampo solo i caratteri dentro la casella di testo
			if ( off_char + ( tmp = this->GetFont()->GetCharWidth( this->GetString()[i] ) ) >= 0 ) {

				// Disegno il carattere
				this->GetFont()->Draw(	this->GetEngine()->GetDesigner(),
										this->GetString()[i], Types::Point2D( pos.x + off_char, pos.y ), blend );
			}

			// Incremento l'offset del carattere
			off_char += tmp;
		}

		// Imposto l'area disegnabile sullo schermo
		this->GetEngine()->GetDesigner().PopDrawableArea();

		// Calcolo la posizione del cursore
		off_char = this->GetFont()->GetStringWidth( this->GetString().substr( 0, this->GetCursorPosition() ) );

		// Imposto il colore del cursore
		this->GetFont()->SetColor( this->GetCursorColor() );

		// Disegno il cursore
		this->GetFont()->Draw(	this->GetEngine()->GetDesigner(), this->GetCursorChar(),
								Types::Point2D( pos.x + off_char - this->scrollx , pos.y ), blend );
	}
}

}; // Chiudo il namespace dell'interfaccia grafica

}; // Chiudo il namespace di VGE

#endif
