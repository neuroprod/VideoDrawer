//
//  MovieWriter.cpp
//  ScreenDrawer
//
//  Created by Kris Temmerman on 13/03/2017.
//
//

#include "MovieWriter.hpp"
using namespace ci;

void MovieWriter::setup()
{


    gl::Fbo::Format format;
    format.setSamples( 4 ); // uncomment this to enable 4x antialiasing
  
    mFbo = gl::Fbo::create( app::getWindowWidth(), app::getWindowHeight(), format.colorTexture() );

   isStarted =false;
}
void MovieWriter::start()
{
    isStarted =true;
    
    fs::path path = app::getSaveFilePath();
    if( ! path.empty() ) {
        auto format = qtime::MovieWriter::Format().codec( qtime::MovieWriter::PRO_RES_4444).fileType( qtime::MovieWriter::QUICK_TIME_MOVIE);
     
        mMovieExporter = qtime::MovieWriter::create( path, app::getWindowWidth(), app::getWindowHeight(), format );
    }


};

void MovieWriter::update()
{
 

    mMovieExporter->addFrame(ci::Surface( mFbo->getColorTexture()->createSource()));
    
   /* else if( mMovieExporter && getElapsedFrames() >= maxFrames ) {
        mMovieExporter->finish();
        mMovieExporter.reset();*/
   // */


}
void MovieWriter::stop()
{
    mMovieExporter->finish();
    mMovieExporter.reset();
}

