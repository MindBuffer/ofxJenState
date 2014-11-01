//
//  ofxJenOscState.cpp
//  example_ofxJenOsc
//
//  Created by Mitchell Nordine on 1/11/2014.
//
//

#include "ofxJenOscState.h"

using namespace ofxJenOsc;

double Playhead::percentage() {
    if (durationInTicks > 0) {
        return (double)positionInTicks / (double)durationInTicks;
    } else {
        return 0.0;
    }
}

void State::update() {
	while(oscReceiver.hasWaitingMessages()){
		ofxOscMessage m;
		oscReceiver.getNextMessage(&m);
        
        // Use messages to update current state here...
        
    }
}

inline vector<const Playhead*> State::getPlayheads() {
    vector<const Playhead*> vec;
    vec.reserve(playheads.size());
    for (int i = 0; i < playheads.size(); i++) {
        const Playhead* playhead = &playheads[i];
        vec.push_back(playhead);
    }
    return vec;
}

inline vector<const Rhythm*> State::getRhythms() {
    vector<const Rhythm*> vec;
    vec.reserve(rhythms.size());
    for (int i = 0; i < rhythms.size(); i++) {
        const Rhythm* rhythm = &rhythms[i];
        vec.push_back(rhythm);
    }
    return vec;
}

inline vector<const Rhythm*> State::getRhythmsOfType(RhythmType type) {
    vector<const Rhythm*> vec;
    vec.reserve(rhythms.size());
    for (int i = 0; i < rhythms.size(); i++) {
        if (rhythms[i].type == type) {
            const Rhythm* rhythm = &rhythms[i];
            vec.push_back(rhythm);
        }
    }
    return vec;
}