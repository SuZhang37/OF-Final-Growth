#pragma once

#include "ofMain.h"
#include "ofxLeapMotion2.h"
#include "demoParticle.hpp"


class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
	
    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    void exit();

    
	ofxLeapMotion leap;
	vector <ofxLeapMotionSimpleHand> simpleHands;
    
	vector <int> fingersFound;
    
	ofEasyCam cam;
    bool frameByframe;
    
    particleMode currentMode;
    vector <demoParticle> p;
    
    int n=0;
    

};


class simpleGesture {
public:
    void setup(ofPoint *points, int maxIndex, int msTout);
    bool track(ofPoint inputPoint);  // given a moving input point returns true if matched
    bool moveDown(ofPoint inputPoint);
    bool moveLeft(ofPoint inputPoint);
    int maxIdx;		// max gesture array index
    int timeout;	// how long do we have to match the gesture before reset

private:
    ofPoint *gPts;	// array of key points in our gesture
    int stepStartTime = 0; // when we finished the last step in the whole gesture
    int curIdx;	// current point we are matching to
    ofPoint lastPoint;  // where last point matched
};
