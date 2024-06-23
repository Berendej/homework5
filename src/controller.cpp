#include <iostream>
#include <string>

#include "graphdoc.h"
#include "console_canvas.h"

using namespace std;

void editor_control()
{
    const string hlp{"h-help d-create doc s-save l-add line r-add rect c-add circle\n"
                     "q-quit e-render s-save o-open x-erase shape\n"};
    sp_ICanvas_t sp_canvas{new console_canvas_c(50, 25)};
    sp_graph_doc_t sp_doc;
    cout << hlp;
    char c;
    unsigned ix;
    bool quit = false;
    string file_name;
    while( not quit )
    {
        cin >> c;

        switch(c)
        {
        case 'h': 
            cout << hlp;
            break;
        case 'q':
            quit = true;
            break;
        case 'd':
        case 'o':
            if ( sp_doc )
            {
                sp_doc->save();
            }
            cout << "enter file name\n";
            cin >> file_name;
            sp_doc.reset(new graph_doc_c(file_name));
            sp_doc->subscribe_canvas(sp_canvas);
            break;
        case 'l':
            if ( sp_doc )
            {
                sp_doc->add_line(2, 2, 10, 10);
            }
            break;
        case 'r':
            if ( sp_doc )
            {
                sp_doc->add_rectangle(12, 12, 10, 10);
            }
            break;
        case 'c':
            if ( sp_doc )
            {
                sp_doc->add_circle(12, 12, 10);
            }
            break;
        case 'e':
            sp_canvas->render();
            break;
        case 's':
            sp_doc->save();
            break;
        case 'x':
            if ( sp_doc )
            {
                cout << sp_doc->string_content();
                cout << "enter shape index to remove\n";
                cin >> ix;
                sp_doc->remove_shape(ix);
            }
        }
    }
}