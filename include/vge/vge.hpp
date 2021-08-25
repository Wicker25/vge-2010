/* 
    Title --- vge.hpp

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


#ifndef VGE_HPP
#define VGE_HPP

#include "vge/consts.hpp"
#include "vge/types.hpp"
#include "vge/math.hpp"

#include "vge/xml.hpp"
#include "vge/inline/xml-inl.hpp"

#include "vge/designer.hpp"
#include "vge/inline/designer-inl.hpp"

#include "vge/input-manager.hpp"
#include "vge/inline/input-manager-inl.hpp"

#include "vge/color.hpp"
#include "vge/inline/color-inl.hpp"

#include "vge/bounding-area.hpp"
#include "vge/inline/bounding-area-inl.hpp"

// =================== INTERFACCE ====================

#include "vge/interfaces/i-ruotable.hpp"
#include "vge/interfaces/inline/i-ruotable-inl.hpp"

#include "vge/interfaces/i-scalable.hpp"
#include "vge/interfaces/inline/i-scalable-inl.hpp"

#include "vge/interfaces/i-colorable.hpp"
#include "vge/interfaces/inline/i-colorable-inl.hpp"

#include "vge/interfaces/i-image.hpp"
#include "vge/interfaces/inline/i-image-inl.hpp"

#include "vge/interfaces/i-clickable.hpp"
#include "vge/interfaces/inline/i-clickable-inl.hpp"

#include "vge/interfaces/i-programmable.hpp"
#include "vge/interfaces/inline/i-programmable-inl.hpp"

#include "vge/interfaces/i-orientable.hpp"
#include "vge/interfaces/inline/i-orientable-inl.hpp"

#include "vge/interfaces/i-margins.hpp"
#include "vge/interfaces/inline/i-margins-inl.hpp"

#include "vge/interfaces/i-range.hpp"
#include "vge/interfaces/inline/i-range-inl.hpp"

// =================== ENTITA' ====================

#include "vge/entity.hpp"
#include "vge/inline/entity-inl.hpp"

#include "vge/image.hpp"
#include "vge/inline/image-inl.hpp"

#include "vge/sprite.hpp"
#include "vge/inline/sprite-inl.hpp"

#include "vge/object.hpp"
#include "vge/inline/object-inl.hpp"

#include "vge/character.hpp"
#include "vge/inline/character-inl.hpp"

#include "vge/player.hpp"
#include "vge/inline/player-inl.hpp"

#include "vge/particle-system.hpp"
#include "vge/inline/particle-system-inl.hpp"

#include "vge/maker.hpp"
#include "vge/inline/maker-inl.hpp"

#include "vge/scene.hpp"
#include "vge/inline/scene-inl.hpp"

#include "vge/viewer.hpp"
#include "vge/inline/viewer-inl.hpp"

#include "vge/mixer.hpp"
#include "vge/inline/mixer-inl.hpp"

#include "vge/engine.hpp"
#include "vge/inline/engine-inl.hpp"

// =================== GUI ====================

#include "vge/widgets/widget.hpp"
#include "vge/widgets/inline/widget-inl.hpp"

#include "vge/widgets/container.hpp"
#include "vge/widgets/inline/container-inl.hpp"

#include "vge/widgets/window.hpp"
#include "vge/widgets/inline/window-inl.hpp"

#include "vge/widgets/font.hpp"
#include "vge/widgets/inline/font-inl.hpp"

#include "vge/widgets/label.hpp"
#include "vge/widgets/inline/label-inl.hpp"

#include "vge/widgets/text-entry.hpp"
#include "vge/widgets/inline/text-entry-inl.hpp"

#include "vge/widgets/text-box.hpp"
#include "vge/widgets/inline/text-box-inl.hpp"

#include "vge/widgets/button.hpp"
#include "vge/widgets/inline/button-inl.hpp"

#include "vge/widgets/text-button.hpp"
#include "vge/widgets/inline/text-button-inl.hpp"

#include "vge/widgets/image-button.hpp"
#include "vge/widgets/inline/image-button-inl.hpp"

#include "vge/widgets/slider.hpp"
#include "vge/widgets/inline/slider-inl.hpp"

#include "vge/widgets/message-box.hpp"
#include "vge/widgets/inline/message-box-inl.hpp"

#include "vge/widgets/progress-bar.hpp"
#include "vge/widgets/inline/progress-bar-inl.hpp"

#endif
