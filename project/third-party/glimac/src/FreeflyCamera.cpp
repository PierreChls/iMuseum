#include <glimac/FreeflyCamera.hpp>

/*********************** CONSTRUCTOR / DESTRUCTOR ***********************/
	FreeflyCamera::FreeflyCamera(){
		m_Position = glm::vec3(0,0,0);
		m_fPhi	   = M_PI;
		m_fTheta   = 0;

		computeDirectionVectors();
	}

	FreeflyCamera::~FreeflyCamera(){}

/*********************** METHODS ***********************/

void FreeflyCamera::computeDirectionVectors(){
	m_FrontVector =glm::vec3( cos(glm::radians(m_fTheta))*sin(glm::radians(m_fPhi)),
					 sin(glm::radians(m_fTheta)),
					 cos(glm::radians(m_fTheta))*cos(glm::radians(m_fPhi)));


	m_LeftVector  =glm::vec3( sin(glm::radians(m_fPhi)+ M_PI/2.0),
					 0,
					 cos(glm::radians(m_fPhi)+ M_PI/2.0));

	m_UpVector    =  glm::cross(m_FrontVector, m_LeftVector);

}

void FreeflyCamera::moveLeft(float t){
	//P += t*V
}

void FreeflyCamera::moveFront(float t){
	//P += t*V
}