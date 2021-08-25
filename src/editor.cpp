/* 
    Title --- editor.cpp

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


#include <iostream>

#include "vge/vge.hpp"

#define SCREEN_W	640
#define SCREEN_H	480

#define SYS_COLOR	0xB0E000A0

using namespace VGE;

class SceneEditor : public Scene {

	/* EDITOR DELLA SCENA */

public:

};


void Pippo1( const Gui::Button * ) {

	//printf( "AAAAAAAA\n" );
}

void Pippo2( const Gui::Button * ) {

	//printf( "BBBBBBBB\n" );
}


int
main( int argc, char *args[] ) {

	// Creo l'istanza dell'engine
	Engine game( Designer::WM_WINDOW, Types::Size2D_u( SCREEN_W, SCREEN_H ), 32, 60 );
	game.GetDesigner().SetWindowCaption( "Editor della scena" );

	// Carico i font
	Gui::Font font0( "fonts/fontset1.png", Types::Size2D_u( 24, 24 ) );
	font0.SetName( SYS_FONT_NORMAL );
	font0.SetLetterSpacing( 0.4f );

	/*
	// Imposto il cursore dei menù
	Image cursor0( "cursor/left_side.png" );
	cursor0.SetPosition( Types::Point3D( 0.0f, 0.0f, Layer::TOP ) );
	cursor0.SetCenter( Types::Point2D( 0, 6 ) );
	game.SetMenuCursor( &cursor0 );
	*/

	// Imposto le caratteristiche della finestra del dialogo
	Gui::MessageBox &sys_dialog = game.GetSystemDialog();

	sys_dialog.GetTextBox().SetRowSpacing( 17.0f );
	sys_dialog.GetBox().SetBorderWidth( 1 );
	//sys_dialog.GetBox().SetColor( MakeColor( 0x2E2EC0FF ) );

	// Carico i suoni del gioco
	//Mixer &mixer = game.GetMixer();



	// Creo la vuota
	SceneEditor scene;
	game.AddScene( &scene );

	scene.AddMapLayer( "tileset/tileset_0.png", Types::Size2D_u( 60, 47 ), Scene::BOTTOM, 255 );
	scene.AddTile( Scene::BOTTOM, 0, Types::Point2D( 0, 0 ), Types::Rect_u( 0, 0, 15, 15 ) );
	scene.AddTile( Scene::BOTTOM, 0, Types::Point2D( 3, 0 ), Types::Rect_u( 2, 2, 6, 6 ) );


	// Creo il titolo della finestra
	Gui::TextBox title( L"Editor della scena" );
	title.SetPosition( Types::Point2D( SCREEN_W / 2 - title.GetSize().w / 2, 15 ) );
	game.AddToSystemViewer( &title );



	// Creo la finestra di lavoro
	Gui::Window window( Types::Size2D_u( SCREEN_W, 80 ) );

	window.SetPosition( Types::Point2D(	0.0f, SCREEN_H - window.GetSize().h ) );

	window.GetBox().SetColor( Color::Make( SYS_COLOR ) );
	window.GetBox().SetBorderWidth( 1 );

	game.AddToSystemViewer( &window );

	// Imposto il focus sulla finestra
	//window.SetFocus( true );


	// Creo il contenitore della barra del percorso
	Gui::Container list_box( Gui::Container::ORIENTATION_HORIZONTAL );
	window.AddChild( &list_box );

	// Carico il tileset
	Image tileset( "tileset/tileset_0.png", Types::Size2D_u( 60, 47 ) );

	// Ricavo il numero di piastrelle
	Types::Uint tiles_h	= ( tileset.GetImageSize().w / tileset.GetClipSize().w ) - 1;
	Types::Uint tiles_v	= ( tileset.GetImageSize().h / tileset.GetClipSize().h ) - 1;
	Types::Uint tiles	= tiles_h * tiles_v;

	// Iteratore
	Types::Uint i = 0;

	// Estraggo le piastrelle
	for ( ; i < VMIN( 8, tiles ); i++ ) {

		Gui::ImageButton *tile = new Gui::ImageButton( tileset );

		tile->GetIcon().SetClipOffset( Types::Size2D_u( i % tiles_h, i / tiles_h ) );
		tile->GetBox().SetBorderWidth( 1 );

		list_box.AddChild( tile, Gui::Container::PACKING_EXPAND, 0.5f, 0.5f );
	}





	/*
	// Creo la finestra di lavoro
	Gui::Window dialog( Types::Size2D_u( 340, 100 ) );

	dialog.SetPosition( Types::Point3D(	SCREEN_W / 2 - dialog.GetSize().w / 2,
										SCREEN_H / 2 - dialog.GetSize().h / 2, Layer::TOP ) );

	dialog.GetBox().SetColor( MakeColor( SYS_COLOR ) );
	dialog.GetBox().SetBorderWidth( 1 );

	game.AddToSystemViewer( &dialog );

	// Creo il contenitore della barra del percorso
	Gui::Container path_container( Gui::Container::HORIZONTAL );
	dialog.AddChild( &path_container );

	// Creo l'etichetta dell'inserimento del percorso
	Gui::Text path_label( Global::GetFont( L"font0" ), L"Percorso:" );
	path_container.AddChild( &path_label, Gui::Container::COLLAPSE, 10.0f, 0.5f );

	// Creo la barra di inserimento del percorso
	Gui::TextEntry path_entry( Global::GetFont( L"font0" ), L"/home/wicker25", Types::Size2D_u( 200, 27 ) );
	path_container.AddChild( &path_entry, Gui::Container::COLLAPSE );

	// Creo il pulsante di conferma
	Gui::TextButton confirm_button( Global::GetFont( L"font0" ), L"Conferma" );
	confirm_button.SignalPressed().connect( sigc::ptr_fun( Pippo1 ) );
	dialog.AddChild( &confirm_button, Gui::Container::EXPAND );

	// Imposto il focus sulla finestra
	//dialog.SetFocus( true );
	*/




	Viewer camera( Types::Size2D_f( 1.0f, 1.0f ), Types::Point3D( 0.0f, 0.0f, 0.0f ) );
	//camera.SetColor( MakeColor( 255, 180, 30, 255 ) );
	camera.GetBox().SetBorderColor( Color::Make( 255, 0, 0, 255 ) );
	camera.GetBox().SetBorderWidth( 0 );
	//camera.SetTarget( player );
	scene.AddViewer( &camera, true );

	game.MainLoop();
	game.Quit();

	return 0;
}

