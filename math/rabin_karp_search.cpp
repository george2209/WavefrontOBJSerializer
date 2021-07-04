#include "rabin_karp_search.h"
#include <math.h>//pow 
#include <string.h> //strlen

namespace my_utils {

	RabinKarpStringSearch::RabinKarpStringSearch() : Q(997), R(10)
	{

	}

	/// <summary>
	/// return the index of the "pattern" starting form "startingIndex" inside of "line"
	/// </summary>
	/// <param name="line">a line of text of length minimum strlen(patter). This must be a NULL terminated string!</param>
	/// <param name="pattern">a NULL terminated string with a size at most equal with the line parameter</param>
	/// <param name="startingIndex">a parameter to search inside the line from</param>
	/// <returns>the index of the starting element of the pattern or -1 if not found</returns>
	int RabinKarpStringSearch::getIndexOf(const char* line, const char* pattern, unsigned int startingIndex)
	{

		return getIndexOf(line, pattern, startingIndex, strlen(line));
	}

	/// <summary>
	/// Calculate a hash of a set of numbers based on Horner method.
	/// https://en.wikipedia.org/wiki/Horner%27s_method
	/// Formula used:
	/// Xi = [t(i) * POW(R,noOfDigits-1) + t(i+1) * POW(R, noOfDigits-2) .... t(i+noOfDigits-1)*POW(R,0)] % Q
	///   where:
	///    * R = 10 (base 10)
	///    * t(i) = line[i]
	///    * Q = 253 (a prime number)
	///    * noOfDigits = the length of the pattern
	///
	/// !!! IMPORTANT: !!!
	/// The upper formula is the simplified one for any i=[0..noOfDigits). 
	/// If we exceed the number "noOfDigits" for i (that is the usual case as the "line" size is expected to be larger than the sub-sequence no of digits)
	/// then we need to substract each time the previous first element, then make a shift in POW(R,noOfDigits-1) to the left by one position 
	/// (by multipling the result by R) then adding the new t(i+M-1)*POW(R,0) and then making again the MOD Q operation.
	///
	/// If you are curious you can check the document "docs/Rabin-Karp_Horner_explanation_20210629_V1.0.pptx" for details.
	///
	/// </summary>
	/// <param name="line">a NULL terminated string</param>
	/// <param name="pattern">a NULL terminated string pattern that will be search into the "line"</param>
	/// <param name="start">the current position inside the "line" to start searching</param>
	/// <param name="end">the end of the search. This will be the length of "line" if you want to search over complete "line" string</param>
	/// <returns>the position (first character) inside le line -1 in case of pattern was not found</returns>
	int RabinKarpStringSearch::getIndexOf(const char* line, const char* pattern, unsigned int start, unsigned int end )
	{
		unsigned int noOfDigits = strlen(pattern);
		int expectedPattern = getStringHash(pattern, 0, noOfDigits);
		if (end - start < noOfDigits)
		{
			return -1;
		}
		else if (end - start == noOfDigits)
		{
			if (expectedPattern == getStringHash(line, start, end))
			{
				if (isSpuriousHitPass(line, start, pattern))
				{
					return start; //success
				}
				
			}
		}
		else {
			int hash = getStringHash(line, start, start + noOfDigits);
			if (hash == expectedPattern &&
				isSpuriousHitPass(line, start, pattern))
			{
				return start;
			}
			else {
				unsigned int r_pow = (unsigned int)pow(R, noOfDigits - 1);
				for (unsigned int i = start + noOfDigits; i < end; i++) {
					hash = (hash - (line[i - noOfDigits] * r_pow) % Q) * R + line[i];
					hash = hash % Q;
					if (hash == expectedPattern &&
						isSpuriousHitPass(line, i, pattern))
					{
						return i + 1 - noOfDigits;
					}
				}
			}
		}

		return -1; //fail
	}

	/// <summary>
	/// calculate the hash of the "line" string from start until end.
	/// </summary>
	/// <param name="line"></param>
	/// <param name="start"></param>
	/// <param name="end"></param>
	/// <param name="noOfDigits"></param>
	/// <returns></returns>
	int RabinKarpStringSearch::getStringHash(const char* line, unsigned int start, unsigned int end)
	{
		int hash = 0;
		unsigned int noOfDigits = end - start;
		for (unsigned int i = start; i < end; i++)
		{
			hash += line[i] * ((unsigned int)pow(R, noOfDigits - (i - start) - 1));
			hash = hash % Q;
		}
		return hash;
	}

	/// <summary>
	/// This method shall be called when you have a hit inside the <code>getStringHash</code> 
	/// method to check if this is a false or true positive hit.
	/// Basically will check if the pattern really matches, by checking each character starting with "startIndex".
	/// </summary>
	/// <param name="line"></param>
	/// <param name="startIndex"></param>
	/// <param name="pattern"></param>
	/// <returns>return true if there is a match or false in case of a sporious hit (worng string)</returns>
	bool RabinKarpStringSearch::isSpuriousHitPass(const char* line, unsigned int startIndex, const char* pattern)
	{
		unsigned int size = strlen(pattern);
		bool isPass = true;
		for (unsigned int i = startIndex; i < size && isPass; i++)
		{
			isPass = line[i] == pattern[i - startIndex];
		}
		return isPass;
	}
}
