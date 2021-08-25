/* 
    Title --- text-box-inl.hpp

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


#ifndef VGE_TEXT_BOX_INL_HPP
#define VGE_TEXT_BOX_INL_HPP

#include "vge/widgets/text-box.hpp"

namespace VGE { // Namespace di VGE

namespace Gui { // Namespace dell'interfaccia grafica

inline void
TextBox::SetFont( Font *font ) {

	// Imposto il font
	this->t_font = font;

	// Imposto il flag di aggiornamento
	this->update = true;
}

inline Font *
TextBox::GetFont() const {

	// Ritorno il puntatore al font
	return ( this->t_font != NULL ) ? this->t_font : Global::GetFont( SYS_FONT_NORMAL );
}

inline const std::wstring
TextBox::GetString() const {

	// Ritorno la stringa
	return this->t_string;
}

inline const std::wstring
TextBox::GetOnlyString() const {

	// Ritorno la stringa senza la formattazione
	return this->t_string;
}

inline void
TextBox::SetRowSpacing( Types::Float value ) {

	// Imposto lo spazio tra le righe
	this->row_spacing = value;

	// Calcolo il numero delle righe visualizzabili
	this->SetMaxRows();
}

inline Types::Float
TextBox::GetRowSpacing() const {

	// Ritorno lo spazio tra le righe
	return this->row_spacing;
}

inline void
TextBox::SetAlign( const TextBox::Align &align ) {

	// Imposto l'allineamento del testo
	this->text_align = align;
}

inline const TextBox::Align &
TextBox::GetAlign() const {

	// Ritorno l'allineamento del testo
	return this->text_align;
}

inline void
TextBox::PrependRow( const std::wstring &string ) {

	// Aggiungo una nuova riga all'inizio del testo
	this->t_string.insert( 0, string + L"\n" );

	// Imposto il flag di aggiornamento
	this->update = true;
}

inline void
TextBox::AppendRow( const std::wstring &string ) {

	// Aggiungo una nuova riga alla fine del testo
	this->t_string.append( L"\n" + string );

	// Imposto il flag di aggiornamento
	this->update = true;
}

inline void
TextBox::SetMaxRows() {

	// Calcolo il numero delle righe visualizzabili
	this->max_rows = std::floor( (Types::Float) ( this->GetSize().h - this->margins.y * 2 ) / this->GetRowSpacing() );
}

inline Types::Uint
TextBox::Lenght() const {

	// Ritorna la lunghezza della stringa
	return (Types::Uint) this->GetString().length();
}

inline Types::Uint
TextBox::GetRows() const {

	// Ritorno il numero delle righe del testo
	return (Types::Uint) ( ( this->row_indices.size() > 0 ) ? this->row_indices.size() - 1 : 0 );
}

inline void
TextBox::SetPage( Types::Uint page ) {

	// Verifico la correttezza dei parametri
	if ( page >= 0 && page <= this->GetNumberOfPages() ) {

		// Imposto la pagina corrente
		this->c_page = page;

		// Invia il segnale di cambio della pagina
		this->SendSignal( SignalType::CHANGE_PAGE, NULL );
	}
}

inline Types::Uint
TextBox::GetPage() const {

	// Ritorno la pagina corrente
	return this->c_page;
}

inline bool
TextBox::NextPage() {

	// Passo alla pagina successiva
	this->SetPage( this->GetPage() + 1 );

	// Controllo se sono arrivato alla fine delle pagine
	return this->IsLastPage();
}

inline bool
TextBox::PreviousPage() {

	// Torno alla pagina precedente
	this->SetPage( this->GetPage() - 1 );

	// Controllo se sono tornato alla prima pagina
	return this->IsFirstPage();
}

inline void
TextBox::GoToFirstPage() {

	// Passo alla prima pagina
	this->SetPage(0);
}

inline void
TextBox::GoToLastPage() {

	// Passo all'ultima pagina
	this->SetPage( this->GetNumberOfPages() - 1 );
}

inline bool
TextBox::IsFirstPage() const {

	// Controllo se la pagina corrente è la prima
	return ( this->GetPage() == 0 );
}

inline bool
TextBox::IsLastPage() const {

	// Controllo se la pagina corrente è l'ultima
	return ( this->GetPage() == this->GetNumberOfPages() - 1 );
}

inline Types::Uint
TextBox::GetNumberOfPages() const {

	// Ritorno il numero delle pagine
	return ceil( (Types::Float) this->GetRows() / (Types::Float) this->max_rows );
}

inline sigc::signal< void, TextBox *, Types::Uint > &
TextBox::SignalChangePage() {

	// Ritorno l'istanza del segnale di cambio della pagina
	return this->signal_change_page;
}

}; // Chiudo il namespace dell'interfaccia grafica

}; // Chiudo il namespace di VGE

#endif
