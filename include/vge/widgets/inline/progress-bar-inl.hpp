/* 
    Title --- progress-bar-inl.hpp

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


#ifndef VGE_PROGRESS_BAR_INL_HPP
#define VGE_PROGRESS_BAR_INL_HPP

#include "vge/widgets/progress-bar.hpp"

namespace VGE { // Namespace di VGE

namespace Gui { // Namespace dell'interfaccia grafica

inline void
ProgressBar::SetFraction( Types::Float value ) {

	// Imposto la frazione di completamento
	InterfaceRange::SetFraction( value );

	// Invia il segnale di modifica della frazione
	this->SendSignal( SignalType::CHANGE_FRACTION, NULL );

	// Imposto il flag di aggiornamento
	this->update = true;
}

inline void
ProgressBar::SetBarColor( Color::RGBA8 value ) {

	// Imposto il colore della barra del progresso
	this->bar_color = value;
}

inline Color::RGBA8
ProgressBar::GetBarColor() const {

	// Ritorna il colore della barra del progresso
	return this->bar_color;
}

inline void
ProgressBar::SetLabelFormat( const wchar_t *format ) {

	// Imposto la formattazione dell'etichetta
	this->label_format = format;
}

inline const wchar_t *
ProgressBar::GetLabelFormat() const {

	// Ritorno la formattazione dell'etichetta
	return this->label_format;
}

inline Label &
ProgressBar::GetLabel() {

	// Ritorno l'etichetta della barra del caricamento
	return this->label;
}

inline const Label &
ProgressBar::GetLabel() const {

	// Ritorno l'etichetta della barra del caricamento
	return this->label;
}

inline sigc::signal< void, Types::Float, Types::Float, ProgressBar * > &
ProgressBar::SignalChangeFraction() {

	// Ritorno l'istanza del segnale di modifica della frazione
	return this->signal_change_fraction;
}

}; // Chiudo il namespace dell'interfaccia grafica

}; // Chiudo il namespace di VGE

#endif
