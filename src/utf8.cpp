/* 
    Title --- utf8.cpp

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


#ifndef VGE_UTF8_CPP
#define VGE_UTF8_CPP

#include "vge/utf8.hpp"
#include "vge/inline/utf8-inl.hpp"

namespace VGE { // Namespace di VGE

Utf8::Utf8( const std::string &path_, OpenMode mode_ ) : path( path_ ), mode( mode_ ) {

	// Controllo la modalità di apertura del file
	if ( this->GetMode() == OUT ) {

		// Creo il descritore della conversione
		this->conv_descriptor = iconv_open( "utf-8", "wchar_t" );

		// Apro il flusso al file
		this->stream = fopen( this->path.c_str(), "wb" );

	} else {

		// Creo il descritore della conversione
		this->conv_descriptor = iconv_open( "wchar_t", "utf-8" );

		// Apro il flusso al file
		this->stream = fopen( this->path.c_str(), "rb" );
	}

	// Controllo che se ci sono stati errori nella creazione del descrittore
	if ( this->conv_descriptor == (iconv_t)(-1) ) {

		printf( "EEEEE\n" );
	}

	// Controllo che lo stream sia stato aperto correttamente
	if ( this->IsOpen() ) {

		// Controllo la dimensione del file
		fseek( this->stream, 0, SEEK_END );

		// Imposto la dimensione del file
		this->size = ftell( stream );

		// Mi riposiziono all'inizio del file
		rewind( stream );

	} else {

		// Imposto la dimensione del file
		this->size = 0;
	}
}

Utf8::~Utf8() {

	// Chiudo lo stream
	this->Close();

	// Elimino il descrittore della conversione
	iconv_close( conv_descriptor );
}

Types::Bool
Utf8::Write( const std::wstring &string ) {

	// Flag di controllo
	Types::Bool wrote = false;

	// Controllo che la modalità di apertura coincida
	if ( this->GetMode() == OUT ) {

		// Controllo che lo stream sia stato aperto correttamente
		if ( this->IsOpen() ) {

			// Dimensione della stringa in byte
			size_t from_len = ( string.size() * sizeof( wchar_t ) );

			// Dimensione della nuova stringa in byte
			size_t to_len = ( from_len * 2 );

			// Alloco la memoria necessaria a contenere la stringa convertita
			char *utf8 = (char *) malloc( to_len );

			// Strutture di lavoro
			char *wdata		= (char *) &string[0];
			size_t wlen		= from_len;
			char *data		= utf8;
			size_t len		= to_len;

			// Converto la stringa
			size_t iconv_value = iconv( this->conv_descriptor, &wdata, &wlen, &data, &len );

			// Gestisco eventuali errori
			if ( !this->CheckError( iconv_value, CANT_WRITE_CODE_FILE ) ) {

				// Scrivo la nuova stringa nel file
				fwrite( utf8, ( to_len - len ), 1, this->stream );

				// Imposto il flag di controllo
				wrote = true;
			}

			// Libero la memoria
			free( utf8 );
		}
	}

	return wrote;
}

Types::Bool
Utf8::Write( const wchar_t *fmt, ... ) {

	va_list ap;
	va_start( ap, fmt );

	// Buffer di lavoro
	std::wstring buffer;
	
	// Alloco una quantità di memoria iniziale
	buffer.resize( 1024 );

	// Preparo la stringa
	buffer.resize( vswprintf( &buffer[0], buffer.size(), fmt, ap ) );

	va_end( ap );

	// Scrivo la stringa sul file
	return this->Write( buffer );
}

Types::Bool
Utf8::Read( std::wstring &string ) {

	// Flag di controllo
	Types::Bool read = false;

	// Controllo che la modalità di apertura coincida
	if ( this->GetMode() == IN ) {

		// Controllo che lo stream sia stato aperto correttamente
		if ( this->IsOpen() ) {

			// Dimensione della nuova stringa in byte
			size_t to_len = ( this->size * sizeof( wchar_t ) );

			// Alloco la memoria necessaria a contenere il testo del file
			char *utf8 = (char *) malloc( this->size );

			// Copio il testo dal file
			fread( utf8, this->size, 1, this->stream );

			// Alloco la memoria necessaria a contenere la stringa convertita
			string.resize( this->size );

			// Strutture di lavoro
			char *wdata		= (char *) &string[0];
			size_t wlen		= to_len;
			char *data		= utf8;
			size_t len		= this->size;

			// Converto la stringa
			size_t iconv_value = iconv( this->conv_descriptor, &data, &len, &wdata, &wlen );

			// Gestisco eventuali errori
			if ( !this->CheckError( iconv_value, CANT_READ_CODE_FILE ) ) {

				// Ottimizzo la memoria
				string.resize( ( to_len - len ) / sizeof( wchar_t ) );

				// Imposto il flag di controllo
				read = true;
			}

			// Libero la memoria
			free( utf8 );
		}
	}

	return read;
}

Types::Bool
Utf8::CheckError( size_t value, const char *message ) {

	// Flag di controllo
	Types::Bool error = false;

	// Gestisco eventuali errori
	if ( value == (size_t) - 1 ) {

		// Imposto il flag di controllo
		error = true;

		// Controllo il tipo di errore
		switch ( errno ) {

			case EILSEQ:

				fprintf( stderr,	message, FATAL, "utf-8",
									this->path.c_str(), "Invalid multibyte sequence" );
				break;

			case EINVAL:

				fprintf( stderr,	message, FATAL, "utf-8",
									this->path.c_str(), "Incomplete multibyte sequence" );
				break;

			case E2BIG:

				fprintf( stderr,	message, FATAL, "utf-8",
									this->path.c_str(), "No more room" );
				break;

			default:

				fprintf( stderr,	message, FATAL, "utf-8",
									this->path.c_str(), strerror( errno ) );
		}
	}

	return error;
}

}; // Chiudo il namespace di VGE

#endif
