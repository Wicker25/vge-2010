/* 
    Title --- global.hpp

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


#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include <list>

#include "vge/consts.hpp"
#include "vge/types.hpp"
#include "vge/math.hpp"

namespace VGE { // Namespace di VGE

// Prototipi
class Entity;
namespace Gui { class Font; }

namespace Global { // Namespace delle variabili globali

// Esporto la lista generale delle entità
extern std::list< Entity * > Entities;

// Esporto la lista generale dei font
extern std::list< Gui::Font * > Fonts;

// Ritorna il puntatore ad un'entità della scena
Entity *GetEntity( const std::wstring &name );

// Ritorna il puntatore al font
Gui::Font *GetFont( const std::wstring &name );

}; // Chiudo il namespace delle variabili globali

}; // Chiudo il namespace di VGE

#endif
