#pragma once

#include "obj_vertex_element.h"

namespace my_utils {
	class abstractserializer
	{
	protected:

		void persistOptionalVertex(std::ofstream* pOutputStream, const obj_vertex_element* pVertex)
		{
			bool status = pVertex != NULL;
			pOutputStream->write((char*)&status, sizeof(bool));
			if (status)
			{
				persistVertex(pOutputStream, pVertex);
			}
		};

		void persistOptionalCharArray(std::ofstream* pOutputStream, const char* pArray)
		{
			bool status = pArray != NULL;
			if (status)
			{
				persistCharArray(pOutputStream, pArray);
			}
			else {
				short noOfChars = 0;
				pOutputStream->write((char*)&noOfChars, sizeof(short));
			}
		}

		void persistVertex(std::ofstream* pOutputStream, const obj_vertex_element* pVertex)
		{
			pOutputStream->write((char*)&(pVertex->x), sizeof(float));
			pOutputStream->write((char*)&(pVertex->y), sizeof(float));
			pOutputStream->write((char*)&(pVertex->z), sizeof(float));
		};

		void persistCharArray(std::ofstream* pOutputStream, const char* pArray)
		{
			short noOfChars = static_cast<short>(strlen(pArray));
			pOutputStream->write((char*)&noOfChars, sizeof(short));
			pOutputStream->write(pArray, sizeof(char) * noOfChars);
		};

		//void persistOptionalFloat(std::ofstream* pOutputStream, const float& val)
		//{
		//	bool status = val != -1;
		//	pOutputStream->write((char*)&status, sizeof(bool));
		//	if (status)
		//	{
		//		pOutputStream->write((char*)&val, sizeof(float));
		//	}
		//};
	};
}
