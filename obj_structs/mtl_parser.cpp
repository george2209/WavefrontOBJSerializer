#include "mtl_parser.h"
#include <fstream> //ifstream
#include<iostream> //cout
#include <assert.h>
#include "../my_utils.h"
#include "mtl_element.h"
#include "../linkedlist.h"


#include <direct.h> // _getcwd

namespace my_utils {
	mtl_parser::mtl_parser()
	{
		this->iTagSearchEngine = new ternary_search< E_MTL_TAGS_t>();
		this->i_pMaterialsList = new linkedlist< mtl_element>();
		this->i_pCurrentMaterial = NULL;

		buildOBJTagsArray();
	}

	mtl_parser::~mtl_parser()
	{
		//DELETE_PTR(i_pCurrentMaterial); //not needed as the element is part of linkedlist
		DELETE_PTR(i_pMaterialsList);
		DELETE_PTR(iTagSearchEngine);
	}

	/// <summary>
	/// fill in the tags vs tad id into the respective supplied array of tags
	/// </summary>
	/// <param name="objArr">a reference to an array of tags</param>
	void mtl_parser::buildOBJTagsArray()
	{
		this->iTagSearchEngine->addTag("# ", E_MTL_TAGS_t::MTL_COMMENT);
		this->iTagSearchEngine->addTag("newmtl ", E_MTL_TAGS_t::MTL_newmtl);
		this->iTagSearchEngine->addTag("Ka ", E_MTL_TAGS_t::MTL_Ka);
		this->iTagSearchEngine->addTag("Kd ", E_MTL_TAGS_t::MTL_Kd);
		this->iTagSearchEngine->addTag("Ks ", E_MTL_TAGS_t::MTL_Ks);
		this->iTagSearchEngine->addTag("Ns ", E_MTL_TAGS_t::MTL_Ns);
		this->iTagSearchEngine->addTag("Ni ", E_MTL_TAGS_t::MTL_Ni);
		this->iTagSearchEngine->addTag("d ", E_MTL_TAGS_t::MTL_d);
		this->iTagSearchEngine->addTag("illum ", E_MTL_TAGS_t::MTL_illum);
		this->iTagSearchEngine->addTag("map_Kd ", E_MTL_TAGS_t::MTL_map_Kd);
	}

	bool mtl_parser::parse(const char* pFileName)
	{
		//INIT
		using namespace std;
		ifstream objStream;
		objStream.open(pFileName, ifstream::in);

		bool isStreamOK = objStream.good();
		if (isStreamOK) {
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

		//CLEANUP
		objStream.close();
		return true;
	}

	bool mtl_parser::processLine(const char* pLine)
	{
		my_utils::E_MTL_TAGS_t lineTag;
		this->iTagSearchEngine->getValue(pLine, &lineTag);
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
			this->i_pCurrentMaterial = new mtl_element();
			this->i_pMaterialsList->addLast(this->i_pCurrentMaterial);
			isSuccess = this->i_pCurrentMaterial->parseMaterialName(pLine, 7);
		} break;
		default:
			break;
		}

		return isSuccess;
	}

	//bool mtl_parser::parse(const char* pLine, int startIndex, int endIndex)
	//{

	//}
}
