/* 
    Title --- font.cpp

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


#ifndef VGE_FONT_CPP
#define VGE_FONT_CPP

#include "vge/widgets/font.hpp"

#include "vge/global.hpp"
#include "vge/inline/global-inl.hpp"

#include "vge/designer.hpp"
#include "vge/inline/designer-inl.hpp"

#include "vge/interfaces/i-image.hpp"
#include "vge/interfaces/inline/i-image-inl.hpp"

#include "vge/widgets/inline/font-inl.hpp"

namespace VGE { // Namespace di VGE

namespace Gui { // Namespace dell'interfaccia grafica

Font::Font( const std::string &path, const Types::Size2D_u &size_ ) :

	InterfaceImage( path, size_ ) {

	// Aggiungo il font alla lista generale
	Global::Fonts.push_back( this );

	// Costruisco il nome temporaneo del font
	wchar_t _name[30]; swprintf( _name, 30, L"font%zu", Global::Fonts.size() - 1 );

	// Imposto il nome del font
	this->SetName( _name );

	// Imposto lo spazio tra i caratteri
	this->SetLetterSpacing( 0 );

	// Disabilito il color blending per i toni ambientali
	this->SetColorBlending( false );

	// Carico la larghezza dei caratteri
	this->LoadCharWidth( path + INFO_EXTENSION );

	// Aggiorno le strutture del carattere
	this->Logic();
}

Font::~Font() {

	// Rimuovo il font dalla lista generale
	Global::Fonts.remove( this );
}

void
Font::LoadCharWidth( const std::string &path ) {

	// Iteratore
	Types::Uint i = 0;

	// Apro lo stream al file con le informazioni
	std::ifstream in( path.c_str(), std::ios_base::in );

	// Controllo se il file è stato aperto correttamente
	if ( in.is_open() ) {

		// Struttura di lavoro
		std::string tmp;

		// Estraggo tutte le larghezze dei 256 caratteri
		while ( in.good() && i < 256 ) {

			// Leggo il carattere corrente
			char c = (char) in.get();

			// Controllo se le cifre del primo numero sono terminate
			if ( c == ',' ) {

				// Memorizzo la larghezza del carattere
				sscanf( tmp.c_str(), "%u", &this->char_width[i++] );

				// Pulisco la stringa della larghezza
				tmp.clear();

			// Controllo se si tratta di una cifra numerica
			} else if ( isdigit( c ) ) {

				// La aggiungo alla stringa della larghezza
				tmp += c;
			}
		}

	} else {

		// Comunico l'errore
		printf( " %s: Impossibile caricare la larghezza dei caratteri \"%s\"!\n", WARNING, path.c_str() );

		// Iteratore
		Types::Uint i = 0;

		// Imposto la larghezza di default
		for ( ; i < 256; i++ )

			this->char_width[i] = this->clip.w;
	}
}

Types::Float
Font::GetStringWidth( const std::wstring &string ) const {

	// Larghezza della stringa
	Types::Float width = 0.0f;

	// Iteratore
	Types::Uint i = 0;

	// Calcolo la larghezza della stringa
	for( ; i < string.length(); i++ ) {

		width += this->GetCharWidth( string[i] );
	}

	// Ritorno la larghezza di una stringa
	return width;
}

Types::Uint
Font::GetStringIndexAt( const std::wstring &string, Types::Float off_x ) const {

	// Larghezza della stringa
	Types::Float width = 0.0f;

	// Iteratore
	Types::Uint i = 0;

	// Calcolo la larghezza della stringa
	for( ; i < string.length() && ( width += this->GetCharWidth( string[i] ) ) <= off_x; i++ );

	// Ritorno l'indice del carattere di una stringa alla posizione indicata
	return i;
}

void
Font::Draw(	const Designer &designer, const wchar_t char_,
			const Types::Point2D &offset, Color::RGBA8 blend ) {

	// Seleziono il carattere
	Types::Uint index = (Types::Uint) char_;
	this->SetClipOffset( Types::Size2D_u( index % this->char_l, index / this->char_l ) );

	// Disegno il carattere sullo schermo
	this->DrawImage( designer, offset, Types::Point2D( 0.0f, 0.0f ), blend );
}

void
Font::Draw(	const Designer &designer, const std::wstring &string,
			const Types::Point2D &offset, Color::RGBA8 blend ) {

	// Offset del carattere
	Types::Uint off_char = 0;

	// Iteratore
	Types::Uint i = 0;

	// Disegno i caratteri della stringa
	for( ; i < string.length(); i++ ) {

		// Seleziono il carattere
		Types::Uint index = (Types::Uint) string[i];
		this->SetClipOffset( Types::Size2D_u( index % this->char_l, index / this->char_l ) );

		// Disegno il carattere sullo schermo
		this->DrawImage( designer,	Types::Point2D( offset.x + off_char, offset.y ),
									Types::Point2D( 0.0f, 0.0f ), blend );

		// Incremento l'offset del carattere
		off_char += this->GetCharWidth( string[i] );
	}
}

void
Font::Draw(	const Designer &designer, const std::wstring &string,
			const Types::Uint start, const Types::Uint end,
			const Types::Point2D &offset, Color::RGBA8 blend ) {

	// Offset del carattere
	Types::Uint off_char = 0;

	// Iteratore
	Types::Uint i = start;

	// Disegno i caratteri della stringa
	for( ; i < end; i++ ) {

		// Seleziono il carattere
		Types::Uint index = (Types::Uint) string[i];
		this->SetClipOffset( Types::Size2D_u( index % this->char_l, index / this->char_l ) );

		// Disegno il carattere sullo schermo
		this->DrawImage( designer,	Types::Point2D( offset.x + off_char, offset.y ),
									Types::Point2D( 0.0f, 0.0f ), blend );

		// Incremento l'offset del carattere
		off_char += this->GetCharWidth( string[i] );
	}
}

}; // Chiudo il namespace dell'interfaccia grafica

}; // Chiudo il namespace di VGE

#endif
