#include "Light.hpp"

using namespace std;

Light::Light(){}
Light::Light(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic, string shader_name):
	position(position),
	ambient(ambient),
	specular(specular),
	constant(constant),
	linear(linear),
	quadratic(quadratic),
	shader_name(shader_name)
	{}

//getter

glm::vec3 Light::getPosition() 	const{
	return position;
}
glm::vec3 Light::getAmbient() 	const{
	return ambient;
}
glm::vec3 Light::getDiffuse() 	const{
	return diffuse;
}
glm::vec3 Light::getSpecular()  const{
	return specular;
}
float Light::getConstant()  const{
	return constant;
}
float Light::getLinear() 	const{
	return linear;
}
float Light::getQuadratic() const{
	return quadratic;
}

//setter

void Light::setPosition(const glm::vec3 new_position)	 {
	position = new_position;
}
void Light::setAmbient(const glm::vec3 new_ambient) 	 {
	ambient = new_ambient;
}
void Light::setDiffuse(const glm::vec3 new_diffuse) 	 {
	diffuse = new_diffuse;
}
void Light::setSpecular(const glm::vec3 new_specular) 	 {
	specular = new_specular;
}
void Light::setConstant(const float new_constant)  	 {
	constant = new_constant;
}
void Light::setLinear(const float new_linear) 	     {
	linear = new_linear;
}
void Light::setQuadratic(const float new_quadratic)  {
	quadratic = new_quadratic;
}
void Light::sendToShader( char lightNumber, const Shader shader){

	std::string temp = "pointLights[" + std::to_string(lightNumber) + "].position";
	const char* temp2 = temp.c_str();

	//std::cout << temp2 << std::endl;
	glUniform3f(glGetUniformLocation(shader.Program, temp2), 		getPosition().x, 	getPosition().y, 	getPosition().z);
				temp = "pointLights[" + std::to_string(lightNumber) + "].ambient";
				temp2 = temp.c_str();
					//std::cout << temp2 << std::endl;
    glUniform3f(glGetUniformLocation(shader.Program, temp2), 		getAmbient().x, 	getAmbient().y, 	getAmbient().z);
    			temp = "pointLights[" + std::to_string(lightNumber) + "].diffuse";
				temp2 = temp.c_str();       
    glUniform3f(glGetUniformLocation(shader.Program, temp2), 		getDiffuse().x,	getDiffuse().y,		getDiffuse().z); 
    			temp = "pointLights[" + std::to_string(lightNumber) + "].specular";
				temp2 = temp.c_str();
    glUniform3f(glGetUniformLocation(shader.Program, temp2), 		getSpecular().x,	getSpecular().y,	getSpecular().z);
    			temp = "pointLights[" + std::to_string(lightNumber) + "].constant";
				temp2 = temp.c_str();
    glUniform1f(glGetUniformLocation(shader.Program, temp2), 		getConstant());
    			temp = "pointLights[" + std::to_string(lightNumber) + "].constant";
				temp2 = temp.c_str();
    glUniform1f(glGetUniformLocation(shader.Program, temp2),		getLinear() 	);
    			temp = "pointLights[" + std::to_string(lightNumber) + "].quadratic";
				temp2 = temp.c_str();
    glUniform1f(glGetUniformLocation(shader.Program, temp2),		getQuadratic());  
}