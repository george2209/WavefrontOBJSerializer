#pragma once

#include "ternary_tag_node.h"
#include <string.h> //strlen

namespace my_utils {

	class obj_tag;

	/// <summary>
	/// This class will use the Ternary Search Tree in order to respond to an OBJ matching tag.
	/// Reason was that in case the number of supported OBJ tags will grow the previous O(m*lg(n)) implementation may become inefficient over large files.
	/// This class can be omited as the implementation was done inside the ternary_tag_node class, however it is here kept for simplicity in understanding the code.
	/// This is why the methods are actualy declared as "inline".
	/// </summary>
	class ternary_search
	{
	public:
		ternary_search();
		virtual ~ternary_search();

		inline void addTag(const char* tag, E_OBJ_TAGS_t value)
		{
			this->root.addTagValue(tag, 0, strlen(tag), value);
		};

		inline void getValue(const char* pLine, E_OBJ_TAGS_t* pOut)
		{
			this->root.getValue(pLine, 0, strlen(pLine), pOut);
		}

	private:
		ternary_tag_node root;
	};
}

