#pragma once

#include "glm.hpp"

class FreeflyCamera
{
private:
	glm::vec3 m_Position;	//Position de la caméra
	float m_fPhi;			//Coordonnées sphériques
	float m_fTheta;			//Coordonnées sphériques

	glm::vec3 m_FrontVector; //Front vector F
	glm::vec3 m_LeftVector;  //Left  vector L
	glm::vec3 m_UpVector;	//Up    vector U

	void computeDirectionVectors();

public:
	FreeflyCamera();		//Constructor
	~FreeflyCamera();		//Destructor
	void moveLeft(float t);  // move to left
	void moveFront(float t);
};