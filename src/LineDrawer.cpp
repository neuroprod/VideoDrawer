//
//  LineDrawer.cpp
//  ScreenDrawer
//
//  Created by Kris Temmerman on 13/03/2017.
//
//

#include "LineDrawer.hpp"

using namespace ci::app;
using namespace std;


void LineDrawer::setup()
{
    color.x=0;
    color.y=0;
    color.z=0;
    drawSize=10;

    mGlsl = cinder::gl::GlslProg::create( cinder::gl::GlslProg::Format()
                                 .vertex(	CI_GLSL( 150,
                                                    uniform mat4	ciModelViewProjection;
                                                    in vec4			ciPosition;
                                                    
                                                    void main( void ) {
                                                        gl_Position	= ciModelViewProjection * ciPosition;
                                                    }
                                                    ) )
                                 .fragment(	CI_GLSL( 150,
                                                    uniform vec3		drawColor;
                                                    out vec4			oColor;
                                                   
                                                    void main( void ) {
                                                        vec2 uv = gl_PointCoord.xy * 2. - 1.;
                                                     
                                                        float l = min(length(uv), 1.);
                                                        float brightness = smoothstep(0.0, 0.4, 1-l);
                                                        oColor = vec4( drawColor.x, drawColor.y , drawColor.z, brightness);
                                                    }
                                                    ) ) );
    

    
}

void LineDrawer::update()
{

}



void LineDrawer::mouseDown( ci::vec2 pos)
{
    if(pos.y>20)
    {
        currentLine = lLine::create();
        currentLine->addPoint(pos);
        lines.push_back(currentLine);
        drawing =true;
    }
}

void LineDrawer::mouseUp( ci::vec2 pos)
{
    if(drawing){
        currentLine->addPoint(pos);
        drawing =false;
    }
}
void LineDrawer::mouseDrag( ci::vec2 pos)
{
    if(drawing){
        currentLine->addPoint(pos);
    }
}




void LineDrawer::draw()
{
    ci::gl::ScopedGlslProg prog(mGlsl);
    mGlsl->uniform("drawColor", color);
    cinder::gl::pointSize(drawSize);//10
    for(auto l:lines )
    {
        l->draw();
    }
 }
void LineDrawer::reset()
{
    lineIndex =0;
    bolIndex =0;

}
bool LineDrawer::drawCount()
{
    ci::gl::ScopedGlslProg prog(mGlsl);
    mGlsl->uniform("drawColor", color);
    cinder::gl::pointSize(drawSize);//10

    ci::gl::disableDepthRead();
    ci::gl::enableAlphaBlendingPremult();
    for(int i=0;i<20;i++){
    if(lineIndex>=lines.size()) return true;
    if(bolIndex>=lines[lineIndex]->points.size() )
    {
        bolIndex =0;
        lineIndex++;
        return false;
    }

    ci::vec2 point=lines[lineIndex]->points[bolIndex];
    ci::gl::begin(GL_POINTS);
    ci::gl::vertex(point.x, point.y);
    ci::gl::end();
    bolIndex++;
    }
    return false;
}
