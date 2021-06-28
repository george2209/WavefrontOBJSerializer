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

	class ternary_tag_node
	{
	public:
		ternary_tag_node();
		virtual ~ternary_tag_node();
	public:
		void addTagValue(const char * tag, unsigned int startIndex, int endIndex, E_OBJ_TAGS_t value);
		E_OBJ_TAGS_t getValue(const char* pLine, unsigned int startIndex, int endIndex);
	private:
		char tagChar;
		E_OBJ_TAGS_t tagValue;
		ternary_tag_node* left;
		ternary_tag_node* mid;
		ternary_tag_node* right;
	};
}

