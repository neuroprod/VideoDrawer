//
//  Line.cpp
//  ScreenDrawer
//
//  Created by Kris Temmerman on 13/03/2017.
//
//

#include "Line.hpp"
using namespace ci;
using namespace std;
LineRef lLine::create()
{

    return std::make_shared<lLine>();
}

void lLine::addPoint(ci::vec2 point)
{

    if(points.size()>1)
    {
    
        vec2 lastPoint =points[points.size()-1];
        float dist =glm::distance(point, lastPoint);
        int   numSteps =round( dist);
        if (numSteps< 5)return;
        if(numSteps<2){
        points.push_back(point);
        }
        else
        {
            for (int i=1;i< numSteps;i++)
            {
                float pos = 1.0f/numSteps *i;
                points.push_back(glm::mix(lastPoint,point,pos));
            
            }
        
        }
        
    }else
    {
    
      points.push_back(point);
    }
    
   
    
    mPPositions = ci::gl::Vbo::create( GL_ARRAY_BUFFER, points.size() * sizeof(ci::vec2), points.data(), GL_STATIC_DRAW );
  
    
    
    ci::geom::BufferLayout particleLayout;
    particleLayout.append(  ci::geom::Attrib::POSITION, 2, sizeof(  points ), 0);
    mesh = cinder::gl::VboMesh::create(  points.size(), GL_POINTS, { { particleLayout,mPPositions } } );

  
   

}
void lLine::draw()
{
    
    gl::pointSize(12);
    gl::draw(mesh);

}
