/* 
    Title --- sprite-maker.cpp

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


#ifndef VGE_SPRITE_MAKER_CPP
#define VGE_SPRITE_MAKER_CPP

#include "vge/sprite.hpp"

#include "vge/utf8.hpp"
#include "vge/inline/utf8-inl.hpp"

#include "vge/xml.hpp"
#include "vge/inline/xml-inl.hpp"

#include "vge/interfaces/i-programmable.hpp"
#include "vge/interfaces/inline/i-programmable-inl.hpp"

#include "vge/entity.hpp"
#include "vge/inline/entity-inl.hpp"

#include "vge/image.hpp"
#include "vge/inline/image-inl.hpp"

#include "vge/maker.hpp"
#include "vge/inline/maker-inl.hpp"

#include "vge/widgets/widget.hpp"
#include "vge/widgets/inline/widget-inl.hpp"

#include "vge/inline/sprite-inl.hpp"

namespace VGE { // Namespace di VGE

Sprite::Sprite( const Xml *node ): Image( node ) {

	// Imposto l'identificativo del tipo di entità
	this->SetMask( SPRITE_MASK );

	/* Costruzione dello sprite */

	// Estraggo l'area di collisione dello sprite
	this->ExtractCollisionArea( node );

	/* ======================= */

	// Memorizzo la posizione
	this->StorePosition( true, true, false );

	// Imposto i flags predefiniti dello sprite
	this->SetSolid( true );
}

/*
	<carea>

		<vertex coord="-40,-120" />
		<vertex coord="-40,30" />
		... ... ... ...

	</carea>
*/

void
Sprite::ExtractCollisionArea( const Xml *node ) {

	// Estraggo l'area di collisione dello sprite
	Maker::ExtractBoundingArea( node, T_CAREA, &this->GetCollisionArea() );
}

void
Sprite::ExtractEvent( const Xml *node, const wchar_t *type, std::vector< wchar_t *> &values ) {

	// Chiama la funzione della classe genitore
	Image::ExtractEvent( node, type, values );

	// Attesa di collisione
	if ( wcscasecmp( type, V_EVENT_WAIT_COLLISION ) == 0 ) {

		// Aggiungo l'evento alla lista
		this->AddEvent( EventType::WAIT_COLLISION );

	// Attesa di interazione
	} else if ( wcscasecmp( type, V_EVENT_WAIT_INTERACTION ) == 0 ) {

		// Aggiungo l'evento alla lista
		this->AddEvent( EventType::WAIT_INTERACTION );
	}
}

void
Sprite::WriteBoundingArea( Utf8 *stream ) const {

	// Chiamo la funzione della classe genitore
	Entity::WriteBoundingArea( stream );

	// Ricavo l'area di visibilità
	const Types::Point2DList &list = this->GetCollisionArea().GetVertices();

	// Apro il tag dell'area di visibilità
	stream->Write( L"\t<%ls>\n\n", T_CAREA );

	// Scrivo i vertici dell'are
	for ( Types::Uint i = 0; i < list.size(); i++ )
		stream->Write( L"\t\t<%ls %ls=\"%.2f,%.2f\" />\n", T_VERTEX, A_COORDS, list[i].x, list[i].y );

	// Chiudo il tag dell'area di visibilità
	stream->Write( L"\n\t</%ls>\n\n", T_CAREA );
}

}; // Chiudo il namespace di VGE

#endif
