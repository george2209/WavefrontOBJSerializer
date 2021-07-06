# WavefrontOBJSerializer
This is a serializer into a binary format from the Wavefront OBJ file.
You may want to use this file to directly load into the memory the OBJ object(s) inside an OBJ file (MTL files are supported and MUST be located into the same folder like OBJ file).

Constraints:
1. Only triangulated faces supported at this moment
2. No smooth directive is supported
3. MTL "Ka R G B" is supported but no support for "Ka spectral..."

Binary format:
- see file "docs/OBJ to binary structure_20210611_V1.0.pptx"

![binary file structure](/docs/binary_format.png)

Export from Blender:
- If you want to export the OBJ from Blender you must use those settings to have an OBJ file compatible with this converter.
![Blender export settings](/docs/blender_export.png)

New requests?
- Add a new "Issue" and maybe you'll have it.
