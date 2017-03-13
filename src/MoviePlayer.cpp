//
//  MoviePlayer.cpp
//  ScreenDrawer
//
//  Created by Kris Temmerman on 13/03/2017.
//
//

#include "MoviePlayer.hpp"

void MoviePlayer::setup()
{
    fs::path moviePath = getAssetPath("movie.MOV");
    if( ! moviePath.empty() )
        loadMovieFile( moviePath );
    
    down  =false;

}

void MoviePlayer::update()
{

    if( mMovie )
        mFrameTexture = mMovie->getTexture();

}
void MoviePlayer::draw()
{

   
    if( mFrameTexture ) {
        
        
        
        Rectf centeredRect = Rectf( mFrameTexture->getBounds() ).getCenteredFit( getWindowBounds(), true );
        gl::draw( mFrameTexture, centeredRect );
        gl::enableAlphaBlending(true);
        gl::color(0,0,0,0.1);
        gl::drawSolidRect(Rectf(0,0,getWindowWidth()*1.1,20));
        gl::color(1,1,1,0.3);
        gl::drawSolidRect(Rectf(0,0,getWindowWidth()*positionPers,20));
        gl::enableAlphaBlending(false);
        gl::color(1,1,1,1);
    }
    
}
void MoviePlayer::mouseDown( vec2 pos)
{
    if(mMovie)
    {
        if(pos.y<=20)
        {
            positionPers =  (float)pos.x/(float)getWindowWidth() ;
            float position  =positionPers*totalTime;
            mMovie->seekToTime(position);
            down =true;
        }
    }

}
void MoviePlayer::mouseUp( vec2 pos)
{
    down =false;
}
void MoviePlayer::mouseDrag( vec2 pos)
{
    if(down && mMovie)
    {
        positionPers =  (float)pos.x/(float)getWindowWidth() ;
        float position  =positionPers*totalTime;
        mMovie->seekToTime(position);
    }

}
void MoviePlayer::loadMovieFile( const fs::path &moviePath ){
    try {
    // load up the movie, set it to loop, and begin playing
        mMovie = qtime::MovieGl::create( moviePath );
        // mMovie->setLoop();
        //mMovie->play();
        totalTime = mMovie->getDuration();
        mMovie->seekToFrame(0);
        mMovie->getWidth();
        mMovie->getHeight();
    }
    catch( ci::Exception &exc ) {
        console() << "Exception caught trying to load the movie from path: " << moviePath << ", what: " << exc.what() << std::endl;
        mMovie.reset();
    }
    
    mFrameTexture.reset();
}
