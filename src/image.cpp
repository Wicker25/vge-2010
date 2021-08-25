/* 
    Title --- image.cpp

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


#ifndef VGE_IMAGE_CPP
#define VGE_IMAGE_CPP

#include "vge/image.hpp"

#include "vge/color.hpp"
#include "vge/inline/color-inl.hpp"

#include "vge/interfaces/i-ruotable.hpp"
#include "vge/interfaces/inline/i-ruotable-inl.hpp"

#include "vge/interfaces/i-scalable.hpp"
#include "vge/interfaces/inline/i-scalable-inl.hpp"

#include "vge/interfaces/i-colorable.hpp"
#include "vge/interfaces/inline/i-colorable-inl.hpp"

#include "vge/interfaces/i-programmable.hpp"
#include "vge/interfaces/inline/i-programmable-inl.hpp"

#include "vge/interfaces/i-image.hpp"
#include "vge/interfaces/inline/i-image-inl.hpp"

#include "vge/interfaces/i-animation.hpp"
#include "vge/interfaces/inline/i-animation-inl.hpp"

#include "vge/entity.hpp"
#include "vge/inline/entity-inl.hpp"

#include "vge/engine.hpp"
#include "vge/inline/engine-inl.hpp"

#include "vge/widgets/widget.hpp"
#include "vge/widgets/inline/widget-inl.hpp"

#include "vge/inline/image-inl.hpp"

namespace VGE { // Namespace di VGE

Image::Image( const std::string &path ) :

	Widget( Types::Point3D( 0.0f, 0.0f, 0.0f ) ),
	InterfaceAnimation( path ) {

	// Imposto l'identificativo del tipo di entità
	this->SetMask( IMAGE_MASK );

	// Imposto il flag di aggiornamento automatico dell'area di visibilità
	this->automatic_varea = true;

	// Imposto l'area di visibilità rettangolare
	this->GetVisibilityArea().SetRectangle( this->clip, this->center );
}

Image::Image( const std::string &path, const Types::Size2D_u &size_ ) :

	Widget( Types::Point3D( 0.0f, 0.0f, 0.0f ) ),
	InterfaceAnimation( path, size_ ) {

	// Imposto l'identificativo del tipo di entità
	this->SetMask( IMAGE_MASK );

	// Imposto il flag di aggiornamento automatico dell'area di visibilità
	this->automatic_varea = true;

	// Imposto l'area di visibilità rettangolare
	this->GetVisibilityArea().SetRectangle( this->clip, this->center );
}

Image::~Image() {

}

void
Image::LoadImage( const Image &other ) {

	// Copia le strutture dall'altra entità
	this->image_path	= other.image_path;
	this->texture		= other.texture;
	this->clip			= other.clip;
	this->image_s		= other.image_s;
	this->or_image_s	= other.or_image_s;
	this->offset		= other.offset;
}

void
Image::SendSignal( Types::Int type, Entity *other ) {

	// Chiamo il gestore dei segnali
	Widget::SendSignal( type, other );

	// Controlla il tipo di segnale
	switch ( type ) {

		// Gestisco il segnale di modifica della scala
		case SignalType::SCALING: { 

			// Emetto il segnale di modifica della scala
			this->SignalScaling().emit( this->scale, this );

			// Aggiorno la dimensione dell'area di visibilità
			this->GetVisibilityArea().SetScale( this->scale );
			break;
		}

		// Gestisco il segnale di rotazione
		case SignalType::ROTATION: { 

			// Emetto il segnale di rotazione
			this->SignalRotation().emit( this->GetRotation(), this );

			// Aggiorno la rotazione dell'area di visibilità
			this->GetVisibilityArea().SetRotation( this->GetRotation() );
			break;
		}

		default: break;
	}
}

Types::Bool
Image::SendEvent( Event *event, Entity *other ) {

	// Flag di controllo
	Types::Bool end_event = false;

	// Controlla il tipo di evento
	switch ( event->type ) {

		// Cambio la velocità dell'animazione
		case EventType::SET_ANIMATION_SPEED: { 

			this->SetAnimationSpeed( event->arg0[0] );
			end_event = true;
			break;
		}

		// Cambio il colore dell'immagine
		case EventType::SET_COLOR: {

			this->SetColor( event->color[0] );
			end_event = true;
			break;
		}

		// Cambio il colore dell'immagine (progressivo)
		case EventType::TRANSIENT_COLOR: {

			// Memorizza il colore iniziale
			if ( event->color[2] == 0 ) {

				event->color[2] = this->GetColor();
				event->arg1[0] = 0.0f;
			}

			// Incremento la transizione
			event->arg1[0] += ( event->arg0[0] / 1000.0f );

			// Ricavo il colore finale
			Color::RGBA8 new_color = event->color[0];
			Color::RGBA8 old_color = event->color[2];

			// Controllo se ho terminato la transizione
			if ( event->arg1[0] <= 1.0f ) {

				// Cambio progressivamente la colorazione
				this->SetColor(	Color::BlendAlpha( new_color, old_color, event->arg1[0] ) );

			} else {

				// Imposto la colorazione finale
				this->SetColor(	Color::BlendAlpha( new_color, old_color, 1.0f ) );

				// Comunico la fine dell'evento
				end_event = true;
			}

			break;
		}

		// Imposto la rotazione dell'immagine
		case EventType::SET_ROTATION: { 

			// Correggo l'angolo di destinazione
			if ( event->arg0[0] > 360.0f )
				event->arg0[0] = fmod( (float) event->arg0[0], 360.0f );

			this->SetRotation( event->arg0[0] );
			end_event = true;
			break;
		}

		// Imposto la rotazione dell'immagine (progressiva)
		case EventType::TRANSIENT_ROTATION: { 

			// Correggo l'angolo di destinazione
			if ( event->arg0[0] > 360.0f )
				event->arg0[0] = fmod( (float) event->arg0[0], 360.0f );

			// Ricavo l'angolo attuale
			Types::Float angle = this->GetRotation();

			// Calcolo il nuovo angolo
			if ( VABS_DIFF( angle, event->arg0[0] ) > VABS( event->arg1[0] ) )

				angle += event->arg1[0];
			else
				angle = event->arg0[0];

			// Imposto la nuova angolazione
			this->SetRotation( angle );

			if ( event->arg0[0] == angle ) end_event = true;
			break;
		}

		default: break;
	}

	// Avvia il gestore degli eventi
	if ( !end_event )
		end_event = Widget::SendEvent( event, other );

	return end_event;
}

void
Image::Update( Viewer *viewer, Player *player ) {

	// Avvio la funzione di lavoro superiore
	Widget::Update( viewer, player );

	// Ricavo i FPS dal disegnatore
	Types::Uint fps_limit = this->GetEngine()->GetDesigner().GetFpsLimit();

	// Aggiorno l'animazione
	this->UpdateAnimation( fps_limit );
}

void
Image::Draw( const Types::Point2D &offset, Color::RGBA8 blend ) const {

	// Disegno l'immagine
	this->DrawImage(	this->GetEngine()->GetDesigner(),
						this->GetPosition() + offset, this->center, blend, this->GetOpacity() );

	// Funzione di disegno dell'entità
	Widget::Draw( offset, blend );
}

}; // Chiudo il namespace di VGE

#endif
