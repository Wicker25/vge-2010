/* 
    Title --- math.hpp

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


#ifndef MATH_HPP
#define MATH_HPP

#include <cmath>

#define VMAX(a,b)		((a > b) ? a : b)
#define VMIN(a,b)		((a < b) ? a : b)
#define VCMP(a,b)		((a == b) ? 0 : ( (a > b) ? 1 : -1 ))
#define VABS(x)			((x > 0) ? x : -x)
#define VABS_DIFF(a,b)	((a > b) ? (a - b) : (b - a))
#define VTORAD(x)		(x * M_PI / 180.0)
#define VTODEGREES(x)	(x * 180.0 / M_PI)
#define VROUND(a,b)		(round(a* pow(10,b)) / pow(10,b))

#endif
