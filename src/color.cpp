/* 
    Title --- color.cpp

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


#ifndef VGE_COLOR_CPP
#define VGE_COLOR_CPP

#include "vge/color.hpp"
#include "vge/inline/color-inl.hpp"

namespace VGE { // Namespace di VGE

namespace Color { // Namespace del colore

RGBA8
Make( Types::Uint8 red, Types::Uint8 green, Types::Uint8 blue, Types::Uint8 alpha ) {

	// Colore come intero senza segno a 32 bit
	RGBA8 color;

	// Converto il colore nella struttura complessa
	Struct *c_struct = ToStruct( color );

	// Copio i canali del colore
	c_struct->red	= red;
	c_struct->green	= green;
	c_struct->blue	= blue;
	c_struct->alpha	= alpha;

	// Ritorno il colore come intero senza segno a 32 bit
	return color;
}

RGBA8
BlendAlpha( RGBA8 color0, RGBA8 color1, Types::Float alpha ) {

	// Colore risultante dal blending
	Types::Uint32 color;

	// Controllo il valore dei canali alpha
	if ( alpha > 0.0f ) {

		// Converto il colore nella struttura complessa
		Struct *c_color		= ToStruct( color );
		Struct *c_color0	= ToStruct( color0 );
		Struct *c_color1	= ToStruct( color1 );

		// Calcolo il canale alpha contrario	
		Types::Float ialpha = ( 1.0f - alpha );

		// Calcolo il nuovo colore
		c_color->alpha	=	VMIN( c_color0->alpha + c_color1->alpha, 255 );

		c_color->red	=	(Types::Float) c_color0->red * alpha + \
							(Types::Float) c_color1->red * ialpha;

		c_color->green	=	(Types::Float) c_color0->green * alpha + \
							(Types::Float) c_color1->green * ialpha;

		c_color->blue	=	(Types::Float) c_color0->blue * alpha + \
							(Types::Float) c_color1->blue * ialpha;

	} else color = color1;

	// Ritorno il colore risultante dal blending
	return color;
}

RGBA8
BlendAvg( RGBA8 color0, RGBA8 color1 ) {

	// Colore risultante dal blending
	Types::Uint32 color;

	// Converto il colore nella struttura complessa
	Struct *c_color		= ToStruct( color );
	Struct *c_color0	= ToStruct( color0 );
	Struct *c_color1	= ToStruct( color1 );

	// Calcolo il nuovo colore
	c_color->alpha	=	( c_color0->alpha + c_color1->alpha ) / 2;
	c_color->red	=	( c_color0->red + c_color1->red ) / 2;
	c_color->green	=	( c_color0->green + c_color1->green ) / 2;
	c_color->blue	=	( c_color0->red + c_color1->blue ) / 2;

	// Ritorno il colore risultante dal blending
	return color;
}

RGBA8
BlendSum( RGBA8 color0, RGBA8 color1 ) {

	// Colore risultante dal blending
	Types::Uint32 color;

	// Converto il colore nella struttura complessa
	Struct *c_color		= ToStruct( color );
	Struct *c_color0	= ToStruct( color0 );
	Struct *c_color1	= ToStruct( color1 );

	// Calcolo il nuovo colore
	c_color->alpha	=	VMIN( ( c_color0->alpha + c_color1->alpha ), 255 );
	c_color->red	=	VMIN( ( c_color0->red + c_color1->red ), 255 );
	c_color->green	=	VMIN( ( c_color0->green + c_color1->green ), 255 );
	c_color->blue	=	VMIN( ( c_color0->red + c_color1->blue ), 255 );

	// Ritorno il colore risultante dal blending
	return color;
}

RGBA8
BlendMul( RGBA8 color0, RGBA8 color1 ) {

	// Colore risultante dal blending
	Types::Uint32 color;

	// Converto il colore nella struttura complessa
	Struct *c_color		= ToStruct( color );
	Struct *c_color0	= ToStruct( color0 );
	Struct *c_color1	= ToStruct( color1 );

	// Calcolo il nuovo colore
	c_color->alpha	=	( c_color0->alpha * ( (Types::Float) c_color1->alpha / 255.0f ) );
	c_color->red	=	( c_color0->red * ( (Types::Float) c_color1->red / 255.0f ) );
	c_color->green	=	( c_color0->green * ( (Types::Float) c_color1->green / 255.0f ) );
	c_color->blue	=	( c_color0->blue * ( (Types::Float) c_color1->blue / 255.0f ) );

	// Ritorno il colore risultante dal blending
	return color;
}

}; // Chiudo il namespace del colore

}; // Chiudo il namespace di VGE

#endif
