#include <stdio.h>
#include <stdlib.h>
#include <GL/glfw.h>


class GLFWApplication
{
public:
	virtual void init(void) = 0;
	virtual void update(double time) = 0;
	virtual void render(void) = 0;
	int width, height, x;
	double t;

	void start(int width, int height, bool fullscreen, const char * title, bool vsync){

		// Create application's window
		initWindow(width, height, fullscreen, title, vsync);

		// Initialisation procedure
		init();

		// Application loop
		loop();

		// Close OpenGL window and terminate GLFW
		glfwTerminate();

		exit( EXIT_SUCCESS );
	}

	void initWindow(int width, int height, bool fullscreen, const char * title, bool vsync){
		// Initialise GLFW
		if( !glfwInit() )
		{
			fprintf( stderr, "Failed to initialize GLFW\n" );
			exit( EXIT_FAILURE );
		}

		// Open a window and create its OpenGL context
		if( !glfwOpenWindow( width, height, 0,0,0,0, 0,0, fullscreen?GLFW_FULLSCREEN:GLFW_WINDOW ) )
		{
			fprintf( stderr, "Failed to open GLFW window\n" );

			glfwTerminate();
			exit( EXIT_FAILURE );
		}

		// Set a window title
		glfwSetWindowTitle(title);

		// Ensure we can capture the escape key being pressed below
		glfwEnable( GLFW_STICKY_KEYS );

		// Enable vertical sync (on cards that support it)
		glfwSwapInterval( vsync?1:0 );
	}



	void loop(){
		do
		{

			t = glfwGetTime();

			// Your update application logics procedure here ...
			update(t);

			// Your rendering procedure here ...
			render();

			// Swap buffers
			glfwSwapBuffers();

		} // Check if the ESC key was pressed or the window was closed
		while( glfwGetKey( GLFW_KEY_ESC ) != GLFW_PRESS &&
			glfwGetWindowParam( GLFW_OPENED ) );
	}


};