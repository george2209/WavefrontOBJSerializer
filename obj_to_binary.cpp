// OBJToBinary.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include<iostream> //cout
#include <fstream> //ifstream
#include "objparser.h"
#include "my_utils.h"
#include "obj_structs.h"
#include <assert.h> //assert


//#include "linkedlist.h"
//#include "rabin_karp_search.h"





//int main(int argc, char* argv[])
//{
//	using namespace std;
//	using namespace my_utils;
//
//	RabinKarpStringSearch rks;
//	int SIZE = 8;
//	char* line = new char[SIZE + 1];
//	int i = 0;
//	line[i++] = 4; //0
//	line[i++] = 3; //1
//	line[i++] = 1; //2
//	line[i++] = 4; //3
//	line[i++] = 1; //4
//	line[i++] = 5; //5
//	line[i++] = 9; //6
//	line[i++] = 2; //7
//	line[i++] = 0; //8 EOL
//
//	char* pattern = new char[3];
//	i = 0;
//	pattern[i++] = 3;
//	pattern[i++] = 1;
//	pattern[i++] = 0;
//
//	cout << "my hash= " << rks.getIndexOf(line, pattern, 0) << "\n";
//
//	DELETE_ARR(pattern);
//	DELETE_ARR(line);
//
//	return 0;
//}

void printHelpMessage()
{
	using namespace std;

	cout << "Usage:" << "\n";
	cout << "\t * 'OBJToBinary.exe -h' or 'OBJToBinary.exe --help' will print this message\n";
	cout << "\t * 'OBJToBinary.exe -cp=<folder path to OBJ files> <file name OBJ> <file name output>'" << "\n";
	cout << "\t\twill load/save all the data from the '<path to OBJ file>' folder.\n";
	cout << "\t\tIf the -cp is missing then all the data will be loaded/saved from the folder where OBJToBinary.exe is located\n";
	cout << "\t * Examples:" << "\n";
	cout << "\t\tOBJToBinary.exe -cp=\"c:\\my_obj_folder\\\" airplane.obj airplane.bin\n";
	cout << "\t\tIn this example the airplane.obj (as well as any eventual MTL file) will be located inside \"c:\\my_obj_folder\\\"\n\n";
	cout << "\t\tOBJToBinary.exe airplane.obj airplane.bin\n";
	cout << "\t\tIn this example the airplane.obj (as well as any eventual MTL file) will be located inside the same folder where the OBJToBinary.exe is located.\n";
}

bool processCommandParams(int argc, char* argv[], my_utils::E_PARSER_OPTIONS& parserOptions)
{
	for (int i = 0; i < argc; i++)
	{
		if (i == 0)
		{
			//calculate default class path as the executable path
			int size = strlen(argv[0]) - 15;// = length of "OBJToBinary.exe"
			parserOptions.OBJ_CLASS_PATH = new char[size + 1];
			(parserOptions.OBJ_CLASS_PATH)[size] = NULL;
			COPY_CHAR_ARRAYS(argv[0], 0, (parserOptions.OBJ_CLASS_PATH), 0, size);
		}
		else {
			const char* pTmp = argv[i];
			int size = strlen(pTmp);

			if (strncmp("-cp=", argv[i], 4) == 0)
			{
				//the last character must be '\'. if not then add it at the end of OBJ_CLASS_PATH
				bool isLastCharOK = (pTmp[size - 1]) == '\\';
				size += (!isLastCharOK);
				if (parserOptions.OBJ_CLASS_PATH != NULL)
					DELETE_ARR(parserOptions.OBJ_CLASS_PATH);

				parserOptions.OBJ_CLASS_PATH = new char[size + 1];
				(parserOptions.OBJ_CLASS_PATH)[size-1] = isLastCharOK? NULL : '\\';
				(parserOptions.OBJ_CLASS_PATH)[size] = NULL;
				COPY_CHAR_ARRAYS(pTmp, 4, (parserOptions.OBJ_CLASS_PATH), 0, size - !isLastCharOK);
			}
			else if ((strncmp("-h", argv[i], 2) == 0) || 
				(strncmp("--help", argv[i], 6) == 0)) {
				printHelpMessage();
				return false;
			}
			else {
				if (parserOptions.OBJ_FILE_NAME == NULL)
				{
					//first param is the OBJ file name
					int sizeFolder = strlen(parserOptions.OBJ_CLASS_PATH);
					parserOptions.OBJ_FILE_NAME = new char[size + sizeFolder + 1];
					parserOptions.OBJ_FILE_NAME[size + sizeFolder] = NULL;
					COPY_CHAR_ARRAYS(parserOptions.OBJ_CLASS_PATH, 0, parserOptions.OBJ_FILE_NAME, 0, sizeFolder);
					COPY_CHAR_ARRAYS(pTmp, 0, parserOptions.OBJ_FILE_NAME, sizeFolder, size);
				}
				else if (parserOptions.BIN_FILE_NAME == NULL){
					//fill in the binary file name
					int sizeFolder = strlen(parserOptions.OBJ_CLASS_PATH);
					parserOptions.BIN_FILE_NAME = new char[size + sizeFolder + 1];
					parserOptions.BIN_FILE_NAME[size + sizeFolder] = NULL;
					
					COPY_CHAR_ARRAYS(parserOptions.OBJ_CLASS_PATH, 0, parserOptions.BIN_FILE_NAME, 0, sizeFolder);
					COPY_CHAR_ARRAYS(pTmp, 0, parserOptions.BIN_FILE_NAME, sizeFolder, size);
				}
				else {
					printHelpMessage();
					return false;
				}
			}
		}
	}

	return true;
}


int main(int argc, char* argv[])
{
	using namespace my_utils;
	using namespace std;

	E_PARSER_OPTIONS parserOptions;
	if (!processCommandParams(argc, argv, parserOptions))
		return 0;
	else {
		cout << "starting with parameters:" << "\n";
		cout << "input/output working folder: " << parserOptions.OBJ_CLASS_PATH<< "\n";
		cout << "input OBJ file: " << parserOptions.OBJ_FILE_NAME << "\n";
		cout << "output BIN file: " << parserOptions.BIN_FILE_NAME << "\n\n";
	}
	ifstream objStream;
	ofstream binStream;
	obj_parser objParser(&binStream, parserOptions.OBJ_CLASS_PATH);



	objStream.open(parserOptions.OBJ_FILE_NAME, ifstream::in);
	binStream.open(parserOptions.BIN_FILE_NAME, ofstream::binary);
	bool isStreamOK = objStream.good();
	if (isStreamOK) {
		int LINE_MAX_LENGTH = 512;
		char* buf = new char[LINE_MAX_LENGTH];
		while (isStreamOK) {
			memset(buf, 0, LINE_MAX_LENGTH);
			objStream.getline(buf, LINE_MAX_LENGTH);
			isStreamOK = objStream.good();
			if (strnlen(buf, LINE_MAX_LENGTH) > 0)
			{
				cout << buf << "\n";
				objParser.processLine(buf);
			}
		}
		objParser.close();
		delete[] buf;
		buf = NULL;
	}
	else {
		cout << "ERROR!!! input stream is NOT OK\n";
	}

	//CLEAN UP the stack
	binStream.flush();
	binStream.close();
	objStream.close();

	return 0;
}
