/* 
    Title --- object-maker.cpp

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


#ifndef VGE_OBJECT_MAKER_CPP
#define VGE_OBJECT_MAKER_CPP

#include "vge/object.hpp"

#include "vge/utf8.hpp"
#include "vge/inline/utf8-inl.hpp"

#include "vge/xml.hpp"
#include "vge/inline/xml-inl.hpp"

#include "vge/interfaces/i-programmable.hpp"
#include "vge/interfaces/inline/i-programmable-inl.hpp"

#include "vge/entity.hpp"
#include "vge/inline/entity-inl.hpp"

#include "vge/image.hpp"
#include "vge/inline/image-inl.hpp"

#include "vge/sprite.hpp"
#include "vge/inline/sprite-inl.hpp"

#include "vge/maker.hpp"
#include "vge/inline/maker-inl.hpp"

#include "vge/widgets/widget.hpp"
#include "vge/widgets/inline/widget-inl.hpp"

#include "vge/inline/object-inl.hpp"

namespace VGE { // Namespace di VGE

Object::Object( const Xml *node ): Sprite( node ) {

	// Imposto l'identificativo del tipo di entità
	this->SetMask( OBJECT_MASK );

	// Imposto la direzione iniziale
	this->SetDirection( DIRECTION_DOWN );

	// Imposto la velocità iniziale
	this->SetSpeed( 1.0f );

	// Imposto l'immagine faccia dell'oggetto
	this->SetFace( NULL );

	// Imposto l'indirizzo dell'ombra iniziale
	this->SetShadow( NULL );

	/* Costruzione dell'oggetto */

	// Estraggo le caratteristiche dell'oggetto
	this->ExtractObjFeatures( node );

	/* ======================= */

	// Aggiorno la profondità
	this->UpdateDepth();
}

// <object_features direction="down" speed="2.5" face="@face0" shadow="@shadow0" />

void
Object::ExtractObjFeatures( const Xml *node ) {

	// Cerco il nodo "object_features"
	Xml obj_features_node = node->Child( T_OBJ_FEATURES );

	// Controllo l'esistenza del nodo
	if ( obj_features_node.Exist() ) {

		// Puntatore all'attributo
		wchar_t *attr = NULL;

		// Cerco la direzione dell'oggetto
		if ( obj_features_node.GetAttribute( A_DIRECTION, &attr ) ) {

			// Direzione dell'oggetto
			Object::Direction direction = Object::DIRECTION_DOWN;

			// Controllo la direzione
			if ( wcscasecmp( attr, V_LEFT ) == 0 )

				direction = Object::DIRECTION_LEFT;

			else if ( wcscasecmp( attr, V_UP ) == 0 )

				direction = Object::DIRECTION_UP;

			else if ( wcscasecmp( attr, V_RIGHT ) == 0 )

				direction = Object::DIRECTION_RIGHT;

			else if ( wcscasecmp( attr, V_DOWN ) == 0 )

				direction = Object::DIRECTION_DOWN;

			else {

				// Comunico l'errore
				fprintf( stderr, WRONG_SYNTAX_OF_W, WARNING, obj_features_node.GetRow(), A_DIRECTION );
			}

			// Imposto la direzione dell'oggetto
			this->SetDirection( direction );
		}

		// Cerco la velocità dell'oggetto
		if ( obj_features_node.GetAttribute( A_SPEED, &attr ) ) {

			// Imposto la velocità dell'oggetto
			this->SetSpeed( (Types::Float) wcstof( attr, NULL ) );
		}

		// Cerco la faccia dell'oggetto
		if ( obj_features_node.GetAttribute( A_FACE, &attr ) ) {

			// Controllo la presenza del carattere di riferimento
			if ( attr[0] == L'@' ) {

				// Entità di riferimento
				Entity *ref = VGE::Global::GetEntity( attr + 1 );

				// Controllo l'esistenza dell'entità di riferimento
				if ( ref != NULL ) {

					// Imposto la faccia dell'oggetto
					this->SetFace( VGE_IMAGE( ref ) );

				} else {

					// Comunico l'errore
					fprintf( stderr, ENTITY_NOT_DEFINED_W, WARNING, obj_features_node.GetRow(), attr + 1 );
				}
			}
		}

		// Cerco l'ombra dell'oggetto
		if ( obj_features_node.GetAttribute( A_SHADOW, &attr ) ) {

			// Controllo la presenza del carattere di riferimento
			if ( attr[0] == L'@' ) {

				// Entità di riferimento
				Entity *ref = VGE::Global::GetEntity( attr + 1 );

				// Controllo l'esistenza dell'entità di riferimento
				if ( ref != NULL ) {

					// Imposto l'ombra dell'oggetto
					this->SetShadow( VGE_IMAGE( ref ) );

				} else {

					// Comunico l'errore
					fprintf( stderr, ENTITY_NOT_DEFINED_W, WARNING, obj_features_node.GetRow(), attr + 1 );
				}
			}
		}

		// Cerco il messaggio dell'oggetto
		if ( obj_features_node.GetAttribute( A_MESSAGE, &attr ) ) {

			// Imposto il messaggio dell'oggetto
			this->SetMessage( attr );
		}
	}
}

void
Object::ExtractEvent( const Xml *node, const wchar_t *type, std::vector< wchar_t *> &values ) {

	// Chiama la funzione della classe genitore
	Sprite::ExtractEvent( node, type, values );

	// Modifica della velocità
	if ( wcscasecmp( type, V_EVENT_SET_SPEED ) == 0 ) {

		// Controllo il numero dei parametri
		if ( values.size() >= 1 ) {

			// Aggiungo l'evento alla lista
			this->AddEvent( EventType::SET_SPEED, wcstof( values[0], NULL ) );
		}

	// Movimento a sinistra
	} else if ( wcscasecmp( type, V_EVENT_MOVE_LEFT ) == 0 ) {

		// Controllo il numero dei parametri
		if ( values.size() >= 1 ) {

			// Aggiungo l'evento alla lista
			this->AddEvent( EventType::MOVE_LEFT, wcstof( values[0], NULL ) );
		}

	// Movimento in alto
	} else if ( wcscasecmp( type, V_EVENT_MOVE_UP ) == 0 ) {

		// Controllo il numero dei parametri
		if ( values.size() >= 1 ) {

			// Aggiungo l'evento alla lista
			this->AddEvent( EventType::MOVE_UP, wcstof( values[0], NULL ) );
		}

	// Movimento a destra
	} else if ( wcscasecmp( type, V_EVENT_MOVE_RIGHT ) == 0 ) {

		// Controllo il numero dei parametri
		if ( values.size() >= 1 ) {

			// Aggiungo l'evento alla lista
			this->AddEvent( EventType::MOVE_RIGHT, wcstof( values[0], NULL ) );
		}

	// Movimento in basso
	} else if ( wcscasecmp( type, V_EVENT_MOVE_DOWN ) == 0 ) {

		// Controllo il numero dei parametri
		if ( values.size() >= 1 ) {

			// Aggiungo l'evento alla lista
			this->AddEvent( EventType::MOVE_DOWN, wcstof( values[0], NULL ) );
		}

	// Comparsa del messaggio dell'oggetto
	} else if ( wcscasecmp( type, V_EVENT_SHOW_OBJ_MESSAGE ) == 0 ) {

		// Controllo il numero dei parametri
		if ( values.size() >= 1 ) {

			// Aggiungo l'evento alla lista
			this->AddEvent( EventType::SHOW_OBJ_MESSAGE, values[0] );
		}
	}
}

//	<object_features direction="down" speed="1.0" face="@face0" shadow="@shadow0" message="" />

void
Object::WriteInfo( Utf8 *stream ) const {

	// Scrivo le informazioni dell'entità padre
	Sprite::WriteInfo( stream );

	// Cerco la direzione dell'oggetto
	const wchar_t *direction = NULL;

	// Controllo la direzione dell'oggetto
	switch ( this->GetDirection() ) {

		case DIRECTION_LEFT: { direction = V_LEFT; break; }

		case DIRECTION_UP: { direction = V_UP; break; }

		case DIRECTION_RIGHT: { direction = V_RIGHT; break; }

		case DIRECTION_DOWN: { direction = V_DOWN; break; }

		default: break;
	}

	// Apro il tag "object_features"
	stream->Write( L"\t<%ls %ls=\"%ls\" %ls=\"%.2f\" ",

			T_OBJ_FEATURES,
			A_DIRECTION, direction,
			A_SPEED, this->GetSpeed()
	);

	// Controllo se ha un volto
	if ( this->GetFace() != NULL ) {

		stream->Write( L"%ls=\"@%ls\" ", A_FACE, this->GetFace()->GetName().c_str() );
	}

	// Controllo se ha un ombra
	if ( this->GetShadow() != NULL ) {

		stream->Write( L"%ls=\"@%ls\" ", A_SHADOW, this->GetShadow()->GetName().c_str() );
	}

	// Controllo se ha un messaggio impostato
	if ( !this->GetMessage().empty() ) {

		stream->Write( L"%ls=\"%ls\" ", A_MESSAGE, this->GetMessage().c_str() );
	}

	stream->Write( L"/>\n\n" );
}

Types::Bool
Object::WriteEvent( Utf8 *stream, Event *event ) const {

	// Chiamo la funzione della classe genitore
	Types::Bool found = Sprite::WriteEvent( stream, event );

	// Controllo che l'evento non sia già stato salvato
	if ( !found ) {

		// Controllo il tipo dell'evento
		switch ( event->type ) {

			// Movimento a sinistra
			case EventType::MOVE_LEFT: {

				stream->Write( L"\t\t<%ls %ls=\"%ls\" %ls0=\"%.2f\" />\n",

						T_EVENT,
						A_TYPE, V_EVENT_MOVE_LEFT,
						A_VALUE, event->arg0[1]
				);

				break;
			}

			// Movimento in alto
			case EventType::MOVE_UP: {

				stream->Write( L"\t\t<%ls %ls=\"%ls\" %ls0=\"%.2f\" />\n",

						T_EVENT,
						A_TYPE, V_EVENT_MOVE_UP,
						A_VALUE, event->arg0[1]
				);

				break;
			}

			// Movimento a destra
			case EventType::MOVE_RIGHT: {

				stream->Write( L"\t\t<%ls %ls=\"%ls\" %ls0=\"%.2f\" />\n",

						T_EVENT,
						A_TYPE, V_EVENT_MOVE_RIGHT,
						A_VALUE, event->arg0[1]
				);

				break;
			}

			// Movimento in basso
			case EventType::MOVE_DOWN: {

				stream->Write( L"\t\t<%ls %ls=\"%ls\" %ls0=\"%.2f\" />\n",

						T_EVENT,
						A_TYPE, V_EVENT_MOVE_DOWN,
						A_VALUE, event->arg0[1]
				);

				break;
			}

			// Cambio della velocità
			case EventType::SET_SPEED: {

				stream->Write( L"\t\t<%ls %ls=\"%ls\" %ls0=\"%.2f\" />\n",

						T_EVENT,
						A_TYPE, V_EVENT_SET_SPEED,
						A_VALUE, event->arg0[1]
				);

				break;
			}

			// Comparsa di un messaggio dell'oggetto
			case EventType::SHOW_OBJ_MESSAGE: {

				stream->Write( L"\t\t<%ls %ls=\"%ls\" %ls0=\"%ls\" />\n",

						T_EVENT,
						A_TYPE, V_EVENT_SHOW_OBJ_MESSAGE,
						A_VALUE, event->string.c_str()
				);

				break;
			}

			default: {

				found = false;
				break;
			}
		}
	}

	return found;
}

}; // Chiudo il namespace di VGE

#endif
