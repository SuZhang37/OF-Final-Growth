#include "demoParticle.hpp"

//------------------------------------------------------------------
demoParticle::demoParticle(){
    
}

//------------------------------------------------------------------
void demoParticle::setMode(particleMode newMode){
    mode = newMode;
    
}

//------------------------------------------------------------------
void demoParticle::setup(){
    uniqueVal = ofRandom(-20000, 20000);
    
    pos.x = ofRandomWidth();
    pos.y = ofRandomHeight();
    
    vel.x = 0.01;
    vel.y = fabs(vel.y) * 3.0;
    
    frc   = ofPoint(0,0,0);
    
    scale = ofRandom(20, 40);
    
    
    drag  = ofRandom(0.97, 0.99);
    
}




//------------------------------------------------------------------
void demoParticle::update(){
    
    
    if( mode == PARTICLE_1 ){
    float fakeWindX = ofSignedNoise(pos.x , pos.y , ofGetElapsedTimef() );
    
    frc.x = fakeWindX * 0.25 ;
    frc.y = ofSignedNoise(uniqueVal, pos.x , ofGetElapsedTimef()) *0.01 +0.1;
    
    vel += frc * 0.1;
    
    
      if( pos.y + vel.y > ofGetHeight() ){
        pos.y -= ofGetHeight();
      }
        
    }
    
    if( mode == PARTICLE_2 ){
        
        float fakeWindX = ofSignedNoise(pos.x * 0.003, pos.y * 0.006, ofGetElapsedTimef() * 0.6);
        
        frc.x = fakeWindX * 0.25 + ofSignedNoise(uniqueVal, pos.y * 0.04) * 0.6;
        frc.y = ofSignedNoise(uniqueVal, pos.x * 0.006, ofGetElapsedTimef()*0.2) * 0.09 + 0.18;
        
        vel *= drag;
        vel += frc * 0.4;
        

        if( pos.y + vel.y > ofGetHeight() ){
            pos.y -= ofGetHeight();
        }
    }
    

    
    
    pos += vel;
    
    
        if( pos.x > ofGetWidth() ){
        pos.x = ofGetWidth()+15;
        vel.x *= -1.0;
    }else if( pos.x < 0 ){
        pos.x = -15;
        vel.x *= -1.0;
    }
    if( pos.y > ofGetHeight() ){
        pos.y = ofGetHeight();
        vel.y *= -1.0;
    }
    else if( pos.y < 0 ){
        pos.y = 0;
        vel.y *= -1.0;
    }
    
}

//------------------------------------------------------------------
void demoParticle::draw(){
    
    if(mode == PARTICLE_1){
    ofSetColor(255,255,255,200);
    ofDrawLine(pos.x, pos.y, pos.x, pos.y+scale);
    }
    
    if(mode == PARTICLE_2){
        ofSetColor(255,255,255);
        ofDrawCircle(pos.x, pos.y, scale * 0.15);
    }
    

}
