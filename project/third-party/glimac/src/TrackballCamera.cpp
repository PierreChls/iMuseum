#include <glimac/TrackballCamera.hpp>

	/*** METHODS ***/

	TrackballCamera::TrackballCamera(){
		m_fDistance = 5;
		m_fAngleX = 0;
		m_fAngleY = 0;
	}
	TrackballCamera::~TrackballCamera(){}

	void TrackballCamera::moveFront(float delta){
		float distance = getDistance();
		setDistance(distance + delta);
	}
	void TrackballCamera::rotateLeft(float degrees){
		float angleY = getAngleY();
		setAngleY(angleY + degrees);
	}
	void TrackballCamera::rotateUp(float degrees){
		float angleX = getAngleX();
		setAngleX(angleX + degrees);
	}

	/*** SETTER ***/

	void TrackballCamera::setDistance(float distance) {
		m_fDistance = distance;
	}
	void TrackballCamera::setAngleX(float angleX) {
		m_fAngleX += angleX;
	}
	void TrackballCamera::setAngleY(float angleY){
		m_fAngleY += angleY;
	}

	/*** GETTER ***/

	float TrackballCamera::getDistance() const{
		return m_fDistance;
	}
	float TrackballCamera::getAngleX() const{
		return m_fAngleX;
	}
	float TrackballCamera::getAngleY() const{
		return m_fAngleY;
	}
	glm::mat4 TrackballCamera::getViewMatrix() const{
		 glm::mat4 VM;
		 glm::mat4 Translation = glm::translate( glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -1*getDistance()));
		 glm::mat4 RotationX   = glm::rotate   ( glm::mat4(1.0f), glm::radians(getAngleX()), glm::vec3(1,0,0));
		 glm::mat4 RotationY   = glm::rotate   ( glm::mat4(1.0f), glm::radians(getAngleY()), glm::vec3(0,1,0));


		 VM =  Translation * RotationX * RotationY;
		 return VM;



	}
