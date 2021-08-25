/* 
    Title --- text-box.hpp

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


#ifndef VGE_TEXT_BOX_HPP
#define VGE_TEXT_BOX_HPP

#include <iostream>
#include <vector>
#include <list>

#include "vge/consts.hpp"
#include "vge/types.hpp"
#include "vge/math.hpp"
#include "vge/global.hpp"

#include "vge/interfaces/i-resizable.hpp"
#include "vge/interfaces/i-margins.hpp"

#include "vge/entity.hpp"

#include "vge/widgets/box.hpp"
#include "vge/widgets/font.hpp"
#include "vge/widgets/widget.hpp"
#include "vge/widgets/frame.hpp"

#define COLOR_RE	L"{%02X%02X%02X}"
#define COLOR_LEN	8

namespace VGE { // Namespace di VGE

namespace SignalType { // Namespace del tipo di segnale

// Tipo del segnale
enum {

	CHANGE_PAGE = 1150, // SEGNALE DI CAMBIO DELLA PAGINA
};

}; // Chiudo il namespace del tipo di segnale

namespace Gui { // Namespace dell'interfaccia grafica

class TextBox : public Frame, public InterfaceMargins {

	/* RIQUADRO DI TESTO */

public:

	// Allineamento del testo
	typedef enum {

		ALIGN_LEFT,		// A sinistra
		ALIGN_CENTER,	// Centrato
		ALIGN_RIGHT,	// A destra

	} Align;

	// Metodi costruttore e distruttore
	TextBox( const std::wstring &string );
	TextBox( const std::wstring &string, const Types::Size2D_u &size_ );
	virtual ~TextBox();

	// Modifica la dimensione del riquadro
	virtual void SetSize( const Types::Size2D_u &size_ );
	// Adatta la dimensione del riquadro alle dimensioni del testo
	virtual void AdjustSize();

	// Imposta il font
	virtual void SetFont( Font *font );
	// Ritorna il puntatore al font
	virtual Font *GetFont() const;

	// Imposta il testo
	virtual void SetString( const std::wstring &string );
	// Ritorna la stringa del testo
	virtual const std::wstring GetString() const;
	// Ritorna la stringa del testo senza la formattazione
	virtual const std::wstring GetOnlyString() const;

	// Imposta lo spazio tra le righe
	virtual void SetRowSpacing( Types::Float value );
	// Ritorna lo spazio tra le righe
	virtual Types::Float GetRowSpacing() const;

	// Imposta l'allineamento del testo
	virtual void SetAlign( const Align &align );
	// Ritorna l'allineamento del testo
	virtual const Align &GetAlign() const;

	// Aggiunge una nuova riga all'inizio del testo
	virtual void PrependRow( const std::wstring &string );
	// Aggiunge una nuova riga alla fine del testo
	virtual void AppendRow( const std::wstring &string );

	// Ritorna il numero dei caratteri del testo
	virtual Types::Uint Lenght() const;
	// Ritorna il numero delle righe del testo
	virtual Types::Uint GetRows() const;

	// Imposta la pagina corrente
	virtual void SetPage( Types::Uint page );
	// Ritorna la pagina corrente
	virtual Types::Uint GetPage() const;

	// Passa alla pagina successiva
	virtual bool NextPage();
	// Torna alla pagina precedente
	virtual bool PreviousPage();

	// Passa alla prima pagina
	virtual void GoToFirstPage();
	// Passa all'ultima pagina
	virtual void GoToLastPage();

	// Controlla se la pagina corrente è la prima
	virtual bool IsFirstPage() const;
	// Controlla se la pagina corrente è l'ultima
	virtual bool IsLastPage() const;

	// Ritorna il numero delle pagine
	virtual Types::Uint GetNumberOfPages() const;

	// Invia un segnale all'oggetto
	virtual void SendSignal( Types::Int type, Entity *other );

	// Avvia un evento dell'oggetto
	virtual Types::Bool SendEvent( Event *event, Entity *other );

	// Funzione di lavoro
	virtual void Update( Viewer *viewer, Player *player );

	// Disegna il testo sullo schermo
	virtual void Draw( const Types::Point2D &offset, Color::RGBA8 blend ) const;


	/* SEGNALI */

	// Ritorna l'istanza del segnale di cambio della pagina
	sigc::signal< void, TextBox *, Types::Uint > &SignalChangePage();

protected:

	// Calcola il numero delle righe visualizzabili
	virtual void SetMaxRows();

	// Prepara la stringa per la scrittura
	virtual void MakeString();

	// Puntatore al font
	Font *t_font;

	// Stringa originale
	std::wstring t_string;

	// Stringa orinale con la formattazione
	std::wstring t_or_string;

	// Struttura dell'indice dei colori
	struct ColorIndex {

		// Posizione
		Types::Uint index;

		// Colore
		Color::RGBA8 color;
	};

	// Indici dei colori
	std::vector< ColorIndex > color_indices;

	// Indici delle righe
	std::vector< Types::Uint > row_indices;

	// Dimensione delle righe
	std::vector< Types::Uint > row_width;

	// Spazio fra le righe
	Types::Float row_spacing;

	// Numero massimo di righe
	Types::Uint max_rows;

	// Allineamento del testo
	Align text_align;

	// Pagina corrent
	Types::Uint c_page;

	// Flag di aggiornamento del testo
	Types::Bool update;


	/* SEGNALI */

	// Segnale di cambio della pagina
	sigc::signal< void, TextBox *, Types::Uint > signal_change_page;
};

// Ridefinizione dei tipo lista
typedef std::list< TextBox * > TextBoxList;

}; // Chiudo il namespace dell'interfaccia grafica

}; // Chiudo il namespace di VGE

#endif
