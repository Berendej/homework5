#ifndef _CANVAS_H_
#define _CANVAS_H_

#include <memory>
#include <list>

#include "definitions.h"

/**
 * /brief ICanvas serves as a VIEW in  model-view-controller paradigm
 * 
 */
class ICanvas
{
public:
    virtual void dot(unsigned x, unsigned y, const draw_operation pix) = 0;
    virtual void render() = 0;
    virtual void clear() = 0;
};
using sp_ICanvas_t = std::shared_ptr<ICanvas>;
using canvas_list_t = std::list<sp_ICanvas_t>;
using i_canvas_list_t = canvas_list_t::iterator;

#endif