#pragma once
#include <string>
#include <memory>
#include "../Render/ShaderProgram.h" 
#include "../Render/Texture2D.h"
#include <map>


class ResourcesManager {
public:
	static ResourcesManager& Instance(const std::string& path = "")
	{
		static ResourcesManager res(path);
		return res;
	}
	std::shared_ptr<Render::ShaderProgram> LoadShaders(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath);
	std::shared_ptr<Render::ShaderProgram> GetShaderProgram(const std::string& shaderName);
	std::shared_ptr<Render::Texture2D> LoadTexture(const std::string& textureName, const std::string& texturePath);
	std::shared_ptr<Render::Texture2D> GetTexture(const std::string& textureName);
private:
	ResourcesManager(const std::string& path);
	~ResourcesManager() = default;
	ResourcesManager(const ResourcesManager&) = delete;
	ResourcesManager& operator=(const ResourcesManager&) = delete;
	ResourcesManager& operator=(ResourcesManager&&) = delete;
	ResourcesManager(ResourcesManager&&) = delete;
	std::string m_path;
	std::string GetFileString(const std::string& relativeFilePath) const;
	typedef std::map<const std::string, std::shared_ptr<Render::ShaderProgram>> ShaderProgramMap;
	typedef std::map<const std::string, std::shared_ptr<Render::Texture2D>> TexturesMap;
	TexturesMap m_textures;
	ShaderProgramMap m_shaders;
};