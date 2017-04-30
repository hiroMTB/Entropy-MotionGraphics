#include "ofApp.h"
#include "ofxEasing.h"


void ofApp::setup(){
	ofSetBackgroundColor(0);
	length = ofGetHeight()/6;
    
    const int nVal = 1200;
    positions.assign(nVal, 0.0f);
    targets.assign(nVal, 0.0f);
    chain.assign(nVal, vector<EasingPrm>() );
    
    const bool bSynch = false;
    
    float duration;
    if(bSynch) duration = 0.2f;
    
    for(int j=0; j<positions.size(); j++){

        if(!bSynch) duration = ofRandom(0.6f, 1.0f);

        float pastEndVal = 0;
        float pastEndTime = 0;
        
        for(int i=0; i<100; i++){
            EasingPrm p;
            p.startTime = pastEndTime;
            p.endTime   = p.startTime + duration;
            p.startVal  = pastEndVal;
            p.endVal    = ofRandom(0, length) * (j%2==0?-1:1);
            p.easing = ofxeasing::easing((ofxeasing::Function)(ofRandom(0,10)), (ofxeasing::Type)(ofRandom(0,3)));

            if(i%10==4){
                p.endVal = length * (j%2==0?-1:1);
                p.endTime += duration*5;
            }
            
            chain[j].push_back(p);
            
            pastEndTime = p.endTime;
            pastEndVal = p.endVal;
        }
    }

    cout << "size of position "  << positions.size() << endl;
    cout << "size of chain "  <<    chain.size() << endl;

}

void ofApp::update(){
    auto now = ofGetElapsedTimef(); //ofGetFrameNum()/30.0f;

    for(int j=0; j<positions.size(); j++){
        
        for(int i=0; i<chain[j].size(); i++){
        
            EasingPrm &p = chain[j][i];
            
            if( p.startTime<=now && now<p.endTime){
                targets[j] = p.endVal;
                positions[j] = ofxeasing::map_clamp(now, p.startTime, p.endTime, p.startVal, p.endVal, p.easing);
            }
        }
    }
    
    poly1.clear();
    poly2.clear();
}

void ofApp::draw(){
	ofSetColor(255);
	auto h = 1;
    
    ofTranslate(50, ofGetHeight()/2);
    
    ofPushMatrix();
    for( int i=0; i<positions.size(); i++){
        ofSetColor(255);
        
        ofPushMatrix();
        ofTranslate(h*i, 0);
        ofSetRectMode(OF_RECTMODE_CENTER);
        ofDrawLine(0, 0, 0, positions[i]);
        ofDrawCircle(0, positions[i], 1);

        ofSetColor(100, 170);
        ofDrawLine(0, 0, 0, targets[i]);
        ofDrawCircle(0, targets[i], 1);
        ofPopMatrix();
        
        if(i%2==0) poly1.addVertex(h*i, positions[i]);
        else poly2.addVertex(h*i, positions[i]);

    }
    ofPopMatrix();

//    ofSetColor(150, 150);
//    poly1.draw();
//    poly2.draw();
    
}
