#include "ofApp.h"
#include "Util.h"
#include "FontManager.h"

//#define EXPORT 1

void ofApp::setup(){
    ofSetBackgroundColor(0);
    ofSetFrameRate(60);
    ofSetCircleResolution(120);
    ofSetFullscreen(false);
    
    int w = 1920;
    int h = 1080;
    
    float scale = h/1080.0f;
    hMargin = w * 0.06;
    vMargin = ofGetWindowHeight() * 0.243;
    
    canvas.width = w * 0.4;
    canvas.height = h * 0.633;
    
    FontManager::setup(scale);
    
#ifdef EXPORT
    exporter.setup(1920, 1080, 60, GL_RGB, 16);
    exporter.setOutputDir("render1");
    exporter.setAutoExit(true);
    exporter.setOverwriteSequence(true);
    exporter.startExport();
#endif
    
    
    // make data
    vector<string> legend = {
        "aaa","aaa","aaa","aaa"
    };
    
    mesh.assign(3, ofVboMesh());
    
    ofFloatImage img;
    filesystem::path imgDir = Util::getResFolder()/"paper"/"1";
    img.load( (imgDir/"3.png").string() );
    
    int skip = 1;
    float sc = 1.2f;
    int width = img.getWidth();
    int height = img.getHeight();
    for(int y=0; y<height-skip; y+=skip) {
        for(int x=0; x<width-skip; x+=skip) {
            float b = img.getColor(x, y).b;
            float br = img.getColor(x, y).getBrightness();
            
            if(br>0.95) continue; // remove white
            if(b>0.1){
                ofVec3f v(x, y, 0);
                v *= sc;
                mesh[0].addVertex(v);
                mesh[0].addColor(ofFloatColor(1, b));
            }
        }
    }
}


void ofApp::update(){
    
    frame++;
    
}

void ofApp::draw(){
    
#ifdef EXPORT
    exporter.begin();
#endif
    
    
    ofBackground(0);

    ofPushMatrix();{
        ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
        ofSetColor(255);
        glPointSize(1.4);
        mesh[0].draw(OF_MESH_POINTS);
        
    }ofPopMatrix();
    
#ifdef EXPORT
    exporter.end();
    exporter.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight() );
#endif

}

void ofApp::keyPressed(int key){
    
    if(key==' '){
        frame = -1;
    }
}

int main(){
    
    ofGLFWWindowSettings s;
    s.setPosition( ofVec2f(0,0));
    s.title = "Entropy Motion Graphics::Measure";
    s.setGLVersion(4, 1);
    s.multiMonitorFullScreen = false;
    s.windowMode = OF_WINDOW;
    s.numSamples = 2;
    s.width = 1920;
    s.height = 1080;
    s.monitor = 1;
    s.decorated = false;
    
    ofCreateWindow(s);
    ofRunApp(ofApp::get());
}

