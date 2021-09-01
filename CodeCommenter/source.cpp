#include <iostream>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include "dirent.h"

using namespace std;


int writeToFile(const string &fileName);
int main()
{
	const string FILETYPE = ".cs";
	const char DIRECTORY[] = "./FILES";


	DIR *dr;
	struct dirent *en;
	dr = opendir(DIRECTORY);

	if (dr)
	{
		while ((en = readdir(dr)) != NULL)
		{
			// Make sure the name of the file contains the file type
			// we're looking for.

			string fileName(en->d_name);

			if (fileName.find(FILETYPE) != string::npos)
			{
				writeToFile(string(DIRECTORY) + "/" + fileName);
			}
		}

		closedir(dr);
	}

	cout << endl << endl;
	cout << "~~~~PROGRAM DONE~~~~";
	getchar();
	return 0;
}

int writeToFile(const string &filePath)
{
	fstream file;
	file.open(filePath, ios::in | ios::out | ios::binary);

	if (file.is_open())
	{
		string line;
		unsigned int cursorPos = 0;
		bool foundDebug = false;
		while (getline(file, line))
		{
			// The line contains 'Debug', so let's search each word till we
			// find the position of it.
			// Also, make sure that it is not already commented by our program.
			if (line.find("Debug") != string::npos && line.find("//Debug") == string::npos)
			{
				istringstream ss(line);

				string word;

				while (ss >> word)
				{
					// The word contains 'Debug', so make note of the cursor position.
					// We'll use the cursor position to comment it out!
					if (word.find("Debug") != string::npos)
					{
						cout << "Found Debug at cursor pos: " << cursorPos << endl;

						file.seekg(cursorPos);

						// Get everything after the 'Debug' statement
						// so we can make sure we append '//' and not overwrite any existing characters.
						string restOfLine; 
						getline(file, restOfLine);

						file.seekg(cursorPos);

						file << "//" + restOfLine;

						foundDebug = true;
					}

					// We add 1 to account for the space after the word.
					cursorPos += word.length() + 1;
					file.seekg(cursorPos);
				}

				// We remove 1 because we reached the end of the line, and
				// we don't want that to be treated as a space.
				cursorPos -= 1;
				file.seekg(cursorPos);
			}
			// If the line does not contain 'Debug', 
			// add its length to the cursorPos.
			
			cursorPos += line.length() + 1;
		}

		if (!foundDebug)
			cout << "No debug found..." << endl;
	}
	else
	{
		cout << "COULD NOT OPEN FILE NAME: " << filePath;
	}
	
	return 1;
}