#include "mtl_element.h"
#include "../my_utils.h"
#include <string.h> //strlen
#include<iostream> //cout
#include "obj_vertex_element.h"

#ifdef _DEBUG
#include <assert.h>
#endif //_DEBUG

namespace my_utils
{
	mtl_element::mtl_element()
	{
		KA = NULL;
		KD = NULL;
		KS = NULL;
		KE = NULL;
		i_arrMaterialName = NULL;
	}

	mtl_element::~mtl_element()
	{
		DELETE_ARR(i_arrMaterialName);
		DELETE_PTR(KA);
		DELETE_PTR(KD);
		DELETE_PTR(KS);
		DELETE_PTR(KE);
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="pLine"></param>
	/// <param name="startIndex"></param>
	/// <returns></returns>
	bool mtl_element::parseKA(const char* pLine, int startIndex)
	{
		return parseVertexElement(KA, pLine, startIndex);
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="pLine"></param>
	/// <param name="startIndex"></param>
	/// <returns></returns>
	bool mtl_element::parseKD(const char* pLine, int startIndex)
	{
		return parseVertexElement(KD, pLine, startIndex);
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="pLine"></param>
	/// <param name="startIndex"></param>
	/// <returns></returns>
	bool mtl_element::parseKS(const char* pLine, int startIndex)
	{
		return parseVertexElement(KS, pLine, startIndex);
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="pLine"></param>
	/// <param name="startIndex"></param>
	/// <returns></returns>
	bool mtl_element::parseKE(const char* pLine, int startIndex)
	{
		return parseVertexElement(KE, pLine, startIndex);
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="pElement"></param>
	/// <param name="pLine"></param>
	/// <param name="startingIndex"></param>
	/// <returns></returns>
	bool mtl_element::parseVertexElement(obj_vertex_element* pElement, const char* pLine, int startingIndex)
	{
#ifdef _DEBUG
		assert(pElement == NULL);
#endif // _DEBUG

		pElement = new obj_vertex_element();
		return pElement->parse(pLine, 0);
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="pLine"></param>
	/// <param name="startingIndex"></param>
	/// <returns></returns>
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


	/// <summary>
	/// 
	/// </summary>
	/// <returns>KA pointer of this class.</returns>
	obj_vertex_element* mtl_element::getKA()
	{
		return this->KA;
	}

	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	obj_vertex_element* mtl_element::getKD()
	{
		return this->KD;
	}

	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	obj_vertex_element* mtl_element::getKS()
	{
		return this->KS;
	}

	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	obj_vertex_element* mtl_element::getKE()
	{
		return this->KE;
	}
}