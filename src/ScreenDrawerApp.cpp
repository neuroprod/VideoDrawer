#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/qtime/QuickTimeGl.h"
#include "MoviePlayer.hpp"
#include "LineDrawer.hpp"
#include "MovieWriter.hpp"
using namespace ci;
using namespace ci::app;
using namespace std;

class ScreenDrawerApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
    void mouseUp( MouseEvent event ) override;
    void mouseDrag( MouseEvent event ) override;
     void keyUp( KeyEvent event ) override;
	void update() override;
	void draw() override;
    void fileDrop( FileDropEvent event ) override;
    MoviePlayer player;
    LineDrawer drawer;
    bool   rendering =false;
    MovieWriter writer;
    int count =0;
    
};

void ScreenDrawerApp::setup()
{
    setWindowSize(1920, 1080);
    player.setup();
    drawer.setup();
    writer.setup();
}

void ScreenDrawerApp::mouseDown( MouseEvent event )
{
    player.mouseDown(event.getPos() );
     drawer.mouseDown(event.getPos() );
}
void ScreenDrawerApp::mouseUp( MouseEvent event )
{
    player.mouseUp(event.getPos() );
     drawer.mouseUp(event.getPos() );
}
void ScreenDrawerApp::mouseDrag( MouseEvent event )
{
    player.mouseDrag(event.getPos() );
     drawer.mouseDrag(event.getPos() );
}
void ScreenDrawerApp::keyUp( KeyEvent event )
{
    if(event.getCode()==KeyEvent::KEY_r)
    {
        count =0;
        rendering =true;
        writer.mFbo->bindFramebuffer();
        gl::clear( ColorA( 0.f, 0.f, 0.f,0.f ) );
        writer.mFbo->unbindFramebuffer();
        drawer.reset();
        writer.start();
        
    }else if(event.getCode()==KeyEvent::KEY_u)
    {
        drawer.lines.pop_back();
       
    }else if(event.getCode()==KeyEvent::KEY_c)
    {
        drawer.lines.clear();
       
    }else if(event.getCode()==KeyEvent::KEY_UP)
    {
        drawer.drawSize ++;
        
    }else if(event.getCode()==KeyEvent::KEY_DOWN)
    {
        drawer.drawSize --;
        if(drawer.drawSize<1)drawer.drawSize=1;
        
    }else if(event.getCode()==KeyEvent::KEY_n)
    {
        console()<<drawer.color.x<<"??"<<endl;
        if(drawer.color.x ==1)
        {
            drawer.color.x =0;
            drawer.color.y =0;
            drawer.color.z =0;
        }else
        {
            drawer.color.x =1;
            drawer.color.y =1;
            drawer.color.z =1;
        
        }
        
    }

};
void ScreenDrawerApp::update()
{
    player.update();
    drawer.update();
}

void ScreenDrawerApp::draw()
{
    
	gl::clear( Color( 0.5, 0.5, 0.5 ) );
   
    if(rendering)
    {
        if(!writer.mMovieExporter)
        {
        
            rendering=false;
            return;
        }
        
        writer.mFbo->bindFramebuffer();
      
        
        bool r = drawer.drawCount();
        writer.mFbo->unbindFramebuffer();
         writer.update();
        
        gl::draw( writer.mFbo->getColorTexture());
        if(r)
        {
            rendering =false;
            for(int i=0;i<100;i++)
            {
           writer.update();
            }
            writer.stop();
        
        }
    }else{
        player.draw();
        drawer.draw();
        
        ci::gl::drawString("drop video file  r:render u:undo c:clear up:+size down:-size n:togle-color",ci::vec2(0,ci::app::getWindowHeight()-10));
    }

}
void ScreenDrawerApp::fileDrop( FileDropEvent event )
{
    player.loadMovieFile( event.getFile( 0 ) );
}


CINDER_APP( ScreenDrawerApp, RendererGl )
