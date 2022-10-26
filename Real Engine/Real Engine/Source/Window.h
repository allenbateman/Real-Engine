#include "Module.h"	
#include "SString.h"
#include "Events.h"


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
		
		static void DropCallBack(GLFWwindow* window, int count, const char** paths);
		void RetrieveDropCallBack(const char* path);
		

	public:
		// The window we'll be rendering to
		GLFWwindow* window;
		OnFileDrop fileDropEvent;

		static const char* filePath;
	private:
		SString title;
		  int width;
		  int height;
		unsigned int scale;

		bool fullScreen;

};

