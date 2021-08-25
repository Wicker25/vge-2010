/* 
    Title --- sprite.hpp

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


#ifndef VGE_SPRITE_HPP
#define VGE_SPRITE_HPP

#include <iostream>

#include "vge/consts.hpp"
#include "vge/types.hpp"
#include "vge/math.hpp"

#include "vge/interfaces/i-clickable.hpp"

#include "vge/image.hpp"

// Macro per il casting
#define VGE_SPRITE( x )		( (VGE::Sprite *) x )

namespace VGE { // Namespace di VGE

namespace SignalType { // Namespace del tipo di segnale

// Tipo del segnale
enum {

	CHANGE_SOLIDITY = 650,		// SEGNALE DI CAMBIO DELLA SOLIDITA'
	COLLISION,					// SEGNALE DI COLLISIONE
	INTERACTION,				// SEGNALE DI INTERAZIONE
};

}; // Chiudo il namespace del tipo di segnale

namespace EventType { // Namespace del tipo dell'evento

// Tipo dell'evento
enum {

	WAIT_COLLISION = 650,	// ASPETTA IL SEGNALE DI COLLISIONE
	WAIT_INTERACTION,		// ASPETTA L'INTERAZIONE CON L'OGGETTO
};

}; // Chiudo il namespace del tipo dell'evento

// Prototipi
class Player;
class Viewer;

class Sprite : public Image {

	/* SPRITE */

public:

	// Metodi costruttore e distruttore
	Sprite( const std::string &path );
	Sprite( const std::string &path, const Types::Size2D_u size_ );
	Sprite( const Image &image );
	Sprite( const Image &image, const Types::Size2D_u size_ );
	virtual ~Sprite();

	// Modifica la posizione dell'oggetto (assoluta)
	virtual void SetPosition( const Types::Point2D &point );
	virtual void SetPosition( const Types::Point3D &point );
	// Modifica la posizione dell'oggetto (relativa)
	virtual void MovePosition( Types::Float x, Types::Float y, Types::Float z );

	// Memorizza la posizione attuale dell'oggetto
	virtual void StorePosition( Types::Bool x, Types::Bool y, Types::Bool z );
	// Ripristina la posizione memorizzata dell'oggetto
	virtual void RestorePosition( Types::Bool x, Types::Bool y, Types::Bool z );
	// Ritorno la vecchia posizione dell'oggetto (assoluta)
	virtual void GetStoredPosition( Types::Float *x, Types::Float *y, Types::Float *z ) const;

	// Ritorna l'area di collisione
	BoundingArea &GetCollisionArea();
	const BoundingArea &GetCollisionArea() const;

	// Modifica la solidità dell'oggetto
	virtual void SetSolid( Types::Bool state );
	// Controlla la solidità dell'oggetto
	virtual Types::Bool GetSolid() const;

	// Invia un segnale all'oggetto
	virtual void SendSignal( Types::Int type, Entity *other );

	// Avvia un evento dell'oggetto
	virtual Types::Bool SendEvent( Event *event, Entity *other );

	// Funzione di lavoro
	virtual void Update( Viewer *viewer, Player *player );

	// Disegna il rettangolo di collisione
	virtual void DrawCollisionRectangle( const Types::Point2D &offset ) const;

	// Disegna lo sprite sullo schermo
	virtual void Draw( const Types::Point2D &offset, Color::RGBA8 blend ) const;


	/* Metodi di costruzione */

	// Costruttore da nodo XML
	Sprite( const Xml *node );

	// Estrae l'area di collisione dello sprite
	void ExtractCollisionArea( const Xml *node );

	// Estrae l'evento dalla lista
	virtual void ExtractEvent( const Xml *node, const wchar_t *type, std::vector< wchar_t *> &values );

	// Scrive le informazioni sull'area dell'entità
	virtual void WriteBoundingArea( Utf8 *stream ) const;


	/* SEGNALI */

	// Ritorna l'istanza del segnale di cambio della solidità
	sigc::signal< void, Types::Bool, Sprite * > &SignalSolidity();

	// Ritorna l'istanza del segnale di collisione
	sigc::signal< void, Sprite *, Sprite * > &SignalCollision();

	// Ritorna l'istanza del segnale di interazione
	sigc::signal< void, Player *, Sprite * > &SignalInteration();

protected:

	// Flags dello solid
	Types::Bool solid;

	// Posizione
	Types::Point3D store;

	// Area di visibilità
	BoundingArea collision_area;


	/* SEGNALI */

	// Segnale di cambio della solidità
	sigc::signal< void, Types::Bool, Sprite * > signal_solidity;

	// Segnale di collisione
	sigc::signal< void, Sprite *, Sprite * > signal_collision;

	// Segnale di interazione
	sigc::signal< void, Player *, Sprite * > signal_interation;
};

}; // Chiudo il namespace di VGE

#endif
