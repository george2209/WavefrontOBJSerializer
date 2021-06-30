#pragma once
namespace my_utils {
	class RabinKarpStringSearch
	{
	public:
		RabinKarpStringSearch();
		int getIndexOf(const char* line, const char* pattern, unsigned int startingIndex);
	private:
		int getIndexOf(const char* line, const char* pattern, unsigned int start, unsigned int end);
		int getStringHash(const char* line, unsigned int start, unsigned int end);
		bool isSpuriousHitPass(const char* line, unsigned int startIndex, const char* pattern);
	private:
		const int Q;
		const int R;
	};
}

