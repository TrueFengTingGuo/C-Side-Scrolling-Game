#include "Shader.h"

bool Shader::setupSprite = false;
GLuint Shader::vbo_sprite;
GLuint Shader::ebo_sprite;
GLuint Shader::vbo_particle;
GLuint Shader::ebo_particle;

Shader::Shader(const char* vertPath, const char* fragPath, bool isSprite) {
	if (!setupSprite)
	{
		makeSprite();
		makeParticles();
	}

	createProgram(vertPath, fragPath);
	if (isSprite)
	{
		SetAttributes_sprite();
	}
	else
	{

		SetAttributes_particle();
	}
}

void Shader::createProgram(const char* vertPath, const char* fragPath)
{

	// Load vertex program source code
	std::string vp = FileUtils::LoadTextFile(vertPath);
	const char* source_vp = vp.c_str();
	std::string fp = FileUtils::LoadTextFile(fragPath);
	const char* source_fp = fp.c_str();

	// Create a shader from vertex program source code
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &source_vp, NULL);
	glCompileShader(vs);

	// Check if shader compiled successfully
	GLint status;
	glGetShaderiv(vs, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE) {
		char buffer[512];
		glGetShaderInfoLog(vs, 512, NULL, buffer);
		throw(std::ios_base::failure(std::string("Error compiling vertex shader: ") + std::string(buffer)));
	}

	// Create a shader from the fragment program source code
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &source_fp, NULL);
	glCompileShader(fs);

	// Check if shader compiled successfully
	glGetShaderiv(fs, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE) {
		char buffer[512];
		glGetShaderInfoLog(fs, 512, NULL, buffer);
		throw(std::ios_base::failure(std::string("Error compiling fragment shader: ") + std::string(buffer)));
	}

	// Create a shader program linking both vertex and fragment shaders
	// together
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vs);
	glAttachShader(shaderProgram, fs);
	glLinkProgram(shaderProgram);

	// Check if shaders were linked successfully
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
	if (status != GL_TRUE) {
		char buffer[512];
		glGetShaderInfoLog(shaderProgram, 512, NULL, buffer);
		throw(std::ios_base::failure(std::string("Error linking shaders: ") + std::string(buffer)));
	}

	// Delete memory used by shaders, since they were already compiled
	// and linked
	glDeleteShader(vs);
	glDeleteShader(fs);



}


void Shader::SetAttributes_particle()
{

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask(GL_FALSE); // draw particles without writing to depth buffer

	glBindBuffer(GL_ARRAY_BUFFER, vbo_particle);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_particle);
	// Set attributes for shaders
	// Should be consistent with how we created the buffers for the particle elements
	GLint vertex_att = glGetAttribLocation(shaderProgram, "vertex");
	glVertexAttribPointer(vertex_att, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(vertex_att);

	GLint dir_att = glGetAttribLocation(shaderProgram, "dir");
	glVertexAttribPointer(dir_att, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));
	glEnableVertexAttribArray(dir_att);

	GLint time_att = glGetAttribLocation(shaderProgram, "t");
	glVertexAttribPointer(time_att, 1, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)(4 * sizeof(GLfloat)));
	glEnableVertexAttribArray(time_att);

	GLint tex_att = glGetAttribLocation(shaderProgram, "uv");
	glVertexAttribPointer(tex_att, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(tex_att);


}

void Shader::SetAttributes_sprite()
{
	glBlendFunc(GL_ONE, GL_ONE);

	glBindBuffer(GL_ARRAY_BUFFER, vbo_sprite);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_sprite);
	// Set attributes for shaders
	// Should be consistent with how we created the buffers for the square
	GLint vertex_att = glGetAttribLocation(shaderProgram, "vertex");
	glVertexAttribPointer(vertex_att, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(vertex_att);

	GLint color_att = glGetAttribLocation(shaderProgram, "color");
	glVertexAttribPointer(color_att, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));
	glEnableVertexAttribArray(color_att);

	GLint tex_att = glGetAttribLocation(shaderProgram, "uv");
	glVertexAttribPointer(tex_att, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(tex_att);
}

void Shader::makeSprite()
{
	// The face of the square is defined by four vertices and two triangles

	// Number of attributes for vertices and faces
	//	const int vertex_att = 7;  // 7 attributes per vertex: 2D (or 3D) position (2), RGB color (3), 2D texture coordinates (2)
	//	const int face_att = 3; // Vertex indices (3)

	GLfloat vertex[] = {
		//  square (two triangles)
		//  Position      Color             Texcoords

		-0.5f, 0.5f,	 1.0f, 0.0f, 0.0f,		0.0f, 0.0f, // Top-left
		0.5f, 0.5f,		 0.0f, 1.0f, 0.0f,		1.0f, 0.0f, // Top-right
		0.5f, -0.5f,	 0.0f, 0.0f, 1.0f,		1.0f, 1.0f, // Bottom-right
		-0.5f, -0.5f,	 1.0f, 1.0f, 1.0f,		0.0f, 1.0f  // Bottom-left
		/*
		-0.0f, 1.0f,	 1.0f, 0.0f, 0.0f,		0.0f, 0.0f, // Top-left
		1.0f, 1.0f,		 0.0f, 1.0f, 0.0f,		1.0f, 0.0f, // Top-right
		1.0f, -0.0f,	 0.0f, 0.0f, 1.0f,		1.0f, 1.0f, // Bottom-right
		-0.0f, 0.0f,	 1.0f, 1.0f, 1.0f,		0.0f, 1.0f  // Bottom-left
		*/
	};


	GLuint face[] = {
		0, 1, 2, // t1
		2, 3, 0  //t2
	};

	// Create buffer for vertices
	glGenBuffers(1, &vbo_sprite);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_sprite);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);

	// Create buffer for faces (index buffer)
	glGenBuffers(1, &ebo_sprite);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_sprite);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(face), face, GL_STATIC_DRAW);

	// Return number of elements in array buffer (6 in this case)
//	return sizeof(face) / sizeof(GLuint);

	setupSprite = true; // finished creating sprite 
}

void Shader::makeParticles()
{

	// Each particle is a square with four vertices and two triangles

	// Number of attributes for vertices and faces
	const int vertex_attr = 7;  // 7 attributes per vertex: 2D (or 3D) position (2), direction (2), 2D texture coordinates (2), time (1)
								//	const int face_att = 3; // Vertex indices (3)

	GLfloat vertex[] = {
		//  square (two triangles)
		//  Position      Color             Texcoords
		-0.5f, 0.5f,	 1.0f, 0.0f, 0.0f,		0.0f, 0.0f, // Top-left
		0.5f, 0.5f,		 0.0f, 1.0f, 0.0f,		1.0f, 0.0f, // Top-right
		0.5f, -0.5f,	 0.0f, 0.0f, 1.0f,		1.0f, 1.0f, // Bottom-right
		-0.5f, -0.5f,	 1.0f, 1.0f, 1.0f,		0.0f, 1.0f  // Bottom-left
	};

	GLfloat particleatt[2000 * vertex_attr];
	float theta, r, tmod;

	for (int i = 0; i < 100; i++)
	{
		if (i % 4 == 0)
		{
			theta = (6.28 * (rand() % 1000) / 1000.0f);//(2*(rand() % 10000) / 10000.0f -1.0f)*0.13f;
			r = 0.0f + 0.8 * (rand() % 10000) / 10000.0f;
			tmod = (rand() % 10000) / 10000.0f;
		}
		// position	
		particleatt[i * vertex_attr + 0] = vertex[(i % 4) * 7 + 0];
		particleatt[i * vertex_attr + 1] = vertex[(i % 4) * 7 + 1];

		// velocity
		particleatt[i * vertex_attr + 2] = sin(theta) * r;
		particleatt[i * vertex_attr + 3] = cos(theta) * r;

		// phase
		particleatt[i * vertex_attr + 4] = tmod;

		// texture coordinate
		particleatt[i * vertex_attr + 5] = vertex[(i % 4) * 7 + 5];
		particleatt[i * vertex_attr + 6] = vertex[(i % 4) * 7 + 6];


	}


	GLuint face[] = {
		0, 1, 2, // t1
		2, 3, 0  //t2
	};

	GLuint manyface[2000 * 6];

	for (int i = 0; i < 2000; i++)
	{
		for (int j = 0; j < 6; j++)
			manyface[i * 6 + j] = face[j] + i * 4;
	}

	// Create buffer for vertices
	glGenBuffers(1, &vbo_particle);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_particle);
	glBufferData(GL_ARRAY_BUFFER, sizeof(particleatt), particleatt, GL_STATIC_DRAW);

	// Create buffer for faces (index buffer)
	glGenBuffers(1, &ebo_particle);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_particle);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(manyface), manyface, GL_STATIC_DRAW);

	// Return number of elements in array buffer
//	return sizeof(manyface);

}


// Sets a uniform integer variable in your shader program to a value
void Shader::setUniform1i(const GLchar* name, int value) {
	glUniform1i(glGetUniformLocation(shaderProgram, name), value);
}

// Sets a uniform float variable in your shader program to a value
void Shader::setUniform1f(const GLchar* name, float value) {
	glUniform1f(glGetUniformLocation(shaderProgram, name), value);
}

// Sets a uniform vector2 variable in your shader program to a vector
void Shader::setUniform2f(const GLchar* name, const glm::vec2& vector) {
	glUniform2f(glGetUniformLocation(shaderProgram, name), vector.x, vector.y);
}

// Sets a uniform vector3 variable in your shader program to a vector
void Shader::setUniform3f(const GLchar* name, const glm::vec3& vector) {
	glUniform3f(glGetUniformLocation(shaderProgram, name), vector.x, vector.y, vector.z);
}

// Sets a uniform vector4 variable in your shader program to a vector
void Shader::setUniform4f(const GLchar* name, const glm::vec4& vector) {
	glUniform4f(glGetUniformLocation(shaderProgram, name), vector.x, vector.y, vector.z, vector.w);
}

// Sets a uniform matrix4x4 variable in your shader program to a matrix4x4
void Shader::setUniformMat4(const GLchar* name, const glm::mat4& matrix) {
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, name), 1, GL_FALSE, glm::value_ptr(matrix));
}

Shader::~Shader() {
	glDeleteProgram(shaderProgram);
}

void Shader::enable() {
	glUseProgram(shaderProgram);
}

void Shader::disable() {
	glUseProgram(0); // nonsense, do not call this function
}