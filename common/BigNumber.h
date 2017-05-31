#pragma once

#include "ofMain.h"

class BigNumber{
    
    
public:
    
    float num;
    float exp;
    
    void setFromExp(float _exp){
        exp = _exp;
        num = pow(10, exp);
    }
    
    void setFromNum(float _num){
        num = _num;
        exp = log10(num);
    }
    
    string getExp(){
        return ofToString(exp, 0);
    }
    
    string getNum(int precision=0){
        return ofToString(num, precision);
    }

};
