#include "MousePicker.hpp"

using namespace std;
using namespace glm;

MousePicker::MousePicker(vec2 screen, Camera cam, mat4 projection):
			screenDim(screen),
			mousePos(vec2(0,0)),
			camera(cam),
			projectionMatrix(projection),
			viewMatrix(cam.getViewMatrix())
			{}

MousePicker::~MousePicker(){}

vec3 MousePicker::getCurrentRay() const{
	return currentRay;
}

vec3 MousePicker::calculateMouseRay(){
	float mouseX = getMouseX();
	float mouseY = getMouseY(); 

	vec2 normalizedCoords = getNormalizedDeviceCoords(mouseX, mouseY);
	vec4 clipCoords = vec4(normalizedCoords.x, normalizedCoords.y, -1.f, 1.f);
	vec4 eyeCoords = toEyeCoords(clipCoords);
	vec3 worldRay = toWorldCoords(eyeCoords);
	return worldRay;
}

vec4 MousePicker::toEyeCoords(vec4 clipCoords){
	mat4 invertedProjection = inverse(projectionMatrix);  // inverser matrice
	vec4 eyeCoords =  invertedProjection * clipCoords;
	return vec4(eyeCoords.x, eyeCoords.y, -1.f, 0.f);
}

vec3 MousePicker::toWorldCoords(vec4 eyeCoords){
	mat4 invertedView = inverse(viewMatrix);
	vec4 rayWorld = invertedView * eyeCoords;
	vec3 mouseRay = vec3(rayWorld.x, rayWorld.y, rayWorld.z);
	mouseRay = normalize(mouseRay); // verifier si ça marche
	return mouseRay;
}

float MousePicker::getMouseX() const{
	return (float)mousePos.x;
}

float MousePicker::getMouseY() const{
	return (float)mousePos.y;
}

float MousePicker::getScreenWidth() const{
	return (float)screenDim.x;
}

float MousePicker::getScreenHeight() const{
	return (float)screenDim.y;
}

vec2 MousePicker::getNormalizedDeviceCoords(const float mouseX, const float mouseY){
	float x = (2.f * mouseX) / getScreenWidth()  -1.f;
	float y = (2.f * mouseY) / getScreenHeight() -1.f;

	return vec2(x, y); // verifier si les coordonnées commencent en haut a gauche ou en bas a gauche si bas gauche   prend min y
}	

void MousePicker::update(vec2 mouse){
	mousePos = mouse;
	viewMatrix = camera.getViewMatrix();
	currentRay = calculateMouseRay();
}