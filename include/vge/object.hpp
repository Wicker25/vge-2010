/* 
    Title --- object.hpp

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


#ifndef VGE_OBJECT_HPP
#define VGE_OBJECT_HPP

#include <iostream>
#include <deque>

#include "vge/consts.hpp"
#include "vge/types.hpp"
#include "vge/math.hpp"

#include "vge/sprite.hpp"

// Macro per il casting
#define VGE_OBJECT( x )		( (VGE::Object *) x )

namespace VGE { // Namespace di VGE

namespace SignalType { // Namespace del tipo di segnale

// Tipo del segnale
enum {

	CHANGE_DIRECTION = 700, // SEGNALE DI CAMBIO DELLA DIREZIONE
	CHANGE_SPEED, 			// SEGNALE DI CAMBIO DELLA VELOCITA'
};

}; // Chiudo il namespace del tipo di segnale

namespace EventType { // Namespace del tipo dell'evento

// Tipo dell'evento
enum {

	SET_SPEED = 700,	// CAMBIA LA VELOCITA' DELL'OGGETTO
	MOVE_LEFT,			// MUOVE L'OGGETTO A SINISTRA
	MOVE_UP,			// MUOVE L'OGGETTO IN ALTO
	MOVE_RIGHT,			// MUOVE L'OGGETTO A DESTRA
	MOVE_DOWN,			// MUOVE L'OGGETTO IN BASSO
	SHOW_OBJ_MESSAGE,	// MOSTRA UN MESSAGGIO CON LA FACCIA DELL'OGGETTO
};

}; // Chiudo il namespace del tipo dell'evento

class Object : public Sprite {

	/* OGGETTO GENERICO */

public:

	// Direzione del giocatore
	typedef enum {

		DIRECTION_LEFT,		// SINISTRA
		DIRECTION_UP,		// SU
		DIRECTION_RIGHT,	// DESTRA
		DIRECTION_DOWN,		// GIU'

	} Direction;

	// Metodi costruttore e distruttore
	Object( const std::string &path );
	Object( const std::string &path, const Types::Size2D_u size_ );
	Object( const Image &image );
	Object( const Image &image, const Types::Size2D_u size_ );

	virtual ~Object();

	// Muove l'oggetto
	virtual void MovePosition( Types::Float x, Types::Float y );
	virtual void MovePosition( Types::Float x, Types::Float y, Types::Bool single_direction );

	// Imposta la direzione dell'oggetto
	virtual void SetDirection( Direction value );
	// Ritorno la direzione dell'oggetto
	virtual Direction GetDirection() const;

	// Imposta la velocità dell'oggetto
	virtual void SetSpeed( Types::Float value );
	// Ritorno la velocità dell'oggetto
	virtual Types::Float GetSpeed() const;

	// Muove l'oggetto a sinistra
	virtual void MoveLeft();
	virtual void MoveLeft( Types::Float value );

	// Muove l'oggetto in alto
	virtual void MoveUp();
	virtual void MoveUp( Types::Float value );

	// Muove l'oggetto a destra
	virtual void MoveRight();
	virtual void MoveRight( Types::Float value );

	// Muove l'oggetto in basso
	virtual void MoveDown();
	virtual void MoveDown( Types::Float value );

	// Mette l'oggetto nello stato inattivo
	virtual void SetIdle();

	// Imposta il messaggio dell'oggetto
	void SetMessage( const std::wstring &string );
	// Ritorna il messaggio dell'oggetto
	const std::wstring &GetMessage() const;

	// Imposta l'immagine faccia dell'oggetto
	void SetFace( Image *image );
	// Ritorna l'immagine faccia dell'oggetto
	Image *GetFace() const;

	// Imposta l'immagine dell'ombra
	void SetShadow( Image *image );
	// Ritorna l'immagine dell'ombra
	Image *GetShadow() const;

	// Invia un segnale all'oggetto
	virtual void SendSignal( Types::Int type, Entity *other );

	// Avvia un evento dell'oggetto
	virtual Types::Bool SendEvent( Event *event, Entity *other );

	// Disegna la direzione dell'oggetto
	virtual void DrawDirection( const Types::Point2D &offset ) const;

	// Disegna l'ombra dell'oggetto
	virtual void DrawShadow( const Types::Point2D &offset, Color::RGBA8 blend ) const;

	// Disegna l'oggetto sullo schermo
	virtual void Draw( const Types::Point2D &offset, Color::RGBA8 blend ) const;


	/* Metodi di costruzione */

	// Costruttore da nodo XML
	Object( const Xml *node );

	// Estrae le caratteristiche dell'oggetto
	void ExtractObjFeatures( const Xml *node );

	// Estrae l'evento dalla lista
	virtual void ExtractEvent( const Xml *node, const wchar_t *type, std::vector< wchar_t *> &values );

	// Scrive le informazioni dell'oggetto in un file xml
	virtual void WriteInfo( Utf8 *stream ) const;

	// Scrive l'evento dell'oggetto
	virtual Types::Bool WriteEvent( Utf8 *stream, Event *event ) const;


	/* SEGNALI */

	// Ritorna l'istanza del segnale di cambio della direzione
	sigc::signal< void, Direction, Object * > &SignalDirection();

	// Ritorna l'istanza del segnale di cambio della velocità
	sigc::signal< void, Types::Float, Object * > &SignalSpeed();

	// Ritorna l'istanza del segnale di movimento per passo
	sigc::signal< void, Direction, Types::Float, Object * > &SignalStep();

protected:

	// Aggiorna la profondità dell'oggetto
	void UpdateDepth();

	// Direzione dell'oggetto
	Direction direction;

	// Valocità dell'oggetto
	Types::Float speed;

	// Messaggio dell'oggetto
	std::wstring message;

	// Immagine faccia dell'oggetto
	Image *face;

	// Ombra dell'oggetto
	Image *shadow;


	/* SEGNALI */

	// Segnale di cambio della solidità
	sigc::signal< void, Object::Direction, Object * > signal_direction;

	// Segnale di cambio della velocità
	sigc::signal< void, Types::Float, Object * > signal_speed;

	// Segnale di cambio della velocità
	sigc::signal< void, Object::Direction, Types::Float, Object * > signal_step;
};

}; // Chiudo il namespace di VGE

#endif
