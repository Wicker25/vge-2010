/* 
    Title --- text-box.cpp

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


#ifndef VGE_TEXT_BOX_CPP
#define VGE_TEXT_BOX_CPP

#include "vge/widgets/text-box.hpp"

#include "vge/interfaces/i-resizable.hpp"
#include "vge/interfaces/inline/i-resizable-inl.hpp"

#include "vge/interfaces/i-colorable.hpp"
#include "vge/interfaces/inline/i-colorable-inl.hpp"

#include "vge/entity.hpp"
#include "vge/inline/entity-inl.hpp"

#include "vge/engine.hpp"
#include "vge/inline/engine-inl.hpp"

#include "vge/interfaces/i-margins.hpp"
#include "vge/interfaces/inline/i-margins-inl.hpp"

#include "vge/widgets/box.hpp"
#include "vge/widgets/inline/box-inl.hpp"

#include "vge/widgets/font.hpp"
#include "vge/widgets/inline/font-inl.hpp"

#include "vge/widgets/widget.hpp"
#include "vge/widgets/inline/widget-inl.hpp"

#include "vge/widgets/frame.hpp"
#include "vge/widgets/inline/frame-inl.hpp"

#include "vge/widgets/inline/text-box-inl.hpp"

namespace VGE { // Namespace di VGE

namespace Gui { // Namespace dell'interfaccia grafica

TextBox::TextBox( const std::wstring &string ) :

	Frame( Types::Point3D( 0.0f, 0.0f, 0.0f ) ) {

	// Imposto il font
	this->SetFont( NULL );

	// Imposto la stringa
	this->SetString( string );

	// Imposto i margini del testo
	this->SetMargins( Types::Size2D_u( 10, 0 ) );

	// Imposto lo spazio tra le righe
	this->SetRowSpacing( 17.0f );

	// Imposto l'allineamento del testo
	this->SetAlign( ALIGN_CENTER );

	// Imposto la dimensione del riquadro
	this->AdjustSize();

	// Imposto l'opacità del testo
	this->SetOpacity( 255 );

	// Imposto il flag di aggiornamento
	this->update = true;
}

TextBox::TextBox( const std::wstring &string, const Types::Size2D_u &size_ ) :

	Frame( Types::Point3D( 0.0f, 0.0f, 0.0f ) ) {

	// Imposto la dimensione del riquadro
	this->SetSize( size_ );

	// Imposto il font
	this->SetFont( NULL );

	// Imposto la stringa
	this->SetString( string );

	// Imposto i margini del testo
	this->SetMargins( Types::Size2D_u( 10, 0 ) );

	// Imposto lo spazio tra le righe
	this->SetRowSpacing( 17.0f );

	// Imposto l'allineamento del testo
	this->SetAlign( ALIGN_CENTER );

	// Imposto l'opacità del testo
	this->SetOpacity( 255 );

	// Imposto il flag di aggiornamento
	this->update = true;
}

TextBox::~TextBox() {

}

void
TextBox::SetSize( const Types::Size2D_u &size_ ) {

	// Modifico la dimensione del riquadro
	Frame::SetSize( size_ );

	// Calcolo il numero delle righe visualizzabili
	this->SetMaxRows();

	// Imposto il flag di aggiornamento
	this->update = true;
}

void
TextBox::AdjustSize() {

	// Nuova dimensione
	Types::Size2D_u new_size( 0, 0 );

	// Controllo che sia stato assegnato un font
	if ( this->GetFont() != NULL ) {

		// Lunghezza della stringa
		Types::Uint len = this->GetString().length();

		// Ultimo ritorno a capo
		Types::Uint last = 0;

		// Contatore delle righe
		Types::Uint rows = 1;

		// Iteratore
		Types::Uint i = 0;

		// Calcolo l'andata a capo del testo
		for ( ; i < len; i++ ) {

			// Cerco i caratteri di ritorno a capo
			if ( this->GetString()[i] == L'\n' || i + 1 == len ) {

				// Memorizzo la dimensione della riga più lunga
				new_size.w = VMAX( this->GetFont()->GetStringWidth( this->GetString().substr( last, i - last ) ), new_size.w );

				// Memorizzo l'ultima andata a capo
				last = i;

				// Incremento il contatore delle righe
				rows++;
			}
		}

		// Calcolo lo spazio verticale del riquadro
		new_size.h = (Types::Uint) ( rows * this->GetRowSpacing() );
	}

	// Modifico la dimensione del riquadro
	this->SetSize( new_size );

	// Imposto il flag di aggiornamento
	this->update = true;
}

inline void
TextBox::SetString( const std::wstring &string ) {

	// Pulisco gli indici dei colori
	this->color_indices.clear();

	// Memorizzo la stringa
	this->t_or_string = string;

	// Stringa non formattata
	std::wstring only_str;

	// Colore estratto
	Types::Uint8 color[3];

	// Caratteri di formattazione
	Types::Uint blank = 0;

	// Lunghezza della stringa
	Types::Uint len = string.length();

	// Iteratore
	Types::Uint i = 0;

	// Calcolo l'andata a capo del testo
	for ( ; i < len; i++ ) {

		// Cerco le stringhe di formattazione
		if ( swscanf( &string[i], COLOR_RE, &color[0], &color[1], &color[2] ) > 0 ) {

			// Creo un nuovo indice del colore
			ColorIndex tmp = { i - blank, Color::Make( color[0], color[1], color[2] ) };

			// Aggiungo il nuovo indice alla lista
			this->color_indices.push_back( tmp );

			// Incremento il numero dei caratteri da ignorare
			blank += COLOR_LEN;

			// Sposto l'iteratore oltre la stringa di formattazione
			i += COLOR_LEN;
		}

		// Copia il carattere senza formattazione
		only_str.push_back( string[i] );
	}

	// Memorizzo il testo non formattato
	this->t_string = only_str;

	// Imposto il flag di aggiornamento
	this->update = true;
}

void
TextBox::MakeString() {

	// Controllo che il testo sia stato configurato correttamente
	if ( this->GetSize().w && this->GetFont() != NULL && this->GetFont()->GetClipSize().w ) {

		// Pulisco gli indici delle righe
		this->row_indices.clear();
		this->row_indices.push_back(0);

		// Pulisco le dimensioni delle righe
		this->row_width.clear();

		// Ricavo la larghezza effettiva del testo
		Types::Uint text_width = (Types::Float) ( this->GetSize().w - this->margins.x * 2 );

		// Lunghezza della stringa
		Types::Uint len = this->GetString().length();

		// Ultimo ritorno a capo
		Types::Uint last = 0;

		// Ultima parola trovata
		Types::Uint lst_word = 0;

		// Iteratore
		Types::Uint i = 0;

		// Calcolo l'andata a capo del testo
		for ( ; i < len; i++ ) {

			// Cerco un carattere di spaziatura
			if ( this->GetFont()->GetStringWidth( this->GetString().substr( last, i - last ) ) > text_width ) {

				// Memorizzo la fine della riga
				this->row_indices.push_back( lst_word );

				// Memorizzo la larghezza della riga
				this->row_width.push_back( this->GetFont()->GetStringWidth( this->GetString().substr( last, lst_word - last ) ) );

				// Memorizzo l'ultimo riscontro e ripristino l'iteratore
				i = last = lst_word;

			// Cerco i caratteri di spaziatura
			} else if ( this->GetString()[i] == L' ' ) {

				// Memorizzo l'ultima parola
				lst_word = i + 1;

			// Cerco i caratteri di spaziatura
			} else if ( this->GetString()[i] == L'\n' ) {

				// Memorizzo la fine della riga
				this->row_indices.push_back( i + 1 );

				// Memorizzo la larghezza della riga
				this->row_width.push_back( this->GetFont()->GetStringWidth( this->GetString().substr( last, i - last ) ) );

				// Memorizzo l'ultimo riscontro
				lst_word = last = i + 1;
			}
		}

		// Aggiungo l'ultimo marcatore di riga
		this->row_indices.push_back( i );

		// Memorizzo la larghezza della riga
		this->row_width.push_back( this->GetFont()->GetStringWidth( this->GetString().substr( last, i - last ) ) );

		// Imposto la pagina iniziale
		this->SetPage(0);
	}
}

void
TextBox::SendSignal( Types::Int type, Entity *other ) {

	// Chiamo il gestore dei segnali
	Frame::SendSignal( type, other );

	// Controlla il tipo di segnale
	switch ( type ) {

		// Gestisco il segnale di cambio della pagina
		case SignalType::CHANGE_PAGE: {

			// Emetto il segnale di cambio della pagina
			this->SignalChangePage().emit( this, this->GetPage() );

			break;
		}

		default: break;
	}
}

Types::Bool
TextBox::SendEvent( Event *event, Entity *other ) {

	// Flag di controllo
	Types::Bool end_event = false;

	// Controlla il tipo di evento
	switch ( event->type ) {

		/*
		// Cambio la pagina del testo
		case EventType::SET_PAGE: { 

			this->SetPage( (Types::Uint) event->arg0[0] );
			end_event = true;

			break;
		}
		*/

		default: break;
	}

	// Avvia il gestore degli eventi
	if ( !end_event )
		end_event = Frame::SendEvent( event, other );

	return end_event;
}

void
TextBox::Update( Viewer *viewer, Player *player ) {

	// Avvio la funzione di lavoro superiore
	Frame::Update( viewer, player );

	// Controllo il flag di aggiornamento
	if ( this->update ) {

		// Preparo la stringa
		this->MakeString();

		// Cambio il flag di aggiornamento
		this->update = false;
	}
}

void
TextBox::Draw( const Types::Point2D &offset, Color::RGBA8 blend ) const {

	// Funzione di disegno del testo
	Frame::Draw( offset, blend );

	// Controllo che il testo sia realmente visibile
	if ( (	this->GetFont() != NULL && !this->GetString().empty() && this->GetRows() ) &&
			this->GetOpacity() > 0 ) {

		// Calcolo la posizione
		Types::Point2D pos = this->GetPosition() + offset;

		// Ricavo la riga iniziale della pagina
		Types::Uint page_row = ( this->GetPage() * this->max_rows );

		// Ricavo la larghezza effettiva del testo
		Types::Uint text_width = (Types::Float) ( this->GetSize().w - this->margins.x * 2 );

		// Indice dei colori
		Types::Uint color_index = 0;

		// Numero delle righe da disegnare
		Types::Uint rows = VMIN( this->GetRows() - page_row, this->max_rows );

		// Iteratore
		Types::Uint j, i = 0;

		// Imposto il colore iniziale del testo
		this->GetFont()->SetColor( Color::Make( 255, 255, 255, this->GetOpacity() ) );

		// Disegno riga per riga
		for ( ; i < rows; i++ ) {

			// Offset dell'allineamento
			Types::Float align_off;

			// Controllo il tipo di allineamento
			switch ( this->GetAlign() ) {

				// Allineamento a sinistra
				case ALIGN_LEFT: {

					align_off = 0.0;
					break;
				}

				// Allineamento al centro
				case ALIGN_CENTER: {

					align_off = ( (Types::Float) text_width - (Types::Float) this->row_width[i + page_row] ) / 2.0;
					break;
				}

				// Allineamento a destra
				case ALIGN_RIGHT: {

					align_off = ( (Types::Float) text_width - (Types::Float) this->row_width[i + page_row] );
					break;
				}

				default: break;
			}

			// Offset del carattere
			Types::Float off_char = 0;

			// Disegno i caratteri della riga
			for ( j = this->row_indices[ i + page_row ]; j < this->row_indices[ i + 1 + page_row ]; j++ ) {

				// Controllo il prossimo indice di colore
				while (	color_index < this->color_indices.size() &&
						j >= this->color_indices[color_index].index ) {

					// Imposto l'alpha del font
					Color::ToStruct( this->color_indices[color_index].color )->alpha = this->GetOpacity();

					// Imposto il colore del carattere
					this->GetFont()->SetColor( this->color_indices[color_index].color );

					// Passo all'indice successivo
					color_index++;
				}

				// Disegno il carattere
				this->GetFont()->Draw(	this->GetEngine()->GetDesigner(),
										this->GetString()[j], Types::Point2D(

										pos.x + this->margins.x + align_off + off_char,
										pos.y + this->margins.y + ( (Types::Float) i * this->row_spacing )

									), blend );

				// Incremento l'offset del carattere
				off_char += this->GetFont()->GetCharWidth( this->GetString()[j] );
			}
		}
	}
}

}; // Chiudo il namespace dell'interfaccia grafica

}; // Chiudo il namespace di VGE

#endif
