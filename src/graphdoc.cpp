#include <fstream>
#include <algorithm>
#include <string>
#include <sstream>
#include <iostream>

#include "graphdoc.h"

using namespace std;

void graph_doc_c::save()
{
    ofstream ofs(m_file_name);
    for_each(m_shapes.begin(),
                  m_shapes.end(),
                  [&](sp_shape_t sp) { sp->serialize(ofs); } );
    ofs.close();
}

void graph_doc_c::save_as(const string &new_file_name)
{
    m_file_name = new_file_name;
    save();
}

graph_doc_c::graph_doc_c(const string &file_name) : m_file_name (file_name)
{
    #define MAX_STR_LEN 100

    ifstream ifs(m_file_name);
    if ( not ifs )
    {
        return; // so far is empty
    }
    string line;
    char buf[MAX_STR_LEN];
    while(ifs.getline(buf, MAX_STR_LEN))
    {
        line = buf;
        istringstream istr(line);
        sp_shape_t sp_shape = deserialize(istr);
        m_shapes.push_back(sp_shape);
    }
    ifs.close();
}

graph_doc_c::graph_doc_c()
{
}

void graph_doc_c::remove_shape(const unsigned index)
{
    sp_shape_t sp_shape = m_shapes[index];
    clear_shape(sp_shape); // notify all subscribers this shape
                           // doesn't exist anymore
    m_shapes.erase(m_shapes.begin() + index);
}

void graph_doc_c::add_shape( shape_c * p_shape)
{
    sp_shape_t sp_shape(p_shape);
    m_shapes.push_back( sp_shape );
    draw_shape(sp_shape);
}

void graph_doc_c::add_line(int sx, int sy, int ex, int ey )
{
    add_shape(new line_c(sx, sy, ex, ey));
}

void graph_doc_c::add_rectangle(int x, int y, int w, int h )
{
    add_shape(new rectangle_c(x, y, w, h));
}

void graph_doc_c::add_circle(int x, int y, int r )
{
    add_shape(new circle_c(x, y, r));
}

void graph_doc_c::render() 
{
    std::for_each(m_subscribers.begin(), 
                  m_subscribers.end(),
                  [] (sp_ICanvas_t &sp_canvas) { sp_canvas->render(); });
}


void graph_doc_c::draw_shape(sp_shape_t sp_shape)
{
    std::for_each(m_subscribers.begin(), 
                  m_subscribers.end(),
                  [&] (sp_ICanvas_t &sp_canvas) { sp_shape->draw(sp_canvas, draw_operation::set_pix); });
}

void graph_doc_c::clear_shape(sp_shape_t sp_shape)
{
    std::for_each(m_subscribers.begin(), 
                  m_subscribers.end(),
                  [&] (sp_ICanvas_t &sp_canvas) { sp_shape->draw(sp_canvas, draw_operation::erase_pix); });
}

void graph_doc_c::subscribe_canvas(sp_ICanvas_t sp_canvas)
{
    sp_canvas->clear();
    m_subscribers.push_back(sp_canvas);
    std::for_each(m_shapes.begin(),
                  m_shapes.end(),
                  [&]( sp_shape_t sp_shape) { sp_shape->draw(sp_canvas, draw_operation::set_pix); });
}

void graph_doc_c::un_subscribe_canvas(sp_ICanvas_t sp)
{
    i_canvas_list_t it = m_subscribers.begin();
    while( it != m_subscribers.end() )
    {
        if ( sp == (*it) )
        {
            m_subscribers.erase(it);
            return;
        }
    }
}

string graph_doc_c::string_content() const
{
    unsigned index = 0;
    std::ostringstream buffer; 
    std::for_each(m_shapes.begin(), 
                  m_shapes.end(),
                  [&] (const sp_shape_t &sp_shape) 
                  {
                    buffer << index++ << " " << sp_shape->to_string() << endl;  
                  });
    return buffer.str();
}

