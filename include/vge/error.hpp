/* 
    Title --- error.hpp

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


#ifndef VGE_ERROR_HPP
#define VGE_ERROR_HPP

#include <iostream>

#include "vge/types.hpp"

#define WARNING		"(W) Warning"
#define FATAL		"(!) Fatal"
#define BROKE		"(E) Broke"

#define CANNOT_OPEN_FILE		" %s: cannot open file \"%s\"!\n"
#define CANNOT_OPEN_FILE_W		" %s: cannot open file \"%ls\"!\n"

#define COULDNT_LOAD_FILE		" %s: couldn't load file \"%s\"!\n"
#define COULDNT_LOAD_FILE_W		" %s: couldn't load file \"%ls\"!\n"

#define EMPTY_FILE				" %s: file \"%s\" is empty!\n"

#define CANT_READ_CODE_FILE		" %s: can't read %s file \"%s\": %s!\n"
#define CANT_WRITE_CODE_FILE	" %s: can't write %s file \"%s\": %s!\n"

#define SYNTAX_ERROR			" %s: line %u, syntax error!\n"

#define NO_TAG_FOUND			" %s: line %u, no \"%s\" tag found!\n"
#define NO_TAG_FOUND_W			" %s: line %u, no \"%ls\" tag found!\n"

#define NO_ATTRIBUTE_FOUND		" %s: line %u, no \"%s\" attribute found!\n"
#define NO_ATTRIBUTE_FOUND_W	" %s: line %u, no \"%ls\" attribute found!\n"

#define VALUE_ERROR				" %s: line %u, \"%s\" value error!\n"
#define VALUE_ERROR_W			" %s: line %u, \"%ls\" value error!\n"

#define NO_FONT_ASSIGNED		" %s: no %s font assigned!\n"
#define NO_FONT_ASSIGNED_W		" %s: no %ls font assigned!\n"

#define FONT_NOT_DEFINED		" %s: line %u, font \"%s\" not defined!\n"
#define FONT_NOT_DEFINED_W		" %s: line %u, font \"%ls\" not defined!\n"

#define INVALID_TYPE			" %s: invalid type \"%s\"!\n"
#define INVALID_TYPE_W			" %s: invalid type \"%ls\"!\n"

#define INVALID_TYPE_LINE		" %s: line %u, invalid type \"%s\"!\n"
#define INVALID_TYPE_LINE_W		" %s: line %u, invalid type \"%ls\"!\n"

#define WRONG_SYNTAX_OF			" %s: line %u, wrong syntax of \"%s\"!\n"
#define WRONG_SYNTAX_OF_W		" %s: line %u, wrong syntax of \"%ls\"!\n"

#define ENTITY_NOT_DEFINED		" %s: line %u, entity \"%s\" not defined!\n"
#define ENTITY_NOT_DEFINED_W	" %s: line %u, entity \"%ls\" not defined!\n"

#endif
