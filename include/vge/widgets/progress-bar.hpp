/* 
    Title --- progress-bar.hpp

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


#ifndef VGE_PROGRESS_BAR_HPP
#define VGE_PROGRESS_BAR_HPP

#include <iostream>
#include <vector>
#include <list>

#include "vge/consts.hpp"
#include "vge/types.hpp"
#include "vge/math.hpp"
#include "vge/global.hpp"

#include "vge/interfaces/i-resizable.hpp"
#include "vge/interfaces/i-colorable.hpp"
#include "vge/interfaces/i-origin.hpp"
#include "vge/interfaces/i-range.hpp"

#include "vge/widgets/box.hpp"
#include "vge/widgets/font.hpp"
#include "vge/widgets/widget.hpp"
#include "vge/widgets/frame.hpp"
#include "vge/widgets/container.hpp"
#include "vge/widgets/label.hpp"

namespace VGE { // Namespace di VGE

namespace Gui { // Namespace dell'interfaccia grafica

class ProgressBar : public Container, public InterfaceRange, public InterfaceOrigin, public InterfaceColorable {

	/* RIQUADRO DI TESTO */

public:

	// Metodi costruttore e distruttore
	ProgressBar( const Types::Size2D_u &size_, Origin origin_ );
	virtual ~ProgressBar();

	// Imposta la frazione di completamento
	virtual void SetFraction( Types::Float value );

	// Imposta il colore della barra del progresso
	virtual void SetBarColor( Color::RGBA8 value );
	// Ritorna il colore della barra del progresso
	virtual Color::RGBA8 GetBarColor() const;

	// Imposta la formattazione dell'etichetta
	virtual void SetLabelFormat( const wchar_t *format );
	// Ritorna la formattazione dell'etichetta
	virtual const wchar_t *GetLabelFormat() const;

	// Ritorna l'etichetta della barra del caricamento
	Label &GetLabel();
	const Label &GetLabel() const;

	// Invia un segnale alla barra del progresso
	virtual void SendSignal( Types::Int type, Entity *other );

	// Funzione di lavoro
	virtual void Update( Viewer *viewer, Player *player );

	// Disegna la barra del caricamento sullo schermo
	virtual void Draw( const Types::Point2D &offset, Color::RGBA8 blend ) const;


	/* SEGNALI */

	// Ritorna l'istanza del segnale di modifica della frazione
	sigc::signal< void, Types::Float, Types::Float, ProgressBar * > &SignalChangeFraction();

protected:

	// Colore della barra del progresso
	Color::RGBA8 bar_color;

	// Formattazione dell'etichetta
	const wchar_t *label_format;

	// Etichetta della barra del caricamento
	Label label;

	// Flag di aggiornamento
	Types::Bool update;

	// Aggiorna l'etichetta della barra del caricamento
	void UpdateLabel();


	/* SEGNALI */

	// Segnale di modifica della frazione
	sigc::signal< void, Types::Float, Types::Float, ProgressBar * > signal_change_fraction;
};

}; // Chiudo il namespace dell'interfaccia grafica

}; // Chiudo il namespace di VGE

#endif
