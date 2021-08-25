/* 
    Title --- label.hpp

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


#ifndef VGE_LABEL_HPP
#define VGE_LABEL_HPP

#include <iostream>
#include <vector>
#include <list>

#include "vge/consts.hpp"
#include "vge/types.hpp"
#include "vge/math.hpp"
#include "vge/global.hpp"

#include "vge/interfaces/i-resizable.hpp"
#include "vge/interfaces/i-colorable.hpp"

#include "vge/entity.hpp"

#include "vge/widgets/box.hpp"
#include "vge/widgets/font.hpp"
#include "vge/widgets/widget.hpp"
#include "vge/widgets/frame.hpp"

namespace VGE { // Namespace di VGE

namespace Gui { // Namespace dell'interfaccia grafica

class Label : public Frame, public InterfaceColorable {

	/* RIQUADRO DI TESTO */

public:

	// Metodi costruttore e distruttore
	Label( const std::wstring &string );
	Label( const std::wstring &string, Font *font );
	virtual ~Label();

	// Imposta il font
	virtual void SetFont( Font *font );
	// Ritorna il puntatore al font
	virtual Font *GetFont() const;

	// Imposta il testo
	virtual void SetString( const std::wstring &string );
	// Ritorna la stringa del testo
	virtual const std::wstring GetString() const;

	// Ritorna il numero dei caratteri del testo
	virtual Types::Uint Lenght() const;

	// Funzione di lavoro
	virtual void Update( Viewer *viewer, Player *player );

	// Disegna il testo sullo schermo
	virtual void Draw( const Types::Point2D &offset, Color::RGBA8 blend ) const;

protected:

	// Puntatore al font
	Font *t_font;

	// Puntatore alla stringa
	std::wstring t_string;

	// Flag di aggiornamento
	Types::Bool update;
};

// Ridefinizione dei tipo lista
typedef std::list< Label * > LabelList;

}; // Chiudo il namespace dell'interfaccia grafica

}; // Chiudo il namespace di VGE

#endif
