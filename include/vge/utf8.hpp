/* 
    Title --- utf8.hpp

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


#ifndef VGE_UTF8_HPP
#define VGE_UTF8_HPP

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cstdarg>

#include <iconv.h>
#include <errno.h>

#include "vge/consts.hpp"
#include "vge/types.hpp"
#include "vge/error.hpp"
#include "vge/math.hpp"

namespace VGE { // Namespace di VGE

// Modalità di apertura
typedef enum {

	IN,
	OUT,

} OpenMode;


class Utf8 {

	/* GESTIONE DEI FILE UTF8 */

public:

	// Metodi costruttore e distruttore
	Utf8( const std::string &path_, OpenMode mode_ );
	virtual ~Utf8();

	// Controlla se il file è stato aperto correttamente
	Types::Bool IsOpen() const;

	// Ritorna la modalità di apertura
	OpenMode GetMode() const;

	// Scrivo una stringa sul file
	Types::Bool Write( const std::wstring &string );
	Types::Bool Write( const wchar_t *fmt, ... );

	// Leggo la stringa dal file
	Types::Bool Read( std::wstring &string );

	// Chiude lo stream al file
	void Close();

private:

	// Cerco eventuali errori nella conversione
	Types::Bool CheckError( size_t value, const char *message );

	// Descrittore della conversione
	iconv_t conv_descriptor;

	// Percorso al file
	std::string path;

	// Dimensione del file
	size_t size;

	// Modalità di apertura
	OpenMode mode;

	// Flusso del file aperto
	FILE *stream;
};

}; // Chiudo il namespace di VGE

#endif
