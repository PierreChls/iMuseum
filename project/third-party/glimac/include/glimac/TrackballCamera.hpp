#pragma once

#include "glm.hpp"


class TrackballCamera
{
private:

	float m_fDistance; // distance par rapport au centre de la scène
	float m_fAngleX;   // angle effectué par la caméra autour de l'axe X (rotation haut bas)
	float m_fAngleY;   // angle effectué par la caméra autour de l'axe Y (rotation gauche droite)


public:

	/*** METHODS ***/

	TrackballCamera();  // constructor
	~TrackballCamera(); // destructor
	void moveFront(float delta);
	void rotateLeft(float degrees);
	void rotateUp(float degrees);
	
	/*** SETTER ***/

	void setDistance(float distance);
	void setAngleX(float angleX);
	void setAngleY(float angleY);

	/*** GETTER ***/

	float getDistance() const;
	float getAngleX() const;
	float getAngleY() const;
	glm::mat4 getViewMatrix() const;
	
};