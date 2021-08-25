/* 
    Title --- image-maker.cpp

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


#ifndef VGE_IMAGE_MAKER_CPP
#define VGE_IMAGE_MAKER_CPP

#include "vge/image.hpp"

#include "vge/utf8.hpp"
#include "vge/inline/utf8-inl.hpp"

#include "vge/xml.hpp"
#include "vge/inline/xml-inl.hpp"

#include "vge/interfaces/i-programmable.hpp"
#include "vge/interfaces/inline/i-programmable-inl.hpp"

#include "vge/interfaces/i-animation.hpp"
#include "vge/interfaces/inline/i-animation-inl.hpp"

#include "vge/entity.hpp"
#include "vge/inline/entity-inl.hpp"

#include "vge/maker.hpp"
#include "vge/inline/maker-inl.hpp"

#include "vge/widgets/widget.hpp"
#include "vge/widgets/inline/widget-inl.hpp"

#include "vge/inline/image-inl.hpp"

namespace VGE { // Namespace di VGE

Image::Image( const Xml *node ):

	Widget( node ),
	InterfaceAnimation( "" ) {

	// Imposto l'identificativo del tipo di entità
	this->SetMask( IMAGE_MASK );

	// Imposto il flag di aggiornamento automatico dell'area di visibilità
	this->automatic_varea = false;

	/* Costruzione dell'immagine */

	// Estraggo le informazioni sull'aspetto dell'immagine
	this->ExtractAspect( node );

	// Estraggo le informazioni sulla manipolazione dell'immagine
	this->ExtractAspectManipulation( node );

	// Estraggo le informazioni sull'animazione dell'immagine
	this->ExtractAspectAnimation( node );

	/* ======================= */

	// Imposto il flag di aggiornamento automatico dell'area di visibilità
	this->automatic_varea = true;
}

// <aspect image="charset/ragnarock_charset.png" clip="50,101" />

void
Image::ExtractAspect( const Xml *node ) {

	// Cerco il nodo "aspect"
	Xml aspect_node = node->Child( T_ASPECT );

	// Controllo l'esistenza del nodo
	if ( aspect_node.Exist() ) {

		// Puntatore all'attributo
		wchar_t *attr = NULL;

		// Cerco l'immagine dell'entità
		if ( aspect_node.GetAttribute( A_IMAGE, &attr ) ) {

			// Controllo la presenza del carattere di riferimento
			if ( attr[0] == L'@' ) {

				// Entità di riferimento
				Entity *ref = VGE::Global::GetEntity( attr + 1 );

				// Controllo l'esistenza dell'entità di riferimento
				if ( ref != NULL ) {

					if ( ref->GetMask() >= Entity::IMAGE_MASK ) {

						// Copio l'immagine da un altra entità
						this->LoadImage( *( VGE_IMAGE( ref ) ) );

						// Log di lavoro
						printf( " Image:\t\t%ls\n", attr );
					}

				} else {

					// Comunico l'errore
					fprintf( stderr, ENTITY_NOT_DEFINED_W, WARNING, aspect_node.GetRow(), attr + 1 );
				}

			} else {

				// Carico l'immagine dal percorso
				this->LoadImage( Types::WideToString( attr ) );

				// Log di lavoro
				printf( " Image:\t\t%ls\n", attr );
			}

			// Cerco il ritaglio dell'immagine
			if ( aspect_node.GetAttribute( A_CLIP, &attr ) ) {

				// Struttura di lavoro
				Types::Size2D_u tmp( this->clip );

				// Estraggo le dimensioni del ritaglio
				if ( swscanf( attr, L"%u,%u", &tmp.w, &tmp.h ) != 2 ) {

					// Comunico l'errore
					fprintf( stderr, WRONG_SYNTAX_OF_W, WARNING, aspect_node.GetRow(), A_CLIP );
				}

				// Modifico le dimensioni del ritaglio
				this->SetClipSize( tmp );
			}

		} else {

			// Comunico l'errore
			fprintf( stderr, NO_ATTRIBUTE_FOUND_W, BROKE, aspect_node.GetRow(), A_IMAGE );
		}
	}
}

// <aspect_manipulation color="FF0000FF" rotation="0" scale="1,1.5" size="50,101" blending="true" />

void
Image::ExtractAspectManipulation( const Xml *node ) {

	// Cerco il nodo "aspect_manipulation"
	Xml aspect_manip_node = node->Child( T_ASPECT_MANIP );

	// Controllo l'esistenza del nodo
	if ( aspect_manip_node.Exist() ) {

		// Puntatore all'attributo
		wchar_t *attr = NULL;

		// Cerco il colore
		if ( aspect_manip_node.GetAttribute( A_COLOR, &attr ) ) {

			// Colore
			Color::RGBA8 color;

			// Converto la stringa nel colore
			if ( Maker::StringToColor( attr, &color ) ) {

				// Imposto il colore dell'aspetto
				this->SetColor( color );

			} else {

				// Comunico l'errore
				fprintf( stderr, WRONG_SYNTAX_OF_W, BROKE, aspect_manip_node.GetRow(), A_COLOR );	
			}
		}

		// Cerco la rotazione
		if ( aspect_manip_node.GetAttribute( A_ROTATION, &attr ) ) {

			// Imposto la rotazione
			this->SetRotation( (Types::Float) wcstof( attr, NULL ) );
		}

		// Cerco la dimensione
		if ( aspect_manip_node.GetAttribute( A_SIZE, &attr ) ) {

			// Strutture di lavoro
			Types::Size2D_u size;

			// Estraggo la dimensione
			if ( swscanf( attr, L"%u,%u", &size.w, &size.h ) != 2 ) {

				// Comunico l'errore
				fprintf( stderr, WRONG_SYNTAX_OF_W, WARNING, aspect_manip_node.GetRow(), A_SIZE );
			}

			// Imposto la dimensione
			this->SetSize( size );

		// Cerco la scala
		} else if ( aspect_manip_node.GetAttribute( A_SCALE, &attr ) ) {

			// Strutture di lavoro
			Types::Size2D_f scale;

			// Estraggo la scala
			if ( swscanf( attr, L"%f,%f", &scale.w, &scale.h ) != 2 ) {

				// Comunico l'errore
				fprintf( stderr, WRONG_SYNTAX_OF_W, WARNING, aspect_manip_node.GetRow(), A_SCALE );
			}

			// Imposto la scala
			this->SetScale( scale );
		}

		// Cerco il color blending
		if ( aspect_manip_node.GetAttribute( A_BLENDING, &attr ) ) {

			// Imposto il color blending
			this->SetColorBlending( ( wcscasecmp( attr, V_TRUE ) == 0 ) );
		}
	}
}

// <aspect_animation status="stop" speed="180" range="1,9" frame="0" />

void
Image::ExtractAspectAnimation( const Xml *node ) {

	// Cerco il nodo "aspect_animation"
	Xml aspect_anim_node = node->Child( T_ASPECT_ANIM );

	// Controllo l'esistenza del nodo
	if ( aspect_anim_node.Exist() ) {

		// Puntatore all'attributo
		wchar_t *attr = NULL;

		// Cerco lo stato dell'animazione
		if ( aspect_anim_node.GetAttribute( A_STATUS, &attr ) ) {

			// Stato dell'animazione
			Animation::Status state = Animation::STOP;

			// Controllo lo stato dell'animazione
			if ( wcscasecmp( attr, V_PLAY ) == 0 )

				state = Animation::PLAY;

			else if ( wcscasecmp( attr, V_PAUSE ) == 0 )

				state = Animation::PAUSE;

			else if ( wcscasecmp( attr, V_STOP ) == 0 )

				state = Animation::STOP;

			// Imposto lo stato dell'animazione
			this->SetAnimationStatus( state );
		}

		// Cerco la velocità dell'animazione
		if ( aspect_anim_node.GetAttribute( A_SPEED, &attr ) ) {

			// Imposto la velocità dell'animazione
			this->SetAnimationSpeed( (Types::Float) wcstof( attr, NULL ) );
		}

		// Cerco la serie di immagine
		if ( aspect_anim_node.GetAttribute( A_SERIES, &attr ) ) {

			// Imposto la dimensione
			this->SetAnimationSeries( (Types::Uint) wcstoul( attr, NULL, 16 ) );
		}

		// Cerco l'intervallo delle immagine
		if ( aspect_anim_node.GetAttribute( A_RANGE, &attr ) ) {

			// Strutture di lavoro
			Types::Uint from, to;

			// Estraggo l'intervallo
			if ( swscanf( attr, L"%u,%u", &from, &to ) != 2 ) {

				// Comunico l'errore
				fprintf( stderr, WRONG_SYNTAX_OF_W, WARNING, aspect_anim_node.GetRow(), A_RANGE );
			}

			// Imposto la dimensione
			this->SetAnimationRange( from, to );
		}

		// Cerco il frame corrente
		if ( aspect_anim_node.GetAttribute( A_FRAME, &attr ) ) {

			// Imposto il frame corrente
			this->SetAnimationFrame( (Types::Uint) wcstoul( attr, NULL, 16 ) );
		}
	}
}

void
Image::ExtractEvent( const Xml *node, const wchar_t *type, std::vector< wchar_t *> &values ) {

	// Colore
	Color::RGBA8 color;

	// Chiama la funzione della classe genitore
	Widget::ExtractEvent( node, type, values );

	// Modifica della velocità dell'animazione
	if ( wcscasecmp( type, V_EVENT_SET_ANIMATION_SPEED ) == 0 ) {

		// Controllo il numero dei parametri
		if ( values.size() >= 1 ) {

			// Aggiungo l'evento alla lista
			this->AddEvent( EventType::SET_ANIMATION_SPEED, wcstof( values[0], NULL ) );
		}

	// Modifica del colore
	} else if ( wcscasecmp( type, V_EVENT_SET_COLOR ) == 0 ) {

		// Controllo il numero dei parametri
		if ( values.size() >= 1 ) {

			// Converto la stringa nel colore
			if ( Maker::StringToColor( values[0], &color ) ) {

				// Aggiungo l'evento alla lista
				this->AddEvent( EventType::SET_COLOR, color );

			} else {

				// Comunico l'errore
				fprintf( stderr, WRONG_SYNTAX_OF_W, BROKE, node->GetRow(), A_COLOR );	
			}
		}

	// Modifica del colore (progressiva)
	} else if ( wcscasecmp( type, V_EVENT_TRANSIENT_COLOR ) == 0 ) {

		// Controllo il numero dei parametri
		if ( values.size() >= 2 ) {

			// Converto la stringa nel colore
			if ( Maker::StringToColor( values[0], &color ) ) {

				// Aggiungo l'evento alla lista
				this->AddEvent(	EventType::TRANSIENT_COLOR, color,
								wcstof( values[1], NULL ) );

			} else {

				// Comunico l'errore
				fprintf( stderr, WRONG_SYNTAX_OF_W, BROKE, node->GetRow(), A_COLOR );	
			}
		}

	// Modifica della rotazione
	} else if ( wcscasecmp( type, V_EVENT_SET_ROTATION ) == 0 ) {

		// Controllo il numero dei parametri
		if ( values.size() >= 1 ) {

			// Aggiungo l'evento alla lista
			this->AddEvent( EventType::SET_ROTATION, wcstof( values[0], NULL ) );
		}

	// Modifica della rotazione (progressiva)
	} else if ( wcscasecmp( type, V_EVENT_TRANSIENT_ROTATION ) == 0 ) {

		// Controllo il numero dei parametri
		if ( values.size() >= 2 ) {

			// Aggiungo l'evento alla lista
			this->AddEvent(	EventType::TRANSIENT_ROTATION,
								wcstof( values[0], NULL ),
								wcstof( values[1], NULL ) );
		}
	}
}

//	<aspect image="charset/ragnarock_charset.png" clip="50,101" />
//	<aspect_manipulation color="FF0000FF" rotation="0" scale="1,1" size="50,101" blending="true" />
//	<aspect_animation status="stop" speed="180" range="1,9" />

void
Image::WriteInfo( Utf8 *stream ) const {

	// Scrivo le informazioni dell'entità padre
	Widget::WriteInfo( stream );

	// Scrivo il tag "aspect"
	stream->Write( L"\t<%ls %ls=\"%s\" %ls=\"%u,%u\" />\n",

			T_ASPECT,
			A_IMAGE, this->image_path.c_str(),
			A_CLIP, this->clip.w, this->clip.h
	);

	// Scrivo il tag "aspect_manipulation"
	stream->Write( L"\t<%ls %ls=\"%08X\" %ls=\"%.2f\" %ls=\"%.2f,%.2f\" %ls=\"%ls\" />\n",

			T_ASPECT_MANIP,
			A_COLOR, Color::Make( this->GetColor() ),
			A_ROTATION, this->GetRotation(),
			A_SCALE, this->scale.w, this->scale.h,
			A_BLENDING, ( this->GetColorBlending() ) ? V_TRUE : V_FALSE
	);

	// Stato dell'animazione
	const wchar_t *status = NULL;

	// Controllo lo stato dell'animazione
	switch ( this->GetAnimationStatus() ) {

		case Animation::PLAY: { status = V_PLAY; break; }

		case Animation::PAUSE: { status = V_PAUSE; break; }

		case Animation::STOP: { status = V_STOP; break; }

		default: break;
	}

	// Scrivo il tag "aspect_animation"
	stream->Write( L"\t<%ls %ls=\"%ls\" %ls=\"%.2f\" %ls=\"%u,%u\" />\n\n",

			T_ASPECT_ANIM,
			A_STATUS, status,
			A_SPEED, this->GetAnimationSpeed(),
			A_RANGE, this->animation_range[0], this->animation_range[1]
	);
}

Types::Bool
Image::WriteEvent( Utf8 *stream, Event *event ) const {

	// Chiamo la funzione della classe genitore
	Types::Bool found = Widget::WriteEvent( stream, event );

	// Controllo che l'evento non sia già stato salvato
	if ( !found ) {

		// Controllo il tipo dell'evento
		switch ( event->type ) {

			// Modifica della velocità dell'animazione
			case EventType::SET_ANIMATION_SPEED: {

				stream->Write( L"\t\t<%ls %ls=\"%ls\" %ls0=\"%.2f\" />\n",

						T_EVENT,
						A_TYPE, V_EVENT_SET_ANIMATION_SPEED,
						A_VALUE, event->arg0[1]
				);

				break;
			}

			// Modifica del colore dell'immagine
			case EventType::SET_COLOR: {

				stream->Write( L"\t\t<%ls %ls=\"%ls\" %ls0=\"%08X\" />\n",

						T_EVENT,
						A_TYPE, V_EVENT_SET_COLOR,
						A_VALUE, Color::Make( event->color[0] )
				);

				break;
			}

			// Modifica del colore dell'immagine (progressiva)
			case EventType::TRANSIENT_COLOR: {

				stream->Write( L"\t\t<%ls %ls=\"%ls\" %ls0=\"%08X\" %ls1=\"%.2f\" />\n",

						T_EVENT,
						A_TYPE, V_EVENT_TRANSIENT_COLOR,
						A_VALUE, Color::Make( event->color[0] ),
						A_VALUE, event->arg0[1]
				);

				break;
			}

			// Modifica della rotazione dell'immagine
			case EventType::SET_ROTATION: {

				stream->Write( L"\t\t<%ls %ls=\"%ls\" %ls0=\"%.2f\" />\n",

						T_EVENT,
						A_TYPE, V_EVENT_SET_ROTATION,
						A_VALUE, event->arg0[1]
				);

				break;
			}

			// Modifica della rotazione dell'immagine (progressiva)
			case EventType::TRANSIENT_ROTATION: {

				stream->Write( L"\t\t<%ls %ls=\"%ls\" %ls0=\"%.2f\" %ls1=\"%.2f\" />\n",

						T_EVENT,
						A_TYPE, V_EVENT_TRANSIENT_ROTATION,
						A_VALUE, event->arg0[1],
						A_VALUE, event->arg1[1]
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
