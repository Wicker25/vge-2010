/* 
    Title --- maker.cpp

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


#ifndef VGE_MAKER_CPP
#define VGE_MAKER_CPP

#include "vge/maker.hpp"

#include "vge/utf8.hpp"
#include "vge/inline/utf8-inl.hpp"

#include "vge/xml.hpp"
#include "vge/inline/xml-inl.hpp"

#include "vge/color.hpp"
#include "vge/inline/color-inl.hpp"

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

#include "vge/particle-system.hpp"
#include "vge/inline/particle-system-inl.hpp"

#include "vge/scene.hpp"
#include "vge/inline/scene-inl.hpp"

#include "vge/engine.hpp"
#include "vge/inline/engine-inl.hpp"

#include "vge/widgets/box.hpp"
#include "vge/widgets/inline/box-inl.hpp"

#include "vge/inline/maker-inl.hpp"

namespace VGE { // Namespace di VGE

Types::Bool
Maker::StringToColor( const std::wstring &string, Color::RGBA8 *color ) {

	// Esito del riscontro
	Types::Bool found = false;

	// Colore estratto
	Types::Uint8 tmp[4];

	// Controllo la sintassi del colore
	if ( wcsncmp( string.c_str(), L"RGB", 3 ) == 0 ) {

		// Cerco il colore
		if ( swscanf( string.c_str(), L"RGBA(%u,%u,%u,%u)", &tmp[0], &tmp[1], &tmp[2], &tmp[3] ) == 4 ) {

			// Ritorno il colore
			*color = Color::Make( tmp[0], tmp[1], tmp[2], tmp[3] );

			// Modifico l'esito del riscontro
			found = true;

		} else if ( swscanf( string.c_str(), L"RGB(%u,%u,%u)", &tmp[0], &tmp[1], &tmp[2] ) == 3 ) {

			// Ritorno il colore
			*color = Color::Make( tmp[0], tmp[1], tmp[2] );

			// Modifico l'esito del riscontro
			found = true;
		}

	} else {

		// Ritorno il colore
		*color = Color::Make( (Color::RGBA8) wcstoul( string.c_str(), NULL, 16 ) );

		// Modifico l'esito del riscontro
		found = true;
	}

	return found;
}

Entity *
Maker::LoadEntity( const std::string &path ) {

	// Puntatore alla nuova entità
	Entity *new_entity = NULL;

	// Log di lavoro
	printf( "<Entity \"%s\">\n", path.c_str() );

	// Codice xml dell'entità
	std::wstring code;

	// Carico il file xml in memoria
	VGE::Utf8 in( path.c_str(), VGE::IN );

	// Controllo se il file è stato aperto correttamente
	if ( in.IsOpen() ) {

		// Memorizzo il testo
		in.Read( code );

		// Chiudo il file
		in.Close();

		// Controllo che il file non sia vuoto
		if ( !code.empty() ) {

			// Estraggo il nodo principale
			Xml main_node( code.data(), T_ENTITY, NULL );

			// Controllo l'esistenza del nodo
			if ( main_node.Exist() ) {

				// Puntatore all'attributo
				wchar_t *attr = NULL;

				// Cerco il tipo dell'entità
				if ( main_node.GetAttribute( A_TYPE, &attr ) ) {

					// Creo un'entità semplice
					if ( wcscasecmp( attr, V_ENTITY ) == 0 )

						new_entity = VGE_ENTITY( new Entity( &main_node ) );

					// Creo un'immagine
					else if ( wcscasecmp( attr, V_IMAGE ) == 0 )

						new_entity = VGE_ENTITY( new Image( &main_node ) );

					// Creo uno sprite
					else if ( wcscasecmp( attr, V_SPRITE ) == 0 )

						new_entity = VGE_ENTITY( new Sprite( &main_node ) );

					// Creo un oggetto
					else if ( wcscasecmp( attr, V_OBJECT ) == 0 )

						new_entity = VGE_ENTITY( new Object( &main_node ) );

					// Creo un personaggio
					else if ( wcscasecmp( attr, V_CHARACTER ) == 0 )

						new_entity = VGE_ENTITY( new Character( &main_node ) );

					// Creo un giocatore
					else if ( wcscasecmp( attr, V_PLAYER ) == 0 )

						new_entity = VGE_ENTITY( new Player( &main_node ) );

					// Creo un sistema particellare
					else if ( wcscasecmp( attr, V_PARTICLE_SYSTEM ) == 0 )

						new_entity = VGE_ENTITY( new ParticleSystem( &main_node ) );
					else
						// Comunico l'errore
						fprintf( stderr, INVALID_TYPE_W, BROKE, attr );

					// Controllo se l'entità è stata creata
					if ( new_entity != NULL )

						// Estraggo la lista degli eventi dell'entità
						new_entity->ExtractEventList( &main_node );
				}

			} else {

				// Comunico l'errore
				fprintf( stderr, NO_TAG_FOUND_W, BROKE, 0u, T_ENTITY );
			}

		} else {

			// Comunico l'errore
			fprintf( stderr, EMPTY_FILE, BROKE, path.c_str() );
		}

	} else {

		// Comunico l'errore
		fprintf( stderr, CANNOT_OPEN_FILE, BROKE, path.c_str() );
	}

	// Log di lavoro
	printf( "</Entity>\n" );

	// Ritorno il puntatore alla nuova entità
	return new_entity;
}

// <frame color="FF8000FF" border_color="00000000" border_width="2" filled="true" />

void
Maker::ExtractFrame( const Xml *node, const wchar_t *tag_name, Gui::Box *frame ) {

	// Cerco il nodo del frame
	Xml frame_node = node->Child( tag_name );

	// Controllo l'esistenza del nodo
	if ( frame_node.Exist() ) {

		// Puntatore all'attributo
		wchar_t *attr = NULL;

		// Colore
		Color::RGBA8 color;

		// Cerco il colore
		if ( frame_node.GetAttribute( A_COLOR, &attr ) ) {

			// Converto la stringa nel colore
			if ( Maker::StringToColor( attr, &color ) ) {

				// Imposto il colore del riquadro
				frame->SetColor( color );

			} else {

				// Comunico l'errore
				fprintf( stderr, WRONG_SYNTAX_OF_W, BROKE, frame_node.GetRow(), A_COLOR );	
			}
		}

		// Cerco il colore
		if ( frame_node.GetAttribute( A_BORDER_COLOR, &attr ) ) {

			// Converto la stringa nel colore
			if ( Maker::StringToColor( attr, &color ) ) {

				// Imposto il colore del bordo
				frame->SetBorderColor( color );

			} else {

				// Comunico l'errore
				fprintf( stderr, WRONG_SYNTAX_OF_W, BROKE, frame_node.GetRow(), A_BORDER_COLOR );	
			}
		}

		// Cerco lo spessore del bordo
		if ( frame_node.GetAttribute( A_BORDER_WIDTH, &attr ) )

			// Modifico lo spessore del bordo
			frame->SetBorderWidth( (Types::Uint8) wcstoul( attr, NULL, 10 ) );
	}
}

/*
	<area>

		<vertex coord="-40,-120" />
		<vertex coord="-40,30" />
		... ... ... ...

	</area>
*/

void
Maker::ExtractBoundingArea( const Xml *node, const wchar_t *tag_name, BoundingArea *area ) {

	// Cerco il nodo dell'area
	Xml area_node = node->Child( tag_name );

	// Controllo l'esistenza del nodo
	if ( area_node.Exist() ) {

		// Pulisco la lista dei vertici
		area->Clear();

		// Struttura del vertice
		Types::Point2D vertex;

		// Iteratore
		wchar_t *iter = NULL;

		// Puntatore all'attributo
		wchar_t *attr = NULL;

		// Flag di controllo
		bool end = false;

		do {

			// Cerco il nodo del vertice
			Xml vertex_node = area_node.Child( T_VERTEX, &iter );

			// Controllo l'esistenza del nodo
			if ( vertex_node.Exist() ) {

				// Cerco le coordinate del vertice
				if ( vertex_node.GetAttribute( A_COORDS, &attr ) ) {

					if ( swscanf( attr, L"%f,%f", &vertex.x, &vertex.y ) != 2 ) {

						// Comunico l'errore
						fprintf( stderr, WRONG_SYNTAX_OF_W, WARNING, vertex_node.GetRow(), A_COORDS );
					}

					// Aggiungo il punto all'area
					area->AddVertex( vertex );
				}

			} else end = true;

		} while ( !end );

		// Aggiorno l'area
		area->ForceUpdate();
 	}
}

Types::Bool
Maker::SaveEntity( const Entity *entity, const std::string &path ) {

	// Flag di controllo
	Types::Bool written = false;

	// Controllo i parametri
	if ( entity != NULL && !path.empty() ) {

		// Carico il file xml in memoria
		VGE::Utf8 out( path.c_str(), VGE::OUT );

		// Controllo se il file è stato aperto correttamente
		if ( out.IsOpen() ) {

			// Richiamo la funzione di salvataggio dell'entità
			entity->Save( &out );

			// Imposto il flag di controllo
			written = true;

			// Chiudo il flusso del file
			out.Close();
		}
	}

	return written;
}

Scene *
Maker::LoadScene( const std::string &path ) {

	// Puntatore alla nuova entità
	Scene *new_scene = NULL;

	// Log di lavoro
	printf( "<Scene \"%s\">\n", path.c_str() );

	// Codice xml dell'entità
	std::wstring code;

	// Carico il file xml in memoria
	VGE::Utf8 in( path.c_str(), VGE::IN );

	// Controllo se il file è stato aperto correttamente
	if ( in.IsOpen() ) {

		// Memorizzo il testo
		in.Read( code );

		// Chiudo il file
		in.Close();

		// Controllo che il file non sia vuoto
		if ( !code.empty() ) {

			// Estraggo il nodo principale
			Xml main_node( code.data(), T_SCENE, NULL );

			new_scene = new Scene( &main_node );

		} else {

			// Comunico l'errore
			fprintf( stderr, EMPTY_FILE, FATAL, path.c_str() );
		}

	} else {

		// Comunico l'errore
		fprintf( stderr, CANNOT_OPEN_FILE, BROKE, path.c_str() );
	}

	// Log di lavoro
	printf( "</Scene>\n" );

	return new_scene;
}

}; // Chiudo il namespace di VGE

#endif
