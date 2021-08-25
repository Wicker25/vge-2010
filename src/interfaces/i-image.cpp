/* 
    Title --- i-image.cpp

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


#ifndef VGE_INTERFACE_IMAGE_CPP
#define VGE_INTERFACE_IMAGE_CPP

#include "vge/interfaces/i-image.hpp"

#include "vge/color.hpp"
#include "vge/inline/color-inl.hpp"

#include "vge/interfaces/i-ruotable.hpp"
#include "vge/interfaces/inline/i-ruotable-inl.hpp"

#include "vge/interfaces/i-scalable.hpp"
#include "vge/interfaces/inline/i-scalable-inl.hpp"

#include "vge/interfaces/i-colorable.hpp"
#include "vge/interfaces/inline/i-colorable-inl.hpp"

#include "vge/image.hpp"
#include "vge/inline/image-inl.hpp"

#include "vge/interfaces/inline/i-image-inl.hpp"

namespace VGE { // Namespace di VGE

void
SetPoTsize( Types::Uint *width, Types::Uint *height ) {

	// Parte intera
	double integral;

	// Ricavo il logaritmo delle dimensioni
	double log_w = log2( (double) *width );
	double log_h = log2( (double) *height );

	// Mi assicuro che siano entrambe potenze di due
	if ( modf( log_w, &integral ) > 0.0f )
		*width = pow( 2.0F, ceil( log_w ) );

	if ( modf( log_h, &integral ) > 0.0f )
		*height = pow( 2.0F, ceil( log_h ) );
}

InterfaceImage::InterfaceImage() {

	// Inizializzo le strutture di lavoro
	this->texture = 0;

	// Scelgo l'offset della porzione dell'immagine
	this->SetClipOffset( Types::Size2D_u( 0, 0 ) );
}

InterfaceImage::InterfaceImage( const std::string &path ) {

	// Inizializzo le strutture di lavoro
	this->texture = 0;

	// Scelgo l'offset della porzione dell'immagine
	this->SetClipOffset( Types::Size2D_u( 0, 0 ) );

	// Carico l'immagine in memoria
	if ( !path.empty() ) this->LoadImage( path );
}

InterfaceImage::InterfaceImage( const std::string &path, const Types::Size2D_u &size_ ) {

	// Inizializzo le strutture di lavoro
	this->texture = 0;

	// Scelgo l'offset della porzione dell'immagine
	this->SetClipOffset( Types::Size2D_u( 0, 0 ) );

	// Carico l'immagine in memoria
	if ( !path.empty() ) this->LoadImage( path, size_ );
}

InterfaceImage::~InterfaceImage() {

	// Libero la memoria
	glDeleteTextures( 1, &this->texture );
}

void
InterfaceImage::LoadImage( const std::string &path, const Types::Size2D_u &size_ ) {

	// Carico l'immagine
	SDL_Surface *image = IMG_Load( path.c_str() );

	// Memorizzo il sorgente dell'immagine
	this->image_path = path;

	// Verifico che sia stata caricata senza errori
	if ( image == NULL ) {

		fprintf( stderr, CANNOT_OPEN_FILE, FATAL, path.c_str() );
		return;
	}

	// Memorizzo le dimensioni originali dell'immagine
	this->or_image_s.w = image->w;
	this->or_image_s.h = image->h;

	// Memorizzo la dimensione dell'immagine
	this->SetImageSize( Types::Size2D_u( image->w, image->h ) );

	// Corregge la dimensione dell'immagine
	SetPoTsize( &this->image_s.w, &this->image_s.h );

	// Scelgo la porzione dell'immagine
	if ( size_.w && size_.h )

		this->SetClipSize( size_ );
	else
		this->SetClipSize( Types::Size2D_u( image->w, image->h ) );

	// Scelgo la struttura dei dati
	glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
	glGenTextures( 1, &this->texture );
	glBindTexture( GL_TEXTURE_2D, this->texture );

	// Genero la texture
	if ( image->format->Amask ) {

		glTexImage2D(	GL_TEXTURE_2D, 0, 4, this->image_s.w, this->image_s.h, 0,
						GL_RGBA, GL_UNSIGNED_BYTE, NULL );

		glTexSubImage2D(	GL_TEXTURE_2D, 0, 0, 0, image->w, image->h,
							GL_RGBA, GL_UNSIGNED_BYTE, image->pixels );

	} else {

		glTexImage2D(	GL_TEXTURE_2D, 0, 4, this->image_s.w, this->image_s.h, 0,
						GL_RGBA, GL_UNSIGNED_BYTE, NULL );

		glTexSubImage2D(	GL_TEXTURE_2D, 0, 0, 0, image->w, image->h,
							GL_RGB, GL_UNSIGNED_BYTE, image->pixels );
	}

	// Libero la memoria
	SDL_FreeSurface( image );
}

}; // Chiudo il namespace di VGE

#endif
