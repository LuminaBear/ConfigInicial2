// Martinez Perez Isaac Tadeo

// 320281589

// Gpo1



#include <iostream>

#include <cmath>

#include <fstream> // Librería para leer/escribir archivos



// GLEW

#include <GL/glew.h>



// GLFW

#include <GLFW/glfw3.h>



// Other Libs

#include "stb_image.h"



// GLM Mathematics

#include <glm/glm.hpp>

#include <glm/gtc/matrix_transform.hpp>

#include <glm/gtc/type_ptr.hpp>



//Load Models

#include "SOIL2/SOIL2.h"



// Other includes

#include "Shader.h"

#include "Camera.h"

#include "Model.h"

#include "Texture.h"





// Function prototypes

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);

void MouseCallback(GLFWwindow* window, double xPos, double yPos);

void DoMovement();

void Animation();



// Window dimensions

const GLuint WIDTH = 800, HEIGHT = 600;

int SCREEN_WIDTH, SCREEN_HEIGHT;



// Camera

Camera  camera(glm::vec3(0.0f, 0.0f, 3.0f));

GLfloat lastX = WIDTH / 2.0;

GLfloat lastY = HEIGHT / 2.0;

bool keys[1024];

bool firstMouse = true;

// Light attributes

glm::vec3 lightPos(0.0f, 0.0f, 0.0f);

bool active;



// Positions of the point lights

glm::vec3 pointLightPositions[] = {

glm::vec3(0.0f, 2.0f, 0.0f),

glm::vec3(0.0f, 0.0f, 0.0f),

glm::vec3(0.0f, 0.0f, 0.0f),

glm::vec3(0.0f, 0.0f, 0.0f)

};



float vertices[] = {

-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

   -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

   -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,



   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

   -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,



   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

   -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,

   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,

   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,

   -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,



0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,

0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,

0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,

0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,



   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,

0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,

   -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,

   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,



   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,

0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,

0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,

0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,

   -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,

   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f

};



glm::vec3 Light1 = glm::vec3(0);



//Anim

float rotBall = 0.0f;

float rotDog = 0.0f;

float rotDogZ = 0.0f;

int dogAnim = 0;



// Patas

float rotFLeft = 0.0f;

float rotFRight = 0.0f;

float rotBLeft = 0.0f;

float rotBRight = 0.0f;

float head = 0.0f;

float tail = 0.0f;



//KeyFrames

float dogPosX = 0.0f, dogPosY = 0.0f, dogPosZ = 0.0f;



#define MAX_FRAMES 9

int i_max_steps = 190;

int i_curr_steps = 0;



typedef struct _frame {

	float rotDog, rotDogInc;

	float rotDogZ, rotDogZInc;

	float dogPosX, incX;

	float dogPosY, incY;

	float dogPosZ, incZ;

	float head, headInc;

	float tail, tailInc;

	float rotFLeft, rotFLeftInc;

	float rotFRight, rotFRightInc;

	float rotBLeft, rotBLeftInc;

	float rotBRight, rotBRightInc;

} FRAME;



FRAME KeyFrame[MAX_FRAMES];

int FrameIndex = 0;

bool play = false;

int playIndex = 0;



void saveFrame(void)

{

	printf("frameindex %d\n", FrameIndex);



	KeyFrame[FrameIndex].dogPosX = dogPosX;

	KeyFrame[FrameIndex].dogPosY = dogPosY;

	KeyFrame[FrameIndex].dogPosZ = dogPosZ;



	KeyFrame[FrameIndex].rotDog = rotDog;

	KeyFrame[FrameIndex].rotDogZ = rotDogZ;

	KeyFrame[FrameIndex].head = head;

	KeyFrame[FrameIndex].tail = tail;



	KeyFrame[FrameIndex].rotFLeft = rotFLeft;

	KeyFrame[FrameIndex].rotFRight = rotFRight;

	KeyFrame[FrameIndex].rotBLeft = rotBLeft;

	KeyFrame[FrameIndex].rotBRight = rotBRight;



	FrameIndex++;

}



void resetElements(void)

{

	dogPosX = KeyFrame[0].dogPosX;

	dogPosY = KeyFrame[0].dogPosY;

	dogPosZ = KeyFrame[0].dogPosZ;



	rotDog = KeyFrame[0].rotDog;

	rotDogZ = KeyFrame[0].rotDogZ;

	head = KeyFrame[0].head;

	tail = KeyFrame[0].tail;



	rotFLeft = KeyFrame[0].rotFLeft;

	rotFRight = KeyFrame[0].rotFRight;

	rotBLeft = KeyFrame[0].rotBLeft;

	rotBRight = KeyFrame[0].rotBRight;

}



void interpolation(void)

{

	KeyFrame[playIndex].incX = (KeyFrame[playIndex + 1].dogPosX - KeyFrame[playIndex].dogPosX) / i_max_steps;

	KeyFrame[playIndex].incY = (KeyFrame[playIndex + 1].dogPosY - KeyFrame[playIndex].dogPosY) / i_max_steps;

	KeyFrame[playIndex].incZ = (KeyFrame[playIndex + 1].dogPosZ - KeyFrame[playIndex].dogPosZ) / i_max_steps;



	KeyFrame[playIndex].rotDogInc = (KeyFrame[playIndex + 1].rotDog - KeyFrame[playIndex].rotDog) / i_max_steps;

	KeyFrame[playIndex].rotDogZInc = (KeyFrame[playIndex + 1].rotDogZ - KeyFrame[playIndex].rotDogZ) / i_max_steps;

	KeyFrame[playIndex].headInc = (KeyFrame[playIndex + 1].head - KeyFrame[playIndex].head) / i_max_steps;

	KeyFrame[playIndex].tailInc = (KeyFrame[playIndex + 1].tail - KeyFrame[playIndex].tail) / i_max_steps;



	KeyFrame[playIndex].rotFLeftInc = (KeyFrame[playIndex + 1].rotFLeft - KeyFrame[playIndex].rotFLeft) / i_max_steps;

	KeyFrame[playIndex].rotFRightInc = (KeyFrame[playIndex + 1].rotFRight - KeyFrame[playIndex].rotFRight) / i_max_steps;

	KeyFrame[playIndex].rotBLeftInc = (KeyFrame[playIndex + 1].rotBLeft - KeyFrame[playIndex].rotBLeft) / i_max_steps;

	KeyFrame[playIndex].rotBRightInc = (KeyFrame[playIndex + 1].rotBRight - KeyFrame[playIndex].rotBRight) / i_max_steps;

}



// --- FUNCIONES PARA ARCHIVOS ---

void saveAnimationToFile() {

	std::ofstream file("animacion_perro.txt");

	if (!file.is_open()) {

		std::cout << "Error al crear el archivo de guardado." << std::endl;

		return;

	}



	file << FrameIndex << "\n";



	for (int i = 0; i < FrameIndex; i++) {

		file << KeyFrame[i].dogPosX << " " << KeyFrame[i].dogPosY << " " << KeyFrame[i].dogPosZ << " "

			<< KeyFrame[i].rotDog << " " << KeyFrame[i].rotDogZ << " " << KeyFrame[i].head << " "

			<< KeyFrame[i].tail << " " << KeyFrame[i].rotFLeft << " " << KeyFrame[i].rotFRight << " "

			<< KeyFrame[i].rotBLeft << " " << KeyFrame[i].rotBRight << "\n";

	}



	file.close();

	std::cout << "Animacion exportada a animacion_perro.txt (" << FrameIndex << " frames)" << std::endl;

}



void loadAnimationFromFile() {

	std::ifstream file("animacion_perro.txt");

	if (!file.is_open()) {

		std::cout << "No se encontro ningun archivo de animacion previo." << std::endl;

		return;

	}



	file >> FrameIndex;

	if (FrameIndex > MAX_FRAMES) FrameIndex = MAX_FRAMES;



	for (int i = 0; i < FrameIndex; i++) {

		file >> KeyFrame[i].dogPosX >> KeyFrame[i].dogPosY >> KeyFrame[i].dogPosZ

			>> KeyFrame[i].rotDog >> KeyFrame[i].rotDogZ >> KeyFrame[i].head

			>> KeyFrame[i].tail >> KeyFrame[i].rotFLeft >> KeyFrame[i].rotFRight

			>> KeyFrame[i].rotBLeft >> KeyFrame[i].rotBRight;

	}



	file.close();

	std::cout << "Animacion importada exitosamente! (" << FrameIndex << " frames)" << std::endl;



	if (FrameIndex > 0) resetElements();

}

// --------------------------------------



// Deltatime

GLfloat deltaTime = 0.0f; // Time between current frame and last frame

GLfloat lastFrame = 0.0f;  // Time of last frame



int main()

{

	// Init GLFW

	glfwInit();



	// Create a GLFWwindow object that we can use for GLFW's functions

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Animacion maquina de estados - Martinez Perez Isaac Tadeo", nullptr, nullptr);



	if (nullptr == window)

	{

		std::cout << "Failed to create GLFW window" << std::endl;

		glfwTerminate();

		return EXIT_FAILURE;

	}



	glfwMakeContextCurrent(window);

	glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);



	// Set the required callback functions

	glfwSetKeyCallback(window, KeyCallback);

	glfwSetCursorPosCallback(window, MouseCallback);



	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions

	glewExperimental = GL_TRUE;

	// Initialize GLEW to setup the OpenGL Function pointers

	if (GLEW_OK != glewInit())

	{

		std::cout << "Failed to initialize GLEW" << std::endl;

		return EXIT_FAILURE;

	}



	// Define the viewport dimensions

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);



	Shader lightingShader("Shader/lighting.vs", "Shader/lighting.frag");

	Shader lampShader("Shader/lamp.vs", "Shader/lamp.frag");

	Shader skyboxShader("Shader/skybox.vs", "Shader/skybox.frag");



	//models

	Model DogBody((char*)"Models/DogBody.obj");

	Model HeadDog((char*)"Models/HeadDog.obj");

	Model DogTail((char*)"Models/TailDog.obj");

	Model F_RightLeg((char*)"Models/F_RightLegDog.obj");

	Model F_LeftLeg((char*)"Models/F_LeftLegDog.obj");

	Model B_RightLeg((char*)"Models/B_RightLegDog.obj");

	Model B_LeftLeg((char*)"Models/B_LeftLegDog.obj");

	Model Piso((char*)"Models/piso.obj");

	Model Ball((char*)"Models/ball.obj");



	//KeyFrames Init

	for (int i = 0; i < MAX_FRAMES; i++)

	{

		KeyFrame[i].dogPosX = 0;

		KeyFrame[i].dogPosY = 0;

		KeyFrame[i].dogPosZ = 0;

		KeyFrame[i].incX = 0;

		KeyFrame[i].incY = 0;

		KeyFrame[i].incZ = 0;

		KeyFrame[i].rotDog = 0;

		KeyFrame[i].rotDogInc = 0;

		KeyFrame[i].rotDogZ = 0;

		KeyFrame[i].rotDogZInc = 0;

		KeyFrame[i].head = 0;

		KeyFrame[i].headInc = 0;

		KeyFrame[i].tail = 0;

		KeyFrame[i].tailInc = 0;

		KeyFrame[i].rotFLeft = 0;

		KeyFrame[i].rotFLeftInc = 0;

		KeyFrame[i].rotFRight = 0;

		KeyFrame[i].rotFRightInc = 0;

		KeyFrame[i].rotBLeft = 0;

		KeyFrame[i].rotBLeftInc = 0;

		KeyFrame[i].rotBRight = 0;

		KeyFrame[i].rotBRightInc = 0;

	}



	GLfloat skyboxVertices[] = {

		// Positions

		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,

		1.0f, -1.0f, -1.0f,

		1.0f, -1.0f, -1.0f,

		1.0f,  1.0f, -1.0f,

		-1.0f,  1.0f, -1.0f,



		-1.0f, -1.0f,  1.0f,

		-1.0f, -1.0f, -1.0f,

		-1.0f,  1.0f, -1.0f,

		-1.0f,  1.0f, -1.0f,

		-1.0f,  1.0f,  1.0f,

		-1.0f, -1.0f,  1.0f,



		1.0f, -1.0f, -1.0f,

		1.0f, -1.0f,  1.0f,

		1.0f,  1.0f,  1.0f,

		1.0f,  1.0f,  1.0f,

		1.0f,  1.0f, -1.0f,

		1.0f, -1.0f, -1.0f,



		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f,  1.0f,

		1.0f,  1.0f,  1.0f,

		1.0f,  1.0f,  1.0f,

		1.0f, -1.0f,  1.0f,

		-1.0f, -1.0f,  1.0f,



		-1.0f,  1.0f, -1.0f,

		1.0f,  1.0f, -1.0f,

		1.0f,  1.0f,  1.0f,

		1.0f,  1.0f,  1.0f,

		-1.0f,  1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,



		-1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,

		1.0f, -1.0f, -1.0f,

		1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,

		1.0f, -1.0f,  1.0f

	};





	GLuint indices[] =

	{  // Note that we start from 0!

	0,1,2,3,

	4,5,6,7,

	8,9,10,11,

	12,13,14,15,

	16,17,18,19,

	20,21,22,23,

	24,25,26,27,

	28,29,30,31,

	32,33,34,35

	};



	// First, set the container's VAO (and VBO)

	GLuint VBO, VAO, EBO;

	glGenVertexArrays(1, &VAO);

	glGenBuffers(1, &VBO);

	glGenBuffers(1, &EBO);





	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);



	// Position attribute

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);

	glEnableVertexAttribArray(0);

	// normal attribute

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	glEnableVertexAttribArray(1);



	// Set texture units

	lightingShader.Use();

	glUniform1i(glGetUniformLocation(lightingShader.Program, "Material.difuse"), 0);

	glUniform1i(glGetUniformLocation(lightingShader.Program, "Material.specular"), 1);



	//skybox

	GLuint skyboxVAO, skyboxVBO;

	glGenVertexArrays(1, &skyboxVAO);

	glGenBuffers(1, &skyboxVBO);

	glBindVertexArray(skyboxVAO);

	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);


	//Load textures

	vector <const GLchar*> faces;

	faces.push_back("Skybox/right.jpg");

	faces.push_back("Skybox/left.jpg");

	faces.push_back("Skybox/top.jpg");

	faces.push_back("Skybox/bottom.jpg");

	faces.push_back("Skybox/back.jpg");

	faces.push_back("Skybox/front.jpg");

	GLuint cubemapTexture = TextureLoading::LoadCubemap(faces);





	glm::mat4 projection = glm::perspective(camera.GetZoom(), (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, 0.1f, 100.0f);



	// Game loop

	while (!glfwWindowShouldClose(window))

	{

		// Calculate deltatime of current frame

		GLfloat currentFrame = glfwGetTime();

		deltaTime = currentFrame - lastFrame;

		lastFrame = currentFrame;



		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions

		glfwPollEvents();

		DoMovement();

		Animation();



		// Clear the colorbuffer

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



		// OpenGL options

		glEnable(GL_DEPTH_TEST);



		glm::mat4 modelTemp = glm::mat4(1.0f); //Temp



		// Use cooresponding shader when setting uniforms/drawing objects

		lightingShader.Use();

		glUniform1i(glGetUniformLocation(lightingShader.Program, "diffuse"), 0);



		GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");

		glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);



		// Directional light

		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.direction"), -0.2f, -1.0f, -0.3f);

		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.ambient"), 0.6f, 0.6f, 0.6f);

		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.diffuse"), 0.6f, 0.6f, 0.6f);

		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.specular"), 0.3f, 0.3f, 0.3f);



		// Point light 1

		glm::vec3 lightColor;

		lightColor.x = abs(sin(glfwGetTime() * Light1.x));

		lightColor.y = abs(sin(glfwGetTime() * Light1.y));

		lightColor.z = sin(glfwGetTime() * Light1.z);



		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);

		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].ambient"), lightColor.x, lightColor.y, lightColor.z);

		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].diffuse"), lightColor.x, lightColor.y, lightColor.z);

		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].specular"), 1.0f, 0.2f, 0.2f);

		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].constant"), 1.0f);

		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].linear"), 0.045f);

		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].quadratic"), 0.075f);



		// SpotLight

		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.position"), camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);

		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.direction"), camera.GetFront().x, camera.GetFront().y, camera.GetFront().z);

		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.ambient"), 0.2f, 0.2f, 0.8f);

		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.diffuse"), 0.2f, 0.2f, 0.8f);

		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.specular"), 0.0f, 0.0f, 0.0f);

		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.constant"), 1.0f);

		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.linear"), 0.3f);

		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.quadratic"), 0.7f);

		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.cutOff"), glm::cos(glm::radians(12.0f)));

		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.outerCutOff"), glm::cos(glm::radians(18.0f)));



		// Set material properties

		glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 5.0f);



		// Create camera transformations

		glm::mat4 view = camera.GetViewMatrix();



		// Get the uniform locations

		GLint modelLoc = glGetUniformLocation(lightingShader.Program, "model");

		GLint viewLoc = glGetUniformLocation(lightingShader.Program, "view");

		GLint projLoc = glGetUniformLocation(lightingShader.Program, "projection");



		// Pass the matrices to the shader

		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));



		glm::mat4 model(1);



		// Carga de modelo 

		model = glm::mat4(1);

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		Piso.Draw(lightingShader);



		model = glm::mat4(1);

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);



		// Body

		modelTemp = model = glm::translate(model, glm::vec3(dogPosX, dogPosY, dogPosZ));

		modelTemp = model = glm::rotate(model, glm::radians(rotDog), glm::vec3(0.0f, 1.0f, 0.0f));

		modelTemp = model = glm::rotate(model, glm::radians(rotDogZ), glm::vec3(0.0f, 0.0f, 1.0f)); // Rotación Z

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		DogBody.Draw(lightingShader);



		// Head

		model = modelTemp;

		model = glm::translate(model, glm::vec3(0.0f, 0.093f, 0.208f));

		model = glm::rotate(model, glm::radians(head), glm::vec3(0.0f, 0.0f, 1.0f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		HeadDog.Draw(lightingShader);



		// Tail 

		model = modelTemp;

		model = glm::translate(model, glm::vec3(0.0f, 0.026f, -0.288f));

		model = glm::rotate(model, glm::radians(tail), glm::vec3(0.0f, 0.0f, -1.0f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		DogTail.Draw(lightingShader);



		// Front Left Leg

		model = modelTemp;

		model = glm::translate(model, glm::vec3(0.112f, -0.044f, 0.074f));

		model = glm::rotate(model, glm::radians(rotFLeft), glm::vec3(1.0f, 0.0f, 0.0f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		F_LeftLeg.Draw(lightingShader);



		// Front Right Leg

		model = modelTemp;

		model = glm::translate(model, glm::vec3(-0.111f, -0.055f, 0.074f));

		model = glm::rotate(model, glm::radians(rotFRight), glm::vec3(1.0f, 0.0f, 0.0f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		F_RightLeg.Draw(lightingShader);



		// Back Left Leg

		model = modelTemp;

		model = glm::translate(model, glm::vec3(0.082f, -0.046f, -0.218f));

		model = glm::rotate(model, glm::radians(rotBLeft), glm::vec3(1.0f, 0.0f, 0.0f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		B_LeftLeg.Draw(lightingShader);



		// Back Right Leg

		model = modelTemp;

		model = glm::translate(model, glm::vec3(-0.083f, -0.057f, -0.231f));

		model = glm::rotate(model, glm::radians(rotBRight), glm::vec3(1.0f, 0.0f, 0.0f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		B_RightLeg.Draw(lightingShader);



		// Ball

		model = glm::mat4(1);

		glEnable(GL_BLEND);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 1);

		model = glm::rotate(model, glm::radians(rotBall), glm::vec3(0.0f, 1.0f, 0.0f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		Ball.Draw(lightingShader);

		glDisable(GL_BLEND);

		glBindVertexArray(0);



		// Draw skybox as last

		glDepthFunc(GL_LEQUAL);

		skyboxShader.Use();

		view = glm::mat4(glm::mat3(camera.GetViewMatrix()));

		glUniformMatrix4fv(glGetUniformLocation(skyboxShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

		glUniformMatrix4fv(glGetUniformLocation(skyboxShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));



		// skybox cube

		glBindVertexArray(skyboxVAO);

		glActiveTexture(GL_TEXTURE0);

		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);

		glDrawArrays(GL_TRIANGLES, 0, 36);

		glBindVertexArray(0);

		glDepthFunc(GL_LESS);



		// Lamp object

		lampShader.Use();

		modelLoc = glGetUniformLocation(lampShader.Program, "model");

		viewLoc = glGetUniformLocation(lampShader.Program, "view");

		projLoc = glGetUniformLocation(lampShader.Program, "projection");



		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));



		model = glm::mat4(1);

		model = glm::translate(model, lightPos);

		model = glm::scale(model, glm::vec3(0.2f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));



		model = glm::mat4(1);

		model = glm::translate(model, pointLightPositions[0]);

		model = glm::scale(model, glm::vec3(0.2f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		glBindVertexArray(VAO);

		glDrawArrays(GL_TRIANGLES, 0, 36);

		glBindVertexArray(0);



		glfwSwapBuffers(window);

	}



	glDeleteVertexArrays(1, &VAO);

	glDeleteBuffers(1, &VBO);

	glDeleteBuffers(1, &EBO);

	glDeleteVertexArrays(1, &skyboxVAO);

	glDeleteBuffers(1, &skyboxVBO);



	glfwTerminate();

	return 0;

}



// Moves/alters the camera positions based on user input

void DoMovement()

{

	// --- DOG POSING CONTROLS ---



	// Cabeza

	if (keys[GLFW_KEY_4]) head += 1.0f;

	if (keys[GLFW_KEY_5]) head -= 1.0f;



	// Rotación general (Y)

	if (keys[GLFW_KEY_2]) rotDog += 1.0f;

	if (keys[GLFW_KEY_3]) rotDog -= 1.0f;



	// Rotación Z (muertito)

	if (keys[GLFW_KEY_O]) rotDogZ += 1.0f;

	if (keys[GLFW_KEY_P]) rotDogZ -= 1.0f;



	// Movimiento X/Z

	if (keys[GLFW_KEY_H]) dogPosZ += 0.01f;

	if (keys[GLFW_KEY_Y]) dogPosZ -= 0.01f;

	if (keys[GLFW_KEY_G]) dogPosX -= 0.01f;

	if (keys[GLFW_KEY_J]) dogPosX += 0.01f;



	// Subir / Bajar cuerpo (Sentarse/Agacharse)

	if (keys[GLFW_KEY_6]) dogPosY -= 0.01f;

	if (keys[GLFW_KEY_7]) dogPosY += 0.01f;



	// Pata Delantera Izquierda

	if (keys[GLFW_KEY_Z]) rotFLeft += 1.0f;

	if (keys[GLFW_KEY_X]) rotFLeft -= 1.0f;



	// Pata Delantera Derecha

	if (keys[GLFW_KEY_C]) rotFRight += 1.0f;

	if (keys[GLFW_KEY_V]) rotFRight -= 1.0f;



	// Pata Trasera Izquierda

	if (keys[GLFW_KEY_B]) rotBLeft += 1.0f;

	if (keys[GLFW_KEY_N]) rotBLeft -= 1.0f;



	// Pata Trasera Derecha

	if (keys[GLFW_KEY_M]) rotBRight += 1.0f;

	if (keys[GLFW_KEY_COMMA]) rotBRight -= 1.0f;



	// --- CAMERA AND LIGHT CONTROLS ---

	if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP]) camera.ProcessKeyboard(FORWARD, deltaTime);

	if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN]) camera.ProcessKeyboard(BACKWARD, deltaTime);

	if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT]) camera.ProcessKeyboard(LEFT, deltaTime);

	if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT]) camera.ProcessKeyboard(RIGHT, deltaTime);



	if (keys[GLFW_KEY_T]) pointLightPositions[0].x += 0.01f;

	if (keys[GLFW_KEY_U]) pointLightPositions[0].z -= 0.1f;

}



// Is called whenever a key is pressed/released via GLFW

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)

{

	if (keys[GLFW_KEY_L])

	{

		if (play == false && (FrameIndex > 1))

		{

			resetElements();

			//First Interpolation

			interpolation();



			play = true;

			playIndex = 0;

			i_curr_steps = 0;

		}

		else

		{

			play = false;

		}

	}



	if (keys[GLFW_KEY_K])

	{

		if (FrameIndex < MAX_FRAMES)

		{

			saveFrame();

		}

	}



	// --- CONTROLES DE ARCHIVO ---

	if (keys[GLFW_KEY_8]) // Exportar

	{

		saveAnimationToFile();

		keys[GLFW_KEY_8] = false;

	}



	if (keys[GLFW_KEY_9]) // Importar

	{

		loadAnimationFromFile();

		keys[GLFW_KEY_9] = false;

	}

	// ----------------------------



	if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)

	{

		glfwSetWindowShouldClose(window, GL_TRUE);

	}



	if (key >= 0 && key < 1024)

	{

		if (action == GLFW_PRESS)

		{

			keys[key] = true;

		}

		else if (action == GLFW_RELEASE)

		{

			keys[key] = false;

		}

	}



	if (keys[GLFW_KEY_SPACE])

	{

		active = !active;

		if (active)

		{

			Light1 = glm::vec3(0.2f, 0.8f, 1.0f);

		}

		else

		{

			Light1 = glm::vec3(0);

		}

	}

}



void Animation() {

	if (play)

	{

		if (i_curr_steps >= i_max_steps) //end of animation between frames?

		{

			playIndex++;

			if (playIndex > FrameIndex - 2) //end of total animation?

			{

				printf("termina anim\n");

				playIndex = 0;

				play = false;

			}

			else //Next frame interpolations

			{

				i_curr_steps = 0; //Reset counter

				interpolation();

			}

		}

		else

		{

			//Draw animation

			dogPosX += KeyFrame[playIndex].incX;

			dogPosY += KeyFrame[playIndex].incY;

			dogPosZ += KeyFrame[playIndex].incZ;



			rotDog += KeyFrame[playIndex].rotDogInc;

			rotDogZ += KeyFrame[playIndex].rotDogZInc;

			head += KeyFrame[playIndex].headInc;

			tail += KeyFrame[playIndex].tailInc;



			rotFLeft += KeyFrame[playIndex].rotFLeftInc;

			rotFRight += KeyFrame[playIndex].rotFRightInc;

			rotBLeft += KeyFrame[playIndex].rotBLeftInc;

			rotBRight += KeyFrame[playIndex].rotBRightInc;



			i_curr_steps++;

		}

	}

}



void MouseCallback(GLFWwindow* window, double xPos, double yPos)

{

	if (firstMouse)

	{

		lastX = xPos;

		lastY = yPos;

		firstMouse = false;

	}



	GLfloat xOffset = xPos - lastX;

	GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left



	lastX = xPos;

	lastY = yPos;



	camera.ProcessMouseMovement(xOffset, yOffset);

}