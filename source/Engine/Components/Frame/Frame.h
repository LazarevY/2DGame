#ifndef FRAME_H
#define FRAME_H

#include "Engine/Components/GraphicsComponents.h"
class Frame
{
public:
	Frame();
	~Frame();

	GLFWwindow* getWindow() const;
	void setTitle(const char* new_title);

	 unsigned getWidth() const;
	 unsigned getHeight() const;
	//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
private:
	GLFWwindow* window;
	 unsigned width;
	 unsigned height;

};

#endif  FRAME_H