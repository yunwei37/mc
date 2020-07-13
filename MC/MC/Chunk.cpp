#include"Chunk.h"

//int Chunk::generateHeight(double x, double y, double z) { //让随机种子，振幅，频率，应用于我们的噪音采样结果 
//	return PerlinNoise3D(x,y,z) + baseHeight;
//} 

Block::blockType Chunk::generateBlockType(int x, int y, int z, int h) {
	if (z > h) { //当前方块位置高于随机生成的高度值时，当前方块类型为空 
		return Block::Air;
	} 
	else if (z == h) { //当前方块位置等于随机生成的高度值时，当前方块类型为草地 
		return Block::Grass;
	} 
	//当前方块位置小于随机生成的高度值 且 大于 genHeight - 5时，当前方块类型为泥土 
	else if (z < h && z > h - 5) { 
		return Block::Soil;
	}  
	else return Block::Stone; //其他情况，当前方块类型为碎石
}

bool Chunk::isVisible(int x, int y, int z)
{	
	if (blocks[x][y][z] == Block::Air) {
		return false;
	}
	else {
		bool flag = false;
		Block::blockType type;
		if (x > 0) {
			type = blocks[x - 1][y][z];
			if (type == Block::Air || type == Block::Water) {
				flag = true;
			}
		}
		else {
			flag = true;
		}
		if (x < width-1) {
			type = blocks[x + 1][y][z];
			if (type == Block::Air || type == Block::Water) {
				flag = true;
			}
		}
		else {
			flag = true;
		}
		if (y > 0) {
			type = blocks[x][y-1][z];
			if (type == Block::Air || type == Block::Water) {
				flag = true;
			}
		}
		else {
			flag = true;
		}
		if (y < width - 1) {
			type = blocks[x][y+1][z];
			if (type == Block::Air || type == Block::Water) {
				flag = true;
			}
		}
		else {
			flag = true;
		}
		if (z > 0) {
			type = blocks[x][y][z-1];
			if (type == Block::Air || type == Block::Water) {
				flag = true;
			}
		}
		if (z < height-1) {
			type = blocks[x][y][z + 1];
			if (type == Block::Air || type == Block::Water) {
				flag = true;
			}
		}
		return flag;
	}
}

Chunk::Chunk(int x, int y)
{
	this->x = x;
	this->y = y;
	for (int i = 0; i < width; ++i) {
		for (int j = 0; j < width; ++j) {
			int h = (int)((PerlinNoise2D(i * 0.3, j * 0.3) + 1) * 10); //获取当前位置方块随机生成的高度值 
			for (int k = 0; k < height; ++k) {
				this->blocks[i][j][k] = generateBlockType(i, j, k, h);
			}
		}
	}
	for (int i = 0; i < width; ++i) {
		for (int j = 0; j < width; ++j) {
			for (int k = 0; k < height; ++k) {
				this->isRender[i][j][k] = isVisible(i,j,k);
			}
		}
	}
}

void Chunk::renderChunk(glm::mat4 model,unsigned int VAO, Shader* myShader)
{	
	Block::blockType type;
	Block::blockType lasttype = Block::Air;
	for (int i = 0; i < width; i++) {//z axis
		for (int j = 0; j < width; j++) {//y axis
			for (int k = 0; k < height; k++) {//1-4,x axis,height
				if (isRender[i][j][k]) {
					type = blocks[i][j][k];
					if (type != lasttype) {
						glActiveTexture(GL_TEXTURE0);
						glBindTexture(Block::textures[type].Type, Block::textures[type].ID);
						lasttype = type;
					}
					if (type != Block::Water) {
						//激活纹理单元： 
						glBindVertexArray(VAO);
						glDrawArrays(GL_TRIANGLES, 0, 36);
					}
				}
				model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f)); //height,x
				myShader->setMat4("model", glm::value_ptr(model));
			}
			model = glm::translate(model, glm::vec3((height) * 1.0f, 1.0f, 0.0f)); //y axis
			x++;
		}
		model = glm::translate(model, glm::vec3(0.0f, -width * 1.0f, 1.0f)); //z axis
		y++;
		x -= width;
	}
}