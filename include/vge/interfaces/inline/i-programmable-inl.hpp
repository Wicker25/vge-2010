/* 
    Title --- i-programmable-inl.hpp

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


#ifndef VGE_INTERFACE_PROGRAMMABLE_INL_HPP
#define VGE_INTERFACE_PROGRAMMABLE_INL_HPP

#include "vge/interfaces/i-programmable.hpp"

namespace VGE { // Namespace di VGE

inline void
InterfaceProgrammable::AddEvent( Types::Int type ) {

	// Aggiungo l'evento alla coda
	this->AddEvent( type, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f );
}

inline void
InterfaceProgrammable::AddEvent( Types::Int type, Types::Int arg0 ) {

	// Aggiungo l'evento alla coda
	this->AddEvent( type, (Types::Float) arg0, 0.0f, 0.0f, 0.0f, 0.0f );
}

inline void
InterfaceProgrammable::AddEvent( Types::Int type, Types::Float arg0 ) {

	// Aggiungo l'evento alla coda
	this->AddEvent( type, arg0, 0.0f, 0.0f, 0.0f, 0.0f );
}

inline void
InterfaceProgrammable::AddEvent( Types::Int type, Types::Float arg0, Types::Float arg1 ) {

	// Aggiungo l'evento alla coda
	this->AddEvent( type, arg0, arg1, 0.0f, 0.0f, 0.0f );
}

inline void
InterfaceProgrammable::AddEvent(	Types::Int type, Types::Float arg0,
									Types::Float arg1, Types::Float arg2 ) {

	// Aggiungo l'evento alla coda
	this->AddEvent( type, arg0, arg1, 0.0f, 0.0f, 0.0f );
}

inline void
InterfaceProgrammable::AddEvent(	Types::Int type, Types::Float arg0, Types::Float arg1,
									Types::Float arg2, Types::Float arg3 ) {

	// Aggiungo l'evento alla coda
	this->AddEvent( type, arg0, arg1, arg2, arg3, 0.0f );
}

inline void
InterfaceProgrammable::AddEvent(	Types::Int type, Types::Float arg0, Types::Float arg1,
									Types::Float arg2, Types::Float arg3, Types::Float arg4 ) {

	// Creo la struttura del nuovo evento
	Event *new_event = this->PushEvent( type, true );

	// Copio i parametri
	new_event->arg0[0]	= arg0;
	new_event->arg0[1]	= arg0;

	new_event->arg1[0]	= arg1;
	new_event->arg1[1]	= arg1;

	new_event->arg2[0]	= arg2;
	new_event->arg2[1]	= arg2;

	new_event->arg3[0]	= arg3;
	new_event->arg3[1]	= arg3;

	new_event->arg4[0]	= arg4;
	new_event->arg4[1]	= arg4;
}

inline void
InterfaceProgrammable::AddEvent( Types::Int type, Color::RGBA8 color ) {

	// Aggiungo l'evento alla coda
	this->AddEvent( type, color, 0, 0.0f );
}

inline void
InterfaceProgrammable::AddEvent( Types::Int type, Color::RGBA8 color0, Color::RGBA8 color1 ) {

	// Aggiungo l'evento alla coda
	this->AddEvent( type, color0, color1, 0.0f );
}

inline void
InterfaceProgrammable::AddEvent( Types::Int type, Color::RGBA8 color0, Color::RGBA8 color1, Types::Float arg0 ) {

	// Creo la struttura del nuovo evento
	Event *new_event = this->PushEvent( type, true );

	// Copio i parametri
	new_event->color[0] = color0;
	new_event->color[1] = color1;
	new_event->color[2] = 0;

	new_event->arg0[0]	= arg0;
	new_event->arg0[1]	= arg0;
}

inline void
InterfaceProgrammable::AddEvent( Types::Int type, Color::RGBA8 color, Types::Float arg0 ) {

	// Creo la struttura del nuovo evento
	Event *new_event = this->PushEvent( type, true );

	// Copio i parametri
	new_event->color[0] = color;
	new_event->color[1] = 0;
	new_event->color[2] = 0;

	new_event->arg0[0]	= arg0;
	new_event->arg0[1]	= arg0;
}

inline void
InterfaceProgrammable::AddEvent( Types::Int type, const std::wstring &string ) {

	// Creo la struttura del nuovo evento
	Event *new_event = this->PushEvent( type, true );

	// Copio i parametri
	new_event->string = string;
}

inline void
InterfaceProgrammable::AddEvent( Types::Int type, Entity *entity ) {

	// Creo la struttura del nuovo evento
	Event *new_event = this->PushEvent( type, true );

	// Copio i parametri
	new_event->entity = entity;
}

inline Event *
InterfaceProgrammable::PushEvent( Types::Int type, Types::Bool loop ) {

	// Creo la struttura del nuovo evento
	Event *new_event = (Event *) new Event;

	// Inizializzo la struttura
	new_event->type = type;
	new_event->loop = loop;

	// Aggiungo un evento alla coda
	this->event_list.push_back( new_event );

	return new_event;
}

inline Event *
InterfaceProgrammable::InserEvent( Types::Int type, Types::Bool loop, Types::Uint index = 0 ) {

	// Creo la struttura del nuovo evento
	Event *new_event = (Event *) new Event;

	// Inizializzo la struttura
	new_event->type = type;
	new_event->loop = loop;

	// Iteratore
	EventList::iterator iter = this->event_list.begin();

	// Mi sposto alla posizione desiderata
	while ( index-- ) iter++;

	// Aggiungo un evento alla coda
	this->event_list.insert( iter, new_event );

	return new_event;
}

inline void
InterfaceProgrammable::SetEventLoop( Types::Bool state ) {

	// Rende ciclica la coda degli eventi
	this->event_loop = state;
}

inline Types::Bool
InterfaceProgrammable::GetEventLoop() const {

	// Controlla se la coda degli eventi è ciclica
	return this->event_loop;
}

inline const EventList &
InterfaceProgrammable::GetEventList() const {

	// Ritorno la lista degli eventi
	return this->event_list;
}

inline Types::Uint
InterfaceProgrammable::GetEventNumber() const {

	// Ritorno il numero degli eventi
	return (Types::Uint) this->event_list.size();
}

}; // Chiudo il namespace di VGE

#endif
