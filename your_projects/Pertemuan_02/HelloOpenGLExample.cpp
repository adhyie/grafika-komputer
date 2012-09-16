#include <stdio.h>
#include <stdlib.h>
#include <GL/glfw.h>
#include "GLFWApplication.h"



class HelloOpenGLExample: public GLFWApplication
{

	virtual void init(void){

	}

	virtual void update(double time){

	}

	virtual void render(void){

		// Setup viewport
		glViewport( 0, 0, width, height );

		// Clear color buffer to black
		
		glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
		glClear( GL_COLOR_BUFFER_BIT );
		

		// Select and setup the projection matrix
		glMatrixMode( GL_PROJECTION );
		glLoadIdentity();
		gluPerspective( 65.0f, (GLfloat)width/(GLfloat)height, 1.0f, 100.0f );

		// Select and setup the modelview matrix
		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity();
		gluLookAt( 0.0f, 1.0f, 0.0f,    // Eye-position
			0.0f, 20.0f, 0.0f,   // View-point
			0.0f, 0.0f, 1.0f );  // Up-vector

		// Draw colorful triangle with TRIANGLES primitive mode
		glTranslatef( 0.0f, 14.0f, 0.0f );

		glBegin( GL_TRIANGLES );
		glColor3f( 1.0f, 0.0f, 0.0f );
		glVertex3f( -5.0f, 0.0f, -4.0f );
		glColor3f( 0.0f, 1.0f, 0.0f );
		glVertex3f( 5.0f, 0.0f, -4.0f );
		glColor3f( 0.0f, 0.0f, 1.0f );
		glVertex3f( 0.0f, 0.0f, 6.0f );
		glEnd();
	}

	virtual void shutdown(void){

	}

};


int main(void){
	// Create application's instance
	HelloOpenGLExample app;
	// Application's settings
	app.width = 800;
	app.height = 600;
	app.title = "Hello OpenGL!";
	app.fullscreen = false;
	app.vsync = true;
	app.showFPS = true;
	// Start application
	app.start();
}
