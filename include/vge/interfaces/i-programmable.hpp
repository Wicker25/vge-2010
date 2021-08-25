/* 
    Title --- i-programmable.hpp

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


#ifndef VGE_INTERFACE_PROGRAMMABLE_HPP
#define VGE_INTERFACE_PROGRAMMABLE_HPP

#include <iostream>
#include <list>

#include <sigc++/sigc++.h>

#include "vge/consts.hpp"
#include "vge/types.hpp"
#include "vge/math.hpp"

#include "vge/color.hpp"

#include "vge/input-manager.hpp"

namespace VGE { // Namespace di VGE

// Prototipi
class Entity;

// Struttura di un evento
typedef struct {

	Types::Int type;	// Tipo dell'evento

	Types::Float arg0[2];	// Primo parametro numerico
	Types::Float arg1[2];	// Secondo parametro numerico
	Types::Float arg2[2];	// Terzo parametro numerico
	Types::Float arg3[2];	// Quarto parametro numerico
	Types::Float arg4[2];	// Quinto parametro numerico

	Color::RGBA8 color[3];	// Parametro colore

	std::wstring string;	// Parametro stringa

	Entity *entity;	// Parametro "entità"

	Types::Bool loop;	// Flag di ciclicità

} Event;

// Ridefinizione del tipo lista
typedef std::list< Event * > EventList;

class InterfaceProgrammable {

	/* INTERFACCIA PROGRAMMABILE */

public:

	// Metodi costruttore e distruttore
	InterfaceProgrammable();
	virtual ~InterfaceProgrammable();

	// Invia un segnale all'oggetto
	virtual void SendSignal( Types::Int type, Entity *This ) = 0;

	// Aggiunge un evento alla coda
	void AddEvent( Types::Int type );
	void AddEvent( Types::Int type, Types::Int arg0 );
	void AddEvent( Types::Int type, Types::Float arg0 );
	void AddEvent( Types::Int type, Types::Float arg0, Types::Float arg1 );
	void AddEvent( Types::Int type, Types::Float arg0, Types::Float arg1, Types::Float arg2 );
	void AddEvent(	Types::Int type, Types::Float arg0, Types::Float arg1,
					Types::Float arg2, Types::Float arg3 );
	void AddEvent(	Types::Int type, Types::Float arg0, Types::Float arg1, Types::Float arg2,
					Types::Float arg3, Types::Float arg4 );
	void AddEvent( Types::Int type, Color::RGBA8 color );
	void AddEvent( Types::Int type, Color::RGBA8 color0, Color::RGBA8 color1 );
	void AddEvent( Types::Int type, Color::RGBA8 color0, Color::RGBA8 color1, Types::Float arg0 );
	void AddEvent( Types::Int type, Color::RGBA8 color, Types::Float arg0 );
	void AddEvent( Types::Int type, const std::wstring &string );
	void AddEvent( Types::Int type, Entity *entity );

	// Avvia un evento dell'oggetto
	virtual Types::Bool SendEvent( Event *event, Entity *other ) = 0;

	// Rende ciclica la coda degli eventi
	void SetEventLoop( Types::Bool state );
	// Controlla se la coda degli eventi è ciclica
	Types::Bool GetEventLoop() const;

	// Ritorna la lista degli eventi
	const EventList &GetEventList() const;

	// Ritorna il numero degli eventi
	Types::Uint GetEventNumber() const;

protected:

	// Lista degli eventi
	EventList event_list;

	// Flag della ciclicità degli eventi
	Types::Bool event_loop;

	// Aggiungo un nuovo evento alla coda
	Event *PushEvent( Types::Int type, Types::Bool loop );
	// Aggiungo un nuovo evento all'inizio della coda
	Event *InserEvent( Types::Int type, Types::Bool loop, Types::Uint index );

	// Rimuovo il primo evento della coda
	virtual void PopEvent( Event *event );
};

}; // Chiudo il namespace di VGE

#endif
