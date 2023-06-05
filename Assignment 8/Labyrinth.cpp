#include "Labyrinth.h"
using namespace std;

void getItem(MazeCell* curr,bool& getSpellBook,bool& getPotion,bool& getWand){

    if(curr->whatsHere == Item::SPELLBOOK){
        getSpellBook = true;
    }
    else if(curr->whatsHere == Item::POTION){
        getPotion = true;
    }
    else if(curr->whatsHere == Item::WAND){
        getWand = true;
    }
    else{
        return ;
    }
    return ;
}
bool pathMove(MazeCell*& curr,char step){
    if(step == 'E'){
        if(curr->east == nullptr){
            return false;
        }
        else{
            curr = curr->east;
        }
    }
    else if(step == 'N'){
        if(curr->north == nullptr){
            return false;
        }
        else{
            curr = curr->north;
        }
    }
    else if(step == 'S'){
        if(curr->south == nullptr){
            return false;
        }
        else{
            curr = curr->south;
        }
    }
    else{
        if(curr->west == nullptr){
            return false;
        }
        else{
            curr = curr->west;
        }
    }
    return true;
}
bool isPathToFreedom(MazeCell* start, const string& moves) {
    bool getSpellBook = false,getPotion = false,getWand = false;
    MazeCell* curr = start;
    for (int i = 0; i < moves.size(); ++i) {
        getItem(curr,getSpellBook,getPotion,getWand);
        bool judge = pathMove(curr,moves[i]);
        if(!judge) return false;
    }
    //结束的位置还要getItem
    getItem(curr,getSpellBook,getPotion,getWand);
    if(getSpellBook && getPotion && getWand)
        return true;
    return false;
}


/* * * * * * Test Cases Below This Point * * * * * */
#include "GUI/SimpleTest.h"
#include "Demos/MazeGenerator.h"

/* Optional: Add your own custom tests here! */














/* * * * * Provided Tests Below This Point * * * * */

/* Utility function to free all memory allocated for a maze. */
void deleteMaze(const Grid<MazeCell*>& maze) {
    for (auto* elem: maze) {
        delete elem;
    }
    /* Good question to ponder: why don't we write 'delete maze;'
     * rather than what's shown above?
     */
}

PROVIDED_TEST("Checks paths in the sample maze.") {
    auto maze = toMaze({"* *-W *",
                        "| |   |",
                        "*-* * *",
                        "  | | |",
                        "S *-*-*",
                        "|   | |",
                        "*-*-* P"});

    /* These paths are the ones in the handout. They all work. */
    EXPECT(isPathToFreedom(maze[2][2], "ESNWWNNEWSSESWWN"));
    EXPECT(isPathToFreedom(maze[2][2], "SWWNSEENWNNEWSSEES"));
    EXPECT(isPathToFreedom(maze[2][2], "WNNEWSSESWWNSEENES"));

    /* These paths don't work, since they don't pick up all items. */
    EXPECT(!isPathToFreedom(maze[2][2], "ESNW"));
    EXPECT(!isPathToFreedom(maze[2][2], "SWWN"));
    EXPECT(!isPathToFreedom(maze[2][2], "WNNE"));

    /* These paths don't work, since they aren't legal paths. */
    EXPECT(!isPathToFreedom(maze[2][2], "WW"));
    EXPECT(!isPathToFreedom(maze[2][2], "NN"));
    EXPECT(!isPathToFreedom(maze[2][2], "EE"));
    EXPECT(!isPathToFreedom(maze[2][2], "SS"));

    deleteMaze(maze);
}

PROVIDED_TEST("Can't walk through walls.") {
    auto maze = toMaze({"* S *",
                        "     ",
                        "W * P",
                        "     ",
                        "* * *"});

    EXPECT(!isPathToFreedom(maze[1][1], "WNEES"));
    EXPECT(!isPathToFreedom(maze[1][1], "NWSEE"));
    EXPECT(!isPathToFreedom(maze[1][1], "ENWWS"));
    EXPECT(!isPathToFreedom(maze[1][1], "SWNNEES"));

    deleteMaze(maze);
}

PROVIDED_TEST("Works when starting on an item.") {
    auto maze = toMaze({"P-S-W"});

    EXPECT(isPathToFreedom(maze[0][0], "EE"));
    EXPECT(isPathToFreedom(maze[0][1], "WEE"));
    EXPECT(isPathToFreedom(maze[0][2], "WW"));

    deleteMaze(maze);
}

