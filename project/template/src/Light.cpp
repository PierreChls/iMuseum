#include "Light.hpp"

/***** POINT LIGHT *****/

PointLight::PointLight(){}
PointLight::PointLight(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic):
	position(position),
	ambient(ambient),
	specular(specular),
	constant(constant),
	linear(linear),
	quadratic(quadratic)
	{}

//getter

glm::vec3 PointLight::getPosition() 		const{
	return position;
}
glm::vec3 PointLight::getAmbient() 			const{
	return ambient;
}
glm::vec3 PointLight::getDiffuse() 			const{
	return diffuse;
}
glm::vec3 PointLight::getSpecular()  		const{
	return specular;
}
float PointLight::getConstant()  			const{
	return constant;
}
float PointLight::getLinear() 				const{
	return linear;
}
float PointLight::getQuadratic() 			const{
	return quadratic;
}

//setter

void PointLight::setPosition(const glm::vec3 new_position)	 {
	position = new_position;
}
void PointLight::setAmbient(const glm::vec3 new_ambient) 	 {
	ambient = new_ambient;
}
void PointLight::setDiffuse(const glm::vec3 new_diffuse) 	 {
	diffuse = new_diffuse;
}
void PointLight::setSpecular(const glm::vec3 new_specular) 	 {
	specular = new_specular;
}
void PointLight::setConstant(const float new_constant)  	 {
	constant = new_constant;
}
void PointLight::setLinear(const float new_linear) 	     {
	linear = new_linear;
}
void PointLight::setQuadratic(const float new_quadratic)  {
	quadratic = new_quadratic;
}
void PointLight::sendToShader( char lightNumber, const Shader shader){

	//Trick to convert char to GLchar

	//position
	std::string temp = "pointLights[" + std::to_string(lightNumber) + "].position";
	const char* temp2 = temp.c_str();
	glUniform3f(glGetUniformLocation(shader.Program, temp2), 		getPosition().x, 	getPosition().y, 	getPosition().z);
	//ambient			
				temp = "pointLights[" + std::to_string(lightNumber) + "].ambient";
				temp2 = temp.c_str();
    glUniform3f(glGetUniformLocation(shader.Program, temp2), 		getAmbient().x, 	getAmbient().y, 	getAmbient().z);
    //diffuse			
    			temp = "pointLights[" + std::to_string(lightNumber) + "].diffuse";
				temp2 = temp.c_str();       
    glUniform3f(glGetUniformLocation(shader.Program, temp2), 		getDiffuse().x,		getDiffuse().y,		getDiffuse().z); 
    //specular			
    			temp = "pointLights[" + std::to_string(lightNumber) + "].specular";
				temp2 = temp.c_str();
    glUniform3f(glGetUniformLocation(shader.Program, temp2), 		getSpecular().x,	getSpecular().y,	getSpecular().z);
    //constant			
    			temp = "pointLights[" + std::to_string(lightNumber) + "].constant";
				temp2 = temp.c_str();
    glUniform1f(glGetUniformLocation(shader.Program, temp2), 		getConstant()	);
    //linear
    			temp = "pointLights[" + std::to_string(lightNumber) + "].linear"; // <<< ICI
				temp2 = temp.c_str();
	///ICI quand on change le .constant en .linear rendu NOIR
				
	glUniform1f(glGetUniformLocation(shader.Program, temp2),		getLinear() 	);
    //quadratic			
    			temp = "pointLights[" + std::to_string(lightNumber) + "].quadratic";
				temp2 = temp.c_str();
    glUniform1f(glGetUniformLocation(shader.Program, temp2),		getQuadratic()	);  
}

/***** DIRECTION LIGHT *****/

DirLight::DirLight(){}

DirLight::DirLight(glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular):
						direction(direction),
						ambient(ambient),
						diffuse(diffuse),
						specular(specular)
						{}

DirLight::~DirLight(){}

//getter
glm::vec3 DirLight::getDirection()	const{
	return direction;
}

glm::vec3 DirLight::getAmbient()	const{
	return ambient;
}

glm::vec3 DirLight::getDiffuse()	const{
	return diffuse;
}
glm::vec3 DirLight::getSpecular()	const{
	return specular;
}

//setter
void DirLight::setDirection(glm::vec3 new_direction){
	direction = new_direction;
}

void DirLight::setAmbient(glm::vec3 new_ambient){
	ambient = new_ambient;
}

void DirLight::setDiffuse(glm::vec3 new_diffuse){
	diffuse = new_diffuse;
}

void DirLight::setSpecular(glm::vec3 new_specular){
	specular = new_specular;
}

//shader

void DirLight::sendToShader(char lightNumber, const Shader shader){

	//Trick to convert char to GLchar

	//direction
	std::string temp = "dirLights[" + std::to_string(lightNumber) + "].direction";
	const char* temp2 = temp.c_str();
	glUniform3f(glGetUniformLocation(shader.Program, temp2), 		getDirection().x, 	getDirection().y, 	getDirection().z);
	//ambient			
				temp = "dirLights[" + std::to_string(lightNumber) + "].ambient";
				temp2 = temp.c_str();
    glUniform3f(glGetUniformLocation(shader.Program, temp2), 		getAmbient().x, 	getAmbient().y, 	getAmbient().z);
    //diffuse			
    			temp = "dirLights[" + std::to_string(lightNumber) + "].diffuse";
				temp2 = temp.c_str();       
    glUniform3f(glGetUniformLocation(shader.Program, temp2), 		getDiffuse().x,	getDiffuse().y,		getDiffuse().z); 
    //specular			
    			temp = "dirLights[" + std::to_string(lightNumber) + "].specular";
				temp2 = temp.c_str();
    glUniform3f(glGetUniformLocation(shader.Program, temp2), 		getSpecular().x,	getSpecular().y,	getSpecular().z);

}