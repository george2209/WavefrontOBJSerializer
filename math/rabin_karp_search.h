#pragma once
namespace my_utils {
	class RabinKarpStringSearch
	{
	public:
		RabinKarpStringSearch();
		int getIndexOf(const char* line, const char* pattern, unsigned int startingIndex);
	public:
		unsigned int getHash(const char* line, unsigned int start, unsigned int end, unsigned int noOfDigits);
	private:
		const int Q;
		const int R;
	};
}

