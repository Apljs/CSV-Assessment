// Made by Rahim Sarpas

#include "CSV.h"

#include <iostream> // String Stream Library for file manipulation
#include <Windows.h> // Windows Standard Library
#include <stdlib.h> // STD Library

// Non Class Based Helper Functions
// Delcarations
int firstSleep(int startTime, int duration, CSV &obj);
int contSleep(int currentTime, int startTime, int duration, CSV &obj);
void clear();

/*
* Delays system from running until start time and then displays
* a message until the duration has ended before it gets cleared
* from the console. This is for the first message.
* @param startTime	The start time specified in miliseconds of
*					when to execute code
* @param duration	The duration of code execution
* @param obj	    The CSV object from where the data is
*					taken from
* @return int		The Time after code execution
*/
int firstSleep(int startTime, int duration, CSV &obj)
{
	// Delay system for x amount of time
	// Convert time to seconds before use 
	float conTime = static_cast<float>(startTime) / 1000;
	Sleep(conTime);
	// Display message
	std::cout << obj.printText(obj.getPrintRow()) << std::endl;
	// Convert duration into seconds
	float conDur = static_cast<float>(duration) / 1000;
	Sleep(conDur);
	// Clear used data from CSV
	obj.clearPrintRow(obj.getPrintRow());
	// Clear Console
	clear();
	// Return current time
	int curTime = startTime + duration;
	return (curTime);
}

/*
* Delays system from running until start time and then displays
* a message until the duration has ended before it gets cleared
* from the console. This is for other messages.
* @param startTime	The start time specified in miliseconds of
*					when to execute code
* @param duration	The duration of code execution
* @param obj	    The CSV object from where the data is
*					taken from
*/
int contSleep(int currentTime, int startTime, int duration, CSV &obj)
{
	// Delay system for the difference in time
	// Between the last execution finalization and the next start
	// Convert to seconds and store before using
	float diff = abs(currentTime - startTime);
	float diffTime = (abs(diff) / 1000);
	Sleep(diffTime);
	// Display Message
	std::cout << obj.printText(obj.getPrintRow()) << std::endl;
	// Delay system for x amount of time
	// Convert duration into seconds
	float conDur = static_cast<float>(duration) / 1000;
	Sleep(conDur);
	// Clear used data from CSV
	obj.clearPrintRow(obj.getPrintRow());
	// Clear Console
	clear();
	// Return current time
	int curTime = startTime + duration;
	return (curTime);
}

/*
* Clears console screen
*/
void clear()
{
	system("CLS");
}