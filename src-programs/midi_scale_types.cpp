#include <iostream>

#include "midi_scale_types.h"
#include "midi_misc.h"


/* MODES */
const char Scale_type::ionian[16] 		= { 0,2,4,5,7,9,11,12,14,16,17,19,21,23,24,26 };
const char Scale_type::dorian[16]		= { 0,2,4,5,7,9,11,12,14,16,17,19,21,23,24,26 };
const char Scale_type::phrygian[16]		= { 0,2,4,5,7,9,11,12,14,16,17,19,21,23,24,26 };
const char Scale_type::lydian[16] 		= { 0,2,4,5,7,9,11,12,14,16,17,19,21,23,24,26 };
const char Scale_type::mixolydian[16]		= { 0,2,4,5,7,9,11,12,14,16,17,19,21,23,24,26 };
const char Scale_type::aeolian[16]		= { 0,2,4,5,7,9,11,12,14,16,17,19,21,23,24,26 };
const char Scale_type::locrian[16]		= { 0,2,4,5,7,9,11,12,14,16,17,19,21,23,24,26 };
/* end-MODES */

void MIDI_Scale::set_scale(int key, const char *scale_type, int num_voices, char *new_scale) {
	for (int i=0; i<num_voices; i++) {
		new_scale[i] = scale_type[i] + key;
		// new_scale[i] = 'x';
	}
	for (int i=num_voices; i<16; i++) {
		new_scale[i] = 128;
	}
}

int MIDI_Scale::note_octave(int note) {
	return 1;
}

void MIDI_Scale::scale_octave(int *dest, int num_voices) {

}

void MIDI_Scale::rand_rests(char *dest, int num_voices) {
	if (num_voices == 0) { return; }
	int z = random_int(1,2);
	// std::cout << z << " ";
	if (z == 1) { *dest = 128; }
	rand_rests(dest+1, num_voices-1);
}