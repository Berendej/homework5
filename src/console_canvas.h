#ifndef _CONSOLE_CANVAS_H_
#define _CONSOLE_CANVAS_H_

#include <memory>
#include <cstdint>

#include "canvas.h"

/**
 * /brief console_canvas_c inherits from ICanvas serves as simple demo view
 * 
 * 
 */
class console_canvas_c : public ICanvas
{
    unsigned m_width;
    unsigned m_height;
    std::uint8_t *m_p_area;
public:
    console_canvas_c (unsigned width, unsigned height);
    ~console_canvas_c();
    void dot(unsigned x, unsigned y, const draw_operation pix) override;
    void render() override;
    void clear() override;


};
using sp_console_canvas_t = std::shared_ptr<console_canvas_c>;

#endif