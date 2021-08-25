/* 
    Title --- i-image.hpp

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


#ifndef VGE_INTERFACE_IMAGE_HPP
#define VGE_INTERFACE_IMAGE_HPP

#include <iostream>
#include <vector>
#include <list>
#include <cmath>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
//#include <SDL/SDL_opengl.h>
#include <GL/glew.h> 

#include "vge/consts.hpp"
#include "vge/types.hpp"
#include "vge/error.hpp"
#include "vge/math.hpp"

#include "vge/color.hpp"

#include "vge/designer.hpp"

#include "vge/interfaces/i-ruotable.hpp"
#include "vge/interfaces/i-scalable.hpp"
#include "vge/interfaces/i-colorable.hpp"

namespace VGE { // Namespace di VGE

// Adatta le dimensioni delle texture, convertendole in potenze di due
void SetPoTsize( Types::Uint *width, Types::Uint *height );

// Prototipi
class Image;

class InterfaceImage : public InterfaceRuotable, public InterfaceScalable, public InterfaceColorable {

	/* INTERFACCIA DELL'IMMAGINE */

public:

	// Metodi costruttore e distruttore
	InterfaceImage();
	InterfaceImage( const std::string &path );
	InterfaceImage( const std::string &path, const Types::Size2D_u &size_ );
	virtual ~InterfaceImage();

	// Carica l'immagine dal file
	virtual void LoadImage( const std::string &path );
	virtual void LoadImage( const std::string &path, const Types::Size2D_u &size_ );

	// Ritorna l'id della texture
	virtual const Types::Uint &GetTextureId() const;

	// Modifica la porzione dell'immagine
	virtual void SetClipSize( const Types::Size2D_u &size_ );
	// Ritorna la porzione dell'immagine
	virtual const Types::Size2D_u &GetClipSize() const;

	// Modifica la dimensione dell'immagine
	virtual void SetImageSize( const Types::Size2D_u &size_ );
	// Ritorna la dimensione dell'immagine
	virtual const Types::Size2D_u &GetImageSize() const;

	// Modifica l'offset della porzione di immagine
	virtual void SetClipOffset( const Types::Size2D_u &offset_ );
	// Ritorna l'offset della porzione di immagine
	virtual const Types::Size2D_u &GetClipOffset() const;

	// Abilita/Disabilita il color blending per i toni ambientali
	virtual void SetColorBlending( Types::Bool state );
	// Ritorna lo stato del color blending
	virtual Types::Bool GetColorBlending() const;

	// Disegna l'immagine sullo schermo
	virtual void DrawImage(	const Designer &designer, const Types::Point2D &position,
							const Types::Point2D &center, Color::RGBA8 blend ) const;

	virtual void DrawImage(	const Designer &designer, const Types::Point2D &position,
							const Types::Point2D &center, Color::RGBA8 blend, Types::Uint8 opacity ) const;

protected:

	// Sorgente dell'immagine
	std::string image_path;

	// Identificato della texture
	Types::Uint texture;

	// Dimensione dell'entità
	Types::Size2D_u clip;

	// Dimensione dell'immagine caricata
	Types::Size2D_u image_s;

	// Dimensione originale dell'immagine caricata
	Types::Size2D_u or_image_s;

	// Offset della porzione dell'immagine
	Types::Size2D_u offset;
};

}; // Chiudo il namespace di VGE

#endif
