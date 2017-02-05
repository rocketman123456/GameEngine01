/* Copyright (C) Steve Rabin, 2000. 
 * All rights reserved worldwide.
 *
 * This software is provided "as is" without express or implied
 * warranties. You may freely copy and compile this source into
 * applications you distribute provided that the copyright text
 * below is included in the resulting source code, for example:
 * "Portions Copyright (C) Steve Rabin, 2000"
 */

#ifndef _PROFILE_H
#define _PROFILE_H

namespace GameEngine {
	namespace Graphics {

		void ProfileInit(int boxl = 0, int boxr = 640, int boxu = 0, int boxd = 480);
		void ProfileBegin(char* name);
		void ProfileEnd(char* name);
		void ProfileDumpOutputToBuffer(void);
		void StoreProfileInHistory(char* name, double percent);
		void GetProfileFromHistory(char* name, double* ave, double* min, double* max);
		void ProfileDraw(void);

	}
}

#endif
