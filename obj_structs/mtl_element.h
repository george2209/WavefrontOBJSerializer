#pragma once

namespace my_utils
{
	class obj_vertex_element;
	class mtl_element
	{
	public:
		mtl_element();
		~mtl_element();
		bool parseMaterialName(const char* pLine, int startingIndex);
		bool parseKA(const char* pLine, int startingIndex);
		bool parseKD(const char* pLine, int startingIndex);
		bool parseKS(const char* pLine, int startingIndex);
		bool parseKE(const char* pLine, int startingIndex);
	
	public:
		inline obj_vertex_element* getKA();
		inline obj_vertex_element* getKD();
		inline obj_vertex_element* getKS();
		inline obj_vertex_element* getKE();

	private:
		bool parseVertexElement(obj_vertex_element * pElement, const char* pLine, int startingIndex);
		
	private:
		obj_vertex_element* KA; //material ambient is multiplied by the texture value
		obj_vertex_element* KD; //material diffuse is multiplied by the texture value
		obj_vertex_element* KS; //material specular is multiplied by the texture value
		obj_vertex_element* KE; //emissive coeficient. It goes together with ambient, 
								//diffuse and specular and represents the amount of light emitted by the material. 
								//If you also have a defined emission color the material will irradiate light.
		char* i_arrMaterialName;
	};
}