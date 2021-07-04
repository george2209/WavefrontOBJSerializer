#pragma once

#include <stdio.h>
namespace my_utils {
#define INVALID_INT (-1)
#define INVALID_CHAR (-1)

#define DELETE_PTR(__ptr__) \
if (__ptr__ != NULL) \
{ \
	delete __ptr__; \
	__ptr__ = NULL; \
}

#define DELETE_ARR(__arr__) \
if(__arr__ != NULL) \
{ \
	delete [] __arr__; \
	__arr__ = NULL; \
}

#define COPY_CHAR_ARRAYS(__source_, __source_start_index, __destination, __destination_start_index, __length) \
for (int i = 0; i < __length; i++) \
{ \
	__destination[i+__destination_start_index] = __source_[i+__source_start_index];\
}

#define CHAR_ARRAY_TO_INT(__source_, __source_start_index, __source_end_index, __ptr_int_out) \
{ \
	const int SIZE = __source_end_index - __source_start_index; \
	char* pTmp = new char[SIZE + 1]; \
	pTmp[SIZE] = NULL; \
	for (int i = 0; i < SIZE; i++) \
	{ \
		pTmp[i] = __source_[i + __source_start_index]; \
	} \
	*(__ptr_int_out) = strtol(pTmp, NULL, 10); \
	DELETE_ARR(pTmp); \
}

}
