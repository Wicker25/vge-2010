/* 
    Title --- slider-inl.hpp

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


#ifndef VGE_SLIDER_INL_HPP
#define VGE_SLIDER_INL_HPP

#include "vge/widgets/slider.hpp"

namespace VGE { // Namespace di VGE

namespace Gui { // Namespace dell'interfaccia grafica

inline void
Slider::SetFont( Font *font ) {

	// Imposto il font
	this->t_font = font;
}

inline Font *
Slider::GetFont() const {

	// Ritorno il puntatore al font
	return ( this->t_font != NULL ) ? this->t_font : Global::GetFont( SYS_FONT_NORMAL );
}

inline void
Slider::SetLabelFormat( const wchar_t *format ) {

	// Imposto la formattazione dell'etichetta
	this->label_format = format;
}

inline const wchar_t *
Slider::GetLabelFormat() const {

	// Ritorno la formattazione dell'etichetta
	return this->label_format;
}

inline void
Slider::SetRulerVisible( Types::Bool state ) {

	// Imposto la visibilità del righello
	this->ruler_visible = state;
}

inline Types::Bool
Slider::GetRulerVisible() const {

	// Ritorno la visibilità del righello
	return this->ruler_visible;
}

inline Button &
Slider::GetBarButton() {

	// Ritorno il pulsante della barra dello scorritore
	return this->bar_button;
}

inline const Button &
Slider::GetBarButton() const {

	// Ritorno il pulsante della barra dello scorritore
	return this->bar_button;
}

inline sigc::signal< void, Types::Float, Types::Float, Slider * > &
Slider::SignalChangeFraction() {

	// Ritorno l'istanza del segnale di modifica della frazione
	return this->signal_change_fraction;
}

}; // Chiudo il namespace dell'interfaccia grafica

}; // Chiudo il namespace di VGE

#endif
