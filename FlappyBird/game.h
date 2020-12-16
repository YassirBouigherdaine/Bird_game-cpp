#pragma once
#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include<dos.h>
#include<conio.h>



// game functions

void gotoxy(int, int);

void draw_screen();

void draw_bird();

// draw & erase first obstacle

void draw_Fobstacle();          

void erase_Fobstacle();      

// draw & erase second obstacle

void draw_Sobstacle();

void erase_Sobstacle();

// updating obstacles and score

void update();

// user input
 
void input();                

// main function

void run_game();                 


