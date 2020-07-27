#include "Map.h"
extern const unsigned int SCR_WIDTH;
extern const unsigned int SCR_HEIGHT;

int Map::getBlockIndex(int x, int y)
{
	x = x / Chunk::width;//chunk在map中的坐标
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
	glBufferData(GL_ARRAY_BUFFER, Map::vsize, Map::vertices, GL_STATIC_DRAW);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(0 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	myShader->use();
	myShader->setInt("myTexture1", 0);

	chunkSize = 0;
	currentChunkMaxX = 4;
	currentChunkMinX = 0;
	currentChunkMaxY = 4;
	currentChunkMinY = 0;
	startPosX = currentChunkMinX * Chunk::width;
	startPosY = currentChunkMinY * Chunk::width;
	for (int i = currentChunkMinX; i <= currentChunkMaxX; ++i) {
		for (int j = currentChunkMinY; j <= currentChunkMaxY; ++j) {
			chunks.push_back(new Chunk(i, j));//render a chunk
			chunkGenerator::generateBlock(*chunks[chunkSize]);
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



void Map::renderMap(operateBlock* changeBlock)
{
	if (changeBlock->mapCoord[0] != -1)
		this->setBlock(changeBlock->mapCoord, changeBlock->type);
	//变换：
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	view = myCamera->GetViewMatrix();
	projection = glm::perspective(glm::radians(myCamera->Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	myShader->setMat4("view", glm::value_ptr(view));
	myShader->setMat4("projection", glm::value_ptr(projection));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	//myShader.setMat4("model", glm::value_ptr(model));
	model = glm::translate(model, glm::vec3(0.0f, Chunk::width * chunks[0]->x * 1.0f, Chunk::width * chunks[0]->y * 1.0f));
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
}

void Map::updateMap()
{
	limitCamera();
	bool isChange = false;
	//std::cout << currentChunkMaxX * Chunk::width << endl;
	//std::cout << myCamera->Position.x << " " << myCamera->Position.y << " " << myCamera->Position.z << " " << endl;
	if (myCamera->Position.z + startPosX > (currentChunkMaxX - 1) * Chunk::width) {
		for (int i = 0; i < chunkSize; ++i) {
			if (chunks[i]->x == currentChunkMinX) {
				chunks[i]->isLoad = false;
			}
		}
		currentChunkMinX++;
		for (int j = currentChunkMinY; j <= currentChunkMaxY; ++j) {
			chunks.push_back(new Chunk(currentChunkMaxX + 1, j));//render a chunk
			chunkGenerator::generateBlock(*chunks[chunkSize]);
			chunkSize++;
		}
		currentChunkMaxX++;
		isChange = true;
	}

	else if (myCamera->Position.z + startPosX < (currentChunkMinX + 2) * Chunk::width) {
		for (int i = 0; i < chunkSize; ++i) {
			if (chunks[i]->x == currentChunkMaxX) {
				chunks[i]->isLoad = false;
			}
		}
		currentChunkMaxX--;
		for (int j = currentChunkMinY; j <= currentChunkMaxY; ++j) {
			chunks.push_back(new Chunk(currentChunkMinX - 1, j));//render a chunk
			chunkGenerator::generateBlock(*chunks[chunkSize]);
			chunkSize++;
		}
		currentChunkMinX--;
		isChange = true;
	}

	/*
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
		isChange = true;
	}

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
		isChange = true;
	}
	*/
	if (isChange) {
		std::vector<Chunk*> chunks1;
		for (int i = 0; i < chunkSize; ++i) {
			if (chunks[i]->isLoad != false) {//原chunk保留
				chunks1.push_back(chunks[i]);
			}
			else {//原chunk不保留，删
				delete chunks[i];
			}
		}
		chunks = chunks1;
		chunkSize = chunks1.size();
	}
}

void Map::setBlock(int worldPos[], Block::blockType type)
{
	int x = 0; //block在chunk中的坐标
	int y = 0;
	assert(worldPos[0] <= (currentChunkMaxX + 1) * Chunk::width);
	assert(worldPos[0] >= currentChunkMinX * Chunk::width);
	assert(worldPos[1] <= (currentChunkMaxY + 1) * Chunk::width);
	assert(worldPos[1] >= currentChunkMinY * Chunk::width);
	int index = getBlockIndex(worldPos[0], worldPos[1]);//获得该block所在的chunk下标
	assert(index != -1);
	//获得block在chunk中的坐标:
	if (worldPos[0] < 0) {
		x = -chunks[index]->x * Chunk::width + worldPos[0];
	}
	else {
		x = worldPos[0] % Chunk::width;
	}
	if (worldPos[1] < 0) {
		y = -chunks[index]->y * Chunk::width + worldPos[1];
	}
	else {
		y = worldPos[1] % Chunk::width;
	}
	assert(x < Chunk::width&& x >= 0);
	assert(y < Chunk::width&& y >= 0);
	int z = getBlockHeight(worldPos[0], worldPos[1]);//得到最贴近地表的空气块纵坐标
	assert(z != -1);//all Air
	if (type == Block::Air) {//delete block
		chunks[index]->blocks[x][y][z - 1] = type;
		chunks[index]->isRender[x][y][z - 1] = false;//删除对象,设置不可见
		chunks[index]->isRender[x][y][z - 2] = true;//下面的
		chunks[index]->isRender[x][y - 1][z - 1] = getBlockType(x, y - 1, z - 1) == Block::Air ? false : true;//周围的设置可见
		chunks[index]->isRender[x][y + 1][z - 1] = getBlockType(x, y + 1, z - 1) == Block::Air ? false : true;
		chunks[index]->isRender[x - 1][y][z - 1] = getBlockType(x - 1, y, z - 1) == Block::Air ? false : true;
		chunks[index]->isRender[x + 1][y][z - 1] = getBlockType(x + 1, y, z - 1) == Block::Air ? false : true;
	}
	else {//add block
		chunks[index]->blocks[x][y][z] = type;
		//设置可见
		chunks[index]->isRender[x][y][z] = true;
	}
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
	assert(x < Chunk::width&& x >= 0);
	assert(y < Chunk::width&& y >= 0);
	return chunks[index]->blocks[x][y][z];
}
int Map::getBlockHeight(int x, int y)//get the highest height in thr position
{//x,y是block在map中的世界坐标
	bool flag = false;
	for (int i = 0; i < Chunk::height; i++) {
		if (getBlockType(x, y, i) != Block::Air) {
			flag = true;
		}
		if (flag && getBlockType(x, y, i) == Block::Air) {
			return i;
		}
	}
	return -1;//all Air
}
void Map::limitCamera()
{
	int cameraPos[3] = { 0 };
	myCamera->getWorldPos(cameraPos);
	int h = getBlockHeight(cameraPos[0], cameraPos[1]);//最贴近地表的空块
	if (cameraPos[2] <= h + 2) {
		myCamera->Position.y = 2.0f + h;
	}
	if (cameraPos[0] < 0)
		cameraPos[0] = 0;
	else if (cameraPos[0] >= Chunk::width * sqrt(chunkSize))
		cameraPos[0] = (int)(Chunk::width * sqrt(chunkSize) - 1);
	if (cameraPos[1] < 0)
		cameraPos[1] = 0;
	else if (cameraPos[1] >= Chunk::width * sqrt(chunkSize))
		cameraPos[1] = (int)(Chunk::width * sqrt(chunkSize) - 1);
}

const float Map::vertices[] = {
-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // Bottom-left
 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // bottom-right         
 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // bottom-left
-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
// Front face
-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // top-left
-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
// Left face
-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-left
-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
// Right face
 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right         
 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
 0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left     
// Bottom face
-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, // top-left
 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
// Top face
-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right     
 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
-0.5f,  0.5f,  0.5f,  0.0f, 0.0f  // bottom-left        
};

const size_t Map::vsize = sizeof(Map::vertices);

std::vector<Texture> Map::textures;

int Map::loadTextures()
{
	std::vector<std::string> grass
	{
		"blocks/grass_side.png",
		"blocks/grass.png",
		"blocks/grass_side.png",
		"blocks/grass_side.png",
		"blocks/grass_side.png",
		"blocks/grass_side.png"
	};
	Texture myTexGrass(grass);

	std::vector<std::string> water
	{
		"blocks/water.png",
		"blocks/water.png",
		"blocks/water.png",
		"blocks/water.png",
		"blocks/water.png",
		"blocks/water.png"
	};
	Texture myTexWater(water);

	std::vector<std::string> dirt
	{
		"blocks/dirt.png",
		"blocks/dirt.png",
		"blocks/dirt.png",
		"blocks/dirt.png",
		"blocks/dirt.png",
		"blocks/dirt.png"
	};
	Texture myTexDirt(dirt);

	std::vector<std::string> sand
	{
		"blocks/sand.png",
		"blocks/sand.png",
		"blocks/sand.png",
		"blocks/sand.png",
		"blocks/sand.png",
		"blocks/sand.png"
	};
	Texture myTexSand(sand);

	std::vector<std::string> stond
	{
		"blocks/stone.png",
		"blocks/stone.png",
		"blocks/stone.png",
		"blocks/stone.png",
		"blocks/stone.png",
		"blocks/stone.png"
	};
	Texture myTexStond(stond);

	std::vector<std::string> stbrick
	{
		"blocks/stonebrick.png",
		"blocks/stonebrick.png",
		"blocks/stonebrick.png",
		"blocks/stonebrick.png",
		"blocks/stonebrick.png",
		"blocks/stonebrick.png"
	};
	Texture myTexStb(stbrick);

	std::vector<std::string> leaf
	{
		"blocks/leaves_oak.png",
		"blocks/leaves_oak.png",
		"blocks/leaves_oak.png",
		"blocks/leaves_oak.png",
		"blocks/leaves_oak.png",
		"blocks/leaves_oak.png"
	};
	Texture myTexleaf(leaf);

	std::vector<std::string> log
	{
		"blocks/log_oak_top.png",
		"blocks/log_oak_top.png",
		"blocks/log_oak.png",
		"blocks/log_oak.png",
		"blocks/log_oak.png",
		"blocks/log_oak.png"
	};
	Texture myTexlog(log);

	std::vector<std::string> cactus
	{
		"blocks/cactus_top.png",
		"blocks/cactus_top.png",
		"blocks/cactus_side.png",
		"blocks/cactus_side.png",
		"blocks/cactus_side.png",
		"blocks/cactus_side.png"
	};
	Texture myTexcac(cactus);

	std::vector<std::string> cloud
	{
		"blocks/glass_white.png",
		"blocks/glass_white.png",
		"blocks/glass_white.png",
		"blocks/glass_white.png",
		"blocks/glass_white.png",
		"blocks/glass_white.png"
	};
	Texture myTexCloud(cloud);

	Map::textures.push_back(myTexDirt); //0
	Map::textures.push_back(myTexWater); //1
	Map::textures.push_back(myTexDirt); //2
	Map::textures.push_back(myTexStond); //3
	Map::textures.push_back(myTexGrass); //4
	Map::textures.push_back(myTexSand); //5
	Map::textures.push_back(myTexStb); //6
	Map::textures.push_back(myTexleaf); //7
	Map::textures.push_back(myTexlog); //8
	Map::textures.push_back(myTexcac); //9
	Map::textures.push_back(myTexCloud); //10
	return 0;
}