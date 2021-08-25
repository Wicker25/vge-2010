/* 
    Title --- viewer.hpp

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


#ifndef VGE_VIEWER_HPP
#define VGE_VIEWER_HPP

#include <iostream>
#include <list>

#include <SDL/SDL.h>
//#include <SDL/SDL_opengl.h>
#include <GL/glew.h> 

#include "vge/consts.hpp"
#include "vge/types.hpp"
#include "vge/math.hpp"

#include "vge/designer.hpp"

#include "vge/interfaces/i-colorable.hpp"
#include "vge/interfaces/i-resizable.hpp"

#include "vge/entity.hpp"
#include "vge/image.hpp"
#include "vge/sprite.hpp"
#include "vge/object.hpp"
#include "vge/character.hpp"
#include "vge/player.hpp"
#include "vge/scene.hpp"

#include "vge/widgets/box.hpp"
#include "vge/widgets/text-box.hpp"

namespace VGE { // Namespace di VGE

// Funzione di ordinamento degli oggetti secondo la profondità
Types::Bool z_order( Entity *a, Entity *b );

// Prototipi
class Scene;
class Engine;

class Viewer : public InterfaceResizable, public InterfaceColorable {

	/* VISUALIZZATORE */

public:

	// Metodi costruttore e distruttore
	Viewer( const Types::Size2D_f &scale_, const Types::Point3D &point );
	virtual ~Viewer();

	// Collega l'istanza al gestore del gioco
	void SetEngine( Engine *engine );
	// Ritorna il puntatore al gestore del gioco
	Engine *GetEngine() const;

	// Modifico la posizione del visualizzatore (assoluta)
	void SetPosition( const Types::Point3D &point );
	// Ritorno la posizione del visualizzatore (assoluta)
	const Types::Point3D &GetPosition() const;

	// Imposto la dimensione della telecamera
	void SetCameraSize( const Types::Size2D_f &scale_ );
	// Ritorna il rettangolo della telecamera
	Types::Rect_f GetCameraRectangle() const;

	// Modifica la posizione della telecamera (assoluta)
	void SetCameraPosition( const Types::Point2D &point );
	// Modifica la posizione della telecamera (relativa)
	void MoveCameraPosition( Types::Float x, Types::Float y );
	// Ritorna la posizione della telecamera (assoluta)
	const Types::Point2D &GetCameraPosition() const;

	// Imposto un obbiettivo da seguire con la camera
	void SetTarget( Entity *new_target, Types::Float elasticity_value );
	// Rimuovo l'obbiettivo da seguire con la camera
	void RemoveTarget();
	// Ritorna l'obbiettivo da seguire con la camera
	void GetTarget( Entity *new_target ) const;

	// Imposta l'elasticità della camera
	void SetElasticity( Types::Float value );
	// Ritorna l'elasticità della camera
	void GetElasticity( Types::Float *value );

	// Imposta l'elasticità della camera
	void SetMaxSpeed( Types::Float value );
	// Ritorna l'elasticità della camera
	void GetMaxSpeed( Types::Float *value );
	// Ritorno la cornice del visualizzatore
	Gui::Box &GetBox();

	// Aggiorna le misure del visualizzatore
	void UpdateSizes();

	// Aggiorna il visualizzatore
	void Update( const Scene &scene );

	// Imposta la visualizzazione
	void Active( Types::Bool value ) const;

	// Disegna gli oggetti della mappa
	void DrawObject( const EntityList &entity_list );
	// Disegna uno strato della mappa
	void DrawLayers( Scene &scene, Scene::Depth depth );
	// Disegna la cornice del visualizzatore
	void DrawFrame();

	// Disegna la scena nel visualizzatore
	void DrawScene( Scene &scene );

protected:

	// Puntatore al gestore del gioco
	Engine *parent_engine;

	// Posizione del visualizzatore
	Types::Point3D position;

	// Dimensione relativa della camera
	Types::Size2D_f size_r;
	// Posizione relativa del visualizzatore
	Types::Point2D pos_r;

	// Posizione della camera
	Types::Point2D cam_pos;

	// Elasticità
	Types::Float elasticity;
	// Velocità massima
	Types::Float max_speed;

	// Riquadro del visualizzatore
	Gui::Box frame;

	// Oggetto da seguire
	Entity *target;

	// Muove la camera sull'obiettivo
	void FollowTarget( const Types::Size2D_u &scene_size );
};

}; // Chiudo il namespace di VGE

#endif
