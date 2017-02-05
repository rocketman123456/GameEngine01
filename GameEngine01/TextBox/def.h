/* Copyright (C) Dante Treglia II, 2000. 
 * All rights reserved worldwide.
 *
 * This software is provided "as is" without express or implied
 * warranties. You may freely copy and compile this source into
 * applications you distribute provided that the copyright text
 * below is included in the resulting source code, for example:
 * "Portions Copyright (C) Dante Treglia II, 2000"
 */

#ifndef _DEF_H
#define _DEF_H

namespace GameEngine {
	namespace Graphics {
		/////////////////////////////////////////////////////////////////////////

		typedef char				s8;
		typedef unsigned char		u8;
		typedef float				f32;
		typedef double				f64;

		typedef __int8				i8;
		typedef __int16				i16;
		typedef __int32				i32;
		typedef __int64				i64;
		//typedef unsigned __int8		u8;
		typedef unsigned __int16	u16;
		typedef unsigned __int32	u32;
		typedef unsigned __int64	u64;

		typedef struct { u8 r, g, b, a; } COLOR;

	#define MALLOC malloc

	#define SET_COLOR(c, rIn, gIn, bIn, aIn) \
	c.r = rIn; \
	c.g = gIn; \
	c.b = bIn; \
	c.a = aIn

		///////////////////////////////////////////////////////////////////////
	}
}

#endif
