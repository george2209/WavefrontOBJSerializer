#include "obj_face_element.h"
#include "rabin_karp_search.h"
#include <stdlib.h>// strtol
#include "../my_utils.h"
#include<iostream> //cout
#include <assert.h>

namespace my_utils {

	obj_face_element::obj_face_element()
	{
		iVertexID = -1;
		iTextureID = -1;
		iNormalID = -1;
	}

	/// <summary>
	/// parse a face vertex. 
	/// A face will alwas have exactly three vertices (unless it was wrongly exported from Blender).
	/// See documentation on how to export correctly from Blender inside the docs folder.
	/// expected text format:
	/// <vertex_id>/<*textureID>/<*normal ID>
	/// * => optional
	// Example of correct strings expected between "startIndex" and "endIndex":
	/// 2 -> only the vertex is present. No UV and no Normal vertices are inside.
	/// 2//1 -> only vertex and normal are present.
	/// 2/1/3 -> all elements present: vertex, texture coordinate and normal
	/// Note:
	/// In case you are debuging, the OBJ file is 1 based index and not 0 based index.
	/// </summary>
	/// <param name="pLine"></param>
	/// <param name="startIndex"></param>
	/// <param name="endIndex"></param>
	/// <returns></returns>
	bool obj_face_element::parse(const char* pLine, int startIndex, int endIndex)
	{
		if (endIndex - startIndex == 1)
		{
			//only vertex info available.
			CHAR_ARRAY_TO_INT(pLine, startIndex, endIndex, &iVertexID);
			iVertexID--; // 0 index!! not 1 index!!
		}
		else {
			RabinKarpStringSearch search;
			int index = search.getIndexOf(pLine, "/", startIndex);
			if (index == -1)
			{
				std::cout << "this shall never happend! No / separator for the face vertices? Have you export it correctly? See documentation on Blender export!" << "\n";
				assert(index != -1);
			}
			else {
				//vertex info
				CHAR_ARRAY_TO_INT(pLine, startIndex, index, &iVertexID);
				iVertexID--;
				if (pLine[index + 1] != '/')
				{
					//texture info
					startIndex = index + 1;
					index = search.getIndexOf(pLine, "/", startIndex);
					//texture info
					CHAR_ARRAY_TO_INT(pLine, startIndex, index, &iTextureID);
					iTextureID--;
				}
				else {
					//no texture coordinate available
					index += 1; //advance 1 step as expected is to have the "//<*normal ID>".
				}

				if (index +1 != endIndex)
				{
					assert(pLine[index] == '/');

					//normal info
					startIndex = index + 1;
					CHAR_ARRAY_TO_INT(pLine, startIndex, endIndex, &iNormalID);
					iNormalID--;
				}

			}
		}

		return true;
	}
}