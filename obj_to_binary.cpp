// OBJToBinary.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include "objparser.h"
#include "linkedlist.h"
#include "abstractobj.h"
#include "my_utils.h"


#include "rabin_karp_search.h"





int main(int argc, char* argv[])
{
	using namespace std;
	using namespace my_utils;

	RabinKarpStringSearch rks;
	int SIZE = 8;
	char* line = new char[SIZE + 1];
	int i = 0;
	line[i++] = 4; //0
	line[i++] = 3; //1
	line[i++] = 1; //2
	line[i++] = 4; //3
	line[i++] = 1; //4
	line[i++] = 5; //5
	line[i++] = 9; //6
	line[i++] = 2; //7
	line[i++] = 0; //8 EOL

	char* pattern = new char[3];
	i = 0;
	pattern[i++] = 3;
	pattern[i++] = 1;
	pattern[i++] = 0;

	cout << "my hash= " << rks.getIndexOf(line, pattern, 0) << "\n";

	DELETE_ARR(pattern);
	DELETE_ARR(line);

	return 0;
}


//int main(int argc, char* argv[])
//{
//    using namespace my_utils;
//    using namespace std;
//
//
//
//    if (argc != 3) {
//        cout << "usage: OBJToBinary.exe <OBJ input file path + name> <binary output path + file>";
//    }
//    else {
//        cout << "input file is: " << argv[1] << "\n";
//        cout << "output file is: " << argv[2] << "\n";
//        ifstream objStream;
//        ofstream binStream;
//        obj_parser objParser(&binStream);
//        
//        
//
//        objStream.open(argv[1], ifstream::in);
//        binStream.open(argv[2], ofstream::binary);
//        bool isStreamOK = objStream.good();
//        if (isStreamOK) {
//            int LINE_MAX_LENGTH = 512;
//            char* buf = new char[LINE_MAX_LENGTH];
//            while (isStreamOK) {
//                memset(buf, 0, LINE_MAX_LENGTH);
//                objStream.getline(buf, LINE_MAX_LENGTH);
//                isStreamOK = objStream.good();
//                if (strnlen(buf, LINE_MAX_LENGTH) > 0)
//                {
//                    cout << buf << "\n";
//                    objParser.processLine(buf);
//                }
//            }
//            objParser.close();
//            delete[] buf;
//            buf = NULL;
//        }
//        else {
//            cout << "ERROR!!! input stream is NOT OK\n";
//        }
//
//        //CLEAN UP the stack
//        objStream.close();
//    }
//}
