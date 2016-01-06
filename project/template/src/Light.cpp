#include "Light.hpp"

Light::Light(){}
Light::~Light(){}
void Light::sendToShader(char lightNumber, const Shader shader){
	std::cout << "TEST A" << std::endl;
}
string Light::getShader() const{}
void Light::update(Camera camera){}

/***** POINT LIGHT *****/

PointLight::PointLight(){}
PointLight::PointLight(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic, string shader_name):
	position(position),
	ambient(ambient),
	specular(specular),
	constant(constant),
	linear(linear),
	quadratic(quadratic),
	shader_name(shader_name)
	{}
PointLight::~PointLight(){}
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
string  PointLight::getShader()				const{
	return shader_name;
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
    			temp = "pointLights[" + std::to_string(lightNumber) + "].linear";
				temp2 = temp.c_str();				
	glUniform1f(glGetUniformLocation(shader.Program, temp2),		getLinear() 	);
    //quadratic			
    			temp = "pointLights[" + std::to_string(lightNumber) + "].quadratic";
				temp2 = temp.c_str();
    glUniform1f(glGetUniformLocation(shader.Program, temp2),		getQuadratic()	);  
}

/***** DIRECTION LIGHT *****/

DirLight::DirLight(){}

DirLight::DirLight(glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, string shader_name):
						direction(direction),
						ambient(ambient),
						diffuse(diffuse),
						specular(specular),
						shader_name(shader_name)
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
string  DirLight::getShader()		const{
	return shader_name;
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

void DirLight::update(const glm::vec3 deltaDir){
	direction += deltaDir;
}

/***** SPOTLIGHT *****/

SpotLight::SpotLight(){}
SpotLight::SpotLight(glm::vec3 position, vec3 direction, float cutOff, float outerCutOff, float constant, float linear, float quadratic, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, string shader_name):
	position(position),
	direction(direction),
	cutOff(cutOff),
	outerCutOff(outerCutOff),
	constant(constant),
	linear(linear),
	quadratic(quadratic),
	ambient(ambient),
	diffuse(diffuse),
	specular(specular),
	shader_name(shader_name)
	{}

SpotLight::~SpotLight(){}

//getter
vec3 SpotLight::getPosition()		const{
	return position;
}
vec3 SpotLight::getDirection()		const{
	return direction;
}
float SpotLight::getCutOff()		const{
	return cutOff;
}
float SpotLight::getOuterCutOff()	const{
	return outerCutOff;
}
float SpotLight::getConstant()		const{
	return constant;
}
float SpotLight::getLinear()		const{
	return linear;
}
float SpotLight::getQuadratic()		const{
	return quadratic;
}
vec3 SpotLight::getAmbient()		const{
	return ambient;
}
vec3 SpotLight::getDiffuse()		const{
	return diffuse;
}
vec3 SpotLight::getSpecular()		const{
	return specular;
}
string  SpotLight::getShader()		const{
	return shader_name;
}

//setter

void SpotLight::setPosition(		const glm::vec3 new_position){
	position = new_position;
}
void SpotLight::setDirection(		const glm::vec3 new_direction){
	direction = new_direction;
}
void SpotLight::setCutOff(			const float 	new_cutOff){
	cutOff = new_cutOff;
}
void SpotLight::setOuterCutOff(		const float		new_outerCutOff){
	outerCutOff = new_outerCutOff;
}
void SpotLight::setConstant(		const float		new_constant){
	constant = new_constant;
}
void SpotLight::setLinear(			const float		new_linear){
	linear = new_linear;
}
void SpotLight::setQuadratic(		const float 	new_quadratic){
	quadratic = new_quadratic;
}
void SpotLight::setAmbient(			const glm::vec3	new_ambient){
	ambient = new_ambient;
}
void SpotLight::setDiffuse(			const glm::vec3 new_diffuse){
	diffuse = new_diffuse;
}
void SpotLight::setSpecular(		const glm::vec3 new_specular){
	specular = new_specular;
}

//if flashlight
void SpotLight::update(Camera camera){
	position = camera.getPosition();
	direction = camera.getDirection();
}


void SpotLight::sendToShader( char lightNumber, const Shader shader){

	//Trick to convert char to GLchar

	//position
	std::string temp = "spotLights[" + std::to_string(lightNumber) + "].position";
	const char* temp2 = temp.c_str();
	glUniform3f(glGetUniformLocation(shader.Program, temp2), 		getPosition().x, 	getPosition().y, 	getPosition().z);

	//direction			
				temp = "spotLights[" + std::to_string(lightNumber) + "].direction";
				temp2 = temp.c_str();			
    glUniform3f(glGetUniformLocation(shader.Program, temp2), 		getDirection().x, 	getDirection().y, 	getDirection().z);

    //cutOff			
    			temp = "spotLights[" + std::to_string(lightNumber) + "].cutOff";
				temp2 = temp.c_str();
    glUniform1f(glGetUniformLocation(shader.Program, temp2), 		getCutOff()	);

    //outerCutOff			
    			temp = "spotLights[" + std::to_string(lightNumber) + "].outerCutOff";
				temp2 = temp.c_str();
    glUniform1f(glGetUniformLocation(shader.Program, temp2), 		getOuterCutOff()	);

    //constant			
    			temp = "spotLights[" + std::to_string(lightNumber) + "].constant";
				temp2 = temp.c_str();
    glUniform1f(glGetUniformLocation(shader.Program, temp2), 		getConstant()	);

    //linear
    			temp = "spotLights[" + std::to_string(lightNumber) + "].linear";
				temp2 = temp.c_str();				
	glUniform1f(glGetUniformLocation(shader.Program, temp2),		getLinear() 	);

    //quadratic			
    			temp = "spotLights[" + std::to_string(lightNumber) + "].quadratic";
				temp2 = temp.c_str();
    glUniform1f(glGetUniformLocation(shader.Program, temp2),		getQuadratic()	);  

    //diffuse			
    			temp = "spotLights[" + std::to_string(lightNumber) + "].diffuse";
				temp2 = temp.c_str();       
    glUniform3f(glGetUniformLocation(shader.Program, temp2), 		getDiffuse().x,		getDiffuse().y,		getDiffuse().z); 

	//ambient			
				temp = "spotLights[" + std::to_string(lightNumber) + "].ambient";
				temp2 = temp.c_str();
	glUniform3f(glGetUniformLocation(shader.Program, temp2), 		getAmbient().x, 	getAmbient().y, 	getAmbient().z);
    
    //specular			
    			temp = "spotLights[" + std::to_string(lightNumber) + "].specular";
				temp2 = temp.c_str();
    glUniform3f(glGetUniformLocation(shader.Program, temp2), 		getSpecular().x,	getSpecular().y,	getSpecular().z);

}