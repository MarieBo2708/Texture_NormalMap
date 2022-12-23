// Local includes
#include "Material.h"
#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"
#include "SceneLoader.h"
// GLM includes
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

// OPENGL includes
#include <GL/glew.h>
#include <GL/glut.h>
#include <vector>
#include <string>

Material::~Material() {
	if (m_program != 0) {
		glDeleteProgram(m_program);
	}
}


void Material::init() {
	// TODO : Change shader by your
	m_program = load_shaders("shaders/unlit/vertex.glsl", "shaders/unlit/fragment.glsl");
	check();
	// TODO : set initial parameters
	m_color = {1.0, 1.0, 1.0, 1.0};
	diffuse_texture = loadTexture2DFromFilePath("data/jean.png");
	normal_texture = loadTexture2DFromFilePath("data/n2.ppm");
	lightPosition = {4., 4., 4.};
	viewPosition = {4., 4., 4.};
}

void Material::clear() {
	glDeleteTextures(1, &diffuse_texture);
	glDeleteTextures(1, &normal_texture);

}

void Material::bind() {
	check();
	glUseProgram(m_program);
	internalBind();
}

void Material::internalBind() {
	// bind parameters
	GLint color = getUniform("color");
	glUniform4fv(color, 1, glm::value_ptr(m_color));

	if (diffuse_texture != -1) {
		glActiveTexture(GL_TEXTURE0+0);
		glUniform1i(getUniform("colorTexture"),0);
		glBindTexture(GL_TEXTURE_2D, diffuse_texture);
		
		
	}
	if (normal_texture != -1){
		glActiveTexture(GL_TEXTURE0+1);
		glUniform1i(getUniform("normalTexture"), 1);
		glBindTexture(GL_TEXTURE_2D, normal_texture);
		
		
	}
	GLint l_p = getUniform("light_position");
	glUniform3fv(l_p, 1.f, glm::value_ptr(lightPosition));

	GLint v_p = getUniform("view_position");
	glUniform3fv(v_p, 1.f, glm::value_ptr(viewPosition));

	// TODO : Add your custom parameters here
}

void Material::setMatrices(glm::mat4& projectionMatrix, glm::mat4& viewMatrix, glm::mat4& modelMatrix)
{
	check();
	glUniformMatrix4fv(getUniform("projection"), 1, false, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(getUniform("view"), 1, false, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(getUniform("model"), 1, false, glm::value_ptr(modelMatrix));

}

GLint Material::getAttribute(const std::string& in_attributeName) {
	check();
	return glGetAttribLocation(m_program, in_attributeName.c_str());
}

GLint Material::getUniform(const std::string& in_uniformName) {
	check();
	return glGetUniformLocation(m_program, in_uniformName.c_str());
}
