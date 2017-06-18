#include <fstream>
#include <string>

#include <boost/random.hpp>
#include <boost/generator_iterator.hpp>
#include <random>

#include "midi_misc.h"

using namespace std;


/* Ended up using boost::filesystem instead
 * This bool func is not in use
 */
bool does_file_exist(string fileName)
{
    ifstream infile(fileName);
    return infile.good();
}

int random_int(int min, int max) {
	random_device rd;		// I think I prefer seeding with random device vs ctime
	mt19937 rng(rd()); 		// seed with Mersenne-Twister engine VS ctime
	uniform_int_distribution<int> uni(min, max);
	return uni(rng);
}

/* Another way to implement random function
void MIDI_Scale::seed_gen() {
	gen.seed(static_cast<unsigned int>(std::time(0)));
}

int MIDI_Scale::gen_rand_num() {
	// seed_gen();
	boost::uniform_int<> dist(1, 2);
    boost::variate_generator<boost::mt19937&, boost::uniform_int<> > num(gen, dist);
    return num();
}
*/