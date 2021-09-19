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
		MTL_map_Ke
	};

//	using namespace std;
//	ostream& operator<<(ostream& os, const E_MTL_TAGS_t& tag)
//	{
//		switch (tag)
//		{
//		case E_MTL_TAGS_t::OBJ_INVALID_TAG:
//		{
//			os << "OBJ_INVALID_TAG";
//		} break;
//		case E_MTL_TAGS_t::MTL_COMMENT:
//		{
//			os << "MTL_COMMENT";
//		} break;
//		case E_MTL_TAGS_t::MTL_newmtl:
//		{
//			os << "MTL_newmtl";
//		} break;
//		case E_MTL_TAGS_t::MTL_Ka:
//		{
//			os << "MTL_Ka";
//		} break;
//		case E_MTL_TAGS_t::MTL_Kd:
//		{
//			os << "MTL_Kd";
//		} break;
//		case E_MTL_TAGS_t::MTL_Ks:
//		{
//			os << "MTL_Ks";
//		} break;
//		case E_MTL_TAGS_t::MTL_Ke:
//		{
//			os << "MTL_Ke";
//		} break;
//		case E_MTL_TAGS_t::MTL_Ns:
//		{
//			os << "MTL_Ns";
//		} break;
//		case E_MTL_TAGS_t::MTL_Ni:
//		{
//			os << "MTL_Ni";
//		} break;
//		case E_MTL_TAGS_t::MTL_d:
//		{
//			os << "MTL_d";
//		} break;
//		case E_MTL_TAGS_t::MTL_illum:
//		{
//			os << "MTL_illum";
//		} break;
//		case E_MTL_TAGS_t::MTL_map_Kd:
//		{
//			os << "MTL_map_Kd";
//		} break;		
//		default:
//		{
//			os << "ERROR! UNKNOWN TAG!" << (int)tag << "\n";
//#ifdef _DEBUG
//			assert(false);
//#else
//			break;
//#endif
//		}
//		}
//		
//		return os;
//	}
}
