/* Gatech ECE2035 2017 FALL MAZE RUNNER
* Copyright (c) 2017 Gatech ECE2035
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/

// Include header files for platform
#include "mbed.h"

// Include header files for pacman project
#include "globals.h"
#include "math_extra.h"
#include "physics.h"
#include "game.h"
#include "wall.h"
#include "doublely_linked_list.h"

// Hardware initialization
DigitalIn left_pb(p21);  // push button
DigitalIn right_pb(p22); // push button
DigitalIn up_pb(p23);    // push button
DigitalIn down_pb(p24);  // push button
uLCD_4DGL uLCD(p9,p10,p11); // LCD (serial tx, serial rx, reset pin;)
Serial pc(USBTX,USBRX);     // used by Accelerometer
MMA8452 acc(p28, p27, 100000); // Accelerometer
SDFileSystem sd(p5, p6, p7, p8, "sd"); // SD card and filesystem (mosi, miso, sck, cs)

// Level creation method declaration
DLinkedList* create_blank_level();
DLinkedList* create_level_one();
DLinkedList* create_level_two();
DLinkedList* create_level_three();

// Parameters. Declared in globals.h
const float mass = 0.001;
const int radius = 4;
const float bounce=0.5;
//double gx = 0;
//double gy = 0;
//double gz = 0;

/** Main() is where you start your implementation */
int main()
{
    ////////////////////////////
    // Power-on initialization
    ////////////////////////////
    // Turn up the serial data rate so we don't lag
    uLCD.baudrate(3000000);
    pc.baud(115200);

    // Initialize the buttons
    // Each *_pb variable is 0 when pressed
    left_pb.mode(PullUp);
    right_pb.mode(PullUp);
    up_pb.mode(PullUp);
    down_pb.mode(PullUp);

    // Other hardware initialization here (SD card, speaker, etc.)
    /*
    mkdir("/sd/mydir", 0777);
    
    FILE *fp = fopen("/sd/mydir/sdtest.txt");
    if(fp == NULL) {
        
    }
    */
    // Start screen
        uLCD.printf("******************");
        uLCD.printf("*                *");
        uLCD.printf("*                *");
        uLCD.printf("*                *");
        uLCD.printf("*   WELCOME TO   *");
        uLCD.printf("*   MAZE RUNNER  *");
        uLCD.printf("*                *");
        uLCD.printf("*                *");
        uLCD.printf("*  Press Any     *");
        uLCD.printf("*    Button to   *");
        uLCD.printf("*       Start    *");
        uLCD.printf("*                *");
        uLCD.printf("*                *");
        uLCD.printf("*                *");
        uLCD.printf("*                *");
        uLCD.printf("******************");
    while (right_pb == 1 && left_pb == 1 && up_pb == 1 && down_pb == 1)
    {

    }
        uLCD.cls();
    ///////////////
    // Reset loop
    ///////////////
    // This is where control between major phases of the game happens
    // This is a good place to add choose levels, add the game menu, etc.
    bool gameEnd = false;
    while(!gameEnd) 
    {
        // Initialze game state
        DLinkedList* arena = create_level_one();
        DLinkedList* arena2 = create_level_two();
        DLinkedList* arena3 = create_level_three();
        
        // Puts all DLinkedList levels in another linked list
        DLinkedList* levels = create_dlinkedlist();
        insertTail(levels, (void*)arena);
        insertTail(levels, (void*)arena2);
        insertTail(levels, (void*)arena3);
        
        //DLinkedList* saveState = create_dlinkedlist();
        
        // Delegate to the game loop to execute the level
        // run_game() is in game.cpp
            DLinkedList* temp = (DLinkedList*)getHead(levels);
            int score[3];
            
        //Goes through the arenas and calls run_game() reinitializing the physics each time
        for (int i = 0; i < 3; i++)
        {
            Physics state = {0};
            state.px = 15.0;        // Position in the center of the screen
            state.py = 15.0;
            state.vx = 0.0;         // Initially unmoving
            state.vy = 0.0;
            score[i] = run_game(levels, temp, &state);
            temp = (DLinkedList*)getNext(levels);
        }
        uLCD.cls();
        
        // Calculates the average score that is returned from each arena
        int totalScore = (score[0] + score[1] + score[2]) / 3;

        // Game Over Screen
        uLCD.printf("                \n");
        uLCD.printf("                \n");
        uLCD.printf("                \n");
        uLCD.printf("                \n");
        uLCD.printf("    GAME OVER   \n");
        uLCD.printf("      Score:    \n");
        uLCD.printf("                \n");
        uLCD.printf("   1. %d\n", score[0]);
        uLCD.printf("   2. %d\n", score[1]);
        uLCD.printf("   3. %d\n\n", score[2]);
        uLCD.printf(" Average Score:\n\n");
        uLCD.printf("   %d\n", totalScore);

        // Destory the arena and entities once we're done with the level
        destroyList(levels);
        
        // Exits while loop so Game Over Screen is not overwritten
        gameEnd = true;
    }
}

/** Creates a level with only bounding walls and a ball. */
DLinkedList* create_blank_level()
{
    DLinkedList* arena = create_dlinkedlist();
    
    // Initialize the walls
    Wall* walls[4];
    walls[0] = create_wall(HORIZONTAL, 0, 0, 127, bounce);  // top
    walls[1] = create_wall(HORIZONTAL, 0, 127, 127, bounce);// bottom
    walls[2] = create_wall(VERTICAL, 0, 0, 127, bounce);    // left
    walls[3] = create_wall(VERTICAL, 127, 0, 127, bounce);  // right
    
    // Add the walls to the arena
    for (int i = 0; i < 4; i++)
        insertTail(arena, (void*)walls[i]);

    // Initialize the ball
    Ball* ball = (Ball*) malloc(sizeof(Ball));
    ball->type = BALL;
    ball->x = 20;
    ball->y = 20;
    
    // Add ball to the arena 
    // NOTE: The ball should always be last in the arena list, so that the other 
    // ArenaElements have a chance to compute the Physics updates before the 
    // ball applies forward euler method.
    insertTail(arena, (void*)ball);
    
    return arena;
}

DLinkedList* create_level_one()
{
    DLinkedList* arena = create_dlinkedlist();

    // Initialize the walls
    Wall* walls[7];
    walls[0] = create_wall(HORIZONTAL, 0, 0, 127, bounce);  // top
    walls[1] = create_wall(HORIZONTAL, 0, 127, 127, bounce);// bottom
    walls[2] = create_wall(VERTICAL, 0, 0, 127, bounce);    // left
    walls[3] = create_wall(VERTICAL, 127, 0, 127, bounce);  // right
    walls[4] = create_wall(VERTICAL, 30, 0, 70, bounce);
    walls[5] = create_wall(VERTICAL, 60, 50, 80, bounce);
    walls[6] = create_wall(VERTICAL, 90, 0, 70, bounce);
    // Add the walls to the arena
    for (int i = 0; i < 7; i++)
        insertTail(arena, (void*)walls[i]);
        
    // Add Destination
    Goal* goal = (Goal*)malloc(sizeof(Goal));
    goal->type = GOAL;
    goal->x = 115;
    goal->y = 15;
    insertTail(arena, (void*)goal);

    // Add potholes
    Pothole* pothole = (Pothole*)malloc(sizeof(Pothole));
    pothole->type = POTHOLE;
    pothole->x = 15;
    pothole->y = 115;
    insertTail(arena, (void*)pothole);
    
    Pothole* pothole2 = (Pothole*)malloc(sizeof(Pothole));
    pothole2->type = POTHOLE;
    pothole2->x = 115;
    pothole2->y = 115;
    insertTail(arena, (void*)pothole2);
    
    // Initialize the ball
    Ball* ball = (Ball*) malloc(sizeof(Ball));
    ball->type = BALL;
    ball->x = 20;
    ball->y = 20;
    
    
    // Add ball to the arena 
    // NOTE: The ball should always be last in the arena list, so that the other 
    // ArenaElements have a chance to compute the Physics updates before the 
    // ball applies forward euler method.
    insertTail(arena, (void*)ball);
    
    return arena;
}

DLinkedList* create_level_two()
{
    DLinkedList* arena = create_dlinkedlist();

    // Initialize the walls
    Wall* walls[10];
    walls[0] = create_wall(HORIZONTAL, 0, 0, 127, bounce);  // top
    walls[1] = create_wall(HORIZONTAL, 0, 127, 127, bounce);// bottom
    walls[2] = create_wall(VERTICAL, 0, 0, 127, bounce);    // left
    walls[3] = create_wall(VERTICAL, 127, 0, 127, bounce);  // right
    walls[4] = create_wall(HORIZONTAL, 0, 30, 70, bounce);
    walls[5] = create_wall(HORIZONTAL, 50, 50, 80, bounce);
    walls[6] = create_wall(VERTICAL, 49, 50, 25, bounce);
    walls[7] = create_wall(VERTICAL, 70, 100,-20, bounce);
    walls[8] = create_wall(HORIZONTAL, 0, 100, 70, bounce);
    walls[9] = create_wall(HORIZONTAL, 90, 100, 60, bounce);
    // Add the walls to the arena
    for (int i = 0; i < 10; i++)
        insertTail(arena, (void*)walls[i]);
        
    // Add Destination
    Goal* goal = (Goal*)malloc(sizeof(Goal));
    goal->type = GOAL;
    goal->x = 115;
    goal->y = 115;
    insertTail(arena, (void*)goal);

    // Add pothole
    Pothole* pothole = (Pothole*)malloc(sizeof(Pothole));
    pothole->type = POTHOLE;
    pothole->x = 115;
    pothole->y = 90;
    insertTail(arena, (void*)pothole);
    
    Slowhole* slowhole = (Slowhole*)malloc(sizeof(Slowhole));
    slowhole->type = SLOWHOLE;
    slowhole->x = 40;
    slowhole->y = 20;
    insertTail(arena, (void*)slowhole);
    
    Slowhole* slowhole2 = (Slowhole*)malloc(sizeof(Slowhole));
    slowhole2->type = SLOWHOLE;
    slowhole2->x = 30;
    slowhole2->y = 70;
    insertTail(arena, (void*)slowhole);
    
    //Backto* backto = (Backto*)malloc(sizeof(Backto));
    //backto->type = BACKTO;
    //backto->x ;
    //backto->y ;
    //insertTail(arena, (void*)backto);
    
    // Initialize the ball
    Ball* ball = (Ball*) malloc(sizeof(Ball));
    ball->type = BALL;
    ball->x = 20;
    ball->y = 20;
    
    
    // Add ball to the arena 
    // NOTE: The ball should always be last in the arena list, so that the other 
    // ArenaElements have a chance to compute the Physics updates before the 
    // ball applies forward euler method.
    insertTail(arena, (void*)ball);
    
    return arena;
}

DLinkedList* create_level_three()
{
    DLinkedList* arena = create_dlinkedlist();

    // Initialize the walls
    Wall* walls[13];
    walls[0] = create_wall(HORIZONTAL, 0, 0, 127, bounce);  // top
    walls[1] = create_wall(HORIZONTAL, 0, 127, 127, bounce);// bottom
    walls[2] = create_wall(VERTICAL, 0, 0, 127, bounce);    // left
    walls[3] = create_wall(VERTICAL, 127, 0, 127, bounce);  // right
    walls[4] = create_wall(HORIZONTAL, 0, 30, 110, bounce);
    walls[5] = create_wall(VERTICAL, 110, 40, -10, bounce);
    walls[6] = create_wall(HORIZONTAL, 60, 40, 50, bounce);
    walls[7] = create_wall(VERTICAL, 60, 40, 20, bounce);
    walls[8] = create_wall(VERTICAL, 40, 45, 60, bounce);
    walls[9] = create_wall(VERTICAL, 20, 45, 75, bounce);
    walls[10] = create_wall(HORIZONTAL, 75, 60, 100, bounce);
    walls[11] = create_wall(HORIZONTAL, 40, 100, 90, bounce);
    walls[12] = create_wall(HORIZONTAL, 20, 120, 70, bounce);
    
    // Add the walls to the arena
    for (int i = 0; i < 13; i++)
        insertTail(arena, (void*)walls[i]);
        
    // Add Destination
    Goal* goal = (Goal*)malloc(sizeof(Goal));
    goal->type = GOAL;
    goal->x = 115;
    goal->y = 115;
    insertTail(arena, (void*)goal);

    // Add pothole
    Pothole* pothole = (Pothole*)malloc(sizeof(Pothole));
    pothole->type = POTHOLE;
    pothole->x = 10;
    pothole->y = 115;
    insertTail(arena, (void*)pothole);

    // Initialize the ball
    Ball* ball = (Ball*) malloc(sizeof(Ball));
    ball->type = BALL;
    ball->x = 20;
    ball->y = 20;
    
    
    // Add ball to the arena 
    // NOTE: The ball should always be last in the arena list, so that the other 
    // ArenaElements have a chance to compute the Physics updates before the 
    // ball applies forward euler method.
    insertTail(arena, (void*)ball);
    
    return arena;
}