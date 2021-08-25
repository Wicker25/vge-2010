/* 
    Title --- player-inl.hpp

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


#ifndef VGE_PLAYER_INL_HPP
#define VGE_PLAYER_INL_HPP

#include "vge/player.hpp"

namespace VGE { // Namespace di VGE

inline BoundingArea &
Player::GetInteractionArea() {

	// Ritorno l'area di interazione
	return this->interaction_area;
}

inline const BoundingArea &
Player::GetInteractionArea() const {

	// Ritorno l'area di interazione
	return this->interaction_area;
}

inline sigc::signal< void, Player *, Sprite * > &
Player::SignalCheckInteration() {

	// Ritorno l'istanza del segnale di ricerca dell'interazione
	return this->signal_check_interation;
}

}; // Chiudo il namespace di VGE

#endif
