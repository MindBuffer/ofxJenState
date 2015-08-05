//
//  ofxJenOscState.h
//  example_ofxJenOsc
//
//  Created by Mitchell Nordine on 1/11/2014.
//
//

#pragma once

#include "ofMain.h"
#include "ofThread.h"
#include "ofxNanomsg.h"
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>

using namespace boost;

namespace ofxJenState {

    /// Represents the different type of musical durations within Jen.
    /// These will also be used to index the `playheads` vector within `State`.
    enum Measure {
        Phrase,
        Segment,
        Bar,
        Minim,
        Beat,
        Quaver,
        SemiQuaver,
        TotalMeasures
    };


    /// Represents the state of a Note.
    class Note {
    public:

        Note(unsigned int _id, float _playhead, float _velocity = 1.0f)
        : id(_id)
        , playhead(_playhead)
        , velocity(_velocity) {
        }
        
        unsigned int id;
        float playhead;
        float velocity;
        
    };

    /// Represents the different types of Patterns generated by Jen.
    enum PatternType {
        Kick,
        Snare,
        Ghost,
        Ride,
        Layer,
        Bass,
        Melodic,
        Chordal,
        Atmos
    };
    
    /// Represents the state of an Instrument.
    class Instrument {
    public:

        Instrument(PatternType _type, string _name, vector<float> _notePlayheads)
        : type(_type)
        , name(_name)
        , notePlayheads(_notePlayheads) {
        }

        const PatternType type;
        const string name;
        vector<float> notePlayheads;
        float amp;
        float pan; /// -1.0 is far left, 0.0 is center and 1.0 is far right.

    };
    
    class Bus {
    public:
        
        Bus(string _name, float _vol)
        : name(_name)
        , vol(_vol) {
        }
        
        string name;
        float vol;
    };
    
    
    class Receiver: public ofThread {
        
    public:
        Receiver() {
            nanoPull.bind("tcp://*:9000");
        }
        
        void threadedFunction();
        
        ofxNanomsgPull nanoPull;
        string stateString;
        bool hasUpdated;
    };
    

    /// Represents the entire state of Jen. By calling `update`, the state will
    /// check for OSC messages and update its entire state accordingly.
    class State {
    public:

        ~State(){
            receiver.stopThread();
            while (receiver.isThreadRunning()) { sleep(10); };
        }
        
        State()
        : playheads(TotalMeasures, 0.0)
        , master("MASTER", 0.0) {
            
            receiver.startThread();
            
        }
        
        void update();

        vector<float> playheads;
        vector<Instrument> instruments;
        vector<Bus> busses;
        Bus master;
        
        Receiver receiver;

    };
    


}

