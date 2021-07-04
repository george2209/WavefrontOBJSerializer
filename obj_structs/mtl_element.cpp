#include "mtl_element.h"
#include "../my_utils.h"
#include <string.h> //strlen
#include<iostream> //cout

#ifdef _DEBUG
#include <assert.h>
#endif //_DEBUG

namespace my_utils
{
	mtl_element::mtl_element()
	{
		i_arrMaterialName = NULL;
	}

	mtl_element::~mtl_element()
	{
		DELETE_ARR(i_arrMaterialName);
	}

	bool mtl_element::parseMaterialName(const char* pLine, int startingIndex)
	{
#ifdef _DEBUG
		assert(i_arrMaterialName == NULL);
#endif // _DEBUG
		int size = strlen(pLine) - startingIndex;
		bool isMTL_NAME_OK = size > 0;
		if (isMTL_NAME_OK)
		{
			this->i_arrMaterialName = new char[size + 1];
			this->i_arrMaterialName[size] = NULL;
			COPY_CHAR_ARRAYS(pLine, startingIndex, this->i_arrMaterialName, 0, size);
		}
		else
		{
#ifdef _DEBUG
			assert(i_arrMaterialName == NULL);
#else
			std::cout << "ERROR! NULL material name detected inside the MTL file.\n at line: " << pLine << "\n";
#endif // _DEBUG
		}
		return isMTL_NAME_OK;
	}
}