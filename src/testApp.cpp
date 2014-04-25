#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
//    mesh.setMode(OF_PRIMITIVE_LINES);
//    mesh.enableColors();
//    mesh.enableIndices();
//    
//    ofVec3f top(100.0, 50.0, 0.0);
//    ofVec3f left(50.0, 150.0, 0.0);
//    ofVec3f right(150.0, 150.0, 0.0);
//    
//    mesh.addVertex(top);
//    mesh.addColor(ofFloatColor(1.0, 0.0, 0.0));
//    
//    mesh.addVertex(left);
//    mesh.addColor(ofFloatColor(0.0, 1.0, 0.0));
//    
//    mesh.addVertex(right);
//    mesh.addColor(ofFloatColor(0.0, 0.0, 1.0));
//    
//    mesh.addIndex(0);
//    mesh.addIndex(1);
//    mesh.addIndex(1);
//    mesh.addIndex(2);
//    mesh.addIndex(2);
//    mesh.addIndex(0);
    
    image.loadImage("galaxyS.jpg");
    mesh.setMode(OF_PRIMITIVE_LINES);
    
    //resize
    image.resize(125, 115);
    
    float intensityThreshold = 140.0;
    int w = image.getWidth();
    int h = image.getHeight();
    for (int x=0; x<w; ++x) {
        for (int y=0; y<h; ++y) {
            
            ofColor c = image.getColor(x, y);
            float intensity = c.getLightness();
            
            if (intensity > intensityThreshold) {
                
                float saturation = c.getSaturation();
                float z = ofMap(saturation, 0, 255, -100, 100);
                
                ofVec3f pos(x*4, y*4, z);
                mesh.addVertex(pos);
                mesh.addColor(c);
                
                offset.push_back(ofVec3f(ofRandom(0,100000), ofRandom(0,100000), ofRandom(0,100000)));
            }
        }
    }
    
//    cout << mesh.getNumVertices() << endl;
    
    float connectionDistance = 15;
    int numVerts = mesh.getNumVertices();
    for (int a=0; a<numVerts; ++a) {
        ofVec3f verta = mesh.getVertex(a);
        for (int b=a+1; b<numVerts; ++b) {
            ofVec3f vertb = mesh.getVertex(b);
            
            float distance = verta.distance(vertb);
            if (distance <= connectionDistance) {
                mesh.addIndex(a);
                mesh.addIndex(b);
            }
        }
    }
    
    
    ofSetFrameRate(60);
    
    
    
    //ORBIT
    meshCentroid = mesh.getCentroid();
    for (int i=0; i<numVerts; ++i) {
        ofVec3f vert = mesh.getVertex(i);
        
        float distance = vert.distance(meshCentroid);
        float angle = atan2(vert.y-meshCentroid.y, vert.x-meshCentroid.x);
        
        distances.push_back(distance);
        angles.push_back(angle);
    }
    
    orbiting = false;
    startOrbitTime = 0.0;
    meshCopy = mesh;
    
    
    mouseDisplacement = false;
}

//--------------------------------------------------------------
void testApp::update(){
    
    int numVerts = mesh.getNumVertices();
    for (int i=0; i<numVerts; ++i) {
        ofVec3f vert = mesh.getVertex(i);
        
        float time = ofGetElapsedTimef();
        float timeScale = 5.0;
        float displacementScale = 0.75;
        ofVec3f timeOffsets = offset[i];
        
        vert.x += (ofSignedNoise(time*timeScale+timeOffsets.x))*displacementScale;
        vert.y += (ofSignedNoise(time*timeScale+timeOffsets.y))*displacementScale;
        vert.z += (ofSignedNoise(time*timeScale+timeOffsets.z))*displacementScale;
        
        mesh.setVertex(i, vert);
        
    }
    
    
    //ORBIT
    if (orbiting) {
        int numVerts = mesh.getNumVertices();
        for (int i=0; i<numVerts; ++i) {
            ofVec3f vert = mesh.getVertex(i);
            
            float distance = distances[i];
            float angle = angles[i];
            float elapsedTime = ofGetElapsedTimef() - startOrbitTime;
            
            float speed = ofMap(distance, 0, 200, 1, 0.25, true);
            float rotatedAngle = elapsedTime * speed + angle;
            
            vert.x = distance * cos(rotatedAngle) + meshCentroid.x;
            vert.y = distance * sin(rotatedAngle) + meshCentroid.y;
            
            mesh.setVertex(i, vert);
        }
    }
    
    //MAG
    ofVec3f mouse(mouseX, ofGetWidth()-mouseY, 0);
    
    for (int i=0; i<mesh.getNumVertices(); ++i) {
        ofVec3f vertex = meshCopy.getVertex(i);
        
        float distanceToMouse = mouse.distance(vertex);
        float displacement = ofMap(distanceToMouse, 0, 400, 300.0, 0, true);
        
        ofVec3f direction = vertex - mouse;
        direction.normalize();
        
        ofVec3f displacedVertex = vertex + displacement * direction;
        mesh.setVertex(i, displacedVertex);
    }

}

//--------------------------------------------------------------
void testApp::draw(){
//    ofBackground(250,241,232);
    ofColor centerColor = ofColor(85,78,68);
    ofColor edgeColor = ofColor(0,0,0);
//    ofBackground(255, 255, 0);
    ofBackgroundGradient(centerColor, edgeColor, OF_GRADIENT_CIRCULAR);
    
    easyCam.begin();
    ofPushMatrix();
    ofTranslate(-ofGetWidth()/2, -ofGetHeight()/2);
        mesh.draw();
//        image.draw(0, 0);
    ofPopMatrix();
    easyCam.end();

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    if (key == 'o') {
        orbiting = !orbiting;
        startOrbitTime = ofGetElapsedTimef();
        mesh = meshCopy;
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
