#include"Chunk.h"
#include"PerlinNoise.h"
int Chunk::generateHeight(double x, double y, double z) { //让随机种子，振幅，频率，应用于我们的噪音采样结果 
	return PerlinNoise3D(x,y,z) + baseHeight;
} 
blockType Chunk::generateBlockType(double Pos[3]) { 
	if (Pos[1] >= height) { //y坐标是否在Chunk内 
		return Air; 
	} 
	float genHeight = generateHeight(Pos[0],Pos[1],Pos[2]); //获取当前位置方块随机生成的高度值 
	if (Pos[1] > genHeight) { //当前方块位置高于随机生成的高度值时，当前方块类型为空 
		return Air; 
	} 
	else if (Pos[1] == genHeight) { //当前方块位置等于随机生成的高度值时，当前方块类型为草地 
		return Grass; 
	} 
	//当前方块位置小于随机生成的高度值 且 大于 genHeight - 5时，当前方块类型为泥土 
	else if (Pos[1] < genHeight && Pos[1] > genHeight - 5) { 
		return Soil; 
	}  
	else return Stone; //其他情况，当前方块类型为碎石
}

Chunk::Chunk()
{

}

/*void Chunk::buildChunk() {
	chunkMesh = new Mesh(); 
	List<Vector3> verts = new List<Vector3>(); 
	List<Vector2> uvs = new List<Vector2>(); 
	List<int> tris = new List<int>(); //遍历chunk, 生成其中的每一个Block 
	for (int x = 0; x < width; x ) { 
		for (int y = 0; y < height; y ) { 
			for (int z = 0; z < width; z ) { 
				buildBlock(x, y, z, verts, uvs, tris); 
			} 
		} 
	} 
	chunkMesh.vertices = verts.ToArray(); 
	chunkMesh.uv = uvs.ToArray(); 
	chunkMesh.triangles = tris.ToArray(); 
	chunkMesh.RecalculateBounds(); 
	chunkMesh.RecalculateNormals(); 
	meshFilter.mesh = chunkMesh; 
	meshCollider.sharedMesh = chunkMesh; 
} */