//
//  MovieWriter.hpp
//  ScreenDrawer
//
//  Created by Kris Temmerman on 13/03/2017.
//
//

#ifndef MovieWriter_hpp
#define MovieWriter_hpp

#include "cinder/qtime/AvfWriter.h"
class MovieWriter
{
    
public:
    MovieWriter(){}
    void setup();
     void start();
    void update();
     void stop();
    ci::qtime::MovieWriterRef mMovieExporter;
    ci::gl::FboRef	mFbo;
    bool isStarted=false;
};
#endif /* MovieWriter_hpp */
