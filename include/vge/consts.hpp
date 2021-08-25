/* 
    Title --- const.hpp

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


#ifndef CONSTS_HPP
#define CONSTS_HPP

#include <climits>
#include <cfloat>
#include <cmath>
#include <list>

#include "vge/types.hpp"

namespace VGE { // Namespace di VGE

namespace Layer { // Namespace del livello di profondità

// Livello di profondità
enum {

	BOTTOM	= 0,
	SHADOW	= 1,
	TOP		= INT_MAX,
};

}; // Chiudo il namespace del livello di profondità


// BORDI

#define BORDER0		0.0020f
#define BORDER1		0.0040f
#define BORDER2		0.0060f
#define BORDER3		0.0080f
#define BORDER4		0.0100f
#define BORDER5		0.0120f
#define BORDER6		0.0140f
#define BORDER7		0.0160f
#define BORDER8		0.0180f
#define BORDER9		0.0200f
#define BORDER10	0.0220f

// --------------------------------

// FONT DI SISTEMA

#define SYS_FONT_NORMAL				L"sys_font_normal"

// --------------------------------

#define T_ASPECT_ANIM			L"aspect_animation"
#define T_ASPECT				L"aspect"
#define T_ASPECT_MANIP			L"aspect_manipulation"
#define T_CAREA					L"carea"
#define T_COLOR_TRANSITION		L"color_transition"
#define T_ENTITY				L"entity"
#define T_EVENT					L"event"
#define T_EVENT_LIST			L"event_list"
#define T_EXPLOSION				L"explosion"
#define T_FRAME					L"frame"
#define T_GRAVITY				L"gravity"
#define T_IAREA					L"iarea"
#define T_LAYER					L"layer"
#define T_OBJ_FEATURES			L"object_features"
#define T_PARTICLES				L"particles"
#define T_SCALE_TRANSITION		L"scale_transition"
#define T_SCENE					L"scene"
#define T_STREAM				L"stream"
#define T_TILE					L"tile"
#define T_TILESET				L"tileset"
#define T_VAREA					L"varea"
#define T_VERTEX				L"vertex"

// --------------------------------

#define A_LEFT			L"left"
#define A_TOP			L"top"
#define A_RIGHT			L"right"
#define A_BOTTOM		L"bottom"

#define A_WIDTH			L"width"
#define A_HEIGHT		L"height"

#define A_ACCELERATION		L"acceleration"
#define A_ACTIVE			L"active"
#define A_BLENDING			L"blending"
#define A_BORDER_COLOR		L"border_color"
#define A_BORDER_WIDTH		L"border_width"
#define A_CENTER			L"center"
#define A_CLIP				L"clip"
#define A_COLOR				L"color"
#define A_COORDS			L"coords"
#define A_DEPTH				L"depth"
#define A_DIRECTION			L"direction"
#define A_END				L"end"
#define A_ENTITY			L"entity"
#define A_FACE				L"face"
#define A_FILLED			L"filled"
#define A_FIXED				L"fixed"
#define A_FONT				L"font"
#define A_FRAME				L"frame"
#define A_FREQUENCY			L"frequency"
#define A_IMAGE				L"image"
#define A_LIFE				L"life"
#define A_LOOP				L"loop"
#define A_MESSAGE			L"message"
#define A_MODEL				L"model"
#define A_NAME				L"name"
#define A_NUMBER			L"number"
#define A_OPACITY			L"opacity"
#define A_PAGE				L"page"
#define A_RANGE				L"range"
#define A_ROTATION			L"rotation"
#define A_ROW_SPACING		L"row_spacing"
#define A_SCALE				L"scale"
#define A_SENSIBLE			L"sensible"
#define A_SERIES			L"series"
#define A_SHADOW			L"shadow"
#define A_SIZE				L"size"
#define A_SOLID				L"solid"
#define A_SPEED				L"speed"
#define A_SRC				L"src"
#define A_START				L"start"
#define A_STATUS			L"status"
#define A_STRING			L"string"
#define A_SYMMETRY			L"symmetry"
#define A_TILESET			L"tileset"
#define A_TILE_SIZE			L"tile_size"
#define A_TYPE				L"type"
#define A_VALUE				L"value"
#define A_VISIBLE			L"visible"

#define A_X				L"x"
#define A_Y				L"y"
#define A_Z				L"z"

// --------------------------------

#define V_TRUE			L"true"
#define V_FALSE			L"false"

#define V_LEFT			L"left"
#define V_UP			L"up"
#define V_RIGHT			L"right"
#define V_DOWN			L"down"

#define V_PLAY			L"play"
#define V_PAUSE			L"pause"
#define V_STOP			L"stop"

#define V_ENTITY			L"entity"
#define V_IMAGE				L"image"
#define V_TEXT				L"text"
#define V_SPRITE			L"sprite"
#define V_OBJECT			L"object"
#define V_CHARACTER			L"character"
#define V_PLAYER			L"player"
#define V_PARTICLE_SYSTEM	L"particle_system"

#define V_EVENT_SET_VISIBLE						L"set_visible"
#define V_EVENT_SET_FIXED						L"set_fixed"
#define V_EVENT_SET_SENSIBLE					L"set_sensible"
#define V_EVENT_SET_POSITION					L"set_position"
#define V_EVENT_MOVE_POSITION					L"move_position"
#define V_EVENT_SHOW_MESSAGE					L"show_message"
#define V_EVENT_WAIT_DIALOG						L"wait_dialog"
#define V_EVENT_WAIT_SECONDS					L"wait_seconds"

#define V_EVENT_SET_ANIMATION_SPEED				L"set_animation_speed"
#define V_EVENT_SET_COLOR						L"set_color"
#define V_EVENT_TRANSIENT_COLOR					L"transient_color"
#define V_EVENT_SET_ROTATION					L"set_rotation"
#define V_EVENT_TRANSIENT_ROTATION				L"transient_rotation"

#define V_EVENT_SET_PAGE						L"set_page"
#define V_EVENT_NEXT_PAGE						L"next_page"
#define V_EVENT_PREVIOUS_PAGE					L"previous_page"

#define V_EVENT_WAIT_COLLISION					L"wait_collision"
#define V_EVENT_WAIT_INTERACTION				L"wait_interaction"

#define V_EVENT_SET_SPEED						L"set_speed"
#define V_EVENT_MOVE_LEFT						L"move_left"
#define V_EVENT_MOVE_UP							L"move_up"
#define V_EVENT_MOVE_RIGHT						L"move_right"
#define V_EVENT_MOVE_DOWN						L"move_down"
#define V_EVENT_SHOW_OBJ_MESSAGE				L"show_obj_message"

#define V_EVENT_SET_ACTIVE						L"set_active"
#define V_EVENT_SET_STREAM_DIRECTION			L"set_stream_direction"
#define V_EVENT_TRANSIENT_STREAM_DIRECTION		L"transient_stream_direction"
#define V_EVENT_SET_COLOR_TRANSITION			L"set_color_transition"

#define V_STREAM_MODEL							L"stream"
#define V_EXPLOSION_MODEL						L"explosion"
#define V_FLAME_MODEL							L"flame"

// --------------------------------

}; // Chiudo il namespace di VGE

#endif
