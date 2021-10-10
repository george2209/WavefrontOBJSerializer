#pragma once
#include "../my_utils.h"
#include <ostream>
#ifdef _DEBUG
#include <assert.h>
#endif // _DEBUG



namespace my_utils {

	class E_PARSER_OPTIONS
	{
	public:
		E_PARSER_OPTIONS() : OBJ_CLASS_PATH(NULL), OBJ_FILE_NAME(NULL), BIN_FILE_NAME(NULL)
		{};
		~E_PARSER_OPTIONS()
		{
			DELETE_ARR(OBJ_CLASS_PATH);
			DELETE_ARR(OBJ_FILE_NAME);
			DELETE_ARR(BIN_FILE_NAME);
		};
		char* OBJ_CLASS_PATH;
		char* OBJ_FILE_NAME;
		char* BIN_FILE_NAME;
	};

	enum class E_OBJ_TAGS_t
	{
		OBJ_INVALID_TAG = INVALID_NUMBER,
		OBJ_COMMENT = 0,
		OBJ_OBJ_NAME,
		OBJ_VERTEX_ARRAY,
		OBJ_VERTEX_TEXTURE,
		OBJ_VERTEX_NORMAL,
		OBJ_FACE,
		OBJ_SMOOTHING,
		OBJ_MTL_FILE,
		OBJ_MTL_USE
	};

	enum class E_MTL_TAGS_t
	{
		OBJ_INVALID_TAG = INVALID_NUMBER,
		MTL_COMMENT = 0,
		MTL_newmtl,
		MTL_Ka,
		MTL_Kd,
		MTL_Ks,
		MTL_Ke,
		MTL_Ns,
		MTL_Ni,
		MTL_d,
		MTL_illum,
		MTL_map_Kd,
		MTL_map_Ka,
		MTL_map_Ks,
		MTL_map_Ke,
		MTL_map_Ns,
		MTL_map_d,
		MTL_map_Bump

	};
}
