#include "obj_root_element.h"
#include "../my_utils.h"
#include "obj_vertex_element.h"
#include "obj_face_element.h"
#include "rabin_karp_search.h"
#include "mtl_parser.h"

#ifdef _DEBUG
#include <assert.h>
#include<iostream>
#endif // _DEBUG

namespace my_utils {

	obj_root_element::obj_root_element(): i_pObjName(NULL), i_mtlID(INVALID_NUMBER)
	{
		lstFaces = new linkedlist<obj_face_element>();
	}

	obj_root_element::~obj_root_element()
	{
		DELETE_PTR(i_pObjName);
		DELETE_PTR(lstFaces);
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="line">a NULL ending line</param>
	/// <param name="start">the position inside the "line" where to start the parsing from</param>
	/// <param name="end">not used</param>
	/// <returns></returns>
	bool obj_root_element::parse(const char* line, int start, int end)
	{
#ifdef _DEBUG
		assert(this->i_pObjName == NULL);
#endif // _DEBUG

		int max_index = strlen(line);
		this->i_pObjName = new char[max_index - start + 1];
		this->i_pObjName[max_index - start] = NULL;
		for (int i = start; i < max_index; i++)
			this->i_pObjName[i - start] = line[i];

		return start < max_index;
	}

	bool obj_root_element::getParseMaterialName(const char* pLine, int startIndex, char** i_arrOut)
	{
#ifdef _DEBUG
		assert((*i_arrOut) == NULL);
#endif // _DEBUG

		int size = strlen(pLine) - startIndex;
		(*i_arrOut) = new char[size + 1];
		(*i_arrOut)[size] = NULL;

		COPY_CHAR_ARRAYS(pLine, startIndex, (*i_arrOut), 0, size);

		return true;
	}

	bool obj_root_element::parseVertexArray(const char* pLine, int startIndex, linkedlist<obj_vertex_element>* lstVertices)
	{
		return parseFloatArray<obj_vertex_element>(lstVertices, pLine, startIndex);
		
	}

	bool obj_root_element::parseVertexTexture(const char* pLine, int startIndex, linkedlist<obj_vertex_element>* lstTextures)
	{
		return parseFloatArray<obj_vertex_element>(lstTextures, pLine, startIndex);
	}

	bool obj_root_element::parseVertexNormal(const char* pLine, int startIndex, linkedlist<obj_vertex_element>* lstNormals)
	{
		return parseFloatArray<obj_vertex_element>(lstNormals, pLine, startIndex);
	}

	/// <summary>
	/// faces are of this form:
	/// "f 1/2/8 3/13/8 4/14/8"
	/// where:
	///  * "f " = face tag (will be ignored as the start index will be always >=1 (0 based).
	///  * "1/2/8"
	///  * "1" = vertex ID (1 based...substract 1 from this number!!!)
	///  * "2" = vertex texture ID --> "vt" array
	///  * "8" = vertex normal ID  --> "vn" array
	/// </summary>
	/// <param name="pLine"></param>
	/// <param name="startIndex"></param>
	/// <param name="endIndex">not used</param>
	/// <returns></returns>
	bool obj_root_element::parseFace(const char* pLine, int startIndex)
	{
		//split by faces.
		//the algorithm expects that the export from Blender is with faces as triangle not polygon! 
		//so always 3 faces are expected!
		const int NO_OF_FACE_VERTICES = 3;

		RabinKarpStringSearch search;
		int index = startIndex - 1;
		
		// first vertex info
		index = search.getIndexOf(pLine, " ", index + 1);
		parseVertexFace(pLine, startIndex, index);
		startIndex = index + 1;

		////second vertex info
		index = search.getIndexOf(pLine, " ", index + 1);
		parseVertexFace(pLine, startIndex, index);

		////third vertex info
		startIndex = index + 1;
		index = strlen(pLine);
		parseVertexFace(pLine, startIndex, index);
		
		return true;
	}

	void obj_root_element::parseVertexFace(const char* pLine, int startIndex, int index)
	{
		//int stringSize = index - startIndex;
		//char* tmpArray = new char[stringSize + 1];
		//tmpArray[stringSize] = NULL;
		//COPY_CHAR_ARRAYS(pLine, startIndex, tmpArray, 0, stringSize);
		//std::cout << "face: '" << tmpArray << "'\n";
		//DELETE_ARR(tmpArray);

		obj_face_element *pV1 = new obj_face_element();
		if (pV1->parse(pLine, startIndex, index))
		{
			this->lstFaces->addLast(pV1);
		}

	}

	/// <summary>
	/// a method that will parse the x,y,z double values and add them inside the "pList" list of values
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="pList"></param>
	/// <param name="pLine"></param>
	/// <param name="startIndex"></param>
	/// <returns></returns>
	template <class T> bool obj_root_element::parseFloatArray(linkedlist<T>* pList, const char* pLine, int startIndex)
	{
		T* pVertex = new T();
		if (pVertex->parse(pLine, startIndex))
		{
			pList->addLast(pVertex);
			return true;
		}
		else {
			return false;
		}
	}


	void obj_root_element::persist(std::ofstream* pOutputStream, obj_vertex_element* pArrVertices, obj_vertex_element* pArrTextures, obj_vertex_element* pArrNormals)
	{
		short noOfChars = (short) strlen(this->i_pObjName) + 1; //add EOL too.
		//no of characters
		pOutputStream->write((char*)&noOfChars, sizeof(short));
		//name of the obj
		pOutputStream->write(this->i_pObjName, sizeof(char) * noOfChars);

		//write the mtl ID
		pOutputStream->write((char*)&i_mtlID, sizeof(short));

		//no of faces
		int noOfFaces = this->lstFaces->size();
		pOutputStream->write((char*) &noOfFaces, sizeof(int));
#ifdef _DEBUG
		assert(noOfFaces%3 == 0);
#endif // _DEBUG
		//persist all faces(triangles)
		
		


		NODE_t<obj_face_element>* pFace = lstFaces->getFirstElement();
		for (int i = 0; i < noOfFaces; i++)
		{
			//write vertex coordinate
			{
				obj_vertex_element& vertex = pArrVertices[pFace->value->getVertexID()];
				pOutputStream->write((char*)&(vertex.x), sizeof(float));
				pOutputStream->write((char*)&(vertex.y), sizeof(float));
				pOutputStream->write((char*)&(vertex.z), sizeof(float));
			}

			//write vertex textures
			char textureSemaphore = 0;
			if (pArrTextures != NULL && pFace->value->getTextureID() > -1)
			{
				textureSemaphore = 1;
				pOutputStream->write((char*)&(textureSemaphore), sizeof(char));
				obj_vertex_element& vertex = pArrTextures[pFace->value->getTextureID()];
				pOutputStream->write((char*)&(vertex.x), sizeof(float)); //U
				pOutputStream->write((char*)&(vertex.y), sizeof(float)); //V
			}
			else {
				pOutputStream->write((char*)&(textureSemaphore), sizeof(char));
			}

			//write vertex normals
			char normalSemaphore = 0;
			if (pArrNormals != NULL && pFace->value->getNormalID() > -1)
			{
				normalSemaphore = 1;
				pOutputStream->write((char*)&(normalSemaphore), sizeof(char));
				obj_vertex_element& vertex = pArrNormals[pFace->value->getNormalID()];
				pOutputStream->write((char*) &(vertex.x), sizeof(float));
				pOutputStream->write((char*) &(vertex.y), sizeof(float));
				float ftmp = vertex.z;
				pOutputStream->write((char*) &ftmp, sizeof(float));
			}
			else {
				pOutputStream->write((char*)&(normalSemaphore), sizeof(char));
			}


			pFace = pFace->next;
		}

		pOutputStream->flush();		
		DELETE_PTR(lstFaces);

		//rebuild all the lists in case use have more obejcts inside the OBJ file
		//lstFaces = new linkedlist<obj_face_element>();
	}
}