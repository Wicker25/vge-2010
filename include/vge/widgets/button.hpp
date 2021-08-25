/* 
    Title --- button.hpp

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


#ifndef VGE_BUTTON_HPP
#define VGE_BUTTON_HPP

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
#include "vge/interfaces/i-margins.hpp"

#include "vge/widgets/widget.hpp"
#include "vge/widgets/container.hpp"

namespace VGE { // Namespace di VGE

namespace SignalType { // Namespace del tipo di segnale

// Tipo del segnale
enum {

	BUTTON_PRESSED = 1050,	// SEGNALE DI PRESSIONE DEL PULSANTE
	BUTTON_RELEASED,		// SEGNALE DI RILASCIO DEL PULSANTE
};

}; // Chiudo il namespace del tipo di segnale

namespace Gui { // Namespace dell'interfaccia grafica

class Button : public Container, public InterfaceMargins {

	/* PULSANTE GENERICO */

public:

	// Metodi costruttore e distruttore
	Button();
	Button( const Types::Size2D_u size_ );
	virtual ~Button();

	// Imposta lo stato del pulsante
	void SetPressed( Types::Bool state );
	// Ritorna lo stato del pulsante
	Types::Bool GetPressed() const;

	// Invia un segnale all'oggetto
	virtual void SendSignal( Types::Int type, Entity *other );

	// Funzione di lavoro
	virtual void Update( Viewer *viewer, Player *player );


	/* SEGNALI */

	// Ritorna l'istanza del segnale di pressione
	sigc::signal< void, Button * > &SignalPressed();

	// Ritorna l'istanza del segnale di rilascio
	sigc::signal< void, Button * > &SignalReleased();

protected:

	// Stato del pulsante
	Types::Bool pressed;

	/* SEGNALI */


	// Segnale di pressione del pulsante
	sigc::signal< void, Button * > signal_pressed;

	// Segnale di rilascio del pulsante
	sigc::signal< void, Button * > signal_released;
};

}; // Chiudo il namespace dell'interfaccia grafica

}; // Chiudo il namespace di VGE

#endif
