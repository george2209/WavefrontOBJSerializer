#pragma once

namespace my_utils {
	class obj_face_element
	{
	public:
		obj_face_element();

		bool parse(const char* pLine, int startIndex, int endIndex = -1);
		inline int getVertexID()
		{
			return iVertexID;
		};
		inline int getTextureID()
		{
			return iTextureID;
		};
		inline int getNormalID()
		{
			return iNormalID;
		};
	private:
		int iVertexID;
		int iTextureID;
		int iNormalID;
	};
}

