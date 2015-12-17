#pragma once

#include "glimac/glm.hpp"
#include <string>
#include "Shader.hpp"
#include <GL/glew.h>

using namespace glm;


class Light
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
		Light();
		Light(	vec3 position,
				vec3 ambient,
				vec3 diffuse,
				vec3 specular,
				float constant,
				float  linear,
				float quadratic);
		~Light();

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
		void setConstant(		const float new_constant)  ;
		void setLinear(			const float new_linear) 	  ;
		void setQuadratic(		const float new_quadratic) ;

		void sendToShader( char lightNumber, const Shader shader);

};