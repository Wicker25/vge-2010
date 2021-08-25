/* 
    Title --- scene.hpp

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


#ifndef VGE_SCENE_HPP
#define VGE_SCENE_HPP

#include <iostream>
#include <vector>
#include <list>
#include <typeinfo>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
//#include <SDL/SDL_opengl.h>
#include <GL/glew.h>

#include "vge/consts.hpp"
#include "vge/types.hpp"
#include "vge/error.hpp"
#include "vge/math.hpp"
#include "vge/xml.hpp"

#include "vge/input-manager.hpp"
#include "vge/mixer.hpp"

#include "vge/interfaces/i-resizable.hpp"

#include "vge/entity.hpp"
#include "vge/sprite.hpp"
#include "vge/player.hpp"

#include "vge/widgets/message-box.hpp"

namespace VGE { // Namespace di VGE

// Struttura di una piastrella
typedef struct {

	Types::Uint x, y;		/* Coordinate nel tileset */
	Types::Rect_u coords;	/* Area nella mappa */

} Tile;

// Ridefinizione dei tipo lista
typedef std::list< Tile > TileList;

// Struttura di un livello
typedef struct {

	Image *tileset;			/* Immagine del tileset */
	TileList tile_list;		/* Lista delle piastrelle nei due strati */

} MapLayer;

// Ridefinizione dei tipo lista
typedef std::vector< MapLayer > MapLayerList;
typedef std::list< Types::Rect_f > SolidAreaList;

// Estrae le coordinate della piastrella 
Types::Bool extract_coords( Types::Rect_u &rectangle, const wchar_t *string );


// Prototipi
class Engine;
class Viewer;

// Ridefinizione dei tipo lista
typedef std::list< Viewer * > ViewerList;


class Scene : public InterfaceResizable {

	/* SCENA */

public:

	// Livelli della scena
	typedef enum {

		BOTTOM,
		TOP,

	} Depth;

	// Metodi costruttore e distruttore
	Scene();
	virtual ~Scene();

	// Carica la mappa da un file XML
	void LoadMapFromXML( Xml *node );

	// Collega l'istanza al gestore del gioco
	void SetEngine( Engine *engine );
	// Ritorna il puntatore al gestore del gioco
	Engine *GetEngine() const;

	// Imposta il nome della scena
	void SetName( const std::wstring &name );
	// Ritorna il nome della scena
	const std::wstring GetName() const;

	// Aggiunge un nuovo tileset alla scena
	void AddMapLayer( const std::string &tileset, const Types::Size2D_u tile_size,
					  Scene::Depth depth, Types::Uint8 opacity );

	// Aggiunge una piastrella alla scena
	void AddTile(	Scene::Depth depth, Types::Uint layer,
					const Types::Point2D &tile, const Types::Rect_u &coords );
	void AddTile(	Scene::Depth depth, Types::Uint layer,
					const Types::Point2D &tile, const Types::Rect_u &coords, Types::Bool solid );

	// Ritorna la lista dei livelli
	const MapLayerList &GetMapLayer( Scene::Depth depth ) const;

	// Aggiunge un'entità alla scena
	void Add( Entity *entity );
	// Ritorna la lista delle entità
	const EntityList &GetEntityList() const;
	// Rimuove un'entità dalla scena
	void Remove( Entity *entity );

	// Aggiunge un visualizzatore alla scena
	void AddViewer( Viewer *viewer, Types::Bool mouse );
	// Rimuove un visualizzatore dalla scena
	void RemoveViewer( Viewer *viewer );

	// Cerca un'interazione tra le entità
	void CheckInteraction();
	// Cerca un'interazione con la mappa
	void CheckMapInteraction( Sprite *object );
	// Cerca un'interazione con gli altri oggetti (e con i giocatori)
	void CheckObjectsInteraction( Sprite *object );

	// Aggiorna la scena
	void Update();

	// Disegna la scena e i suoi entità sullo schermo
	void Draw();


	/* Metodi di costruzione */

	// Costruttore da nodo XML
	Scene( const Xml *node );

	// Carica il tileset dal file XML
	void ExtractLayers( const Xml *node );

	// Carica la lista di piastrelle dal file XML
	Types::Uint ExtractTileList( const Xml *node, Scene::Depth depth, Types::Uint layer );

protected:

	// Nome della scena
	std::wstring s_name;

	// Lista dei livelli della mappa
	MapLayerList layer_list[2];

	// Aree di collisione
	SolidAreaList collision_areas;

	// Puntatore al gestore del gioco
	Engine *parent_engine;

	// Lista delle entità
	EntityList entity_list;

	// Lista dei visualizzatori
	ViewerList viewer_list;

	// Visualizzatore del mouse
	Viewer *mouse_viewer;
};

}; // Chiudo il namespace di VGE

#endif
