/* 
    Title --- xml-inl.hpp

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


#ifndef VGE_XML_INL_HPP
#define VGE_XML_INL_HPP

#include "vge/xml.hpp"

namespace VGE { // Namespace di VGE

inline Types::Uint
xstrlen( const wchar_t *start, const wchar_t *end ) {

	// Conta i caratteri di una stringa delimitata da due puntatori
	return (Types::Uint) (Types::Uint) ( end - start );
}

inline const wchar_t *
Xml::GetName() const {

	// Ritorno il nome del nodo
	return this->tag_name;
}

inline Types::Uint
Xml::GetRow() const {

	// Ritorna la riga di posizione del tag
	return xstrrow( this->n_buffer, this->n_start );
}

inline Xml
Xml::Child( const wchar_t *tag ) const {

	// Ritorno un elemento figlio
	Xml child( this->n_buffer, tag, this );

	return child;
}

inline const Xml *
Xml::Parent() const {

	// Ritorno un puntatore all'istanza padre
	return this->n_parent;
}

inline Types::Bool
Xml::Exist() const {

	// Controllo l'esistenza del nodo
	return ( this->n_start != NULL );
}

}; // Chiudo il namespace di VGE

#endif
