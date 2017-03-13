//
//  MoviePlayer.hpp
//  ScreenDrawer
//
//  Created by Kris Temmerman on 13/03/2017.
//
//

#ifndef MoviePlayer_hpp
#define MoviePlayer_hpp
#include "cinder/app/App.h"
#include "cinder/gl/gl.h"
#include "cinder/qtime/QuickTimeGl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class MoviePlayer
{

public:
    void setup();
  
    void update();
    
    void draw();
   
    gl::TextureRef			mFrameTexture;
    qtime::MovieGlRef		mMovie;
    void loadMovieFile( const fs::path &moviePath );
    void mouseDown( vec2 pos);
   
    void mouseUp( vec2 pos);
    void mouseDrag( vec2 pos);
    float  totalTime;
    float positionPers;
    bool down;


};

#endif /* MoviePlayer_hpp */
