/* 
    Title --- scene-inl.hpp

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


#ifndef VGE_SCENE_INL_HPP
#define VGE_SCENE_INL_HPP

#include "vge/scene.hpp"

namespace VGE { // Namespace di VGE

inline void
Scene::SetEngine( Engine *engine ) {

	// Collego l'istanza al gestore del gioco
	this->parent_engine = engine;
}

inline Engine *
Scene::GetEngine() const {

	// Ritorno il puntatore al gestore del gioco
	return this->parent_engine;
}

inline void
Scene::SetName( const std::wstring &name ) {

	// Imposto il nome della scena
	this->s_name = name;
}

inline const std::wstring
Scene::GetName() const {

	// Ritorno il nome della scena
	return this->s_name;
}

inline void
Scene::AddTile(	Scene::Depth depth, Types::Uint layer,
				const Types::Point2D &tile, const Types::Rect_u &coords ) {

	// Aggiungo una piastrella alla scena
	this->AddTile( depth, layer, tile, coords, false );
}

inline const MapLayerList &
Scene::GetMapLayer( Scene::Depth depth ) const {

	// Ritorno la lista delle entità
	return this->layer_list[depth];
}

inline const EntityList &
Scene::GetEntityList() const {

	// Ritorno la lista delle entità
	return this->entity_list;
}

}; // Chiudo il namespace di VGE

#endif
