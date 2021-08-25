/* 
    Title --- mixer-inl.hpp

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


#ifndef VGE_MIXER_INL_HPP
#define VGE_MIXER_INL_HPP

#include "vge/mixer.hpp"

namespace VGE { // Namespace di VGE

inline void
Mixer::SetListenerPosition( const Types::Point2D &point ) {

	// Imposto la posizione dell'ascoltatore
	alListener3f( AL_POSITION, point.x, point.y, 0.0f );
}

inline void
Mixer::GetListenerPosition( Types::Point2D &point ) {

	// Variabile di appoggio
	Types::Float z;

	// Ritorno la posizione dell'ascoltatore
	alGetListener3f( AL_POSITION, &point.x, &point.y, &z );
}

inline void
Mixer::SetDistanceModel( Mixer::DistanceModel model ) {

	// Imposto il modello della distanza dei suoni
	this->distance_model = model;
}

inline Mixer::DistanceModel
Mixer::GetDistanceModel() {

	// Ritorno il modello della distanza dei suoni
	return this->distance_model;
}

inline void
Mixer::SetSoundPosition( Types::Uint sound, const Types::Point2D &point ) {

	// Controllo la validità dell'indice
	if ( sound < (Types::Uint) this->sound_list.size() ) {

		// Imposto la posizione del suono
		alSourcei( this->sound_list[sound].source, AL_SOURCE_RELATIVE, AL_FALSE );
		alSource3f( this->sound_list[sound].source, AL_POSITION, point.x, point.y, 0.0f );
	}
}

inline void
Mixer::GetSoundPosition( Types::Uint sound, Types::Point2D &point ) {

	// Variabile di appoggio
	Types::Float z;

	// Controllo la validità dell'indice
	if ( sound < (Types::Uint) this->sound_list.size() )

		// Ritorno la posizione del suono
		alGetSource3f( this->sound_list[sound].source, AL_POSITION, &point.x, &point.y, &z );
}

inline void
Mixer::UnsetSoundPosition( Types::Uint sound ) {

	// Controllo la validità dell'indice
	if ( sound < (Types::Uint) this->sound_list.size() ) {

		// Disimposto la posizione del suono
		alSourcei( this->sound_list[sound].source, AL_SOURCE_RELATIVE, AL_TRUE );
		alSource3f( this->sound_list[sound].source, AL_POSITION, 0.0f, 0.0f, 0.0f );
	}
}

inline void
Mixer::SetSoundVolume( Types::Uint sound, Types::Float volume ) {

	// Controllo la validità dell'indice
	if ( sound < (Types::Uint) this->sound_list.size() )

		// Imposto il volume del suono
		alSourcef( this->sound_list[sound].source, AL_GAIN, volume );
}

inline Types::Float
Mixer::GetSoundVolume( Types::Uint sound ) {

	// Valore del volume corrente
	Types::Float volume;

	// Controllo la validità dell'indice
	if ( sound < (Types::Uint) this->sound_list.size() )

		// Ricavo il volume corrente
		alGetSourcef( this->sound_list[sound].source, AL_GAIN, &volume );

	// Ritorno il volume del suono
	return volume;
}

inline void
Mixer::SetSoundSpeed( Types::Uint sound, Types::Float speed ) {

	// Controllo la validità dell'indice
	if ( sound < (Types::Uint) this->sound_list.size() )

		// Imposto la velocità di riproduzione del suono
		alSourcef( this->sound_list[sound].source, AL_PITCH, speed );
}

inline Types::Float
Mixer::GetSoundSpeed( Types::Uint sound ) {

	// Valore della velocità corrente
	Types::Float speed;

	// Controllo la validità dell'indice
	if ( sound < (Types::Uint) this->sound_list.size() )

		// Ricavo la velocità corrente
		alGetSourcef( this->sound_list[sound].source, AL_PITCH, &speed );

	// Ritorno la velocità di riproduzione del suono
	return speed;
}

inline void
Mixer::SetSoundLoop( Types::Uint sound, Types::Bool value ) {

	// Controllo la validità dell'indice
	if ( sound < (Types::Uint) this->sound_list.size() )

		// Imposto la velocità di riproduzione del suono
		alSourcei( this->sound_list[sound].source, AL_LOOPING, value );
}

inline Types::Bool
Mixer::GetSoundLoop( Types::Uint sound ) {

	// Valore della velocità di riproduzione del suono
	ALint value;

	// Controllo la validità dell'indice
	if ( sound < (Types::Uint) this->sound_list.size() ) {

		// Ricavo la velocità di riproduzione del suono
		alGetSourcei( this->sound_list[sound].source, AL_LOOPING, &value );
	}

	// Ritorno la velocità di riproduzione del suono
	return (Types::Bool) value;
}

inline void
Mixer::SetSoundDistance( Types::Uint sound,	Types::Float reference_distance,
										Types::Float rolloff_factor,
										Types::Float max_distance ) {

	// Controllo la validità dell'indice
	if ( sound < (Types::Uint) this->sound_list.size() ) {

		// Imposto i parametri della distanza del suono
		alSourcef( this->sound_list[sound].source, AL_REFERENCE_DISTANCE, reference_distance );
		alSourcef( this->sound_list[sound].source, AL_ROLLOFF_FACTOR, rolloff_factor );
		alSourcef( this->sound_list[sound].source, AL_MAX_DISTANCE, max_distance );
	}
}

inline void
Mixer::GetSoundDistance( Types::Uint sound,	Types::Float *reference_distance,
										Types::Float *rolloff_factor,
										Types::Float *max_distance ) const {

	// Controllo la validità dell'indice
	if ( sound < (Types::Uint) this->sound_list.size() ) {

		// Ritorno i parametri della distanza del suono
		alGetSourcef( this->sound_list[sound].source, AL_REFERENCE_DISTANCE, reference_distance );
		alGetSourcef( this->sound_list[sound].source, AL_ROLLOFF_FACTOR, rolloff_factor );
		alGetSourcef( this->sound_list[sound].source, AL_MAX_DISTANCE, max_distance );
	}
}

inline void
Mixer::PlaySound( Types::Uint sound ) {

	// Riproduco un suono
	this->PlaySound( sound, false );
}

inline void
Mixer::PauseSound( Types::Uint sound ) {

	// Controllo la validità dell'indice
	if ( sound < (Types::Uint) this->sound_list.size() )

		// Fermo temporaneamente la riproduzione di un suono
		alSourcePause( this->sound_list[sound].source );
}

inline void
Mixer::StopSound( Types::Uint sound ) {

	// Controllo la validità dell'indice
	if ( sound < (Types::Uint) this->sound_list.size() )

		// Fermo la riproduzione del suono
		alSourceStop( this->sound_list[sound].source );
}

inline void
Mixer::RewindSound( Types::Uint sound ) {

	// Controllo la validità dell'indice
	if ( sound < (Types::Uint) this->sound_list.size() )

		// Riavvolgo la riproduzione di un suono
		alSourceRewind( this->sound_list[sound].source );
}

}; // Chiudo il namespace di VGE

#endif
