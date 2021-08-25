/* 
    Title --- maker.hpp

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


#ifndef VGE_MAKER_HPP
#define VGE_MAKER_HPP

#include <iostream>
#include <vector>

#include "vge/consts.hpp"
#include "vge/types.hpp"
#include "vge/error.hpp"
#include "vge/math.hpp"

#include "vge/xml.hpp"

#include "vge/color.hpp"

#include "vge/entity.hpp"
#include "vge/scene.hpp"

#include "vge/widgets/box.hpp"

namespace VGE { // Namespace di VGE

class Maker {

	/* COSTRUTTORE DI ENTITA' */

public:

	// Converte una stringa nel colore
	static Types::Bool StringToColor( const std::wstring &string, Color::RGBA8 *color );

	// Carica un entità da un file xml
	static Entity *LoadEntity( const std::string &path );

	// Estrae le informazioni su un riquadro
	static void ExtractFrame( const Xml *node, const wchar_t *tag_name, Gui::Box *frame );

	// Estrae un area di delimitazione
	static void ExtractBoundingArea( const Xml *node, const wchar_t *tag_name, BoundingArea *area );

	// Salva un entità in un file xml
	static Types::Bool SaveEntity( const Entity *entity, const std::string &path );

	// Carica una scena da un file xml
	static Scene *LoadScene( const std::string &path );
};

}; // Chiudo il namespace di VGE

#endif
