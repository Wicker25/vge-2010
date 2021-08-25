/* 
    Title --- designer-inl.hpp

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


#ifndef VGE_DESIGNER_INL_HPP
#define VGE_DESIGNER_INL_HPP

#include "vge/designer.hpp"

namespace VGE { // Namespace di VGE

inline void
Designer::SetScreenSize( const Types::Size2D_u &size_ ) {

	// Modifico la dimensione dello schermo
	this->screen_size = size_;
}

inline const Types::Size2D_u &
Designer::GetScreenSize() const {

	// Ritorno la dimensione dello schermo
	return this->screen_size;
}

inline void
Designer::SetWindowCaption( const std::string &title ) {

	// Modifico il titolo e l'icona della finestra
	this->SetWindowCaption( title, "" );
}

inline void
Designer::SetWindowCaption( const std::string &title, const std::string &icon ) {

	// Modifico il titolo e l'icona della finestra
	this->window_title = title;
	this->window_icon = icon;

	SDL_WM_SetCaption(	this->window_title.c_str(),
						this->window_icon.c_str() );
}

inline void
Designer::SetFpsLimit( Types::Uint fps ) {

	// Imposta i FPS massimi
	this->fps_limit = fps;
}

inline const Types::Uint &
Designer::GetFpsLimit() const {

	// Ritorno i FPS massimi
	return this->fps_limit;
}

inline const Types::Uint &
Designer::GetFpsCount() const {

	// Ritorno i FPS massimi
	return this->fps_count;
}

inline void
Designer::SetPosition( const Types::Point2D &position ) const {

	// Imposto la posizione
	glTranslatef( (GLfloat) std::floor( position.x ), (GLfloat) floor( position.y ), 0.0f );
}

inline void
Designer::SetColor( Color::RGBA8 value ) const {

	// Converto il colore nella struttura complessa
	Color::Struct *c_color = Color::ToStruct( value );

	// Applico i colori scelti tenendo conto della trasparenza
	glColor4ub(	(GLubyte) c_color->red,
				(GLubyte) c_color->green,
				(GLubyte) c_color->blue,
				(GLubyte) c_color->alpha );
}

inline void
Designer::SetColor( Color::RGBA8 value, Types::Uint8 opacity ) const {

	// Converto il colore nella struttura complessa
	Color::Struct *c_color = Color::ToStruct( value );

	// Applico i colori scelti tenendo conto della trasparenza
	glColor4ub(	(GLubyte) c_color->red,
				(GLubyte) c_color->green,
				(GLubyte) c_color->blue,
				(GLubyte) ( c_color->alpha * ( (Types::Float) opacity / 255.0f ) ) );
}

inline void
Designer::SetScale( const Types::Size2D_f &scale ) const {

	// Imposto la scala
	if ( scale.w != 1.0f || scale.h != 1.0f )

		glScalef( (GLfloat) scale.w, (GLfloat) scale.h, 0.0f );
}

inline void
Designer::SetRotation( Types::Float value ) const {

	// Imposto la rotazione
	if ( value ) glRotatef( (GLfloat) value, 0.0f, 0.0f, 1.0f );
}

inline void
Designer::SetLineWidth( Types::Uint8 value ) const {

	// Imposto lo spessore della linea
	glLineWidth( (GLfloat) value );
}

inline void
Designer::PushMatrix() const {

	// Memorizzo la matrice corrente
	glPushMatrix();
}

inline void
Designer::PopMatrix() const {

	// Ripristino la matrice precedente
	glPopMatrix();
}

inline void
Designer::DrawLine(	const Types::Point2D &point0, const Types::Point2D &point1 ) const {

	// Disegno una linea
	this->DrawLine( point0, point1, Types::Point2D( 0.0f, 0.0f ) );
}

inline void
Designer::DrawRectangle( const Types::Rect_f &rectangle ) const {

	// Disegno un rettangolo
	this->DrawRectangle( rectangle, Types::Point2D( 0.0f, 0.0f ) );
}

inline void
Designer::DrawFillRectangle( const Types::Rect_f &rectangle ) const {

	// Disegno un rettangolo pieno
	this->DrawFillRectangle( rectangle, Types::Point2D( 0.0f, 0.0f ) );
}

inline void
Designer::DrawCircle( const Types::Point2D &position_center, Types::Float ray ) const {

	// Disegno un cerchio
	this->DrawCircle( position_center, ray, 100 );
}

inline void
Designer::DrawFillCircle( const Types::Point2D &position_center, Types::Float ray ) const {

	// Disegno un cerchio pieno
	this->DrawFillCircle( position_center, ray, 100 );
}

inline void
Designer::DrawCurve(	const Types::Point2D &position_center, Types::Float start_angle,
						Types::Float end_angle, Types::Float ray ) const {

	// Disegno un cerchio
	this->DrawCurve( position_center, start_angle, end_angle, ray, ( end_angle - start_angle ) / 3 );
}

inline void
Designer::DrawPolygon( const Types::Point2DList &point_list ) const {

	// Disegno un poligono
	this->DrawPolygon( point_list, Types::Point2D( 0.0f, 0.0f ) );
}

inline void
Designer::DrawFillPolygon( const Types::Point2DList &point_list ) const {

	// Disegno un poligono pieno
	this->DrawFillPolygon( point_list, Types::Point2D( 0.0f, 0.0f ) );
}

}; // Chiudo il namespace di VGE

#endif
