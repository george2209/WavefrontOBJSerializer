#pragma once
#include "abstractobj.h"
#include "ternary_search.h"

namespace my_utils {

	enum class E_MTL_TAGS_t
	{
		MTL_COMMENT = 0,
		MTL_newmtl,
		MTL_Ka,
		MTL_Kd,
		MTL_Ks,
		MTL_Ns,
		MTL_Ni,
		MTL_d,
		MTL_illum,
		MTL_map_Kd,
		OBJ_INVALID_TAG
	};

	class mtl_element;
	template <class T> class linkedlist;

	class mtl_parser
	{
	public:
		mtl_parser();
		~mtl_parser();
		bool parse(const char* pFileName);
		//bool parse(const char* pLine, int startIndex, int endIndex = -1);
	private:
		void buildOBJTagsArray();
		bool processLine(const char* line);
	private:
		ternary_search< E_MTL_TAGS_t>*iTagSearchEngine;
		linkedlist<mtl_element>* i_pMaterialsList;
		mtl_element* i_pCurrentMaterial;
	};
}

