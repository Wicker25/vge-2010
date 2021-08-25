/* 
    Title --- container.hpp

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


#ifndef VGE_CONTAINER_HPP
#define VGE_CONTAINER_HPP

#include <iostream>
#include <cmath>

#include <vector>

#include "vge/consts.hpp"
#include "vge/types.hpp"
#include "vge/error.hpp"
#include "vge/math.hpp"

#include "vge/entity.hpp"

#include "vge/interfaces/i-orientable.hpp"

#include "vge/widgets/box.hpp"
#include "vge/widgets/widget.hpp"
#include "vge/widgets/frame.hpp"

// Macro per il casting
#define VGE_CONTAINER( x )		( (VGE::Gui::Container *) x )

namespace VGE { // Namespace di VGE

namespace SignalType { // Namespace del tipo di segnale

// Tipo del segnale
enum {

	UPDATE_PACKING = 1100, // SEGNALE DI AGGIORNAMENTO DELL'IMPACCHETTAMENTO
};

}; // Chiudo il namespace del tipo di segnale

namespace Gui { // Namespace dell'interfaccia grafica

class Container : public Frame, public InterfaceOrientable {

	/* CONTENITORE DI WIDGETS */

public:

	// Impacchettamento del widget
	typedef enum {

		PACKING_COLLAPSE,	// Riempimento
		PACKING_EXPAND,		// Espansione
		PACKING_FILL,		// Riempimento

	} PackingType;

	// Struttura di impacchettamento di un widget 
	typedef struct {

		Widget *widget; 			// Puntatore al widget
		Types::Point2D position;	// Ancoraggio/margine del widget
		PackingType	type;			// Flag di riempimento del widget

	} Child;

	// Ridefinizione del tipo lista
	typedef std::vector< Child > ChildList;

	// Metodi costruttore e distruttore
	Container( Orientation orientation_ );
	virtual ~Container();

	// Collega l'istanza al gestore del gioco
	virtual void SetEngine( Engine *engine );

	// Collega l'istanza al gestore della scena
	virtual void SetScene( Scene *scene );

	// Imposta l'opacità del widget
	virtual void SetOpacity( Types::Uint8 value );

	// Controlla se il contenitore ha il focus
	virtual Types::Bool GetFocus() const;

	// Aggiunge un widget figlio al contenitore
	virtual void AddChild( Widget *widget );
	virtual void AddChild( Widget *widget, PackingType type );
	virtual void AddChild( Widget *widget, PackingType type, Types::Float x, Types::Float y );

	// Configura l'impacchettamento di un widget figlio nel contenitore
	virtual void SetChildPacking( Types::Uint iter, PackingType type, Widget *widget, Types::Float x, Types::Float y );
	virtual void SetChildPosition( Types::Uint iter, Types::Float x, Types::Float y );

	// Ritorna un widget impacchettato
	virtual Widget *GetChildPacking( Types::Uint iter ) const;

	// Rimuove un widget figlio dal contenitore
	virtual void RemoveChild( Widget *widget );

	// Ritorna il numero dei widget figli nel contenitore
	virtual Types::Uint GetNumberOfChilds() const;

	// Aggiorna la posizione dei widget figli
	virtual void UpdatePacking();

	// Invia un segnale al contenitore
	virtual void SendSignal( Types::Int type, Entity *other );

	// Funzione di lavoro
	virtual void Update( Viewer *viewer, Player *player );

	// Disegna il contenitore con tutti i suoi elementi
	virtual void Draw( const Types::Point2D &offset, Color::RGBA8 blend ) const;

protected:

	// Flag di aggiornamento dell'impacchettamento
	Types::Bool update;

	// Lista dei widget impacchettati
	ChildList child_list;

	// Ritorna lo spazio totale occupato dai widget orizzontalmente
	Types::Float GetHorizontalSize( Types::Uint &expanded_widgets ) const;
	// Ritorna lo spazio totale occupato dai widget verticalmente
	Types::Float GetVerticalSize( Types::Uint &expanded_widgets ) const;

	// Impacchetta i widget figli del contenitore (orizzontalmente)
	virtual void SetHorizontal() const;
	// Impacchetta i widget figli del contenitore (verticalmente)
	virtual void SetVertical() const;

	// Legge l'input da tastiera
	virtual void ReadKeyboard();
};

}; // Chiudo il namespace dell'interfaccia grafica

}; // Chiudo il namespace di VGE

#endif
