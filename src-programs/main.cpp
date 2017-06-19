/* Author:		Ruslan Pantaev <arpiseaQ>
 * License:		MIT License
 * Start_Date:		6/4/2017
 * Last_modified:	6/19/2017
 */

#include <iostream>
#include <string>
#include <cstdio>		// For std::fopen(), std::fwrite(), std::fclose()
#include <boost/filesystem.hpp>	// For creating folders/dir arpiseaQ_6/5/2017_20:51
#include <vector>
#include <unordered_map>	// implementing hashmap for chords arpiseaQ_6/7/2017_10:29

#include "midi_chord_types.h"	// Chord definitions & methods arpiseaQ_6/5/2017_20:43
#include "midi_scale_types.h"	// Scale definitions arpiseaQ_6/6/2017_05:26
#include "midi_gen_bisqwit.h"	// Put midi classes in a sep file arpiseaQ_6/7/2017_13:22
#include "midi_misc.h"		// For random_int boost function arpiseaQ_6/17/2017_11:43

using namespace std;


int main() {
	/* -------------------------------------------------------------------------------------------------
	 * start-Implementation example of MIDI_Chord class
 	 * -------------------------------------------------------------------------------------------------
	 */

	MIDI_Chord ch;

	/* Example of how to explicitly populate vector of chords to be used */
	// ch.add_chord(note::E, "maj7");
	// ch.add_chord(note::Gb, "min7");
	// ch.add_chord(note::Db, "min9");
	// ch.add_chord(note::Ab, "min9");
	// ch.add_chord(note::A, "sus4_add_9");
	// ch.add_chord(note::B, "dom7");
	// ch.add_chord(note::D, "dim");
	// ch.add_chord(note::E+note::oct_up, "maj11");

	/* Or random chords with user-specified Key */
	/* add_rand_chord(int key) is also overloaded without any key parameter */
	for (int i=0; i<8; ++i) {
		ch.add_rand_chord(key::C);
	}

	/* Print chords to terminal */
	ch.print_chords();

	ch.inversion(0, 1);
	ch.inversion(1, 2);
	ch.inversion(2, 2);
	ch.inversion(3, 1);
	ch.inversion(4, 1);
	ch.inversion(5, 1);
	ch.inversion(6, 1);
	ch.inversion(7, 2);

	for (int i=0; i<8; ++i) {
		ch.oct_up(i);
	}

	/* -------------------------------------------------------------------------------------------------
	 * end-Implementation example of MIDI_Chord class
 	 * -------------------------------------------------------------------------------------------------
	 */

	/* -------------------------------------------------------------------------------------------------
	 * start-Implementation example of MIDI_Scale class
 	 * -------------------------------------------------------------------------------------------------
	 */

	// MIDI_Scale scl_obj;

	// char chordline[64] = {
	//     0,x,1,2,x,3,x, 4,x,5,x,6,8,x,8,x,  8,x,6,8,x,10,x, 10,x,11,x,6,3,x,5,x,
	//     4,x,3,2,x,1,x, 0,x,5,x,6,8,x,8,x,  6,7,6,x,8,x,9,x,10,9,8,7,6,5,4,3
	// };

	// scl_obj.set_scale(note::D, scl_obj.scl.dorian, 16, &chordline[0]);
	// scl_obj.set_scale(note::D, scl_obj.scl.dorian, 16, &chordline[16]);
	// scl_obj.set_scale(note::A, scl_obj.scl.dorian, 16, &chordline[32]);
	// scl_obj.set_scale(note::D, scl_obj.scl.dorian, 16, &chordline[48]);

	// // cout << "BEFORE: \n";
	// // for (int i=0; i<64; i++) {
	// //     chordline[i] = 'x';
	// // }

	// scl_obj.rand_rests(chordline, 64);

	// cout << "AFTER: \n";
	// for (int i=0; i<64; i++) {
	//     cout << chordline[i] << endl;
	// }

	/* -------------------------------------------------------------------------------------------------
	 * end-Implementation example of MIDI_Scale class
 	 * -------------------------------------------------------------------------------------------------
	 */

 	/* -------------------------------------------------------------------------------------------------
	 * start-Define instrument rhythyms
 	 * -------------------------------------------------------------------------------------------------
	 */

	/* TODO should these be const static?
	 * Maybe it'll be better to be be able to wipe these
	 * Assign chordlines and melodies using set_scale(key, vector<char> scale_type)
	 * edit arpiseaQ_6/5/2017_13:21
	 * edit arpiseaQ_6/19/2017_09:25 (Italy timezone)
	 */

	const char x = 128;		// Value to specify "no note" --> 128 for note-off (preprocessor definition emitted err)

	static const char chordline[64] =
	{
		0,1,2,3,4,5,6,7, 1,x,x,x,x,x,x,x,  2,x,x,x,x,x,x,x, 3,x,x,x,x,x,x,x,
		4,x,x,x,x,x,x,x, 5,x,x,x,4,5,x,x,  6,x,x,x,1,x,2,x, 7,x,x,x,x,3,7,3,
	};

	static const char bassline[64] =
	{
		note::C,x,x,x,x,x,x,x,
		note::A,x,x,x,x,x,x,x,
		x,x,note::D,x,x,x,x,x,
		note::G,x,x,x,note::D,x,note::G,x,
		note::C,x,x,x,x,x,x,x,
		note::A,x,x,x,x,x,x,x,
		x,x,note::F,x,note::E,x,note::D,x,
		note::C,note::D,note::F,note::A,note::G,note::B,note::A,note::C+note::oct_up
	};

	static const char fluteline[64] =
	{
		note::C,note::D,note::F,note::A,note::G,note::B,note::A,note::C+note::oct_up,
		note::C,note::D,note::F,note::A,note::G,note::B,note::A,note::C+note::oct_up,
		note::C,note::D,note::F,note::A,note::G,note::B,note::A,note::C+note::oct_up,
		note::C,note::D,note::F,note::A,note::G,note::B,note::A,note::C+note::oct_up,
		note::C,note::D,note::F,note::A,note::G,note::B,note::A,note::C+note::oct_up,
		note::C,note::D,note::F,note::A,note::G,note::B,note::A,note::C+note::oct_up,
		note::C,note::D,note::F,note::A,note::G,note::B,note::A,note::C+note::oct_up,
		note::C,note::D,note::F,note::A,note::G,note::B,note::A,note::C+note::oct_up
	};

	/* -------------------------------------------------------------------------------------------------
	 * end-Define instrument rhythyms
 	 * -------------------------------------------------------------------------------------------------
	 */

	/* -------------------------------------------------------------------------------------------------
	 * start-Generate .mid file
	 * -------------------------------------------------------------------------------------------------
	 *
	 * TODO put below into functions, with following user defined parameters:
	 * 	patches (make commented list of corresponding instruments for ease of use)
	 *	tempo
	 * 	num repeats / loops
	 *	length of each measure (how will I handle odd time; how should I represent time signatures?)
	 * 	chordline rhythmic patterns to be used (vector<int> or vector<char> ?)
	 *		% (mod) value based on chordline.size()
	 *	create randomize velocities function? (within specified range)
	 */

	MIDIfile file;
	file.set_tempo(1200000);						// TODO convert to readable BPM format
	file.AddLoopStart();

	/* Choose instruments ("patches") for each channel: */
	static const char patches[16] =
	{
		0,0,0, 52,52,52, 48,48,48, 0,0,0,0,0, 35,74
	/* 0=piano, 52=choir aahs, 48=strings, 35=fretless bass, 74=pan flute */
	};

	for (unsigned c=0; c<16; ++c) {
		if (c != 10) {							// Patch any other channel but not the percussion channel.
			file[0].Patch(c, patches[c]);
		}
	}

	int keys_on[16] = { -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1 };

	for (unsigned loops=0; loops<4; ++loops) {				// SET num REPEATS here
		for (unsigned row=0; row<128; ++row) {				// SET length of each measure
			for(unsigned c=0; c<16; ++c) {				// 16 for patches, c stands for CHANNEL
				int note 	= x;					// Arbitrary value to specify "no note" --> 128 for note-off
				int add 	= 0;
				int vol 	= 127;

				if (c < 3) {					// Piano chord
					int chord = chordline[row%64];
					if (chord != x) {
						note = ch.return_chord(chord)[c%3];
						add=12*5;
						vol=0x4B; 			// equivalent to 75
					}
				} else if (c >= 3 && c < 5) {			// Aux chord (choir)
					int chord = chordline[row%64];
					if (chord != x) {
						note = ch.return_chord(chord)[c%3];
						add=12*4;
						vol=0x50;
					}
				}
				else if(c >= 6 && c < 8) {			// Aux chord (strings)
					int chord = chordline[row%64];
					if(chord != x) {
						note = ch.return_chord(chord)[c%3];
						add=12*5;
						vol=0x45;
					}
				}
				else if (c == 14) {				// Bass
					note = bassline[row%64];
					add=12*3;
					vol=122;
				}
				else if (c == 15 && row >= 64) {		// Flute
					note = fluteline[row%64];
					add=12*5;
					vol=0x6F;
				}
				if (note == x && (c<15 || row%31)) {
					continue;
				}
				file[0].KeyOff(c, keys_on[c], 0x20);
				keys_on[c] = -1;
				if (note == x) {
					continue;
				}
				file[0].KeyOn(c, keys_on[c] = note+add, vol);	// channel, note number, pressure
			}
			file[0].AddDelay(500);					// val 500 fixes tempo to be playable/locked in at 120bpm
		}
		if (loops == 0) {
			file.AddLoopEnd();
		}
		/* TODO add delay at EOF or add fade_out() function */
	}

	file.Finish();

	/* -------------------------------------------------------------------------------------------------
	 * end-Generate .mid file
	 * -------------------------------------------------------------------------------------------------
	 */

	/* -------------------------------------------------------------------------------------------------
	 * start-Create / check Dir & output .mid file
 	 * -------------------------------------------------------------------------------------------------
	 */

	if (!boost::filesystem::exists("../midi_files")) {
		boost::filesystem::create_directories("../midi_files");
	}
	int file_num = 0;
	string filename = ("untitled_" + to_string(file_num) + ".mid").c_str();
	while (boost::filesystem::exists( ("../midi_files/"+filename).c_str()) ) {
		file_num++;
		filename = ("untitled_" + to_string(file_num) + ".mid").c_str();
	}

	FILE* outfile = fopen( ("../midi_files/"+filename).c_str(), "wb");
	fwrite(&file.at(0), 1, file.size(), outfile);
	fclose(outfile); 

	cout << "untitled.mid file created successfully \n";

	/* -------------------------------------------------------------------------------------------------
	 * end-Create / check Dir & output .mid file
 	 * -------------------------------------------------------------------------------------------------
	 */

	return 0;
}