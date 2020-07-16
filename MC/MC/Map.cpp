#include "Map.h"
#include "particleGenerator.h"
#include "Chunk.h"
#include "resource_manager.h"
#include "MapGenerator.h"
extern const unsigned int SCR_WIDTH;
extern const unsigned int SCR_HEIGHT;

int Map::getBlockIndex(int x, int y)
{
	x = x / Chunk::width;
	y = y / Chunk::width;
	for (int i = 0; i < chunkSize; ++i) {
		if (chunks[i]->x == x && chunks[i]->y == y) {
			return i;
		}
	}
	return -1;
}

Map::Map(Camera* myCamera)
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

	chunkSize = 0;
	currentChunkMaxX = 3;
	currentChunkMinX = 0;
	currentChunkMaxY = 3;
	currentChunkMinY = 0;
	startPosX = currentChunkMinX * Chunk::width;
	startPosY = currentChunkMinY * Chunk::width;
	for (int i = currentChunkMinX; i <= currentChunkMaxX; ++i) {
		for (int j = currentChunkMinY; j <= currentChunkMaxY; ++j) {
			chunks.push_back(new Chunk(i, j));//render a chunk
			generateBlock(chunkSize);
			chunkSize++;
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
		if (chunks[i]->isLoad) {
			chunks[i]->renderChunk(model, VAO, myShader);
		}
		if (i < chunkSize - 1 && chunkSize != 1) {
			int dx = chunks[i + 1]->x - chunks[i]->x;
			int dy = chunks[i + 1]->y - chunks[i]->y;
			model = glm::translate(model, glm::vec3(0.0f, Chunk::width * dy * 1.0f, Chunk::width * dx * 1.0f));
		}
	}
	//std::cout << myCamera->Position.x << " " << myCamera->Position.y << " " << myCamera->Position.z << " " << endl;
}

void Map::updateMap()
{
	//std::cout << myCamera->Position.x << " " << myCamera->Position.y << " " << myCamera->Position.z << " " << endl;
	if (myCamera->Position.z + startPosX > currentChunkMaxX * Chunk::width) {
		for (int i = 0; i < chunkSize; ++i) {
			if (chunks[i]->x == currentChunkMinX) {
				chunks[i]->isLoad = false;
			}
		}
		currentChunkMinX++;
		for (int j = currentChunkMinY; j <= currentChunkMaxY; ++j) {
			chunks.push_back(new Chunk(currentChunkMaxX + 1, j));//render a chunk
			generateBlock(chunkSize);
			chunkSize++;
		}
		currentChunkMaxX++;
	}
	/*
	else if (myCamera->Position.z + startPosX < (currentChunkMinX + 1) * Chunk::width) {
		for (int i = 0; i < chunkSize; ++i) {
			if (chunks[i]->x == currentChunkMaxX) {
				chunks[i]->isLoad = false;
			}
		}
		currentChunkMaxX--;
		for (int j = currentChunkMinY; j <= currentChunkMaxY; ++j) {
			chunks.push_back(new Chunk(currentChunkMinX - 1, j));//render a chunk
			generateBlock(chunkSize);
			chunkSize++;
		}
		currentChunkMinX--;
	}
	*/

	else if (myCamera->Position.y + startPosY > currentChunkMaxY * Chunk::width) {
		for (int i = 0; i < chunkSize; ++i) {
			if (chunks[i]->y == currentChunkMinY) {
				chunks[i]->isLoad = false;
			}
		}
		currentChunkMinY++;
		for (int j = currentChunkMinX; j <= currentChunkMaxX; ++j) {
			chunks.push_back(new Chunk(j, currentChunkMaxY + 1));//render a chunk
			generateBlock(chunkSize);
			chunkSize++;
		}
		currentChunkMaxY++;
	}
	/*
	else if (myCamera->Position.y + startPosY < (currentChunkMinY + 1) * Chunk::width) {
		for (int i = 0; i < chunkSize; ++i) {
			if (chunks[i]->y == currentChunkMaxY) {
				chunks[i]->isLoad = false;
			}
		}
		currentChunkMaxY--;
		for (int j = currentChunkMinX; j <= currentChunkMaxX; ++j) {
			chunks.push_back(new Chunk(j, currentChunkMinY - 1));//render a chunk
			generateBlock(chunkSize);
			chunkSize++;
		}
		currentChunkMinY--;
	}
	*/
}

void Map::setBlock(int x, int y, int z, Block::blockType type)
{
	assert(x <= (currentChunkMaxX + 1) * Chunk::width);
	assert(x >= currentChunkMinX * Chunk::width);
	assert(y <= (currentChunkMaxY + 1) * Chunk::width);
	assert(y >= currentChunkMinY * Chunk::width);
	int index = getBlockIndex(x, y);
	assert(index != -1);
	if (x < 0) {
		x = -chunks[index]->x * Chunk::width + x;
	}
	else {
		x = x % Chunk::width;
	}
	if (y < 0) {
		y = -chunks[index]->y * Chunk::width + y;
	}
	else {
		y = y % Chunk::width;
	}
	assert(x < Chunk::width&& x > 0);
	assert(y < Chunk::width&& y > 0);
	chunks[index]->blocks[x][y][z] = type;
	// 如果不是空气，设置可见
	if(type!=Block::Air)
		chunks[index]->isRender[x][y][z] = true;
	// 设置周围方块为可见
	setBlock(x - 1, y, z, getBlockType(x - 1, y, z)); 
	setBlock(x + 1, y, z, getBlockType(x + 1, y, z));
	setBlock(x, y - 1, z, getBlockType(x, y - 1, z));
	setBlock(x, y - 1, z, getBlockType(x, y - 1, z));
	setBlock(x, y, z + 1, getBlockType(x, y, z + 1));
	setBlock(x, y, z - 1, getBlockType(x, y, z - 1));
}

Block::blockType Map::getBlockType(int x, int y, int z)
{
	if (x > (currentChunkMaxX + 1) * Chunk::width) {
		return Block::Air;
	}
	else if (x < currentChunkMinX * Chunk::width) {
		return Block::Air;
	}
	else if (y > (currentChunkMaxY + 1) * Chunk::width) {
		return Block::Air;
	}
	else if (y < currentChunkMinY * Chunk::width) {
		return Block::Air;
	}
	int index = getBlockIndex(x, y);
	assert(index != -1);
	if (x < 0) {
		x = -chunks[index]->x * Chunk::width + x;
	}
	else {
		x = x % Chunk::width;
	}
	if (y < 0) {
		y = -chunks[index]->y * Chunk::width + y;
	}
	else {
		y = y % Chunk::width;
	}
	assert(x < Chunk::width&& x > 0);
	assert(y < Chunk::width&& y > 0);
	return chunks[index]->blocks[x][y][z];
}
