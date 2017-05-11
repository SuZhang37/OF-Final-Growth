#include "ofApp.h"

//--------------------------------------------------------------

ofPoint pLe = ofPoint(150, -100);
ofPoint pRi = ofPoint(-150, -100);


ofPoint gPoints1[] = {pLe, pRi};


ofVideoPlayer myPlayer;
ofSoundPlayer player_rain;
ofSoundPlayer player_wind;

int n=0;

simpleGesture gesture;


ofFbo fbo,spFbo;

//--------------------------------------------------------------
void ofApp::setup(){
    

    
    int num = 500;
    p.assign(num, demoParticle());
    currentMode;
    
    for(unsigned int i = 0; i < p.size(); i++){
        p[i].setup();
        
    }


    ofSetFrameRate(60);
    ofSetVerticalSync(true);

    
    fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA32F);
    spFbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA32F);


    
	leap.open();
    
	cam.setOrientation(ofPoint(0, 0, 0));
    
	glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    
    gesture.setup(gPoints1, 4, 2000);



    myPlayer.load(to_string(n)+".m4v");
    myPlayer.play();
    
    

   player_rain.load("rain.wav");
   player_wind.load("wind.wav");
}


//--------------------------------------------------------------
void ofApp::update(){


        for(unsigned int i = 0; i < p.size(); i++){
            p[i].setMode(currentMode);
            p[i].update();
        }


    
	fingersFound.clear();
	
    simpleHands = leap.getSimpleHands();
    
    
    myPlayer.update();

 

    
    if( leap.isFrameNew() && simpleHands.size() ){
        
        leap.setMappingX(-230, 230, -ofGetWidth()/2, ofGetWidth()/2);
		leap.setMappingY(90, 490, -ofGetHeight()/2, ofGetHeight()/2);
        leap.setMappingZ(-150, 150, -200, 200);
        
        fingerType fingerTypes[] = {THUMB, INDEX, MIDDLE, RING, PINKY};
        
        
        for(int i = 0; i < simpleHands.size(); i++){
            for (int f=0; f<5; f++) {
                int id = simpleHands[i].fingers[ fingerTypes[f] ].id;
                ofPoint mcp = simpleHands[i].fingers[ fingerTypes[f] ].mcp; // metacarpal
                ofPoint pip = simpleHands[i].fingers[ fingerTypes[f] ].pip; // proximal
                ofPoint dip = simpleHands[i].fingers[ fingerTypes[f] ].dip; // distal
                ofPoint tip = simpleHands[i].fingers[ fingerTypes[f] ].tip; // fingertip
                fingersFound.push_back(id);
                
            }
            
          
        }
         
    }
    

	leap.markFrameAsOld();
}

//--------------------------------------------------------------

void simpleGesture::setup(ofPoint *points, int maxIndex, int msTout){
    gPts = points;
    maxIdx = maxIndex;
    timeout = msTout;
    curIdx = 1;
}


bool simpleGesture::moveLeft (ofPoint iPt) {
    bool xMatch = false, yMatch = false;

    int timePerPoint = timeout / maxIdx;

    int currentT = ofGetElapsedTimeMillis();
    if (currentT > stepStartTime + timePerPoint) {
        curIdx = 1;
        lastPoint = iPt;
        stepStartTime = currentT;
    }

    // where to go next abs screen coords
    ofPoint absNext = lastPoint + gPoints1[curIdx];

    if (gPoints1[curIdx-1].x == gPoints1[curIdx].x) {  // if nothing has changed, match.
        xMatch = true;
    }

    if (gPoints1[curIdx-1].y == gPoints1[curIdx].y) {  // if nothing has changed, match.
        yMatch = true;
    }

    // find out what direction we are heading in
    if (gPoints1[curIdx-1].x < gPoints1[curIdx].x) {  // going right
        if (absNext.x < iPt.x)			// have we exceeded that x?
            
            xMatch = true;

        
    } else {					// going left
        if (absNext.x > iPt.x )
            xMatch = true;

    }



    if ( xMatch ) {
        
        curIdx++;
        lastPoint = iPt;
        stepStartTime = currentT;

        if (curIdx == maxIdx) {  // if we just matched our last point
            curIdx = 1; // start from beginning
            return(true);
        }
    }

        return (false);

}


//--------------------------------------------------------------
void ofApp::draw(){
    bool particles = false;

    
    ofSetColor(0, 0, 0);
    ofDrawRectangle(0, 0, 350, ofGetHeight());
    ofDrawRectangle(ofGetWidth()-250, 0, 250, ofGetHeight());

    ofBackgroundGradient(ofColor(0, 0, 0), ofColor(0, 0, 0),  OF_GRADIENT_BAR);

    
    ofSetColor(255);


    

	cam.begin();
    
    myPlayer.draw(-ofGetWidth()/2+70,-ofGetHeight()/2+30,ofGetWidth()*0.96,ofGetHeight()*0.96);
    
    if(n>0 && n<6){
      if(myPlayer.getCurrentFrame()>=myPlayer.getTotalNumFrames()-5){
         myPlayer.setPaused(true);
      }
    }
    

    if(n==5){
        if(myPlayer.getCurrentFrame()>=myPlayer.getTotalNumFrames()-5){
            myPlayer.setPaused(false);
            myPlayer.load(to_string(0)+".m4v");
            myPlayer.play();
        }
    }

    
    
    
    fingerType fingerTypes[] = {THUMB, INDEX, MIDDLE, RING, PINKY};
    

    
    for(int i = 0; i < simpleHands.size(); i++){
        bool isLeft        = simpleHands[i].isLeft;
        ofPoint handPos    = simpleHands[i].handPos;
        ofPoint handNormal = simpleHands[i].handNormal;


        ofSetColor(255,240,0,150);
        ofDrawSphere(handPos.x, handPos.y, handPos.z, 30);


        cout<< n << endl;
        

        bool LeftDone = gesture.moveLeft(simpleHands[i].fingers[INDEX].tip);

        
        //write another if state to check if the boolean has switched on
        if (LeftDone){
            cout << "----------------------LEFT----------------------" << endl;
            //cout << simpleHands[0].fingers[INDEX].tip  << endl;
            n++;
           // cout<<n<<endl;
            
            if(n>=6){
                n=0;

            }
            myPlayer.load(to_string(n)+".m4v");
            myPlayer.play();

            myPlayer.firstFrame();
            
            
                }


        
        
        for (int f=0; f<5; f++) {
            ofPoint mcp = simpleHands[i].fingers[ fingerTypes[f] ].mcp;  // metacarpal
            ofPoint pip = simpleHands[i].fingers[ fingerTypes[f] ].pip;  // proximal
            ofPoint dip = simpleHands[i].fingers[ fingerTypes[f] ].dip;  // distal
            ofPoint tip = simpleHands[i].fingers[ fingerTypes[f] ].tip;  // fingertip
            
//             ofSetColor(0, 255, 0);
//            ofDrawSphere(mcp.x, mcp.y, mcp.z, 12);
//            ofDrawSphere(pip.x, pip.y, pip.z, 12);
//            ofDrawSphere(dip.x, dip.y, dip.z, 12);
//            ofDrawSphere(tip.x, tip.y, tip.z, 12);
//
//
//            
//            ofSetColor(255, 0, 0);
//            ofSetLineWidth(20);
//            ofLine(mcp.x, mcp.y, mcp.z, pip.x, pip.y, pip.z);
//            ofLine(pip.x, pip.y, pip.z, dip.x, dip.y, dip.z);
//            ofLine(dip.x, dip.y, dip.z, tip.x, tip.y, tip.z);

           
            
            //float dist = tip.y-mcp.y;
            if(handPos.y>100){

                particles = true;

               }

            }
        
    }
    


	cam.end();

    
    if(particles==true && n>0 && n<4) {
        
        currentMode = PARTICLE_1;
        for(unsigned int i = 0; i < p.size(); i++){
            p[i].draw();
            
        }
        player_rain.play();
        
    } else {
        
    }
    
    if(particles==true && n >=4) {
        currentMode = PARTICLE_2;
        for(unsigned int i = 0; i < p.size(); i++){
            p[i].draw();
            
        }
        player_wind.load("wind.wav");
    }
    

    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if( key == '1'){

        n--;
        if(n<=0){
            n=0;
            
        }
    }

    if( key == '2'){
        n++;
        
        if(n>=6){
            n=0;
            
        }

   }
    myPlayer.load(to_string(n)+".m4v");
    myPlayer.play();
    myPlayer.firstFrame();
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}

//--------------------------------------------------------------
void ofApp::exit(){
    // let's close down Leap and kill the controller
    leap.close();
}
