#include "Module.h"	
#include "SString.h"

struct GLFWwindow;

class Window : public Module
{
	public:

		Window(bool isActive);

		// Destructor
		virtual ~Window();

		// Called before render is available
		bool Awake();

		bool PreUpdate();

		bool PostUpdate();

		// Called before quitting
		bool CleanUp();

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

