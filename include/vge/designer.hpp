/* 
    Title --- designer.hpp

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


#ifndef VGE_DESIGNER_HPP
#define VGE_DESIGNER_HPP

#include <iostream>
#include <vector>
#include <stack>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/glew.h> 

#include "vge/consts.hpp"
#include "vge/types.hpp"
#include "vge/error.hpp"
#include "vge/math.hpp"
#include "vge/global.hpp"

#include "vge/color.hpp"

namespace VGE { // Namespace di VGE

// Pila delle aree da disegno
typedef std::stack< Types::Rect_u > DrawableStack;

// Prototipi
class InterfaceImage;
class Image;

class Designer {

	/* DISEGNATORE PRINCIPALE */

public:

	// Modalità video
	typedef enum {

		WM_FULLSCREEN,
		WM_WINDOW,

	} VideoModes;

	// Inizializza il gestore degli eventi in ingresso
	void Init( VideoModes mode, const Types::Size2D_u &size, Types::Uint8 depth, Types::Uint fps );

	// Deinizializza il gestore degli eventi in ingresso
	void Close();

	// Modifica la dimensione dello schermo
	void SetScreenSize( const Types::Size2D_u &size_ );
	// Ritorna la dimensione dello schermo
	const Types::Size2D_u &GetScreenSize() const;

	// Modifica il titolo e l'icona della finestra
	void SetWindowCaption( const std::string &title );
	void SetWindowCaption( const std::string &title, const std::string &icon );

	// Imposta i FPS massimi
	void SetFpsLimit( Types::Uint fps );
	// Ritorna i FPS massimi
	const Types::Uint &GetFpsLimit() const;
	// Ritorna i FPS correnti
	const Types::Uint &GetFpsCount() const;

	// Aggiunge un'area disegnabile alla pila
	void PushDrawableArea( const Types::Rect_u &area );
	// Torna all'area disegnabile precedente
	void PopDrawableArea();
	// Rimuove l'area disegnabile
	void CleanDrawableArea();

	// Imposto la posizione
	void SetPosition( const Types::Point2D &position ) const;

	// Imposta il colore
	void SetColor( Color::RGBA8 value ) const;
	void SetColor( Color::RGBA8 value, Types::Uint8 opacity ) const;

	// Imposto la scala
	void SetScale( const Types::Size2D_f &scale ) const;

	// Imposto la rotazione
	void SetRotation( Types::Float value ) const;

	// Imposta lo spessore della linea
	void SetLineWidth( Types::Uint8 value ) const;

	// Memorizza la matrice corrente
	void PushMatrix() const;
	// Ripristina la matrice precedente
	void PopMatrix() const;

	// Aggiorna lo schermo
	Types::Bool Update();

	// Disegna un punto
	void DrawPoint( const Types::Point2D &point ) const;

	// Disegna una linea
	void DrawLine( const Types::Point2D &point0, const Types::Point2D &point1 ) const;
	void DrawLine( const Types::Point2D &point0, const Types::Point2D &point1, const Types::Point2D &offset ) const;

	// Disegna un rettangolo
	void DrawRectangle( const Types::Rect_f &rectangle ) const;
	void DrawRectangle( const Types::Rect_f &rectangle, const Types::Point2D &offset ) const;

	// Disegna un rettangolo pieno
	void DrawFillRectangle( const Types::Rect_f &rectangle ) const;
	void DrawFillRectangle( const Types::Rect_f &rectangle, const Types::Point2D &offset ) const;

	// Disegna un cerchio
	void DrawCircle( const Types::Point2D &position_center, Types::Float ray ) const;
	void DrawCircle( const Types::Point2D &position_center, Types::Float ray, Types::Uint vertices ) const;

	// Disegna un cerchio pieno
	void DrawFillCircle( const Types::Point2D &position_center, Types::Float ray ) const;
	void DrawFillCircle( const Types::Point2D &position_center, Types::Float ray, Types::Uint vertices ) const;

	// Disegna una curva
	void DrawCurve(	const Types::Point2D &position_center, Types::Float start_angle,
					Types::Float end_angle, Types::Float ray ) const;
	void DrawCurve(	const Types::Point2D &position_center, Types::Float start_angle,
					Types::Float end_angle, Types::Float ray, Types::Uint vertices ) const;

	// Disegna un poligono
	void DrawPolygon( const Types::Point2DList &point_list ) const;
	void DrawPolygon( const Types::Point2DList &point_list, const Types::Point2D &offset ) const;

	// Disegna un poligono pieno
	void DrawFillPolygon( const Types::Point2DList &point_list ) const;
	void DrawFillPolygon( const Types::Point2DList &point_list, const Types::Point2D &offset ) const;

	// Disegna un'immagine
	void DrawImage(	const InterfaceImage &image, const Types::Point2D &position,
					const Types::Point2D &center, Color::RGBA8 blend, Types::Uint8 opacity ) const;

protected:

	// Superficie principale
	SDL_Surface *screen;

	// Dimensioni della finestra
	Types::Size2D_u screen_size;

	// Titolo e icona della finestra
	std::string window_title;
	std::string window_icon;

	// Limite degli FPS
	Types::Uint fps_limit;

	// Regolazione degli fps
	Types::Uint fps_count;
	Types::Int clock;
	Types::Int clock_fps_draw;

	// Pila delle aree da disegno
	DrawableStack drawable_areas;

	// Stampa la versione delle librerie usate
	void PrintLibraryVersion();

	// Aggiorna il titolo della finestra
	void UpdateCaption();
};

}; // Chiudo il namespace di VGE

#endif
