/* 
    Title --- widget-maker.cpp

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


#ifndef VGE_WIDGET_MAKER_CPP
#define VGE_WIDGET_MAKER_CPP

#include "vge/widgets/widget.hpp"

#include "vge/utf8.hpp"
#include "vge/inline/utf8-inl.hpp"

#include "vge/xml.hpp"
#include "vge/inline/xml-inl.hpp"

#include "vge/interfaces/i-programmable.hpp"
#include "vge/interfaces/inline/i-programmable-inl.hpp"

#include "vge/entity.hpp"
#include "vge/inline/entity-inl.hpp"

#include "vge/maker.hpp"
#include "vge/inline/maker-inl.hpp"

#include "vge/widgets/inline/widget-inl.hpp"

namespace VGE { // Namespace di VGE

namespace Gui { // Namespace dell'interfaccia grafica

Widget::Widget( const Xml *node ) : Entity( node ) {

	// Imposto l'identificativo del tipo di entità
	this->SetMask( WIDGET_MASK );

	// Collego il widget ad un contenitore
	this->SetContainer( NULL );

	// Imposto l'opacità del widget
	this->SetOpacity( 255 );
}

void
Widget::ExtractEvent( const Xml *node, const wchar_t *type, std::vector< wchar_t *> &values ) {

	// Chiama la funzione della classe genitore
	Entity::ExtractEvent( node, type, values );
}

void
Widget::WriteInfo( Utf8 *stream ) const {

	// Scrivo le informazioni dell'entità padre
	Entity::WriteInfo( stream );
}

}; // Chiudo il namespace dell'interfaccia grafica

}; // Chiudo il namespace di VGE

#endif
