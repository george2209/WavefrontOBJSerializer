#pragma once
namespace my_utils {
	class abstractobj
	{
	public:
		virtual bool parse(const char* pLine, int startIndex) = 0;
	};
}

