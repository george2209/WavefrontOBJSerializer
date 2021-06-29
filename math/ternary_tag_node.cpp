#include "ternary_tag_node.h"
#include "../my_utils.h"
#include <iostream> //cout
namespace my_utils {
#define INVALID_CHAR (-1)

	ternary_tag_node::ternary_tag_node() : left(NULL), right(NULL), mid(NULL)
	{
		tagChar = INVALID_CHAR;
		tagValue = E_OBJ_TAGS_t::OBJ_INVALID_TAG;
	}
	
	ternary_tag_node::~ternary_tag_node()
	{
		DELETE_PTR(this->left);
		DELETE_PTR(this->mid);
		DELETE_PTR(this->right);
	}

	void ternary_tag_node::addTagValue(const char* tag, unsigned int startIndex, int endIndex, E_OBJ_TAGS_t value)
	{
		if (this->tagChar == INVALID_CHAR || this->tagChar == tag[startIndex])
		{
			this->tagChar = tag[startIndex];
			if (startIndex == endIndex - 1)
			{
#ifdef _DEBUG
				if (this->tagValue != E_OBJ_TAGS_t::OBJ_INVALID_TAG)
				{
					std::cout << "ERROR! tag " << tag << " was already added!\n";
					throw "tag already added exception";
				}
#endif // _DEBUG
				this->tagValue = value;
			}
			else {
				if (this->mid == NULL)
					mid = new  ternary_tag_node();
				this->mid->addTagValue(tag, ++startIndex, endIndex, value);
			}
		}
		else {
			if (this->tagChar > tag[startIndex])
			{
				if(this->left == NULL)
					left = new ternary_tag_node();
				this->left->addTagValue(tag, startIndex, endIndex, value);
			}
			else {
				if (this->right == NULL)
					right = new  ternary_tag_node();
				this->right->addTagValue(tag, startIndex, endIndex, value);
			}
		}
	}

	void ternary_tag_node::getValue(const char* pLine, unsigned int startIndex, int endIndex, E_OBJ_TAGS_t* pOut)
	{
		if (pLine[startIndex] == this->tagChar)
		{
			if ((this->tagValue != E_OBJ_TAGS_t::OBJ_INVALID_TAG) ||
				(startIndex == endIndex - 1))
			{
				*pOut = this->tagValue; //match found!
			}		
			else 
			{
				if (this->mid != NULL)
					this->mid->getValue(pLine, ++startIndex, endIndex, pOut);
				else
					*pOut = E_OBJ_TAGS_t::OBJ_INVALID_TAG;
			}
		}
		else {
			if (pLine[startIndex] < this->tagChar)
			{
				if(this->left != NULL)
					this->left->getValue(pLine, startIndex, endIndex, pOut);
				else 
					*pOut = E_OBJ_TAGS_t::OBJ_INVALID_TAG;
			}
			else {
				if(this->right != NULL)
					this->right->getValue(pLine, startIndex, endIndex, pOut);
				else
					*pOut = E_OBJ_TAGS_t::OBJ_INVALID_TAG;
			}
		}
	}
}
