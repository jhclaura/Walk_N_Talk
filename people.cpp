//
//  people.cpp
//  walk_talk
//
//  Created by Laura JH Chen on 4/25/14.
//
//

#include "people.h"

people::people(float _posX, float _posY){
    
    position.x = _posX;
    position.y = _posY;
    
    vector<ofColor> cs;
    cs.push_back(ofColor(51, 205, 199));
    cs.push_back(ofColor(0, 101, 97));
    cs.push_back(ofColor(255, 169, 0));
    cs.push_back(ofColor(253, 0 ,6));
    cs.push_back(ofColor(0,253, 247));
    
    c = cs[ (int)ofRandom(0,6) ];
    
    ppl.setMode(OF_PRIMITIVE_LINE_LOOP);
    
    
    for (int i=0; i<verticesNum; i++) {
        
        float posX( position.x + sin((360/verticesNum*i)*(pi/180))*radius );
        float posY( position.y + sin(pi/2 + (360/verticesNum*i)*(pi/180))*radius);
        ofVec3f pos(posX, posY, 0);
        
        ppl.addVertex(pos);
        ppl.addColor( c );
        
    }
    
}


void people::update(float _x, float _y){
    
    ofVec3f mouse(_x, _y, 0);
    
    for (int i=0; i<ppl.getNumVertices(); i++) {
        
        ofVec3f vertex = ppl.getVertex(i);
        float distanceToMouse = mouse.distance(vertex);
        
        if(distanceToMouse < 50.0){
            
            ofVec3f direction = vertex - mouse;
            direction.normalize();
            
            ofVec3f displacedVertex = vertex + 20 * direction;
            ppl.setVertex(i, displacedVertex);
        }
    }
}

void people::draw(){
    ppl.draw();
}


ofVec3f people::getPos(){
    return position;
}



