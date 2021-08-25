/* 
    Title --- game.cpp

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

using namespace VGE;

void
pipponio( Gui::Button *button ) {

	printf( "Hai premuto su %ls\n", static_cast< Gui::TextButton * >( button )->GetName().c_str() );
}

void
pipponio2( Types::Float fraction, Types::Float value, Gui::Slider *slider, Gui::ProgressBar *progress_bar ) {

	printf( "Scorritore: %f - %f - %p \n", fraction, value, slider );
	progress_bar->SetValue( value );
	//progress_bar->SetFraction( fraction );
}


int
main( int argc, char *args[] ) {

	// Creo l'istanza dell'engine
	Engine game( Designer::WM_WINDOW, Types::Size2D_u( 640, 480 ), 32, 60 );
	game.GetDesigner().SetWindowCaption( "VGE" );

	// Carico i font
	Gui::Font font0( "data/fonts/fontset0.png", Types::Size2D_u( 24, 24 ) );
	font0.SetName( SYS_FONT_NORMAL );
	//font0.SetLetterSpacing( 0 );

	// Imposto le caratteristiche della finestra del dialogo
	Gui::MessageBox &dialog = game.GetSystemDialog();

	dialog.GetTextBox().SetRowSpacing( 17.0f );
	dialog.GetBox().SetBorderWidth( 1 );
	//dialog.GetBox().SetColor( Color::Make( 0x2E2EC0FF ) );

	// Carico i suoni del gioco
	Mixer &mixer = game.GetMixer();

	mixer.LoadSound( "data/music/village.ogg" );
	mixer.LoadSound( "data/sound/cursor1.wav" );
	mixer.LoadSound( "data/sound/cursor2.wav" );
	mixer.LoadSound( "data/sound/choice2.wav" );
	mixer.LoadSound( "data/sound/absorb1.wav" );
	mixer.LoadSound( "data/sound/waterfall1.wav" );

	Types::Uint fountain_sound	= mixer.LoadSound( "data/sound/waterfall2_mono.wav" );
	Types::Uint fire_sound		= mixer.LoadSound( "data/sound/fire_wood.wav" );

	mixer.SetSoundVolume( fountain_sound, 0.3f );
	mixer.SetSoundPosition( fountain_sound, Types::Point2D( 325.0f, 180.0f ) );
	mixer.SetSoundDistance( fountain_sound, 300.0f, 1.0f, 500.0f );

	mixer.SetSoundVolume( fire_sound, 1.0f );
	mixer.SetSoundPosition( fire_sound, Types::Point2D( 380, 250 ) );
	mixer.SetSoundDistance( fire_sound, 200.0f, 5.0f, 700.0f );

	//mixer.PlaySound( 0, true );
	//mixer.PlaySound( fountain_sound, true );
	//mixer.PlaySound( fire_sound, true );


	// Carico la scene
	Scene *scene = Maker::LoadScene( "data/scenes/level0.xml" );
	game.AddScene( scene );

	Image face0( "data/images/face_squall.png" );
	face0.SetName( L"face0" );

	Image charset0( "data/charset/ragnarock.png" );
	charset0.SetName( L"charset0" );

	Image shadow( "data/images/shadow.png" );
	shadow.SetName( L"shadow0" );
	shadow.SetCenter( Types::Point2D( 29, 14 ) );
	shadow.SetColor( Color::Make( 255, 255, 255, 180 ) );


	// Carico il giocatore
	Entity *player = Maker::LoadEntity( "data/entities/player0.xml" );
	//player->SetPosition( Types::Point2D( 120, 240 ) );
	scene->Add( player );

	Image particle0( "data/images/particle0.png" );
	particle0.SetName( L"particle0" );
	particle0.SetCenter( Types::Point2D( 17.0f, 17.0f ) );
	particle0.SetOpacity( 120 );

	Image fire_particle( "data/images/particle_fire.png" );
	fire_particle.SetName( L"fire_particle" );
	fire_particle.SetCenter( Types::Point2D( 5.0f, 5.0f ) );
	fire_particle.SetOpacity( 150 );


	// Carico un personaggio
	Entity *character0 = Maker::LoadEntity( "data/entities/character0.xml" );
	scene->Add( character0 );

	//VGE_CHARACTER( character0 )->SetRotation( 45 );
	//VGE_CHARACTER( character0 )->SetDirection( Object::DIRECTION_RIGHT );
	//character0->AddEvent( EventType::TRANSIENT_ROTATION, 359.0f, 1.0f );

	scene->Add( Maker::LoadEntity( "data/entities/pipponio.xml" ) );

	character0->SetPosition( Types::Point2D( 250.0f, 240.0f ) );

	//Entity *text0 = Maker::LoadEntity( "entities/text0.xml" );
	//game.AddToSystemViewer( text0 );

	Gui::Window window( L"Titolo della finestra", Types::Size2D_u( 350, 250 ) );
	window.SetPosition( Types::Point2D( 50.0f, 50.0f ) );
	// window.SetPosition( Types::Point2D( 50.0f, 170.0f ) );
	//game.AddToSystemViewer( &window ); // FIXME FIXME FIXME

	Gui::ProgressBar progress_bar( Types::Size2D_u( 250, 25 ), Gui::ProgressBar::ORIGIN_LEFT );
	progress_bar.SetLabelFormat( L"Loading ... %.1f%%" );
	progress_bar.SetFraction( 0.35f );
	//progress_bar.SetRange( Types::Size2D_f( 20, 80 ) );
	//progress_bar.SetBarColor( Color::Make( 255, 0, 0, 150 ) );
	window.AddChild( &progress_bar );

	Gui::Slider slider( Types::Size2D_u( 250, 15 ), Gui::Slider::ORIENTATION_HORIZONTAL );
	//slider.GetBarButton().SetSize( Types::Size2D_u( 30, 30 ) );
	//slider.SetRulerVisible( false );
	//slider.SetLabelFormat( L"%.0f%%" );
	//slider.SetLabelFormat( L"%+.0f" );
	//slider.GetBox().SetBorderColor( Color::Make( 255, 0, 0, 255 ) );
	//slider.SetColor( Color::Make( 255, 255, 0, 255 ) );
	slider.SetRange( Types::Size2D_f( 0, 100 ) );
	//slider.SetStep( 5 );
	//slider.SignalChangeFraction().connect( sigc::bind( sigc::ptr_fun( pipponio2 ), &progress_bar ) );
	window.AddChild( &slider );

	Gui::Label text0( L"Prova prova" );
	text0.SetColor( Color::Make( 255, 255, 0, 200 ) );
	window.AddChild( &text0 );

	Gui::Container container0( Gui::Container::ORIENTATION_HORIZONTAL );
	window.AddChild( &container0 );

	Gui::TextButton button0( L"Premi qui!" );
	button0.GetLabel().SetString( L"AAAA" );
	button0.SignalPressed().connect( sigc::ptr_fun( pipponio ) );
	container0.AddChild( &button0 );
	//game.AddToSystemViewer( &button0 );

	Gui::ImageButton button1( "data/images/charset_.png" );
	button1.SignalPressed().connect( sigc::ptr_fun( pipponio ) );
	container0.AddChild( &button1 );


	Gui::TextEntry entry0( L"abcdefghilmno" );
	entry0.SetPosition( Types::Point2D( 50.0f, 350.0f ) );
	game.AddToSystemViewer( &entry0 );



	/*
	Entity *flame0 = Maker::LoadEntity( "data/entities/flame0.xml" );
	scene->Add( flame0 );

	Entity *fountain0 = Maker::LoadEntity( "data/entities/fountain0.xml" );
	scene->Add( fountain0 );

	ParticleSystem pippo( &particle0, ParticleSystem::EXPLOSION_MODEL, 7, 100, 1.5f, 1200 );
	pippo.SetPosition( Types::Point2D( 250, 250 ) );
	pippo.SetExplosionRange( 45, 90 );
	scene->Add( &pippo );
	*/

	Viewer camera( Types::Size2D_f( 1.0f, 1.0f ), Types::Point3D( 0.0f, 0.0f, 0.0f ) );
	//camera.SetColor( Color::Make( 255, 0, 0, 255 ) );
	camera.GetBox().SetBorderColor( Color::Make( 255, 0, 0, 255 ) );
	camera.GetBox().SetBorderWidth( 0 );
	camera.SetTarget( player );
	scene->AddViewer( &camera, true );

	/*
	Viewer camera2( Types::Size2D_f( 0.3f, 0.3f ), Types::Point3D( 0.600f, 0.1f, 0.0f ) );
	camera2.SetColor( Color::Make( 40, 200, 255, 255 ) );
	camera2.GetBox().SetBorderColor( Color::Make( 0, 255, 0, 255 ) );
	camera2.GetBox().SetBorderWidth( 2 );
	camera2.SetTarget( character0 );
	scene->AddViewer( &camera2, false );
	*/

	game.MainLoop();
	game.Quit();

	return 0;
}

