/* 
    Title --- global.cpp

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


#ifndef GLOBAL_CPP
#define GLOBAL_CPP

#include "vge/global.hpp"

#include "vge/entity.hpp"
#include "vge/inline/entity-inl.hpp"

#include "vge/widgets/font.hpp"
#include "vge/widgets/inline/font-inl.hpp"

#include "vge/inline/global-inl.hpp"

namespace VGE { // Namespace di VGE

namespace Global { // Namespace delle variabili globali

// Creo la lista generale delle entità
std::list< Entity * > Entities;

// Creo la lista generale dei fonts
std::list< Gui::Font * > Fonts;

Entity *
GetEntity( const std::wstring &name ) {

	// Puntatore all'entità
	Entity *entity = NULL;

	// Iteratori
	std::list< Entity * >::const_iterator iter	= Global::Entities.begin();
	std::list< Entity * >::const_iterator end	= Global::Entities.end();

	// Cerco l'entità
	for ( ; iter != end; iter++ ) {

		// Confronto il nome dell'entità
		if ( name == (*iter)->GetName() )

			entity = *iter;
	}

	// Ritorno il puntatore all'entità
	return entity;
}

Gui::Font *
GetFont( const std::wstring &name ) {

	// Puntatore al font
	Gui::Font *font = NULL;

	// Iteratori
	std::list< Gui::Font * >::const_iterator iter	= Global::Fonts.begin();
	std::list< Gui::Font * >::const_iterator end	= Global::Fonts.end();

	// Cerco l'entità
	for ( ; iter != end; iter++ ) {

		// Confronto il nome dell'entità
		if ( name == (*iter)->GetName() )

			font = *iter;
	}

	// Ritorno il puntatore al font
	return font;
}

}; // Chiudo il namespace delle variabili globali

}; // Chiudo il namespace di VGE

#endif
