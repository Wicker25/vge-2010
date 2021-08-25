/* 
    Title --- entity-maker.cpp

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


#ifndef VGE_ENTITY_MAKER_CPP
#define VGE_ENTITY_MAKER_CPP

#include "vge/entity.hpp"

#include "vge/utf8.hpp"
#include "vge/inline/utf8-inl.hpp"

#include "vge/xml.hpp"
#include "vge/inline/xml-inl.hpp"

#include "vge/interfaces/i-programmable.hpp"
#include "vge/interfaces/inline/i-programmable-inl.hpp"

#include "vge/entity.hpp"
#include "vge/inline/entity-inl.hpp"

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

#include "vge/maker.hpp"
#include "vge/inline/maker-inl.hpp"

#include "vge/image.hpp"
#include "vge/inline/image-inl.hpp"

#include "vge/widgets/font.hpp"
#include "vge/widgets/inline/font-inl.hpp"

#include "vge/widgets/message-box.hpp"
#include "vge/widgets/inline/message-box-inl.hpp"

#include "vge/inline/entity-inl.hpp"

namespace VGE { // Namespace di VGE

Entity::Entity( const Xml *node ) {

	// Aggiungo l'entità alla lista generale
	Global::Entities.push_back( this );

	// Imposto l'identificativo del tipo di entità
	this->SetMask( ENTITY_MASK );

	/* Costruzione dell'entità */

	// Estraggo il nome dell'entità
	this->ExtractName( node );

	// Estraggo la posizione dell'entità
	this->ExtractPosition( node );

	// Estraggo il centro dell'entità
	this->ExtractCenter( node );

	// Estraggo i flags dell'entità
	this->ExtractFlags( node );

	// Estraggo l'area di visibilità dell'entità
	this->ExtractVisibilityArea( node );

	/* ======================= */

	// Collego l'entità all'engine
	this->SetEngine( NULL );

	// Collego l'entità alla scene
	this->SetScene( NULL );

	// Imposto la modalità di debug
	this->SetDebugMode( false );
	//this->SetDebugMode( true );
}

// <entity name="Wicker25"

void
Entity::ExtractName( const Xml *node ) {

	// Puntatore all'attributo
	wchar_t *attr = NULL;

	// Cerco il nome dell'entità
	if ( node->GetAttribute( A_NAME, &attr ) && ( attr != NULL ) ) {

		// Log di lavoro
		printf( " Name:\t\t%ls\n", attr );

		// Modifico il nome dell'entità
		this->SetName( attr );

	} else {

		// Comunico l'errore
		fprintf( stderr, NO_ATTRIBUTE_FOUND_W, BROKE, node->GetRow(), A_NAME );
	}
}

// coord="380,250,250"

void
Entity::ExtractPosition( const Xml *node ) {

	// Nuova posizione
	Types::Point3D tmp( 0.0f, 0.0f, 0.0f );

	// Puntatore all'attributo
	wchar_t *attr = NULL;

	// Cerco la posizione dell'entità
	if ( node->GetAttribute( A_COORDS, &attr ) ) {

		if ( swscanf( attr, L"%f,%f,%f", &tmp.x, &tmp.y, &tmp.z ) < 2 ) {

			// Comunico l'errore
			fprintf( stderr, WRONG_SYNTAX_OF_W, WARNING, node->GetRow(), A_COORDS );

		} else {

			// Log di lavoro
			printf( " Coord:\t\t%.1f ' %.1f ' %.1f\n", tmp.x, tmp.y, tmp.z );
		}
	}

	// Modifico la posizione dell'entità
	this->SetPosition( Types::Point3D( tmp.x, tmp.y, tmp.z ) );
}

// center="15,20"

void
Entity::ExtractCenter( const Xml *node ) {

	// Nuova centro
	Types::Point2D tmp( 0.0f, 0.0f );

	// Puntatore all'attributo
	wchar_t *attr = NULL;

	// Cerco il centro dell'entità
	if ( node->GetAttribute( A_CENTER, &attr ) ) {

		if ( swscanf( attr, L"%f,%f", &tmp.x, &tmp.y ) != 2 ) {

			// Comunico l'errore
			fprintf( stderr, WRONG_SYNTAX_OF_W, WARNING, node->GetRow(), A_CENTER );

		} else {

			// Log di lavoro
			//printf( " Center:\t%.1f ' %.1f\n", tmp.x, tmp.y );
		}
	}

	// Modifico il centro dell'entità
	this->SetCenter( Types::Point2D( tmp.x, tmp.y ) );
}

// fixed="false" visible="true" sensible="true" >

void
Entity::ExtractFlags( const Xml *node ) {

	// Puntatore all'attributo
	wchar_t *attr = NULL;

	// Cerco la visibilità
	if ( node->GetAttribute( A_VISIBLE, &attr ) )

		// Modifico la visibilità dell'entità
		this->SetVisible( ( wcscasecmp( attr, V_TRUE ) == 0 ) );
	else
		// Modifico la visibilità dell'entità
		this->SetVisible( true );

	// Cerco la posizione rispetto allo schermo
	if ( node->GetAttribute( A_FIXED, &attr ) )

		// Modifico la posizione dell'entità rispetto allo schermo
		this->SetFixed( ( wcscasecmp( attr, V_TRUE ) == 0 ) );
	else
		// Modifico la posizione dell'entità rispetto allo schermo
		this->SetFixed( false );

	// Cerco la sensibilità
	if ( node->GetAttribute( A_SENSIBLE, &attr ) )

		// Modifico la sensibilità dell'entità
		this->SetSensible( ( wcscasecmp( attr, V_TRUE ) == 0 ) );
	else
		// Modifico la sensibilità dell'entità
		this->SetSensible( true );
}

/*
	<varea>

		<vertex coord="-40,-120" />
		<vertex coord="-40,30" />
		... ... ... ...

	</varea>
*/

void
Entity::ExtractVisibilityArea( const Xml *node ) {

	// Estraggo l'area di visibilità dell'entità
	Maker::ExtractBoundingArea( node, T_VAREA, &this->GetVisibilityArea() );
}

/*
	<event_list loop="true">

		<event type="transient_color" value0="0000FFFF" value1="30" />
		<event type="move_right" value0="120" />
		<event type="move_left" value0="120" />
		... ... ... ...

	</event_list>
*/

void
Entity::ExtractEventList( const Xml *node ) {

	// Cerco il nodo "event_list"
	Xml event_list_node = node->Child( T_EVENT_LIST );

	// Controllo l'esistenza del nodo
	if ( event_list_node.Exist() ) {

		// Puntatore all'attributo
		wchar_t *attr = NULL;

		// Cerco la ciclicità degli eventi
		if ( event_list_node.GetAttribute( A_LOOP, &attr ) )

			this->SetEventLoop( wcscasecmp( attr, V_TRUE ) == 0 );

		// Iteratore
		wchar_t *iter = NULL;

		// Flag di controllo
		bool end = false;

		do {

			// Cerco il nodo dell'evento
			Xml event_node = event_list_node.Child( T_EVENT, &iter );

			// Controllo l'esistenza del nodo
			if ( event_node.Exist() ) {

				// Cerco il tipo dell'evento
				if ( event_node.GetAttribute( A_TYPE, &attr ) && attr != NULL ) {

					// Parametri dell'evento
					std::vector< wchar_t *> values;

					// Nome del parametro
					wchar_t param_name[7];

					// Iteratore
					Types::Uint i = 0;

					// Cerco i parametri dell'evento
					for ( ; i < 6; i++ ) {

						// Valore del parametro
						wchar_t *val;

						// Preparo il nome del parametro
						swprintf( param_name, 7, L"%ls%u\0", A_VALUE, i );

						// Estraggo il parametro
						if ( event_node.GetAttribute( param_name, &val ) )

							values.push_back( val );
						else
							i = 10;
					}

					// Estraggo l'evento dalla lista
					this->ExtractEvent( &event_node, attr, values );

				} else {

					// Comunico l'errore
					fprintf( stderr, INVALID_TYPE_LINE_W, WARNING, node->GetRow(), attr );
				}

			} else end = true;

		} while ( !end );
	}
}

void
Entity::ExtractEvent( const Xml *node, const wchar_t *type, std::vector< wchar_t *> &values ) {

	// Modifica della visibilità
	if ( wcscasecmp( type, V_EVENT_SET_VISIBLE ) == 0 ) {

		// Controllo il numero dei parametri
		if ( values.size() >= 1 ) {

			// Aggiungo l'evento alla lista
			this->AddEvent( EventType::SET_VISIBLE, wcscasecmp( values[0], V_TRUE ) == 0 );
		}

	// Modifica della posizione rispetto alla camera
	} else if ( wcscasecmp( type, V_EVENT_SET_FIXED ) == 0 ) {

		// Controllo il numero dei parametri
		if ( values.size() >= 1 ) {

			// Aggiungo l'evento alla lista
			this->AddEvent( EventType::SET_FIXED, wcscasecmp( values[0], V_TRUE ) == 0 );
		}

	// Modifica la sensibilità dell'entità
	} else if ( wcscasecmp( type, V_EVENT_SET_SENSIBLE ) == 0 ) {

		// Controllo il numero dei parametri
		if ( values.size() >= 1 ) {

			// Aggiungo l'evento alla lista
			this->AddEvent( EventType::SET_SENSIBLE, wcscasecmp( values[0], V_TRUE ) == 0 );
		}

	// Modifica della posizione
	} else if ( wcscasecmp( type, V_EVENT_SET_POSITION ) == 0 ) {

		// Controllo il numero dei parametri
		if ( values.size() >= 2 ) {

			// Aggiungo l'evento alla lista
			this->AddEvent( EventType::SET_POSITION,	wcstof( values[0], NULL ),
														wcstof( values[1], NULL ) );
		}

	// Modifica della posizione relativa
	} else if ( wcscasecmp( type, V_EVENT_MOVE_POSITION ) == 0 ) {

		// Controllo il numero dei parametri
		if ( values.size() >= 2 ) {

			// Aggiungo l'evento alla lista
			this->AddEvent( EventType::MOVE_POSITION,	wcstof( values[0], NULL ),
														wcstof( values[1], NULL ) );
		}

	// Comparsa di un messaggio di sistema
	} else if ( wcscasecmp( type, V_EVENT_SHOW_MESSAGE ) == 0 ) {

		// Controllo il numero dei parametri
		if ( values.size() >= 1 ) {

			// Aggiungo l'evento alla lista
			this->AddEvent( EventType::SHOW_MESSAGE, values[0] );
		}

	// Attesa del dialogo
	} else if ( wcscasecmp( type, V_EVENT_WAIT_DIALOG ) == 0 ) {

		// Aggiungo l'evento alla lista
		this->AddEvent( EventType::WAIT_DIALOG );

	// Attesa in secondi
	} else if ( wcscasecmp( type, V_EVENT_WAIT_SECONDS ) == 0 ) {

		// Controllo il numero dei parametri
		if ( values.size() >= 1 ) {

			// Aggiungo l'evento alla lista
			this->AddEvent( EventType::WAIT_SECONDS, wcstof( values[0], NULL ) );
		}
	}
}

void
Entity::Save( Utf8 *stream ) const {

	// Scrivo l'intestazione del file xml
	stream->Write( L"<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n\n" );

	// Nome del tipo dell'entità
	const wchar_t *type = NULL;

	// Controllo il tipo dell'entità
	switch ( this->GetMask() ) {

		case ENTITY_MASK: { type = V_ENTITY; break; }

		case PARTICLE_SYSTEM_MASK: { type = V_PARTICLE_SYSTEM; break; }

		case IMAGE_MASK: { type = V_IMAGE; break; }

		case SPRITE_MASK: { type = V_SPRITE; break; }

		case OBJECT_MASK: { type = V_OBJECT; break; }

		case CHARACTER_MASK: { type = V_CHARACTER; break; }

		case PLAYER_MASK: { type = V_PLAYER; break; }

		default: break;
	}

	// Apro il tag principale
	stream->Write( L"<%ls %ls=\"%ls\" %ls=\"%ls\" %ls=\"%.2f,%.2f\" "
							L"%ls=\"%.2f,%.2f\" %ls=\"%ls\" %ls=\"%ls\" %ls=\"%ls\" >\n\n",

			T_ENTITY,
			A_NAME, this->GetName().c_str(),
			A_TYPE, type,
			A_COORDS, this->position.x, this->position.y,
			A_CENTER, this->center.x, this->center.y,
			A_VISIBLE, ( this->GetVisible() ) ? V_TRUE : V_FALSE,
			A_FIXED, ( this->GetFixed() ) ? V_TRUE : V_FALSE,
			A_SENSIBLE, ( this->GetSensible() ) ? V_TRUE : V_FALSE
	);

	// Scrivo le informazioni sull'entità
	this->WriteInfo( stream );

	// Scrivo le informazioni sull'area dell'entità
	this->WriteBoundingArea( stream );

	// Controllo se sono stati definiti degli eventi
	if ( !this->GetEventList().empty() )

		// Scrivo la lista degli eventi dell'entità
		this->WriteEventList( stream );

	// Chiudo il tag principale
	stream->Write( L"</%ls>\n", T_ENTITY );
}

void
Entity::WriteInfo( Utf8 *stream ) const {

}

void
Entity::WriteBoundingArea( Utf8 *stream ) const {

	// Ricavo l'area di visibilità
	const Types::Point2DList &list = this->GetVisibilityArea().GetVertices();

	// Iteratore
	Types::Uint i = 0;

	// Apro il tag dell'area di visibilità
	stream->Write( L"\t<%ls>\n\n", T_VAREA );

	// Scrivo i vertici dell'are
	for ( ; i < list.size(); i++ )

		stream->Write( L"\t\t<%ls %ls=\"%.2f,%.2f\" />\n", T_VERTEX, A_COORDS, list[i].x, list[i].y );

	// Chiudo il tag dell'area di visibilità
	stream->Write( L"\n\t</%ls>\n\n", T_VAREA );
}

void
Entity::WriteEventList( Utf8 *stream ) const {

	// Ricavo l'area di visibilità
	const EventList &list = this->GetEventList();

	// Iteratori
	EventList::const_iterator iter	= list.begin();
	EventList::const_iterator end	= list.end();

	// Apro il tag dell'area di visibilità
	stream->Write( L"\t<%ls %ls=\"%ls\">\n\n",

			T_EVENT_LIST,
			A_LOOP, ( this->GetEventLoop() ) ? V_TRUE : V_FALSE
	);

	// Scrivo gli eventi dell'entità
	for ( ; iter != end; iter++ )

		this->WriteEvent( stream, *iter );

	// Chiudo il tag dell'area di visibilità
	stream->Write( L"\n\t</%ls>\n\n", T_EVENT_LIST );
}

Types::Bool
Entity::WriteEvent( Utf8 *stream, Event *event ) const {

	// Flag di controllo
	Types::Bool found = true;

	// Controllo il tipo dell'evento
	switch ( event->type ) {

		// Cambio della visibilità
		case EventType::SET_VISIBLE: {

			stream->Write( L"\t\t<%ls %ls=\"%ls\" %ls0=\"%ls\" />\n",

					T_EVENT,
					A_TYPE, V_EVENT_SET_VISIBLE,
					A_VALUE, ( event->arg0[1] ) ? V_TRUE : V_FALSE
			);

			break;
		}

		// Cambio della posizione rispetto allo schermo
		case EventType::SET_FIXED: {

			stream->Write( L"\t\t<%ls %ls=\"%ls\" %ls0=\"%ls\" />\n",

					T_EVENT,
					A_TYPE, V_EVENT_SET_FIXED,
					A_VALUE, ( event->arg0[1] ) ? V_TRUE : V_FALSE
			);

			break;
		}

		// Cambio della sensibilità
		case EventType::SET_SENSIBLE: {

			stream->Write( L"\t\t<%ls %ls=\"%ls\" %ls0=\"%ls\" />\n",

					T_EVENT,
					A_TYPE, V_EVENT_SET_SENSIBLE,
					A_VALUE, ( event->arg0[1] ) ? V_TRUE : V_FALSE
			);

			break;
		}

		// Cambio della posizione
		case EventType::SET_POSITION: {

			stream->Write( L"\t\t<%ls %ls=\"%ls\" %ls0=\"%.2f\" %ls1=\"%.2f\" />\n",

					T_EVENT,
					A_TYPE, V_EVENT_SET_POSITION,
					A_VALUE, event->arg0[1],
					A_VALUE, event->arg1[1]
			);

			break;
		}

		// Cambio della posizione (relativa)
		case EventType::MOVE_POSITION: {

			stream->Write( L"\t\t<%ls %ls=\"%ls\" %ls0=\"%.2f\" %ls1=\"%.2f\" />\n",

					T_EVENT,
					A_TYPE, V_EVENT_MOVE_POSITION,
					A_VALUE, event->arg0[1],
					A_VALUE, event->arg1[1]
			);

			break;
		}

		// Comparsa di un messaggio di sistema
		case EventType::SHOW_MESSAGE: {

			stream->Write( L"\t\t<%ls %ls=\"%ls\" %ls0=\"%ls\" />\n",

					T_EVENT,
					A_TYPE, V_EVENT_SHOW_MESSAGE,
					A_VALUE, event->string.c_str()
			);

			break;
		}

		// Attesa della chiusura di un messaggio di sistema
		case EventType::WAIT_DIALOG: {

			stream->Write( L"\t\t<%ls %ls=\"%ls\" />\n",

					T_EVENT,
					A_TYPE, V_EVENT_WAIT_DIALOG
			);

			break;
		}

		// Attesa di alcuni secondi
		case EventType::WAIT_SECONDS: {

			stream->Write( L"\t\t<%ls %ls=\"%ls\" %ls0=\"%.2f\" />\n",

					T_EVENT,
					A_TYPE, V_EVENT_WAIT_SECONDS,
					A_VALUE, event->arg0[1]
			);
			break;
		}

		default: {

			found = false;
			break;
		}
	}

	return found;
}

}; // Chiudo il namespace di VGE

#endif
