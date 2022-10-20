#include "Module.h"	
#include "SString.h"

struct GLFWwindow;

class Window : public Module
{
	public:

		Window(bool isActive);
		virtual ~Window();
		bool Awake();
		bool Start();
		bool CleanUp();


		void Swapbuffers();
		void Clear();

		// Changae title
		void SetTitle(const char* title);

		// Retrive window size
		void GetWindowSize(unsigned int& width, unsigned int& height) const;

		// Retrieve window scale
		unsigned int GetScale() const;

		// Retrieve window Width
		int GetWidth() const;

		// Retrieve window height
		int GetHeight() const;

		void SetFullScreen(bool fullScreen);
		bool GetFullScreen();
		virtual bool HandleEvent( Event* event);
		void ResizeWindow(int newWidth, int newHeight);
		

	public:
		// The window we'll be rendering to
		GLFWwindow* window;
	private:
		SString title;
		  int width;
		  int height;
		unsigned int scale;

		bool fullScreen;

};

