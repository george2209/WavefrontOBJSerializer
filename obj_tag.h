#pragma once

namespace my_utils {

	enum class E_OBJ_TAGS_t
	{
		OBJ_COMMENT = 0,
		OBJ_OBJ_NAME,
		OBJ_VERTEX_ARRAY,
		OBJ_VERTEX_TEXTURE,
		OBJ_VERTEX_NORMAL,
		OBJ_FACE,
		OBJ_SMOOTHING,
		OBJ_MTL_FILE,
		OBJ_MTL_USE,
		OBJ_NO_OF_TAGS,
		OBJ_INVALID_TAG
	};

	class obj_tag
	{
	public:
		obj_tag(int tagSize, E_OBJ_TAGS_t tagType);
	public:
		const int tagSize;
		const E_OBJ_TAGS_t tagType;
	};
}

