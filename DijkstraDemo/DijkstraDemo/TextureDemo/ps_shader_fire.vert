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


float distance( in vec2 a, in vec2 b ) { return dot(a-b,a-b); }

void main()
{
	vec4 ppos;
	float acttime;
	float speed = 4.0;
	float gravity = 2.8;
	vec4 changedColor = ps_color; //store temp color 
	acttime = mod(time + t*2.0, 2.0);

	//drag the sprite make it more like fire
	vec2 changedVertex = vertex; 
	changedVertex.x *= 0.3;
	changedVertex.y *= 2.0;
	
    ppos = vec4(changedVertex.x+dir.x*acttime*speed- dir.x* 0.5*gravity*acttime*acttime , changedVertex.y+dir.y*acttime*speed + 0.5*gravity*acttime*acttime, 0.0, 1.0);
    gl_Position = viewMatrix*transformationMatrix*ppos;
	
	float y_distanceBetween = distance(vertex.y ,changedVertex.y+dir.y*acttime*speed + 0.5*gravity*acttime*acttime);
	float x_distanceBetween = distance(vertex.x ,changedVertex.x+dir.x*acttime*speed- dir.x* 0.5*gravity*acttime*acttime);

	//change color///////
	//set green, blue and transparency to 0
	changedColor.g = -1.0;
	changedColor.b = -1.0;
	changedColor.a = -1.0;

	if(0 < x_distanceBetween && x_distanceBetween <0.5 && y_distanceBetween < 4){
		changedColor.r += (1 - acttime /3.0) + 0.2; //add bright flame in  the middle
		changedColor.g += (1 - acttime /3.0) + 0.2;
		changedColor.b += (1 - acttime /3.0) + 0.2;
	}

	if(0 < x_distanceBetween && x_distanceBetween <1.0){
		changedColor.g += (1 - acttime /3.0) + 0.2; //add yellow flame
	}
	if(0.0 < x_distanceBetween && x_distanceBetween < 2.0){
		changedColor.a += 1- (x_distanceBetween /3.0) ;	//add transparency flame

	}
	else{
		changedColor.a = -1;
	}

    color_interp = changedColor;
	uv_interp = uv;
}
