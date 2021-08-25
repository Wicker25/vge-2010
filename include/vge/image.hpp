/* 
    Title --- image.hpp

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


#ifndef VGE_IMAGE_HPP
#define VGE_IMAGE_HPP

#include <iostream>

#include "vge/consts.hpp"
#include "vge/types.hpp"
#include "vge/error.hpp"
#include "vge/math.hpp"

#include "vge/color.hpp"

#include "vge/interfaces/i-image.hpp"
#include "vge/interfaces/i-animation.hpp"

#include "vge/entity.hpp"

#include "vge/widgets/widget.hpp"

// Macro per il casting
#define VGE_IMAGE( x )		( (VGE::Image *) x )

namespace VGE { // Namespace di VGE

namespace EventType { // Namespace del tipo dell'evento

// Tipo dell'evento
enum {

	SET_ANIMATION_SPEED = 600,	// CAMBIA LA VELOCITA' DELL'ANIMAZIONE
	SET_COLOR,					// CAMBIA IL COLORE DELL'OGGETTO
	TRANSIENT_COLOR,			// CAMBIA IL COLORE DELL'OGGETTO (PROGRESSIVO)
	SET_ROTATION,				// IMPOSTA LA RUOTAZIONE DELL'OGGETTO
	TRANSIENT_ROTATION,			// IMPOSTA LA RUOTAZIONE DELL'OGGETTO (PROGRESSIVA)
};

}; // Chiudo il namespace del tipo dell'evento

class Image : public Gui::Widget, public InterfaceAnimation {

	/* IMMAGINE */

public:

	// Metodi costruttore e distruttore
	Image( const std::string &path );
	Image( const std::string &path, const Types::Size2D_u &size_ );
	Image( const Image &image, const Types::Size2D_u &size_ );
	virtual ~Image();

	// Modifica la dimensione
	virtual void SetSize( const Types::Size2D_u &size_ );
	// Ritorna dimensione
	virtual Types::Size2D_u GetSize() const;
	
	// Carica l'immagine del file
	virtual void LoadImage( const std::string &path );
	virtual void LoadImage( const std::string &path, const Types::Size2D_u &size_ );
	// Carica l'immagine da un'altra entità
	virtual void LoadImage( const Image &other );

	// Modifica la porzione dell'immagine
	virtual void SetClipSize( const Types::Size2D_u &size_ );

	// Modifica il centro dell'immagine
	virtual void SetCenter( const Types::Point2D &point );

	// Modifica la proporzione
	virtual void SetScale( const Types::Size2D_f &scale_ );

	// Modifica l'angolo di rotazione dell'immagine
	virtual void SetRotation( Types::Float value );

	// Invia un segnale all'immagine
	virtual void SendSignal( Types::Int type, Entity *other );

	// Avvia un evento dell'immagine
	virtual Types::Bool SendEvent( Event *event, Entity *other );

	// Funzione di lavoro
	virtual void Update( Viewer *viewer, Player *player );

	// Disegna l'immagine sullo schermo
	virtual void Draw( const Types::Point2D &offset, Color::RGBA8 blend ) const;


	/* Metodi di costruzione */

	// Costruttore da nodo XML
	Image( const Xml *node );

	// Estrae le informazioni sull'aspetto dell'immagine
	void ExtractAspect( const Xml *node );

	// Estrae le informazioni sulla manipolazione dell'immagine
	void ExtractAspectManipulation( const Xml *node );

	// Estrae le informazioni sull'animazione dell'immagine
	void ExtractAspectAnimation( const Xml *node );

	// Estrae l'evento dalla lista
	virtual void ExtractEvent( const Xml *node, const wchar_t *type, std::vector< wchar_t *> &values );

	// Scrive le informazioni dell'immagine in un file xml
	virtual void WriteInfo( Utf8 *stream ) const;

	// Scrive l'evento dell'immagine
	virtual Types::Bool WriteEvent( Utf8 *stream, Event *event ) const;


	/* SEGNALI */

	// Ritorna l'istanza del segnale di modifica della scala
	sigc::signal< void, Types::Size2D_f, Image * > &SignalScaling();

	// Ritorna l'istanza del segnale di rotazione
	sigc::signal< void, Types::Float, Image * > &SignalRotation();

private:

	// Flag di aggiornamento automatico dell'area di visibilità
	Types::Bool automatic_varea;


	/* SEGNALI */

	// Segnale di modifica della scala
	sigc::signal< void, Types::Size2D_f, Image * > signal_scaling;

	// Segnale di rotazione
	sigc::signal< void, Types::Float, Image * > signal_rotation;
};

}; // Chiudo il namespace di VGE

#endif
