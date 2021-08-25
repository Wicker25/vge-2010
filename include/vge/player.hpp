/* 
    Title --- player.hpp

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


#ifndef VGE_PLAYER_HPP
#define VGE_PLAYER_HPP

#include <iostream>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
//#include <SDL/SDL_opengl.h>
#include <GL/glew.h> 

#include "vge/consts.hpp"
#include "vge/types.hpp"
#include "vge/math.hpp"

#include "vge/input-manager.hpp"

#include "vge/character.hpp"

// Macro per il casting
#define VGE_PLAYER( x )		( (VGE::Player *) x )

namespace VGE { // Namespace di VGE

namespace SignalType { // Namespace del tipo di segnale

// Tipo del segnale
enum {

	CHECK_INTERACTION = 750, // SEGNALE DI RICERCA DELL'INTERAZIONE
	CHECK_MOUSE_INTERACTION, // SEGNALE DI RICERCA DELL'INTERAZIONE ATTRAVERSO IL MOUSE
};

}; // Chiudo il namespace del tipo di segnale

class Player : public Character {

	/* GIOCATORE */

public:

	// Metodi costruttore e distruttore
	Player( const std::string &path, const Types::Size2D_u size_, Types::Uint n_frames );
	Player( const Image &image, const Types::Size2D_u size_, Types::Uint n_frames );
	virtual ~Player();

	// Ritorna l'area di interazione
	BoundingArea &GetInteractionArea();
	const BoundingArea &GetInteractionArea() const;

	// Invia un segnale all'oggetto
	virtual void SendSignal( Types::Int type, Entity *other );

	// Gestisce gli eventi da tastiera
	virtual void Update( Viewer *viewer, Player *player );

	// Disegna il rettangolo di interazione
	virtual void DrawInteractionRectangle( const Types::Point2D &offset ) const;

	// Disegna l'oggetto sullo schermo
	virtual void Draw( const Types::Point2D &offset, Color::RGBA8 blend ) const;


	/* Metodi di costruzione */

	// Costruttore da nodo XML
	Player( const Xml *node );

	// Estrae l'area di interazione del personaggio
	void ExtractInteractionArea( const Xml *node );

	// Scrive le informazioni sull'area dell'entità
	virtual void WriteBoundingArea( Utf8 *stream ) const;


	/* SEGNALI */

	// Ritorna l'istanza del segnale di ricerca dell'interazione
	sigc::signal< void, Player *, Sprite * > &SignalCheckInteration();

protected:

	// Area di interazione
	BoundingArea interaction_area;

	// Eventi
	Types::Bool interaction;


	/* SEGNALI */

	// Segnale di cambio di ricerca dell'interazione
	sigc::signal< void, Player *, Sprite * > signal_check_interation;
};

// Ridefinizione dei tipo lista
typedef std::list< Player * > PlayerList;

}; // Chiudo il namespace di VGE

#endif
