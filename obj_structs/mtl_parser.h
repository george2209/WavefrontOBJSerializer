#pragma once
#include "ternary_search.h"
#include <unordered_map>
#include <fstream>
#include "abstractserializer.h"


namespace my_utils {

	enum class E_MTL_TAGS_t;
	class mtl_element;
	class obj_vertex_element;

	/*template<
		class Key,
		class T,
		class Hash = std::hash<Key>,
		class KeyEqual = std::equal_to<Key>,
		class Allocator = std::allocator< std::pair<const Key, T> >
	> class std::unordered_map;*/

	struct mtl_hash_algoritm
	{
		/// <summary>
		/// a hash algorithm following the Horner method
		/// </summary>
		/// <param name="val"></param>
		/// <returns></returns>
		size_t operator() (const char * val) const {
			int Q = 231; //a random prime number smaller than (but close to) char max value
			int R = 10; //base 10
			int hashVal = 0;
			int M = strlen(val);
			for (int i = 0; i < M; i++)
			{
				hashVal += (val[i] * (int)pow(R, (M - (i + 1)))) % Q;
			}
			return hashVal;
		}
	};

	struct mtl_hash_comparator
	{
		inline bool operator()(const char* c1, const char* c2) const {
			int i = strcmp(c1, c2);
			std::cout << "res=" << i<<"\n";
			return i == 0;
		}
	};
	

	class mtl_parser : protected abstractserializer
	{
	public:
		mtl_parser();
		~mtl_parser();
		bool parse(const char* pFileName);
		void persist(std::ofstream* pOutputStream);
		void getMaterialByName(const char* pName, mtl_element** pOut);
	private:
		void buildOBJTagsArray();
		bool processLine(const char* line);
	private:
		ternary_search<E_MTL_TAGS_t>* i_pTagSearchEngine;
		std::unordered_map<const char*, mtl_element*, mtl_hash_algoritm, mtl_hash_comparator>* i_pMaterialContainer;
		mtl_element* i_pCurrentMaterial;
		short i_MaterialNo;
	};
}

