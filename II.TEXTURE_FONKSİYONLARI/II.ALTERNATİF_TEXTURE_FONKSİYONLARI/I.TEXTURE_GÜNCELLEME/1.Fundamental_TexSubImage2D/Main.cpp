#include<iostream>
#include<math.h>

#include"Texture.h"
#include"VBO.h"
#include"EBO.h"
#include"shaderClass.h"

#define SCR_WIDTH  256
#define SCR_HEIGHT  256
#define CHECK_GL_ERROR CatchErrorAndPrint(__FUNCTION__, __FILE__, __LINE__)


void CatchErrorAndPrint(const char* function, const char* file, int line) {
    GLenum error = glGetError();
    while (error != GL_NO_ERROR) {
        const char* errorStr;
        switch (error) {
            case GL_INVALID_ENUM: errorStr = "GL_INVALID_ENUM"; break;
            case GL_INVALID_VALUE: errorStr = "GL_INVALID_VALUE"; break;
            case GL_INVALID_OPERATION: errorStr = "GL_INVALID_OPERATION"; break;
            case GL_OUT_OF_MEMORY: errorStr = "GL_OUT_OF_MEMORY"; break;
            case GL_INVALID_FRAMEBUFFER_OPERATION: errorStr = "GL_INVALID_FRAMEBUFFER_OPERATION"; break;
            default: errorStr = "Unknown Error"; break;
        }
        std::cout << "OpenGL error in function '" << function << "' (" << file << ":" << line << "): " << errorStr << std::endl;
        error = glGetError();
    }
}

// Vertices coordinates
GLfloat vertices[] =
{ //     COORDINATES     /        COLORS      /   TexCoord  //
-0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,        0.0f, 1.0f,   // Sol alt köşe// Lower left corner
-0.5f,  0.5f, 0.0f,     0.0f, 1.0f, 0.0f,        0.0f, 0.0f, // Sol üst köşe // Upper left corner
 0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f,        1.0f, 0.0f,   // Sağ üst köşe// Upper right corner
 0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f,        1.0f, 1.0f // Sağ alt köşe // Lower right corner
/*Tex Coordların konumlanması önemli victorun ki stbye uyarlamak için texkoordlar ters konumlanmış*/
};
/*TEX COORD
0.0f, 1.0f,
0.0f, 0.0f,
1.0f, 0.0f,
1.0f, 1.0f  
*/

// Indices for vertices order
GLuint indices[] =
{
	0, 2, 1, // Upper triangle
	0, 3, 2 // Lower triangle
};


int main()
{
	// Initialize GLFW
    if (!glfwInit()) {
        return -1;
    }

	// Tell GLFW what version of OpenGL we are using 
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	// Tell GLFW we are using the CORE profile

	// Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "beginner_glTexSubImage2D", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Introduce the window into the current context
	glfwMakeContextCurrent(window);
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
	CHECK_GL_ERROR;
	// Generates Shader object using shaders defualt.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");
	CHECK_GL_ERROR;
	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	CHECK_GL_ERROR;

	EBO EBO1(indices, sizeof(indices));
	CHECK_GL_ERROR;

    GLint aPos = glGetAttribLocation(shaderProgram.ID,"aPos");
	CHECK_GL_ERROR;
	VBO1.LinkAttrib(VBO1, aPos, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	CHECK_GL_ERROR;

	GLint aColor = glGetAttribLocation(shaderProgram.ID,"aColor");
	VBO1.LinkAttrib(VBO1, aColor, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	CHECK_GL_ERROR;

    GLint aTex = glGetAttribLocation(shaderProgram.ID,"aTex");
	CHECK_GL_ERROR;
	VBO1.LinkAttrib(VBO1, aTex, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    CHECK_GL_ERROR;

    // Unbind the buffer and shader program after setting up attributes
    VBO1.Unbind();
	EBO1.Unbind();
    CHECK_GL_ERROR;

	/*Texture işlemleri başlıyor !*/
    
	unsigned char update[] = {
		255,0,0,
	};
	unsigned char update2[] = {
		0,255,0,
	};
	unsigned char update3[] = {
		0,0,255,
	};
	unsigned char update4[] = {
		255,0,255,
	};
	Texture pixel_128x128(NULL,2,2,GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	CHECK_GL_ERROR;
	pixel_128x128.texUnit(shaderProgram, "tex0", 0);
	CHECK_GL_ERROR;
	glBindTexture(GL_TEXTURE_2D,pixel_128x128.ID);
	glTexSubImage2D(GL_TEXTURE_2D,0,0,0,1,1,GL_RGB,GL_UNSIGNED_BYTE,update);
	glTexSubImage2D(GL_TEXTURE_2D,0,1,0,1,1,GL_RGB,GL_UNSIGNED_BYTE,update2);
	glTexSubImage2D(GL_TEXTURE_2D,0,0,1,1,1,GL_RGB,GL_UNSIGNED_BYTE,update3);
    glTexSubImage2D(GL_TEXTURE_2D,0,1,1,1,1,GL_RGB,GL_UNSIGNED_BYTE,update4);
    CHECK_GL_ERROR;
	
	
	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
    shaderProgram.Activate();
	glUniform1f(glGetUniformLocation(shaderProgram.ID, "scale"), 0.5f);
	pixel_128x128.Bind();
	VBO1.Bind();
    glBindBuffer(GL_ARRAY_BUFFER, VBO1.ID);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, indices);

	if(glGetError() != GL_NO_ERROR){
		CHECK_GL_ERROR;
		break;
	}
	
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glfwSwapBuffers(window);
    glfwPollEvents();
	}



	// Delete all the objects we've created
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}
