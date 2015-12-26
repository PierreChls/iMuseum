#pragma once

#include "glimac/glm.hpp"
#include <string>
#include "Shader.hpp"
#include <GL/glew.h>
#include "Camera.hpp"

using namespace glm;

class PointLight
{
	private:
		vec3 position;
		vec3 ambient;
		vec3 diffuse;
		vec3 specular;
		float constant;
		float linear;
		float quadratic;

	public:
		PointLight();
		PointLight(	vec3 position,
					vec3 ambient,
					vec3 diffuse,
					vec3 specular,
					float constant,
					float  linear,
					float quadratic);
		~PointLight();

		//getter
		vec3 getPosition() 		const;
		vec3 getAmbient() 		const;
		vec3 getDiffuse() 		const;
		vec3 getSpecular()  	const;
		float getConstant()  	const;
		float getLinear() 		const;
		float getQuadratic() 	const;

		//setter

		void setPosition(		const vec3 new_position)  ;
		void setAmbient(		const vec3 new_ambient)   ;
		void setDiffuse(		const vec3 new_diffuse)   ;
		void setSpecular(		const vec3 new_specular)  ;
		void setConstant(		const float new_constant) ;
		void setLinear(			const float new_linear)   ;
		void setQuadratic(		const float new_quadratic);

		//shader
		void sendToShader( char lightNumber, const Shader shader);

};

class DirLight
{
private:
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

public:
	DirLight();
	DirLight( vec3 direction,
			  vec3 ambient,
			  vec3 diffuse,
			  vec3 specular);
	~DirLight();
	
	//getter
	vec3 getDirection()			const;
	vec3 getAmbient()			const;
	vec3 getDiffuse()			const;
	vec3 getSpecular()			const;

	//setter

	void setDirection( 	const vec3 new_direction);
	void setAmbient (	const vec3 new_ambient);
	void setDiffuse ( 	const vec3 new_diffuse);
	void setSpecular( 	const vec3 new_specular);

	void update(		const vec3 deltaDir);

	//shader
	void sendToShader(char lightNumber, const Shader shader);
};

class SpotLight
{
private:
	vec3 position;
	vec3 direction;
	float cutOff;
	float outerCutOff;

	float constant;
	float linear;
	float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

public:
	SpotLight();
	SpotLight( vec3 position,
			   vec3 direction,
			   float cutOff,
			   float outerCutOff,
			   float constant,
			   float linear,
			   float quadratic,
			   vec3 ambient,
			   vec3 diffuse,
			   vec3 specular);
	~SpotLight();
	
	//getter

	vec3	getPosition()		const;
	vec3	getDirection()		const;
	float	getCutOff()			const;
	float	getOuterCutOff()	const;
	float	getConstant()		const;
	float	getLinear()			const;
	float	getQuadratic()		const;
	vec3	getAmbient()		const;
	vec3	getDiffuse()		const;
	vec3	getSpecular()		const;

	//setter

	void	setPosition(		const	vec3 new_position);
	void	setDirection(		const 	vec3 new_direction);
	void	setCutOff(			const 	float new_cutOff);
	void	setOuterCutOff(		const 	float new_outerCutOff);
	void	setConstant(		const 	float new_constant);
	void	setLinear(			const 	float new_linear);
	void	setQuadratic( 		const 	float new_quadratic);
	void	setAmbient( 		const 	vec3 new_ambient);
	void 	setDiffuse(			const 	vec3 new_diffuse);
	void	setSpecular(		const 	vec3 new_specular);

	void 	update(Camera camera);
	void	sendToShader(char lightNumber, Shader shader);
};	