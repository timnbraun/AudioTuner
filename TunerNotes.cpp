/* Audio Library Note Frequency Detection & Guitar/Bass Tuner
 *
 * TunerNotes.cpp
 *
 * AudioTuner helper structs and class to get human friendly output
 *
 * This currently assumes A = 440 Hz tuning, and equal-tempered notes.
 * The note centre frequencies are defined in a const arrary in this file.
 *
 * Copyright (c) 2025, Tim Braun
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice, development funding notice, and this permission
 * notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <Arduino.h>
#include <cstdint>
#include <string>

#include "TunerNotes.h"

const DefinedNote Notes::theNotes[9][12] = {
 // 0
 { { C, "C", 16.35 }, { Csharp, "C#", 17.32 }, { D, "D", 18.35 }, { Eflat, "Eb", 19.45 },
 { E, "E", 20.6 }, { F, "F", 21.83 }, { Fsharp, "F#", 23.12 }, { G, "G", 24.5 },
 { Gsharp, "G#", 25.96 }, { A, "A", 27.5 }, { Bflat, "Bb", 29.14 }, { B, "B", 30.87 } },

 // 1
 { { C, "C", 32.7 }, { Csharp, "C#", 34.65 }, { D, "D", 36.71 }, { Eflat, "Eb", 38.89 },
 { E, "E", 41.2 }, { F, "F", 43.65 }, { Fsharp, "F#", 46.25 }, { G, "G", 49.0 },
 { Gsharp, "G#", 51.91 }, { A, "A", 55.0 }, { Bflat, "Bb", 58.27 }, { B, "B", 61.74 } },

 // 2
 { { C, "C", 65.41 }, { Csharp, "C#", 69.3 }, { D, "D", 73.42 }, { Eflat, "Eb", 77.78 },
 { E, "E", 82.41 }, { F, "F", 87.31 }, { Fsharp, "F#", 92.5 }, { G, "G", 98.0 },
 { Gsharp, "G#", 103.83 }, { A, "A", 110.0 }, { Bflat, "Bb", 116.54 }, { B, "B", 123.47 } },

 // 3
 { { C, "C", 130.81 }, { Csharp, "C#", 138.59 }, { D, "D", 146.83 }, { Eflat, "Eb", 155.56 },
 { E, "E", 164.81 }, { F, "F", 174.61 }, { Fsharp, "F#", 185.0 }, { G, "G", 196.0 },
 { Gsharp, "G#", 207.65 }, { A, "A", 220.0 }, { Bflat, "Bb", 233.08 }, { B, "B", 246.94 } },

 // 4
 { { C, "C", 261.63 }, { Csharp, "C#", 277.18 }, { D, "D", 293.66 }, { Eflat, "Eb", 311.13 },
 { E, "E", 329.63 }, { F, "F", 349.23 }, { Fsharp, "F#", 369.99 }, { G, "G", 392.0 },
 { Gsharp, "G#", 415.3 }, { A, "A", 440.0 }, { Bflat, "Bb", 466.16 }, { B, "B", 493.88 } },

 // 5
 { { C, "C", 523.25 }, { Csharp, "C#", 554.37 }, { D, "D", 587.33 }, { Eflat, "Eb", 622.25 },
 { E, "E", 659.26 }, { F, "F", 698.46 }, { Fsharp, "F#", 739.99 }, { G, "G", 783.99 },
 { Gsharp, "G#", 830.61 }, { A, "A", 880.0 }, { Bflat, "Bb", 932.33 }, { B, "B", 987.77 } },

 // 6
 { { C, "C", 1046.5 }, { Csharp, "C#", 1108.73 }, { D, "D", 1174.66 }, { Eflat, "Eb", 1244.51 },
 { E, "E", 1318.51 }, { F, "F", 1396.91 }, { Fsharp, "F#", 1479.98 }, { G, "G", 1567.98 },
 { Gsharp, "G#", 1661.22 }, { A, "A", 1760.0 }, { Bflat, "Bb", 1864.66 }, { B, "B", 1975.53 } },

 // 7
 { { C, "C", 2093.0 }, { Csharp, "C#", 2217.46 }, { D, "D", 2349.32 }, { Eflat, "Eb", 2489.02 },
 { E, "E", 2637.02 }, { F, "F", 2793.83 }, { Fsharp, "F#", 2959.96 }, { G, "G", 3135.96 },
 { Gsharp, "G#", 3322.44 }, { A, "A", 3520.0 }, { Bflat, "Bb", 3729.31 }, { B, "B", 3951.07 } },

 // 8
 { { C, "C", 4186.01 }, { Csharp, "C#", 4434.92 }, { D, "D", 4698.64 }, { Eflat, "Eb", 4978.03 },
 { E, "E", 5274.04 }, { F, "F", 5587.65 }, { Fsharp, "F#", 5919.91 }, { G, "G", 6271.93 },
 { Gsharp, "G#", 6644.88 }, { A, "A", 7040.0 }, { Bflat, "Bb", 7458.62 }, { B, "B", 7902.13 } }

};

Notes::Notes()
{
}


///
//  Notes::Note()
// 
//  Note returns a measured note result which
//  is a static struct. Be sure to either
//  copy the output before calling again, 
//  or otherwise be done with the results,
//  they will get over-written on each call.
//
//  A binary search of the note table is done to find the
//  nearest note for the frequency input.
///
const MeasuredNote Notes::Note(float freq)
{
	int closest_index;
	const DefinedNote *searching;

	// Safety limits
	if (freq < 0.1)
		freq = 0.1;
	else if (freq > 10000.0)
		freq = 10000.0;

	if (freq > theNotes[8][11].pitch) {
		closest_index = 8*12 + 11;
		searching = &theNotes[8][11];
	}
	else if (freq < theNotes[0][0].pitch) {
		closest_index = 0;
		searching = &theNotes[0][0];
	}
	else {
		// Find nearest pitch with binary search
		closest_index = 64;
		searching = &theNotes[closest_index/12][closest_index % 12];
		for (int i = 32; i > 0; i >>= 1) {
			if (freq > searching->pitch) {
				if (freq < (searching + 1)->pitch) {
					// found it!
					break;
				}
				// Serial.printf("Higher than % 4.2f\n", searching->pitch);
				closest_index += i;
				searching += i;
			}
			else if (freq < searching->pitch) {
				closest_index -= i;
				searching -= i;
			}
		}
	}

	// We have to decide if the closest pitch is higher or lower than our target
    float centsSharp = 1200.0f * log( freq / searching->pitch ) / log( 2.0 );
	if (centsSharp > 50.0 && closest_index < (8*12 + 11)) {
		searching++;
		closest_index++;
    	centsSharp = 1200.0f * log( freq / searching->pitch ) / log( 2.0 );
	}

	// Serial.printf("Searching for % 4.2f, found pitch % 4.2f at %u\n", 
	// 	freq, searching->pitch, closest_index);

	static MeasuredNote answer;
	answer.name = searching->nameString;
	answer.octave = closest_index / 12;
	answer.measuredPitch = freq;
	answer.definedPitch = searching->pitch;
	answer.centsSharp = int( centsSharp + 0.5f );
	return answer;
}
