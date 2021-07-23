#pragma once

#include <iterator> // For std::forward_iterator_tag
#include <cstddef>  // For std::ptrdiff_t

namespace my_utils {
	template <class T> struct NODE_t
	{
		T* value;
		NODE_t<T>* next;
	};

	/// <summary>
	/// A linked list class template that will keep a pointer of its elements.
	/// The elements life-time is contoled by this list, meaning they will be deleted once the list
	/// is deleted from stack. 
	/// No need to take care about this outside this list!
	/// </summary>
	/// <typeparam name="T"></typeparam>
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

		void addLast(T* val)
		{
			if (listSize == 0)
			{
				pFirst = new NODE_t<T>();
				pFirst->value = val;
				pFirst->next = NULL;
				pLast = pFirst;
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

		/// <summary>
		/// will load the content into the already initialized array.
		/// use <code>size</code> method to initialize the array at the proper size
		/// </summary>
		/// <param name="arrOut"></param>
		void asArray(T* arrOut) {
			NODE_t<T>* pTmp = pFirst;;
			for (int i = 0; i < listSize; i++)
			{
				arrOut[i] = *(pTmp->value);
				pTmp = pTmp->next;
			}
		};

		//maybe implement an iterator..I prefere not adding too much overhead if not needed.
		NODE_t<T>* getFirstElement() 
		{
			return this->pFirst;
		};

		NODE_t<T>* getLastElement()
		{
			return this->pLast;
		};

		inline int size() { return listSize; };
	private:
		NODE_t<T>* pFirst;
		NODE_t<T>* pLast;
		int listSize;
	};
};

