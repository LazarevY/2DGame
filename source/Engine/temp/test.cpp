
#include <Engine.h>
#include <Windows.h>

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}


int main(int argc, char* argv[])
{
	Frame* frame = new Frame();
	ResourceManager* resource_manager = new ResourceManager();
	glfwSetKeyCallback(frame->getWindow(), key_callback);

	std::vector<GLfloat> background_vertices = {
		-1.0f, -1.0f, 0, 0,
		-1.0f, 1.0f, 0, 1.0f,
		1.0f, -1.0f, 1.0f, 0,
		1.0f, 1.0f, 1.0f, 1.0f
	};
	std::vector<GLfloat> horse_vertices = {
		-0.4f, 0, 0, 0,
		-0.4f, 1.0f, 0, 1.0f,
		0.4f, 0, 1.0f, 0,
		0.4f, 1.0, 1.0f, 1.0f
	};
	std::vector<GLfloat> horse_no_normalized = {
		0, 200, 0, 0,
		0, 400, 0, 1,
		300, 200, 1, 0,
		300, 400, 1, 1,
	};
	std::vector<GLuint> index_vec = {
		0, 1, 2,
		1, 2, 3
	};


	ArrayBufferHandler* horse_picture_buffer = new ArrayBufferHandler(horse_vertices.size() * sizeof(GLfloat),
	                                                                  horse_vertices, ArrayBufferDataType::StaticData);
	horse_picture_buffer->addElementBuffer();
	horse_picture_buffer->setElementBufferData(index_vec.size() * sizeof(GLuint), index_vec,
	                                           ArrayBufferDataType::StaticData);
	horse_picture_buffer->setAttributes(0, 2, GL_FLOAT, false, 4 * sizeof(GLfloat), (GLvoid*)nullptr);
	horse_picture_buffer->setAttributes(1, 2, GL_FLOAT, false, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));

	ArrayBufferHandler* background_buffer = new ArrayBufferHandler(background_vertices.size() * sizeof(float),
	                                                               background_vertices,
	                                                               ArrayBufferDataType::StaticData);
	background_buffer->addElementBuffer();
	background_buffer->setElementBufferData(index_vec.size() * sizeof(GLuint), index_vec,
	                                        ArrayBufferDataType::StaticData);
	background_buffer->setAttributes(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)nullptr);
	background_buffer->setAttributes(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));

	Texture* tex_test = resource_manager->load_resource<Texture>(
		"C:/Users/LAZAREV/source/repos/2DGame/resources/Textures/horse.png", "",
		Texture::TexturePixelData::Load_RGBA)->getSourcePtr();
	tex_test->setWrapMode(Texture::WrapModes::ClampToEdge);
	tex_test->setMinFiltering(Texture::FilteringType::Linear);
	tex_test->setMagFiltering(Texture::FilteringType::LinearMipmapLinear);

	Texture* bricks = resource_manager->load_resource<Texture>(
		"C:/Users/LAZAREV/source/repos/2DGame/resources/Textures/texture_4.jpg",
		"background", Texture::TexturePixelData::Load_RGB)->getSourcePtr();
	bricks->setWrapMode(Texture::WrapModes::ClampToEdge);
	bricks->setMinFiltering(Texture::FilteringType::Linear);
	bricks->setMagFiltering(Texture::FilteringType::LinearMipmapLinear);

	ShaderProgram* simple_shader = resource_manager->
	                               load_resource<ShaderProgram>(
		                               "C:/Users/LAZAREV/source/repos/2DGame/resources/Shaders/Simple/simpleShader.shd")
	                               ->getSourcePtr();

	while (!glfwWindowShouldClose(frame->getWindow()))
	{
		glfwPollEvents();
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		simple_shader->useProgram();
		bricks->bindTexture();
		background_buffer->drawIndexData(DrawDataMode::Triangles, 6, DrawDataType::UnsignedInt, nullptr);
		bricks->unbindTexture();
		tex_test->bindTexture();
		horse_picture_buffer->drawIndexData(DrawDataMode::Triangles, 6, DrawDataType::UnsignedInt, nullptr);

		glfwSwapBuffers(frame->getWindow());
		Sleep(20);
	}
	delete frame;
	delete resource_manager;
	delete simple_shader;
	delete bricks;
	delete tex_test;

	delete horse_picture_buffer;
	delete background_buffer;
	system("pause");

	return 0;
}
