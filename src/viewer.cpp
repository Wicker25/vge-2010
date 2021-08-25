/* 
    Title --- viewer.cpp

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


#ifndef VGE_VIEWER_CPP
#define VGE_VIEWER_CPP

#include <iostream>
#include <algorithm>

#include "vge/viewer.hpp"

#include "vge/designer.hpp"
#include "vge/inline/designer-inl.hpp"

#include "vge/interfaces/i-resizable.hpp"
#include "vge/interfaces/inline/i-resizable-inl.hpp"

#include "vge/interfaces/i-colorable.hpp"
#include "vge/interfaces/inline/i-colorable-inl.hpp"

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

#include "vge/scene.hpp"
#include "vge/inline/scene-inl.hpp"

#include "vge/engine.hpp"
#include "vge/inline/engine-inl.hpp"

#include "vge/widgets/box.hpp"
#include "vge/widgets/inline/box-inl.hpp"

#include "vge/inline/viewer-inl.hpp"

namespace VGE { // Namespace di VGE

Types::Bool
z_order( Entity *a, Entity *b ) {

	return a->GetPosition().z < b->GetPosition().z;
}

Viewer::Viewer( const Types::Size2D_f &scale_, const Types::Point3D &point ) {

	/** INIZIALIZZO IL VISUALIZZATORE **/

	// Imposto la posizione del visualizzatore
	this->SetPosition( point );

	// Imposto la dimensione della camera
	this->SetCameraSize( scale_ );

	// Imposto la posizione della camera
	this->SetCameraPosition( Types::Point2D( 0.0f, 0.0f ) );

	// Imposto l'obiettivo iniziale
	this->SetTarget( NULL, 25.0f );

	// Imposto la velocità massima iniziale
	this->SetMaxSpeed( 2.5f );

	// Disabilito il riempimento del riquadro
	this->GetBox().SetFilled( false );
}

Viewer::~Viewer() {

}

void
Viewer::UpdateSizes() {

	// Ricavo la dimensione dello schermo
	const Types::Size2D_u &screen_size = this->GetEngine()->GetDesigner().GetScreenSize();

	// Calcolo la dimensione effettiva del visualizzatore
	this->size.w = screen_size.w * this->size_r.w;
	this->size.h = screen_size.h * this->size_r.h;

	// Calcolo la dimensione effettiva del visualizzatore
	this->position.x = screen_size.w * this->pos_r.x;
	this->position.y = screen_size.h * this->pos_r.y;
}

void
Viewer::Update( const Scene &scene ) {

	// Aggiorno la dimensione del visualizzatore
	this->UpdateSizes();

	// Muove il visualizzatore verso l'obiettivo
	this->FollowTarget( scene.GetSize() );
}

inline void
Viewer::Active( Types::Bool value ) const {

	// Imposto l'area disegnabile sullo schermo
	if ( value ) {

		this->GetEngine()->GetDesigner().PushDrawableArea(

			Types::Rect_u(	this->position.x,
							this->position.y,
							this->position.x + this->size.w,
							this->position.y + this->size.h )
		);

	} else this->GetEngine()->GetDesigner().PopDrawableArea();
}

void
Viewer::FollowTarget( const Types::Size2D_u &scene_size ) {

	// Muovo la camera sull'obbiettivo
	if ( this->target != NULL ) {

		// Ricavo la posizione attuale dell'obbiettivo
		const Types::Point2D target_pos = this->target->GetPosition();

		// Tengo conto della costante elastica
		if ( this->elasticity > 0.0f ) {

			// Calcolo la distanza tra l'obbiettivo ed il centro della camera
			Types::Float diff_x = ( target_pos.x - this->cam_pos.x - this->size.w / 2 );
			Types::Float diff_y = ( target_pos.y - this->cam_pos.y - this->size.h / 2 );

			// Calcolo lo spostamento della camera verso l'obiettivo
			diff_x = diff_x / this->elasticity;
			diff_y = diff_y / this->elasticity;

			// Applico un limite di velocità
			diff_x = ( VABS( diff_x ) > this->max_speed ) ? VCMP( diff_x, 0 ) * this->max_speed : diff_x;
			diff_y = ( VABS( diff_y ) > this->max_speed ) ? VCMP( diff_y, 0 ) * this->max_speed : diff_y;

			// Muovo la camera
			this->MoveCameraPosition( diff_x, diff_y );

		} else {

			// Muovo la camera
			this->SetCameraPosition( Types::Floor( Types::Point2D(	target_pos.x - this->size.w / 2,
																	target_pos.y - this->size.h / 2 ) ) );
		}

		// Confino la telecamera all'interno della mappa
		if ( this->cam_pos.x < 0 ) this->cam_pos.x = 0;
		if ( this->cam_pos.y < 0 ) this->cam_pos.y = 0;
		if ( this->cam_pos.x + this->size.w > scene_size.w ) this->cam_pos.x = scene_size.w - this->size.w;
		if ( this->cam_pos.y + this->size.h > scene_size.h ) this->cam_pos.y = scene_size.h - this->size.h;
	}
}

void
Viewer::DrawLayers( Scene &scene, Scene::Depth depth ) {

	// Ricavo il rettangolo della telecamera
	Types::Rect_f cam_r = this->GetCameraRectangle();

	// Verifico che siano delle piastrelle da disegnare
	if ( !scene.GetMapLayer( depth ).empty() ) {

		// Iteratori
		MapLayerList::const_iterator layer_iter	= scene.GetMapLayer( depth ).begin();
		MapLayerList::const_iterator layer_end	= scene.GetMapLayer( depth ).end();

		// Selezioni i livelli alla profondità scelta
		for ( ; layer_iter != layer_end; layer_iter++ ) {

			// Ricavo la dimensione della piastrella
			Types::Size2D_u tile_size = layer_iter->tileset->GetClipSize();

			// Iteratori
			Types::Int j, i;

			// Iteratori
			TileList::const_iterator iter	= layer_iter->tile_list.begin();
			TileList::const_iterator end	= layer_iter->tile_list.end();

			/* DISEGNO LA PORZIONE DELLA MAPPA */
			for ( ; iter != end; iter++ ) {

				// Ricavo la struttura della piastrella
				const Tile &tile = *iter;

				// Scelgo la piastrella nel tileset
				layer_iter->tileset->SetClipOffset( Types::Size2D_u( tile.x, tile.y ) );

				// Seleziono la porzione di piastrelle visibili
				Types::Int left		= VMAX(	(Types::Int) tile.coords.left,
											(Types::Int) this->GetCameraRectangle().left / (Types::Int) tile_size.w );

				Types::Int top		= VMAX(	(Types::Int) tile.coords.top,
											(Types::Int) this->GetCameraRectangle().top / (Types::Int) tile_size.h );

				Types::Int right	= VMIN(	(Types::Int) tile.coords.right,
											(Types::Int) this->GetCameraRectangle().right / (Types::Int) tile_size.w );

				Types::Int bottom	= VMIN(	(Types::Int) tile.coords.bottom,
											(Types::Int) this->GetCameraRectangle().bottom / (Types::Int) tile_size.h );

				// Disegno le piastrelle dell'area richiesta
				for ( i = left; i <= right; i++ ) {

					for ( j = top; j <= bottom; j++ ) {

						// Disegno la singola piastrella
						layer_iter->tileset->Draw(

							Types::Point2D(


									this->GetPosition() - this->cam_pos + \

									Types::Point2D(	(Types::Float) i * (Types::Float) tile_size.w,
													(Types::Float) j * (Types::Float) tile_size.h )
							),

						this->GetColor() );
					}
				}
			}
		}
	}
}

void
Viewer::DrawObject( const EntityList &entity_list ) {

	// Iteratori
	EntityList::const_iterator iter = entity_list.begin();
	EntityList::const_iterator end = entity_list.end();

	// Disegna gli oggetti
	for ( ; iter != end; iter++ ) {

		// Prendo in considerazione un oggetto
		Entity *entity = (*iter);

		// Controllo la visibilità dell'oggetto
		if ( entity->GetVisible() ) {

			// Ricavo l'area di visibilità dell'entità
			const BoundingArea &area = entity->GetVisibilityArea();

			// Controllo che l'oggetto nello schermo sia "fisso"
			if ( entity->GetFixed() ||
				 area.CollideRectangularArea( Types::Rect_f(	this->cam_pos.x,
				 												this->cam_pos.y,
				 												this->cam_pos.x + this->size.w,
				 												this->cam_pos.y + this->size.h ) ) ) {

				// Disegno l'oggetto
				if ( !entity->GetFixed() )

					entity->Draw(	Types::Floor( this->GetPosition() - this->GetCameraPosition() ),
									( this->GetColorBlending() ) ? this->color : NULL );
				else
					entity->Draw( Types::Floor( this->GetPosition() ), ( this->GetColorBlending() ) ? this->color : NULL );
			}
		}
	}
}

void
Viewer::DrawFrame() {

	// Disegno la cornice del visualizzatore
	this->GetBox().Draw( this->GetEngine()->GetDesigner(), this->GetPosition(), this->size, NULL );
}

void
Viewer::DrawScene( Scene &scene ) {

	// Imposto la visualizzazione
	this->Active( true );

	// Disegna la scena (strato inferiore)
	this->DrawLayers( scene, Scene::BOTTOM );

	// Disegna gli oggetti della scena
	this->DrawObject( scene.GetEntityList() );

	// Disegna la scena (strato superiore)
	this->DrawLayers( scene, Scene::TOP );

	// Rimuovo la visualizzazione
	this->Active( false );

	// Disegna la cornice del visualizzatore
	this->DrawFrame();
}

}; // Chiudo il namespace di VGE

#endif
