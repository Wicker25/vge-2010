/* 
    Title --- mixer.cpp

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


#ifndef VGE_MIXERS_CPP
#define VGE_MIXERS_CPP

#include "vge/mixer.hpp"
#include "vge/inline/mixer-inl.hpp"

namespace VGE { // Namespace di VGE

void
Mixer::Init() {

	// Log di lavoro
	printf( "<Mixer>\n" );

	// Inizializzo le OpenAL e le altre librerie connesse
	alutInit( NULL, 0 );

	// Errore
	ALenum error;

	// Controllo se ci sono stati errori
	if ( ( error = alutGetError() ) != AL_NO_ERROR ) {

		fprintf( stderr,	" %s: Could not initialize FreeALUT framework: %s\n",
							FATAL, alutGetErrorString( error ) );
		exit(1);
	}

	// Log di lavoro
	printf( " Loaded OpenAL v%s\n", alGetString( AL_VERSION ) );
	printf( " Loaded FreeALUT v%d.%d\n", alutGetMajorVersion(), alutGetMinorVersion() );

	// Imposto il modello della distanza dei suoni
	this->SetDistanceModel( LINEAR_DISTANCE_CLAMPED );

	// Log di lavoro
	printf( "</Mixer>\n" );
}

void
Mixer::Close() {

	// Iteratore
	Types::Uint i = 0;

	// Dealloco tutte i suon i caricati
	for ( ; i < (Types::Uint) this->sound_list.size(); i++ ) {

		// Fermo la riproduzione del suono
		alSourceStop( this->sound_list[i].source );

		// Dealloco la memoria del suono
		alDeleteSources( 1, &this->sound_list[i].source );
		alDeleteBuffers( 1, &this->sound_list[i].buffer );
	}

	// Deinizializzo le OpenAl e le altre librerie connesse
	alutExit();
}

void
Mixer::LoadWAV( const std::string &path, Sound *sound ) {

	// Carico il file formato "wav"
	sound->data = (Types::Uint8 *) alutLoadMemoryFromFile(	path.c_str(), &sound->format,
															&sound->size, &sound->rate );

	// Controllo se ci sono stati degli errori
	if ( alutGetError() != ALUT_ERROR_NO_ERROR ) {

		// Comunico l'errore
		fprintf( stderr, COULDNT_LOAD_FILE, FATAL, path.c_str() );

		// Deinizializzo il gestore degli effetti sonori
		this->Close();

		// Esco dal programma
		exit(1);
	}
}

void
Mixer::LoadOGG( const std::string &path, Sound *sound ) {

	// Apro il file del suono
	FILE *file = fopen( path.c_str(), "rb" );

	// Controllo che il file sia stato caricato corretamente
	if ( file == NULL ) {

		// Comunico l'errore
		fprintf( stderr, COULDNT_LOAD_FILE, FATAL, path.c_str() );

		// Deinizializzo il gestore degli effetti sonori
		this->Close();

		// Esco dal programma
		exit(1);
	}

	// Stream del file formato "ogg"
	OggVorbis_File stream;

	// Codice dell'errore
	int error;

	// Carico il file formato "ogg"
	error = ov_open( file, &stream, NULL, 0 );

	// Controllo che non ci siano stati errori
	if ( error < 0 ) {

		// Comunico l'errore
		fprintf( stderr, COULDNT_LOAD_FILE, FATAL, path.c_str() );

		// Chiudo il file del suono
		fclose( file );

		// Deinizializzo il gestore degli effetti sonori
		this->Close();

		// Esco dal programma
		exit(1);
	}

	// Ricavo le informazioni del file formato "ogg"
	vorbis_info *info		= ov_info( &stream, -1 );
	//vorbis_comment *comment	= ov_comment( &stream, -1 );

	// Memorizzo la frequenza
	sound->rate = info->rate;

	// Controllo il formato sonoro del file formato "ogg"
	if ( info->channels == 1 )

		sound->format = AL_FORMAT_MONO16;
	else
		sound->format = AL_FORMAT_STEREO16;

	// Buffer dei dati
	std::vector< Types::Uint8 > data;

	// Buffer di lettura
	char tmp[4096];

	// Byte letti dal buffer
	long length;

	do {

		length = ov_read( &stream, tmp, 4096, 0, 2, 1, NULL );
		data.insert( data.end(), tmp, tmp + length );

	} while ( length > 0 );

	// Copio la dimensione del buffer nella struttura del suono
	sound->size = data.size();

	// Copio il buffer nella struttura del suono
	sound->data = (Types::Uint8 *) malloc( sound->size * sizeof(Types::Uint8) );
	memcpy( sound->data, &data[0], sound->size );

	// Chiudo lo stream del file formato "ogg"
	ov_clear( &stream );
}

Types::Uint
Mixer::LoadSound( const std::string &path ) {

	// Creo la struttura del suono
	Sound sound;

	// Controllo l'estensione del file
	const char *ext = strrchr( path.c_str(), '.' ) + 1;

	// Carica il file formato "wav"
	if ( strncasecmp( ext, EXT_WAV, 3 ) == 0 )

		this->LoadWAV( path, &sound );

	// Carica il file formato "ogg"
	else if ( strncasecmp( ext, EXT_OGG, 3 ) == 0 )

		this->LoadOGG( path, &sound );

	// Alloco la memoria neccessaria
    alGenBuffers( 1, &sound.buffer );
    alGenSources( 1, &sound.source );

	// Carica il suono in memoria
	alBufferData(	sound.buffer, sound.format, sound.data,
					(ALsizei) sound.size, (ALsizei) sound.rate );

	alSourcei( sound.source, AL_BUFFER, sound.buffer );

	// Imposta le caratteristiche del suono
	alSourcef( sound.source, AL_ROLLOFF_FACTOR, 1.0f );
	alSourcef( sound.source, AL_REFERENCE_DISTANCE, 300.0f );
	alSourcef( sound.source, AL_MAX_DISTANCE, 500.0f );

	alSourcei( sound.source, AL_SOURCE_RELATIVE, AL_TRUE );
	alSource3f( sound.source, AL_POSITION, 0.0f, 0.0f, 0.0f );

	// Aggiungo la sounda di sottofondo alla lista
	this->sound_list.push_back( sound );

	// Ritorno l'indice del nuovo suono
	return (Types::Uint) ( this->sound_list.size() - 1 );
}

void
Mixer::PlaySound( Types::Uint sound, Types::Bool loop ) {

	// Controllo la validità dell'indice
	if ( sound < (Types::Uint) this->sound_list.size() ) {

		// Abilito/Disabilito la ciclicità del suono
		alSourcei( this->sound_list[sound].source, AL_LOOPING, loop );

		// Avvio la riproduzione del suono
	    alSourcePlay( this->sound_list[sound].source );

		// Controllo se ci sono stati degli errori
		if ( alGetError() != AL_NO_ERROR ) {

		    printf( "Can't play sound %u!\n", sound );
			exit(1);
		}
	}
}

Types::Bool
Mixer::Update() {

	// Stato di lavoro del gestore degli effetti sonori
	Types::Bool active = false;

	/*
	// Aggiorna i suoni in riproduzione
	int processed;
    alGetSourcei(source, AL_BUFFERS_PROCESSED, &processed);

    while(processed--)
    {
        ALuint buffer;
        
        alSourceUnqueueBuffers(source, 1, &buffer);

        active = stream(buffer);

        alSourceQueueBuffers(source, 1, &buffer);
    }
	*/

	// Ritorna lo stato di lavoro del gestore degli effetti sonori
	return active;
}

}; // Chiudo il namespace di VGE

#endif
