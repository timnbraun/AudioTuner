/* Audio Library Note Frequency Detection & Guitar/Bass Tuner
 *
 * TunerNotes.h
 *
 * AudioTuner helper structs and class to get human friendly output
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

#pragma once

#include <cstdint>
#include <string>

//
// maybe we don't need an enum
typedef enum eNoteName {
	A, Bflat, B, C, Csharp, D, Eflat, E, F, Fsharp, G, Gsharp
} eNoteName;

typedef struct {
	eNoteName name;
	String nameString;
	float pitch;
} DefinedNote;

typedef struct {
	String		name;	// e.g. Asharp
	uint32_t	octave;	// e.g. 2
	float		measuredPitch;
	float		definedPitch;
	int32_t		centsSharp;
} MeasuredNote;


class Notes {
	public:
		Notes();
		static const MeasuredNote Note(float freq);
	private:
		static const DefinedNote theNotes[9][12];
};
