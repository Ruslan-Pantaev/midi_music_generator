# edit arpiseaQ_6/5/2017_22:28
# TODO edit this build_system into a makefile 

{
"cmd" : ["g++ -std=c++11 *.cpp -L/usr/local/Cellar/boost/1.64.0_1/include/boost/ -lboost_filesystem-mt -lboost_system-mt -lboost_random-mt -I/Users/arpiseaQ/Documents/codeMASTER/SUMMER_17_projects/MIDI_CHORDS_arpiseaQ/include/ -o $file_base_name"], 
# "file_regex": "^(..[^:]*):([0-9]+):?([0-9]+)?:? (.*)$",
"selector" : "source.c++",
"shell": true,
"working_dir" : "$file_path"
}