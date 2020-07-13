#include "Map.h"

extern const unsigned int SCR_WIDTH;
extern const unsigned int SCR_HEIGHT;

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

	chunkSize = 6;
	chunks.push_back(new Chunk(0, 0));
	chunks.push_back(new Chunk(0, 1));
	chunks.push_back(new Chunk(1, 0));
	chunks.push_back(new Chunk(1, 1));
	chunks.push_back(new Chunk(2, 0));
	chunks.push_back(new Chunk(2, 1));

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
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//background
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//�任��
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
		if (i < chunkSize - 1) {
			int dx = chunks[i + 1]->x - chunks[i]->x;
			int dy = chunks[i + 1]->y - chunks[i]->y;
			model = glm::translate(model, glm::vec3(0.0f, Chunk::width * dy * 1.0f, Chunk::width * dx * 1.0f));
		}
	}
}
