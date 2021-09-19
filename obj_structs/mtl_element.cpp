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

	mtl_element::mtl_element(short id) : i_ID(id)
	{
		KA = NULL;
		KD = NULL;
		KS = NULL;
		KE = NULL;
		NS = INVALID_NUMBER;
		NI = INVALID_NUMBER;
		d = INVALID_NUMBER;
		illum = INVALID_NUMBER;
		i_arrMaterialName = NULL;
		i_arrMapKaFile = NULL;
		i_arrMapKdFile = NULL;
		i_arrMapKsFile = NULL;
		i_arrMapKeFile = NULL;
		i_arrMapNsFile = NULL;
		i_arrMapDFile = NULL;
	}

	mtl_element::~mtl_element()
	{
		DELETE_ARR(i_arrMaterialName);
		DELETE_ARR(i_arrMapKaFile);
		DELETE_ARR(i_arrMapKdFile);
		DELETE_ARR(i_arrMapKsFile);
		DELETE_ARR(i_arrMapKeFile);
		DELETE_ARR(i_arrMapNsFile);
		DELETE_ARR(i_arrMapDFile);
		DELETE_PTR(KA);
		DELETE_PTR(KD);
		DELETE_PTR(KS);
		DELETE_PTR(KE);
	}

	bool mtl_element::parseNS(const char* pLine, int startingIndex)
	{
		return this->parseFloat(&NS, pLine, startingIndex);
	}

	bool mtl_element::parseNI(const char* pLine, int startingIndex)
	{
		return this->parseFloat(&NI, pLine, startingIndex);
	}

	bool mtl_element::parseD(const char* pLine, int startingIndex)
	{
		return this->parseFloat(&d, pLine, startingIndex);
	}

	bool mtl_element::parseIllum(const char* pLine, int startingIndex)
	{
		int size = strlen(pLine);
		char* pTmp;
		char* line = new char[size - startingIndex + 1];
		for (int i = startingIndex; i < size; i++)
		{
			line[i - startingIndex] = pLine[i];
		}

		illum = (char)strtol(line, &pTmp, 10);

		DELETE_ARR(line);
		return true;
	}

	bool mtl_element::parseFloat(float* pElement, const char* pLine, int startingIndex)
	{
		int size = strlen(pLine);
		char* pTmp;
		char* line = new char[size - startingIndex + 1];
		line[size - startingIndex] = NULL;

		for (int i = startingIndex; i < size; i++)
		{
			line[i - startingIndex] = pLine[i];
		}

		(*pElement) = strtof(line, &pTmp);

		DELETE_ARR(line);

		return true;
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
	bool mtl_element::parseVertexElement(obj_vertex_element *& pElement, const char* pLine, int startingIndex)
	{
#ifdef _DEBUG
		assert(pElement == NULL);
#endif // _DEBUG

		pElement = new obj_vertex_element();
		return pElement->parse(pLine, startingIndex);
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
#ifndef _DEBUG
		else
		{
			std::cout << "ERROR! NULL material name detected inside the MTL file.\n at line: " << pLine << "\n";
		}
#endif // _DEBUG		
		assert(i_arrMaterialName != NULL);
		return isMTL_NAME_OK;
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="pLine"></param>
	/// <param name="startingIndex"></param>
	/// <returns></returns>
	bool mtl_element::parseMapKa(const char* pLine, int startingIndex)
	{
		return this->parseMapTagIntoArray(pLine, startingIndex, &i_arrMapKaFile);
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="pLine"></param>
	/// <param name="startingIndex"></param>
	/// <returns></returns>
	bool mtl_element::parseMapKd(const char* pLine, int startingIndex)
	{
		return this->parseMapTagIntoArray(pLine, startingIndex, &i_arrMapKdFile);
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="pLine"></param>
	/// <param name="startingIndex"></param>
	/// <returns></returns>
	bool mtl_element::parseMapKs(const char* pLine, int startingIndex)
	{
		return this->parseMapTagIntoArray(pLine, startingIndex, &i_arrMapKsFile);
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="pLine"></param>
	/// <param name="startingIndex"></param>
	/// <returns></returns>
	bool mtl_element::parseMapKe(const char* pLine, int startingIndex)
	{
		return this->parseMapTagIntoArray(pLine, startingIndex, &i_arrMapKeFile);
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="pLine"></param>
	/// <param name="startingIndex"></param>
	/// <returns></returns>
	bool mtl_element::parseMapNs(const char* pLine, int startingIndex)
	{
		return this->parseMapTagIntoArray(pLine, startingIndex, &i_arrMapNsFile);
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="pLine"></param>
	/// <param name="startingIndex"></param>
	/// <returns></returns>
	bool mtl_element::parseMapD(const char* pLine, int startingIndex)
	{
		return this->parseMapTagIntoArray(pLine, startingIndex, &i_arrMapDFile);
	}

	/// <summary>
	/// Helper method for:	
	///		- map_ka
	///		- map_kd
	/// TODO:
	/// it can be updated to support the options: "-options args"
	/// </summary>
	/// <param name="pLine"></param>
	/// <param name="startingIndex"></param>
	/// <param name="p_outArr"></param>
	/// <returns></returns>
	bool mtl_element::parseMapTagIntoArray(const char* pLine, int startingIndex, char** p_outArr)
	{
#ifdef _DEBUG
		assert((*p_outArr) == NULL);
#endif // _DEBUG
		int size = strlen(pLine) - startingIndex;
		bool isMTL_NAME_OK = size > 0;
		if (isMTL_NAME_OK)
		{
			(*p_outArr) = new char[size + 1];
			(*p_outArr)[size] = NULL;
			COPY_CHAR_ARRAYS(pLine, startingIndex, (*p_outArr), 0, size);
		}
#ifndef _DEBUG
		else
		{
			std::cout << "ERROR! NULL Map_Ka name detected inside the MTL file.\n at line: " << pLine << "\n";
		}
#endif // _DEBUG
		assert((*p_outArr) != NULL);
		return isMTL_NAME_OK;
	}

	/// <summary>
	/// 
	/// </summary>
	/// <returns>KA pointer of this class.</returns>
	const obj_vertex_element* mtl_element::getKA()
	{
		return this->KA;
	}

	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	const obj_vertex_element* mtl_element::getKD()
	{
		return this->KD;
	}

	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	const obj_vertex_element* mtl_element::getKS()
	{
		return this->KS;
	}

	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	const obj_vertex_element* mtl_element::getKE()
	{
		return this->KE;
	}


}