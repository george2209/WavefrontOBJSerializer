#pragma once

#include "obj_structs.h"

#include "ternary_tag_node.h"
#include <string.h> //strlen
#include "../my_utils.h"

namespace my_utils {
	
	/// <summary>
	/// This class will use the Ternary Search Tree in order to respond to an OBJ matching tag.
	/// Reason was that in case the number of supported OBJ tags will grow the previous O(m*lg(n)) implementation may become inefficient over large files.
	/// This class can be omited as the implementation was done inside the ternary_tag_node class, however it is here kept for simplicity in understanding the code.
	/// This is why the methods are actualy declared as "inline".
	/// </summary>
	template <class T> class ternary_search
	{
	public:
		ternary_search()
		{
			i_pRoot = new ternary_tag_node<T>();
		};
		virtual ~ternary_search()
		{
			DELETE_PTR(i_pRoot);
		};

		void addTag(const char* tag, T value)
		{
			this->i_pRoot->addTagValue(tag, 0, strlen(tag), value);
		};
		void getValue(const char* pLine, T* pOut)
		{
			this->i_pRoot->getValue(pLine, 0, strlen(pLine), pOut);
		};

	private:
		ternary_tag_node<T> * i_pRoot;
	};
}

