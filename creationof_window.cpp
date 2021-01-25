#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
using namespace std;
const char* vertex_shader =
"#version 430 core\n"
"layout(location = 0) in vec3 position;\n" //locaion 0 is where
//positions are
"layout(location = 1) in vec3 colors;\n"
"out vec3 color_fragment;\n" //out putting color fragment
"void main()\n"
"{\n"
"   gl_Position = vec4(position, 1.0);\n"
"color_fragment = colors;\n" //setting color fragment
   //= to colors
	"}\n";
const char* fragment_shader =
"#version 430 core\n"
"out vec4 fragcolors;\n"
"in vec3 color_fragment;\n"//input our color_fragment
"void main()\n"
"{\n"
"fragcolors = vec4(color_fragment, 1.0f);\n"
"}\n";
int main() {
	glfwInit();
	GLFWwindow* window = glfwCreateWindow(800, 600, "Spencer's triangle", NULL, NULL);
	if (window == NULL)
	{
		cout << "error";
	}
	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glViewport(0, 0, 800, 600);

	int vertex = glCreateShader(GL_VERTEX_SHADER);
	int fragment = glCreateShader(GL_FRAGMENT_SHADER);
	const char* pointer_to_shaders[1];
	pointer_to_shaders[0] = vertex_shader;
	glShaderSource(vertex, 1, pointer_to_shaders, 0);
	pointer_to_shaders[0] = fragment_shader;
	glShaderSource(fragment, 1, pointer_to_shaders, 0);
	glCompileShader(vertex);
	glCompileShader(fragment);
	int program = glCreateProgram();
	glAttachShader(program, vertex);
	glAttachShader(program, fragment);

	glLinkProgram(program);
	//glUseProgram(program);

	float points[]{
	0.5f, -0.5f, 0.0f,         1.0f, 0.0f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,        5.0f, 1.0f, 0.0f,  // bottom left
     0.0f,  0.5f, 0.0f,        1.0f, 0.0f, 1.0f   // top 

		 //third row of numbers are colors
	};

	unsigned int space;

	glGenVertexArrays(1, &space); //change color of each
	//verts
	glGenBuffers(1, &space);
	glBindVertexArray(space); //bind color


	glBindBuffer(GL_ARRAY_BUFFER, space);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);



	//6 times the size of float, how much separated they are
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
	glEnableVertexAttribArray(0);



	//location of where color buffer is

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	//A void* does not mean anything. It is a pointer, but the type that it points to is not known.
	//the reason it is 3 * the size of float because
	//at the end of the first color row, you have to go 3 more floats(position 2nd row),
	//until you get to the second color row


	glUseProgram(program);

	while (!glfwWindowShouldClose(window))
	{





		glBindVertexArray(space);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();



		//	glfwSwapInterval(20);

	}
	glfwTerminate();
	return 0;
}