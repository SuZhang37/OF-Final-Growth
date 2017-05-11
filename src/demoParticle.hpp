#pragma once
#include "ofMain.h"

enum particleMode{
    
    PARTICLE_1,
    PARTICLE_2,

    
};

class demoParticle{
    
public:
    demoParticle();
    
    void setMode(particleMode newMode);
    void reset();
    void update();
    void draw();
    void setup();
    
    ofPoint pos;
    ofPoint vel;
    ofPoint frc;
    
    float drag;
    float uniqueVal;
    float scale;
    
    particleMode mode;
    
    vector <ofPoint> * attractPoints;
    vector<ofColor> colors;
};
