#pragma once

#include "glimac/glm.hpp"
#include "Camera.hpp"

using namespace std;
using namespace glm;

class ModelPicker
{
private:
	vec2 screenDim;
	vec3 mousePos;
	vec3 currentRay;

	mat4 projectionMatrix;
	mat4 viewMatrix;
	Camera camera;

	vec3 calculateMouseRay();
	vec3 getNormalizedDeviceCoords(const float posX, const float posY, const float posZ);
	vec4 toEyeCoords(vec4 clipCoords);
	vec3 toWorldCoords(vec4 eyeCoords);
	float getMouseX() const;
	float getMouseY() const;
	float getMouseZ() const;
	float getScreenWidth() const;
	float getScreenHeight() const;

public:

	ModelPicker(vec2 screen, Camera cam, mat4 projection);
	~ModelPicker();
	
	void update(vec3 mouse);
	vec3 getCurrentRay() const ;
};