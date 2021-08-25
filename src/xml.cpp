/* 
    Title --- xml.cpp

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


#ifndef VGE_XML_CPP
#define VGE_XML_CPP

#include "vge/xml.hpp"

#include "vge/utf8.hpp"
#include "vge/inline/utf8-inl.hpp"

#include "vge/inline/xml-inl.hpp"

namespace VGE { // Namespace di VGE

Types::Uint
xstrrow( const wchar_t *start, const wchar_t *end ) {

	// Conta gli spazi in una stringa delimitata da due puntatori
	Types::Uint length = xstrlen( start, end );

	Types::Uint i = 0, count = 1;

	for ( ; i < length; i++ )

		if ( start[i] == L'\n' ) count++;

	return count;
}

wchar_t *
xstrchr( const wchar_t key, const wchar_t *start, const wchar_t *end, const wchar_t *nokey = NULL ) {

	// Cerca un carattere in una stringa delimitata da due puntatori
	wchar_t *ptr = (wchar_t *) start;

	while ( ptr != end ) {

		if ( *ptr == key ) return ptr;
		else if ( nokey != NULL ) {

			Types::Uint i = 0, l = wcslen( nokey );
			for ( ; i < l; i++ ) if ( *ptr == nokey[i] ) return NULL;
		}
		ptr++;
	}

	return NULL;
}

wchar_t *
xrstrchr( const wchar_t key, const wchar_t *start, const wchar_t *end, const wchar_t *nokey = NULL ) {

	// Cerca un carattere in una stringa delimitata da due puntatori (all'indietro)
	wchar_t *ptr = (wchar_t *) end;

	while ( ptr != start ) {

		if ( *ptr == key ) return ptr;
		else if ( nokey != NULL ) {

			Types::Uint i = 0, l = wcslen( nokey );
			for ( ; i < l; i++ ) if ( *ptr == nokey[i] ) return NULL;
		}
		ptr--;
	}

	return NULL;
}

wchar_t *
xstrstr( const wchar_t *key, const wchar_t *start, const wchar_t *end, const wchar_t *nokey = NULL ) {

	// Cerca una sequenza di caratteri in una stringa delimitata da due puntatori
	Types::Uint len = wcslen( key );

	if ( end == NULL ) {

		Types::Uint tlen = wcslen( start );
		end = &start[tlen];
	}

	if ( xstrlen( start, end ) >= len ) end -= len;
	else return NULL;

	wchar_t *ptr = (wchar_t *) start;

	while ( ptr != end ) {

		if ( !wcsncmp( ptr, key, len ) ) return ptr;
		else if ( nokey != NULL ) {

			Types::Uint i = 0, l = wcslen( nokey );
			for ( ; i < l; i++ ) if ( *ptr == nokey[i] ) return NULL;
		}
		ptr++;
	}

	return NULL;
}

wchar_t *
xrstrstr( const wchar_t *key, const wchar_t *start, const wchar_t *end, const wchar_t *nokey = NULL ) {

	// Cerca una sequenza di caratteri in una stringa delimitata da due puntatori (all'indietro)
	Types::Uint len = wcslen( key );

	if ( end == NULL ) {

		Types::Uint tlen = wcslen( start );
		end = &start[tlen];
	}

	if ( xstrlen( start, end ) >= len ) end -= len;
	else return NULL;


	wchar_t *ptr = (wchar_t *) end;

	while ( ptr != start ) {

		if ( wcsncmp( ptr, key, len ) == 0 ) return ptr;
		else if ( nokey != NULL ) {

			Types::Uint i = 0, l = wcslen( nokey );
			for ( ; i < l; i++ ) if ( *ptr == nokey[i] ) return NULL;
		}
		ptr--;
	}

	return NULL;
}

void
xstrncpy( wchar_t *dest, const wchar_t *start, const wchar_t *end, Types::Uint length ) {

	// Copia una stringa delimitata da due puntatori
	length = VMIN( xstrlen( start, end ), length );
	Types::Uint i = 0;

	for ( ; i < length; i++ )

		dest[i] = start[i];

	dest[i] = L'\0';
}

void
xprint_str( const wchar_t *start, const wchar_t *end, Types::Bool endl = true ) {

	// Stampa stringa delimitata da due puntatori
	wchar_t *ptr = (wchar_t *) start;
	while ( ptr != end ) printf( "%lc", *ptr++ );
	if ( endl ) printf( "\n" );
}

Xml::Xml( const wchar_t *buffer, const wchar_t *tag, const Xml *parent = NULL ) : n_parent( parent ) {

	// Memorizzo il nome del tag
	this->tag_name = tag;

	// Creo la lista degli attributi
	this->attributes = new AttributesList;

	// Inizializzo le strutture di lavoro
	this->n_buffer	= buffer;
	this->n_start	= NULL;
	this->n_end		= NULL;

	// Cerco l'elemento radice
	if ( parent == NULL )
		this->extract_tag( tag, (wchar_t *) buffer, NULL );

	else if ( parent->n_start != parent->n_end )
		this->extract_tag( tag, parent->n_start, parent->n_end );
}

Xml::~Xml() {

	// Libero la memoria
	Types::Int i = this->attributes->size();
	Attribute *attr;

	while ( --i >= 0 ) {

		attr = &this->attributes->at(i);

		free( attr->name );
		free( attr->value );
	}

	this->attributes->clear();
	delete this->attributes;
}

void
Xml::extract_tag( const wchar_t *tag, const wchar_t *start, const wchar_t *end ) {

	// Strutture di lavoro
	wchar_t *find = (wchar_t *) start;
	wchar_t key[100];

	// Costruisco la chiave di ricerca
	wcscpy( key, L"<" );
	wcsncat( key, tag, 30 );

	do {

		// Cerco il tag nel buffer
		if ( ( find = xstrstr( key, find, end ) ) == NULL ) { 

			//print_error( 2, tag );
			return;
		}

		find += wcslen(tag);

	// Controllo il carattere alla fine del nome del tag
	} while ( *(find + 1) != L'>' && *(find + 1) != L' ' );

	if ( ( this->n_start = xstrchr( L'>', find, end, L"<" ) ) == NULL ) {

		//print_error( 0, xstrrow( this->n_buffer, find ) );
		return;
	}

	if ( *( this->n_start - 1 ) != L'/' ) {

		this->n_start++;

		// Costruisco la chiave di ricerca
		wcscpy( key, L"</" );
		wcsncat( key, tag, 30 );
		wcscat( key, L">" );

		// Cerco il tag di chiusura nel buffer
		if ( ( this->n_end = xstrstr( key, this->n_start, end ) ) == NULL ) {

			//print_error( 0, this->GetRow() );
			printf( "A: %ls\n", key );
			return;
		}

	} else this->n_end = this->n_start;

	// Estraggo gli attributi del tag
	this->extract_attributes( find, this->n_start );
}

void
Xml::extract_attributes( wchar_t *start, wchar_t *end ) {

	// Strutture di lavoro
	wchar_t *ptr_s[2] = { start, start };
	Attribute attr;
	Types::Uint length;
 
	while ( ( ptr_s[0] = xstrstr( L"=\"", ptr_s[0], end ) ) != NULL ) {

		// Estraggo il nome dell'attributo
		if ( ( ptr_s[1] = xstrchr( L' ', ptr_s[1], ptr_s[0] - 1 ) ) == NULL ) {

			//print_error( 0, xstrrow( this->n_buffer, ptr_s[0] ) );
			break;
		}

		// Copio il nome dell'attributo
		length = xstrlen( ptr_s[1] + 1, ptr_s[0] );
		attr.name = (wchar_t *) malloc( sizeof(wchar_t) * ( length + 1 ) );
		xstrncpy( attr.name, ++ptr_s[1], ptr_s[0], 20 );

		ptr_s[0] += 2;

		// Estraggo il valore dell'attributo
		if ( ( ptr_s[1] = xstrchr( L'"', ptr_s[0], end, L"<>" ) ) == NULL ) {

			//print_error( 0, xstrrow( this->n_buffer, ptr_s[0] ) );
			break;
		}

		// Copio il valore dell'attributo
		length = xstrlen( ptr_s[0], ptr_s[1] );
		attr.value = (wchar_t *) malloc( sizeof(wchar_t) * ( xstrlen( ptr_s[0], ptr_s[1] + 1 ) ) );
		xstrncpy( attr.value, ptr_s[0], ptr_s[1], length );

		// Aggiungo l'attributo alla lista
		this->attributes->push_back( attr );
	}
}

Xml
Xml::Child( const wchar_t *tag, wchar_t **iterator ) const {

	if ( *iterator == NULL ) *iterator = (wchar_t *) this->n_start;

	// Modifico il campo di ricerca in base all'iteratore
	wchar_t *tmp = this->n_start;

	// Aggiro la protezione dalla scrittura
	wchar_t **start_ = const_cast< wchar_t ** > ( &this->n_start );

	*start_ = *iterator;

	// Ritorno un elemento figlio
	Xml child( this->n_buffer, tag, this );

	// Ripristino il campo di ricerca
	*start_ = tmp;

	// Aggiorno l'iteratore
	*iterator = (wchar_t *) child.n_start;

	return child;
}

wchar_t *
Xml::Value() const {

	// Controllo la validità dell'istanza
	if ( this->n_start == this->n_end ) return NULL;
	if ( this->n_start == NULL || this->n_end == NULL ) return NULL;

	// Ritorno il contenuto dell'elemento
	Types::Uint length = xstrlen( this->n_start, this->n_end );

	wchar_t *value = (wchar_t *) malloc( sizeof(wchar_t) * length );
	xstrncpy( value, this->n_start, this->n_end, length );

	return value;
}

Types::Bool
Xml::GetAttribute( const wchar_t *name, wchar_t **ptr ) const {

	// Strutture di lavoro
	Types::Int i = this->attributes->size();
	Attribute *attr;

	// Cerco un attributo
	while ( --i >= 0 ) {

		attr = &(*this->attributes)[i];

		if ( wcscmp( name, attr->name ) == 0 ) {

			*ptr = attr->value;
			return true;
		}
	}

	// Ritorna il valore di un attributo
	return false;
}

}; // Chiudo il namespace di VGE

#endif
