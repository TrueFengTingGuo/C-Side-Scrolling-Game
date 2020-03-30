// Source code of vertex shader for particle system
#version 130

// Vertex buffer
in vec2 vertex;
in vec2 dir;
in float t; //phase
in vec2 uv;

// Uniform (global) buffer
uniform mat4 transformationMatrix;
uniform mat4 viewMatrix;
uniform float time;
uniform vec4 ps_color;

// Attributes forwarded to the fragment shader
out vec4 color_interp;
out vec2 uv_interp;

//global variable

float distance2( in vec2 a, in vec2 b ) { return dot(a-b,a-b); }


vec4 drawParticle(float local_firework_time, vec2 startPos, float timeLength, float rocketSpeed, float rocketTravelTime,out vec4 temp_ps_color){
	vec4 tempBuff = vec4(0.0);	
	float gravity = 0.25;
	float explodingspeed = 20.0;
	vec2 explotionStart = vec2(0.0 ,  rocketSpeed *rocketTravelTime);
	vec2 explotionEnd = vec2(vertex.x+dir.x*(local_firework_time-rocketTravelTime)*explodingspeed ,vertex.y + dir.y*(local_firework_time-rocketTravelTime)*explodingspeed  + rocketSpeed *rocketTravelTime );

	//shrink by distance traveled
	float particle_distance = distance2(explotionStart, explotionEnd);
	vec2 tempvertex = vertex;
	if(particle_distance < timeLength *explodingspeed){
		
		tempvertex*= ((timeLength *explodingspeed) - distance2(explotionStart, explotionEnd))/(timeLength *explodingspeed);
		
	}
	else{
		tempvertex*= 0;
	}

	//change transparancy  depends on distance	
	temp_ps_color.a = - ((0.3*timeLength *explodingspeed) -distance2(explotionStart, explotionEnd))/(0.3*timeLength *explodingspeed);
	
	//calculate the gravity
	float  gravity_Impact = -0.5 *gravity *(local_firework_time-rocketTravelTime);

	//construct the final vertex
	tempBuff = vec4(tempvertex.x+dir.x*(local_firework_time-rocketTravelTime)*explodingspeed , tempvertex.y + (dir.y +  gravity_Impact)*(local_firework_time-rocketTravelTime)*explodingspeed  + rocketSpeed *rocketTravelTime, 0.0, 1.0);
	return tempBuff;
}

vec4 draw_firework(float local_firework_time, vec2 rocketStartLoactaion,float rocketSpeed, out vec4 temp_ps_color){

	float exlodingTime = 0;
	float exlodingEnd = 2;
	vec4 tempBuff;

	//draw different effect depends  on the time
	if(local_firework_time <= 0.0){
		return tempBuff;
	}

	//draw  particle based  on time
	if(local_firework_time < exlodingEnd){
		tempBuff = drawParticle(local_firework_time,rocketStartLoactaion,25.0,rocketSpeed,exlodingTime,temp_ps_color);
	}
	else{
		tempBuff = vec4(0.0); // nothing to do
	}

	return tempBuff;

}


void main()
{
	vec4 temp_ps_color = ps_color;
	//my implementation
    gl_Position = viewMatrix*transformationMatrix *draw_firework( time ,vec2(0.0), 10.0, temp_ps_color);
	
 
    color_interp = temp_ps_color;
	uv_interp = uv;
}
