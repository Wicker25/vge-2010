/* 
    Title --- engine.cpp

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


#ifndef VGE_ENGINE_CPP
#define VGE_ENGINE_CPP

#include "vge/engine.hpp"

#include "vge/xml.hpp"
#include "vge/inline/xml-inl.hpp"

#include "vge/designer.hpp"
#include "vge/inline/designer-inl.hpp"

#include "vge/input-manager.hpp"
#include "vge/inline/input-manager-inl.hpp"

#include "vge/mixer.hpp"
#include "vge/inline/mixer-inl.hpp"

#include "vge/interfaces/i-ruotable.hpp"
#include "vge/interfaces/inline/i-ruotable-inl.hpp"

#include "vge/interfaces/i-scalable.hpp"
#include "vge/interfaces/inline/i-scalable-inl.hpp"

#include "vge/interfaces/i-colorable.hpp"
#include "vge/interfaces/inline/i-colorable-inl.hpp"

#include "vge/interfaces/i-image.hpp"
#include "vge/interfaces/inline/i-image-inl.hpp"

#include "vge/interfaces/i-clickable.hpp"
#include "vge/interfaces/inline/i-clickable-inl.hpp"

#include "vge/interfaces/i-programmable.hpp"
#include "vge/interfaces/inline/i-programmable-inl.hpp"

#include "vge/bounding-area.hpp"
#include "vge/inline/bounding-area-inl.hpp"

#include "vge/entity.hpp"
#include "vge/inline/entity-inl.hpp"

#include "vge/image.hpp"
#include "vge/inline/image-inl.hpp"

#include "vge/sprite.hpp"
#include "vge/inline/sprite-inl.hpp"

#include "vge/object.hpp"
#include "vge/inline/object-inl.hpp"

#include "vge/character.hpp"
#include "vge/inline/character-inl.hpp"

#include "vge/player.hpp"
#include "vge/inline/player-inl.hpp"

#include "vge/particle-system.hpp"
#include "vge/inline/particle-system-inl.hpp"

#include "vge/scene.hpp"
#include "vge/inline/scene-inl.hpp"

#include "vge/viewer.hpp"
#include "vge/inline/viewer-inl.hpp"

#include "vge/widgets/box.hpp"
#include "vge/widgets/inline/box-inl.hpp"

#include "vge/widgets/widget.hpp"
#include "vge/widgets/inline/widget-inl.hpp"

#include "vge/widgets/container.hpp"
#include "vge/widgets/inline/container-inl.hpp"

#include "vge/widgets/window.hpp"
#include "vge/widgets/inline/window-inl.hpp"

#include "vge/widgets/font.hpp"
#include "vge/widgets/inline/font-inl.hpp"

#include "vge/widgets/text-box.hpp"
#include "vge/widgets/inline/text-box-inl.hpp"

#include "vge/widgets/message-box.hpp"
#include "vge/widgets/inline/message-box-inl.hpp"

#include "vge/inline/engine-inl.hpp"

namespace VGE { // Namespace di VGE

Types::Bool
v_order( Viewer *a, Viewer *b ) {

	// Ordino gli oggetti secondo la profondità
	return a->GetPosition().z < b->GetPosition().z;
}

Engine::Engine(	Designer::VideoModes mode, const Types::Size2D_u &size, Types::Uint depth, Types::Uint fps = 60 ) :

	system_viewer( Types::Size2D_f( 1.0f, 1.0f ), Types::Point3D( 0.0f, 0.0f, 0.0f ) ),
	system_dialog( Types::Size2D_u( 200, 50 ) ) {

	// Inizializzo l'engine
	this->Init( mode, size, depth, fps );

	// Imposto il giocatore con il controllo del mouse
	this->SetMousePlayer( NULL );

	// Imposta il widget con il focus iniziale
	this->SetWidgetFocus( NULL );

	// Collego il visualizzatore principale all'engine
	this->system_viewer.SetEngine( this );

	// Aggiungo il dialogo di sistema al visualizzatore di sistema
	this->AddToSystemViewer( &this->system_dialog );
}

Engine::~Engine() {

}

void
Engine::Init( Designer::VideoModes mode, const Types::Size2D_u &size, Types::Uint depth, Types::Uint fps ) {

	// Log di lavoro
	printf( "<Loading>\n" );

	// Inizializzo il generatore di numeri casuali
	srand( time( NULL ) );

	// Inizializzo le SDL
	if ( SDL_Init( SDL_INIT_VIDEO ) != 0 ) {

		fprintf( stderr, " %s: Could not initialize SDL framework: %s\n", FATAL, SDL_GetError() );
		exit(1);
	}

	// Inizializzo il disegnatore principale
	this->GetDesigner().Init( mode, size, depth, fps );

	// Inizializzo il gestore degli eventi in ingresso
	this->GetInputManager().Init();

	// Inizializzo il gestore degli effetti sonori
	this->GetMixer().Init();

	// Inizializzo il dialogo di sistema
	this->InitSystemDialog();

	// Imposto le funzioni da eseguire in caso di uscita improvvisa
	atexit( SDL_Quit );

	// Log di lavoro
	printf( "</Loading>\n" );
}

void
Engine::InitSystemDialog() {

	// Inizializzo il flag di apertura del dialogo di sistema
	this->system_dialog_is_open	= false;

	// Ricavo la dimensione dello schermo
	const Types::Size2D_u &screen_size = this->GetDesigner().GetScreenSize();

	// Calcolo le dimensioni del dialogo di sistema
	Types::Size2D_u size(	screen_size.w * 0.91f,
							screen_size.h * 0.24f );

	// Imposto la dimensione del dialogo di sistema
	this->GetSystemDialog().SetSize( size );

	// Calcolo la posizione del dialogo di sistema
	Types::Point3D position(	(Types::Float) screen_size.w * 0.05f,
								(Types::Float) screen_size.h * 0.05f,
								VGE::Layer::TOP );

	// Imposto le caratteristiche del dialogo di sistema
	this->GetSystemDialog().SetPosition( position );
	this->GetSystemDialog().SetFixed( true );
	this->GetSystemDialog().SetSensible( false );
	this->GetSystemDialog().SetOpacity( 0 );
}

void
Engine::AddScene( Scene *scene ) {

	// Verifico i parametri
	if ( scene != NULL ) {

		// Aggiungo la scena alla lista
		this->scene_list.push_back( scene );

		// Collego la scena all'engine
		scene->SetEngine( this );
	}
}

void
Engine::ShowSystemDialog( const std::wstring &text, Image *image ) {

	// Configuro il dialogo di sistema
	this->GetSystemDialog().GetTextBox().SetFont( Global::GetFont( L"default_normal" ) );
	this->GetSystemDialog().GetTextBox().SetString( text );

	// Aggiungo l'immagine al dialogo di sistema
	this->GetSystemDialog().SetImage( image, 8.0f, 0.5f );

	// Vado alla prima pagina del dialogo di sistema
	this->GetSystemDialog().GetTextBox().GoToFirstPage();

	// Preparo il dialogo di sistema all'animazione di ingresso
	this->GetSystemDialog().SetOpacity( 0 );

	// Aggiunge l'evento di animazione al dialogo di sistema
	this->GetSystemDialog().AddEvent( EventType::FADING_IN, 15.0f );

	// Rende sensibile il dialogo di sistema
	this->GetSystemDialog().SetSensible( true );

	// Modifico lo stato del dialogo di sistema
	this->system_dialog_is_open = true;
}

void
Engine::HideSystemDialog() {

	// Aggiunge l'evento di animazione al dialogo di sistema
	this->GetSystemDialog().AddEvent( EventType::FADING_OUT, 15.0f );

	// Rende sensibile il dialogo di sistema
	this->GetSystemDialog().SetSensible( true );

	// Modifico lo stato del dialogo di sistema
	this->system_dialog_is_open = false;
}

Types::Bool
Engine::ReadEvents() {

	// Flag di uscita
	Types::Bool end_game = this->GetInputManager().Update();

	// Evento d'uscita
	if ( !end_game && this->GetInputManager().GetKeyState( SDLK_ESCAPE, true ) ) {

		end_game = true;
	}

	return end_game;
}

void
Engine::DrawScreen() {

	// FIXME
	if ( !this->scene_list.empty() )

		// Disegna la scena ed i suoi oggetti
		this->scene_list[0]->Draw();

	/** DISEGNO GLI OGGETTI DI SISTEMA **/

	// Disegna gli oggetti di sistema
	this->system_viewer.UpdateSizes();
	this->system_viewer.Active( true );
	this->system_viewer.DrawObject( this->system_list );
	this->system_viewer.Active( false );
	this->system_viewer.DrawFrame();

	// Aggiorno lo schermo
	this->GetDesigner().Update();
}

void
Engine::MainLoop() {

	// Iteratori
	PlayerList::iterator iter = this->player_list.begin();
	PlayerList::const_iterator end = this->player_list.end();

	// Aggiungo i giocatori alla mappa
	for ( ; iter != end; iter++ ) {

		// FIXME
		if ( !this->scene_list.empty() )
			this->scene_list[0]->Add( (*iter) );
	}

	// Strutture di lavoro
	Types::Bool loop = false;

	// Avvia il ciclo principale
	do {

		// Chiama la funzione di lavoro del gestore degli effetti sonori
		this->GetMixer().Update();

		// Pulisce lo schermo
		this->ClearScreen();

		// Legge gli eventi della finestra
		loop = this->ReadEvents();

		// Gestisce le collissioni
		this->CheckInteraction();

		// Iteratori
		EntityList::iterator iter = this->system_list.begin();
		EntityList::const_iterator end = this->system_list.end();

		/* AGGIORNO GLI OGGETTI DI SISTEMA */
		for ( ; iter != end; iter++ ) {

			/* AVVIO LA FUNZIONE DI LAVORO */
			if ( (*iter)->GetSensible() )

				(*iter)->Update( &this->system_viewer, this->GetMousePlayer() );
		}

		// Disegna il gioco sullo schermo
		this->DrawScreen();

	} while ( !loop );
}

}; // Chiudo il namespace di VGE

#endif
