#pragma once

#include <stdio.h>
namespace my_utils {
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

}
