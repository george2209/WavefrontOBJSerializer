#pragma once

#include <iterator> // For std::forward_iterator_tag
#include <cstddef>  // For std::ptrdiff_t

namespace my_utils {
	template <class T> struct NODE_t
	{
		T* value;
		NODE_t<T>* next;
	};

	template <class T> class linkedlist
	{
	public:
		linkedlist<T>()
		{
			listSize = 0;
			pFirst = NULL;
			pLast = NULL;
		};

		~linkedlist<T>()
		{
			NODE_t<T>* pTmp = NULL;
			while (pFirst != NULL)
			{
				pTmp = pFirst->next;
				delete pFirst;
				pFirst = pTmp;
			}
		};

		void addLast(T*& val)
		{
			if (listSize == 0)
			{
				pFirst = new NODE_t<T>();
				pFirst->value = val;
				pFirst->next = NULL;
			}
			else {
				if (pFirst->next == NULL)
				{
					pLast = new NODE_t<T>();
					pLast->value = val;
					pLast->next = NULL;
					pFirst->next = pLast;
				}
				else {
					pLast->next = new NODE_t<T>();
					pLast->next->value = val;
					pLast->next->next = NULL;
					pLast = pLast->next;
				}
			}
			listSize++;
		};

		//maybe implement an iterator..I prefere not adding too much overhead if not needed.
		NODE_t<T>* getFirstElement() 
		{
			return this->pFirst;
		};

		int size() { return listSize; };
	private:
		NODE_t<T>* pFirst;
		NODE_t<T>* pLast;
		int listSize;
	};
};

