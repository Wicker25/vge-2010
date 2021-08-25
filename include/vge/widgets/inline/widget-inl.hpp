/* 
    Title --- widget-inl.hpp

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


#ifndef VGE_WIDGET_INL_HPP
#define VGE_WIDGET_INL_HPP

#include "vge/widgets/widget.hpp"

namespace VGE { // Namespace di VGE

namespace Gui { // Namespace dell'interfaccia grafica

inline void
Widget::SetContainer( Container *container ) {

	// Collego il widget ad un contenitore
	this->parent_container = container;
}

inline Container *
Widget::GetContainer() const {

	// Ritorno il puntatore al contenitore
	return this->parent_container;
}

inline void
Widget::SetSize( const Types::Size2D_u &size_ ) {

	// Modifico la dimensione del widget
	InterfaceResizable::SetSize( size_ );

	// Invia il segnale di ridimensionamento
	this->SendSignal( SignalType::RESIZING, NULL );
}

inline void
Widget::SetOpacity( Types::Uint8 value ) {

	// Imposto l'opacità del widget
	this->opacity = value;
}

inline Types::Uint8
Widget::GetOpacity() const {

	// Ritorno l'opacità del widget
	return this->opacity * (Types::Uint8) this->GetVisible();
}

inline void
Widget::SetFocusable( Types::Bool state ) {

	// Abilito/disabilito la capacità di prendere il focus
	this->focusable = state;
}

inline Types::Bool
Widget::GetFocusable() const {

	// Ritorno la capacità di prendere il focus
	return this->focusable;
}

inline sigc::signal< void, const Types::Size2D_u &, Widget * > &
Widget::SignalResizing() {

	// Ritorno l'istanza del segnale di ridimensionamento
	return this->signal_resizing;
}

inline sigc::signal< void, Types::Bool, Widget * > &
Widget::SignalFocus() {

	// Ritorno l'istanza del segnale di cambio del focus
	return this->signal_focus;
}

}; // Chiudo il namespace dell'interfaccia grafica

}; // Chiudo il namespace di VGE

#endif
