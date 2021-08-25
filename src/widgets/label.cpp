/* 
    Title --- label.cpp

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


#ifndef VGE_LABEL_CPP
#define VGE_LABEL_CPP

#include "vge/widgets/label.hpp"

#include "vge/interfaces/i-resizable.hpp"
#include "vge/interfaces/inline/i-resizable-inl.hpp"

#include "vge/interfaces/i-colorable.hpp"
#include "vge/interfaces/inline/i-colorable-inl.hpp"

#include "vge/entity.hpp"
#include "vge/inline/entity-inl.hpp"

#include "vge/engine.hpp"
#include "vge/inline/engine-inl.hpp"

#include "vge/widgets/box.hpp"
#include "vge/widgets/inline/box-inl.hpp"

#include "vge/widgets/font.hpp"
#include "vge/widgets/inline/font-inl.hpp"

#include "vge/widgets/widget.hpp"
#include "vge/widgets/inline/widget-inl.hpp"

#include "vge/widgets/frame.hpp"
#include "vge/widgets/inline/frame-inl.hpp"

#include "vge/widgets/inline/label-inl.hpp"

namespace VGE { // Namespace di VGE

namespace Gui { // Namespace dell'interfaccia grafica

Label::Label( const std::wstring &string ) : Frame( Types::Point3D( 0.0f, 0.0f, 0.0f ) ) {

	// Imposto il font
	this->SetFont( NULL );

	// Imposto la stringa
	this->SetString( string );

	// Imposto il colore dell'etichetta
	this->SetColor( Color::Make( 255, 255, 255, 255 ) );

	// Imposto il flag di aggiornamento
	this->update = true;
}

Label::Label( const std::wstring &string, Font *font ) : Frame( Types::Point3D( 0.0f, 0.0f, 0.0f ) ) {

	// Imposto il font
	this->SetFont( font );

	// Imposto la stringa
	this->SetString( string );

	// Imposto il colore dell'etichetta
	this->SetColor( Color::Make( 255, 255, 255, 255 ) );

	// Imposto il flag di aggiornamento
	this->update = true;
}

Label::~Label() {

}

void
Label::Update( Viewer *viewer, Player *player ) {

	// Avvio la funzione di lavoro superiore
	Frame::Update( viewer, player );

	// Controllo se è abilitato il flag di aggiornamento
	if ( this->update ) {

		// Aggiorno le dimensioni del widget
		this->SetSize( Types::Size2D_u( this->GetFont()->GetStringWidth( this->GetString() ),
										this->GetFont()->GetClipSize().h ) );

		// Disabilito il flag di aggiornamento
		this->update = false;
	}
}

void
Label::Draw( const Types::Point2D &offset, Color::RGBA8 blend ) const {

	// Funzione di disegno del testo
	Frame::Draw( offset, blend );

	// Controllo che il testo sia realmente visibile
	if ( ( this->GetFont() != NULL && !this->GetString().empty() ) && this->GetOpacity() > 0 ) {

		// Imposto il colore
		this->GetFont()->SetColor( this->GetColor() );

		// Disegno l'etichetta
		this->GetFont()->Draw(	this->GetEngine()->GetDesigner(), this->GetString(),
								this->GetPosition() + offset, blend );
	}
}

}; // Chiudo il namespace dell'interfaccia grafica

}; // Chiudo il namespace di VGE

#endif
