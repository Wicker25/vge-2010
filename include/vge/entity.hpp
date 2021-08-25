/* 
    Title --- entity.hpp

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


#ifndef VGE_ENTITY_HPP
#define VGE_ENTITY_HPP

#include <iostream>
#include <list>

#include "vge/consts.hpp"
#include "vge/types.hpp"
#include "vge/error.hpp"
#include "vge/math.hpp"
#include "vge/global.hpp"

#include "vge/xml.hpp"

#include "vge/color.hpp"

#include "vge/interfaces/i-programmable.hpp"

#include "vge/bounding-area.hpp"
#include "vge/input-manager.hpp"

#include "vge/widgets/font.hpp"

// Macro per il casting
#define VGE_ENTITY( x )		( (VGE::Entity *) x )

namespace VGE { // Namespace di VGE

namespace SignalType { // Namespace del tipo di segnale

// Tipo del segnale
enum {

	CHANGE_VISIBILITY = 550,		// SEGNALE DI CAMBIO DELLA VISIBILITA'
	CHANGE_FIXING,					// SEGNALE DI CAMBIO DELLA POSIZIONE RISPETTO ALLO CAMERA
	CHANGE_SENSIBILITY,				// SEGNALE DI CAMBIO DELLA SENSIBILITA'
	MOTION,							// SEGNALE DI MOVIMENTO
};

}; // Chiudo il namespace del tipo di segnale

namespace EventType { // Namespace del tipo dell'evento

// Tipo dell'evento
enum {

	SET_VISIBLE = 550,	// CAMBIA LA VISIBILITA' DELL'ENTITA'
	SET_FIXED,			// FISSA/STACCA L'ENTITA' SULLA CAMERA
	SET_SENSIBLE,		// CAMBIA LA SENSIBILITA' DELL'ENTITA'
	SET_POSITION,		// CAMBIA LA POSIZIONE DELL'ENTITA' (ASSOLUTA)
	MOVE_POSITION,		// CAMBIA LA POSIZIONE DELL'ENTITA' (RELATIVA)
	SHOW_MESSAGE,		// MOSTRA UN MESSAGGIO DI SISTEMA
	WAIT_DIALOG,		// ASPETTA LA CHIUSURA DEL MESSAGGIO DI SISTEMA
	WAIT_SECONDS,		// ASPETTA ALCUNI SECONDI
};

}; // Chiudo il namespace del tipo dell'evento

// Prototipi
class Player;
class Viewer;
class Scene;
class Engine;

class Entity : public InterfaceProgrammable {

	/* ENTITA' DEL GIOCO */

public:

	// Maschere delle entità
	typedef enum {

		ENTITY_MASK,
		PARTICLE_SYSTEM_MASK,
		WIDGET_MASK,
		CONTAINER_MASK,
		CONTAINER_DERIVED_MASK,
		IMAGE_MASK,
		SPRITE_MASK,
		OBJECT_MASK,
		CHARACTER_MASK,
		PLAYER_MASK,

	} MaskType;

	// Metodi costruttore e distruttore
	Entity( const Types::Point3D &position );
	virtual ~Entity();

	// Ritorna l'identificativo del tipo di entità
	MaskType GetMask() const;

	// Collega l'istanza al gestore del gioco
	virtual void SetEngine( Engine *engine );
	// Ritorna il puntatore al gestore del gioco
	virtual Engine *GetEngine() const;

	// Collega l'istanza al gestore della scena
	virtual void SetScene( Scene *scene );
	// Ritorna il puntatore al gestore della scena
	virtual Scene *GetScene() const;

	// Imposta il nome dell'entità
	virtual void SetName( const std::wstring &name );
	// Ritorna il nome dell'entità
	virtual std::wstring GetName() const;

	// Modifica la posizione dell'entità (assoluta)
	virtual void SetPosition( const Types::Point2D &point );
	virtual void SetPosition( const Types::Point3D &point );
	// Ritorna la posizione dell'entità (assoluta)
	virtual const Types::Point3D &GetPosition() const;
	// Modifica la posizione dell'entità (relativa)
	virtual void MovePosition( Types::Float x, Types::Float y, Types::Float z );

	// Modifica il centro dell'immagine
	virtual void SetCenter( const Types::Point2D &point );
	// Ritorna il centro dell'immagine
	virtual const Types::Point2D &GetCenter() const;

	// Ritorna l'area di visibilità
	BoundingArea &GetVisibilityArea();
	const BoundingArea &GetVisibilityArea() const;

	// Modifica la visibilità dell'entità
	virtual void SetVisible( Types::Bool state );
	// Controlla la visibilità dell'entità
	virtual Types::Bool GetVisible() const;

	// Imposta la posizione dell'entità rispetto alla camera
	virtual void SetFixed( Types::Bool state );
	// Ritorna la posizione dell'entità rispetto alla camera
	virtual Types::Bool GetFixed() const;

	// Imposta la sensibilità dell'entità
	virtual void SetSensible( Types::Bool state );
	// Ritorna la sensibilità dell'entità
	virtual Types::Bool GetSensible() const;

	// Imposta la modalità di debug
	virtual void SetDebugMode( Types::Bool state );
	// Ritorna lo stato della modalità di debug
	virtual Types::Bool GetDebugMode() const;

	// Invia un segnale all'entità
	virtual void SendSignal( Types::Int type, Entity *other );

	// Avvia un evento dell'entità
	virtual Types::Bool SendEvent( Event *event, Entity *other );

	// Funzione di lavoro
	virtual void Update( Viewer *viewer, Player *player );

	// Disegna il centro dello sprite
	virtual void DrawCenter( const Types::Point2D &offset ) const;

	// Disegna l'area di visibilità
	virtual void DrawVisibilityArea( const Types::Point2D &offset ) const;

	// Disegna l'entità
	virtual void Draw( const Types::Point2D &offset, Color::RGBA8 blend ) const;


	/* Metodi di costruzione */

	// Costruttore da nodo XML
	Entity( const Xml *node );

	// Estrae il nome dell'entità
	void ExtractName( const Xml *node );

	// Estrae la posizione dell'entità
	void ExtractPosition( const Xml *node );

	// Estrae il centro dell'entità
	void ExtractCenter( const Xml *node );

	// Estrae i flags dell'entità
	void ExtractFlags( const Xml *node );

	// Estrae l'area di visibilità dell'entità
	void ExtractVisibilityArea( const Xml *node );

	// Estrae la lista degli eventi dell'entità
	virtual void ExtractEventList( const Xml *node );

	// Estrae l'evento dalla lista
	virtual void ExtractEvent( const Xml *node, const wchar_t *type, std::vector< wchar_t *> &values );

	// Salva l'entità in un file xml
	void Save( Utf8 *stream ) const;

	// Scrive le informazioni dell'entità in un file xml
	virtual void WriteInfo( Utf8 *stream ) const;

	// Scrive le informazioni sull'area dell'entità
	virtual void WriteBoundingArea( Utf8 *stream ) const;

	// Scrive la lista degli eventi dell'entità
	virtual void WriteEventList( Utf8 *stream ) const;

	// Scrive l'evento dell'entità
	virtual Types::Bool WriteEvent( Utf8 *stream, Event *event ) const;


	/* SEGNALI */

	// Ritorna l'istanza del segnale di cambio della visibilità
	sigc::signal< void, Types::Bool, Entity * > &SignalVisibility();

	// Ritorna l'istanza del segnale di cambio della posizione rispetto alla camera
	sigc::signal< void, Types::Bool, Entity * > &SignalFixing();

	// Ritorna l'istanza del segnale di cambio della sensibilità
	sigc::signal< void, Types::Bool, Entity * > &SignalSensibility();

	// Ritorna l'istanza del segnale di movimento
	sigc::signal< void, Types::Point3D, Entity * > &SignalMotion();

protected:

	// Imposta l'identificativo del tipo di entità
	void SetMask( MaskType mask );

	// Identificativo del tipo di entità
	MaskType mask;

	// Puntatore al gestore del gioco
	Engine *parent_engine;

	// Puntatore al gestore della scena
	Scene *parent_scene;

	// Nome dell'entità
	std::wstring e_name;

	// Posizione
	Types::Point3D position;

	// Centro
	Types::Point2D center;

	// Area di visibilità
	BoundingArea visibility_area;

	// Flags di stato dell'entità
	Types::Bool visible;
	Types::Bool fixed;
	Types::Bool sensibility;

	// Flag della modalità di debug
	Types::Bool debug_mode;


	/* SEGNALI */

	// Segnale di cambio della visibilità
	sigc::signal< void, Types::Bool, Entity * > signal_visibility;

	// Segnale cambio della posizione rispetto alla camera
	sigc::signal< void, Types::Bool, Entity * > signal_fixing;

	// Segnale di cambio della sensibilità
	sigc::signal< void, Types::Bool, Entity * > signal_sensibility;

	// Segnale di movimento
	sigc::signal< void, Types::Point3D, Entity * > signal_motion;
};

// Ridefinizione del tipo lista
typedef std::list< Entity * > EntityList;

}; // Chiudo il namespace di VGE

#endif
