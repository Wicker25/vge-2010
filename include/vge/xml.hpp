/* 
    Title --- xml.hpp

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


#ifndef VGE_XML_HPP
#define VGE_XML_HPP

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

#include "vge/consts.hpp"
#include "vge/types.hpp"
#include "vge/error.hpp"
#include "vge/math.hpp"
#include "vge/utf8.hpp"

namespace VGE { // Namespace di VGE

// Struttura dell'attributo
typedef struct {

	wchar_t *name;
	wchar_t *value;

} Attribute;

// Ridefinizione del tipo lista
typedef std::vector< Attribute > AttributesList;

// Conta gli spazi in una stringa delimitata da due puntatori
Types::Uint xstrrow( const wchar_t *start, const wchar_t *end );

// Cerca un carattere in una stringa delimitata da due puntatori
wchar_t *xstrchr( const wchar_t key, const wchar_t *start, const wchar_t *end, const wchar_t *nokey );

// Cerca un carattere in una stringa delimitata da due puntatori (all'indietro)
wchar_t *xrstrchr( const wchar_t key, const wchar_t *start, const wchar_t *end, const wchar_t *nokey );

// Cerca una sequenza di caratteri in una stringa delimitata da due puntatori
wchar_t *xstrstr( const wchar_t* key, const wchar_t *start, const wchar_t *end, const wchar_t *nokey );

// Cerca una sequenza di caratteri in una stringa delimitata da due puntatori (all'indietro)
wchar_t *xrstrstr( const wchar_t* key, const wchar_t *start, const wchar_t *end, const wchar_t *nokey );

// Copia una stringa delimitata da due puntatori
void xstrncpy( wchar_t *dest, const wchar_t *start, const wchar_t *end, Types::Uint length );

// Conta i caratteri di una stringa delimitata da due puntatori
Types::Uint xstrlen( const wchar_t *start, const wchar_t *end );

// Stampa stringa delimitata da due puntatori
void xprint_str( const wchar_t *start, const wchar_t *end, Types::Bool endl );

class Xml {

	/* PARSER XML */

public:

	// Metodi costruttore e distruttore
	Xml( const wchar_t *buffer, const wchar_t *tag, const Xml *parent );
	virtual ~Xml();

	// Ritorna un elemento figlio
	Xml Child( const wchar_t *tag ) const;
	Xml Child( const wchar_t *tag, wchar_t **iterator ) const;

	// Ritorna il nome del nodo
	const wchar_t *GetName() const;

	// Ritorna la riga di posizione del tag
	Types::Uint GetRow() const;

	// Ritorna il contenuto dell'elemento
	wchar_t *Value() const;
	// Ritorna il valore di un attributo
	Types::Bool GetAttribute( const wchar_t *name, wchar_t **ptr ) const;

	// Ritorna un puntatore all'istanza padre
	const Xml *Parent() const;
	// Controlla l'esistenza del nodo
	Types::Bool Exist() const;

protected:

	// Struttura del nodo XML
	const wchar_t *tag_name;
	const Xml *n_parent;
	const wchar_t *n_buffer;
	wchar_t *n_start;
	wchar_t *n_end;

	// Attributi del nodo
	AttributesList *attributes;

	// Cerca un tag nel buffer
	void extract_tag( const wchar_t *tag, const wchar_t *start, const wchar_t *end );
	// Cerca gli attributi del tag
	void extract_attributes( wchar_t *start, wchar_t *end );
};

}; // Chiudo il namespace di VGE

#endif
