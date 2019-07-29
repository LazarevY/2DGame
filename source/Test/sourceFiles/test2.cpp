#include <Engine/Engine.h>
#include <Engine/Components/Grafics/Render/SimpleTextureRender.h>
#include <Windows.h>
#include <glm/gtc/matrix_transform.hpp>
//#define DEBUG_AXIS



const float world_unit = 100;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void scrollCallback(GLFWwindow* window, double offsetX, double offsetY);
void load_resource(ResourceManager* manager);
void key_handle();

Frame* frame = new Frame();
const unsigned WIDTH = frame->getWidth();
const unsigned HEIGHT = frame->getHeight();

#define VIEWPORT_HALF_X (WIDTH/2.f)
#define VIEWPORT_HALF_Y (HEIGHT/2.f)

Camera2D camera(vector2(0, 0), 1, VIEWPORT_HALF_X / world_unit, VIEWPORT_HALF_Y / world_unit, world_unit);
bool keys[1024];
vector2 camera_move_x(20, 0);
vector2 camera_move_y(0, 20);

float delta_time = 0;
float last_frame = 0;
//#define DEBUG_AXIS
int main(int argc, char* argv[])
{

	glfwSetKeyCallback(frame->getWindow(), key_callback);
	glfwSetScrollCallback(frame->getWindow(), scrollCallback);
	ResourceManager* resource_manager = new ResourceManager();

	load_resource(resource_manager);


	Texture2D* horse = resource_manager->getResource<Texture2D>("horse").getSourcePtr();
	ShaderProgram* program = resource_manager->getResource<ShaderProgram>("simple_texture").getSourcePtr();

#ifdef DEBUG_AXIS
	ShaderProgram* line_shader= 	resource_manager->load_resource<ShaderProgram>
	("../../resources/Shaders/line_render.glsl", "line_shader", nullptr)->getSourcePtr();	
	
	ShaderProgram* line_unit_shader= 	resource_manager->load_resource<ShaderProgram>
	("../../resources/Shaders/line_unit_render.glsl", "line_unit_shader", nullptr)->getSourcePtr();
	line_unit_shader->setUniformId("stride");
#endif
	horse->setWrapMode(Texture2D::WrapMode::ClampToEdge);
	horse->setMinFiltering(Texture2D::FilteringType::Linear);
	horse->setMagFiltering(Texture2D::FilteringType::LinearMipmapLinear);

	SimpleTextureRender texture_render(program);
	
	
	// 450x 327.5

	float local_width = 450.f / (2 * world_unit);
	float local_height = 327.5f/ (2 * world_unit);
	std::vector<float> local_horse_vertex
	{
		-local_width, -local_height,		0.f,	0.f,
		-local_width,   local_height,		0.f,	1.f,
		 local_width,	  -local_height,		1.f,	0.f,
		local_width,		local_height,	1.f,	1.f
	};
#ifdef DEBUG_AXIS
	std::vector<float> line_vertex
	{	-1.f, 0.f,		1.f, 0.f,
		0.f, -1.f,		0.f, 1.f
	};

	std::vector<GLuint> line_index{0,1,2,3};
	std::vector<GLuint> line_unit_index{0,1};

#endif
	std::vector<GLuint > indexes = { 0,1,2,		1,2,3};


	ArrayBufferHandler horse_buffer(local_horse_vertex.size() * sizeof(GLfloat), local_horse_vertex, ArrayBufferDataType::StaticData);
	horse_buffer.addElementBuffer();
	horse_buffer.setElementBufferData(indexes.size() * sizeof(GLuint), indexes, ArrayBufferDataType::StaticData);
	horse_buffer.setAttributes(0, 4, GL_FLOAT, false, 0 * sizeof(float), 0);
#ifdef DEBUG_AXIS
	ArrayBufferHandler line_buffer(line_vertex.size() * sizeof(float), line_vertex, ArrayBufferDataType::StaticData);
	line_buffer.addElementBuffer();
	line_buffer.setElementBufferData(line_index.size() * sizeof(GLuint), line_index, ArrayBufferDataType::StaticData);
	line_buffer.setAttributes(0, 2, GL_FLOAT, false, 2* sizeof(float), 0);

	ArrayBufferHandler x_axis(4 * sizeof(float), std::vector<GLfloat>{0.f, -0.05, 0.f, 0.05}, ArrayBufferDataType::StaticData);
	x_axis.addElementBuffer();
	x_axis.setElementBufferData(16, line_unit_index, ArrayBufferDataType::StaticData);
	x_axis.setAttributes(0, 2, GL_FLOAT, false, 2 * sizeof(float), 0);	
	
	ArrayBufferHandler y_axis(4 * sizeof(float), std::vector<GLfloat>{-0.05f, 0.f, 0.05f, 0.f}, ArrayBufferDataType::StaticData);
	y_axis.addElementBuffer();
	y_axis.setElementBufferData(16, line_unit_index, ArrayBufferDataType::StaticData);
	y_axis.setAttributes(0, 2, GL_FLOAT, false, 2 * sizeof(float), 0);
#endif
	matrix4 model;
	model = glm::scale(model, vector3(0.8, 0.8, 1.0));






	while(!glfwWindowShouldClose(frame->getWindow()))
	{
#ifdef DEBUG_AXIS
		vector2 x_str(1/camera.getZoom() * world_unit / VIEWPORT_HALF_X, 0);
		vector2 y_str(0, 1/camera.getZoom() * world_unit / VIEWPORT_HALF_Y);
#endif
		
		last_frame = glfwGetTime();
	//	std::cout << delta_time << std::endl;
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwPollEvents();
		key_handle();
		matrix4 view = camera.getViewMatrix();
		matrix4 proj_view = camera.getProjectionMatrix() * view;
		texture_render.render(horse_buffer, *horse, model, proj_view);

		
		

#ifdef DEBUG_AXIS
		line_shader->useProgram();
		line_buffer.drawIndexData(DrawDataMode::Lines, 4, DrawDataType::UnsignedInt, 0);

		line_unit_shader->useProgram();
		matrix3 x_stride = glm::translate(matrix3(), vector2(x_str));

		for (int i = 0; i < 25; ++i)
		{
			line_unit_shader->setUniformParameter("stride", x_stride);
			x_axis.drawIndexData(DrawDataMode::Lines, 2, DrawDataType::UnsignedInt, 0);
			 x_stride = glm::translate(x_stride, x_str);
		}
		matrix3 y_stride = glm::translate(matrix3(), y_str);
		for (int i = 0; i < 15; ++i)
		{
			line_unit_shader->setUniformParameter("stride", y_stride);
			y_axis.drawIndexData(DrawDataMode::Lines, 2, DrawDataType::UnsignedInt, 0);
			 y_stride = glm::translate(y_stride,y_str);
		}
#endif


		glfwSwapBuffers(frame->getWindow());

		Sleep(20);
		delta_time = glfwGetTime() - last_frame;
	}

	delete frame;
	delete resource_manager;

	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if(key > 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			keys[key] = true;
		if (action == GLFW_RELEASE)
			keys[key] = false;
	}
}

void key_handle()
{
	if (keys[GLFW_KEY_D])
		camera.setPosition(camera.getPosition() + delta_time* camera_move_x);	
	if (keys[GLFW_KEY_A])
		camera.setPosition(camera.getPosition() - delta_time  * camera_move_x);
	if (keys[GLFW_KEY_W])
		camera.setPosition(camera.getPosition() + delta_time   * camera_move_y);
	if (keys[GLFW_KEY_S])
		camera.setPosition(camera.getPosition() - delta_time   * camera_move_y);
	if (keys[GLFW_KEY_E])
	{
		camera.setPosition(vector2(0));
		camera.setZoom(1);
	}
		
}


void scrollCallback(GLFWwindow * window, double offsetX, double offsetY)
{
	if (offsetY > 0 && camera.getZoom() < 3)
		camera.setZoom(camera.getZoom() + 0.1);	
	if (offsetY < 0 && camera.getZoom() > 0.3)
		camera.setZoom(camera.getZoom() - 0.1);
}

void load_resource(ResourceManager* manager)
{
	manager->load_resource<ShaderProgram>("../../resources/Shaders/Temp/simple_texture.glsl", "simple_texture", nullptr);
	manager->load_resource<Texture2D>("../../resources/Textures/horse.png", "horse", Texture::TexturePixelData::Load_RGBA);
}
