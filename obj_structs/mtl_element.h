#pragma once

namespace my_utils
{
	class obj_vertex_element;
	class mtl_element
	{
	public:
		mtl_element(short id);
		~mtl_element();
		bool parseMaterialName(const char* pLine, int startingIndex);
		bool parseKA(const char* pLine, int startingIndex);
		bool parseKD(const char* pLine, int startingIndex);
		bool parseKS(const char* pLine, int startingIndex);
		bool parseKE(const char* pLine, int startingIndex);
		bool parseNS(const char* pLine, int startingIndex);
		bool parseNI(const char* pLine, int startingIndex);
		bool parseD(const char* pLine, int startingIndex);
		bool parseIllum(const char* pLine, int startingIndex);
		bool parseMapKa(const char* pLine, int startingIndex);
		bool parseMapKd(const char* pLine, int startingIndex);
		bool parseMapKs(const char* pLine, int startingIndex);
		bool parseMapKe(const char* pLine, int startingIndex);
		bool parseMapNs(const char* pLine, int startingIndex);
		bool parseMapD(const char* pLine, int startingIndex);
		bool parseMapBump(const char* pLine, int startingIndex);
	
	public:
		inline const char* getMaterialName()
		{
			return this->i_arrMaterialName;
		};
		const obj_vertex_element* getKA();
		const obj_vertex_element* getKD();
		const obj_vertex_element* getKS();
		const obj_vertex_element* getKE();
		inline float getNS() { return NS; };
		inline float getNI() { return NI; };
		inline float getD() { return d; };
		inline char getIllum() { return illum; };
		inline float getBumpBM() { return this->i_map_bump_bm; }
		inline short getID() { return this->i_ID; };
		inline const char* getMapKdFileName() { return this->i_arrMapKdFile; };
		inline const char* getMapKaFileName() { return this->i_arrMapKaFile; };
		inline const char* getMapKsFileName() { return this->i_arrMapKsFile; };
		inline const char* getMapKeFileName() { return this->i_arrMapKeFile; };
		inline const char* getMapNsFileName() { return this->i_arrMapNsFile; };
		inline const char* getMapDFileName() { return this->i_arrMapDFile; };
		inline const char* getMapBumpFileName() { return this->i_arrMapBumpFile; };

	private:
		bool parseVertexElement(obj_vertex_element *& pElement, const char* pLine, int startingIndex);
		bool parseMapTagIntoArray(const char* pLine, int startingIndex, char ** p_outArr);
		bool parseFloat(float* pElement, const char* pLine, int startingIndex);
		
	private:
		obj_vertex_element* KA; //material ambient is multiplied by the texture value
		obj_vertex_element* KD; //material diffuse is multiplied by the texture value
		obj_vertex_element* KS; //material specular is multiplied by the texture value
		obj_vertex_element* KE; //emissive coeficient. It goes together with ambient, 
								//diffuse and specular and represents the amount of light emitted by the material. 
								//If you also have a defined emission color the material will irradiate light.
		float NS; //focus of specular highlight; Specifies the specular exponent for the current material.
				  //Ns values normally range from 0 to 1000.
		float NI; //optical density; index of refraction
				  //NI The values can range from 0.001 to 10.
		float d; //specifies a factor for dissolve; 1->Opaque, 0=Transparent
		char illum; //specifies the illumination model to use in the material.
					 //can be a number from 0 to 10.
					 //The illumination models are summarized below:
					 //	0		Color on and Ambient off
					 // 1		Color on and Ambient on
					 // 2		Highlight on
					 //	3		Reflection on and Ray trace on
					 //	4		Transparency: Glass on
					 //	Reflection : Ray trace on
					 //	5		Reflection : Fresnel on and Ray trace on
					 //	6		Transparency : Refraction on
					 //	Reflection : Fresnel off and Ray trace on
					 //	7		Transparency : Refraction on
					 //	Reflection : Fresnel on and Ray trace on
					 //	8		Reflection on and Ray trace off
					 //	9		Transparency : Glass on
					 //	Reflection : Ray trace off
					 //	10		Casts shadows onto invisible surfaces
		char* i_arrMaterialName;
		char* i_arrMapKaFile; // Specifies that a color texture file or a color procedural texture file 
							  // is applied to the ambient reflectivity of the material.During
							  // rendering, the "map_Ka" value is multiplied by the "Ka" value.
		char* i_arrMapKdFile; //Specifies that a color texture file or color procedural texture file is 
							  //linked to the diffuse reflectivity of the material.During rendering,
							  //the map_Kd value is multiplied by the Kd value.
		
		char* i_arrMapKsFile; //Specifies that a color texture file or color procedural texture file is 
							   //linked to the specular reflectivity of the material.During rendering,
							   //the map_Ks value is multiplied by the Ks value.

		char* i_arrMapKeFile; //Specifies that the "emissive  coeficient" :
								//Ke and map_Ke for emissive color equivalents to Kd and map_Kd 
								//the map_Ke value is multiplied by the Ke value.

		char* i_arrMapNsFile; //Specifies that a scalar texture file or scalar procedural texture file 
							   //is linked to the specular exponent of the material.During rendering,
							   //the map_Ns value is multiplied by the Ns value.

		char* i_arrMapDFile; // Specifies that a scalar texture file or scalar procedural texture file 
							 //is linked to the dissolve of the material.During rendering, the map_d
							 //value is multiplied by the d value.

		char* i_arrMapBumpFile; // Specifies that a bump texture file is linked to the material. To be see how this is working against the normal.
								// Supported parameters : only bm = float[0.0…1.0]
		float i_map_bump_bm;


		//map_aat not implemented.
		
		const short i_ID; //will be used to reference the material inside of the OBJ file.
	};
}