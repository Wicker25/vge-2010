/* 
    Title --- i-programmable.cpp

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


#ifndef VGE_INTERFACE_PROGRAMMABLE_CPP
#define VGE_INTERFACE_PROGRAMMABLE_CPP

#include "vge/interfaces/i-programmable.hpp"

#include "vge/color.hpp"
#include "vge/inline/color-inl.hpp"

#include "vge/entity.hpp"
#include "vge/inline/entity-inl.hpp"

#include "vge/input-manager.hpp"
#include "vge/inline/input-manager-inl.hpp"

#include "vge/interfaces/inline/i-programmable-inl.hpp"

namespace VGE { // Namespace di VGE

InterfaceProgrammable::InterfaceProgrammable() {

	// Disabilità la ciclicità degli eventi
	this->SetEventLoop( false );
}

InterfaceProgrammable::~InterfaceProgrammable() {

	// Libero la memoria
	while ( !this->event_list.empty() ) {

		// Ricavo il primo elemento della coda
		Event *event = this->event_list.front();

		// Elimino la struttura dell'evento
		free( event );

		// Elimino l'elemento dalla coda
		this->event_list.pop_front();
	}
}

void
InterfaceProgrammable::PopEvent( Event *event ) {

	// Controllo se la coda è ciclica 
	if ( this->GetEventLoop() && event->loop ) {

		// Ripristino i parametri
		event->arg0[0]	= event->arg0[1];
		event->arg1[0]	= event->arg1[1];
		event->arg2[0]	= event->arg2[1];
		event->arg3[0]	= event->arg3[1];
		event->arg4[0]	= event->arg4[1];

		event->color[2] = 0;

		// Rimetto in coda l'evento
		this->event_list.push_back( event );

	} else {

		// Elimino la struttura dell'evento
		free( event );
	}

	// Elimino l'elemento della prima posizione
	this->event_list.pop_front();
}

}; // Chiudo il namespace di VGE

#endif
