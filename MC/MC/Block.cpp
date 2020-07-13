#include "Block.h"

const float Block::vertices[] = {
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

const size_t Block::vsize = sizeof(Block::vertices);

std::vector<Texture> Block::textures;

int Block::loadTextures()
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
     
    Block::textures.push_back(myTexDirt); //0
    Block::textures.push_back(myTexDirt); //1
    Block::textures.push_back(myTexDirt); //2
    Block::textures.push_back(myTexStond); //3
    Block::textures.push_back(myTexGrass); //4
    Block::textures.push_back(myTexSand); //5
    Block::textures.push_back(myTexStb); //6
    return 0;
}
