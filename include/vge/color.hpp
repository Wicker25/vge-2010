/* 
    Title --- color.hpp

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


#ifndef VGE_COLOR_HPP
#define VGE_COLOR_HPP

#include <iostream>
#include <vector>

#include "vge/consts.hpp"
#include "vge/types.hpp"
#include "vge/error.hpp"
#include "vge/math.hpp"

#define RMASK	0x000000FF
#define GMASK	0x0000FF00
#define BMASK	0x00FF0000
#define AMASK	0xFF000000

#define RSHIFT	0
#define GSHIFT	8
#define BSHIFT	16
#define ASHIFT	24

namespace VGE { // Namespace di VGE

namespace Color { // Namespace del colore

// Informazioni di un pixel
typedef enum {

	CH_RED		= RSHIFT,	// Rosso
	CH_GREEN	= GSHIFT,	// Verde
	CH_BLUE		= BSHIFT,	// Blu
	CH_ALPHA	= ASHIFT,	// Alpha

} Channel;

// Struttura semplice del colore
typedef Types::Uint32 RGBA8;

// Struttura complessa del colore
struct Struct {

	Types::Uint8 red;	// Rosso
	Types::Uint8 green;	// Verde
	Types::Uint8 blue;	// Blue
	Types::Uint8 alpha;	// Alpha
};

// Casting dal colore alla struttura complessa
Struct *ToStruct( const Types::Uint32 &color );

// Costruisce un colore
RGBA8 Make( Types::Uint32 color );
RGBA8 Make( Types::Uint8 red, Types::Uint8 green, Types::Uint8 blue );
RGBA8 Make( Types::Uint8 red, Types::Uint8 green, Types::Uint8 blue, Types::Uint8 alpha );

// Estrae il canale di un colore
Types::Uint8 Split( RGBA8 color, Channel channel );

// Miscela due colori secondo il canale alpha
RGBA8 Blend( RGBA8 color0, RGBA8 color1 );

// Miscela due colori in base ad un valore alpha
RGBA8 BlendAlpha( RGBA8 color0, RGBA8 color1, Types::Float alpha );

// Miscela due colori attraverso una media aritmetica
RGBA8 BlendAvg( RGBA8 color0, RGBA8 color1 );

// Miscela due colori attraverso la somma
RGBA8 BlendSum( RGBA8 color0, RGBA8 color1 );

// Miscela due colori attraverso la moltiplicazione
RGBA8 BlendMul( RGBA8 color0, RGBA8 color1 );


// Struttura di un tema
struct Theme {

	// Informazioni sui colori
	std::vector< RGBA8 > data;

	// Costruttori
	Theme() : data( 1, Make( 255, 255, 255, 255 ) ) { };
	Theme( const RGBA8 &color ) : data( 1, color ) { };
};

}; // Chiudo il namespace del colore

}; // Chiudo il namespace di VGE

#endif
