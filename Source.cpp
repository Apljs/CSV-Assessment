// Made by Rahim Sarpas

#include "CSV.h"

#include <iostream> // String Stream Library for file manipulation
#include <Windows.h> // Windows Standard Library
#include <stdlib.h> // STD Library
#include "Display.h" // Helper functions

// Main Program
int main() {
	
	// Create CSV Object
	CSV x;
	// Populate the object
	x.updateCSV("Messages.csv");
	// Display and clear the first element and store the time
	int currentTime = firstSleep(x.getStart(x.getPrintRow()), 
		x.getDur(x.getPrintRow()), x);
	// Loop through the rest of the data rows in the object
	for (int i = 1; i < x.getTextSize(); i++)
	{
		currentTime = contSleep(currentTime, x.getStart(x.getPrintRow()),
			x.getDur(x.getPrintRow()), x);
	}
	return 0;
}