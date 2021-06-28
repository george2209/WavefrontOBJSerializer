#include "StringUtils.h"
#include "StringUtils.h"

namespace my_utils {

    /// <summary>
   /// search if the line is starting with the string value of stringPattern
   /// </summary>
   /// <param name="stringLine">a string that must be longer than the stringPattern</param>
   /// <param name="stringPattern">a pattern string that will be check against</param>
   /// <param name="patternLength">the length of the pattern string to avoid checking all the time the length of the string</param>
   /// <returns></returns>
    bool StringUtils::isStartingWith(const char* stringLine, const char* stringPattern, unsigned int patternLength)
    {
        return searchString(stringLine, stringPattern, 0, patternLength);
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="stringLine"></param>
    /// <param name="stringPattern"></param>
    /// <param name="start"></param>
    /// <param name="end"></param>
    /// <returns></returns>
    bool StringUtils::searchString(const char* stringLine, const char* stringPattern, unsigned short start, unsigned short end) {
        if (start == end)
        {
            return stringLine[start] == stringPattern[start];
        }
        else {
            unsigned short midPivot = start + (end - start) / 2;
            bool isMatch = stringLine[midPivot] == stringPattern[midPivot];
            if (midPivot + 1 < end)
                isMatch = isMatch && searchString(stringLine, stringPattern, midPivot + 1, end);
            if (start <= midPivot - 1)
                isMatch = isMatch && searchString(stringLine, stringPattern, start, midPivot - 1);

            return isMatch;
        }
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="strLine">a NULL terminated array of chars</param>
    /// <param name="stringPattern">a NULL terminated array of chars</param>
    /// <param name="startIndex"></param>
    /// <returns>an index where the "stringPattern" was found inside the "strLine" starting from index "startIndex". 
    /// If EOL (NULL terminated) was found OR if the "stringPattern" is not inside then it returns -1.</returns>
    int StringUtils::indexOf(const char* strLine, const char* stringPattern, unsigned int startIndex)
    {
        return -1;
    }
}
