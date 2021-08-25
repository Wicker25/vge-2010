/* 
    Title --- text-entry-inl.hpp

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


#ifndef VGE_TEXT_ENTRY_INL_HPP
#define VGE_TEXT_ENTRY_INL_HPP

#include "vge/widgets/text-entry.hpp"

namespace VGE { // Namespace di VGE

namespace Gui { // Namespace dell'interfaccia grafica

inline void
TextEntry::SetFont( Font *font ) {

	// Imposto il font
	this->t_font = font;

	// Controllo se è stato impostato il font
	if ( this->GetFont() != NULL ) {

		// Aggiorno le dimensioni del widget
		this->SetSize( Types::Size2D_u( this->GetFont()->GetStringWidth( this->GetString() ),
										this->GetFont()->GetClipSize().h ) );
	}

}

inline Font *
TextEntry::GetFont() const {

	// Ritorno il puntatore al font
	return ( this->t_font != NULL ) ? this->t_font : Global::GetFont( SYS_FONT_NORMAL );
}

inline void
TextEntry::SetString( const std::wstring &string ) {

	// Imposto la stringa
	this->t_string = string;

	// Controllo se è stato impostato il font
	if ( this->GetFont() != NULL ) {

		// Aggiorno le dimensioni del widget
		this->SetSize( Types::Size2D_u( this->GetFont()->GetStringWidth( this->GetString() ),
										this->GetFont()->GetClipSize().h ) );
	}
}

inline const std::wstring
TextEntry::GetString() const {

	// Ritorno la stringa
	return this->t_string;
}

inline void
TextEntry::SetMaxChars( Types::Uint value ) {

	// Imposto il numero massimo di caratteri
	this->max_chars = value;
}

inline Types::Uint
TextEntry::GetMaxChars() const {

	// Ritorno il numero massimo di caratteri
	return this->max_chars;
}

inline void
TextEntry::SetCursorPosition( Types::Uint position ) {

	// Imposto la posizione del cursore
	this->cursor_pos = position;
}

inline void
TextEntry::MoveCursorPosition( Types::Uint position ) {

	// Muovo la posizione del cursore
	this->cursor_pos = (Types::Uint) VMIN( VMAX( (Types::Int) this->GetCursorPosition() + \
										(Types::Int) position, 0 ), (Types::Int) this->GetString().length() );
}

inline Types::Uint
TextEntry::GetCursorPosition() const {

	// Ritorno la posizione del cursore
	return this->cursor_pos;
}

inline void
TextEntry::SetCursorChar( const wchar_t character ) {

	// Imposto il carattere del cursore
	this->cursor_char = character;
}

inline wchar_t 
TextEntry::GetCursorChar() const {

	// Ritorno il carattere del cursore
	return this->cursor_char;
}

inline void
TextEntry::SetCursorColor( Color::RGBA8 value ) {

	// Modifico i colori del cursore
	this->cursor_color = value;
}

inline Color::RGBA8
TextEntry::GetCursorColor() const {

	// Ritorno i colori del cursore
	return this->cursor_color;
}

}; // Chiudo il namespace dell'interfaccia grafica

}; // Chiudo il namespace di VGE

#endif
