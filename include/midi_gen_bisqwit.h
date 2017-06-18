/* 
 * Copyright (c) 2010 Joel Yliluoma <bisqwit>
 * Thanks to bisqwit for these MIDI classes
 * Implemented and modified by arpiseaQ
 * Using timidity++ to play .mid files
 * See <http://www.ccarh.org/courses/253/handout/smf/>
 */

#ifndef MIDI_GEN_BISQWIT_H
#define MIDI_GEN_BISQWIT_H

#include <vector>
#include <cstring>
#include <cstdio>               // For std::fopen(), std::fwrite(), std::fclose()


typedef unsigned char byte;

/* First define a custom wrapper over std::vector<byte>
 * so we can quickly push_back multiple bytes with a single call.
 */
class MIDIvec: public std::vector<byte> {
public:
    // Methods for appending raw data into the vector:
    template<typename... Args>
    void AddBytes(byte data, Args...args) {
        push_back(data);
        AddBytes(args...);
    }
    template<typename... Args>
    void AddBytes(const char* s, Args...args) {
        insert(end(), s, s + std::strlen(s));
        AddBytes(args...);
    }
    void AddBytes() { }
};

/* Define a class which encodes MIDI events into a track */
class MIDItrack: public MIDIvec {
protected:
    unsigned delay, running_status;
public:
    MIDItrack() : MIDIvec(), delay(0), running_status(0) { }
    
    // Methods for indicating how much time elapses:
    void AddDelay(unsigned amount) { delay += amount; }
    
    void AddVarLen(unsigned t) {
        if(t >> 21) AddBytes(0x80 | ((t >> 21) & 0x7F));
        if(t >> 14) AddBytes(0x80 | ((t >> 14) & 0x7F));
        if(t >>  7) AddBytes(0x80 | ((t >>  7) & 0x7F));
        AddBytes(((t >> 0) & 0x7F));
    }
    
    void Flush() {
        AddVarLen(delay);
        delay = 0;
    }
    
    // Methods for appending events into the track:
    template<typename... Args>
    void AddEvent(byte data, Args...args) {
        /* MIDI tracks have the following structure:
         *
         * { timestamp [metaevent ... ] event } ...
         *
         * Each event is prefixed with a timestamp,
         * which is encoded in a variable-length format.
         * The timestamp describes the amount of time that
         * must be elapsed before this event can be handled.
         *
         * After the timestamp, comes the event data.
         * The first byte of the event always has the high bit on,
         * and the remaining bytes always have the high bit off.
         *
         * The first byte can however be omitted; in that case,
         * it is assumed that the first byte is the same as in
         * the previous command. This is called "running status".
         * The event may furthermore be prefixed
         * with a number of meta events.
         */
       Flush();
       if(data != running_status) AddBytes(running_status = data);
       AddBytes(args...);
    }
    void AddEvent() { }
    
    template<typename... Args>
    void AddMetaEvent(byte metatype, byte nbytes, Args...args)
    {
        Flush();
        AddBytes(0xFF, metatype, nbytes, args...);
    }
    
    // Key-related parameters: channel number, note number, pressure
    void KeyOn(int ch, int n, int p) {
        if (n>=0)
            AddEvent(0x90|ch, n, p);
    }

    void KeyOff(int ch, int n, int p) {
        if (n>=0)
            AddEvent(0x80|ch, n, p);
    }

    void KeyTouch(int ch, int n, int p) {
        if (n>=0)
            AddEvent(0xA0|ch, n, p);
    }
    
    // Events with other types of parameters:
    void Control(int ch, int c, int v) {
        AddEvent(0xB0|ch, c, v);
    }

    void Patch(int ch, int patchno) {
        AddEvent(0xC0|ch, patchno);
    }

    void Wheel(int ch, unsigned value) {
        AddEvent(0xE0|ch, value&0x7F, (value>>7)&0x7F);
    }
    
    // Methods for appending metadata into the track:
    void AddText(int texttype, const char* text) {
        AddMetaEvent(texttype, std::strlen(text), text);
    }
};

/* Define a class that encapsulates all methods needed to craft a MIDI file. */
class MIDIfile: public MIDIvec {
protected:
    std::vector<MIDItrack> tracks;
    unsigned deltaticks, tempo;
public:
    MIDIfile() : MIDIvec(), tracks(), deltaticks(1000), tempo(1050000) { }
    
    void AddLoopStart() {
        (*this)[0].AddText(6, "loopStart");
    }

    void AddLoopEnd() {
        (*this)[0].AddText(6, "loopEnd");
    }
    
    MIDItrack& operator[] (unsigned trackno) {
        if (trackno >= tracks.size()) {
            tracks.reserve(16);
            tracks.resize(trackno+1);
        }
        
        MIDItrack& result = tracks[trackno];
        if (result.empty()) {
            // Meta 0x58 (misc settings):
                //      time signature: 4/2
                //      ticks/metro:    24
                //      32nd per 1/4:   8
            result.AddMetaEvent(0x58,4,  4,2, 24,8);
            // Meta 0x51 (tempo):
            result.AddMetaEvent(0x51,3,  tempo>>16, tempo>>8, tempo);
        }
        return result;
    }
    
    void Finish() {
        clear();
        AddBytes(
            // MIDI signature (MThd and number 6)
            // see for explanation of MThd and MTrk--> <http://www.ccarh.org/courses/253/handout/smf/>
            "MThd", 0,0,0,6,
            // Format number (1: multiple tracks, synchronous)
            0,1,
            tracks.size() >> 8, tracks.size(),
            deltaticks    >> 8, deltaticks);
        for (unsigned a=0; a<tracks.size(); ++a) {
            // Add meta 0x2F to the track, indicating the track end:
            tracks[a].AddMetaEvent(0x2F, 0);
            // Add the track into the MIDI file:
            AddBytes("MTrk",
                tracks[a].size() >> 24,
                tracks[a].size() >> 16,
                tracks[a].size() >>  8,
                tracks[a].size() >>  0);
            insert(end(), tracks[a].begin(), tracks[a].end());
        }
    }

    void set_tempo(unsigned t) {tempo = t;}
};


#endif