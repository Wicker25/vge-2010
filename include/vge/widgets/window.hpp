/* 
    Title --- window.hpp

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


#ifndef VGE_WINDOW_HPP
#define VGE_WINDOW_HPP

#include <iostream>
#include <cmath>

#include "vge/consts.hpp"
#include "vge/types.hpp"
#include "vge/error.hpp"
#include "vge/math.hpp"

#include "vge/color.hpp"

#include "vge/entity.hpp"

#include "vge/widgets/label.hpp"
#include "vge/widgets/container.hpp"

namespace VGE { // Namespace di VGE

namespace EventType { // Namespace del tipo dell'evento

// Tipo dell'evento
enum {

	FADING_IN = 1250,	// APPARIZIONE CON DISSOLVENZA
	FADING_OUT,			// SCOMPARSA CON DISSOLVENZA
};

}; // Chiudo il namespace del tipo dell'evento

namespace Gui { // Namespace dell'interfaccia grafica

class Window : public Container {

	/* FINESTRA */

public:

	// Metodi costruttore e distruttore
	Window( const Types::Size2D_u &size_ );
	Window( const std::wstring &title, const Types::Size2D_u &size_ );
	virtual ~Window();

	// Ritorna il titolo della finestra
	Label &GetTitle();
	const Label &GetTitle() const;

	// Invia un segnale all'oggetto
	virtual void SendSignal( Types::Int type, Entity *other );

	// Avvia un evento dell'oggetto
	virtual Types::Bool SendEvent( Event *event, Entity *other );

	// Disegna la finestra
	virtual void Draw( const Types::Point2D &offset, Color::RGBA8 blend ) const;

protected:

	// Titolo della finestra
	Label l_title;
};

}; // Chiudo il namespace dell'interfaccia grafica

}; // Chiudo il namespace di VGE

#endif
