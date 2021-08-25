/* 
    Title --- character.hpp

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


#ifndef VGE_CHARACTER_HPP
#define VGE_CHARACTER_HPP

#include <iostream>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
//#include <SDL/SDL_opengl.h>
#include <GL/glew.h> 

#include "vge/consts.hpp"
#include "vge/types.hpp"
#include "vge/math.hpp"

#include "vge/object.hpp"

// Macro per il casting
#define VGE_CHARACTER( x )		( (VGE::Character *) x )

namespace VGE { // Namespace di VGE

class Character : public Object {

	/* PERSONAGGIO */

public:

	// Metodi costruttore e distruttore
	Character( const std::string &path, const Types::Size2D_u size_, Types::Uint n_frames );
	Character( const Image &image, const Types::Size2D_u size_, Types::Uint n_frames );
	virtual ~Character();

	// Mette il personaggio nello stato inattivo
	virtual void SetIdle();

	// Invia un segnale al personaggio
	virtual void SendSignal( Types::Int type, Entity *other );

	// Funzione di lavoro
	virtual void Update( Viewer *viewer, Player *player );


	/* Metodi di costruzione */

	// Costruttore da nodo XML
	Character( const Xml *node );

	// Estrae le caratteristiche dell'oggetto
	//void ExtractObjFeatures( const Xml *node );
};

}; // Chiudo il namespace di VGE

#endif
