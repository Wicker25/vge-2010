/* 
    Title --- particle-system-maker.cpp

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


#ifndef VGE_PARTICLE_SYSTEM_MAKER_CPP
#define VGE_PARTICLE_SYSTEM_MAKER_CPP

#include "vge/particle-system.hpp"

#include "vge/utf8.hpp"
#include "vge/inline/utf8-inl.hpp"

#include "vge/xml.hpp"
#include "vge/inline/xml-inl.hpp"

#include "vge/color.hpp"
#include "vge/inline/color-inl.hpp"

#include "vge/interfaces/i-programmable.hpp"
#include "vge/interfaces/inline/i-programmable-inl.hpp"

#include "vge/entity.hpp"
#include "vge/inline/entity-inl.hpp"

#include "vge/particle-system.hpp"
#include "vge/inline/particle-system-inl.hpp"

#include "vge/maker.hpp"
#include "vge/inline/maker-inl.hpp"

#include "vge/inline/particle-system-inl.hpp"

namespace VGE { // Namespace di VGE

ParticleSystem::ParticleSystem( const Xml *node ): Entity( node ) {

	// Imposto l'identificativo del tipo di entità
	this->SetMask( PARTICLE_SYSTEM_MASK );

	// Imposto il modello del sistema particellare
	this->SetModel( ParticleSystem::STREAM_MODEL );

	// Imposto l'entità particella del sistema
	this->SetParticleEntity( NULL );

	// Imposto il numero delle particelle
	this->SetParticleNumber( 30 );

	// Imposto la frequenza delle particelle (in millisecondi)
	this->SetParticleFrequency( 50.0f );

	// Imposta la durata vitale delle particelle
	this->SetParticleLife( 500.0f );

	// Imposto la velocità delle particelle
	this->SetParticleSpeed( 2.5f );

	// Imposto la larghezza del flusso di particelle
	this->SetStreamWidth( 20 );

	// Imposto la direzione del flusso di particelle
	this->SetStreamDirection( 90.0f );

	// Imposta l'intervallo delle direzioni delle particelle nel modello ad esplosione
	this->SetExplosionRange( 0.0f, 359.0f );

	// Imposto la direzione della gravità nel sistema particellare 
	this->SetGravityDirection( 270.0f );

	// Imposto l'accelerazione della gravità nel sistema particellare 
	this->SetGravityAcceleration( 0.0f );

	// Imposto la transizione del colore delle particelle
	this->SetColorTransition(	Color::Make( 255, 255, 255, 255 ),
								Color::Make( 255, 255, 255, 255 ), 0.0f );

	// Imposto la transizione della scala delle particelle
	this->SetScaleTransition( 1.0f, 1.0f, 0.5f );

	// Imposto lo stato del sistema particellare
	this->SetActive( true );

	/* Costruzione del sistema particellare */

	// Estraggo le informazioni sulle particelle
	this->ExtractParticles( node );

	// Estraggo le informazioni sul flusso di particelle
	this->ExtractParticleStream( node );

	// Estraggo le informazioni sul flusso di particelle nel modello ad esplosione
	this->ExtractParticleExplosion( node );

	// Estraggo le informazioni sulla gravità nel sistema particellare
	this->ExtractParticleGravity( node );

	// Estraggo le informazioni sulla transizione del colore nel sistema particellare
	this->ExtractParticleColorTransition( node );

	// Estraggo le informazioni sulla transizione della scala nel sistema particellare
	this->ExtractParticleScaleTransition( node );

	/* ==================================== */
}

// <particles entity="@fire_particle" model="flame" number="35" frequency="30.0" speed="3.5" life="400.0" />

void
ParticleSystem::ExtractParticles( const Xml *node ) {

	// Cerco il nodo "particles"
	Xml particles_node = node->Child( T_PARTICLES );

	// Controllo l'esistenza del nodo
	if ( particles_node.Exist() ) {

		// Puntatore all'attributo
		wchar_t *attr = NULL;

		// Cerco l'entità particella
		if ( particles_node.GetAttribute( A_ENTITY, &attr ) ) {

			// Controllo la presenza del carattere di riferimento
			if ( attr[0] == L'@' ) {

				// Entità di riferimento
				Entity *ref = VGE::Global::GetEntity( attr + 1 );

				// Controllo l'esistenza dell'entità di riferimento
				if ( ref != NULL ) {

					if ( ref->GetMask() >= Entity::IMAGE_MASK )

						// Imposto l'entità particella del sistema
						this->SetParticleEntity( ref );

						// Log di lavoro
						printf( " Entity:\t%ls\n", attr );

				} else {

					// Comunico l'errore
					fprintf( stderr, ENTITY_NOT_DEFINED_W, WARNING, particles_node.GetRow(), attr + 1 );
				}

			} else {

				// Comunico l'errore
				fprintf( stderr, ENTITY_NOT_DEFINED_W, WARNING, particles_node.GetRow(), attr );
			}
		} else {

			// Comunico l'errore
			fprintf( stderr, NO_ATTRIBUTE_FOUND_W, BROKE, particles_node.GetRow(), A_ENTITY );
		}

		// Cerco il modello del sistema particellare
		if ( particles_node.GetAttribute( A_MODEL, &attr ) ) {

			// Memorizzo il modello del sistema particellare
			if ( wcscasecmp( attr, V_STREAM_MODEL ) == 0 )

				// Imposto il modello del sistema particellare
				this->SetModel( ParticleSystem::STREAM_MODEL );

			else if ( wcscasecmp( attr, V_EXPLOSION_MODEL ) == 0 )

				// Imposto il modello del sistema particellare
				this->SetModel( ParticleSystem::EXPLOSION_MODEL );

			else if ( wcscasecmp( attr, V_FLAME_MODEL ) == 0 )

				// Imposto il modello del sistema particellare
				this->SetModel( ParticleSystem::FLAME_MODEL );
		}

		// Cerco il numero di particelle
		if ( particles_node.GetAttribute( A_NUMBER, &attr ) )

			// Imposta il numero delle particelle
			this->SetParticleNumber( (Types::Uint) wcstoul( attr, NULL, 10 ) );

		// Cerco la frequenza delle particelle
		if ( particles_node.GetAttribute( A_FREQUENCY, &attr ) )

			// Imposto la frequenza delle particelle (in millisecondi)
			this->SetParticleFrequency( (Types::Float) wcstof( attr, NULL ) );

		// Cerco la velocità delle particelle
		if ( particles_node.GetAttribute( A_SPEED, &attr ) )

			// Imposto la velocità delle particelle
			this->SetParticleSpeed( (Types::Float) wcstof( attr, NULL ) );

		// Cerco la vita delle particelle
		if ( particles_node.GetAttribute( A_LIFE, &attr ) )

			// Imposta la durata vitale delle particelle
			this->SetParticleLife( (Types::Float) wcstof( attr, NULL ) );

		// Cerco lo stato del sistema particellare
		if ( particles_node.GetAttribute( A_ACTIVE, &attr ) )

			// Modifico lo stato del sistema particellare
			this->SetActive( ( wcscasecmp( attr, V_TRUE ) == 0 ) );
	}
}

// <stream width="40" direction="90.0" />

void
ParticleSystem::ExtractParticleStream( const Xml *node ) {

	// Cerco il nodo "stream"
	Xml particle_stream_node = node->Child( T_STREAM );

	// Controllo l'esistenza del nodo
	if ( particle_stream_node.Exist() ) {

		// Puntatore all'attributo
		wchar_t *attr = NULL;

		// Cerco la dimensione del flusso di particelle
		if ( particle_stream_node.GetAttribute( A_WIDTH, &attr ) ) {

			// Imposto la dimensione del flusso di particelle
			this->SetStreamWidth( (Types::Uint) wcstoul( attr, NULL, 10 ) );
		}

		// Cerco la direzione del flusso di particelle
		if ( particle_stream_node.GetAttribute( A_DIRECTION, &attr ) ) {

			// Imposto  la direzione del flusso di particelle
			this->SetStreamDirection( (Types::Float) wcstof( attr, NULL ) );
		}
	}
}

// <explosion range="0.0,75.0" />

void
ParticleSystem::ExtractParticleExplosion( const Xml *node ) {

	// Cerco il nodo "explosion"
	Xml particle_explosion_node = node->Child( T_EXPLOSION );

	// Controllo l'esistenza del nodo
	if ( particle_explosion_node.Exist() ) {

		// Puntatore all'attributo
		wchar_t *attr = NULL;

		// Cerco l'intervallo
		if ( particle_explosion_node.GetAttribute( A_RANGE, &attr ) ) {

			// Intervallo delle direzioni delle particelle nel modello ad esplosione
			Types::Float from, to;

			// Estraggo l'intervallo
			if ( swscanf( attr, L"%f,%f", &from, &to ) == 2 ) {

				// Imposto l'intervallo delle direzioni delle particelle nel modello ad esplosione
				this->SetExplosionRange( from, to );

			} else {

				// Comunico l'errore
				fprintf( stderr, WRONG_SYNTAX_OF_W, WARNING, particle_explosion_node.GetRow(), A_RANGE );
			}
		}
	}
}

// <gravity direction="270.0" acceleration="0.5" />

void
ParticleSystem::ExtractParticleGravity( const Xml *node ) {

	// Cerco il nodo "gravity"
	Xml particle_gravity_node = node->Child( T_GRAVITY );

	// Controllo l'esistenza del nodo
	if ( particle_gravity_node.Exist() ) {

		// Puntatore all'attributo
		wchar_t *attr = NULL;

		// Cerco la direzione della gravita
		if ( particle_gravity_node.GetAttribute( A_DIRECTION, &attr ) ) {

			// Imposto la direzione della gravita
			this->SetGravityDirection( (Types::Float) wcstof( attr, NULL ) );
		}

		// Cerco l'accelerazione gravitazionale
		if ( particle_gravity_node.GetAttribute( A_ACCELERATION, &attr ) ) {

			// Imposto l'accelerazione gravitazionale
			this->SetGravityAcceleration( (Types::Float) wcstof( attr, NULL ) );
		}
	}
}

// <color_transition start="FF0000FF" end="40100030" symmetry="0.55" />

void
ParticleSystem::ExtractParticleColorTransition( const Xml *node ) {

	// Cerco il nodo "color_transition"
	Xml particle_color_node = node->Child( T_COLOR_TRANSITION );

	// Controllo l'esistenza del nodo
	if ( particle_color_node.Exist() ) {

		// Puntatore all'attributo
		wchar_t *attr = NULL;

		// Colori
		Color::RGBA8 start, end;

		// Cerco il colore iniziale delle particelle
		if ( particle_color_node.GetAttribute( A_START, &attr ) ) {

			// Converto la stringa nel colore
			if ( Maker::StringToColor( attr, &start ) ) {

				// Cerco il colore finale delle particelle
				if ( particle_color_node.GetAttribute( A_END, &attr ) ) {

					// Converto la stringa nel colore
					if ( Maker::StringToColor( attr, &end ) ) {

						// Cerco la simmetria
						if ( particle_color_node.GetAttribute( A_SYMMETRY, &attr ) ) {

							// Imposto la transizione del colore del sistema particellare
							this->SetColorTransition( start, end, (Types::Float) wcstof( attr, NULL ) );
						}

					} else {

						// Comunico l'errore
						fprintf( stderr, WRONG_SYNTAX_OF_W, BROKE, particle_color_node.GetRow(), A_START );
					}
				}

			} else {

				// Comunico l'errore
				fprintf( stderr, WRONG_SYNTAX_OF_W, BROKE, particle_color_node.GetRow(), A_END );
			}
		}
	}
}

// <scale_transition start="2.0" end="1.0" symmetry="0.5" />

void
ParticleSystem::ExtractParticleScaleTransition( const Xml *node ) {

	// Cerco il nodo "scale_transition"
	Xml particle_scale_node = node->Child( T_SCALE_TRANSITION );

	// Controllo l'esistenza del nodo
	if ( particle_scale_node.Exist() ) {

		// Puntatore all'attributo
		wchar_t *attr = NULL;

		// Cerco la scala iniziale delle particelle
		if ( particle_scale_node.GetAttribute( A_START, &attr ) ) {

			// Scala iniziale
			Types::Float start = (Types::Float) wcstof( attr, NULL );

			// Cerco la scala finale delle particelle
			if ( particle_scale_node.GetAttribute( A_END, &attr ) ) {

				// Scala iniziale
				Types::Float end = (Types::Float) wcstof( attr, NULL );

				// Cerco la simmetria
				if ( particle_scale_node.GetAttribute( A_SYMMETRY, &attr ) ) {

					// Imposto la transizione della scala del sistema particellare
					this->SetScaleTransition( start, end, (Types::Float) wcstof( attr, NULL ) );
				}
			}
		}
	}
}

void
ParticleSystem::ExtractEvent( const Xml *node, const wchar_t *type, std::vector< wchar_t *> &values ) {

	// Colore
	Color::RGBA8 color[2];

	// Chiama la funzione della classe genitore
	Entity::ExtractEvent( node, type, values );

	// Modifica della posizione rispetto alla camera
	if ( wcscasecmp( type, V_EVENT_SET_ACTIVE ) == 0 ) {

		// Controllo il numero dei parametri
		if ( values.size() >= 1 ) {

			// Aggiungo l'evento alla lista
			this->AddEvent( EventType::SET_ACTIVE, wcscasecmp( values[0], V_TRUE ) == 0 );
		}

	// Modifica della direzione del flusso
	} else if ( wcscasecmp( type, V_EVENT_SET_STREAM_DIRECTION ) == 0 ) {

		// Controllo il numero dei parametri
		if ( values.size() >= 1 ) {

			// Aggiungo l'evento alla lista
			this->AddEvent( EventType::SET_STREAM_DIRECTION, wcstof( values[0], NULL ) );
		}

	// Modifica della direzione del flusso (progressiva)
	} else if ( wcscasecmp( type, V_EVENT_TRANSIENT_STREAM_DIRECTION ) == 0 ) {

		// Controllo il numero dei parametri
		if ( values.size() >= 2 ) {

			// Aggiungo l'evento alla lista
			this->AddEvent(	EventType::TRANSIENT_STREAM_DIRECTION,
								wcstof( values[0], NULL ),
								wcstof( values[1], NULL ) );
		}

	// Modifica la transizione del colore
	} else if ( wcscasecmp( type, V_EVENT_SET_COLOR_TRANSITION ) == 0 ) {

		// Controllo il numero dei parametri
		if ( values.size() >= 3 ) {

			// Converto la stringa nel colore
			if ( Maker::StringToColor( values[0], &color[0] ) ) {

				// Converto la stringa nel colore
				if ( Maker::StringToColor( values[1], &color[1] ) ) {

					// Aggiungo l'evento alla lista
					this->AddEvent(	EventType::SET_COLOR_TRANSITION,
									color[0], color[1], wcstof( values[2], NULL ) );

				} else {

					// Comunico l'errore
					fprintf( stderr, WRONG_SYNTAX_OF_W, BROKE, node->GetRow(), A_COLOR );	
				}

			} else {

				// Comunico l'errore
				fprintf( stderr, WRONG_SYNTAX_OF_W, BROKE, node->GetRow(), A_COLOR );	
			}
		}
	}
}

// <particles entity="@fire_particle" model="flame" number="35" frequency="30.0" speed="3.5" life="400.0" active="true" />
// <stream width="40" direction="90.0" />
// <explosion range="0.0,75.0" />
// <gravity direction="270.0" acceleration="0.0" />
// <color_transition start="RGBA(255,170,5,255)" end="RGBA(40,10,0,30)" symmetry="0.55" />
// <scale_transition start="2.0" end="1.0" symmetry="0.5" />

void
ParticleSystem::WriteInfo( Utf8 *stream ) const {

	// Scrivo le informazioni dell'entità padre
	Entity::WriteInfo( stream );

	// Modello del sistema
	const wchar_t *model = NULL;

	// Controllo lo stato dell'animazione
	switch ( this->GetModel() ) {

		case STREAM_MODEL: { model = V_STREAM_MODEL; break; }

		case EXPLOSION_MODEL: { model = V_EXPLOSION_MODEL; break; }

		case FLAME_MODEL: { model = V_FLAME_MODEL; break; }

		default: break;
	}

	// Ricavo l'entità del sistema particellare
	const wchar_t *entity = ( this->GetParticleEntity() != NULL ) ? \
						this->GetParticleEntity()->GetName().c_str() : NULL;

	// Scrivo il blocco "particles"
	stream->Write(	L"\t<%ls %ls=\"@%ls\" %ls=\"%ls\" %ls=\"%u\" %ls=\"%.2f\" "
					L"%ls=\"%.2f\" %ls=\"%.2f\" %ls=\"%ls\" />\n",

			T_PARTICLES,
			A_ENTITY, entity,
			A_MODEL, model,
			A_NUMBER, this->GetParticleNumber(),
			A_FREQUENCY, this->GetParticleFrequency(),
			A_SPEED, this->GetParticleSpeed(),
			A_LIFE, this->GetParticleLife(),
			A_ACTIVE, ( this->GetActive() ) ? V_TRUE : V_FALSE
	);

	// Controllo se il modello supporta il prossimo tag
	if ( this->GetModel() == STREAM_MODEL || this->GetModel() == FLAME_MODEL ) {

		// Scrivo il blocco "particles"
		stream->Write( L"\t<%ls %ls=\"%u\" %ls=\"%.2f\" />\n",

				T_STREAM,
				A_WIDTH, this->GetStreamWidth(),
				A_DIRECTION, this->GetStreamDirection()
		);

	// Controllo se il modello supporta il prossimo tag
	} else if ( this->GetModel() == EXPLOSION_MODEL ) {

		// Scrivo il blocco "particles"
		stream->Write( L"\t<%ls %ls=\"%.2f,%.2f\" />\n",

				T_EXPLOSION,
				A_RANGE, this->explosion_range[0], this->explosion_range[0]
		);
	}

	// Scrivo il tag "gravity"
	stream->Write( L"\t<%ls %ls=\"%.2f\" %ls=\"%.2f\" />\n",

			T_GRAVITY,
			A_DIRECTION, this->GetGravityDirection(),
			A_ACCELERATION, this->GetGravityAcceleration()
	);

	// Scrivo il tag "color_transition"
	stream->Write( L"\t<%ls %ls=\"%08X\" %ls=\"%08X\" %ls=\"%.2f\" />\n",

			T_COLOR_TRANSITION,
			A_START, Color::Make( this->fade_color[0] ),
			A_END, Color::Make( this->fade_color[1] ),
			A_SYMMETRY, this->fade_color_symmetry
	);

	// Scrivo il tag "scale_transition"
	stream->Write( L"\t<%ls %ls=\"%.2f\" %ls=\"%.2f\" %ls=\"%.2f\" />\n\n",

			T_SCALE_TRANSITION,
			A_START, this->scaling_size[0],
			A_END, this->scaling_size[1],
			A_SYMMETRY, this->scaling_symmetry
	);
}

Types::Bool
ParticleSystem::WriteEvent( Utf8 *stream, Event *event ) const {

	// Chiamo la funzione della classe genitore
	Types::Bool found = Entity::WriteEvent( stream, event );

	// Controllo che l'evento non sia già stato salvato
	if ( !found ) {

		// Controllo il tipo dell'evento
		switch ( event->type ) {

			// Cambio dello stato del sistema
			case EventType::SET_ACTIVE: {

				stream->Write( L"\t\t<%ls %ls=\"%ls\" %ls0=\"%ls\" />\n",

						T_EVENT,
						A_TYPE, V_EVENT_SET_ACTIVE,
						A_VALUE, ( event->arg0[1] ) ? V_TRUE : V_FALSE
				);

				break;
			}

			// Modifica della direzione del flusso di particelle
			case EventType::SET_STREAM_DIRECTION: {

				stream->Write( L"\t\t<%ls %ls=\"%ls\" %ls0=\"%.2f\" />\n",

						T_EVENT,
						A_TYPE, V_EVENT_SET_STREAM_DIRECTION,
						A_VALUE, event->arg0[1]
				);

				break;
			}

			// Modifica della direzione del flusso di particelle (progressiva)
			case EventType::TRANSIENT_STREAM_DIRECTION: {

				stream->Write( L"\t\t<%ls %ls=\"%ls\" %ls0=\"%.2f\" %ls1=\"%.2f\" />\n",

						T_EVENT,
						A_TYPE, V_EVENT_TRANSIENT_STREAM_DIRECTION,
						A_VALUE, event->arg0[1],
						A_VALUE, event->arg1[1]
				);

				break;
			}

			// Modifica della transizione del colore
			case EventType::SET_COLOR_TRANSITION: {

				stream->Write( L"\t\t<%ls %ls=\"%ls\" %ls0=\"%08X\" %ls1=\"%08X\" %ls2=\"%.2f\" />\n",

						T_EVENT,
						A_TYPE, V_EVENT_SET_COLOR_TRANSITION,
						A_VALUE, Color::Make( event->color[0] ),
						A_VALUE, Color::Make( event->color[1] ),
						A_VALUE, event->arg0[0]
				);

				break;
			}

			default: {

				found = false;
				break;
			}
		}
	}

	return found;
}

}; // Chiudo il namespace di VGE

#endif
