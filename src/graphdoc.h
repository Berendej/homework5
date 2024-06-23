#ifndef _GRAPHDOC_H_
#define _GRAPHDOC_H_

#include <vector>
#include <string>
#include <memory>
#include "shapes.h"
#include "canvas.h"

/**
 * /brief graph_doc_c serves as a MODEL in  model-view-controller paradigm
 *
 * 
 */
class graph_doc_c
{
    std::string m_file_name;
    shape_vector_t m_shapes;
    canvas_list_t m_subscribers; 
    void add_shape( shape_c * p_shape);
public:
    void save();
    void save_as(const std::string &new_file_name);
    graph_doc_c(const std::string &file_name);
    graph_doc_c();

    void add_line(int sx, int sy, int ex, int ey );
    void add_rectangle(int x, int y, int w, int h );
    void add_circle(int x, int y, int r );
    void render();
    void draw_shape(sp_shape_t sp_shape);
    void clear_shape(sp_shape_t sp_shape);
    void subscribe_canvas(sp_ICanvas_t sp);
    void un_subscribe_canvas(sp_ICanvas_t sp);
    void remove_shape(const unsigned index);
    std::string string_content() const;
};
using sp_graph_doc_t = std::shared_ptr<graph_doc_c>;

#endif // ifndef _GRAPHDOC_H_