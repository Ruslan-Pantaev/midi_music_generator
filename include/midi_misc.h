#ifndef MIDI_MISC_H
#define MIDI_MISC_H


/* Ended up using boost::filesystem instead
 * This bool func is not in use
 */
bool does_file_exist(std::string fileName);

int random_int(int min, int max);

#endif