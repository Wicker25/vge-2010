/* 
    Title --- particle-system-inl.hpp

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


#ifndef VGE_PARTICLE_SYSTEM_INL_HPP
#define VGE_PARTICLE_SYSTEM_INL_HPP

#include "vge/particle-system.hpp"

namespace VGE { // Namespace di VGE

inline void
ParticleSystem::SetModel( ParticleSystem::Model model ) {

	// Imposto il modello del sistema particellare
	this->system_model = model;

	// Controllo se il modello scelto è la fiamma
	if ( model == FLAME_MODEL ) {

		// Modifico la direzione del flusso
		this->SetStreamDirection( 90.0f );
	}
}

inline ParticleSystem::Model
ParticleSystem::GetModel() const {

	// Ritorno il modello del sistema particellare
	return this->system_model;
}

inline void
ParticleSystem::SetParticleEntity( Entity *entity ) {

	// Imposto l'entità della particella
	this->particle_entity = entity;

	// Verifico i parametri inseriti
	if ( entity != NULL ) {

		// Scollego l'entità all'engine
		entity->SetEngine( NULL );

		// Scollego l'entità alla scena
		entity->SetScene( NULL );
	}
}

inline Entity *
ParticleSystem::GetParticleEntity() const {

	// Ritorno l'entità della particella
	return this->particle_entity;
}

inline void
ParticleSystem::SetParticleNumber( Types::Uint num ) {

	// Imposto il numero delle particelle
	this->partition_number = num;
}

inline Types::Uint
ParticleSystem::GetParticleNumber() const {

	// Ritorno il numero della particella
	return this->partition_number;
}

inline void
ParticleSystem::SetParticleLife( Types::Float life ) {

	// Imposto la durata vitale delle particelle (in millisecondi)
	this->particle_life = life;
}

inline Types::Float
ParticleSystem::GetParticleLife() const {

	// Ritorno la durata vitale delle particelle (in millisecondi)
	return this->particle_life;
}

inline void
ParticleSystem::SetParticleFrequency( Types::Float frequency ) {

	// Imposto la frequenza delle particelle (in millisecondi)
	this->particle_frequency[0] = 0.0f;
	this->particle_frequency[1] = frequency;
}

inline Types::Float
ParticleSystem::GetParticleFrequency() const {

	// Ritorno la frequenza delle particelle (in millisecondi)
	return this->particle_frequency[1];
}

inline void
ParticleSystem::SetParticleSpeed( Types::Float speed ) {

	// Imposto la velocità delle particelle
	this->particle_speed = speed;
}

inline Types::Float
ParticleSystem::GetParticleSpeed() const {

	// Ritorno la velocità delle particelle
	return this->particle_speed;
}

inline void
ParticleSystem::SetStreamDirection( Types::Float value ) {

	// Calcola la nuova direzione
	value = fmod( (float) value, 360.0f );

	// Imposto la direzione del flusso di particelle
	this->stream_direction = ( value >= 0.0f ) ? value : ( 360.0f + value );
}

inline Types::Float
ParticleSystem::GetStreamDirection() const {

	// Ritorno la direzione del flusso di particelle
	return this->stream_direction;
}

inline void
ParticleSystem::SetStreamWidth( Types::Uint width ) {

	// Imposto la larghezza del flusso di particelle
	this->stream_width = width;
}

inline Types::Uint
ParticleSystem::GetStreamWidth() const {

	// Ritorno la larghezza del flusso di particelle
	return this->stream_width;
}

inline void
ParticleSystem::SetExplosionRange( Types::Float from, Types::Float to ) {

	// Imposta l'intervallo delle direzioni delle particelle nel modello ad esplosione
	from = fmod( (float) from, 360.0f );
	to = fmod( (float) to, 360.0f );

	this->explosion_range[0] = ( from >= 0.0f ) ? from : ( 360.0f + from );
	this->explosion_range[1] = ( to >= 0.0f ) ? to : ( 360.0f + to );
}

inline void
ParticleSystem::GetExplosionRange( Types::Float *from, Types::Float *to ) const {

	// Ritorna l'intervallo delle direzioni delle particelle nel modello ad esplosione
	if ( from != NULL )	*from	= this->explosion_range[0];
	if ( to != NULL )	*to		= this->explosion_range[1];
}

inline void
ParticleSystem::SetGravityDirection( Types::Float direction ) {

	// Imposto la direzione della gravità nel sistema particellare 
	this->gravity_direction = fmod( (float) direction, 360.0f );
}

inline Types::Float
ParticleSystem::GetGravityDirection() const {

	// Ritorno la direzione della gravità nel sistema particellare 
	return this->gravity_direction;
}

inline void
ParticleSystem::SetGravityAcceleration( Types::Float acceleration ) {

	// Imposto l'accelerazione della gravità nel sistema particellare 
	this->gravity_acceleration = acceleration;
}

inline Types::Float
ParticleSystem::GetGravityAcceleration() const {

	// Ritorno l'accelerazione della gravità nel sistema particellare 
	return this->gravity_acceleration;
}

inline Types::Float
ParticleSystem::GetColorTransition( Color::RGBA8 *from, Color::RGBA8 *to ) const {

	// Controllo la validità dei parametri
	if ( from != NULL )

		// Ritorno il colore iniziale della transizione
		*from = this->fade_color[0];

	// Controllo la validità dei parametri
	if ( to != NULL )

		// Ritorno il colore finale della transizione
		*to = this->fade_color[1];

	// Ritorno il valore di simmetria della transizione
	return this->fade_color_symmetry;
}

inline void
ParticleSystem::SetScaleTransition( Types::Float from, Types::Float to, Types::Float symmetry ) {

	// Imposto la transizione della scala delle particelle
	this->scaling_size[0] = ( from < 0.0f ) ? 0.0f : from;
	this->scaling_size[1] = ( to < 0.0f ) ? 0.0f : to;

	// Imposto il valore di simmetria della transizione
	this->scaling_symmetry = VMIN( VMAX( symmetry, 0.0f ), 1.0f );
}

inline Types::Float
ParticleSystem::GetScaleTransition( Types::Float *from, Types::Float *to ) const {

	// Ritorno la transizione della scala delle particelle
	if ( from != NULL )	*from	= this->scaling_size[0];
	if ( to != NULL )	*to		= this->scaling_size[1];

	// Ritorno il valore di simmetria della transizione
	return this->scaling_symmetry;
}

inline void
ParticleSystem::SetActive( Types::Bool state ) {

	// Modifico lo stato del sistema particellare
	this->active = state;
}

inline Types::Bool
ParticleSystem::GetActive() const {

	// Ritorno lo stato del sistema particellare
	return this->active;
}

}; // Chiudo il namespace di VGE

#endif
