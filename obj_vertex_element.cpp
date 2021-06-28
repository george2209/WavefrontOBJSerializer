#include "obj_vertex_element.h"
namespace my_utils {
	obj_vertex_element::obj_vertex_element()
	{
		x = -1.0;
		y = -1.0;
		z = -1.0;
	}

	bool obj_vertex_element::parse(char* pLine, int startIndex)
	{
		int index = 0;
		int pivot = startIndex;
		while (pLine[pivot] != '\0')
		{
			//aici am ramas
		}

		return (index == 2);
	}
}