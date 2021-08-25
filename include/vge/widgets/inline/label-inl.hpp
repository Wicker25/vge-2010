/* 
    Title --- label-inl.hpp

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


#ifndef VGE_LABEL_INL_HPP
#define VGE_LABEL_INL_HPP

#include "vge/widgets/label.hpp"

namespace VGE { // Namespace di VGE

namespace Gui { // Namespace dell'interfaccia grafica

inline void
Label::SetFont( Font *font ) {

	// Imposto il font
	this->t_font = font;

	// Controllo se è stato impostato il font
	if ( this->GetFont() != NULL ) {

		// Imposto il flag di aggiornamento
		this->update = true;
	}
}

inline Font *
Label::GetFont() const {

	// Ritorno il puntatore al font
	return ( this->t_font != NULL ) ? this->t_font : Global::GetFont( SYS_FONT_NORMAL );
}

inline void
Label::SetString( const std::wstring &string ) {

	// Imposto la stringa
	this->t_string = string;

	// Controllo se è stato impostato il font
	if ( this->GetFont() != NULL ) {

		// Imposto il flag di aggiornamento
		this->update = true;
	}
}

inline const std::wstring
Label::GetString() const {

	// Ritorno la stringa
	return this->t_string;
}

inline Types::Uint
Label::Lenght() const {

	// Ritorna la lunghezza della stringa
	return (Types::Uint) this->GetString().length();
}

}; // Chiudo il namespace dell'interfaccia grafica

}; // Chiudo il namespace di VGE

#endif
