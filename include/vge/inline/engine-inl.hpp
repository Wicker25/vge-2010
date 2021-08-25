/* 
    Title --- engine-inl.hpp

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


#ifndef VGE_ENGINE_INL_HPP
#define VGE_ENGINE_INL_HPP

#include "vge/engine.hpp"

namespace VGE { // Namespace di VGE

inline Designer &
Engine::GetDesigner() {

	// Ritorno il disegnatore principale
	return this->designer;
}

inline InputManager &
Engine::GetInputManager() {

	// Ritorno il gestore degli eventi in ingresso
	return this->input_manager;
}

inline Mixer &
Engine::GetMixer() {

	// Ritorno il gestore degli effetti sonori
	return this->mixer;
}

inline void
Engine::AddPlayer( Player *player, Types::Bool mouse = false ) {

	// Verifico i parametri inseriti
	if ( player != NULL ) {

		// Aggiungo il giocatore alla lista
		this->player_list.push_back( player );

		// Scelgo il giocatore del mouse
		if ( mouse ) this->mouse_player = player;
	}
}

inline void
Engine::RemovePlayer( Player *player ) {

	// Verifico i parametri inseriti
	if ( player != NULL ) {

		// Rimuovo il giocatore dalla lista
		this->player_list.remove( player );
	}
}

inline void
Engine::SetMousePlayer( Player *player ) {

	// Imposto il giocatore del mouse
	this->mouse_player = player;
}

inline Player *
Engine::GetMousePlayer() const {

	// Ritorno il giocatore del mouse
	return this->mouse_player;
}

inline void
Engine::SetWidgetFocus( Gui::Widget *widget ) {

	// Imposto il widget con il focus
	this->widget_focus = widget;
}

inline Gui::Widget *
Engine::GetWidgetFocus() const {

	// Ritorno il widget con il focus
	return this->widget_focus;
}

inline void
Engine::ShowSystemDialog( const std::wstring &text ) {

	// Mostro il dialogo di sistema
	this->ShowSystemDialog( text, NULL );
}

inline Gui::MessageBox &
Engine::GetSystemDialog() {

	// Ritorno il puntatore al dialogo di sistema
	return this->system_dialog;
}

inline Types::Bool
Engine::SystemDialogIsOpen() {

	// Ritorna lo stato del dialogo di sistema
	return this->system_dialog_is_open;
}

inline void
Engine::AddToSystemViewer( Entity *entity ) {

	// Verifico i parametri inseriti
	if ( entity != NULL ) {

		// Aggiungo un oggetto al gioco
		this->system_list.push_back( entity );

		// Collego l'oggetto al gioco
		entity->SetEngine( this );
	}
}

inline void
Engine::RemoveFromSystemViewer( Entity *entity ) {

	// Verifico i parametri inseriti
	if ( entity != NULL ) {

		// Rimuovo un oggetto dal gioco
		this->system_list.remove( entity );
	}
}

inline void
Engine::CheckInteraction() {

	// Avvio il gestore delle collisioni della mappa
	// FIXME
	if ( !this->scene_list.empty() )

		this->scene_list[0]->Update();
}

inline void
Engine::ClearScreen() {

	// Pulisco lo schermo
	glClear( GL_COLOR_BUFFER_BIT ); // | GL_DEPTH_BUFFER_BIT
}

inline void
Engine::Quit() {

	// Log di lavoro
	printf( "\nEnding game...\n" );

	// Deinizializzo il gestore degli eventi in ingresso
	this->GetInputManager().Close();

	// Deinizializzo il gestore degli effetti sonori
	this->GetMixer().Close();
}

}; // Chiudo il namespace di VGE

#endif
