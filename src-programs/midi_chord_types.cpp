#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <unordered_map>

#include "midi_chord_types.h"
#include "midi_misc.h"

using namespace std;

MIDI_Chord::MIDI_Chord() : note(0), chords_vec( {} ) { }

unordered_map<string, vector<int>> MIDI_Chord::chord_master {
		// DYADS
		{ "_unison",		{ 0,0 } },
		{ "_b2",		{ 0,1 } },
		{ "_2",			{ 0,2 } },
		{ "_b3",		{ 0,3 } },
		{ "_3",			{ 0,4 } },
		{ "_4",			{ 0,5 } },
		{ "_b5",		{ 0,6 } },
		{ "_5",			{ 0,7 } },
		{ "_b6",		{ 0,8 } },
		{ "_6",			{ 0,9 } },
		{ "_b7",		{ 0,10 } },
		{ "_7",			{ 0,11 } },
		{ "_8va",		{ 0,12 } },

		{ "_b9",		{ 0,13 } },
		{ "_9",			{ 0,14 } },
		{ "_b10",		{ 0,15 } },
		{ "_10",		{ 0,16 } },
		{ "_11",		{ 0,17 } },
		{ "_b12",		{ 0,18 } },
		{ "_12",		{ 0,19 } },
		{ "_b13",		{ 0,20 } },
		{ "_13",		{ 0,21 } },
		{ "_b14",		{ 0,22 } },
		{ "_14",		{ 0,23 } },
		{ "_15ma",		{ 0,24 } },		
		// end-DYADS

		// TRIADS
		{ "maj",		{ 0,4,7 } },
		{ "min",		{ 0,3,7 } },
		{ "sus2",		{ 0,2,7 } },
		{ "sus4",		{ 0,5,7 } },
		{ "dim",		{ 0,3,6 } },
		{ "aug",		{ 0,4,8 } },
		// end-TRIADS

		// SEVENTHS/QUADS
		{ "maj7",		{ 0,4,7,11 } },
		{ "min7",		{ 0,3,7,10 } },
		{ "dom7",		{ 0,4,7,10 } },
		{ "min7_b5",		{ 0,3,6,10 } },
		{ "half_dim7",		{ 0,3,6,10 } },
		{ "dim7",		{ 0,3,6,9 } },
		{ "full_dim7",		{ 0,3,6,9 } },

		{ "min_maj7",		{ 0,3,7,11 } },
		{ "maj7_sus2",		{ 0,2,7,11 } },
		{ "maj7_sus4",		{ 0,5,7,11 } },
		{ "min7_sus2",		{ 0,2,7,10 } },
		{ "min7_sus4",		{ 0,5,7,10 } },

		{ "maj6",		{ 0,4,7,9 } },
		{ "min6",		{ 0,3,7,9 } },

		{ "maj_add_b9",		{ 0,4,7,13 } },
		{ "maj_add_9",		{ 0,4,7,14 } },
		{ "maj_add_sharp9",	{ 0,4,7,15 } },
		{ "maj_add_b10",	{ 0,4,7,15 } },
		{ "maj_add_11",		{ 0,4,7,17 } },
		{ "maj_add_sharp11",	{ 0,4,7,18 } },
		{ "maj_add_b12",	{ 0,4,7,18 } },
		{ "maj_add_13",		{ 0,4,7,21 } },
		{ "maj_add_sharp13",	{ 0,4,7,22 } },
		{ "maj_add_b14",	{ 0,4,7,22 } },

		{ "min_add_b9",		{ 0,3,7,13 } },
		{ "min_add_9",		{ 0,3,7,14 } },
		{ "min_add_sharp9",	{ 0,3,7,15 } },
		{ "min_add_b10",	{ 0,3,7,15 } },
		{ "min_add_11",		{ 0,3,7,17 } },
		{ "min_add_sharp11",	{ 0,3,7,18 } },
		{ "min_add_b12",	{ 0,3,7,18 } },
		{ "min_add_13",		{ 0,3,7,21 } },
		{ "min_add_sharp13",	{ 0,3,7,22 } },
		{ "min_add_b14",	{ 0,3,7,22 } },

		{ "sus2_add_9",		{ 0,2,7,14 } },
		{ "sus2_add_sharp9",	{ 0,2,7,15 } },
		{ "sus2_add_b10",	{ 0,2,7,15 } },
		{ "sus2_add_11",	{ 0,2,7,17 } },
		{ "sus2_add_sharp11",	{ 0,2,7,18 } },
		{ "sus2_add_b12",	{ 0,2,7,18 } },
		{ "sus2_add_13",	{ 0,2,7,21 } },
		{ "sus2_add_sharp13",	{ 0,2,7,22 } },
		{ "sus2_add_b14",	{ 0,2,7,22 } },

		{ "sus4_add_9",		{ 0,5,7,14 } },
		{ "sus4_add_sharp9",	{ 0,5,7,15 } },
		{ "sus4_add_b10",	{ 0,5,7,15 } },
		{ "sus4_add_11",	{ 0,5,7,17 } },
		{ "sus4_add_sharp11",	{ 0,5,7,18 } },
		{ "sus4_add_b12",	{ 0,5,7,18 } },
		{ "sus4_add_13",	{ 0,5,7,21 } },
		{ "sus4_add_sharp13",	{ 0,5,7,22 } },
		{ "sus4_add_b14",	{ 0,5,7,22 } },
		// end-SEVENTHS/QUADS

		// NINTHS/QUINTS
		{ "maj9",			{ 0,4,7,11,14 } },
		{ "min9",			{ 0,3,7,10,14 } },
		{ "dom9",			{ 0,4,7,10,14 } },
		{ "min9_b5",			{ 0,3,6,10,14 } },
		{ "maj11",			{ 0,4,11,14,18 } },
		{ "min11",			{ 0,3,10,14,17 } },
		{ "maj13",			{ 0,4,11,14,21 } },
		{ "min13",			{ 0,3,10,14,21 } },
		{ "dom11",			{ 0,4,10,14,18 } },
		{ "dom13",			{ 0,4,10,14,21 } }
		// end-NINTHS/QUINTS
};

ostream &operator <<(ostream &os, const MIDI_Chord &midi_chord) {
	/* using cbegin() and cend when working with const object */
	unordered_map<string, vector<int>>::const_iterator it = midi_chord.chord_master.cbegin();
 
	while (it != midi_chord.chord_master.cend()) {
		os << "chord: " << it->first;
		if (it->first.length() > 8) os << "\t\t";
		else os << "\t\t\t";
		auto vec_end = it->second.cend();
		for (auto it2 = it->second.cbegin(); it2 != vec_end; ++it2)
            os << *it2 << (it2 == vec_end-1 ? "\n" : ", ");
		it++;
	}
	return os;
}

int MIDI_Chord::note_octave(int note) {
	return note + 12;
}

void MIDI_Chord::oct_up(int index) {
	vector<int>::size_type size = chords_vec[index].size();
	for (int i=0; i<size; ++i)
		chords_vec[index][i] += 12;
}

void MIDI_Chord::oct_down(int index) {
	vector<int>::size_type size = chords_vec[index].size();
	for (int i=0; i<size; ++i)
		chords_vec[index][i] -= 12;
}

void MIDI_Chord::inversion(int index, int inv_type) {
	/* usage:
	 * 1 = first inv 	{12,x,x,x}
	 * 2 = second inv 	{12,12,x,x}
	 * 3 = third inv 	{12,12,12,x}
	 */
	if (inv_type != 1 && inv_type != 2 && inv_type != 3) {
		cerr << "usage: inv_type must be 1, 2 or 3" << endl;
		return;
	}
	chords_vec[index].at(0) += 12;			// will work on all chords including dyad
	if (inv_type == 2) {
		chords_vec[index].at(1) += 12;
	} else if (inv_type == 3) {
		chords_vec[index].at(1) += 12;
		chords_vec[index].at(2) += 12;
	}
}

vector<int> MIDI_Chord::get_chord(int key, string chord_type) {
	vector<int>::size_type size = chord_master[chord_type].size();
	vector<int> temp(size);
	for (int i=0; i<size; ++i)
		temp[i] = chord_master[chord_type][i] + key;
	return temp;
}

void MIDI_Chord::set_chord(int key, string chord_type, vector<int> &new_chord) {
	vector<int>::size_type size = chord_master[chord_type].size();
	new_chord.reserve(size);
	for (int i=0; i<size; ++i)
		new_chord[i] = chord_master[chord_type][i] + key;
}

void MIDI_Chord::add_chord(int key, string chord_type) {
	chords_vec.push_back(get_chord(key, chord_type));
}

void MIDI_Chord::randomize_key(string chord_type, vector<int> &chord) {
	vector<int>::size_type size = chord.size();
	int new_key = random_int(0,11);
	cout << "NEW RANDOM KEY: " << new_key << " CHORD: " << chord_type << "\n";
	for (int i=0; i<size; ++i) {
		chord[i] += new_key;
	}
}

void MIDI_Chord::define_key(int relative_key, string chord_type, vector<int> &chord) {
	vector<int>::size_type size = chord.size();
	cout << "RELATIVE KEY: " << relative_key << " CHORD: " << chord_type << "\n";
	for (int i=0; i<size; ++i) {
		chord[i] += relative_key;
	}
}

void MIDI_Chord::add_rand_chord() {
	auto random_it = next(begin(chord_master), random_int(0, chord_master.size()-1 ));
	chords_vec.push_back(chord_master[random_it->first]);
	randomize_key(random_it->first, chords_vec.back());
}

void MIDI_Chord::add_rand_chord(int key) {
	auto random_it = next(begin(chord_master), random_int(0, chord_master.size()-1 ));
	while (chord_master[random_it->first].size() < 3) {
		random_it = next(begin(chord_master), random_int(0, chord_master.size()-1 ));
	}
	chords_vec.push_back(chord_master[random_it->first]);
	string chord_type = random_it->first;
	if (chord_type.find("maj") != string::npos) {
		int n = random_int(0,5);
		if (n < 4) { 			// this maj chord remains the root I chord
		} else if (n == 4) {
			key += 5;			// this maj chord will become the IV chord
		} else {
			key += 7;			// this maj chord will become the V chord
		}
	} else if (chord_type.find("min") != string::npos) {
		int n = random_int(0,2);
		if (n == 0) {
			key += 2;			// this min chord will become the ii chord
		} else if (n == 1) {
			key += 4;			// this min chord will become the iii chord
		} else {
			key += 9;			// this min chord will become the vi chord
		}
	} else if (chord_type.find("dom") != string::npos) {
		key += 7;				// this dom chord will become the V chord
	} else if (chord_type.find("dim") != string::npos
			|| chord_type.find("b5") != string::npos) {
		key += 11;				// this dim / b5 chord will become the vii chord
	} else if (chord_type.find("sus2") != string::npos
			|| chord_type.find("sus4") != string::npos) {
		int n = random_int(0,5);
		if (n == 0) { 			// this sus chord remains the root I chord
		} else if (n == 1) {
			key += 2;			// this sus chord will become the ii chord
		} else if (n == 2) {
			key += 4;			// this sus chord will become the iii chord
		} else if (n == 3) {
			key += 5;			// this sus chord will become the IV chord
		} else if (n == 4) {
			key += 7;			// this sus chord will become the V chord
		} else if (n == 5) {
			key += 9;			// this sus chord will become the vi chord
		}
	} else { }					// undefined; leave key unchanged (TODO define rest?)
	define_key(key, chord_type, chords_vec.back());
}

void MIDI_Chord::pop_chord() {
	chords_vec.pop_back();
}

vector<int> MIDI_Chord::return_chord(int index) {
	return chords_vec[index];
}

void MIDI_Chord::print_chords() {
	if (chords_vec.empty()) { cout << "chords_vec is empty!"; return; }
	vector<int>::size_type size_outer = chords_vec.size();
	for (unsigned int i=0; i<size_outer; ++i) {
		cout << "Index: " << i << " Chord: ";
    	for (unsigned int j=0; j<chords_vec[i].size(); ++j) {
        	cout << chords_vec[i][j] << " ";
    	}
    	cout << "\n";
	}
}
