// PlantillaOpenGL.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>

#define GLEW_STATIC

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <iostream>

using namespace std;

//Declaramos apuntador de ventana
GLFWwindow *window;

float xTriangulo = 0.0f;
float yTriangulo = 0.0f;

float velocidad = 0.001f;

double tiempoAnterior = 0.0;
double tiempoActual = 0.0;
double tiempoDiferencial = 0.05;

void dibujarTraingulo(){
	glPushMatrix();
	glTranslatef(xTriangulo, yTriangulo, 0.0f);
	glBegin(GL_TRIANGLES);
	glColor3f(1, 0, 0);
	glVertex3f(0, 0.2, 0);
	glVertex3f(0.2, -0.2, 0);
	glVertex3f(-0.2, -0.2, 0);
	glEnd();
	glPopMatrix();
}

void moverTriangulo() 
{
	int estadoTeclaDerecha = glfwGetKey(window, GLFW_KEY_RIGHT);
	if (estadoTeclaDerecha == GLFW_PRESS)
	{
		xTriangulo += velocidad * tiempoDiferencial;
	
	}

	
	int estadoTeclaIzquierda = glfwGetKey(window, GLFW_KEY_LEFT);
	if (estadoTeclaIzquierda == GLFW_PRESS)
	{
		xTriangulo -= velocidad * tiempoDiferencial;

	}

	int estadoTeclaArriba = glfwGetKey(window, GLFW_KEY_UP);
	if (estadoTeclaArriba == GLFW_PRESS)
	{
		yTriangulo += velocidad * tiempoDiferencial;

	}

	int estadoTeclaAbajo = glfwGetKey(window, GLFW_KEY_DOWN);
	if (estadoTeclaAbajo == GLFW_PRESS)
	{
		yTriangulo -= velocidad * tiempoDiferencial;

	}

}
void dibujar()
{
	dibujarTraingulo();
}

void actualizar() 
{
	tiempoActual = glfwGetTime();
	tiempoDiferencial = tiempoActual - tiempoAnterior;
	moverTriangulo();
	tiempoAnterior = glfwGetTime();
}

void teclado_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_RIGHT && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		xTriangulo += velocidad;
	}
	if (key == GLFW_KEY_LEFT && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		xTriangulo -= velocidad;
	}
	if (key == GLFW_KEY_UP && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		yTriangulo += velocidad;
	}
	if (key == GLFW_KEY_DOWN && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		yTriangulo -= velocidad;
	}
}

int main()
{
	

	//si no se pudo inicializar glfw terminamos ejecución
	if (!glfwInit())
		exit(EXIT_FAILURE);

	//si se pudo iniciar GLFW entonces inicializamos la ventana
	window = glfwCreateWindow(1024, 768, "Ventana", NULL, NULL);

	//si no podemos iniciar la ventana entonces terminamos la ejecución
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	//establecemos el contexto
	glfwMakeContextCurrent(window);

	//UNa vez establecido el contexto activamos funciones modernas (CPU/GPU)
	glewExperimental = true;
	GLenum errorGlew = glewInit();

	if (errorGlew != GLEW_OK) {
		cout << glewGetErrorString(errorGlew);
	}

	const GLubyte *versionGL = glGetString(GL_VERSION);
	cout << "Version OpenGL: " << versionGL;

	//glfwSetKeyCallback(window, teclado_callback);

	tiempoAnterior = glfwGetTime();

	//Cilco de dibijo (Draw loop)
	while (!glfwWindowShouldClose(window)) {
		//Establecer region de dibujo
		glViewport(0, 0, 1024, 768);
		//Esctablece el color de borrado
		glClearColor(0.25, 0, 0.3, 1);
		//Borramos
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Rutina de dibujo
		dibujar();
		actualizar();

		//Cambiar los buffers
		glfwSwapBuffers(window);
		//Reconocer si hay entradas
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

    return 0;
}

