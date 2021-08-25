/* 
    Title --- container-inl.hpp

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


#ifndef VGE_CONTAINER_INL_HPP
#define VGE_CONTAINER_INL_HPP

#include "vge/widgets/container.hpp"

namespace VGE { // Namespace di VGE

namespace Gui { // Namespace dell'interfaccia grafica

inline void
Container::AddChild( Widget *widget ) {

	// Imposto il tipo di impacchettamento di default
	PackingType type;

	if ( widget != NULL && widget->GetMask() == CONTAINER_MASK )

		type = Container::PACKING_FILL;
	else
		type = Container::PACKING_EXPAND;

	// Aggiungo un widget figlio al contenitore
	this->AddChild( widget, type );
}

inline void
Container::AddChild( Widget *widget, PackingType type ) {

	// Aggiungo un widget figlio al contenitore
	if ( type == Container::PACKING_FILL )

		this->AddChild( widget, type, 0.0f, 0.0f );
	else
		this->AddChild( widget, type, 0.5f, 0.5f );
}

inline void
Container::AddChild( Widget *widget, PackingType type, Types::Float x, Types::Float y ) {

	// Creo la nuova struttura per l'impacchettamento
	Child child;

	// Aggiungo un widget figlio al contenitore
	this->child_list.push_back( child );

	// Configuro l'impacchettamento del widget figlio nel contenitore
	this->SetChildPacking( this->child_list.size() - 1, type, widget, x, y );
}

inline void
Container::SetChildPosition( Types::Uint iter, Types::Float x, Types::Float y ) {

	// Ricavo la struttura del widget impacchettato
	Child *child = &this->child_list[iter];

	// Reinizializzo la struttura
	child->position.x	= x;
	child->position.y	= y;
}

inline Widget *
Container::GetChildPacking( Types::Uint iter ) const {

	// Puntatore al widget figlio
	Widget *widget = NULL;

	// Verifico l'esistenza dell'impacchettamento
	if ( iter >= 0 && iter < this->child_list.size() ) 

		// Ricavo il widget impacchettato
		widget = this->child_list[iter].widget;

	// Ritorno un widget impacchettato
	return widget;
}

inline Types::Uint
Container::GetNumberOfChilds() const {

	// Ritorno il numero dei widget figli nel contenitore
	return (Types::Uint) this->child_list.size();
}

}; // Chiudo il namespace dell'interfaccia grafica

}; // Chiudo il namespace di VGE

#endif
