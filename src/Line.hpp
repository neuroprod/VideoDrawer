//
//  Line.hpp
//  ScreenDrawer
//
//  Created by Kris Temmerman on 13/03/2017.
//
//

#ifndef Line_hpp
#define Line_hpp
#include "cinder/app/App.h"
#include "cinder/gl/gl.h"

class lLine;

typedef std::shared_ptr<lLine> LineRef;


class lLine
{
public:
    lLine(){};
    
    static LineRef create();
    
    void draw();
    void addPoint(ci::vec2 point);
    std::vector<ci::vec2> points;
    cinder::gl::VboRef		mPPositions;
    cinder::gl::VboMeshRef mesh;
};
#endif /* Line_hpp */
