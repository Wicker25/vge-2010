/* 
    Title --- message-box-inl.hpp

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


#ifndef VGE_MESSAGE_BOX_INL_HPP
#define VGE_MESSAGE_BOX_INL_HPP

#include "vge/widgets/message-box.hpp"

namespace VGE { // Namespace di VGE

namespace Gui { // Namespace dell'interfaccia grafica

inline void
MessageBox::SetImage( Image *image, Types::Float x, Types::Float y ) {

	// Riconfiguro l'impacchettamento del widget nel contenitore
	this->container.SetChildPacking( 0, VGE::Gui::Container::PACKING_COLLAPSE, image, x, y );
}

inline void
MessageBox::SetImage( Image *image ) {

	// Riconfiguro l'impacchettamento del widget nel contenitore
	this->SetImage( image, 10.0f, 0.5f );
}

inline Image *
MessageBox::GetImage() const {

	// Ritorno il messaggio dell'oggetto
	return static_cast< Image * >( this->container.GetChildPacking( 0 ) );
}

inline TextBox &
MessageBox::GetTextBox() {

	// Ritorno il messaggio dell'oggetto
	return this->text_box;
}

inline const TextBox &
MessageBox::GetTextBox() const {

	// Ritorno il messaggio dell'oggetto
	return this->text_box;
}

}; // Chiudo il namespace dell'interfaccia grafica

}; // Chiudo il namespace di VGE

#endif
