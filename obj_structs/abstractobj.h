#pragma once
namespace my_utils {
	class abstractobj
	{
	public:
		virtual bool parse(const char* pLine, int startIndex, int endIndex = -1) = 0;
	};
}

