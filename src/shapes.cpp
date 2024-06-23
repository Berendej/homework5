#include <fstream>
#include <iostream>
#include <sstream>

#include "definitions.h"
#include "shapes.h"

using namespace std;

line_c::line_c(int sx, int sy, int ex, int ey )
:  m_start_x(sx), m_start_y(sy), m_end_x(ex), m_end_y(ey)
{
}

line_c::line_c()
:  m_start_x(1), m_start_y(1), m_end_x(2), m_end_y(2)
{
}

void line_c::draw(sp_ICanvas_t sp_canvas, const draw_operation pix) const
{
     int deltax = abs((int)m_end_x - (int)m_start_x);
     int deltay = abs((int)m_end_y - (int)m_start_y);
     float error = 0;
     float deltaerr = (deltay + 1) / (deltax + 1);
     int y = m_start_y;
     int diry = m_end_y - m_start_y;
     if (diry > 0)
         diry = 1;
     if (diry < 0)
         diry = -1;
     for( int x = m_start_x; x <=  m_end_x; x++ )
     {
         sp_canvas->dot(x, y, pix);
         error += deltaerr;
         if (error >= 1.0)
         {
             y += diry;
             error -=  1.0;
         }
     }
}

void line_c::serialize(std::ofstream &ofs) const
{
    ofs << line_c::shape_id << " "
        << m_start_x << " "
        << m_start_y << " "
        << m_end_x << " "
        << m_end_y << std::endl;
}

void line_c::deserialize(std::istream &ifs)
{
    // typeid was already ate
    ifs >> m_start_x >> m_start_y >> m_end_x >> m_end_y;
}

std::string line_c::to_string() const
{
    std::ostringstream buffer; 
    buffer << "line "<< m_start_x << " " << m_start_y 
           <<  " "    << m_end_x   << " " << m_end_y;
    return buffer.str();    
}


rectangle_c::rectangle_c(int x, int y, int w, int h)
: m_x(x), m_y(y), m_width(w), m_height(h)
{
}

rectangle_c::rectangle_c()
: m_x(1), m_y(1), m_width(1), m_height(1)
{
}

std::string rectangle_c::to_string() const
{
    std::ostringstream buffer; 
    buffer << "rectangle "<< m_x << " " << m_y 
           <<  " "    << m_width   << " " << m_height;
    return buffer.str();    
}

void rectangle_c::draw(sp_ICanvas_t sp_canvas, const draw_operation pix) const
{
    for( int x = m_x; x < m_x + m_width; x++ )
    {
        sp_canvas->dot(x, m_y, pix);
        sp_canvas->dot(x, m_y + m_height, pix);
    }
    for( int y = m_y; y < m_y + m_height; y++ )
    {
        sp_canvas->dot(m_x, y, pix);
        sp_canvas->dot(m_x+m_width, y, pix);
    }
}

void rectangle_c::serialize(std::ofstream &ofs) const
{
    ofs << rectangle_c::shape_id << " "
        << m_x << " "
        << m_y << " "
        << m_width << " "
        << m_height << std::endl;
}

void rectangle_c::deserialize(std::istream &ifs)
{
    // typeid was already ate
    ifs >> m_x >> m_y >> m_width >> m_height;
}

circle_c::circle_c(int x, int y, int r)
  : m_x(x), m_y(y), m_radius(r)
{
}

circle_c::circle_c()
  : m_x(1), m_y(1), m_radius(1)
{
}

std::string circle_c::to_string() const
{
    std::ostringstream buffer; 
    buffer << "circle "<< m_x << " " << m_y 
           <<   " "    << m_radius;
    return buffer.str();    
}

void aux_draw_circle(sp_ICanvas_t sp_canvas, 
                       int xc, int yc, 
                       int x, int y,
                       const draw_operation pix)
{
    sp_canvas->dot(xc+x, yc+y, pix);
    sp_canvas->dot(xc-x, yc+y, pix);
    sp_canvas->dot(xc+x, yc-y, pix);
    sp_canvas->dot(xc-x, yc-y, pix);
    sp_canvas->dot(xc+y, yc+x, pix);
    sp_canvas->dot(xc-y, yc+x, pix);
    sp_canvas->dot(xc+y, yc-x, pix);
    sp_canvas->dot(xc-y, yc-x, pix);
}

//void circleBres(int xc, int yc, int r)
void circle_c::draw(sp_ICanvas_t sp_canvas, const draw_operation pix) const
{
    int x = 0;
    int y = m_radius;
    int d = 3 - 2 * m_radius;
    aux_draw_circle(sp_canvas, m_x, m_y, x, y, pix);
    while (y >= x)
    {
        x++;
        if (d > 0)
        {
            y--; 
            d = d + 4 * (x - y) + 10;
        }
        else
            d = d + 4 * x + 6;
        aux_draw_circle(sp_canvas, m_x, m_y, x, y, pix);
    }
}

void circle_c::serialize(std::ofstream &ofs) const
{
    ofs << circle_c::shape_id << " "
        << m_x << " "
        << m_y << " "
        << m_radius << std::endl;
}

void circle_c::deserialize(std::istream &ifs)
{
    // typeid was already ate
    ifs >> m_x >> m_y >> m_radius;
}

sp_shape_t deserialize(std::istream &ifs)
{
    sp_shape_t sp_shape;
    int type;
    ifs >> type;
    switch(type)
    {
        case line_c::shape_id:
            sp_shape.reset(new line_c());
            break;
        case rectangle_c::shape_id:
            sp_shape.reset(new rectangle_c());
            break;
        case circle_c::shape_id:
            sp_shape.reset(new circle_c());
            break;
    }
    if ( sp_shape )
    {
        sp_shape->deserialize(ifs);
    }
    return sp_shape;
}
