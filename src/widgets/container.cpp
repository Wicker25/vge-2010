/* 
    Title --- container.cpp

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


#ifndef VGE_CONTAINER_CPP
#define VGE_CONTAINER_CPP

#include "vge/widgets/container.hpp"

#include "vge/designer.hpp"
#include "vge/inline/designer-inl.hpp"

#include "vge/mixer.hpp"
#include "vge/inline/mixer-inl.hpp"

#include "vge/input-manager.hpp"
#include "vge/inline/input-manager-inl.hpp"

#include "vge/interfaces/i-orientable.hpp"
#include "vge/interfaces/inline/i-orientable-inl.hpp"

#include "vge/entity.hpp"
#include "vge/inline/entity-inl.hpp"

#include "vge/engine.hpp"
#include "vge/inline/engine-inl.hpp"

#include "vge/widgets/box.hpp"
#include "vge/widgets/inline/box-inl.hpp"

#include "vge/widgets/widget.hpp"
#include "vge/widgets/inline/widget-inl.hpp"

#include "vge/widgets/frame.hpp"
#include "vge/widgets/inline/frame-inl.hpp"

#include "vge/widgets/inline/container-inl.hpp"

namespace VGE { // Namespace di VGE

namespace Gui { // Namespace dell'interfaccia grafica

Container::Container( Orientation orientation_ ) : 

	Frame( Types::Point3D( 0.0f, 0.0f, 0.0f ) ),
	InterfaceOrientable( orientation_ ) {

	// Imposto l'identificativo del tipo di oggetto
	this->SetMask( CONTAINER_MASK );

	// Imposto il tipo di contenitore
	this->SetOrientation( orientation );

	// Imposto l'area di visibilità rettangolare
	this->GetVisibilityArea().SetRectangle( this->GetSize(), this->GetCenter() );

	// Abilito la capacità di prendere il focus
	this->SetFocusable( true );

	// Inizializzo le strutture
	this->update = true;
}

Container::~Container() {

}

void
Container::SetEngine( Engine *engine ) {

	// Collego l'istanza al gestore del gioco
	Frame::SetEngine( engine );

	// Iteratori
	ChildList::const_iterator iter = this->child_list.begin();
	ChildList::const_iterator end = this->child_list.end();

	// Collego i widgets figli al gestore del gioco
	for ( ; iter != end; iter++ ) {

		// Verifico la validità
		if ( (*iter).widget != NULL ) {

			// Collego il widget all'engine
			(*iter).widget->SetEngine( this->GetEngine() );
		}
	}

	// Imposto il flag di aggiornamento dell'impacchettamento
	this->update = true;
}

void
Container::SetScene( Scene *scene ) {

	// Collego l'istanza al gestore della scena
	Frame::SetScene( scene );

	// Iteratori
	ChildList::const_iterator iter = this->child_list.begin();
	ChildList::const_iterator end = this->child_list.end();

	// Collego i widgets figli al gestore della scena
	for ( ; iter != end; iter++ ) {

		// Verifico la validità
		if ( (*iter).widget != NULL ) {

			// Collego il widget alla scena
			(*iter).widget->SetScene( this->GetScene() );
		}
	}

	// Imposto il flag di aggiornamento dell'impacchettamento
	this->update = true;
}

void
Container::SetOpacity( Types::Uint8 value ) {

	// Imposto ll'opacità del contenitore
	Frame::SetOpacity( value );

	// Iteratori
	ChildList::const_iterator iter = this->child_list.begin();
	ChildList::const_iterator end = this->child_list.end();

	// Imposto l'opacità dei widget nel contenitore
	for ( ; iter != end; iter++ ) 
		if ( (*iter).widget != NULL )
			(*iter).widget->SetOpacity( value );

	// Imposto l'opacità del riquadro
	this->GetBox().SetOpacity( value );
}

Types::Bool
Container::GetFocus() const {

	// Flag di controllo
	Types::Bool child_has_focus = false;

	// Controllo se il contenitore non ha il focus direttamente
	if ( !Widget::GetFocus() ) {

		// Iteratori
		ChildList::const_iterator iter = this->child_list.begin();
		ChildList::const_iterator end = this->child_list.end();

		// Controllo se uno dei widget figli ha il focus
		for ( ; iter != end && !child_has_focus; iter++ ) {

			child_has_focus = ( (*iter).widget != NULL && (*iter).widget->GetFocus() );
		}
	}

	return ( Widget::GetFocus() || child_has_focus );
}

void
Container::SetChildPacking(	Types::Uint iter, PackingType type, Widget *widget,
							Types::Float x, Types::Float y ) {

	// Controllo la validità dell'iteratore
	if ( iter < this->GetNumberOfChilds() ) {

		// Ricavo la struttura del widget impacchettato
		Child *child = &this->child_list[iter];

		// Reinizializzo la struttura
		child->widget	= widget;
		child->type		= type;
		child->position.x	= x;
		child->position.y	= y;

		// Controllo la validità del widget
		if ( widget != NULL ) {

			// Collego il widget al contenitore
			widget->SetContainer( this );

			// Collego il widget all'engine
			widget->SetEngine( this->GetEngine() );

			// Collego il widget alla scena
			widget->SetScene( this->GetScene() );

			// Reimposto il cento del widget
			widget->SetCenter( Types::Point2D( 0.0f, 0.0f ) );

			// Reimposto la posizione del widget
			widget->SetFixed( true );

			// Imposto l'opacità del widget
			widget->SetOpacity( this->GetOpacity() );
		}

		// Imposto il flag di aggiornamento dell'impacchettamento
		this->update = true;
	}
}

void
Container::RemoveChild( Widget *widget ) {

	// Iteratori
	ChildList::iterator iter = this->child_list.begin();
	ChildList::const_iterator end = this->child_list.end();

	// Rimuovo il widget figlio dal contenitore
	for ( ; iter != end; iter++ ) {

		if ( (*iter).widget == widget ) {

			// Rimuovo il widget figlio dalla lista
			this->child_list.erase( iter );

			// Rimuovo i collegamenti con la mappa, l'engine ed il contenitore padre
			widget->SetEngine( NULL );
			widget->SetScene( NULL );
			widget->SetContainer( NULL );

			// Imposto il flag di aggiornamento dell'impacchettamento
			this->update = true;
		}
	}
}

void
Container::ReadKeyboard() {

	// Ricavo il gestore degli eventi in ingresso
	InputManager &input_manager = this->GetEngine()->GetInputManager();

	// Ricavo la lista dei caratteri premuti
	const InputManager::KeyList keys = input_manager.GetKeyList();

	// Iteratori
	InputManager::KeyList::const_iterator iter = keys.begin();
	InputManager::KeyList::const_iterator end = keys.end();

	// Applico i nuovi caratteri alla stringa
	for ( ; iter != end; iter++ ) {

		// Gestisco la freccia sinistra
		if ( iter->sym == SDLK_LEFT ) {

		// Gestisco la freccia destra
		} else if ( iter->sym == SDLK_RIGHT ) {

		}
	}
}

Types::Float
Container::GetHorizontalSize( Types::Uint &expanded_widgets ) const {

	// Azzero il numero di elementi espansi
	expanded_widgets = 0;

	// Spazi tra i widget
	Types::Float spacing = 0.0;

	// Iteratore
	Types::Uint j = 0;

	// Calcolo lo spazio dei widget figli "espansi"
	for ( ; j < this->GetNumberOfChilds(); j++ ) {

		// Ricavo il widget figlio
		Widget *widget = this->child_list[j].widget;

		// Controllo la validità del widget figlio
		if ( widget != NULL && widget->GetVisible() ) {

			if ( this->child_list[j].type != Container::PACKING_COLLAPSE ) {

				// Incremento il numero di widget "espansi"			
				expanded_widgets++;

				if ( this->child_list[j].type == Container::PACKING_FILL )

					// Conto gli spazi tra i widget
					spacing += this->child_list[j].position.x * 2.0;

			} else {

				// Conto gli spazi tra i widget
				spacing += (Types::Float) widget->GetSize().h + this->child_list[j].position.x * 2.0;
			}
		}
	}

	return spacing;
}

void
Container::SetHorizontal() const {

	// Numero di widget espansi
	Types::Uint expanded_widgets;

	// Spazi tra i widget
	Types::Float spacing = this->GetHorizontalSize( expanded_widgets );

	// Divido lo spazio secondo il numero dei widget espansi
	Types::Float size = ( (Types::Float) this->GetSize().w - (Types::Float) spacing ) / (Types::Float) expanded_widgets;



	// Numero di widget figli
	const Types::Uint n_widgets = this->GetNumberOfChilds();

	// Posizione del prossimo elemento
	Types::Float next = 0.0f;

	// Iteratore
	Types::Uint i = 0;

	// Impacchetto i widget figli del contenitore
	for ( ; i < n_widgets; i++ ) {

		// Ricavo il widget
		Widget *widget = this->child_list[i].widget;

		// Controllo la validità del widget figlio
		if ( widget != NULL && widget->GetVisible() ) {

			// Controllo il tipo di impacchettamento
			switch ( this->child_list[i].type ) {

				// Collasso
				case Container::PACKING_COLLAPSE: {

					// Calcolo l'ancoraggio del widget figlio
					Types::Float offy = ( this->GetSize().h > (Types::Float) widget->GetSize().h ) ? \
						( this->GetSize().h - (Types::Float) widget->GetSize().h ) * this->child_list[i].position.y : 0.0f;

					// Calcolo il margine orizzontale del widget figlio
					next += this->child_list[i].position.x;

					// Sposta l'elemento
					widget->SetPosition( Types::Point2D(	this->GetPosition().x + next,
															this->GetPosition().y + offy ) );

					// Calcolo la posizione del prossimo elemento
					next += (Types::Float) widget->GetSize().w + this->child_list[i].position.x;
					break;
				}

				// Riempimento
				case Container::PACKING_FILL: {

					// Calcolo il margine orizzontale del widget figlio
					next += this->child_list[i].position.x;

					// Modifico la dimensione dell'elemento
					widget->SetSize( Types::Size2D_u( (Types::Uint) size, this->GetSize().h ) );

					// Sposta l'elemento
					widget->SetPosition( Types::Point2D(	this->GetPosition().x + next,
															this->GetPosition().y ) );

					// Calcolo la posizione del prossimo elemento
					next += size + this->child_list[i].position.y;

					break;
				}

				// Espansione
				case Container::PACKING_EXPAND: {

					// Calcolo l'ancoraggio del widget figlio
					Types::Float offx = ( size > (Types::Float) widget->GetSize().w ) ? \
						( size - (Types::Float) widget->GetSize().w )  * this->child_list[i].position.x : 0.0f;

					Types::Float offy = ( this->GetSize().h > (Types::Float) widget->GetSize().h ) ? \
						( this->GetSize().h - (Types::Float) widget->GetSize().h ) * this->child_list[i].position.y : 0.0f;

					// Sposta l'elemento
					widget->SetPosition( Types::Point2D(	this->GetPosition().x + offx + next,
															this->GetPosition().y + offy ) );

					// Calcolo la posizione del prossimo elemento
					next += size;
					break;
				}
			}

			// Controllo se il widget figlio è un altro contenitore
			if (	widget->GetMask() == CONTAINER_MASK ||
					widget->GetMask() == CONTAINER_DERIVED_MASK	) {

				// Invio il segnale di impacchettamento
				VGE_CONTAINER( widget )->UpdatePacking();
			}
		}
	}
}

Types::Float
Container::GetVerticalSize( Types::Uint &expanded_widgets ) const {

	// Azzero il numero di elementi espansi
	expanded_widgets = 0;

	// Spazi tra i widget
	Types::Float spacing = 0.0f;

	// Iteratore
	Types::Uint j = 0;

	// Calcolo lo spazio dei widget figli "espansi"
	for ( ; j < this->GetNumberOfChilds(); j++ ) {

		// Ricavo il widget figlio
		Widget *widget = this->child_list[j].widget;

		// Controllo la validità del widget figlio
		if ( widget != NULL && widget->GetVisible() ) {

			if ( this->child_list[j].type != Container::PACKING_COLLAPSE ) {

				// Incremento il numero dei widget "espansi"			
				expanded_widgets++;

				if ( this->child_list[j].type == Container::PACKING_FILL )

					// Conto gli spazi tra i widget
					spacing += this->child_list[j].position.y * 2.0f;

			} else {

				spacing += (Types::Float) widget->GetSize().h + this->child_list[j].position.y * 2.0f;
			}
		}
	}

	return spacing;
}

void
Container::SetVertical() const {

	// Numero di widget espansi
	Types::Uint expanded_widgets;

	// Spazi tra i widget
	Types::Float spacing = this->GetVerticalSize( expanded_widgets );

	// Divido lo spazio secondo il numero dei widget espansi
	Types::Float size = ( (Types::Float) this->GetSize().h - (Types::Float) spacing ) / (Types::Float) expanded_widgets;


	// Numero di widget figli
	const Types::Uint n_widgets = this->GetNumberOfChilds();

	// Posizione del prossimo elemento
	Types::Float next = 0.0f;

	// Iteratore
	Types::Uint i = 0;

	// Impacchetto i widget figli del contenitore
	for ( ; i < n_widgets; i++ ) {

		// Ricavo il widget figlio
		Widget *widget = this->child_list[i].widget;

		// Controllo la validità del widget figlio
		if ( widget != NULL && widget->GetVisible() ) {

			// Controllo il tipo di impacchettamento
			switch ( this->child_list[i].type ) {

				// Collasso
				case Container::PACKING_COLLAPSE: {

					// Calcolo l'ancoraggio del widget figlio
					Types::Float offx = ( this->GetSize().w > (Types::Float) widget->GetSize().w ) ? \
						( this->GetSize().w - (Types::Float) widget->GetSize().w ) * this->child_list[i].position.x : 0.0f;

					// Calcolo il margine verticale del widget figlio
					next += this->child_list[i].position.y;

					// Sposta l'elemento
					widget->SetPosition( Types::Point2D(	this->GetPosition().x + offx,
															this->GetPosition().y + next ) );

					// Calcolo la posizione del prossimo elemento
					next += (Types::Float) widget->GetSize().h + this->child_list[i].position.y;
					break;
				}

				// Riempimento
				case Container::PACKING_FILL: {

					// Calcolo il margine verticale del widget figlio
					next += this->child_list[i].position.y;

					// Modifico la dimensione dell'elemento
					widget->SetSize( Types::Size2D_u( this->GetSize().w, (Types::Uint) size ) );

					// Sposta l'elemento
					widget->SetPosition( Types::Point2D(	this->GetPosition().x,
															this->GetPosition().y + next ) );

					// Calcolo la posizione del prossimo elemento
					next += size + this->child_list[i].position.y;

					break;
				}

				// Espansione
				case Container::PACKING_EXPAND: {

					// Calcolo l'ancoraggio del widget figlio
					Types::Float offx = ( this->GetSize().w > (Types::Float) widget->GetSize().w ) ? \
						( this->GetSize().w - (Types::Float) widget->GetSize().w ) * this->child_list[i].position.x : 0.0f;

					Types::Float offy = ( size > (Types::Float) widget->GetSize().h ) ? \
						( size - (Types::Float) widget->GetSize().h )  * this->child_list[i].position.y : 0.0f;

					// Sposta l'elemento
					widget->SetPosition( Types::Point2D(	this->GetPosition().x + offx,
															this->GetPosition().y + offy + next ) );

					// Calcolo la posizione del prossimo elemento
					next += size;
					break;
				}
			}

			// Controllo se il widget figlio è un altro contenitore
			if (	widget->GetMask() == CONTAINER_MASK ||
					widget->GetMask() == CONTAINER_DERIVED_MASK	) {

				// Invio il segnale di impacchettamento
				VGE_CONTAINER( widget )->UpdatePacking();
			}
		}
	}
}

void
Container::UpdatePacking() {

	/* Impacchettamento dei widget */

	// Controllo l'orientamento
	switch ( this->GetOrientation() ) {

		// Orientamento orizzontale
		case ORIENTATION_HORIZONTAL: {

			this->SetHorizontal();
			break;
		}

		// Orientamento verticale
		case ORIENTATION_VERTICAL: {

			this->SetVertical();
			break;
		}
	}
}

void
Container::SendSignal( Types::Int type, Entity *other ) {

	// Chiamo il gestore dei segnali
	Frame::SendSignal( type, other );

	// Controlla il tipo di segnale
	switch ( type ) {

		// Gestisco il segnale di ridimensionamento
		case SignalType::RESIZING:

		// Gestisco il segnale di aggiornamento dell'impacchettamento
		case SignalType::UPDATE_PACKING: {

			// Imposto il flag di aggiornamento dell'impacchettamento
			this->update = true;
			break;
		}

		default: break;
	}
}

void
Container::Update( Viewer *viewer, Player *player ) {

	// Avvio la funzione di lavoro superiore
	Frame::Update( viewer, player );

	// Controllo se il widget ha il focus
	if ( this->GetFocus() ) {

		// Legge l'input da tastiera
		this->ReadKeyboard();

		// Legge l'input del joystick
		//this->ReadJoystick();
	}

	// Numero di widget figli
	const Types::Uint n_widgets = this->GetNumberOfChilds();

	// Iteratore
	Types::Uint i = 0;

	// Aggiorno gli elementi del contenitore
	for ( ; i < n_widgets; i++ ) {

		// Ricavo il puntatore al  widget figlio
		Widget *widget = this->child_list[i].widget;

		if ( widget != NULL && widget->GetSensible() ) {

			 widget->Update( viewer, player );
		}
	}

	// Controllo se è abilitato il flag di aggiornamento
	if ( this->update ) {

		// Aggiorno la posizione dei widget figli
		this->UpdatePacking();

		// Disabilito il flag di aggiornamento
		this->update = false;
	}
}

void
Container::Draw( const Types::Point2D &offset, Color::RGBA8 blend ) const {

	// Funzione di disegno del frame
	Frame::Draw( offset, blend );

	// Numero di widget figli
	const Types::Uint n_widgets = this->GetNumberOfChilds();

	// Iteratore
	Types::Uint i = 0;

	// Disegno gli elementi del contenitore
	for ( ; i < n_widgets; i++ ) {

		if ( this->child_list[i].widget != NULL && this->child_list[i].widget ) {

			this->child_list[i].widget->Draw( offset, blend );
		}
	}
}

}; // Chiudo il namespace dell'interfaccia grafica

}; // Chiudo il namespace di VGE

#endif
