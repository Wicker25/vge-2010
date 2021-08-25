/* 
    Title --- utf8-inl.hpp

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


#ifndef VGE_UTF8_INL_HPP
#define VGE_UTF8_INL_HPP

#include "vge/utf8.hpp"

namespace VGE { // Namespace di VGE

inline Types::Bool
Utf8::IsOpen() const {

	// Controllo se lo stream è stato aperto correttamente	
	return ( this->stream != NULL );
}

inline OpenMode
Utf8::GetMode() const {

	// Ritorno la modalità di apertura
	return this->mode;
}

inline void
Utf8::Close() {

	// Controllo che lo stream sia stato aperto correttamente
	if ( this->IsOpen() ) {

		// Chiudo lo stream
		fclose( this->stream );

		// Modifico il puntatore al file
		this->stream = NULL;
	}
}

}; // Chiudo il namespace di VGE

#endif
