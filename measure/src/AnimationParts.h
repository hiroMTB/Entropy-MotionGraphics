#pragma once


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
