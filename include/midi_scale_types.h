#ifndef MIDI_SCALE_TYPES_H
#define MIDI_SCALE_TYPES_H

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/variate_generator.hpp>


struct Scale_type {
	/* MODES */
	static const char ionian[16];
	static const char dorian[16];
	static const char phrygian[16];
	static const char lydian[16];
	static const char mixolydian[16];
	static const char aeolian[16];
	static const char locrian[16];
	/* end-MODES */
};

class MIDI_Scale {
	// friend ostream operator <<(ostream &os, const MIDI_Chord_Speller &midi_chord_speller);

public:
	MIDI_Scale() : note(0), scl() {}

	const Scale_type scl;

	void set_scale(int key, const char *scale_type, int num_voices, char *new_scale);

	int note_octave(int note);

	void scale_octave(int *dest, int num_voices);

	void seed_gen();

	int gen_rand_num();

	void rand_rests(char *dest, int num_voices);

private:
	int note; // set to C
	// boost::mt19937 gen;		// no longer in use
};


#endif