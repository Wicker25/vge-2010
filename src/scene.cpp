/* 
    Title --- scene.cpp

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


#ifndef VGE_SCENE_CPP
#define VGE_SCENE_CPP

#include "vge/scene.hpp"

#include "vge/xml.hpp"
#include "vge/inline/xml-inl.hpp"

#include "vge/interfaces/i-resizable.hpp"
#include "vge/interfaces/inline/i-resizable-inl.hpp"

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

#include "vge/viewer.hpp"
#include "vge/inline/viewer-inl.hpp"

#include "vge/input-manager.hpp"
#include "vge/inline/input-manager-inl.hpp"

#include "vge/engine.hpp"
#include "vge/inline/engine-inl.hpp"

#include "vge/widgets/font.hpp"
#include "vge/widgets/inline/font-inl.hpp"

#include "vge/widgets/text-box.hpp"
#include "vge/widgets/inline/text-box-inl.hpp"

#include "vge/widgets/message-box.hpp"
#include "vge/widgets/inline/message-box-inl.hpp"

#include "vge/inline/scene-inl.hpp"

namespace VGE { // Namespace di VGE

Types::Bool
extract_coords( Types::Rect_u &rectangle, const wchar_t *string ) {

	// Estraggo le coordinate della piastrella 
	Types::Uint n_coord = swscanf( string, L"%u,%u,%u,%u",	&rectangle.left,
															&rectangle.top,
															&rectangle.right,
															&rectangle.bottom );

	// Correggo i dati per la forma singola
	if ( n_coord == 2 ) {

		rectangle.right = rectangle.left;
		rectangle.bottom = rectangle.top;
	};

	// Verifico la correttezza dei dati
	return ( n_coord % 2 == 0 );
}

Scene::Scene() {

	// Inizializzo le strutture
	this->mouse_viewer	= NULL;
}

Scene::~Scene() {

	// Iteratore
	Types::Uint i = 0;

	// Dealloco i tileset e le liste delle piastrelle
	for ( ; i < (Types::Uint) this->layer_list[0].size(); i++ ) {

		// Elimino l'immagine del tileset
		delete this->layer_list[0][i].tileset;
	}

	for ( ; i < (Types::Uint) this->layer_list[1].size(); i++ ) {

		// Elimino l'immagine del tileset
		delete this->layer_list[1][i].tileset;
	}

	// Libero la memoria
	//this->viewer_list.clear();
}

void
Scene::AddMapLayer(	const std::string &tileset, const Types::Size2D_u tile_size,
					Scene::Depth depth, Types::Uint8 opacity ) {

	// Creo la struttura del nuovo livello
	MapLayer new_layer;

	// Creo l'immagine del nuovo tileset
	new_layer.tileset = new Image( tileset, tile_size );

	// Imposta l'opacità del tileset
	new_layer.tileset->SetOpacity( opacity );

	// Disabilito la modalità di debug del tileset
	new_layer.tileset->SetDebugMode( false );

	// Aggiungo il nuovo tileset alla lista
	this->layer_list[depth].push_back( new_layer );
}

void
Scene::AddTile(	Scene::Depth depth, Types::Uint layer,
				const Types::Point2D &tile, const Types::Rect_u &coords, Types::Bool solid ) {

	// Creo la struttura della nuova piastrella
	Tile new_tile = { tile.x, tile.y, coords };

	// Aggiungo la piastrella alla lista
	this->layer_list[depth][layer].tile_list.push_back( new_tile );

	// Controllo se piastrella è solida
	if ( solid ) {

		// Ricavo la dimensione delle piastrelle
		Types::Size2D_u tile_size = this->layer_list[depth][layer].tileset->GetClipSize();

		// Determino il rettangolo dell'area
		Types::Rect_f collision_area(	coords.left * tile_size.w,
										coords.top * tile_size.h,
										( coords.right + 1 ) * tile_size.w,
										( coords.bottom + 1 ) * tile_size.h );

		// Aggiungo la nuova area di collisione
		this->collision_areas.push_back( collision_area );
	}
}

void
Scene::Add( Entity *entity ) {

	// Verifico i parametri inseriti
	if ( entity != NULL ) {

		// Aggiungo un'entità alla scena
		this->entity_list.push_back( entity );

		// Collego l'entità all'engine
		entity->SetEngine( this->GetEngine() );

		// Collego l'entità alla scena
		entity->SetScene( this );

		// Invio il segnale di movimento
		entity->SendSignal( SignalType::MOTION, NULL );
	}
}

void
Scene::Remove( Entity *entity ) {

	// Verifico i parametri inseriti
	if ( entity != NULL ) {

		// Rimuovo un'entità dalla scena
		this->entity_list.remove( entity );
	}
}

void
Scene::AddViewer( Viewer *viewer, Types::Bool mouse = false ) {

	// Verifico i parametri inseriti
	if ( viewer != NULL ) {

		// Aggiungo un visualizzatore dalla scena
		this->viewer_list.push_back( viewer );

		// Collego il visualizzatore all'engine
		viewer->SetEngine( this->GetEngine() );

		// Scelgo il giocatore del mouse
		if ( mouse ) this->mouse_viewer = viewer;
	}
}

void
Scene::RemoveViewer( Viewer *viewer ) {

	// Verifico i parametri inseriti
	if ( viewer != NULL )

		// Rimuovo un visualizzatore dalla scena
		this->viewer_list.remove( viewer );
}

void
Scene::CheckInteraction() {

	// Iteratori
	EntityList::const_iterator iter = this->entity_list.begin();
	EntityList::const_iterator end = this->entity_list.end();

	/* GESTISCO LE COLLISIONI */
	for ( ; iter != end; iter++ ) {

		/* AVVIO LA FUNZIONE DI LAVORO */
		if ( (*iter)->GetSensible() )

			(*iter)->Update( this->mouse_viewer, this->GetEngine()->GetMousePlayer() );

		// Controllo il tipo di entità
		if ( (*iter)->GetMask() >= Entity::SPRITE_MASK ) {

			// Puntatore all'entità
			Sprite *object = VGE_SPRITE( *iter );

			// Verifico la solidità dell'entità
			if ( object->GetSolid() && !object->GetFixed() ) {

				/* COLLISIONI CON LA MAPPA */
				this->CheckMapInteraction( object );

				/* COLLISIONI CON UN ALTRO OGGETTO */
				this->CheckObjectsInteraction( object );
			}
		}
	}
}

void
Scene::CheckMapInteraction( Sprite *object ) {

	// Iteratori
	SolidAreaList::const_iterator iter = this->collision_areas.begin();
	SolidAreaList::const_iterator end = this->collision_areas.end();

	for ( ; iter != end; iter++ ) {

		// Confronto le aree di collisione
		if ( object->GetCollisionArea().CollideRectangularArea( *iter ) ) {

			// Avvio i segnali di collisione
			object->SendSignal( SignalType::COLLISION, NULL );
		}
	}
}

void
Scene::CheckObjectsInteraction( Sprite *object ) {

	// Iteratori
	EntityList::const_iterator iter = this->entity_list.begin();
	EntityList::const_iterator end = this->entity_list.end();

	for ( ; iter != end; iter++ ) {

		// Controllo il tipo di entità
		if ( (*iter)->GetMask() >= Entity::SPRITE_MASK ) {

			// Puntatore al secondo entità
			Sprite *other = VGE_SPRITE( *iter );

			// Controllo che i due oggetti siano distinti
			if ( object != other ) {

				// Verifico la solidità del secondo entità
				if ( other->GetSolid() && !other->GetFixed() ) {

					// Confronto le aree di collisione
					if ( object->GetCollisionArea().CollideBoundingArea( other->GetCollisionArea() ) ) {

						// Avvio i segnali di collisione
						object->SendSignal( SignalType::COLLISION, other );
						other->SendSignal( SignalType::COLLISION, object );
					}

					/* INTERAZIONE DI UN GIOCATORE */
					if ( object->GetMask() == Entity::PLAYER_MASK ) {

						// Puntatore al giocatore
						Player *player = VGE_PLAYER( object );

						// Confronto l'aree di interazione con quella di collisione
						if ( player->GetInteractionArea().CollideBoundingArea( other->GetCollisionArea() ) ) {

							// Avvio i segnali di interazione
							player->SendSignal( SignalType::CHECK_INTERACTION, VGE_SPRITE( other ) );
						}
					}
				}
			}
		}
	}
}

void
Scene::Update() {

	// Ordino le entità in base alla profondità
	this->entity_list.sort( z_order );

	// Ordino i visualizzatori in base alla profondità
	this->viewer_list.sort( v_order );

	// Gestisce le interazioni tra le entità e il mondo circostante
	this->CheckInteraction();
}

void
Scene::Draw() {

	// Iteratori
	ViewerList::iterator iter = this->viewer_list.begin();
	ViewerList::iterator end = this->viewer_list.end();

	// Disegno la scena e i suoi oggetti attraverso i visualizzatori
	for ( ; iter != end; iter++ ) {

		// Aggiorna il visualizzatore
		(*iter)->Update( *this );

		// Disegna la scena nel visualizzatore
		(*iter)->DrawScene( *this );
	}
}

}; // Chiudo il namespace di VGE

#endif
