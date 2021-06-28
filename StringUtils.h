#pragma once

namespace my_utils {
	class StringUtils
	{
	public:
		static bool isStartingWith(const char* stringLine, const char* stringPattern, unsigned int patternLength);
		static bool searchString(const char* stringLine, const char* stringPattern, unsigned short start, unsigned short end);
		static int indexOf(const char* strLine, const char* stringPattern, unsigned int startIndex);
	};
}

