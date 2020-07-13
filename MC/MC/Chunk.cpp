#include"Chunk.h"

int Chunk::generateHeight(double x, double y, double z) { //让随机种子，振幅，频率，应用于我们的噪音采样结果 
	return PerlinNoise3D(x,y,z) + baseHeight;
} 
Block::blockType Chunk::generateBlockType(double Pos[3]) {
	if (Pos[1] >= height) { //y坐标是否在Chunk内 
		return Block::Air;
	} 
	float genHeight = generateHeight(Pos[0],Pos[1],Pos[2]); //获取当前位置方块随机生成的高度值 
	if (Pos[1] > genHeight) { //当前方块位置高于随机生成的高度值时，当前方块类型为空 
		return Block::Air;
	} 
	else if (Pos[1] == genHeight) { //当前方块位置等于随机生成的高度值时，当前方块类型为草地 
		return Block::Grass;
	} 
	//当前方块位置小于随机生成的高度值 且 大于 genHeight - 5时，当前方块类型为泥土 
	else if (Pos[1] < genHeight && Pos[1] > genHeight - 5) { 
		return Block::Soil;
	}  
	else return Block::Stone; //其他情况，当前方块类型为碎石
}

Chunk::Chunk()
{

}

void Chunk::renderChunk(glm::mat4 model,unsigned int VAO, Shader* myShader)
{
	int z = 0, x = 0, y = 0;//block position in chunk	

	for (int i = 0; i < width; i++) {//z axis
		for (int j = 0; j < width; j++) {//y axis
			z = (int)((PerlinNoise2D(x * 0.3, y * 0.3) + 1) * 10);
			for (int k = 0; k < z + baseHeight; k++) {//1-4,x axis,height
				/*if (k == 0 || k == x+chunk.baseHeight || j == 0 || i == chunk.width) {
					glCullFace(GL_BACK);
				}
				else glCullFace(GL_FRONT_AND_BACK);*/
				glBindVertexArray(VAO);
				glDrawArrays(GL_TRIANGLES, 0, 36);
				model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f)); //height,x
				myShader->setMat4("model", glm::value_ptr(model));
			}
			model = glm::translate(model, glm::vec3((z + baseHeight) * 1.0f, 1.0f, 0.0f)); //y axis
			x++;
		}
		model = glm::translate(model, glm::vec3(0.0f, -width * 1.0f, 1.0f)); //z axis
		y++;
		x -= width;
	}
}

int Chunk::generateChunk(double x, double y)
{
	return 0;
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