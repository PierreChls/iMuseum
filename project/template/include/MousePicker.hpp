#pragma once

#include "glimac/glm.hpp"
#include "Camera.hpp"

using namespace std;
using namespace glm;

class MousePicker
{
private:
	vec2 screenDim;
	vec2 mousePos;
	vec3 currentRay;

	mat4 projectionMatrix;
	mat4 viewMatrix;
	Camera camera;

	vec3 calculateMouseRay();
	vec2 getNormalizedDeviceCoords(const float mouseX, const float mouseY);
	vec4 toEyeCoords(vec4 clipCoords);
	vec3 toWorldCoords(vec4 eyeCoords);
	float getMouseX() const;
	float getMouseY() const;
	float getScreenWidth() const;
	float getScreenHeight() const;

public:

	MousePicker(vec2 screen, Camera cam, mat4 projection);
	~MousePicker();
	
	void update(vec2 mouse);
	vec3 getCurrentRay() const ;
};