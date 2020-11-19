#include "ResourceManager.h"
#include "../Renderer/ShaderProgram.h"

#include <sstream>
#include <fstream>
#include <iostream>

ResourceManager::ResourceManager(const string& executablePath) {

	size_t found = executablePath.find_last_of("/\\");
	m_path = executablePath.substr(0, found);
}

string ResourceManager::getFileString(const string& relativeFilePath) const {

	ifstream f;
	f.open(m_path + "/" + relativeFilePath.c_str(), ios::in | ios::binary);
	if (!f.is_open()) {
		cerr << "Faild to open file: "<< relativeFilePath << endl;
		return string{};
	}

	stringstream buffer;
	buffer << f.rdbuf();
	return buffer.str();
}

shared_ptr<Renderer::ShaderProgram> ResourceManager::loadShaders(const string& shaderName, const string& vertexPath, const string& fragmentPath) {

	string vertexString = getFileString(vertexPath);
	if (vertexString.empty()) {
		cerr << "No vertex shader!" << endl;
		return nullptr;
	}

	string fragmentString = getFileString(fragmentPath);
	if (fragmentString.empty()) {
		cerr << "No fragment shader!" << endl;
		return nullptr;
	}

	shared_ptr<Renderer::ShaderProgram>& newShader = m_shaderProgram.emplace(shaderName, std::make_shared<Renderer::ShaderProgram>(vertexString, fragmentString)).first->second;
	if (newShader->isComplited()) {
		return newShader;
	}

	cerr << "Can`t load shader program" << endl
		<< "Vertex:" << vertexPath << endl
		<< "Fragment:" << fragmentPath << endl;

	return nullptr;
}

shared_ptr<Renderer::ShaderProgram> ResourceManager::getShaderProgram(const string& shaderName) {

	ShaderProgramsMap::const_iterator it = m_shaderProgram.find(shaderName);
	if (it != m_shaderProgram.end()) {

		return it->second;
	}

	cerr << "Can`t find the shader program: " << shaderName << endl;
	return nullptr;
}