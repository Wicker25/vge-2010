/* 
    Title --- font.hpp

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


#ifndef VGE_FONT_HPP
#define VGE_FONT_HPP

#include <iostream>
#include <fstream>
#include <vector>

#include "vge/consts.hpp"
#include "vge/types.hpp"
#include "vge/error.hpp"
#include "vge/math.hpp"
#include "vge/global.hpp"

#include "vge/designer.hpp"

#include "vge/interfaces/i-image.hpp"

#define INFO_EXTENSION	".info"

namespace VGE { // Namespace di VGE

namespace Gui { // Namespace dell'interfaccia grafica

class Font : public InterfaceImage {

	/* CARATTERE */

public:

	// Metodi costruttore e distruttore
	Font( const std::string &path, const Types::Size2D_u &size_ );
	virtual ~Font();

	// Carica l'immagine dal font
	virtual void LoadImage( const std::string &path, const Types::Size2D_u &size_ );

	// Imposta il nome del font
	void SetName( const std::wstring &name );
	// Ritorna il nome del font
	std::wstring GetName() const;

	// Carica la larghezza dei caratteri da un file di testo
	void LoadCharWidth( const std::string &path );

	// Imposta lo spazio tra i caratteri
	void SetLetterSpacing( Types::Uint value );
	// Ritorna lo spazio tra i caratteri
	Types::Uint GetLetterSpacing();

	// Ritorna la larghezza di una stringa
	virtual Types::Float GetStringWidth( const std::wstring &string ) const;
	// Ritorna la larghezza di un carattere
	virtual Types::Float GetCharWidth( const wchar_t character ) const;

	// Ritorna l'indice del carattere di una stringa alla posizione indicata
	virtual Types::Uint GetStringIndexAt( const std::wstring &string, Types::Float off_x ) const;

	// Disegna un carattere sullo schermo
	virtual void Draw(	const Designer &designer, const wchar_t char_,
						const Types::Point2D &offset, Color::RGBA8 blend );

	// Disegna una stringa sullo schermo
	virtual void Draw(	const Designer &designer, const std::wstring &string,
						const Types::Point2D &offset, Color::RGBA8 blend );

	virtual void Draw(	const Designer &designer, const std::wstring &string, const Types::Uint start,
						const Types::Uint end, const Types::Point2D &offset, Color::RGBA8 blend );

protected:

	// Aggiorno le strutture del carattere
	void Logic();

	// Nome del font
	std::wstring f_name;

	// Dimensione dei caratteri
	Types::Uint char_width[256];

	// Spazio tra i caratteri
	Types::Uint letter_spacing;

	// Numero di caratteri per linea
	Types::Uint char_l;
};

// Ridefinizione del tipo lista
typedef std::vector< Font * > FontList;

}; // Chiudo il namespace dell'interfaccia grafica

}; // Chiudo il namespace di VGE

#endif
