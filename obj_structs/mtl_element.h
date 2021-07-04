#pragma once

namespace my_utils
{
	class mtl_element
	{
	public:
		mtl_element();
		~mtl_element();
		bool parseMaterialName(const char* pLine, int startingIndex);
	private:
		char* i_arrMaterialName;
	};
}