/* 
    Title --- slider.hpp

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


#ifndef VGE_SLIDER_HPP
#define VGE_SLIDER_HPP

#include <iostream>
#include <vector>
#include <cmath>

#include <sigc++/sigc++.h>

#include "vge/consts.hpp"
#include "vge/types.hpp"
#include "vge/error.hpp"
#include "vge/math.hpp"

#include "vge/color.hpp"

#include "vge/interfaces/i-image.hpp"
#include "vge/interfaces/i-orientable.hpp"
#include "vge/interfaces/i-range.hpp"

#include "vge/widgets/widget.hpp"
#include "vge/widgets/container.hpp"
#include "vge/widgets/button.hpp"

namespace VGE { // Namespace di VGE

namespace Gui { // Namespace dell'interfaccia grafica

class Slider : public Container, public InterfaceRange, public InterfaceColorable {

	/* SCORRITORE */

public:

	// Metodi costruttore e distruttore
	Slider( const Types::Size2D_u size_, Orientation orientation_ );
	virtual ~Slider();

	// Imposta il font
	virtual void SetFont( Font *font );
	// Ritorna il puntatore al font
	virtual Font *GetFont() const;

	// Imposta la frazione corrente
	virtual void SetFraction( Types::Float value );

	// Imposta la formattazione dell'etichetta
	virtual void SetLabelFormat( const wchar_t *format );
	// Ritorna la formattazione dell'etichetta
	virtual const wchar_t *GetLabelFormat() const;

	// Imposta la visibilità del righello
	virtual void SetRulerVisible( Types::Bool state );
	// Ritorna la visibilità del righello
	virtual Types::Bool GetRulerVisible() const;

	// Ritorna il pulsante della barra dello scorritore
	Button &GetBarButton();
	const Button &GetBarButton() const;

	// Invia un segnale allo scorritore
	virtual void SendSignal( Types::Int type, Entity *other );

	// Funzione di lavoro
	virtual void Update( Viewer *viewer, Player *player );

	// Disegna il righello dello scorritore
	virtual void DrawRuler( const Types::Point2D &offset, Color::RGBA8 blend ) const;

	// Disegna lo scorritore sullo schermo
	virtual void Draw( const Types::Point2D &offset, Color::RGBA8 blend ) const;


	/* SEGNALI */

	// Ritorna l'istanza del segnale di modifica della frazione
	sigc::signal< void, Types::Float, Types::Float, Slider * > &SignalChangeFraction();

protected:

	// Pulsante della barra dello scorritore
	Button bar_button;

	// Puntatore al font
	Font *t_font;

	// Formattazione dell'etichetta
	const wchar_t *label_format;

	// Flag di visibilità del righello
	Types::Bool ruler_visible;

	// Posizione del mouse al momento della pressione
	Types::Point2D mouse_pos;

	// Frazione prima della pressione
	Types::Float old_fraction;

	// Flag di scorrimento
	Types::Bool scrolling;

	// Aggiorna la dimensione del pulsante
	virtual void UpdateSize( const Types::Size2D_u &, Widget * );

	// Aggiorna il valore dello scorritore
	virtual void UpdateButton( Button *, Types::Bool pressed );

	// Legge l'input da tastiera
	virtual void ReadKeyboard();

	// Legge l'input dal joystick
	virtual void ReadJoystick();


	/* SEGNALI */

	// Segnale di modifica della frazione
	sigc::signal< void, Types::Float, Types::Float, Slider * > signal_change_fraction;
};

}; // Chiudo il namespace dell'interfaccia grafica

}; // Chiudo il namespace di VGE

#endif
