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
     
    Block::textures.push_back(myTexDirt); //0
    Block::textures.push_back(myTexDirt); //1
    Block::textures.push_back(myTexDirt); //2
    Block::textures.push_back(myTexStond); //3
    Block::textures.push_back(myTexGrass); //4
    Block::textures.push_back(myTexSand); //5
    Block::textures.push_back(myTexStb); //6
    Block::textures.push_back(myTexleaf); //7
    Block::textures.push_back(myTexlog); //8
    Block::textures.push_back(myTexcac); //9
    Block::textures.push_back(myTexCloud); //10
    return 0;
}
