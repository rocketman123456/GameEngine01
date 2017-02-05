/* Copyright (C) Steve Rabin, 2000. 
 * All rights reserved worldwide.
 *
 * This software is provided "as is" without express or implied
 * warranties. You may freely copy and compile this source into
 * applications you distribute provided that the copyright text
 * below is included in the resulting source code, for example:
 * "Portions Copyright (C) Steve Rabin, 2000"
 */


#include "profile.h"
#include "custom_time.h"
#include "../TextBox/TextBox.h"
#include <cassert>
#include <string>
#include <iostream>
#include <stdio.h>

namespace GameEngine {
	namespace Graphics {
		///
		typedef struct {
			bool bValid;							//Whether this data is valid
			unsigned int iProfileInstances;      //# of times ProfileBegin called
			int iOpenProfiles;					//# of times ProfileBegin w/o ProfileEnd
			char szName[256];					//Name of sample
			double fStartTime;					//The current open profile start time
			double fAccumulator;					//All samples this frame added together
			double fChildrenSampleTime;			//Time taken by all children
			unsigned int iNumParents;            //Number of profile parents
		} ProfileSample;

		typedef struct {
			bool bValid;							//Whether the data is valid
			char szName[256];					//Name of the sample
			double fAve;							//Average time per frame (percentage)
			double fMin;							//Minimum time per frame (percentage)
			double fMax;							//Maximum time per frame (percentage)
		} ProfileSampleHistory;

	#define NUM_PROFILE_SAMPLES		100
		static ProfileSample			g_samples[NUM_PROFILE_SAMPLES];
		static ProfileSampleHistory		g_history[NUM_PROFILE_SAMPLES];
		static double						g_startProfile = 0.0;
		static double						g_endProfile = 0.0;
		static TextBox					*textBox = 0;

		void ProfileInit(int boxl, int boxr, int boxu, int boxd) {
			unsigned int i;

			for (i = 0; i < NUM_PROFILE_SAMPLES; i++) {
				g_samples[i].bValid = false;
				g_history[i].bValid = false;
			}

			g_startProfile = GetExactTime();

			textBox = new TextBox(boxl, boxr, boxu, boxd);
			textBox->SetMode(TEXT_NONE);
		}

		void ProfileBegin(char* name) {
			unsigned int i = 0;

			while (i < NUM_PROFILE_SAMPLES && g_samples[i].bValid == true) {
				if (strcmp(g_samples[i].szName, name) == 0) {
					//Found the sample
					g_samples[i].iOpenProfiles++;
					g_samples[i].iProfileInstances++;
					g_samples[i].fStartTime = GetExactTime();
					assert(g_samples[i].iOpenProfiles == 1); //max 1 open at once
					return;
				}
				i++;
			}

			if (i >= NUM_PROFILE_SAMPLES) {
				assert(!"Exceeded Max Available Profile Samples");
				return;
			}

			strcpy(g_samples[i].szName, name);
			g_samples[i].bValid = true;
			g_samples[i].iOpenProfiles = 1;
			g_samples[i].iProfileInstances = 1;
			g_samples[i].fAccumulator = 0.0f;
			g_samples[i].fStartTime = GetExactTime();
			g_samples[i].fChildrenSampleTime = 0.0f;
		}

		void ProfileEnd(char* name) {
			unsigned int i = 0;
			unsigned int numParents = 0;

			while (i < NUM_PROFILE_SAMPLES && g_samples[i].bValid == true) {
				if (strcmp(g_samples[i].szName, name) == 0) {  //Found the sample
					unsigned int inner = 0;
					int parent = -1;
					double fEndTime = GetExactTime();
					g_samples[i].iOpenProfiles--;

					//Count all parents and find the immediate parent
					while (g_samples[inner].bValid == true) {
						if (g_samples[inner].iOpenProfiles > 0) {  //Found a parent (any open profiles are parents)
							numParents++;
							if (parent < 0) {  //Replace invalid parent (index)
								parent = inner;
							}
							else if (g_samples[inner].fStartTime >= g_samples[parent].fStartTime) {  //Replace with more immediate parent
								parent = inner;
							}
						}
						inner++;
					}

					//Remember the current number of parents of the sample
					g_samples[i].iNumParents = numParents;

					if (parent >= 0) {  //Record this time in fChildrenSampleTime (add it in)
						g_samples[parent].fChildrenSampleTime += fEndTime - g_samples[i].fStartTime;
					}

					//Save sample time in accumulator
					g_samples[i].fAccumulator += fEndTime - g_samples[i].fStartTime;
					return;
				}
				i++;
			}
		}

		void ProfileDumpOutputToBuffer(void) {
			unsigned int i = 0;

			g_endProfile = GetExactTime();
			textBox->Clear();

			textBox->Printf("      Ave |       Min |       Max |    # | Profile Name\n");
			textBox->Printf("------------------------------------------------------\n");

			while (i < NUM_PROFILE_SAMPLES && g_samples[i].bValid == true) {
				unsigned int indent = 0;
				double sampleTime, percentTime, aveTime, minTime, maxTime;
				char line[256], name[256], indentedName[256];
				char ave[16], min[16], max[16], num[16];

				if (g_samples[i].iOpenProfiles < 0) {
					assert(!"ProfileEnd() called without a ProfileBegin()");
				}
				else if (g_samples[i].iOpenProfiles > 0) {
					assert(!"ProfileBegin() called without a ProfileEnd()");
				}

				sampleTime = g_samples[i].fAccumulator - g_samples[i].fChildrenSampleTime;
				percentTime = (sampleTime / (g_endProfile - g_startProfile)) * 100.0;

				aveTime = minTime = maxTime = sampleTime;
				//aveTime = minTime = maxTime = percentTime;

				//Add new measurement into the history and get the ave, min, and max
				StoreProfileInHistory(g_samples[i].szName, sampleTime);
				//StoreProfileInHistory(g_samples[i].szName, percentTime);
				GetProfileFromHistory(g_samples[i].szName, &aveTime, &minTime, &maxTime);

				//Format the data
				sprintf(ave, "%5.3f", aveTime);
				sprintf(min, "%5.3f", minTime);
				sprintf(max, "%5.3f", maxTime);
				sprintf(num, "%4d", g_samples[i].iProfileInstances);

				strcpy(indentedName, g_samples[i].szName);
				for (indent = 0; indent < g_samples[i].iNumParents; indent++) {
					sprintf(name, "   %s", indentedName);
					strcpy(indentedName, name);
				}

				sprintf(line, "%9s | %9s | %9s | %4s | %s\n", ave, min, max, num, indentedName);
				textBox->Printf(line);	//Send the line to text buffer
				i++;
			}

			{  //Reset samples for next frame
				unsigned int i;
				for (i = 0; i < NUM_PROFILE_SAMPLES; i++) {
					g_samples[i].bValid = false;
				}
				g_startProfile = GetExactTime();
			}
		}

		void StoreProfileInHistory(char* name, double percent) {
			unsigned int i = 0;
			double oldRatio;
			double newRatio = 0.8 * GetElapsedTime();
			if (newRatio > 1.0) {
				newRatio = 1.0;
			}
			oldRatio = 1.0f - newRatio;

			while (i < NUM_PROFILE_SAMPLES && g_history[i].bValid == true) {
				if (strcmp(g_history[i].szName, name) == 0) {  //Found the sample
					g_history[i].fAve = (g_history[i].fAve*oldRatio) + (percent*newRatio);
					if (percent < g_history[i].fMin) {
						g_history[i].fMin = percent;
					}
					else {
						g_history[i].fMin = (g_history[i].fMin*oldRatio) + (percent*newRatio);
					}

					if (g_history[i].fMin < 0.0) {
						g_history[i].fMin = 0.0;
					}


					if (percent > g_history[i].fMax) {
						g_history[i].fMax = percent;
					}
					else {
						g_history[i].fMax = (g_history[i].fMax*oldRatio) + (percent*newRatio);
					}
					return;
				}
				i++;
			}

			if (i < NUM_PROFILE_SAMPLES) {  //Add to history
				strcpy(g_history[i].szName, name);
				g_history[i].bValid = true;
				g_history[i].fAve = g_history[i].fMin = g_history[i].fMax = percent;
			}
			else {
				assert(!"Exceeded Max Available Profile Samples!");
			}
		}

		void GetProfileFromHistory(char* name, double* ave, double* min, double* max) {
			unsigned int i = 0;
			while (i < NUM_PROFILE_SAMPLES && g_history[i].bValid == true) {
				if (strcmp(g_history[i].szName, name) == 0) {  //Found the sample
					*ave = g_history[i].fAve;
					*min = g_history[i].fMin;
					*max = g_history[i].fMax;
					return;
				}
				i++;
			}
			*ave = *min = *max = 0.0;
		}

		void ProfileDraw(void) {
			if (textBox) {
				//textBox->Printf( "Yippee Yahoo!!!\n" );
				textBox->Draw();
			}
		}
		///
	}
}
