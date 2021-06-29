#include "rabin_karp_search.h"
#include <math.h>//pow 

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

		return -1;
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
	/// <param name="line"></param>
	/// <param name="start">the current position inside the "line"</param>
	/// <param name="noOfDigits"> 
	/// So if you need to calculate for example from a char array the characters 2 to 4 (inclusive 4th one) then you put here 5! </param>
	/// <param name="previousHash">it can be 0 if there was no previous hash</param>
	/// <returns>the calculated hash after Horner method</returns>
	unsigned int RabinKarpStringSearch::getHash(const char* line, unsigned int start, unsigned int end, unsigned int noOfDigits)
	{
		unsigned int hash = 0;
		if (end - start == noOfDigits)
		{
			for (unsigned int i = start; i < end; i++)
			{
				hash += line[i] * ((unsigned int)pow(R, noOfDigits-(i-start)-1) );
				hash = hash % Q;
			}
		}
		else {
			hash = getHash(line, start, start + noOfDigits, noOfDigits);
			unsigned int r_pow = (unsigned int)pow(R, noOfDigits - 1);
			for (unsigned int i = start + noOfDigits; i < end; i++) {
				hash = (hash - (line[i - noOfDigits] * r_pow) % Q) * R + line[i];
				hash = hash % Q;
			}
		}

		return hash;
	}
}
