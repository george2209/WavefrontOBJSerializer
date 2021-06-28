// OBJToBinary.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include "objparser.h"
#include "linkedlist.h"
#include "abstractobj.h"





//int main()
//{
//	using namespace std;
//	using namespace my_utils;
//
//	abstractobj *p1 = new abstractobj(1);
//	abstractobj *p2 = new abstractobj(2);
//	abstractobj *p3 = new abstractobj(3);
//	
//	
//	
//	linkedlist<abstractobj>* pLinkedList = new linkedlist<abstractobj>();;
//	pLinkedList->addLast(p1);
//	pLinkedList->addLast(p2);
//	pLinkedList->addLast(p3);
//
//	NODE_t<abstractobj> *el = pLinkedList->getFirstElement();
//	while (el != NULL)
//	{
//		cout << "el = " << el->value->tmp << "\n";
//		el = el->next;
//	}
//	
//	delete pLinkedList;
//	delete p1;
//	delete p2;
//	delete p3;
//
//	return 0;
//}


int main(int argc, char* argv[])
{
    using namespace my_utils;
    using namespace std;



    if (argc != 3) {
        cout << "usage: OBJToBinary.exe <OBJ input file path + name> <binary output path + file>";
    }
    else {
        cout << "input file is: " << argv[1] << "\n";
        cout << "output file is: " << argv[2] << "\n";
        ifstream objStream;
        ofstream binStream;
        obj_parser objParser(&binStream);
        
        

        objStream.open(argv[1], ifstream::in);
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
        objStream.close();
    }
}



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
