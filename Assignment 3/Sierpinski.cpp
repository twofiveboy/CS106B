#include "Sierpinski.h"
#include "error.h"
using namespace std;

/**
 * Draws a triangle with the specified corners in the specified window. Feel free
 * to edit this function as you see fit to change things like color, fill style,
 * etc. in whatever way you'd like!
 *
 * @param window The window in which to draw the triangle.
 * @param x0 y0 The first corner of the triangle.
 * @param x1 y1 The second corner of the triangle.
 * @param x2 y2 The third corner of the triangle.
 */
void drawTriangle(GWindow& window,
                  double x0, double y0,
                  double x1, double y1,
                  double x2, double y2) {
    window.setColor("black");
    window.fillPolygon({ x0, y0, x1, y1, x2, y2 });
}

/* TODO: Refer to Sierpinski.h for more information about what this function should do.
 * Then, delete this comment.
 */
void drawSierpinskiTriangle(GWindow& window,
                            double x0, double y0,
                            double x1, double y1,
                            double x2, double y2,
                            int order) {
    if(order < 0) error("order is less than zero");
    if(order == 0){
        drawTriangle(window,x0,y0,x1,y1,x2,y2);
    }
    else{
        double mid_x0 = (x0+x1)/2,mid_x1 = (x0+x2)/2,mid_x2 = (x1+x2)/2;
        double mid_y0 = (y0+y1)/2,mid_y1 = (y0+y2)/2,mid_y2 = (y1+y2)/2;
        drawSierpinskiTriangle(window,x0,y0,mid_x0,mid_y0,mid_x1,mid_y1,order-1);
        drawSierpinskiTriangle(window,mid_x0,mid_y0,x1,y1,mid_x2,mid_y2,order-1);
        drawSierpinskiTriangle(window,mid_x1,mid_y1,mid_x2,mid_y2,x2,y2,order-1);
    }
}
