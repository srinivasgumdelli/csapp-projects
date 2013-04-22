/* @file main.cpp
 * Main File for WANDERER game
 *
 * @author Kelsey Yuen
 * @date 03-21-2013
 */

#include <iostream>

#include <fstream>
#include <assert.h>

/*	Attempt at WANDERER
 *	C++ Game, all info in the main file, will split afterwards
 *	A "3D" game, but graphically represented as a 2.5D game (isometric)
 *
 *	Game Mechanics:
 *	Walk or Run around
 *	World is Dark, You hold light which illuminates in front of you
 *	Explore
 *	Fight
 *	Live!
 *
 */
 
#include "map.h"

using namespace std;

#define filename "SAVE"

int main{
/*	Main Function
 *
 *	Should declare global variables
 *	Then, enter first loop (main menu)
 *	Then, either exit (j end) or enter the game loop (j gameloop)
 *	Run Game Loop
 *		- Read User Input
 *		- Modify Values
 *		- Check for Collisions
 *		- Correct Values
 *		- Update Graphics
 *	Exit
 */
 
	// checksum function goes here
	
	// variables go here
	bool exit_status = true;
	bool start_status = false;
	Map *current_map;
	
	// menu loop
menu:	while (true){
		if (start_status)
			current_map.readFromFile(filename);
			break;
		if (exit_status)
			goto end;
	}
	
	// game loop
	while (true){
		// read user input
		
		// modify values
		
		if (exit_status)
			break;
		
		// check for collisions
		
		// correct values
		
		// update graphics
	}
	
end:	return 0;
}