/* 
    Title --- scene-maker.cpp

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


#ifndef VGE_SCENE_MAKER_CPP
#define VGE_SCENE_MAKER_CPP

#include "vge/scene.hpp"

#include "vge/xml.hpp"
#include "vge/inline/xml-inl.hpp"

#include "vge/input-manager.hpp"
#include "vge/inline/input-manager-inl.hpp"

#include "vge/interfaces/i-resizable.hpp"
#include "vge/interfaces/inline/i-resizable-inl.hpp"

#include "vge/interfaces/i-image.hpp"
#include "vge/interfaces/inline/i-image-inl.hpp"

#include "vge/image.hpp"
#include "vge/inline/image-inl.hpp"

#include "vge/engine.hpp"
#include "vge/inline/engine-inl.hpp"

#include "vge/inline/scene-inl.hpp"

namespace VGE { // Namespace di VGE

Scene::Scene( const Xml *node ) {

	/* Costruzione della scena */

	// Inizializzo le strutture
	this->mouse_viewer	= NULL;

	// Puntatore all'attributo
	wchar_t *attr = NULL;

	// Cerco il nome della scena
	if ( !node->GetAttribute( A_NAME, &attr ) ) {

		// Comunico l'errore
		fprintf( stderr, NO_ATTRIBUTE_FOUND_W, WARNING, node->GetRow(), A_NAME );
	}

	// Memorizzo il nome della scena
	this->SetName( attr );

	// Log di lavoro
	printf( " Name:\t\t%ls\n", this->GetName().c_str() );

	// Cerco la dimensione della scena
	if ( node->GetAttribute( A_SIZE, &attr ) ) {

		// Estraggo le dimensioni della scena
		if ( swscanf( attr, L"%u,%u", &this->size.w, &this->size.h ) != 2 ) {

			// Comunico l'errore
			fprintf( stderr, WRONG_SYNTAX_OF_W, WARNING, node->GetRow(), A_SIZE );
		}
	}

	// Log di lavoro
	printf( " Size:\t\t%ux%u\n", this->size.w, this->size.h );

	// Estraggo i livelli della scena
	this->ExtractLayers( node );
}

// <layer tileset="tileset/tileset_0.png" depth="bottom">

void
Scene::ExtractLayers( const Xml *node ) {

	// Percorso del tileset
	std::wstring tileset;

	// Dimensione della piastrella
	Types::Size2D_u tile_size;

	// Profondità del livello
	Scene::Depth depth;
	
	// Opacità del tileset
	Types::Uint8 opacity;

	// Puntatore all'attributo
	wchar_t *attr;

	// Iteratore
	wchar_t *iter = NULL;

	// Variabile di controllo
	Types::Bool end = false;

	do {

		// Cerco un nodo dello strato
		Xml layer_node = node->Child( T_LAYER, &iter );

		// Verifico l'esistenza del nodo
		if ( layer_node.Exist() ) {

			// Cerco il percorso del tileset
			if ( layer_node.GetAttribute( A_TILESET, &attr ) ) {

				// Memorizzo il percorso del tileset
				tileset = attr;

				// Log di lavoro
				printf( " Tileset:\t%ls\n", tileset.c_str() );

				// Cerco la dimensione della scena
				if ( layer_node.GetAttribute( A_TILE_SIZE, &attr ) ) {

					// Estraggo le dimensioni della scena
					if ( swscanf( attr, L"%u,%u", &tile_size.w, &tile_size.h ) != 2 ) {

						// Comunico l'errore
						fprintf( stderr, WRONG_SYNTAX_OF_W, WARNING, layer_node.GetRow(), A_SIZE );
					}

					// Log di lavoro
					printf( " Tile size:\t%dx%d\n", tile_size.w, tile_size.h );

					// Cerco l'opacità del tileset
					if ( layer_node.GetAttribute( A_OPACITY, &attr ) ) {

						// Estraggo l'opacità del tileset
						opacity = (Types::Uint8) wcstoul( attr, NULL, 10 );

					} else {

						// Imposto l'opacità del tileset
						opacity = 255;
					}

					// Cerco la profondità del livello
					if ( layer_node.GetAttribute( A_DEPTH, &attr ) ) {

						// Controlla la profondità del livello
						if ( !wcscasecmp( attr, A_BOTTOM ) ) {

							depth = Scene::BOTTOM;

						// Estrae la lista delle piastrelle del secondo strato
						} else if ( !wcscasecmp( attr, A_TOP ) ) {

							depth = Scene::TOP;
						}

					} else {

						// Comunico l'errore
						fprintf( stderr, NO_ATTRIBUTE_FOUND_W, FATAL, layer_node.GetRow(), A_DEPTH );

						// Imposto la profondità standard
						depth = Scene::BOTTOM;
					}

					// Carico l'immagine del tileset
					this->AddMapLayer( Types::WideToString( tileset ), tile_size, depth, opacity );

					// Estraggo le piastrelle del livello
					Types::Uint num = this->ExtractTileList( &layer_node, depth, this->layer_list[depth].size() - 1 );

					// Log di lavoro
					printf( " Tiles: %u\n", num );

				// Comunico l'errore all'utente
				} else fprintf( stderr, NO_ATTRIBUTE_FOUND_W, BROKE, layer_node.GetRow(), A_TILE_SIZE );

			// Comunico l'errore all'utente
			} else fprintf( stderr, NO_ATTRIBUTE_FOUND_W, BROKE, layer_node.GetRow(), A_TILESET );

		} else end = true;

	} while ( !end );
}

Types::Uint
Scene::ExtractTileList( const Xml *node, Scene::Depth depth, Types::Uint layer ) {

	// Posizione della piastrella
	Types::Point2D position;

	// Puntatore ad una stringa
	wchar_t *attr;

	// Iteratore
	wchar_t *iter = NULL;

	// Variabile di controllo
	Types::Bool end = false;

	do {

		// Cerco il nodo della piastrella
		Xml tile_node = node->Child( T_TILE, &iter );

		// Verifico l'esistenza del nodo
		if ( tile_node.Exist() ) {

			// Cerco l'ascissa della piastrella nel tileset
			if ( tile_node.GetAttribute( A_LEFT, &attr ) ) {

				// Memorizzo l'ascissa della piastrella nel tileset
				position.x = (Types::Uint) wcstoul( attr, NULL, 10 );

			// Comunico l'errore all'utente
			} else fprintf( stderr, NO_ATTRIBUTE_FOUND_W, WARNING, tile_node.GetRow(), A_LEFT );

			// Cerco l'ordinata della piastrella nel tileset
			if ( tile_node.GetAttribute( A_TOP, &attr ) ) {

				// Memorizzo l'ordinata della piastrella nel tileset
				position.y = (Types::Uint) wcstoul( attr, NULL, 10 );

			// Comunico l'errore all'utente
			} else fprintf( stderr, NO_ATTRIBUTE_FOUND_W, WARNING, tile_node.GetRow(), A_TOP );

			// Cerco le coordinate della piastrella nella scena
			if ( tile_node.GetAttribute( A_COORDS, &attr ) ) {

				// Cordinate nella scena
				Types::Rect_u coords;

				// Estraggo e memorizzo le coordinate della piastrella nel tileset
				if ( extract_coords( coords, attr ) ) {

					// Cerco la solidità della piastrella
					Types::Bool solid = tile_node.GetAttribute( A_SOLID, &attr ) && !wcscasecmp( attr, V_TRUE ) ;

					// Aggiungo la piastrella alla scena
					this->AddTile( depth, layer, position, coords, solid );

				// Comunico l'errore all'utente
				} else fprintf( stderr, VALUE_ERROR_W, WARNING, tile_node.GetRow(), A_COORDS );

			// Comunico l'errore all'utente
			} else fprintf( stderr, NO_ATTRIBUTE_FOUND_W, WARNING, tile_node.GetRow(), A_COORDS );

		} else end = true;

	} while ( !end );

	return (Types::Uint) this->layer_list[depth][layer].tile_list.size();
}

}; // Chiudo il namespace di VGE

#endif
