#include "objparser.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
#include "StringUtils.h"
#include "ternary_search.h"
#include "ternary_tag_node.h"
#include "obj_container.h"
#include "my_utils.h"

namespace my_utils {
    obj_parser::obj_parser(std::ofstream * pOutputStream)
	{
        this->iTagSearchEngine = new ternary_search();
        iCurrentObjContainer = NULL;
        iOutputStream = pOutputStream;

        buildOBJTagsArray();
	}

    obj_parser::~obj_parser()
	{
        if (iCurrentObjContainer != NULL)
        {
            close();
        }
        DELETE_PTR(iTagSearchEngine);
	}

	/// <summary>
	/// fill in the tags vs tad id into the respective supplied array of tags
	/// </summary>
	/// <param name="objArr">a reference to an array of tags</param>
	void obj_parser::buildOBJTagsArray()
	{
        this->iTagSearchEngine->addTag("# ", E_OBJ_TAGS_t::OBJ_COMMENT);
        this->iTagSearchEngine->addTag("o ", E_OBJ_TAGS_t::OBJ_OBJ_NAME);
        this->iTagSearchEngine->addTag("v ", E_OBJ_TAGS_t::OBJ_VERTEX_ARRAY);
        this->iTagSearchEngine->addTag("vt ", E_OBJ_TAGS_t::OBJ_VERTEX_TEXTURE);
        this->iTagSearchEngine->addTag("vn ", E_OBJ_TAGS_t::OBJ_VERTEX_NORMAL);
        this->iTagSearchEngine->addTag("f ", E_OBJ_TAGS_t::OBJ_FACE);
        this->iTagSearchEngine->addTag("s ", E_OBJ_TAGS_t::OBJ_SMOOTHING);
        this->iTagSearchEngine->addTag("mtllib ", E_OBJ_TAGS_t::OBJ_MTL_FILE);
        this->iTagSearchEngine->addTag("usemtl ", E_OBJ_TAGS_t::OBJ_MTL_USE);
	}

    void obj_parser::processLine(const char* line)
    {
        my_utils::E_OBJ_TAGS_t lineTag; 
        this->iTagSearchEngine->getValue(line, &lineTag);

        switch (lineTag)
        {
        case my_utils::E_OBJ_TAGS_t::OBJ_COMMENT:
            break;
        case my_utils::E_OBJ_TAGS_t::OBJ_OBJ_NAME:
        {
            if (iCurrentObjContainer != NULL)
            {
                iCurrentObjContainer->persist(this->iOutputStream); 
                DELETE_PTR(iCurrentObjContainer);
            }
            
            iCurrentObjContainer = new obj_container();
            iCurrentObjContainer->parse(line, 2);//todo..replace the struct E_OBJ_TAGS_t with a class to return more values 2=length of this tag
            
        } break;
        case my_utils::E_OBJ_TAGS_t::OBJ_VERTEX_ARRAY:
        {
            iCurrentObjContainer->parseVertexArray(line, 2);//todo..replace the struct E_OBJ_TAGS_t with a class to return more values 2=length of this tag
        } break;
        case my_utils::E_OBJ_TAGS_t::OBJ_VERTEX_TEXTURE:     
        {
            iCurrentObjContainer->parseVertexTexture(line, 3);//todo..replace the struct E_OBJ_TAGS_t with a class to return more values 2=length of this tag
        } break;
        case my_utils::E_OBJ_TAGS_t::OBJ_VERTEX_NORMAL:
        {
            iCurrentObjContainer->parseVertexNormal(line, 3);//todo..replace the struct E_OBJ_TAGS_t with a class to return more values 2=length of this tag
        } break;
        case my_utils::E_OBJ_TAGS_t::OBJ_FACE:
        case my_utils::E_OBJ_TAGS_t::OBJ_MTL_FILE:
        case my_utils::E_OBJ_TAGS_t::OBJ_MTL_USE:
        case my_utils::E_OBJ_TAGS_t::OBJ_SMOOTHING:
        {
            std::cout << "Info: tag not serialized: " << (int)lineTag << "\n";
        }break;
        case my_utils::E_OBJ_TAGS_t::OBJ_NO_OF_TAGS:
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
        iCurrentObjContainer->persist(this->iOutputStream); //TODO..fix it!
        delete iCurrentObjContainer;
        iCurrentObjContainer = NULL;
    }
}

