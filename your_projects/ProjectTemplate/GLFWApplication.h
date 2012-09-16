#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <GL/glfw.h>
#include <FTGLPixmapFont.h>

class GLFWApplication
{
private:
	FTFont * defaultFont;
	int old_fps;
	char fps_string[40];

protected:

public:
	virtual void init(void) = 0;
	virtual void update(double time) = 0;
	virtual void render(void) = 0;
	virtual void shutdown(void) = 0;
	int width, height, fps, redbits, greenbits, bluebits, alphabits, stencilbits, depthbits;
	double time, lasttime;
	bool fullscreen, vsync, showFPS, showInfo;
	const char * title;

	void start(){

		// Create application's window
		initWindow();

		// Init default font
		initDefaultFont();

		// Initialisation procedure
		init();

		// Application's loop
		loop();

		// Shutdown procedure
		shutdown();

		// Close OpenGL window and terminate GLFW
		glfwTerminate();

		exit( EXIT_SUCCESS );
	}

	void initWindow(){
		// Initialise GLFW
		if( !glfwInit() )
		{
			fprintf( stderr, "Failed to initialize GLFW\n" );
			exit( EXIT_FAILURE );
		}

		// Open a window and create its OpenGL context
		if( !glfwOpenWindow( width, height, redbits, greenbits, bluebits, alphabits, depthbits, stencilbits, fullscreen?GLFW_FULLSCREEN:GLFW_WINDOW ) )
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
		lasttime = glfwGetTime();
		old_fps = 0;
		fps = 0;
		do
		{
			// Get delta time
			time = glfwGetTime();

			// Get window size (may be different than the requested size)
			glfwGetWindowSize( &width, &height );

			// Special case: avoid division by zero below
			height = height > 0 ? height : 1;

			// update fps
			updateFPS();

			// Your update application logics procedure here ...
			update(time);

			// Your rendering procedure here ...
			render();

			// Show FPS
			if(showFPS){
				drawFPS();
			}

			// Swap buffers
			glfwSwapBuffers();

		} // Check if the ESC key was pressed or the window was closed
		while( glfwGetKey( GLFW_KEY_ESC ) != GLFW_PRESS &&
			glfwGetWindowParam( GLFW_OPENED ) );
	}

	void updateFPS(){
		if (time - lasttime > 1) {
			old_fps = fps;
			fps = 0;
			lasttime += 1;
		}
		fps++;
	}

	void drawFPS(){
		char fps_str[21];
		itoa(old_fps, fps_str, 10);
		strcpy(fps_string, "FPS : ");
		strcat(fps_string, fps_str);
		ortho();
		glColor3f(1,1,1);
		drawString(fps_string, 5,height-18);
	}

	void initDefaultFont(){
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		defaultFont = new FTGLPixmapFont("C:\\Windows\\Fonts\\arial.ttf");
		setFontSize(18);
	}

	void ortho(){
		GLdouble size;

		GLdouble aspect;

		aspect = (GLdouble)width / (GLdouble)height;

		// Use the whole window.
		glViewport(0, 0, width, height);

		// We are going to do some 2-D orthographic drawing.
		glMatrixMode(GL_PROJECTION);

		glLoadIdentity();

		size = (GLdouble)((width >= height) ? width : height) / 2.0;

		if (width <= height) {

			aspect = (GLdouble)height/(GLdouble)width;

			glOrtho(-size, size, -size*aspect, size*aspect,

				-100000.0, 100000.0);

		}

		else {

			aspect = (GLdouble)width/(GLdouble)height;

			glOrtho(-size*aspect, size*aspect, -size, size,

				-100000.0, 100000.0);

		}

		// Make the world and window coordinates coincide so that 1.0 in

		// model space equals one pixel in window space.
		glScaled(aspect, aspect, 1.0);

		// Now determine where to draw things.
		glMatrixMode(GL_MODELVIEW);

		glLoadIdentity();
	}

	void drawString(const char *s, int x, int y)
	{
		float h = defaultFont->LineHeight()/2+2;
		glRasterPos2f(x-(width/2),-y+(height/2-h));
		defaultFont->Render(s);
	}

	void setFontSize(int fontSize){
	defaultFont->FaceSize(fontSize);
	}
};