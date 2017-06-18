#ifndef MIDI_CHORD_TYPES_H
#define MIDI_CHORD_TYPES_H


namespace note {
    enum interval {
        root =0, min_second, second, min_third, third, fourth,
        	sharp_fourth, dim =6, fifth, min_sixth, sixth,
        	min_seventh, seventh, octave, min_ninth, ninth,
        	min_tenth, tenth, eleventh, sharp_eleventh, twelve,
        	min_thirteenth, thirteenth,
        
        _0 =0, _b2, _2, _sharp2, _b3 =3, _3, _4, _sharp4, _b5 =6,
        	_5, _sharp5, _b6 = 8, _6, _b7, _7,
        	_8va =12, _b9, _9, _b10, _10, _11, _b12, _12, _b13,
        	_13, _b14, _14, _15ma =24
    };
    enum names {
        C 		= 0,
        Csharp, Db 	= 1,
        D 		= 2,
        Dsharp, Eb 	= 3,
        E 		= 4,
        F 		= 5,
        Fsharp, Gb 	= 6,
        G 		= 7,
        Gsharp, Ab 	= 8,
        A 		= 9,
        Asharp, Bb 	= 10,
        B 		= 11
    };
    enum octave {
    	oct_up = 12, oct_down = -12
    };
};

namespace key {			// Redundant, but a more intuitive namespace for specifying Key
	enum names {
        C 		= 0,
        Csharp, Db 	= 1,
        D 		= 2,
        Dsharp, Eb 	= 3,
        E 		= 4,
        F 		= 5,
        Fsharp, Gb 	= 6,
        G 		= 7,
        Gsharp, Ab 	= 8,
        A 		= 9,
        Asharp, Bb 	= 10,
        B 		= 11
    };
};

class MIDI_Chord {
	friend std::ostream &operator <<(std::ostream &os, const MIDI_Chord &midi_chord);

public:
	MIDI_Chord();

	int note_octave(int note);

	void oct_up(int index);

	void oct_down(int index);

	void inversion(int index, int inv_type);

	/* return chord in correct key for user to do as they wish */
	std::vector<int> get_chord(int key, std::string chord_type);

	/* set external vector<int> as initialized by user (vs using push_back(get_chord())... */
	void set_chord(int key, std::string chord_type, std::vector<int> &new_chord);

	/* populate private data member <chords> */
	void add_chord(int key, std::string chord_type);

	/* to be used by the add_rand_chord() method */
	void randomize_key(std::string chord_type, std::vector<int> &chord);

	void define_key(int key, std::string chord_type, std::vector<int> &chord);

	void add_rand_chord();

	void add_rand_chord(int key);

	/* pop_back() last added chord */
	void pop_chord();

	std::vector<int> return_chord(int index);

	void print_chords();

	/* TODO harmonize method (make copy of chords_vec or simply add extra notes to existing vec?) */
	/* TODO random oct_up, oct_down for chord notes in chord_vec */
private:
	int note;
	static std::unordered_map<std::string, std::vector<int>> chord_master;
	std::vector<std::vector<int>> chords_vec;
};


#endif
