#include "ResourcesManager.h"
#include "../Render/ShaderProgram.h"

#include <sstream>
#include <fstream>
#include <iostream>

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