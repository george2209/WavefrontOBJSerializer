// OBJToBinary.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include "objparser.h"
#include "linkedlist.h"
#include "abstractobj.h"
#include "my_utils.h"





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
        binStream.open(argv[2], ofstream::binary);
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
