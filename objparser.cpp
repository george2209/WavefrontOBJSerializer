#include "objparser.h"
#include <stdio.h>
#include <string.h> //strlen
#include <iostream>
#include "ternary_search.h"
#include "ternary_tag_node.h"
#include "obj_root_element.h"
#include "mtl_parser.h"
#include "my_utils.h"

namespace my_utils {
    obj_parser::obj_parser(std::ofstream * pOutputStream)
	{
        this->i_pTagSearchEngine = new ternary_search<E_OBJ_TAGS_t>();
        this->i_pMTLParser = new mtl_parser();
        i_pCurrentObjContainer = NULL;
        i_pOutputStream = pOutputStream;

        buildOBJTagsArray();
	}

    obj_parser::~obj_parser()
	{
        if (i_pCurrentObjContainer != NULL)
        {
            close();
        }
        DELETE_PTR(i_pTagSearchEngine);
        DELETE_PTR(i_pMTLParser);
	}

	/// <summary>
	/// fill in the tags vs tad id into the respective supplied array of tags
	/// </summary>
	/// <param name="objArr">a reference to an array of tags</param>
	void obj_parser::buildOBJTagsArray()
	{
        this->i_pTagSearchEngine->addTag("# ", E_OBJ_TAGS_t::OBJ_COMMENT);
        this->i_pTagSearchEngine->addTag("o ", E_OBJ_TAGS_t::OBJ_OBJ_NAME);
        this->i_pTagSearchEngine->addTag("v ", E_OBJ_TAGS_t::OBJ_VERTEX_ARRAY);
        this->i_pTagSearchEngine->addTag("vt ", E_OBJ_TAGS_t::OBJ_VERTEX_TEXTURE);
        this->i_pTagSearchEngine->addTag("vn ", E_OBJ_TAGS_t::OBJ_VERTEX_NORMAL);
        this->i_pTagSearchEngine->addTag("f ", E_OBJ_TAGS_t::OBJ_FACE);
        this->i_pTagSearchEngine->addTag("s ", E_OBJ_TAGS_t::OBJ_SMOOTHING);
        this->i_pTagSearchEngine->addTag("mtllib ", E_OBJ_TAGS_t::OBJ_MTL_FILE);
        this->i_pTagSearchEngine->addTag("usemtl ", E_OBJ_TAGS_t::OBJ_MTL_USE);
	}

    void obj_parser::processLine(const char* pLine)
    {
        my_utils::E_OBJ_TAGS_t lineTag; 
        this->i_pTagSearchEngine->getValue(pLine, &lineTag);

        switch (lineTag)
        {
        case my_utils::E_OBJ_TAGS_t::OBJ_COMMENT:
            break;
        case my_utils::E_OBJ_TAGS_t::OBJ_OBJ_NAME:
        {
            if (i_pCurrentObjContainer != NULL)
            {
                i_pCurrentObjContainer->persist(this->i_pOutputStream); 
                DELETE_PTR(i_pCurrentObjContainer);
            }
            
            i_pCurrentObjContainer = new obj_root_element();
            i_pCurrentObjContainer->parse(pLine, 2);//todo..replace the struct E_OBJ_TAGS_t with a class to return more values 2=length of this tag
            
        } break;
        case my_utils::E_OBJ_TAGS_t::OBJ_VERTEX_ARRAY:
        {
            i_pCurrentObjContainer->parseVertexArray(pLine, 2);//todo..replace the struct E_OBJ_TAGS_t with a class to return more values 2=length of this tag
        } break;
        case my_utils::E_OBJ_TAGS_t::OBJ_VERTEX_TEXTURE:     
        {
            i_pCurrentObjContainer->parseVertexTexture(pLine, 3);//todo..replace the struct E_OBJ_TAGS_t with a class to return more values 2=length of this tag
        } break;
        case my_utils::E_OBJ_TAGS_t::OBJ_VERTEX_NORMAL:
        {
            i_pCurrentObjContainer->parseVertexNormal(pLine, 3);//todo..replace the struct E_OBJ_TAGS_t with a class to return more values 2=length of this tag
        } break;
        case my_utils::E_OBJ_TAGS_t::OBJ_FACE:
        {
            i_pCurrentObjContainer->parseFace(pLine, 2);
        } break;
        case my_utils::E_OBJ_TAGS_t::OBJ_MTL_FILE:
        {
            int size = strlen(pLine) - 7; //7="mtllib " 
            char* pFileName = new char[size + 1]; // 1 NULL termination
            pFileName[size] = NULL;
            COPY_CHAR_ARRAYS(pLine, 7, pFileName, 0, size);
            i_pMTLParser->parse(pFileName);
            DELETE_ARR(pFileName);
        } break;
        case my_utils::E_OBJ_TAGS_t::OBJ_MTL_USE:
        case my_utils::E_OBJ_TAGS_t::OBJ_SMOOTHING:
        {
            std::cout << "Info: tag not serialized: " << (int)lineTag << "\n";
        }break;
        case my_utils::E_OBJ_TAGS_t::OBJ_INVALID_TAG:
        default:
            std::cout << "unknown tag: " << (int)lineTag << "\n";
            throw "UNKNOWN TAG EXCEPTION";
        }
    }

    /// <summary>
    /// release all the resources used by this class
    /// </summary>
    void obj_parser::close()
    {
        i_pCurrentObjContainer->persist(this->i_pOutputStream); //TODO..fix it!
        delete i_pCurrentObjContainer;
        i_pCurrentObjContainer = NULL;
    }
}

