# C++ MIDI music generator

 * Author:          Ruslan Pantaev <arpiseaQ>
 * License:         MIT License
 * Start_Date:      6/4/2017
 * Last_modified:   6/18/2017
 

 
The C++ MIDI music generator creates midi files from scratch. It can accept user defined note sequences & chords, random chords, or pseuodo-random chords within a specified key or mode. I will continue to update chords & scales and allow for custom tone-rows. Special thanks to Joel Yliluoma <bisqwit> for the midi handling classes (see midi_gen_bisqwit.h, ported from <http://bisqwit.iki.fi/jutut/kuvat/programming_examples/midimake.cc>).


### Todos

 - Write install instructions and dependencies
 - Fix makefile (currently a custom sublime-text Build System w/ arbitrary file path to src-programs)
 - Work out midi_scale_types to generate melodies & define chord-scales within a specified key
 - Change scale_types to vector<char> to handle octatonic, pentatonic, custom tone-rows & traditional modes (using char so user can indicate 'x' to indicate note-offs with the added benefit of taking up 1 byte vs 4 bytes of an int)
 - Create main.cpp template for ease of use
 - Clean up & simplify classes
 - Put dir and file check / creation into midi_misc.h?
 - Incorporate libsndfile wav / aiff handling
 - Incorporate timidity++ or some other lib to convert .mid to audio file? (experienced bugs in osx 10.11.6)
 - Port over backend to server and create web-app frontend for ease of use?

---

**Share and enjoy!**