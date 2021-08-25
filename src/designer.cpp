/* 
    Title --- designer.cpp

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


#ifndef VGE_DESIGNERS_CPP
#define VGE_DESIGNERS_CPP

#include "vge/designer.hpp"

#include "vge/global.hpp"
#include "vge/inline/global-inl.hpp"

#include "vge/color.hpp"
#include "vge/inline/color-inl.hpp"

#include "vge/interfaces/i-image.hpp"
#include "vge/interfaces/inline/i-image-inl.hpp"

#include "vge/image.hpp"
#include "vge/inline/image-inl.hpp"

#include "vge/inline/designer-inl.hpp"

namespace VGE { // Namespace di VGE

void
Designer::Init( VideoModes mode, const Types::Size2D_u &size, Types::Uint8 depth, Types::Uint fps ) {

	// Log di lavoro
	printf( "<Video>\n" );

	// Log di lavoro
	printf( " Mode %dx%d@%d %dfps %s\n", size.w, size.h, depth, fps, (mode) ? "Window" : "Fullscreen" );

	// Preparo i flags del video
	Types::Int flags = SDL_OPENGL | SDL_HWSURFACE | SDL_HWACCEL | SDL_DOUBLEBUF;
	if ( mode == WM_FULLSCREEN ) flags |= SDL_FULLSCREEN;

	// Inizializzo lo schermo
	this->screen		= SDL_SetVideoMode( size.w, size.h, depth, flags );
	this->SetScreenSize( size );
	this->fps_limit		= fps;

	// Inizializzo le GLEW
	GLenum error = glewInit();

	// Controllo se l'inizializzazione è andata a buon fine
	if ( GLEW_OK != error ) {

		fprintf( stderr, " %s: Could not initialize GLEW: %s\n", FATAL, glewGetErrorString( error ) );
		exit(1);
	};

	// Disabilita la profondità
	glDisable( GL_DEPTH_TEST );

	// Abilito l'alpha blending
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	glEnable( GL_ALPHA_TEST );
	glAlphaFunc( GL_GREATER, 0.0f );

	// Abilito lo scissor test
	glEnable( GL_SCISSOR_TEST );

	// Imposto il colore di sfondo
	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();

	glOrtho(	(GLdouble) 0.0, (GLdouble) size.w, (GLdouble) size.h,
				(GLdouble) 0.0, (GLdouble) -1.0, (GLdouble) 1.0 );

	// Inizializzo le strutture per la regolazione degli fps
	this->clock				= 0;
	this->clock_fps_draw	= 0;
	this->fps_count			= 0; 

	// Stampa la versione delle librerie usate
	this->PrintLibraryVersion();

	// Log di lavoro
	printf( "</Video>\n" );
}

void
Designer::Close() {

	// Chiude l'engine
	SDL_Quit();
}

void
Designer::PrintLibraryVersion() {

	// Log di lavoro
	const SDL_version *sdl_version = SDL_Linked_Version();

	printf( " Loaded SDL v%d.%d.%d\n",	sdl_version->major,
										sdl_version->minor,
										sdl_version->patch );

	// Log di lavoro
	const SDL_version *img_version = IMG_Linked_Version();

	printf( " Loaded SDL_image v%d.%d.%d\n",	img_version->major,
												img_version->minor,
												img_version->patch );

	// Log di lavoro
	printf( " Loaded OpenGL v%s\n", glGetString( GL_VERSION ) );

	// Log di lavoro
	printf( " Loaded GLEW v%s\n", glewGetString(GLEW_VERSION ) );

}

void
Designer::UpdateCaption() {

	// Aggiorno il titolo della finestra
	char fps_string[40];
	snprintf( fps_string, 40, "  -  FPS : %d  -  Entities: %zu", this->GetFpsCount(), Global::Entities.size() );

	SDL_WM_SetCaption( ( this->window_title + fps_string ).c_str(),
						 this->window_icon.c_str() );
}

void
Designer::PushDrawableArea( const Types::Rect_u &area ) {

	// Calcolo l'intersezione dell'area da disegno con quella superiore
	Types::Rect_u rect;

	if ( !this->drawable_areas.empty() )

		rect = this->drawable_areas.top().Sub( area );
	else
		rect = area;

	if ( rect.left <= rect.right && rect.top <= rect.bottom ) {

		// Imposto l'area disegnabile
		glScissor(	(GLint) rect.left,
					(GLint) ( this->GetScreenSize().h - rect.top - ( rect.bottom - rect.top ) ),
					(GLsizei) rect.right - rect.left,
					(GLsizei) rect.bottom - rect.top );

		// Aggiungo l'area alla pila
		this->drawable_areas.push( rect );
	}
}

void
Designer::PopDrawableArea() {

	// Controllo se esiste almeno un'area da disegno
	if ( !this->drawable_areas.empty() )

		// Rimuovo l'area da disegno corrente
		this->drawable_areas.pop();

	// Controllo se esiste un'area da disegno precedente
	if ( !this->drawable_areas.empty() ) {

		// Ricavo l'area
		const Types::Rect_u &area = this->drawable_areas.top();

		// Imposto l'area disegnabile
		glScissor(	(GLint) area.left,
					(GLint) ( this->GetScreenSize().h - area.top - ( area.bottom - area.top ) ),
					(GLsizei) area.right - area.left,
					(GLsizei) area.bottom - area.top );
	} else {

		// Rimuovo l'area disegnabile
		glScissor( (GLint) 0, (GLint) 0, (GLsizei) this->GetScreenSize().w, (GLsizei) this->GetScreenSize().h );
	}
}

void
Designer::CleanDrawableArea() {

	// Rimuovo l'area disegnabile
	glScissor( (GLint) 0, (GLint) 0, (GLsizei) this->GetScreenSize().w, (GLsizei) this->GetScreenSize().h );

	// Pulisco la pila delle aree da disegno
	while ( !this->drawable_areas.empty() )

		this->drawable_areas.pop();
}

Types::Bool
Designer::Update() {

	// Incremento il contatore dei FPS
	this->fps_count++;

	// Aggiorno lo schermo
	SDL_GL_SwapBuffers();

	// Regolo dinamicamente i FPS
	Types::Int c_clock = SDL_GetTicks() - this->clock;

	if ( c_clock < (Types::Int) ( 1000 / this->GetFpsLimit() ) )
		SDL_Delay( ( 1000 / this->GetFpsLimit() ) - c_clock );

	this->clock = SDL_GetTicks();

	// Controllo che sia passato almeno un secondo
	if ( SDL_GetTicks() - this->clock_fps_draw >= 1000 ) {

		// Aggiorno il titolo della finestra
		this->UpdateCaption();

		// Azzero il contatore dei frames
		this->fps_count = 0;
		// Azzero il timer	
		this->clock_fps_draw = SDL_GetTicks();
	}

	return true;
}

void
Designer::DrawPoint( const Types::Point2D &point ) const {

	// Memorizzo la matrice
	this->PushMatrix();

	// Disegno un punto
	glBegin( GL_POINTS );

		glVertex2i( (GLfloat) point.x, (GLfloat) point.y );

	glEnd();

	// Ricarico la matrice
	this->PopMatrix();
}

void
Designer::DrawLine(	const Types::Point2D &point0, const Types::Point2D &point1,
					const Types::Point2D &offset ) const {

	// Memorizzo la matrice
	this->PushMatrix();

	// Imposto l'offset
	this->SetPosition( offset );

	// Disegno una linea
	glBegin( GL_LINES );

		glVertex2i( (GLfloat) point0.x, (GLfloat) point0.y );
		glVertex2i( (GLfloat) point1.x, (GLfloat) point1.y );

	glEnd();

	// Ricarico la matrice
	this->PopMatrix();
}

void
Designer::DrawRectangle( const Types::Rect_f &rectangle, const Types::Point2D &offset ) const {

	// Memorizzo la matrice
	this->PushMatrix();

	// Imposto l'offset
	this->SetPosition( offset );

	// Disegno un rettangolo
	glBegin( GL_LINE_LOOP );

		glVertex2i( (GLfloat) rectangle.left, (GLfloat) rectangle.top );
		glVertex2i( (GLfloat) rectangle.right, (GLfloat) rectangle.top );
		glVertex2i( (GLfloat) rectangle.right, (GLfloat) rectangle.bottom );
		glVertex2i( (GLfloat) rectangle.left, (GLfloat) rectangle.bottom );

	glEnd();

	// Ricarico la matrice
	this->PopMatrix();
}

void
Designer::DrawFillRectangle( const Types::Rect_f &rectangle, const Types::Point2D &offset ) const {

	// Memorizzo la matrice
	this->PushMatrix();

	// Imposto l'offset
	this->SetPosition( offset );

	// Disegno un rettangolo pieno
	glBegin( GL_QUADS );

		glVertex2i( (GLfloat) rectangle.left, (GLfloat) rectangle.top );
		glVertex2i( (GLfloat) rectangle.right, (GLfloat) rectangle.top );
		glVertex2i( (GLfloat) rectangle.right, (GLfloat) rectangle.bottom );
		glVertex2i( (GLfloat) rectangle.left, (GLfloat) rectangle.bottom );

	glEnd();

	// Ricarico la matrice
	this->PopMatrix();
}

void
Designer::DrawCircle( const Types::Point2D &position_center, Types::Float ray, Types::Uint vertices ) const {

	// Memorizzo la matrice
	this->PushMatrix();

	// Imposto l'offset
	this->SetPosition( position_center );

	// Calcolo la distanza tra un vertice e l'altro
	const Types::Float step = 360.0f / (Types::Float) vertices;

	// Disegno un cerchio
	glBegin( GL_LINE_LOOP );

		for ( Types::Float angle = 0.0f; angle < 360; angle += step ) {

			glVertex2f(	(GLfloat) cos( VTORAD( angle ) ) * ray,
						(GLfloat) sin( VTORAD( angle ) ) * ray );
		}

	glEnd();

	// Ricarico la matrice
	this->PopMatrix();
}

void
Designer::DrawFillCircle( const Types::Point2D &position_center, Types::Float ray, Types::Uint vertices ) const {

	// Memorizzo la matrice
	this->PushMatrix();

	// Imposto l'offset
	this->SetPosition( position_center );

	// Calcolo la distanza tra un vertice e l'altro
	const Types::Float step = 360.0f / (Types::Float) vertices;

	// Disegno un cerchio pieno
	glBegin( GL_TRIANGLE_FAN );

		for ( Types::Float angle = 0.0f; angle < 360; angle += step ) {

			glVertex2f(	(GLfloat) cos( VTORAD( angle ) ) * ray,
						(GLfloat) sin( VTORAD( angle ) ) * ray );
		}

	glEnd();

	// Ricarico la matrice
	this->PopMatrix();
}

void
Designer::DrawCurve(	const Types::Point2D &position_center, Types::Float start_angle,
						Types::Float end_angle, Types::Float ray, Types::Uint vertices	) const {

	// Memorizzo la matrice
	this->PushMatrix();

	// Imposto l'offset
	this->SetPosition( position_center );

	// Calcolo la distanza tra un vertice e l'altro
	const Types::Float step = ( end_angle - start_angle ) / (Types::Float) vertices;

	// Disegno una curva
	glBegin( GL_LINE_STRIP );

		for ( Types::Float angle = start_angle; angle < end_angle; angle += step ) {

			glVertex2f(	(GLfloat) -cos( VTORAD( angle ) ) * ray,
						(GLfloat) -sin( VTORAD( angle ) ) * ray );
		}

	glEnd();

	// Ricarico la matrice
	this->PopMatrix();
}

void
Designer::DrawPolygon( const Types::Point2DList &point_list, const Types::Point2D &offset ) const {

	// Controllo che la lista dei punti non sia vuota
	if ( !point_list.empty() ) {

		// Memorizzo la matrice
		this->PushMatrix();

		// Imposto l'offset
		this->SetPosition( offset );

		// Disegno un poligono
		glBegin( GL_LINE_LOOP );

			for ( Types::Uint i = 0; i < point_list.size(); i++ )

				glVertex2f( (GLfloat) point_list[i].x, (GLfloat) point_list[i].y );

		glEnd();

		// Ricarico la matrice
		this->PopMatrix();
	}
}

void
Designer::DrawFillPolygon( const Types::Point2DList &point_list, const Types::Point2D &offset ) const {

	// Controllo che la lista dei punti non sia vuota
	if ( !point_list.empty() ) {

		// Memorizzo la matrice
		this->PushMatrix();

		// Imposto l'offset
		this->SetPosition( offset );

		// Disegno un poligono pieno
		glBegin( GL_TRIANGLE_FAN );

			for ( Types::Uint i = 0; i < point_list.size(); i++ )

				glVertex2f( (GLfloat) point_list[i].x, (GLfloat) point_list[i].y );

		glEnd();

		// Ricarico la matrice
		this->PopMatrix();
	}
}

void
Designer::DrawImage(	const InterfaceImage &image, const Types::Point2D &position,
						const Types::Point2D &center, Color::RGBA8 blend, Types::Uint8 opacity ) const {

	// Abilito le texture 2D
	glEnable( GL_TEXTURE_2D );

	// Scelgo la texture
	glBindTexture( GL_TEXTURE_2D, image.GetTextureId() );

	// Imposto i parametri di filtering
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
	//glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );
	//glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );

	// Memorizzo la matrice
	this->PushMatrix();

	// Imposto la posizione dell'immagine
	this->SetPosition( position );

	// Applico le modifiche all'oggetto
	this->SetRotation( image.GetRotation() );
	this->SetScale( image.GetScale() );

	// Controllo se è abilitato il color blending per i toni ambientali
	if ( !image.GetColorBlending() )

		this->SetColor( image.GetColor(), opacity );
	else
		this->SetColor( Color::BlendMul( image.GetColor(), blend ), opacity );

	// Calcolo la posizione del ritaglio
	GLfloat src_x = (GLfloat) ( image.GetClipOffset().x * image.GetClipSize().w );
	GLfloat src_y = (GLfloat) ( image.GetClipOffset().y * image.GetClipSize().h );

	// Calcolo i vertici della texture
	GLfloat tex1_x = src_x / (GLfloat) image.GetImageSize().w;
	GLfloat tex1_y = src_y / (GLfloat) image.GetImageSize().h;
	GLfloat tex2_x = (GLfloat) ( src_x + (GLfloat) image.GetClipSize().w ) / (GLfloat) image.GetImageSize().w;
	GLfloat tex2_y = (GLfloat) ( src_y + (GLfloat) image.GetClipSize().h ) / (GLfloat) image.GetImageSize().h;

	// Disegno la texture
	glBegin( GL_TRIANGLE_STRIP );

		glTexCoord2f( tex1_x, tex2_y );
		glVertex2i( (GLint) -center.x, (GLint) image.GetClipSize().h - (GLint) center.y );

		glTexCoord2f( tex1_x, tex1_y );
		glVertex2i( (GLint) -center.x, (GLint) -center.y );

		glTexCoord2f( tex2_x, tex2_y );
		glVertex2i( (GLint) image.GetClipSize().w - (GLint) center.x, (GLint) image.GetClipSize().h - (GLint) center.y );

		glTexCoord2f( tex2_x, tex1_y );
		glVertex2i( (GLint) image.GetClipSize().w - (GLint) center.x, (GLint) -center.y );

	glEnd();

	// Ricarico la matrice
	this->PopMatrix();

	// Disabilito le texture 2D
	glDisable( GL_TEXTURE_2D );
}

}; // Chiudo il namespace di VGE

#endif
