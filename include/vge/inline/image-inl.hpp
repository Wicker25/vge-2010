/* 
    Title --- image-inl.hpp

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


#ifndef VGE_IMAGE_INL_HPP
#define VGE_IMAGE_INL_HPP

#include "vge/image.hpp"

namespace VGE { // Namespace di VGE

inline void
Image::LoadImage( const std::string &path, const Types::Size2D_u &size_ ) {

	// Carica l'immagine del file
	InterfaceImage::LoadImage( path, size_ );

	// Imposto l'area di visibilità rettangolare
	if ( this->automatic_varea )
		this->GetVisibilityArea().SetRectangle( this->clip, this->center );
}

inline void
Image::LoadImage( const std::string &path ) {

	// Carico l'immagine dal file
	this->LoadImage( path, Types::Size2D_u( 0, 0 ) );
}

inline void
Image::SetSize( const Types::Size2D_u &size_ ) {

	// Modifico la dimensione del contenitore tenendo conto della scala
	this->SetScale( Types::Size2D_f( size_ ) / Types::Size2D_f( this->clip ) );
}

inline Types::Size2D_u
Image::GetSize() const {

	// Modifica i valori in base alla scala
	return Types::Size2D_u(	this->GetClipSize().w * this->GetScale().w,
							this->GetClipSize().h * this->GetScale().h );
}

inline void
Image::SetCenter( const Types::Point2D &point ) {

	// Modifico il centro dell'entità
	this->center = point;

	// Imposto l'area di visibilità rettangolare
	if ( this->automatic_varea )
		this->GetVisibilityArea().SetRectangle( this->clip, this->center );
}

inline void
Image::SetClipSize( const Types::Size2D_u &size_ ) {

	InterfaceImage::SetClipSize( size_ );

	// Imposto l'area di visibilità rettangolare
	if ( this->automatic_varea )
		this->GetVisibilityArea().SetRectangle( this->clip, this->center );
}

inline void
Image::SetScale( const Types::Size2D_f &scale_ ) {

	// Modifico la proporzione
	InterfaceScalable::SetScale( scale_ );

	// Invia il segnale di modifica della scala
	this->SendSignal( SignalType::SCALING, NULL );
}

inline void
Image::SetRotation( Types::Float value ) {

	// Modifico l'angolo di rotazione dell'immagine
	InterfaceRuotable::SetRotation( value );

	// Invia il segnale di rotazione
	this->SendSignal( SignalType::ROTATION, NULL );
}

inline sigc::signal< void, Types::Size2D_f, Image * > &
Image::SignalScaling() {

	// Ritorno l'istanza del segnale di modifica della scala
	return this->signal_scaling;
}

inline sigc::signal< void, Types::Float, Image * > &
Image::SignalRotation() {

	// Ritorno l'istanza del segnale di rotazione
	return this->signal_rotation;
}

}; // Chiudo il namespace di VGE

#endif
