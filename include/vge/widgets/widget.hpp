/* 
    Title --- widget.hpp

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


#ifndef VGE_WIDGET_HPP
#define VGE_WIDGET_HPP

#include <iostream>
#include <cmath>

#include "vge/consts.hpp"
#include "vge/types.hpp"
#include "vge/error.hpp"
#include "vge/math.hpp"

#include "vge/interfaces/i-resizable.hpp"
#include "vge/interfaces/i-clickable.hpp"

#include "vge/entity.hpp"

// Macro per il casting
#define VGE_WIDGET( x )		( (VGE::Widget *) x )

namespace VGE { // Namespace di VGE

namespace SignalType { // Namespace del tipo di segnale

// Tipo del segnale
enum {

	CHANGE_FOCUS = 1200,	// SEGNALE DI CAMBIO DEL FOCUS
};

}; // Chiudo il namespace del tipo di segnale

namespace Gui { // Namespace dell'interfaccia grafica

// Prototipi
class Container;

class Widget : public Entity, public InterfaceResizable, public InterfaceClickable {

	/* WIDGET DELL'INTERFACCIA GRAFICA */

public:

	// Metodi costruttore e distruttore
	Widget( const Types::Point3D &position );
	virtual ~Widget();

	// Collega il widget ad un contenitore
	virtual void SetContainer( Container *container );
	// Ritorna il puntatore al contenitore
	virtual Container *GetContainer() const;

	// Modifica la dimensione del widget
	virtual void SetSize( const Types::Size2D_u &size_ );

	// Imposta l'opacità del widget
	virtual void SetOpacity( Types::Uint8 value );
	// Ritorna l'opacità del widget
	virtual Types::Uint8 GetOpacity() const;

	// Abilita/disabilita la capacità di prendere il focus
	virtual void SetFocusable( Types::Bool state );
	// Ritorna la capacità di prendere il focus
	virtual Types::Bool GetFocusable() const;

	// Controlla se il widget ha il focus
	virtual Types::Bool GetFocus() const;

	// Invia un segnale all'oggetto
	virtual void SendSignal( Types::Int type, Entity *other );

	// Funzione di lavoro
	virtual void Update( Viewer *viewer, Player *player );

	// Funzione di disegno
	virtual void Draw( const Types::Point2D &offset, Color::RGBA8 blend ) const;


	/* Metodi di costruzione */

	// Costruttore da nodo XML
	Widget( const Xml *node );

	// Estrae l'evento dalla lista
	virtual void ExtractEvent( const Xml *node, const wchar_t *type, std::vector< wchar_t *> &values );

	// Scrive le informazioni del widget in un file xml
	virtual void WriteInfo( Utf8 *stream ) const;


	/* SEGNALI */

	// Ritorna l'istanza del segnale di ridimensionamento
	sigc::signal< void, const Types::Size2D_u &, Widget * > &SignalResizing();

	// Ritorna l'istanza del segnale di cambio del focus
	sigc::signal< void, Types::Bool, Widget * > &SignalFocus();

protected:

	// Puntatore al container genitore
	Container *parent_container;

	// Trasparenza del widget
	Types::Uint8 opacity;

	// Flag della capacità di ottenere il focus
	Types::Bool focusable;

	/* SEGNALI */

	// Segnale di ridimensionamento
	sigc::signal< void, const Types::Size2D_u &, Widget * > signal_resizing;

	// Segnale di cambio del focus
	sigc::signal< void, Types::Bool, Widget * > signal_focus;
};

// Ridefinizione del tipo lista
typedef std::list< Widget * > WidgetList;

}; // Chiudo il namespace dell'interfaccia grafica

}; // Chiudo il namespace di VGE

#endif
