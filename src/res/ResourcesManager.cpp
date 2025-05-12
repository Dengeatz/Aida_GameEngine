#include "ResourcesManager.h"
#include "../Render/ShaderProgram.h"
#include <sstream>
#include <fstream>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

ResourcesManager::ResourcesManager(const std::string& path) 
{
	std::size_t found = path.find_last_of("/\\");
	m_path = path.substr(0, found);
}

std::string ResourcesManager::GetFileString(const std::string& relativeFilePath) const {
    std::string shaderCode;

    std::ifstream shaderFile;

    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        shaderFile.open(m_path + "/" + relativeFilePath.c_str());
        std::stringstream shaderStream;
        shaderStream << shaderFile.rdbuf();
        shaderFile.close();
        shaderCode = shaderStream.str();
        return shaderCode;
    }
    catch (std::ifstream::failure& e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
}

std::shared_ptr<Render::ShaderProgram> ResourcesManager::LoadShaders(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath) 
{
    std::string vertexString = GetFileString(vertexPath);
    std::string fragmentString = GetFileString(fragmentPath);

    std::shared_ptr<Render::ShaderProgram>& newShader = m_shaders.emplace(shaderName, std::make_shared<Render::ShaderProgram>(vertexString, fragmentString)).first->second;
    if (!newShader->IsCompiled())
    {
        std::cerr << "ERROR::SHADER NOT COMPILED";
        system("pause");
    }
    return newShader;
}

std::shared_ptr<Render::ShaderProgram> ResourcesManager::GetShaderProgram(const std::string& shaderName) 
{
    ShaderProgramMap::const_iterator it = m_shaders.find(shaderName);
    if (it != m_shaders.end())
    {
        return it->second;
    }
    std::cerr << "ERROR::SHADER NOT FOUND! \n" << shaderName << std::endl;
    system("pause");
}

std::shared_ptr<Render::Texture2D> ResourcesManager::LoadTexture(const std::string& textureName, const std::string& texturePath)
{
    int channel = 0;
    int width = 0;
    int height = 0;

    stbi_set_flip_vertically_on_load(true);
    unsigned char* pixels = stbi_load(std::string(m_path + "/" + texturePath).c_str(), &width, &height, &channel, 0);

    if (!pixels) {
        std::cerr << "ERROR::TEXTURE NOT FOUND!";
        system("pause");
    }

    std::shared_ptr<Render::Texture2D> texture = m_textures.emplace(textureName, std::make_shared<Render::Texture2D>(width, height, pixels, channel, gl::GL_NEAREST, gl::GL_CLAMP_TO_EDGE)).first->second;
    return texture;
    stbi_image_free(pixels);
}

std::shared_ptr<Render::Texture2D> ResourcesManager::GetTexture(const std::string& textureName) 
{
    TexturesMap::const_iterator it = m_textures.find(textureName);
    if (it != m_textures.end())
    {
        return it->second;
    }
    std::cerr << "ERROR::SHADER NOT FOUND! \n" << textureName << std::endl;
    system("pause");
}