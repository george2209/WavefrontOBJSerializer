#include "obj_vertex_element.h"
#include <string.h> //strlen
#include <stdlib.h> //strtod 
#include "my_utils.h"

namespace my_utils {
	obj_vertex_element::obj_vertex_element()
	{
		x = 0.0;
		y = 0.0;
		z = 0.0;
	}

	bool obj_vertex_element::parse(const char* pLine, int startIndex)
	{
		int end = strlen(pLine);
		char* pTmp;
		char* line = new char[end- startIndex + 1];
		line[end - startIndex] = NULL;

		for (int i = startIndex; i < end; i++)
		{
			line[i - startIndex] = pLine[i];
		}

		x = strtof(line, &pTmp);
		y = strtof(pTmp, &pTmp);
		z = strtof(pTmp, &pTmp);

		DELETE_ARR(line);

		return true;
	}
}