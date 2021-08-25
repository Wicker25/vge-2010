/* 
    Title --- character-maker.cpp

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


#ifndef VGE_CHARACTER_MAKER_CPP
#define VGE_CHARACTER_MAKER_CPP

#include "vge/character.hpp"

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

#include "vge/sprite.hpp"
#include "vge/inline/sprite-inl.hpp"

#include "vge/object.hpp"
#include "vge/inline/object-inl.hpp"

#include "vge/maker.hpp"
#include "vge/inline/maker-inl.hpp"

#include "vge/widgets/widget.hpp"
#include "vge/widgets/inline/widget-inl.hpp"

#include "vge/inline/character-inl.hpp"

namespace VGE { // Namespace di VGE

Character::Character( const Xml *node ): Object( node ) {

	// Imposto l'identificativo del tipo di entità
	this->SetMask( CHARACTER_MASK );

	/* Costruzione del personaggio */

	// Estraggo le caratteristiche dell'oggetto
	//this->ExtractObjFeatures( node );

	/* ======================= */

	// Invio il segnale di cambio della direzione
	this->SendSignal( SignalType::CHANGE_DIRECTION, NULL );

	// Metto il personaggio nello stato inattivo
	this->SetIdle();
}

}; // Chiudo il namespace di VGE

#endif
