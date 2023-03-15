#include "HumanPyramids.h"
#include "error.h"
#include "map.h"
#include "grid.h"
using namespace std;

/* TODO: Refer to HumanPyramids.h for more information about what this function should do.
 * Then, delete this comment.
 */
bool inBound(int row, int col, int pyramidHeight){
    if(row < 0 || col <0 || pyramidHeight < 0) return false;
    else if(col > row) return false;
    else if(row > pyramidHeight -1 || col >= pyramidHeight) return false;  //一样的判断条件
    return true;

}
double weightOnBackOfHelper(int row, int col,Grid<double>& table){
    if(row == 0 && col == 0) return 0.0;
    else if(table[row][col] !=0) return table[row][col]; //不为0即已经收录
    else{
        if(col == 0) {
            table[row][col] = 80.0 + weightOnBackOfHelper(row-1,0,table)/2;
            return  table[row][col];
        }
        else if(row == col) {
            table[row][col] = 80.0 + weightOnBackOfHelper(row-1,col-1,table)/2;
            return table[row][col];
        }
        else{
            table[row][col] = 160.0 + (weightOnBackOfHelper(row-1,col,table)+weightOnBackOfHelper(row-1,col-1,table))/2 ;
            return table[row][col];
        }
    }
//    if(row == 0 && col == 0) return 0.0;
//    else if(col == 0) return 80.0 + weightOnBackOf(row-1,0,pyramidHeight)/2;
//    else if(row == col) return 80.0 + weightOnBackOf(row-1,col-1,pyramidHeight)/2;
//    else return 160.0 + (weightOnBackOf(row-1,col,pyramidHeight)+weightOnBackOf(row-1,col-1,pyramidHeight))/2;
}
double weightOnBackOf(int row, int col, int pyramidHeight) {
    /* TODO: Delete the next few lines and implement this function. */
    if(!inBound(row,col,pyramidHeight)) error("out of bounds");
    Grid<double>table(pyramidHeight,pyramidHeight);
    //初始化table
    table.fill(0);
    return weightOnBackOfHelper(row,col,table);
}






/* * * * * * Test Cases * * * * * */
#include "GUI/SimpleTest.h"

/* TODO: Add your own tests here. You know the drill - look for edge cases, think about
 * very small and very large cases, etc.
 */














/* * * * * * Test cases from the starter files below this point. * * * * * */

PROVIDED_TEST("Check Person E from the handout.") {
    /* Person E is located at row 2, column 1. */
    EXPECT_EQUAL(weightOnBackOf(2, 1, 5), 240);
}

PROVIDED_TEST("Function reports errors in invalid cases.") {
    EXPECT_ERROR(weightOnBackOf(-1, 0, 10));
    EXPECT_ERROR(weightOnBackOf(10, 10, 5));
    EXPECT_ERROR(weightOnBackOf(-1, 10, 20));
}

PROVIDED_TEST("Stress test: Memoization is implemented (should take under a second)") {
    /* TODO: Yes, we are asking you to make a change to this test case! Delete the
     * line immediately after this one - the one that starts with SHOW_ERROR - once
     * you have implemented memoization to test whether it works correctly.
     */
    //SHOW_ERROR("This test is configured to always fail until you delete this line from\n         HumanPyramids.cpp. Once you have implemented memoization and want\n         to check whether it works correctly, remove the indicated line.");

    /* Do not delete anything below this point. :-) */

    /* This will take a LONG time to complete if memoization isn't implemented.
     * We're talking "heat death of the universe" amounts of time. :-)
     *
     * If you did implement memoization but this test case is still hanging, make
     * sure that in your recursive function (not the wrapper) that your recursive
     * calls are to your new recursive function and not back to the wrapper. If you
     * call the wrapper again, you'll get a fresh new memoization table rather than
     * preserving the one you're building up in your recursive exploration, and the
     * effect will be as if you hadn't implemented memoization at all.
     */
    EXPECT(weightOnBackOf(100, 50, 200) >= 10000);
}

STUDENT_TEST("col > row error"){
    EXPECT_ERROR(weightOnBackOf(5,7,10));
}
STUDENT_TEST("H man test"){
    EXPECT_EQUAL(weightOnBackOf(3,1,4),340);
}
/* TODO: Add your own tests here. You know the drill - look for edge cases, think about
 * very small and very large cases, etc.
 */
