/* 
    Title --- i-clickable.cpp

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


#ifndef VGE_INTERFACE_CLICKABLE_CPP
#define VGE_INTERFACE_CLICKABLE_CPP

#include "vge/interfaces/i-clickable.hpp"

#include "vge/bounding-area.hpp"
#include "vge/inline/bounding-area-inl.hpp"

#include "vge/input-manager.hpp"
#include "vge/inline/input-manager-inl.hpp"

#include "vge/viewer.hpp"
#include "vge/inline/viewer-inl.hpp"

#include "vge/scene.hpp"
#include "vge/inline/scene-inl.hpp"

#include "vge/player.hpp"
#include "vge/inline/player-inl.hpp"

#include "vge/interfaces/inline/i-clickable-inl.hpp"

namespace VGE { // Namespace di VGE

InterfaceClickable::InterfaceClickable() {

}

InterfaceClickable::~InterfaceClickable() {

}

Types::Uint
InterfaceClickable::CheckMouseEvent(	InputManager *input_manager,
										BoundingArea *area, Viewer *viewer, Types::Bool fixed ) {

	// Evento riscontrato
	Types::Uint event = SignalType::MOUSE_NO_EVENT;

	// Ricavo la posizione del mouse
	Types::Point2D mouse_position = input_manager->GetMousePosition();

	// Controllo che sia stato specificato un visualizzatore
	if ( viewer != NULL && !fixed ) {

		// Tengo conto della posizione della camera
		mouse_position = mouse_position + ( viewer->GetCameraPosition() - viewer->GetPosition() );
	}

	// Controllo se il puntatore è sopra l'entità
	if ( area->PointInArea( mouse_position ) ) {

		event = SignalType::MOUSE_SELECTION;

		if ( input_manager->GetMouseButtonPress( InputManager::MOUSE_LEFT_BUTTON ) ) {

			event = SignalType::MOUSE_LEFT_PRESSED;

		} else if ( input_manager->GetMouseButtonPress( InputManager::MOUSE_MIDDLE_BUTTON ) ) {

			event = SignalType::MOUSE_MIDDLE_PRESSED;

		} else if ( input_manager->GetMouseButtonPress( InputManager::MOUSE_RIGHT_BUTTON ) ) {

			event = SignalType::MOUSE_RIGHT_PRESSED;

		} else if ( input_manager->GetMouseButtonRelease( InputManager::MOUSE_LEFT_BUTTON ) ) {

			event = SignalType::MOUSE_LEFT_RELEASED;

		} else if ( input_manager->GetMouseButtonRelease( InputManager::MOUSE_MIDDLE_BUTTON ) ) {

			event = SignalType::MOUSE_MIDDLE_RELEASED;

		} else if ( input_manager->GetMouseButtonRelease( InputManager::MOUSE_RIGHT_BUTTON ) ) {

			event = SignalType::MOUSE_RIGHT_RELEASED;
		}
	}

	return event;
}

}; // Chiudo il namespace di VGE

#endif
