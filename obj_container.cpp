#include "obj_container.h"
#include "my_utils.h"
#include "obj_vertex_element.h"

#ifdef _DEBUG
#include <assert.h>
#endif // _DEBUG

namespace my_utils {

	obj_container::obj_container(): i_pObjName(NULL)
	{
		lstVertices = new linkedlist<obj_vertex_element>();
		lstTextures = new linkedlist<obj_vertex_element>();
		lstNormals = new linkedlist<obj_vertex_element>();
	}

	obj_container::~obj_container()
	{
		DELETE_PTR(i_pObjName);
		DELETE_PTR(lstVertices);
		DELETE_PTR(lstTextures);
		DELETE_PTR(lstNormals);
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="line">a NULL ending line</param>
	/// <param name="start">the position inside the "line" where to start the parsing from</param>
	/// <returns></returns>
	/// <returns></returns>
	bool obj_container::parse(const char* line, int start)
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

	bool obj_container::parseVertexArray(const char* pLine, int startIndex)
	{
		return parseFloatArray<obj_vertex_element>(this->lstVertices, pLine, startIndex);
		
	}

	bool obj_container::parseVertexTexture(const char* pLine, int startIndex)
	{
		return parseFloatArray<obj_vertex_element>(this->lstTextures, pLine, startIndex);
	}

	bool obj_container::parseVertexNormal(const char* pLine, int startIndex)
	{
		return parseFloatArray<obj_vertex_element>(this->lstNormals, pLine, startIndex);
	}

	/// <summary>
	/// a method that will parse the x,y,z double values and add them inside the "pList" list of values
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="pList"></param>
	/// <param name="pLine"></param>
	/// <param name="startIndex"></param>
	/// <returns></returns>
	template <class T> bool obj_container::parseFloatArray(linkedlist<T>* pList, const char* pLine, int startIndex)
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

	

	void obj_container::persist(std::ofstream* pOutputStream)
	{
		int noOfChars = strlen(this->i_pObjName) + 1; //add EOL too.
		//no of characters
		pOutputStream->write((char*)&noOfChars, sizeof(int));
		//name of the obj
		pOutputStream->write(this->i_pObjName, sizeof(char) * noOfChars);

		//no of vertices
		int vertices = this->lstVertices->size();
		pOutputStream->write((char*) &vertices, sizeof(int));
	}
}