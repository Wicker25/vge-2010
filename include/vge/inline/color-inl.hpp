/* 
    Title --- color-inl.hpp

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


#ifndef VGE_COLOR_INL_HPP
#define VGE_COLOR_INL_HPP

#include "vge/color.hpp"

namespace VGE { // Namespace di VGE

namespace Color { // Namespace del colore

inline Struct *
ToStruct( const Types::Uint32 &color ) {

	// Casting dal colore alla struttura complessa
	return (Struct *) &color;
}

inline RGBA8
Make( Types::Uint32 color ) {

	// Costruisco il colore
	return SWAP32( color );
}

inline RGBA8
Make( Types::Uint8 red, Types::Uint8 green, Types::Uint8 blue ) {

	// Costruisco il colore
	return Make( red, green, blue, 255 );
}

inline Types::Uint8
Split( RGBA8 color, Channel channel ) {

	// Estraggo il canale di un colore
	return (Types::Uint8) ( ( color >> channel ) & 0xFF );
}

inline RGBA8
Blend( RGBA8 color0, RGBA8 color1 ) {

	// Ricavo il canale alpha	
	Types::Float alpha = (Types::Float) ToStruct( color0 )->alpha / 255.0f;

	// Ritorno il colore risultante dal blending
	return BlendAlpha( color0, color1, alpha );
}

}; // Chiudo il namespace del colore

}; // Chiudo il namespace di VGE

#endif
