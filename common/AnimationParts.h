#pragma once

#include "ofMain.h"

struct AnimText{
    
public:
    string t;
    string tshow;
    float tpos;
    float a;
    float movex;
    float movey;
    
    AnimText(){
        reset();
    }
    
    void update(){
        int pos = t.size() * tpos;
        tshow = t.substr(0, pos);
    }
    
    void reset(){
        t = "";
        tpos = 0;
        a = 1;
        movex = 0;
        movey = 0;
    }
};

struct AnimPoint{

    AnimPoint(){
        reset();
    }
    
    ofPoint p;
    float w;
    float a;
    void reset(){
        p.set(0,0);
    }
};

struct AnimLine{
    
public:
    AnimLine(){
        reset();
    }
    
    ofPoint p1, p2;
    float w;
    float a;
    void reset(){
        p1.set(0,0);
        p2.set(0,0);
        w = 5;
        a = 0;
    }
};

struct AnimCircle{

public:
    
    AnimCircle(){
        reset();
    }
    
    ofPoint center;
    float rad;
    float w;
    float a;

    void reset(){
        center.set(0,0);
        rad = 0;
        w = 5;
        a = 0;
    }
};


struct AnimArc{
    
public:
    AnimArc(){
        reset();
    }
    
    ofPoint center;
    float rad;
    float start, end;
    float w;
    float a;
    float angle;
    
    void reset(){
        center.set(0,0);
        rad = 0;
        start = 0;
        end = 0;
        w = 5;
        a = 0;
    }
};

struct AnimRect{

public:
    AnimRect(){
        reset();
    }
    ofRectangle rect;
    float w;
    float a;
    
    void reset(){
        rect.x = 0;
        rect.y = 0;
        rect.width = 0;
        rect.height = 0;
        w = 5;
        a = 0;
    }
};

struct AnimTriangle{

public:
    AnimTriangle(){
        reset();
    }
    
    ofPoint p1, p2, p3;
    float w;
    float a;
    
    void reset(){
        p1.set(0,0);
        p2.set(0,0);
        p3.set(0,0);
        w = 0;
        a = 0;
    }
};


