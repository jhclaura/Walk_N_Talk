//
//  people.h
//  walk_talk
//
//  Created by Laura JH Chen on 4/25/14.
//
//

#ifndef __walk_talk__people__
#define __walk_talk__people__

#include <iostream>
#include "ofMain.h"

using namespace std;

class people{
    
public:
    people(float _posX, float _posY);
    
//    void create(float _x, float _y);
    void update(float _x, float _y);
    void draw();
    ofVec3f getPos();
    
    ofMesh ppl;
    ofColor c;
    ofVec3f position;
    int verticesNum = 40;
    float radius = 60;
};



#endif /* defined(__walk_talk__people__) */
