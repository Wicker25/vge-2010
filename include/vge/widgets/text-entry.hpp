/* 
    Title --- text-entry.hpp

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


#ifndef VGE_TEXT_ENTRY_HPP
#define VGE_TEXT_ENTRY_HPP

#include <iostream>
#include <vector>
#include <list>

#include "vge/consts.hpp"
#include "vge/types.hpp"
#include "vge/math.hpp"
#include "vge/global.hpp"

#include "vge/interfaces/i-resizable.hpp"
#include "vge/interfaces/i-colorable.hpp"

#include "vge/entity.hpp"

#include "vge/widgets/box.hpp"
#include "vge/widgets/font.hpp"
#include "vge/widgets/widget.hpp"
#include "vge/widgets/frame.hpp"

namespace VGE { // Namespace di VGE

namespace Gui { // Namespace dell'interfaccia grafica

class TextEntry : public Frame, public InterfaceColorable {

	/* CASELLA DI IMMISSIONE DEL TESTO */

public:

	// Metodi costruttore e distruttore
	TextEntry( const std::wstring &string );
	TextEntry( const std::wstring &string, Font *font );
	virtual ~TextEntry();

	// Imposta il font
	virtual void SetFont( Font *font );
	// Ritorna il puntatore al font
	virtual Font *GetFont() const;

	// Imposta il testo
	virtual void SetString( const std::wstring &string );
	// Ritorna la stringa del testo
	virtual const std::wstring GetString() const;

	// Imposta il numero massimo di caratteri
	virtual void SetMaxChars( Types::Uint value );
	// Ritorna il numero massimo di caratteri
	virtual Types::Uint GetMaxChars() const;

	// Imposta la posizione del cursore
	virtual void SetCursorPosition( Types::Uint position );
	// Muove la posizione del cursore
	virtual void MoveCursorPosition( Types::Uint position );
	// Ritorna la posizione del cursore
	virtual Types::Uint GetCursorPosition() const;

	// Imposta il carattere del cursore
	virtual void SetCursorChar( wchar_t value );
	// Ritorna il carattere del cursore
	virtual wchar_t GetCursorChar() const;

	// Imposta il colore del cursore
	virtual void SetCursorColor( Color::RGBA8 value );
	// Ritorna il colore del cursore
	virtual Color::RGBA8 GetCursorColor() const;

	// Aggiusta lo scorrimento della casella di testo
	virtual void AdjustScroll();

	// Invia un segnale alla casella di testo
	virtual void SendSignal( Types::Int type, Entity *other );

	// Funzione di lavoro
	virtual void Update( Viewer *viewer, Player *player );

	// Disegna il testo sullo schermo
	virtual void Draw( const Types::Point2D &offset, Color::RGBA8 blend ) const;

protected:

	// Puntatore al font
	Font *t_font;

	// Puntatore alla stringa
	std::wstring t_string;

	// Numero massimo di caratteri
	Types::Uint max_chars;

	// Posizione del cursore
	Types::Uint cursor_pos;

	// Carattere del cursore
	wchar_t cursor_char;

	// Colore del cursore
	Color::RGBA8 cursor_color;

	// Scorrimento della casella di testo
	Types::Float scrollx;

	// Legge l'input da tastiera
	virtual void ReadKeyboard();

	// Legge l'input dal joystick
	virtual void ReadJoystick();
};

// Ridefinizione dei tipo lista
typedef std::list< TextEntry * > TextEntryList;

}; // Chiudo il namespace dell'interfaccia grafica

}; // Chiudo il namespace di VGE

#endif
