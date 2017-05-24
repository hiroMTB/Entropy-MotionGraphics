#pragma once

#include "ofMain.h"

namespace ScreenGuide{
    
    const static float renderW = 3840;
    const static float renderH = 1080;
    
    const static ofRectangle safeAreaL(renderW*0.1679, renderH*0.243, renderW*0.2128, renderH*0.633);
    const static ofRectangle safeAreaR(renderW*0.6184, renderH*0.243, renderW*0.2128, renderH*0.633);
    
};
