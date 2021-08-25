/* 
    Title --- font-inl.hpp

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


#ifndef VGE_FONT_INL_HPP
#define VGE_FONT_INL_HPP

#include "vge/widgets/font.hpp"

namespace VGE { // Namespace di VGE

namespace Gui { // Namespace dell'interfaccia grafica

inline void
Font::LoadImage( const std::string &path, const Types::Size2D_u &size_ ) {

	// Carico l'immagine dal file
	InterfaceImage::LoadImage( path, size_ );

	// Aggiorno le strutture del carattere
	this->Logic();
}

inline void
Font::SetName( const std::wstring &name ) {

	// Imposto il nome del font
	this->f_name = name;
}

inline std::wstring
Font::GetName() const {

	// Ritorno il nome del font
	return this->f_name;
}

inline void
Font::SetLetterSpacing( Types::Uint value ) {

	// Imposto lo spazio tra i caratteri
	this->letter_spacing = value;
}

inline Types::Uint
Font::GetLetterSpacing() {

	// Ritorno lo spazio tra i caratteri
	return this->letter_spacing;
}

inline Types::Float
Font::GetCharWidth( const wchar_t character ) const {

	// Ritorno la dimensione di un carattere
	return (Types::Float) this->char_width[(Types::Uint) character] * this->scale.w + this->letter_spacing;
}

inline void
Font::Logic() {

	// Calcolo il numero di caratteri per riga
	this->char_l = ( this->or_image_s.w / this->clip.w ); // FIXMI inserirlo in una funzione a parte
}

}; // Chiudo il namespace dell'interfaccia grafica

}; // Chiudo il namespace di VGE

#endif
