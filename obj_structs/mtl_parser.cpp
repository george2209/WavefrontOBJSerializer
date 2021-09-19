#include "mtl_parser.h"
#include <fstream> //ifstream
#include<iostream> //cout
#include <assert.h>
#include "../my_utils.h"
#include "mtl_element.h"
#include "../linkedlist.h"
#include "obj_structs.h"
#include "obj_vertex_element.h"
#include <unordered_map>

#ifdef _DEBUG
#include <direct.h> // _getcwd
#include <assert.h>
#endif // DEBUG




namespace my_utils {
	mtl_parser::mtl_parser() : i_MaterialNo(0)
	{
		this->i_pTagSearchEngine = new ternary_search<E_MTL_TAGS_t>();
		i_pMaterialContainer = new std::unordered_map<const char*, mtl_element*, mtl_hash_algoritm, mtl_hash_comparator>();
		this->i_pCurrentMaterial = NULL;

		buildOBJTagsArray();
	}

	mtl_parser::~mtl_parser()
	{
		//clean up the hash as it must control the life time of its values inside it
		for (auto it = i_pMaterialContainer->begin(); it != i_pMaterialContainer->end(); )
		{
			mtl_element* pTmp = it->second;
			assert(pTmp != NULL);
			i_pMaterialContainer->erase(it++);
			DELETE_PTR(pTmp);
		}

		DELETE_PTR(i_pMaterialContainer);
		DELETE_PTR(i_pTagSearchEngine);
		
	}

	/// <summary>
	/// fill in the tags vs tad id into the respective supplied array of tags
	/// </summary>
	/// <param name="objArr">a reference to an array of tags</param>
	void mtl_parser::buildOBJTagsArray()
	{
		this->i_pTagSearchEngine->addTag("# ", E_MTL_TAGS_t::MTL_COMMENT);
		this->i_pTagSearchEngine->addTag("newmtl ", E_MTL_TAGS_t::MTL_newmtl);
		this->i_pTagSearchEngine->addTag("Ka ", E_MTL_TAGS_t::MTL_Ka);
		this->i_pTagSearchEngine->addTag("Kd ", E_MTL_TAGS_t::MTL_Kd);
		this->i_pTagSearchEngine->addTag("Ks ", E_MTL_TAGS_t::MTL_Ks);
		this->i_pTagSearchEngine->addTag("Ke ", E_MTL_TAGS_t::MTL_Ke);
		this->i_pTagSearchEngine->addTag("Ns ", E_MTL_TAGS_t::MTL_Ns);
		this->i_pTagSearchEngine->addTag("Ni ", E_MTL_TAGS_t::MTL_Ni);
		this->i_pTagSearchEngine->addTag("d ", E_MTL_TAGS_t::MTL_d);
		this->i_pTagSearchEngine->addTag("illum ", E_MTL_TAGS_t::MTL_illum);
		this->i_pTagSearchEngine->addTag("map_Kd ", E_MTL_TAGS_t::MTL_map_Kd);
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="pName"></param>
	/// <param name="pOut"></param>
	void mtl_parser::getMaterialByName(const char* pName, mtl_element** pOut)
	{
		assert((*pOut) == NULL);
		for (auto it = i_pMaterialContainer->begin(); it != i_pMaterialContainer->end(); it++)
		{
			const char* pTmp = it->first;
			std::cout << strcmp(pName, pTmp)<<"\n";
		}

		mtl_element * pEl = i_pMaterialContainer->at(pName);
		*pOut = i_pMaterialContainer->at(pName);
	}

	void mtl_parser::persist(std::ofstream* pOutputStream)
	{
#ifdef _DEBUG
		assert(this->i_MaterialNo == this->i_pMaterialContainer->size());
#endif // _DEBUG
		//write the number of materials
		pOutputStream->write((char*)&(this->i_MaterialNo), sizeof(short));
		for (int i = 0; i < this->i_MaterialNo; i++)
		{
			//TODO: search for id inside hash map..this can be improved later if needed. no time now for less than 10 elements..sorry.
			//maybe switch on map with a defined comparator of the key by ID OR adding a second map <key=ID, value=name>
			//This may be a good case for a study of a proper container. I may come back here later.
			mtl_element* pElement = NULL;
			for (auto it= i_pMaterialContainer->begin(); it != i_pMaterialContainer->end(); )
			{
				if (it->second->getID() == i)
				{
					pElement = it->second;
					//we cannot erase it as we need it to match the id<->name inside OBJ file!
					//it = i_pMaterialContainer->erase(it);
					break;
				}
				//else {
					it++;
				//}
			}
			assert(pElement != NULL);
			//material name
			this->persistCharArray(pOutputStream, pElement->getMaterialName());
			//KA
			this->persistOptionalVertex(pOutputStream, pElement->getKA());
			//KD
			this->persistOptionalVertex(pOutputStream, pElement->getKD());
			//KS
			this->persistOptionalVertex(pOutputStream, pElement->getKS());
			//KE
			this->persistOptionalVertex(pOutputStream, pElement->getKE());
			//NS
			float floatVal = pElement->getNS();
			pOutputStream->write((char*)&floatVal, sizeof(float));
			//NI
			floatVal = pElement->getNI();
			pOutputStream->write((char*)&floatVal, sizeof(float));
			//d
			floatVal = pElement->getD();
			pOutputStream->write((char*)&floatVal, sizeof(float));
			//illum
			char charVal = pElement->getIllum();
			pOutputStream->write(&charVal, sizeof(char));
			//map_ka
			this->persistOptionalCharArray(pOutputStream, pElement->getMapKaFileName());
			//map_kd
			this->persistOptionalCharArray(pOutputStream, pElement->getMapKdFileName());
			//map_ks
			this->persistOptionalCharArray(pOutputStream, pElement->getMapKsFileName());
			//map_ke
			this->persistOptionalCharArray(pOutputStream, pElement->getMapKeFileName());
			//map_ns
			this->persistOptionalCharArray(pOutputStream, pElement->getMapNsFileName());
			//map_d
			this->persistOptionalCharArray(pOutputStream, pElement->getMapDFileName());
		}
		
	}

	bool mtl_parser::parse(const char* pFileName)
	{
		//INIT
		using namespace std;
		ifstream objStream;
		
		objStream.open(pFileName, ifstream::in);
		bool isStreamOK = objStream.good();
		assert(isStreamOK);
#ifdef _DEBUG
		if (isStreamOK) {
#endif  //_DEBUG
			int LINE_MAX_LENGTH = 512;
			char* buf = new char[LINE_MAX_LENGTH];
			while (isStreamOK) {
				memset(buf, 0, LINE_MAX_LENGTH);
				objStream.getline(buf, LINE_MAX_LENGTH);
				isStreamOK = objStream.good();
				if (strnlen(buf, LINE_MAX_LENGTH) > 0)
				{
					cout<< "\tMTL:: " << buf << "\n";
					this->processLine(buf);
				}
			}
			delete[] buf;
			buf = NULL;
#ifdef _DEBUG
		}
		else {

			int LINE_MAX_LENGTH = 2048;
			char* buf = new char[LINE_MAX_LENGTH];
			strerror_s(buf, LINE_MAX_LENGTH, errno);
			cerr << "Error: " << buf << "\n";
			_getcwd(buf, LINE_MAX_LENGTH);
			cout << "cannot open the MTL file: " << buf << " "<< pFileName << "\n";
			DELETE_ARR(buf);
			assert(isStreamOK);
		}
#endif  //_DEBUG

		//CLEANUP
		objStream.close();

		return true;
	}

	bool mtl_parser::processLine(const char* pLine)
	{
		E_MTL_TAGS_t lineTag;
		this->i_pTagSearchEngine->getValue(pLine, &lineTag);
		bool isSuccess = false;
		switch (lineTag)
		{
		case E_MTL_TAGS_t::MTL_COMMENT:
		{
			isSuccess = true;
		}
			break;
		case E_MTL_TAGS_t::MTL_newmtl:
		{
			this->i_pCurrentMaterial = new mtl_element(i_MaterialNo++);
			isSuccess = this->i_pCurrentMaterial->parseMaterialName(pLine, 7);
			assert(isSuccess);
			(*i_pMaterialContainer)[i_pCurrentMaterial->getMaterialName()] =  i_pCurrentMaterial;
		} break;
		case E_MTL_TAGS_t::MTL_Ka:
		{
			isSuccess = this->i_pCurrentMaterial->parseKA(pLine, 3);
		} break;
		case E_MTL_TAGS_t::MTL_Kd:
		{
			isSuccess = this->i_pCurrentMaterial->parseKD(pLine, 3);
		} break;
		case E_MTL_TAGS_t::MTL_Ks:
		{
			isSuccess = this->i_pCurrentMaterial->parseKS(pLine, 3);
		} break;
		case E_MTL_TAGS_t::MTL_Ke:
		{
			isSuccess = this->i_pCurrentMaterial->parseKE(pLine, 3);
		} break;
		case E_MTL_TAGS_t::MTL_Ni:
		{
			isSuccess = this->i_pCurrentMaterial->parseNI(pLine, 3);
		} break;
		case E_MTL_TAGS_t::MTL_Ns:
		{
			isSuccess = this->i_pCurrentMaterial->parseNS(pLine, 3);
		} break;
		case E_MTL_TAGS_t::MTL_d:
		{
			isSuccess = this->i_pCurrentMaterial->parseD(pLine, 2);
		} break;
		case E_MTL_TAGS_t::MTL_illum:
		{
			isSuccess = this->i_pCurrentMaterial->parseIllum(pLine, 6);
		} break;
		case E_MTL_TAGS_t::MTL_map_Kd:
		{
			isSuccess = this->i_pCurrentMaterial->parseMapKd(pLine, 7);
		} break;
		case E_MTL_TAGS_t::MTL_map_Ka:
		{
			isSuccess = this->i_pCurrentMaterial->parseMapKa(pLine, 7);
		} break;
		case E_MTL_TAGS_t::MTL_map_Ks:
		{
			isSuccess = this->i_pCurrentMaterial->parseMapKs(pLine, 7);
		} break;
		case E_MTL_TAGS_t::MTL_map_Ke:
		{
			isSuccess = this->i_pCurrentMaterial->parseMapKe(pLine, 7);
		} break;
		default:
			std::cout << "unsuported MTL Tag detected: " << (int)lineTag << "\n";
			break;
		}

		return isSuccess;
	}
}
