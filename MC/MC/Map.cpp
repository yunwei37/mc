#include "Map.h"
#include "particleGenerator.h"
#include "Chunk.h"
#include "particleGenerator.h"
#include "resource_manager.h"
extern const unsigned int SCR_WIDTH;
extern const unsigned int SCR_HEIGHT;

Map::Map(Camera* myCamera, int chunkSize):chunkSize(chunkSize)
{	
	myShader = new Shader("test_vs.txt", "test_fs.txt");
	this->myCamera = myCamera;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, Block::vsize, Block::vertices, GL_STATIC_DRAW);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(0 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	myShader->use();
	myShader->setInt("myTexture1", 0);

	//chunkSize = 9;
	int len = sqrt(chunkSize);
	for (int i = 0; i < len; ++i) {
		for (int j = 0; j < len; ++j) {
			chunks.push_back(new Chunk(i, j, CHUNK_WIDTH, CHUNK_HEIGHT));//render a chunk
		}
	}
}

Map::~Map()
{	
	for (int i = 0; i < chunkSize; ++i) {
		delete chunks[i];
	}
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	//glDeleteBuffers(1, &EBO);
}

void Map::renderMap()
{
	//变换：
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	view = myCamera->GetViewMatrix();
	projection = glm::perspective(glm::radians(myCamera->Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	myShader->setMat4("view", glm::value_ptr(view));
	myShader->setMat4("projection", glm::value_ptr(projection));
	model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	//myShader.setMat4("model", glm::value_ptr(model));
	for (int i = 0; i < chunkSize; ++i) {
		chunks[i]->renderChunk(model, VAO, myShader);
		if (i < chunkSize - 1 && chunkSize != 1) {
			int dx = chunks[i + 1]->x - chunks[i]->x;
			int dy = chunks[i + 1]->y - chunks[i]->y;
			model = glm::translate(model, glm::vec3(0.0f, CHUNK_WIDTH * dy * 1.0f, CHUNK_WIDTH * dx * 1.0f));
		}
	}
}
void Map::renderBlock(std::vector<operateBlock*> extraBlocks)
{//map_x, chunk_x横着, map_y, chunk_y竖着
	if (extraBlocks.size() == 0) return;//place no blocks
	int map_x = 0;
	int map_y = 0;
	int chunk_x = 0;
	int chunk_y = 0;
	int i = 0;
	int loop = 0;
	Block::blockType type;
	//变换：
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);
	view = myCamera->GetViewMatrix();
	projection = glm::perspective(glm::radians(myCamera->Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	myShader->setMat4("view", glm::value_ptr(view));
	myShader->setMat4("projection", glm::value_ptr(projection));
	for (int itr = 0; itr < extraBlocks.size(); itr++) {
		map_x = extraBlocks[itr]->mapCoord[0];
		map_y = extraBlocks[itr]->mapCoord[1];
		chunk_x = extraBlocks[itr]->chunkCoord[0];
		chunk_y = extraBlocks[itr]->chunkCoord[1];
		type = extraBlocks[itr]->type;
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		loop = map_y * sqrt(MAP_SIZE) + map_y;//get chunk position in map
		for (i = 0; i < loop; ++i) {
			if (i < chunkSize - 1) {
				int dx = chunks[i + 1]->x - chunks[i]->x;
				int dy = chunks[i + 1]->y - chunks[i]->y;
				model = glm::translate(model, glm::vec3(0.0f, CHUNK_WIDTH * dy * 1.0f, CHUNK_WIDTH * dx * 1.0f));
			}
		}
		//find block position in chunks[i]:	
		int hoffset = chunks[i]->visibleHeight[chunk_x][chunk_y]+1;//height to place extra block
		model = glm::translate(model, glm::vec3(hoffset*(-1.0f), chunk_x*1.0f, chunk_y*1.0f));
		//render the extra block:
		myShader->setMat4("model", glm::value_ptr(model));
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(Block::textures[type].Type, Block::textures[type].ID);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}
void Map::destroyBlock(std::vector<operateBlock*> delBlocks)//delete blocks
{
	ParticleGen* Particles;
	if (delBlocks.size() == 0) return;
	int map_x = 0;
	int map_y = 0;
	int chunk_x = 0;
	int chunk_y = 0;
	int chunkIdx = 0;
	ResourceManager::LoadShader("particle.vs", "particle.frag", nullptr, "particle");
	ResourceManager::LoadTexture("particle.png", GL_TRUE, "particle");
	Particles = new ParticleGen(
		ResourceManager::GetShader("particle"),
		ResourceManager::GetTexture("particle"),
		500
	);
	for (int itr = 0; itr < delBlocks.size(); itr++) {
		map_x = delBlocks[itr]->mapCoord[0];
		map_y = delBlocks[itr]->mapCoord[1];
		chunk_x = delBlocks[itr]->chunkCoord[0];
		chunk_y = delBlocks[itr]->chunkCoord[1];
		chunkIdx = map_y * sqrt(MAP_SIZE) + map_y;
		int h = chunks[chunkIdx]->visibleHeight[chunk_x][chunk_y];
		chunks[chunkIdx]->isRender[chunk_x][chunk_y][h] = false;
		chunks[chunkIdx]->isRender[chunk_x][chunk_y][h-1] = true;
//		Particles->Update(dt, , 2, glm::vec3);
 		Particles->Draw();
	}
}