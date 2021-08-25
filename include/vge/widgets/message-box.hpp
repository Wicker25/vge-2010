/* 
    Title --- message-box.hpp

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


#ifndef VGE_MESSAGE_BOX_HPP
#define VGE_MESSAGE_BOX_HPP

#include <iostream>
#include <vector>
#include <list>

#include "vge/consts.hpp"
#include "vge/types.hpp"
#include "vge/math.hpp"

#include "vge/image.hpp"

#include "vge/widgets/box.hpp"
#include "vge/widgets/window.hpp"
#include "vge/widgets/text-box.hpp"

namespace VGE { // Namespace di VGE

namespace Gui { // Namespace dell'interfaccia grafica

class MessageBox : public Window {

	/* FINESTRA DI DIALOGO */

public:

	// Metodi costruttore e distruttore
	MessageBox( const Types::Size2D_u size_ );
	MessageBox( const std::wstring &string, const Types::Size2D_u size_ );
	virtual ~MessageBox();

	// Imposta l'immagine del dialogo
	void SetImage( Image *image, Types::Float x, Types::Float y );
	void SetImage( Image *image );
	// Ritorna l'immagine del dialogo
	Image *GetImage() const;

	// Ritorna il messaggio del dialogo
	TextBox &GetTextBox();
	const TextBox &GetTextBox() const;

	// Avvia un evento dell'oggetto
	virtual Types::Bool SendEvent( Event *event, Entity *other );

protected:

	// Messaggio del dialogo
	Container container;

	// Messaggio del dialogo
	TextBox text_box;
};

}; // Chiudo il namespace dell'interfaccia grafica

}; // Chiudo il namespace di VGE

#endif
