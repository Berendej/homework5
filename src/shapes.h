#ifndef _SHAPES_H_
#define _SHAPES_H_

#include <memory>
#include <vector>
#include <fstream>

#include "definitions.h"
#include "canvas.h"

/**
 * /brief shape_c root of shapes hierarhy
 * 
 */
class shape_c
{
    public:
        virtual void draw(sp_ICanvas_t sp_canvas, const draw_operation pix) const = 0;
        virtual void serialize(std::ofstream &ofs) const = 0;
        virtual void deserialize(std::istream &ifs) = 0;
        virtual std::string to_string() const = 0;
        static constexpr unsigned int shape_id = 0;
};
using sp_shape_t = std::shared_ptr<shape_c>;
using shape_vector_t = std::vector<sp_shape_t>;
using i_shape_vector_t = shape_vector_t::iterator;

class line_c : public shape_c
{
    unsigned m_start_x;
    unsigned m_start_y;
    unsigned m_end_x;
    unsigned m_end_y;
    public:
        line_c(int sx, int sy, int ex, int ey );
        line_c();
        void draw(sp_ICanvas_t sp_canvas, const draw_operation pix) const override;
        void serialize(std::ofstream &ofs) const;
        void deserialize(std::istream &ifs);
        std::string to_string() const;
        static constexpr unsigned int shape_id = shape_c::shape_id + 1;
};

class rectangle_c : public shape_c
{
    unsigned m_x;
    unsigned m_y;
    unsigned m_width;
    unsigned m_height;
    public:
        rectangle_c(int x, int y, int w, int h);
        rectangle_c();

        void draw(sp_ICanvas_t sp_canvas, const draw_operation pix) const override;
        void serialize(std::ofstream &ofs) const;
        void deserialize(std::istream &ifs);
        std::string to_string() const;
        static constexpr unsigned int shape_id = line_c::shape_id + 1;
};

class circle_c : public shape_c
{
    unsigned m_x;
    unsigned m_y;
    unsigned m_radius;
    public:
        circle_c(int x, int y, int r);
        circle_c();

        void draw(sp_ICanvas_t sp_canvas, const draw_operation pix) const override;
        void serialize(std::ofstream &ofs) const;
        void deserialize(std::istream &ifs);
        std::string to_string() const;
        static constexpr unsigned int shape_id = rectangle_c::shape_id + 1;
};

sp_shape_t deserialize(std::istream &ifs);

#endif // ifndef _SHAPES_H_