//
//  LineDrawer.hpp
//  ScreenDrawer
//
//  Created by Kris Temmerman on 13/03/2017.
//
//

#ifndef LineDrawer_hpp
#define LineDrawer_hpp
#include "cinder/app/App.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/GlslProg.h"
#include "Line.hpp"

class LineDrawer
{

public:
    LineDrawer(){}
    void setup();
    
    void update();
    void reset();
    void draw();
     bool drawCount();
    void mouseDown( ci::vec2 pos);
    
    void mouseUp( ci::vec2 pos);
    void mouseDrag( ci::vec2 pos);
    LineRef currentLine;
    std::vector< LineRef> lines;
    ci::gl::GlslProgRef		mGlsl;
    bool drawing =false;
    int lineIndex =0;
     int bolIndex =0;
};
#endif /* LineDrawer_hpp */
