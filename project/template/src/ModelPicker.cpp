#include "ModelPicker.hpp"

using namespace std;
using namespace glm;

ModelPicker::ModelPicker(vec2 screen, Camera cam, mat4 projection):
			screenDim(screen),
			mousePos(vec3(0,0,0)),
			camera(cam),
			projectionMatrix(projection),
			viewMatrix(cam.getViewMatrix())
			{}

ModelPicker::~ModelPicker(){}

vec3 ModelPicker::getCurrentRay() const{
	return currentRay;
}

vec3 ModelPicker::calculateMouseRay(){
	float mouseX = getMouseX();
	float mouseY = getMouseY(); 
	float mouseZ = getMouseZ(); 

	//vec3 normalizedCoords = getNormalizedDeviceCoords(mouseX, mouseY, mouseZ);
	vec4 clipCoords = vec4(mouseX, mouseY, mouseZ, 1.f);
	vec4 eyeCoords = toEyeCoords(clipCoords);
	vec3 worldRay = toWorldCoords(eyeCoords);
	return worldRay;
}

vec4 ModelPicker::toEyeCoords(vec4 clipCoords){
	mat4 invertedProjection = inverse(projectionMatrix);  // inverser matrice
	vec4 eyeCoords =  invertedProjection * clipCoords;
	return vec4(eyeCoords.x, eyeCoords.y, -1.f, 0.f);
}

vec3 ModelPicker::toWorldCoords(vec4 eyeCoords){
	mat4 invertedView = inverse(viewMatrix);
	vec4 rayWorld = invertedView * eyeCoords;
	vec3 mouseRay = vec3(rayWorld.x, rayWorld.y, rayWorld.z);
	mouseRay = normalize(mouseRay); // verifier si ça marche
	return mouseRay;
}

float ModelPicker::getMouseX() const{
	return (float)mousePos.x;
}

float ModelPicker::getMouseY() const{
	return (float)mousePos.y;
}

float ModelPicker::getMouseZ() const{
	return (float)mousePos.z;
}

float ModelPicker::getScreenWidth() const{
	return (float)screenDim.x;
}

float ModelPicker::getScreenHeight() const{
	return (float)screenDim.y;
}

vec3 ModelPicker::getNormalizedDeviceCoords(const float posX, const float posY, const float posZ){
	float x = (2.f * posX) / getScreenWidth()  -1.f;
	float y = (2.f * posY) / getScreenHeight() -1.f;
	float z = (2.f * posY) / getScreenHeight() -1.f;

	return vec3(x, y, z); // verifier si les coordonnées commencent en haut a gauche ou en bas a gauche si bas gauche   prend min y
}	

void ModelPicker::update(vec3 mouse){
	mousePos = mouse;
	viewMatrix = camera.getViewMatrix();
	currentRay = calculateMouseRay();
}