/* 
    Title --- entity.cpp

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


#ifndef VGE_ENTITY_CPP
#define VGE_ENTITY_CPP

#include "vge/entity.hpp"

#include "vge/global.hpp"
#include "vge/inline/global-inl.hpp"

#include "vge/designer.hpp"
#include "vge/inline/designer-inl.hpp"

#include "vge/interfaces/i-programmable.hpp"
#include "vge/interfaces/inline/i-programmable-inl.hpp"

#include "vge/input-manager.hpp"
#include "vge/inline/input-manager-inl.hpp"

#include "vge/bounding-area.hpp"
#include "vge/inline/bounding-area-inl.hpp"

#include "vge/color.hpp"
#include "vge/inline/color-inl.hpp"

#include "vge/maker.hpp"
#include "vge/inline/maker-inl.hpp"

#include "vge/viewer.hpp"
#include "vge/inline/viewer-inl.hpp"

#include "vge/scene.hpp"
#include "vge/inline/scene-inl.hpp"

#include "vge/engine.hpp"
#include "vge/inline/engine-inl.hpp"

#include "vge/widgets/font.hpp"
#include "vge/widgets/inline/font-inl.hpp"

#include "vge/inline/entity-inl.hpp"

namespace VGE { // Namespace di VGE

Entity::Entity( const Types::Point3D &position ) {

	// Aggiungo l'entità alla lista generale
	Global::Entities.push_back( this );

	// Imposto l'identificativo del tipo di entità
	this->SetMask( ENTITY_MASK );

	// Collego l'entità all'engine
	this->SetEngine( NULL );

	// Collego l'entità alla scene
	this->SetScene( NULL );

	// Costruisco il nome temporaneo dell'entità
	wchar_t _name[30]; swprintf( _name, 30, L"entity%zu", Global::Entities.size() - 1 );

	// Imposto il nome dell'entità
	this->SetName( _name );

	// Scelgo la posizione iniziale dell'entità
	this->SetPosition( position );

	// Scelgo il centro dell'entità
	this->SetCenter( Types::Point2D( 0.0f, 0.0f ) );

	// Rendo visibile l'entità
	this->SetVisible( true );

	// Imposto la posizione dell'entità rispetto alla camera
	this->SetFixed( false );

	// Imposto la sensibilità dell'entità
	this->SetSensible( true );

	// Imposto la modalità di debug
	this->SetDebugMode( false );
	//this->SetDebugMode( true );

	// Imposto l'area di visibilità rettangolare
	this->GetVisibilityArea().SetRectangle( Types::Size2D_u( 1, 1 ), this->GetCenter() );
}

Entity::~Entity() {

	// Rimuovo l'entità dalla lista generale
	Global::Entities.remove( this );
}

void
Entity::SendSignal( Types::Int type, Entity *other ) {

	// Controlla il tipo di segnale
	switch ( type ) {

		// Gestisco il segnale di cambio della visibilità
		case SignalType::CHANGE_VISIBILITY: { 

			// Emetto il segnale di cambio della visibilità
			this->SignalVisibility().emit( this->GetVisible(), this );
			break;
		}

		// Gestisco il segnale di cambio della posizione rispetto alla camera
		case SignalType::CHANGE_FIXING: { 

			// Emetto il segnale di cambio della posizione rispetto alla camera
			this->SignalFixing().emit( this->GetFixed(), this );
			break;
		}

		// Gestisco il segnale di cambio della sensibilità
		case SignalType::CHANGE_SENSIBILITY: { 

			// Emetto il segnale di cambio della sensibilità
			this->SignalSensibility().emit( this->GetSensible(), this );
			break;
		}

		// Gestisco il segnale di movimento
		case SignalType::MOTION: { 

			// Emetto il segnale di movimento
			this->SignalMotion().emit( this->GetPosition(), this );

			// Aggiorno la posizione dell'area di visibilità
			this->GetVisibilityArea().SetPosition( this->GetPosition() );
			break;
		}

		default: break;
	}

	// Aggiorno l'area di visibilità nello spazio 2D
	this->GetVisibilityArea().Update();
}

Types::Bool
Entity::SendEvent( Event *event, Entity *This ) {

	// Variabile di controllo
	Types::Bool end_event = false;

	// Controlla il tipo di evento
	switch ( event->type ) {

		// Cambio la visibilità dell'entità
		case EventType::SET_VISIBLE: { 

			this->SetVisible( ( event->arg0[0] > 0 ) ? true : false );
			end_event = true;
			break;
		}

		// Cambio la posizione dell'entità rispetto alla camera
		case EventType::SET_FIXED: { 

			this->SetFixed( ( event->arg0[0] > 0 ) ? true : false );
			end_event = true;
			break;
		}

		// Cambo la sensibilità dell'entità
		case EventType::SET_SENSIBLE: { 

			this->SetSensible( ( event->arg0[0] > 0 ) ? true : false );
			end_event = true;
			break;
		}

		// Cambio la posizione dell'entità
		case EventType::SET_POSITION: { 

			this->SetPosition( Types::Point2D( event->arg0[0], event->arg1[0] ) );
			end_event = true;
			break;
		}

		// Cambio la posizione dell'entità
		case EventType::MOVE_POSITION: { 

			this->MovePosition( event->arg0[0], event->arg1[0], 0.0f );
			end_event = true;
			break;
		}

		// Mostro il messaggio di sistema
		case EventType::SHOW_MESSAGE: {

			this->GetEngine()->ShowSystemDialog( event->string, NULL );
			end_event = true;
			break;
		}

		// Aspetta la chiusura del messaggio di sistema
		case EventType::WAIT_DIALOG: {

			if ( !this->GetEngine()->SystemDialogIsOpen() )
				end_event = true;

			break;
		}

		// Aspetta alcuni secondi
		case EventType::WAIT_SECONDS: {

			// Controllo i FPS dal disegnatore principale
			Types::Uint fps_limit = this->GetEngine()->GetDesigner().GetFpsLimit();

			event->arg0[0] -= ( 1.0f / (Types::Float) fps_limit );
			if ( event->arg0[0] <= 0.0f ) end_event = true;
			break;
		}

		default: break;
	}

	return end_event;
}

void
Entity::Update( Viewer *viewer, Player *player ) {

	// Controlla che ci sia almeno un elemento in coda
	if ( !this->event_list.empty() ) {

		// Ricavo il primo elemento della coda
		Event *event = this->event_list.front();

		// Invia l'evento
		Types::Bool end = this->SendEvent( event, this );

		// Controllo se l'evento si è concluso
		if ( end ) {

			// Rimuovo il primo evento della coda
			this->PopEvent( event );
		}
	}

	// Aggiorno l'area di visibilità nello spazio 2D
	this->GetVisibilityArea().Update();
}

void
Entity::DrawCenter( const Types::Point2D &offset ) const {

	// Ricavo il disegnatore principale
	const Designer &designer = this->GetEngine()->GetDesigner();

	// Imposto il colore del bordo del riquadro
	designer.SetColor( Color::Make( 255, 255, 0, 255 ) );

	// Imposto lo spessore della linea
	designer.SetLineWidth( 1 );

	// Disegno il centro dell'entità
	designer.DrawLine(	Types::Point2D( -5.0f, 0.0f ), Types::Point2D( 5.0f, 0.0f ),
						this->GetPosition() + offset );

	designer.DrawLine(	Types::Point2D( 0.0f, -5.0f ), Types::Point2D( 0.0f, 5.0f ),
						this->GetPosition() + offset );
}

void
Entity::DrawVisibilityArea( const Types::Point2D &offset ) const {

	// Ricavo il disegnatore principale
	const Designer &designer = this->GetEngine()->GetDesigner();

	// Imposto il colore del bordo del riquadro
	designer.SetColor( Color::Make( 255, 0, 0, 255 ) );

	// Imposto lo spessore della linea
	designer.SetLineWidth( 1 );

	// Disegno l'area di visibilità
	designer.DrawPolygon( this->GetVisibilityArea().GetPolygon(), offset );
}

void
Entity::Draw( const Types::Point2D &offset, Color::RGBA8 blend ) const {

	// Controllo se la modalità di debug è attiva
	if ( this->GetDebugMode() ) {

		/*
		// Ricavo il font di sistema
		Gui::Font *font = Global::GetFont( SYS_FONT_NORMAL ); 

		// Verifico che sia stato trovato
		if ( font != NULL ) {

			// Imposto il colore del testo
			font->SetColor( Color::Make( 255, 255, 255, 255 ) );

			// Disegno il nome dell'entità
			font->Draw( this->GetEngine()->GetDesigner(), this->GetName(), this->GetPosition() + offset + Types::Point2D( 10, 20 ), blend );
		}
		*/

		// Disegna l'area di visibilità
		this->DrawVisibilityArea( offset );

		// Disegna il centro dello sprite
		this->DrawCenter( offset );
	}
}

}; // Chiudo il namespace di VGE

#endif
