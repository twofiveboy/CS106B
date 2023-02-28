#include "Plotter.h"
#include "strlib.h"
using namespace std;

void runPlotterScript(istream& input) {
    bool isup = true;
    PenStyle style = {1 , "red"};
    double x1=0,y1=0,x2,y2;
    string op; //operator
    for (string line; getline(input,line);) {
        Vector<string>cmd = stringSplit(line," ");
        op = toLowerCase(cmd[0]);
        if (op == "pendown") {
            isup = false;
        }
        else if (op == "penup") {
            isup = true;
        }
        else if (op == "moveabs") {
            x2 = stringToReal(cmd[1]);
            y2 = stringToReal(cmd[2]);
            if (!isup) drawLine(x1, y1, x2, y2, style);
            x1 = x2; y1 = y2;
        }
        else if (op == "moverel") {
            x2 = x1 + stringToReal(cmd[1]);
            y2 = y1 + stringToReal(cmd[2]);
            if (!isup) drawLine(x1, y1, x2, y2, style);
            x1 = x2; y1 = y2;
        }
        else if (op == "pencolor") {
            style.color = cmd[1];
        }
        else if (op == "penwidth") {
            style.width = stringToReal(cmd[1]);
        }


    }
    return ;
}
