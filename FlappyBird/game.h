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

void draw_obstacle();          

void erase_obstacle();        
 
void input();                

// main function

void run_game();                 


