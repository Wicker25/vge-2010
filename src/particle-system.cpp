/* 
    Title --- particle-system.cpp

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


#ifndef VGE_PARTICLE_SYSTEM_CPP
#define VGE_PARTICLE_SYSTEM_CPP

#include "vge/particle-system.hpp"

#include "vge/color.hpp"
#include "vge/inline/color-inl.hpp"

#include "vge/designer.hpp"
#include "vge/inline/designer-inl.hpp"

#include "vge/interfaces/i-ruotable.hpp"
#include "vge/interfaces/inline/i-ruotable-inl.hpp"

#include "vge/interfaces/i-colorable.hpp"
#include "vge/interfaces/inline/i-colorable-inl.hpp"

#include "vge/engine.hpp"
#include "vge/inline/engine-inl.hpp"

#include "vge/inline/particle-system-inl.hpp"

namespace VGE { // Namespace di VGE

ParticleSystem::ParticleSystem(	Entity *entity, Model model, Types::Uint num,
								Types::Float frequency, Types::Float speed, Types::Float life ) :

	Entity( Types::Point3D( 0.0f, 0.0f, 0.0f ) ) {

	// Imposto l'identificativo del tipo di entità
	this->SetMask( PARTICLE_SYSTEM_MASK );

	// Imposto il modello del sistema particellare
	this->SetModel( model );

	// Imposto l'entità particella del sistema
	this->SetParticleEntity( entity );

	// Imposto il numero delle particelle
	this->SetParticleNumber( num );

	// Imposto la frequenza delle particelle (in millisecondi)
	this->SetParticleFrequency( frequency );

	// Imposta la durata vitale delle particelle
	this->SetParticleLife( life );

	// Imposto la velocità delle particelle
	this->SetParticleSpeed( speed );

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

	// Imposto l'area di visibilità rettangolare
	this->GetVisibilityArea().SetRectangle( Types::Rect_f( -9999, -9999, 9999, 9999 ) );
}

ParticleSystem::~ParticleSystem() {

}

void
ParticleSystem::SetColorTransition( Color::RGBA8 from, Color::RGBA8 to, Types::Float symmetry ) {

	// Imposto il colore iniziale della transizione
	this->fade_color[0] = from;

	// Imposto il colore finale della transizione
	this->fade_color[1] = to;

	// Imposto il valore di simmetria della transizione
	this->fade_color_symmetry = VMIN( VMAX( symmetry, 0.0f ), 1.0f );
}

Types::Bool
ParticleSystem::SendEvent( Event *event, Entity *other ) {

	// Flag di controllo
	Types::Bool end_event = false;

	// Controlla il tipo di evento
	switch ( event->type ) {

		// Imposto lo stato del sistema particellare
		case EventType::SET_ACTIVE: {

			this->SetActive( (Types::Bool) event->arg0[0] );
			end_event = true;
			break;
		}

		// Imposto la direzione del flusso di particelle
		case EventType::SET_STREAM_DIRECTION: {

			// Correggo l'angolo di destinazione
			if ( event->arg0[0] > 360.0f )
				event->arg0[0] = fmod( (float) event->arg0[0], 360.0f );

			this->SetStreamDirection( event->arg0[0] );
			end_event = true;
			break;
		}

		// Imposto la rotazione dell'oggetto (progressiva)
		case EventType::TRANSIENT_STREAM_DIRECTION: {

			// Correggo l'angolo di destinazione
			if ( event->arg0[0] > 360.0f )
				event->arg0[0] = fmod( (float) event->arg0[0], 360.0f );

			// Ricavo l'angolo attuale
			Types::Float angle = this->GetStreamDirection();

			// Calcolo il nuovo angolo
			if ( VABS_DIFF( angle, event->arg0[0] ) > VABS( event->arg1[0] ) )

				angle += event->arg1[0];
			else
				angle = event->arg0[0];

			// Imposto la nuova angolazione
			this->SetStreamDirection( angle );

			if ( event->arg0[0] == angle ) end_event = true;
			break;
		}

		// Imposto la transizione del colore
		case EventType::SET_COLOR_TRANSITION: {

			// Imposto la transizione del colore
			this->SetColorTransition( event->color[0], event->color[1], event->arg0[0] );
			end_event = true;
			break;
		}

		default: break;
	}

	// Avvia il gestore degli eventi
	if ( !end_event )
		end_event = Entity::SendEvent( event, other );

	return end_event;
}

void
ParticleSystem::EmitStreamParticles() {

	// Iteratore
	Types::Uint i = 0;

	// Emetto le particelle seguendo il modello a flusso 
	for ( ; i < this->GetParticleNumber(); i++ ) {

		// Calcolo la posizione della nuova particella
		const Types::Float rnd = (Types::Float) ( rand() % ( this->GetStreamWidth() * 1000 ) ) / 1000.0f - \
								 ( this->GetStreamWidth() / 2.0f );

		const Types::Point2D pos(
										this->position.x + sin( VTORAD( this->GetStreamDirection() ) ) * rnd,
										this->position.y + cos( VTORAD( this->GetStreamDirection() ) ) * rnd
								);

		// Creo la struttura della nuova particella
		Particle particle = {
								pos, this->GetParticleLife(),

								Types::Point2D(

									-cos( VTORAD( this->GetStreamDirection() ) ) * this->GetParticleSpeed(),
									-sin( VTORAD( this->GetStreamDirection() ) ) * this->GetParticleSpeed()
								)
							};

		// Aggiungo la particella alla lista
		this->particle_list.push_back( particle );
	}
}

void
ParticleSystem::EmitExplosionParticles() {

	// Iteratore
	Types::Uint i = 0;

	// Emetto le particelle seguendo il modello ad esplosione 
	for ( ; i < this->GetParticleNumber(); i++ ) {

		// Calcolo l'angolo della nuova particella
		const Types::Float range = ( this->explosion_range[1] - this->explosion_range[0] );
		const Types::Float angle =	range / 1000.0f * (Types::Float) ( rand() % 1000 ) + \
									this->explosion_range[0];

		// Calcolo la posizione della nuova particella
		const Types::Point2D pos(
									this->position.x + cos( VTORAD( angle ) ),
									this->position.y + sin( VTORAD( angle ) )
								);

		// Creo la struttura della nuova particella
		Particle particle = {
								pos, this->GetParticleLife(),

								Types::Point2D(

									-cos( VTORAD( angle ) ) * this->GetParticleSpeed(),
									-sin( VTORAD( angle ) ) * this->GetParticleSpeed()
								)
							};

		// Aggiungo la particella alla lista
		this->particle_list.push_back( particle );
	}
}

void
ParticleSystem::EmitFlameParticles() {

	// Iteratore
	Types::Uint i = 0;

	// Emetto le particelle seguendo il modello a fiamma 
	for ( ; i < this->GetParticleNumber(); i++ ) {

		// Calcolo la posizione della nuova particella
		const Types::Float angle =	(Types::Float) ( rand() % 360000 ) / 1000.0f;

		const Types::Float radius =	(Types::Float) ( rand() % ( this->GetStreamWidth() * 1000 ) ) / 1000.0f - \
									( (Types::Float) this->GetStreamWidth() / 2.0f );

		const Types::Point2D pos(
										this->position.x + cos( VTORAD( angle ) ) * radius,
										this->position.y + sin( VTORAD( angle ) ) * radius
								);

		// Creo un concentramento di particelle nella parte centrale della fiamma
		const Types::Float life = VMAX( 1.0f - pow(	( pos.x - this->position.x ) / \
										(Types::Float) this->GetParticleNumber(), 2.0f ), 0.0f );

		// Implemento le scintille
		const Types::Bool spark = ( ( rand() % 1000 ) % 200 == 0 );

		// Creo la struttura della nuova particella
		Particle particle = {
								pos,	this->GetParticleLife() * life + \
										( spark * (Types::Float) this->GetParticleLife() / 2.0f ),

								Types::Point2D( 0.0f, - this->GetParticleSpeed() )
							};

		// Aggiungo la particella alla lista
		this->particle_list.push_back( particle );
	}
}

void
ParticleSystem::UpdateParticles() {

	// Ricavo gli FPS dal disegnatore
	Types::Uint fps_limit = this->GetEngine()->GetDesigner().GetFpsLimit();

	// Iteratori
	ParticleList::iterator iter = this->particle_list.begin();
	ParticleList::const_iterator end = this->particle_list.end();

	// Aggiorno la posizione delle particelle
	for ( ; iter != end; iter++ ) {

		// Ricavo la posizione della particella
		Types::Point2D &pos = iter->position;

		// Controllo se la particella è ancora viva
		if ( iter->life >= 0.0f ) {

			// Decremento la durata vitale della particella
			iter->life -= ( 1000.0f / (Types::Float) fps_limit );

			// Muovo la particella
			pos.x += iter->direction.x;
			pos.y += iter->direction.y;

			iter->direction.x += cos( VTORAD( this->gravity_direction ) ) * this->gravity_acceleration;
			iter->direction.y -= sin( VTORAD( this->gravity_direction ) ) * this->gravity_acceleration;

		// Elimino la particella morta
		} else this->particle_list.erase( iter++ );

		// Controllo se la particella è uscita dal limite rettangolare
		const Types::Rect< Types::Float > &area = this->GetVisibilityArea().GetRectangle();

		if (	( pos.x < area.left || pos.x > area.right ) ||
				( pos.y < area.top || pos.y > area.bottom ) ) {

			// Elimino la particella morta
			this->particle_list.erase( iter++ );
		}
	}
}

void
ParticleSystem::Update( Viewer *viewer, Player *player ) {

	SetDebugMode(true);

	// Avvio la funzione di lavoro superiore
	Entity::Update( viewer, player );

	// Controllo se l'engine è stato impostato
	if ( this->GetEngine() != NULL ) {

		// Ricavo gli FPS dal disegnatore
		Types::Uint fps_limit = this->GetEngine()->GetDesigner().GetFpsLimit();

		// Decremento il conto alla rovesca per la nuova generazione
		this->particle_frequency[0] -= ( 1000.0f / (Types::Float) fps_limit );

		// Controllo se è il momento di creare la nuova generazione
		if ( this->GetActive() && this->particle_frequency[0] < 0.0f ) {

			// Riavvio il conto alla rovescia per la nuova generazione
			this->particle_frequency[0] = this->particle_frequency[1];

			// Controllo il modello del sistema particellare
			switch ( this->GetModel() ) {

				// Modello a flusso di particelle
				case STREAM_MODEL: {

					// Emetto le particelle seguendo il modello a flusso 
					this->EmitStreamParticles();
					break;
				}

				// Modello ad esplosione di particelle
				case EXPLOSION_MODEL: {

					// Emetto le particelle seguendo il modello ad esplosione 
					this->EmitExplosionParticles();
					break;
				}

				// Modello a fiamma di particelle
				case FLAME_MODEL: {

					// Emetto le particelle seguendo il modello a fiamma 
					this->EmitFlameParticles();
					break;
				}
			}
		}

		// Aggiorno le particelle del sistema 
		this->UpdateParticles();

		// Controllo che sia stata definita l'entità particellare
		if ( this->GetParticleEntity() != NULL ) {

			// Collego l'entità all'engine
			this->GetParticleEntity()->SetEngine( this->GetEngine() );

			// Collego l'entità alla scena
			this->GetParticleEntity()->SetScene( this->GetScene() );

			// Disabilito la modalità di debug dall'entità particellare
			this->GetParticleEntity()->SetDebugMode( false );

			// Avvio la funzione di lavoro dell'entità particellare
			this->GetParticleEntity()->Update( viewer, player );
		}
	}
}

void
ParticleSystem::DrawSystem( const Types::Point2D &offset ) const {

	// Ricavo il disegnatore principale
	const Designer &designer = this->GetEngine()->GetDesigner();

	// Calcolo la posizione
	Types::Point2D pos = this->GetPosition() + offset;

	// Controllo il modello particellare
	if ( this->GetModel() != EXPLOSION_MODEL ) {

		// Imposto il colore
		designer.SetColor( Color::Make( 20, 220, 20, 255 ) );

		// Imposto lo spessore della linea
		designer.SetLineWidth( 1 );

		// Disegno l'area del flusso di particelle
		designer.DrawCircle( this->GetPosition() + offset, (Types::Float) this->GetStreamWidth() / 2.0f );


		// Imposto il colore
		designer.SetColor( Color::Make( 255, 190, 40, 255 ) );

		// Calcolo il raggio della direzione in base alla velocità delle particelle
		const Types::Float power = ( this->GetParticleSpeed() * 10.0f );

		// Disegna la direzione del flusso di particelle
		designer.DrawLine(	Types::Point2D( 0.0f, 0.0f ),
							Types::Point2D( -cos( VTORAD( this->GetStreamDirection() ) ) * power,
											-sin( VTORAD( this->GetStreamDirection() ) ) * power ),
							this->GetPosition() + offset );

	} else {

		// Imposto il colore
		designer.SetColor( Color::Make( 120, 255, 20, 255 ) );

		// Imposto lo spessore della linea
		designer.SetLineWidth( 2 );

		// Disegno l'angolo del flusso di particelle
		designer.DrawCurve(	this->GetPosition() + offset, this->explosion_range[0], this->explosion_range[1], 25.0f );
	}

	// Calcolo il raggio della direzione della gravità
	const Types::Float gravity = ( this->gravity_acceleration * 75.0f );

	// Imposto il colore della linea
	designer.SetColor( Color::Make( 160, 20, 255, 255 ) );

	// Imposto lo spessore della linea
	designer.SetLineWidth( 2 );

	// Disegno la direzione della gravità
	designer.DrawLine(	Types::Point2D( 0.0f, 0.0f ),
						Types::Point2D(	-cos( VTORAD( this->gravity_direction ) ) * gravity,
										-sin( VTORAD( this->gravity_direction ) ) * gravity ),
						this->GetPosition() + offset );
}

void
ParticleSystem::Draw( const Types::Point2D &offset, Color::RGBA8 blend ) const {

	// Controllo che sia stato definita l'entità particellare
	if ( this->GetParticleEntity() != NULL ) {

		// Iteratori
		ParticleList::const_reverse_iterator iter = this->particle_list.rbegin();
		ParticleList::const_reverse_iterator end = this->particle_list.rend();

		// Disegno le particelle
		for ( ; iter != end; iter++ ) {

			// Ricavo la posizione della particella
			const Types::Point2D &pos = iter->position;

			// Imposto la posizione dell'entità particellare
			this->GetParticleEntity()->SetPosition( pos );

			// Controllo che l'entità particellare sia colorabile // this->fade_color_symmetry > 0.0f 
			if ( this->GetParticleEntity()->GetMask() >= IMAGE_MASK ) {

				// Converto l'entità particellare
				Image *image = VGE_IMAGE( this->GetParticleEntity() );

				// Calcolo la percentuale di vitalità
				const Types::Float eps = ( iter->life / this->GetParticleLife() );

				// Calcolo la percentuale di transizione del colore
				const Types::Float color = VMIN( VMAX( eps / this->fade_color_symmetry - 0.5f, 0.0f ), 1.0f );

				// Modifico il colore dell'entità particellare
				image->SetColor( Color::BlendAlpha( this->fade_color[0], this->fade_color[1], color ) );

				// Calcolo la percentuale di transizione della scala
				const Types::Float diff = ( this->scaling_size[1] - this->scaling_size[0] );
				Types::Float scale = ( 1.0f - eps + this->scaling_symmetry - 0.5f ) * diff;

				if ( this->scaling_size[1] > this->scaling_size[0] )

					scale = VMIN(	scale + this->scaling_size[0] + this->scaling_symmetry,
									this->scaling_size[1] );
				else
					scale = VMIN(	scale + this->scaling_size[0] + this->scaling_symmetry,
									this->scaling_size[0] );

				// Modifico la scala dell'entità particellare
				image->SetScale( Types::Size2D_f( scale, scale ) );
			}

			// Disegno l'entità particellare
			this->GetParticleEntity()->Draw( offset, blend );
		}
	}

	// Funzione di disegno dell'entità
	Entity::Draw( offset, blend );

	// Controllo se la modalità di debug è attiva
	if ( this->GetDebugMode() ) {

		// Disegna i dati sul flusso di particelle
		this->DrawSystem( offset );
	}
}

}; // Chiudo il namespace di VGE

#endif
