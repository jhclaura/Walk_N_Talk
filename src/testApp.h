#pragma once

#include "ofMain.h"
#include "people.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
    
    ofMesh mesh;
    ofImage image;
    
    ofEasyCam easyCam;
    
    vector<ofVec3f> offset;
    
    ofMesh meshCopy;
    bool orbiting;
    float startOrbitTime;
    
    vector<float> distances;
    vector<float> angles;
    ofVec3f meshCentroid;
    
    //MAG
    bool mouseDisplacement;
    
    //DRAW_GEOMETRY
    void makeGeo(int x, int y);
    vector<ofMesh> geos;
    vector<ofColor> colors;
    
    ofMesh point;
    
    //------------ CLASS_PEOPLE -------------
    vector<people*> ppls;
    
};
