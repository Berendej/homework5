#include "graphdoc.h"
#include "console_canvas.h"

using namespace std;

void demo()
{
    sp_ICanvas_t sp_canvas{new console_canvas_c(50, 20)};
    {
        sp_graph_doc_t sp_doc( new graph_doc_c() );
        sp_doc->subscribe_canvas(sp_canvas);
        sp_doc->add_rectangle(0, 0, 5, 5);
        sp_doc->add_line(7, 7, 35, 15);
        sp_doc->add_circle(10, 10, 7);
        sp_doc->render();
        sp_doc->save_as("new_doc.txt");
    }
    {
        sp_graph_doc_t sp_doc( new graph_doc_c("new_doc.txt") );
        sp_doc->subscribe_canvas(sp_canvas);
        sp_doc->add_circle(5, 10, 3);
        sp_doc->render();
        sp_doc->save_as("new_doc2.txt");
    }
}
