#include"Chunk.h"

Chunk::Chunk(int x, int y)
{
	this->x = x;
	this->y = y;
	isLoad = true;
	for (int i = 0; i < CHUNKWIDTH; ++i) {
		for (int j = 0; j < CHUNKWIDTH; ++j) {
			for (int k = 0; k < CHUNKHEIGHT; ++k) {
				blocks[i][j][k] = Block::Air;
				isRender[i][j][k] = false;
			}
		}
	}
	for (int k = 0; k < CHUNKHEIGHT; ++k) {
		layerRender[k] = false;
	}
}


void Chunk::renderChunk(glm::mat4 model, unsigned int VAO, Shader* myShader)
{
	Block::blockType type;
	Block::blockType lasttype = Block::Air;
	for (int k = 0; k < CHUNKHEIGHT; k++) {//1-4,x axis,height
		if (layerRender[k]) {
			for (int i = 0; i < CHUNKWIDTH; i++) {//z axis
				for (int j = 0; j < CHUNKWIDTH; j++) {//y axis
					if (isRender[i][j][k]) {
						myShader->setMat4("model", glm::value_ptr(model));
						type = blocks[i][j][k];
						if (type != lasttype) {
							glActiveTexture(GL_TEXTURE0);
							glBindTexture(Block::textures[type].Type, Block::textures[type].ID);
							lasttype = type;
						}
						//激活纹理单元： 
						glBindVertexArray(VAO);
						glDrawArrays(GL_TRIANGLES, 0, 36);
					}
					model = glm::translate(model, glm::vec3(0.0f, 1.0f, 0.0f)); //y axis
				}
				model = glm::translate(model, glm::vec3(0.0f, -CHUNKWIDTH * 1.0f, 1.0f)); //z axis
			}
		}
		model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -CHUNKWIDTH * 1.0f)); //height,x
	}
	model = glm::translate(model, glm::vec3((CHUNKHEIGHT) * 1.0f, 0.0f, 0.0f)); //y axis
}

void Chunk::updateRenderInformation()
{
	for (int k = 0; k < CHUNKHEIGHT; ++k) {
		bool flag = false;
		for (int i = 0; i < CHUNKWIDTH; ++i) {
			for (int j = 0; j < CHUNKWIDTH; ++j) {
				if (isRender[i][j][k]) {
					flag = true;
				}
			}
		}
		layerRender[k] = flag;
	}
}
