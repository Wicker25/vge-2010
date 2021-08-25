/* 
    Title --- engine.hpp

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


#ifndef VGE_ENGINE_HPP
#define VGE_ENGINE_HPP

#include <iostream>
#include <cstdio>
#include <ctime>
#include <fstream>

#include <vector>

#include "vge/consts.hpp"
#include "vge/types.hpp"
#include "vge/math.hpp"
#include "vge/global.hpp"

#include "vge/designer.hpp"
#include "vge/input-manager.hpp"
#include "vge/mixer.hpp"

#include "vge/scene.hpp"
#include "vge/viewer.hpp"

#include "vge/widgets/box.hpp"
#include "vge/widgets/widget.hpp"

namespace VGE { // Namespace di VGE

// Ridefinizione del tipo lista
typedef std::vector< Scene * > ScenesList;

// Funzione di ordinamento dei visualizzatori secondo la profondità
Types::Bool v_order( Viewer *a, Viewer *b );

class Engine {

	/* MOTORE DEL GIOCO */

public:

	// Modalità video
	enum {

		WM_FULLSCREEN,
		WM_WINDOW,
	};

	// Metodi costruttore e distruttore
	Engine(	Designer::VideoModes mode, const Types::Size2D_u &size, Types::Uint depth, Types::Uint fps );
	virtual ~Engine();

	// Ritorna il disegnatore principale
	Designer &GetDesigner();

	// Ritorna il gestore degli eventi in ingresso
	InputManager &GetInputManager();

	// Ritorna il gestore degli effetti sonori
	Mixer &GetMixer();

	// Mostra il dialogo di sistema
	void ShowSystemDialog( const std::wstring &msg );
	void ShowSystemDialog( const std::wstring &msg, Image *image );

	// Nasconte il dialogo di sistema
	void HideSystemDialog();

	// Ritorno il puntatore al dialogo di sistema
	Gui::MessageBox &GetSystemDialog();

	// Ritorna lo stato del dialogo di sistema
	Types::Bool SystemDialogIsOpen();

	// Aggiunge un giocatore al gioco
	void AddPlayer( Player *player, Types::Bool mouse );
	// Rimuove un giocatore al gioco
	void RemovePlayer( Player *player );

	// Aggiunge un oggetto al visualizzatore di sistema
	void AddToSystemViewer( Entity *entity );
	// Rimuove un oggetto dal gioco
	void RemoveFromSystemViewer( Entity *entity );

	// Aggiunge una scena alla lista
	void AddScene( Scene *scene );


	// Imposta il giocatore del mouse
	void SetMousePlayer( Player *player );
	// Ritorna il giocatore del mouse
	Player *GetMousePlayer() const;

	// Imposta il widget con il focus
	void SetWidgetFocus( Gui::Widget *widget );
	// Ritorna il widget con il focus
	Gui::Widget *GetWidgetFocus() const;


	// Legge gli eventi della finestra
	Types::Bool ReadEvents();
	// Chiama il gestore delle collisioni
	void CheckInteraction();

	// Pulisce lo schermo
	void ClearScreen();
	// Aggiorna lo schermo
	void DrawScreen();

	// Avvia il loop principale
	void MainLoop();

	// Chiude l'engine
	void Quit();

protected:

	// Disegnatore principale
	Designer designer;

	// Gestore degl eventi in ingresso
	InputManager input_manager;

	// Gestore degli effetti sonori
	Mixer mixer;

	// Lista degli oggetti di sistema
	EntityList system_list;

	// Lista dei giocatori
	PlayerList player_list;

	// Visualizzatore di sistema
	Viewer system_viewer;

	// Dialogo di sistema
	Gui::MessageBox system_dialog;
	// Stato del dialogo di sistema
	Types::Bool system_dialog_is_open;

	// Lista delle scene
	ScenesList scene_list;

	// Giocatore del mouse
	Player *mouse_player;

	// Widget con il focus
	Gui::Widget *widget_focus;

	// Inizializza l'engine
	void Init( Designer::VideoModes mode, const Types::Size2D_u &size, Types::Uint depth, Types::Uint fps );

	// Inizializza il dialogo di sistema
	void InitSystemDialog();
};

}; // Chiudo il namespace di VGE

#endif
