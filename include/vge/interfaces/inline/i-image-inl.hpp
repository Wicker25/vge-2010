/* 
    Title --- i-image-inl.hpp

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


#ifndef VGE_INTERFACE_IMAGE_INL_HPP
#define VGE_INTERFACE_IMAGE_INL_HPP

#include "vge/interfaces/i-image.hpp"

namespace VGE { // Namespace di VGE

inline void
InterfaceImage::LoadImage( const std::string &path ) {

	// Carico l'immagine dal file
	this->LoadImage( path, Types::Size2D_u( 0, 0 ) );
}

inline const Types::Uint &
InterfaceImage::GetTextureId() const {

	// Ritorno l'id della texture
	return this->texture;
}

inline void
InterfaceImage::SetImageSize( const Types::Size2D_u &size_ ) {

	// Modifico la dimensione dell'immagine
	this->image_s = size_;
}

inline const Types::Size2D_u &
InterfaceImage::GetImageSize() const {

	// Ritorno la dimensione dell'immagine
	return this->image_s;
}

inline void
InterfaceImage::SetClipSize( const Types::Size2D_u &size_ ) {

	// Modifico la porzione dell'immagine
	this->clip = size_;
}

inline const Types::Size2D_u &
InterfaceImage::GetClipSize() const {

	// Ritorno la porzione dell'immagine
	return this->clip;
}

inline void
InterfaceImage::SetClipOffset( const Types::Size2D_u &offset_ ) {

	// Modifico l'offset dell'imagine
	this->offset = offset_;
}

inline const Types::Size2D_u &
InterfaceImage::GetClipOffset() const {

	// Ritorno l'offset dell'imagine
	return this->offset;
}

inline void
InterfaceImage::SetColorBlending( Types::Bool state = true ) {

	// Abilito/Disabilito il color blending per i toni ambientali
	this->color_blending = state;
}

inline Types::Bool
InterfaceImage::GetColorBlending() const {

	// Ritorno lo stato del color blending
	return this->color_blending;
}

inline void
InterfaceImage::DrawImage(	const Designer &designer, const Types::Point2D &position,
							const Types::Point2D &center, Color::RGBA8 blend ) const {

	// Disegno l'immagine sullo schermo
	designer.DrawImage( *this, position, center, blend, 255 );
}

inline void
InterfaceImage::DrawImage(	const Designer &designer, const Types::Point2D &position, const Types::Point2D &center,
							Color::RGBA8 blend, Types::Uint8 opacity ) const {

	// Disegno l'immagine sullo schermo
	designer.DrawImage( *this, position, center, blend, opacity );
}

}; // Chiudo il namespace di VGE

#endif
