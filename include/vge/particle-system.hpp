/* 
    Title --- particle-system.hpp

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


#ifndef VGE_PARTICLE_SYSTEM_HPP
#define VGE_PARTICLE_SYSTEM_HPP

#include <iostream>
#include <list>

#include "vge/consts.hpp"
#include "vge/types.hpp"
#include "vge/error.hpp"
#include "vge/math.hpp"

#include "vge/color.hpp"

#include "vge/entity.hpp"

// Macro per il casting
#define VGE_PARTICLE_SYSTEM( x )		( (ParticleSystem *) x )

namespace VGE { // Namespace di VGE

namespace EventType { // Namespace del tipo dell'evento

// Tipo dell'evento
enum {

	SET_ACTIVE = 800,			// CAMBIA LO STATO DEL SISTEAM PARTICELLARE
	SET_STREAM_DIRECTION,		// CAMBIA LA DIREZIONE DEL FLUSSO DI PARTICELLE
	TRANSIENT_STREAM_DIRECTION,	// CAMBIA LA DIREZIONE DEL FLUSSO DI PARTICELLE (PROGRESSIVA)
	SET_COLOR_TRANSITION,		// CAMBIA LA TRANSIZIONE DEL COLORE
};

}; // Chiudo il namespace del tipo dell'evento


class ParticleSystem : public Entity {

	/* SISTEMA PARTICELLARE */

public:

	// Modello del sistema particellare
	typedef enum {

		STREAM_MODEL,		// Modello a flusso di particelle
		EXPLOSION_MODEL,	// Modello ad esplosione di particelle
		FLAME_MODEL,		// Modello a fiamma

	} Model;

	// Struttura di una particella
	typedef struct {

		Types::Point2D position;	// Posizione
		Types::Float life;			// Vitalità in secondi
		Types::Point2D direction;	// Direzione

	} Particle;

	// Ridefinizione del tipo lista
	typedef std::list< Particle > ParticleList;

	// Metodi costruttore e distruttore
	ParticleSystem(	Entity *entity, Model model, Types::Uint num, Types::Float frequency,
					Types::Float speed, Types::Float life );
	virtual ~ParticleSystem();

	// Imposta il modello del sistema particellare
	void SetModel( Model model );
	// Ritorna il modello del sistema particellare
	Model GetModel() const;

	// Imposta l'entità della particella
	void SetParticleEntity( Entity *entity );
	// Ritorna l'entità della particella
	Entity *GetParticleEntity() const;

	// Imposta il numero delle particelle
	void SetParticleNumber( Types::Uint num );
	// Ritorna il numero delle particelle
	Types::Uint GetParticleNumber() const;

	// Imposta la durata vitale delle particelle (in millisecondi)
	void SetParticleLife( Types::Float life );
	// Ritorna la durata vitale delle particelle (in millisecondi)
	Types::Float GetParticleLife() const;

	// Imposta la frequenza delle particelle (in millisecondi)
	void SetParticleFrequency( Types::Float frequency );
	// Ritorna la frequenza delle particelle (in millisecondi)
	Types::Float GetParticleFrequency() const;

	// Imposta la velocità delle particelle
	void SetParticleSpeed( Types::Float speed );
	// Ritorna la velocità delle particelle
	Types::Float GetParticleSpeed() const;

	// Imposta la direzione del flusso di particelle
	void SetStreamDirection( Types::Float value );
	// Ritorna la direzione del flusso di particelle
	Types::Float GetStreamDirection() const;

	// Imposta la larghezza del flusso di particelle
	void SetStreamWidth( Types::Uint width );
	// Ritorna la larghezza del flusso di particelle
	Types::Uint GetStreamWidth() const;

	// Imposta l'intervallo delle direzioni delle particelle nel modello ad esplosione
	void SetExplosionRange( Types::Float from, Types::Float to );
	// Ritorna l'intervallo delle direzioni delle particelle nel modello ad esplosione
	void GetExplosionRange( Types::Float *from, Types::Float *to ) const;

	// Imposta la direzione della gravità nel sistema particellare 
	void SetGravityDirection( Types::Float direction );
	// Ritorna la direzione della gravità nel sistema particellare 
	Types::Float GetGravityDirection() const;

	// Imposta l'accelerazione della gravità nel sistema particellare 
	void SetGravityAcceleration( Types::Float acceleration );
	// Ritorna l'accelerazione della gravità nel sistema particellare 
	Types::Float GetGravityAcceleration() const;

	// Imposta la transizione del colore delle particelle
	void SetColorTransition( Color::RGBA8 from, Color::RGBA8 to, Types::Float symmetry );
	// Ritorna la transizione del colore delle particelle
	Types::Float GetColorTransition( Color::RGBA8 *from, Color::RGBA8 *to ) const;

	// Imposta la transizione della scala delle particelle
	void SetScaleTransition( Types::Float from, Types::Float to, Types::Float symmetry );
	// Ritorno la transizione della scala delle particelle
	Types::Float GetScaleTransition( Types::Float *from, Types::Float *to ) const;

	// Modifica lo stato del sistema particellare
	void SetActive( Types::Bool state );
	// Ritorna lo stato del sistema particellare
	Types::Bool GetActive() const;

	// Avvia un evento del sistema particellare
	virtual Types::Bool SendEvent( Event *event, Entity *other );

	// Funzione di lavoro
	virtual void Update( Viewer *viewer, Player *player );

	// Disegna i dati sul flusso di particelle
	virtual void DrawSystem( const Types::Point2D &offset ) const;

	// Disegna il sistema particellare sullo schermo
	virtual void Draw( const Types::Point2D &offset, Color::RGBA8 blend ) const;

	/* Metodi di costruzione */

	// Costruttore da nodo XML
	ParticleSystem( const Xml *node );

	// Estrae le informazioni sulle particelle
	void ExtractParticles( const Xml *node );
	
	// Estrae le informazioni sul flusso di particelle
	void ExtractParticleStream( const Xml *node );

	// Estrae le informazioni sul flusso di particelle nel modello ad esplosione
	void ExtractParticleExplosion( const Xml *node );

	// Estrae le informazioni sulla gravità nel sistema particellare
	void ExtractParticleGravity( const Xml *node );

	// Estrae le informazioni sulla transizione del colore nel sistema particellare
	void ExtractParticleColorTransition( const Xml *node );

	// Estrae le informazioni sulla transizione della scala nel sistema particellare
	void ExtractParticleScaleTransition( const Xml *node );

	// Estrae l'evento dalla lista
	virtual void ExtractEvent( const Xml *node, const wchar_t *type, std::vector< wchar_t *> &values );

	// Scrive le informazioni dell'entità in un file xml
	virtual void WriteInfo( Utf8 *stream ) const;

	// Scrive l'evento del sistema particellare
	virtual Types::Bool WriteEvent( Utf8 *stream, Event *event ) const;

private:

	// Emette le nuove particelle seguendo il modello a flusso 
	void EmitStreamParticles();

	// Emette le nuove particelle seguendo il modello ad esplosione 
	void EmitExplosionParticles();

	// Emette le nuove particelle seguendo il modello a fiamma 
	void EmitFlameParticles();

	// Aggiorna le particelle del sistema 
	void UpdateParticles();

	// Flag di stato
	Types::Bool active;

	// Modello del sistema particellare
	Model system_model;

	// Entità della particella
	Entity *particle_entity;

	// Lista delle particelle
	ParticleList particle_list;

	// Numero di particelle della nuova generazione
	Types::Uint partition_number;

	// Vita delle particelle in secondi
	Types::Float particle_life;

	// Conto alla rovescia per la nuova generazione
	Types::Float particle_frequency[2];

	// Velocità delle particelle
	Types::Float particle_speed;

	// Direzione del flusso di particelle
	Types::Float stream_direction;

	// Larghezza del flusso di particelle
	Types::Uint stream_width;

	// Types::Intervallo delle direzioni delle particelle nel modello ad esplosione
	Types::Float explosion_range[2];

	// Direzione della gravità
	Types::Float gravity_direction;

	// Accelerazione della gravità
	Types::Float gravity_acceleration;

	// Colore di transizione delle particelle
	Color::RGBA8 fade_color[2];

	// Simmetria della transizione di colore delle particelle
	Types::Float fade_color_symmetry;

	// Transizione della scala
	Types::Float scaling_size[2];

	// Simmetria della transizione della scala delle particelle
	Types::Float scaling_symmetry;
};

}; // Chiudo il namespace di VGE

#endif
