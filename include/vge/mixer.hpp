/* 
    Title --- mixer.hpp

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


#ifndef VGE_MIXER_HPP
#define VGE_MIXER_HPP

#include <iostream>
#include <cstring>
#include <string>
#include <vector>

#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>

#include <ogg/ogg.h>
#include <vorbis/vorbisfile.h>

#include "vge/consts.hpp"
#include "vge/types.hpp"
#include "vge/error.hpp"
#include "vge/math.hpp"

#define EXT_WAV "wav"
#define EXT_OGG "ogg"

namespace VGE { // Namespace di VGE

class Mixer {

	/* GESTORE DEGLI EFFETTI SONORI */

public:

	// Modello della distanza dei suoni
	typedef enum {

		NO_DISTANCE					= AL_NONE,
		INVERSE_DISTANCE			= AL_INVERSE_DISTANCE,
		INVERSE_DISTANCE_CLAMPED	= AL_INVERSE_DISTANCE_CLAMPED,
		LINEAR_DISTANCE				= AL_LINEAR_DISTANCE,
		LINEAR_DISTANCE_CLAMPED		= AL_LINEAR_DISTANCE_CLAMPED,
		EXPONENT_DISTANCE			= AL_EXPONENT_DISTANCE,
		EXPONENT_DISTANCE_CLAMPED	= AL_EXPONENT_DISTANCE_CLAMPED,

	} DistanceModel;

	// Struttura di un suono
	typedef struct {

		ALuint buffer;		// Id del buffer
		ALuint source;		// Id del sorgente
		ALenum format;		// Formato
		ALfloat rate;		// Frequenza

		Types::Uint8 *data;	// Buffer dei dati
		ALsizei size;	// Dimensione del buffer dei dati

	} Sound;

	// Ridefinizione del tipo lista
	typedef std::vector< Sound > SoundList;

	// Inizializza il gestore degli effetti sonori
	void Init();

	// Deinizializza il gestore degli effetti sonori
	void Close();

	// Imposta la posizione dell'ascoltatore
	void SetListenerPosition( const Types::Point2D &point );
	// Ritorna la posizione dell'ascoltatore
	void GetListenerPosition( Types::Point2D &point );

	// Imposta il modello della distanza dei suoni
	void SetDistanceModel( Mixer::DistanceModel model );
	// Ritorna il modello della distanza dei suoni
	Mixer::DistanceModel GetDistanceModel();

	// Carica in memoria un effetto sonoro
	Types::Uint LoadSound( const std::string &path );

	// Imposta il volume del suono
	void SetSoundVolume( Types::Uint sound, Types::Float volume );
	// Ritorna il volume del suono
	Types::Float GetSoundVolume( Types::Uint sound );

	// Imposta la velocità di riproduzione del suono
	void SetSoundSpeed( Types::Uint sound, Types::Float speed );
	// Ritorna la velocità di riproduzione del suono
	Types::Float GetSoundSpeed( Types::Uint sound );

	// Imposta la ciclicità del suono
	void SetSoundLoop( Types::Uint sound, Types::Bool value );
	// Ritorna la ciclicità del suono
	Types::Bool GetSoundLoop( Types::Uint sound );

	// Imposta i parametri della distanza del suono
	void SetSoundDistance( Types::Uint sound,	Types::Float reference_distance,
										Types::Float rolloff_factor,
										Types::Float max_distance );
	// Ritorna i parametri della distanza del suono
	void GetSoundDistance( Types::Uint sound,	Types::Float *reference_distance,
										Types::Float *rolloff_factor,
										Types::Float *max_distance ) const;

	// Imposta la posizione di un suono
	void SetSoundPosition( Types::Uint sound, const Types::Point2D &point );
	// Ritorno la posizione di un suono
	void GetSoundPosition( Types::Uint sound, Types::Point2D &point );
	// Disimposta la posizione di un suono
	void UnsetSoundPosition( Types::Uint sound );

	// Riproduce un effetto sonoro
	void PlaySound( Types::Uint sound );
	void PlaySound( Types::Uint sound, Types::Bool loop );
	// Ferma temporaneamente la riproduzione di un effetto sonoro
	void PauseSound( Types::Uint sound );
	// Ferma la riproduzione di un effetto sonoro
	void StopSound( Types::Uint sound );
	// Riavvolgo la riproduzione di un effetto sonoro
	void RewindSound( Types::Uint sound );

	// Aggiorna i suoni in riproduzione
	Types::Bool Update();

protected:

	// Carica un file formato "wav"
	void LoadWAV( const std::string &path, Sound *sound );

	// Carica un file formato "ogg"
	void LoadOGG( const std::string &path, Sound *sound );

	// Lista degli effetti sonori
	SoundList sound_list;

	// Posizione dell'ascoltatore
	Types::Point2D listener_position;

	// Modello della distanza dei suoni
	DistanceModel distance_model;
};

}; // Chiudo il namespace di VGE

#endif
