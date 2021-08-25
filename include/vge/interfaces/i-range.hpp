/* 
    Title --- i-range.hpp

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


#ifndef VGE_INTERFACE_RANGE_HPP
#define VGE_INTERFACE_RANGE_HPP

#include <iostream>
#include <list>

#include "vge/consts.hpp"
#include "vge/types.hpp"
#include "vge/error.hpp"
#include "vge/math.hpp"

namespace VGE { // Namespace di VGE

namespace SignalType { // Namespace del tipo di segnale

// Tipo del segnale
enum {

	CHANGE_FRACTION = 250,	// SEGNALE DI MODIFICA DELLA FRAZIONE
};

}; // Chiudo il namespace del tipo di segnale

class InterfaceRange {

	/* INTERFACCIA CON UN INTERVALLO DI VALORI */

public:

	// Metodi costruttore e distruttore
	InterfaceRange();
	InterfaceRange( const Types::Size2D_f &range_ );
	virtual ~InterfaceRange();

	// Imposto l'intervallo di valori
	virtual void SetRange( const Types::Size2D_f &range_ );
	// Ritorna l'intervallo di valori
	virtual Types::Size2D_f GetRange() const;

	// Imposta la frazione corrente
	virtual void SetFraction( Types::Float value );
	// Ritorna la frazione corrente
	virtual Types::Float GetFraction() const;

	// Imposto il valore corrente
	virtual void SetValue( Types::Float value );
	// Ritorna il valore corrente
	virtual Types::Float GetValue() const;

	// Imposta il valore del passo
	virtual void SetStep( Types::Float value );
	// Ritorna il valore del passo
	virtual Types::Float GetStep() const;

protected:

	// Intervallo di valori
	Types::Size2D_f range;

	// Frazione di completamento
	Types::Float fraction;

	// Valore del passo
	Types::Float step;
};

}; // Chiudo il namespace di VGE

#endif
