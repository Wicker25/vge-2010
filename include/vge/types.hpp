/* 
    Title --- types.hpp

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


#ifndef TYPES_H
#define TYPES_H

#include <string>
#include <cwchar>
#include <list>
#include <vector>
#include <stdint.h>

#include <SDL/SDL_byteorder.h>
#include <SDL/SDL_types.h>

#if SDL_BYTEORDER == SDL_BIG_ENDIAN

	#define SWAP16(X)	(X)
	#define SWAP32(X)	(X)
#else
	#define SWAP16(X)	SDL_Swap16(X)
	#define SWAP32(X)	SDL_Swap32(X)
#endif

namespace VGE { // Namespace di VGE

namespace Types { // Namespace dei tipi

// Ridefinizione dei tipi base
typedef int8_t Int8;
typedef int16_t Int16;
typedef int32_t Int32;
typedef int Int;

typedef uint8_t Uint8;
typedef uint16_t Uint16;
typedef uint32_t Uint32;
typedef unsigned int Uint;

typedef float Float;
typedef double Double;
typedef bool Bool;

// Prototipi
struct Point3D;

// Un punto nel piano bidimensionale
struct Point2D {

	Float x, y;	// Coordinate

	// Costruttori
	Point2D() { x = 0.0f; y = 0.0f; }
	Point2D( Float x_, Float y_ ) { x = x_; y = y_; }
	Point2D( const Point2D &other ) { x = other.x; y = other.y; }

	// Costruttori di copia
	Point2D( const Point3D &point );

	// Translazione del punto
	Point2D Translate( const Point2D &point_ ) const {

		return Point2D( x + point_.x, y + point_.y );
	}

	// Inverte le coordinate del punto
	Point2D Invert() const {

		return Point2D( -x, -y );
	}
};

// Operatore di somma
inline Point2D
operator+ ( const Point2D &first, const Point2D &second ) {

    return Point2D( first.x + second.x, first.y + second.y );
}

// Operatore di sottrazione
inline Point2D
operator- ( const Point2D &first, const Point2D &second ) {

    return Point2D( first.x - second.x, first.y - second.y );
}

// Operatore di moltiplicazione
inline Point2D
operator* ( const Point2D &first, const Point2D &second ) {

    return Point2D( first.x * second.x, first.y * second.y );
}

// Operatore di divisione
inline Point2D
operator/ ( const Point2D &first, const Point2D &second ) {

    return Point2D( first.x / second.x, first.y / second.y );
}

// Arrotonda le coordinate di un punto
inline Point2D
Ceil( const Point2D &point ) {

    return Point2D( std::ceil( point.x ), std::ceil( point.y ) );
}

// Arrotonda le coordinate di un punto
inline Point2D
Floor( const Point2D &point ) {

    return Point2D( std::floor( point.x ), std::floor( point.y ) );
}

// Ridefinizione dei tipo lista
typedef std::vector< Point2D > Point2DList;


/**** Punto nel piano tridimensionale ****/

struct Point3D {

	Float x, y, z;	// Coordinate

	// Costruttori
	Point3D() { x = 0.0f; y = 0.0f; z = 0.0f; }
	Point3D( Float x_, Float y_ ) { x = x_; y = y_; z = 0.0f; }
	Point3D( Float x_, Float y_, Float z_ ) { x = x_; y = y_; z = z_; }
	Point3D( const Point3D &other ) { x = other.x; y = other.y; z = other.z; }

	// Costruttori di copia
	Point3D( const Point2D &point ) { x = point.x; y = point.y; z = 0.0f; }

	// Translazione del punto
	Point3D Translate( const Point3D &point_ ) const {

		return Point3D( x + point_.x, y + point_.y, z + point_.z );
	}

	// Inverte le coordinate del punto
	Point3D Invert() const {

		return Point3D( -x, -y, -z );
	}
};

// Costruttore di copia nel punto del piano
inline Point2D::Point2D( const Point3D &point ) { x = point.x; y = point.y; }

// Distanza tra due punti
inline Float
PointDistance( const Point3D &first, const Point3D &second ) {

	return sqrt( pow( first.x - second.x, 2.0f ) + pow( first.y - second.y, 2.0f ) );
}

// Ridefinizione dei tipo lista
typedef std::vector< Point3D > Point3DList;



/**** Dimensione bidimensionale ****/

template< typename Type >
struct Size2D {

	// Elementi
	union { Type w, x, a; };
	union { Type h, y, b; };

	// Costruttori
	Size2D() { w = 0; h = 0; }
	Size2D( Type w_, Type h_ ) { w = w_; h = h_; }
	Size2D( const Size2D &other ) { w = other.w; h = other.h; }

	// Costruttori di copia
	template< typename Type_b >
	Size2D( const Size2D< Type_b > &other ) { w = (Type) other.w; h = (Type) other.h; }

	// Operatore di moltiplicazione
	Size2D< Type > &operator *= ( const Size2D< Type > &other ) {

		// Moltiplico gli elementi
		w *= other.w;
		h *= other.h;

	    return *this;
	}

	// Operatore di divisione
	Size2D< Type > &operator /= ( const Size2D< Type > &other ) {

		// Moltiplico gli elementi
		w /= other.w;
		h /= other.h;

	    return *this;
	}
};

// Operatore di addizione
template< typename Type >
Size2D< Type > operator+ ( const Size2D< Type > &first, const Size2D< Type > &second ) {

    return Size2D< Type >( first.w + second.w, first.h + second.h );
}

// Operatore di sottrazione
template< typename Type >
Size2D< Type > operator- ( const Size2D< Type > &first, const Size2D< Type > &second ) {

    return Size2D< Type >( first.w - second.w, first.h - second.h );
}

// Operatore di moltiplicazione
template< typename Type >
Size2D< Type > operator* ( const Size2D< Type > &first, const Size2D< Type > &second ) {

    return Size2D< Type >( first.w * second.w, first.h * second.h );
}

// Operatore di divisione
template< typename Type >
Size2D< Type > operator/ ( const Size2D< Type > &first, const Size2D< Type > &second ) {

    return Size2D< Type >( first.w / second.w, first.h / second.h );
}

// Alias del tipo
typedef Size2D< Types::Int > Size2D_i;
typedef Size2D< Types::Uint > Size2D_u;
typedef Size2D< Types::Float > Size2D_f;

/**** Area rettangolare ****/

template< typename Type >
struct Rect {

	Type left;		// Lato sinistro
	Type top;		// Lato superiore

	union { Type right, width; };		// Lato destro o larghezza
	union { Type bottom, height; };	// Lato inferiore o altezza

	// Costruttori
	Rect() { left = 0; top = 0; right = 0; bottom = 0; }

	Rect( Type left_, Type top_, Type right_, Type bottom_ ) {

		left	= left_;
		top		= top_;
		right	= right_;
		bottom	= bottom_;
	}

	template< typename Type_b >
	Rect( Types::Point2D position, Types::Size2D< Type_b > size ) {

		left	= position.x;
		top		= position.y;
		right	= position.x + size.w;
		bottom	= position.y + size.h;
	}

	// Costruttori di copia
	template< typename Type_b >
	Rect( const Rect< Type_b > &other ) {

		left	= (Type) other.left;
		top		= (Type) other.top;
		right	= (Type) other.right;
		bottom	= (Type) other.bottom;
	}

	// Restituisce l'intersezione con un altro rettangolo
	template< typename Type_b >
	Rect< Type > Sub( const Rect< Type_b > &other ) const {

		return Rect< Type_b > (

			( other.left > left ) ? other.left : left,
			( other.top > top ) ? other.top : top,
			( other.right < right ) ? other.right : right,
			( other.bottom < bottom ) ? other.bottom : bottom
		);
	}
};

// Alias del tipo
typedef Rect< Types::Int > Rect_i;
typedef Rect< Types::Uint > Rect_u;
typedef Rect< Types::Float > Rect_f;


/**** Conversioni tra stringhe ****/

// Converte una stringa nel formato wide-char
inline std::wstring
StringToWide( const std::string &str ) {

	return std::wstring( str.begin(), str.end() );
}

// Converte una stringa dal formato wide-char
inline std::string
WideToString( const std::wstring &str ) {

	return std::string( str.begin(), str.end() );
}

}; // Chiudo il namespace dei tipi

}; // Chiudo il namespace di VGE

#endif
