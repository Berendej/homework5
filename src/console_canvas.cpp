#include <iostream>
#include "console_canvas.h"

using std::cout;

console_canvas_c::console_canvas_c (unsigned width, unsigned height) : 
        m_width(width),
        m_height(height)
{
    m_p_area = new uint8_t[m_width * m_height];
}

console_canvas_c::~console_canvas_c()
{
    delete [] m_p_area;
}

void console_canvas_c::dot(unsigned x, unsigned y, const draw_operation pix) 
{
    if ( x < m_width and 
         y < m_height )
    {
        // put a dot in x,y 
        if ( draw_operation::set_pix == pix )
        {
            m_p_area[y*m_width + x] = true;
        }
        else // erase pixel
        {
            m_p_area[y*m_width + x] = false;
        }
    }
};

void console_canvas_c::clear()
{
    for( unsigned ix =0 ; ix < m_width * m_height; ix++ )
    {
        m_p_area[ix] = false;
    }
}

void console_canvas_c::render()
{
    cout << "render\n";
    unsigned x;
    unsigned y = 0;
    std::string line;
    while( y < m_height )
    {
        line.clear();
        x = 0;
        while( x < m_width )
        {
            if ( m_p_area[y*m_width + x] )
            {
                line.push_back('*');
            }
            else
            {
                line.push_back('.');
            }
            x++;
        }
        line.push_back('\n');
        cout << line;
        y++;
    }
} 
