
#include <Engine/Engine.h>
#include <Windows.h>

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);


bool inverse_x = false;
vector2 pos = vector2(1500, 192.5);

vector2 player_direction(1,0);
float player_speed = 35.f;

bool keys[1024];
int main_off(int argc, char* argv[])
{
	std::cout << glGetError() << std::endl;
#define TEXTURE_2D_ARRAY_TEST
#ifndef TEXTURE_2D_ARRAY_TEST
	Frame* frame = new Frame();
	ResourceManager* resource_manager = new ResourceManager();
	glfwSetKeyCallback(frame->getWindow(), key_callback);
	// 1500x955
	std::vector<GLfloat> backgr_ver ={
			0.f,		0.f,				0.f,		0.f,
			0.f,		1080.f,			0.f,		955.f,
			1920.f,	0.f,				1500.f,	0.f,
			1920.f,	1080.f,			1500.f,	955.f
	};
	//1800x1310
	std::vector<GLfloat> horse_ver = {
		0.f,		0.f,
		0.f,		1310.f,
		1800.f,	0.f,
		1800.f,	1310.f
	};

	std::vector<GLuint> index_vec = {
		0, 1, 2,
		1, 2, 3
	};

	std::vector<GLfloat> test_anim_data = {	0.f,		0.f,	
																	0.f,		385.f,
																	280.f,	0.f,
																	280.f,	385.f
																	};

	
	ArrayBufferHandler* horse_picture_buffer = new ArrayBufferHandler(horse_ver.size() * sizeof(GLfloat),
					horse_ver, ArrayBufferDataType::StaticData);
	horse_picture_buffer->addElementBuffer();
	horse_picture_buffer->setElementBufferData(index_vec.size() * sizeof(GLuint), index_vec,
	                                           ArrayBufferDataType::StaticData);

	horse_picture_buffer->setAttributes(0, 2, GL_FLOAT, false, 0 * sizeof(GLfloat), (GLvoid*)nullptr);


	ArrayBufferHandler* background_buffer = new ArrayBufferHandler(backgr_ver.size() * sizeof(float),
	                                                               backgr_ver,
	                                                               ArrayBufferDataType::StaticData);
	background_buffer->addElementBuffer();
	background_buffer->setElementBufferData(index_vec.size() * sizeof(GLuint), index_vec,
	                                        ArrayBufferDataType::StaticData);
	background_buffer->setAttributes(0, 2, GL_FLOAT, false, 4 * sizeof(GLfloat), (GLvoid*)nullptr);
	background_buffer->setAttributes(1, 2, GL_FLOAT, false, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));	
	
	ArrayBufferHandler* test_anim_buffer = new ArrayBufferHandler(test_anim_data.size() * sizeof(float),
	                                                               test_anim_data,
	                                                               ArrayBufferDataType::StaticData);
	test_anim_buffer->addElementBuffer();
	test_anim_buffer->setElementBufferData(index_vec.size() * sizeof(GLuint), index_vec,
	                                        ArrayBufferDataType::StaticData);
	test_anim_buffer->setAttributes(0, 2, GL_FLOAT, false, 0 * sizeof(GLfloat), (GLvoid*)nullptr);

	Texture2D* tex_test = resource_manager->load_resource<Texture2D>(
		"C:/Users/LAZAREV/source/repos/2DGame/resources/Textures/horse.png", "",
		Texture2D::TexturePixelData::Load_RGBA)->getSourcePtr();
	tex_test->setWrapMode(Texture2D::WrapMode::ClampToEdge);
	tex_test->setMinFiltering(Texture2D::FilteringType::Linear);
	tex_test->setMagFiltering(Texture2D::FilteringType::LinearMipmapLinear);

	Texture2D* anim_texture = resource_manager->load_resource<Texture2D>(
		"C:/Users/LAZAREV/source/repos/2DGame/resources/Textures/Animation_1.png", "",
		Texture2D::TexturePixelData::Load_RGBA)->getSourcePtr();
	anim_texture->setWrapMode(Texture2D::WrapMode::ClampToEdge);
	anim_texture->setMinFiltering(Texture2D::FilteringType::Linear);
	anim_texture->setMagFiltering(Texture2D::FilteringType::LinearMipmapLinear);

	Texture2D* bricks = resource_manager->load_resource<Texture2D>(
		"C:/Users/LAZAREV/source/repos/2DGame/resources/Textures/texture_4.jpg",
		"background", Texture2D::TexturePixelData::Load_RGB)->getSourcePtr();
	bricks->setWrapMode(Texture2D::WrapMode::ClampToEdge);
	bricks->setMinFiltering(Texture2D::FilteringType::Linear);
	bricks->setMagFiltering(Texture2D::FilteringType::LinearMipmapLinear);

	//ShaderProgram* backround_shader = resource_manager->
	//							load_resource<ShaderProgram>("C:/Users/LAZAREV/source/repos/2DGame/resources/Shaders/Simple/simple_transform_shader.glsl")
	//							->getSourcePtr();

	//	backround_shader->setUniformId("normalize_vertexMatrix");
	//	backround_shader->setUniformId("normalize_textureMatrix");

		ShaderProgram* union_shader = resource_manager->
			load_resource<ShaderProgram>("C:/Users/LAZAREV/source/repos/2DGame/resources/Shaders/Simple/union_texture_vertex.glsl")
			->getSourcePtr();

		union_shader->setUniformId("normalize_vertexMatrix");
		union_shader->setUniformId("normalize_textureMatrix	");
		union_shader->setUniformId("transformMatrix");


		SpriteAnimation* test_animation = new SpriteAnimation(anim_texture, 5,2,10);
		test_animation->setCurrentFrameNumber(0);
		SpriteAnimator* test_animator = new SpriteAnimator(test_animation, 0.1);

		ShaderProgram* animation_uniform_shader = resource_manager->
			load_resource<ShaderProgram>("C:/Users/LAZAREV/source/repos/2DGame/resources/Shaders/Simple/union_anim_shader.glsl")
			->getSourcePtr();

		animation_uniform_shader->setUniformId("normalize_vertexMatrix");
		animation_uniform_shader->setUniformId("transformMatrix");
		animation_uniform_shader->setUniformId("normalize_textureMatrix");
		animation_uniform_shader->setUniformId("offset_matrix");


	//matrix3 backgr_vertex = matrix3();

	//backgr_vertex= glm::scale(backgr_vertex, vector2(1.f / 960.f, 1.f / 540.f));
	//backgr_vertex = glm::translate(backgr_vertex, vector2(-960, -540));

	//matrix3 backgr_texture = matrix3();
	//backgr_texture = glm::scale(backgr_texture,vector2(1.f/bricks->getWidth(), 1.f/bricks->getHeight()));

	matrix3 horse_normalize_vertex = matrix3();
	horse_normalize_vertex = glm::scale(horse_normalize_vertex, vector2(1.f / 750.f, 2.f / 955.f));
	horse_normalize_vertex = glm::translate(horse_normalize_vertex, vector2(-750, -955.f/2.f));

	matrix3 horse_normalize_texture = matrix3();
	horse_normalize_texture = glm::scale(horse_normalize_texture,vector2(1.f/1500.f, 1.f/1310.f));

	matrix3 horse_transform = matrix3();

	horse_transform = glm::translate(horse_transform, vector2(600.f,30.f));
	horse_transform = glm::scale(horse_transform, vector2(0.3, 0.3));

	matrix3 anim_vertex_normalize = matrix::vertexNormalizeMatrix3x3(280, 385);
	matrix3 anim_texture_normalize = matrix::textureNormalizeMatrix3x3(1400, 770);
	matrix3 anim_transform = matrix3();
	
	anim_transform = glm::scale(anim_transform, vector2(0.20,0.25));
	anim_transform = glm::translate(anim_transform, vector2(400,0));
	test_animator->start(glfwGetTime());
	while (!glfwWindowShouldClose(frame->getWindow()))
	{
		glfwPollEvents();
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//simple_shader->useProgram();


		//backround_shader->useProgram();
		//glUniformMatrix3fv(backround_shader->getUniformId("normalize_vertexMatrix"), 1, false, glm::value_ptr(backgr_vertex));
		//glUniformMatrix3fv(backround_shader->getUniformId("normalize_textureMatrix"), 1, false, glm::value_ptr(backgr_texture));		
		//bricks->bindTexture();
		//background_buffer->drawIndexData(DrawDataMode::Triangles, 6, DrawDataType::UnsignedInt, nullptr);
		//bricks->unbindTexture();
		////simple_shader->useProgram();
		animation_uniform_shader->useProgram();
		test_animator->animate(glfwGetTime());
		glUniformMatrix3fv(animation_uniform_shader->getUniformId("normalize_vertexMatrix"), 1, false, glm::value_ptr(anim_vertex_normalize));
		glUniformMatrix3fv(animation_uniform_shader->getUniformId("normalize_textureMatrix"), 1, false, glm::value_ptr(anim_texture_normalize));
		glUniformMatrix3fv(animation_uniform_shader->getUniformId("offset_matrix"), 1, false, glm::value_ptr(test_animation->getOffsetMatrix()));
		glUniformMatrix3fv(animation_uniform_shader->getUniformId("transformMatrix"), 1, false, glm::value_ptr(anim_transform));

		anim_texture->bindTexture();
		
		test_anim_buffer->drawIndexData(DrawDataMode::Triangles, 6, DrawDataType::UnsignedInt, nullptr);

		//union_shader->useProgram();
		//glUniformMatrix3fv(union_shader->getUniformId("normalize_vertexMatrix"), 1, false, glm::value_ptr(horse_normalize_vertex));
		//glUniformMatrix3fv(union_shader->getUniformId("normalize_textureMatrix"), 1, false, glm::value_ptr(horse_normalize_texture));
		//glUniformMatrix3fv(union_shader->getUniformId("transformMatrix"), 1, false, glm::value_ptr(horse_transform));
		//tex_test->bindTexture();
		//horse_picture_buffer->drawIndexData(DrawDataMode::Triangles, 6, DrawDataType::UnsignedInt, nullptr);


		Sleep(50);
		glfwSwapBuffers(frame->getWindow());
	}
	delete frame;
	delete resource_manager;
	//delete backround_shader;
	//delete union_shader;
	delete bricks;
	delete tex_test;

	delete horse_picture_buffer;
	delete background_buffer;
	system("pause");



#endif
	Frame* frame = new Frame();
	glfwSetKeyCallback(frame->getWindow(), key_callback);
	ResourceManager* resource_manager = new ResourceManager();

	std::vector<GLfloat> vertex = {		-140.f,		 -192.5f,			0.f, 0.f,
															-140.f,		  192.5f,			0.f, 1.f,
															 140.f,		-192.5f,			1.f, 0.f,
															 140.f,		  192.5f,			1.f, 1.f
	};
	// 274.25 x 375
	std::vector <GLfloat> wall_vertex = {
				-137.25f, -187.5f,		0.f,	0.f,
				-137.25f,	 187.5f,		0.f,	1.f,
				 137.25f,	-187.5f,	1.f,	0.f,
				 137.25f,	 187.5f,		1.f,	1.f
	};

	std::vector<GLuint> index = {	0,1,2,
													1,2,3
	};

	ArrayBufferHandler wall_buffer(wall_vertex.size() * sizeof(GLfloat),wall_vertex, ArrayBufferDataType::StaticData);

	wall_buffer.addElementBuffer();
	wall_buffer.setElementBufferData(index.size() * sizeof(GLint), index, ArrayBufferDataType::StaticData);

	wall_buffer.setAttributes(0, 2, GL_FLOAT, false, 4 * sizeof(GLfloat), (GLvoid*)nullptr);
	wall_buffer.setAttributes(1, 2, GL_FLOAT, false, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));

	ArrayBufferHandler* handler = new ArrayBufferHandler(vertex.size() * sizeof(GLfloat), vertex,
								ArrayBufferDataType::StaticData);
	handler->addElementBuffer();
	handler->setElementBufferData(index.size() * sizeof(GLint), index, ArrayBufferDataType::StaticData);

	handler->setAttributes(0, 2, GL_FLOAT, false, 4 * sizeof(GLfloat), (GLvoid*)nullptr);
	handler->setAttributes(1, 2, GL_FLOAT, false, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));

	ShaderProgram* program = resource_manager->load_resource<ShaderProgram>("../../resources/Shaders/Simple/shader_array.glsl")
		->getSourcePtr();

	program->setUniformId("layer");
	program->setUniformId("inverse_x");
	program->setUniformId("normalize_vertexMatrix");
	program->setUniformId("transformMatrix");
	 
	ShaderProgram wall_shader = *resource_manager->load_resource<ShaderProgram>("../../resources/Shaders/Simple/texture_n_vertex_nn.glsl")->getSourcePtr();
	wall_shader.setUniformId("normalize_vertexMatrix");
	wall_shader.setUniformId("transform");

	//matrix3 normalize_viewport = matrix::vertexNormalizeMatrix3x3(1920, 1080);

	matrix3 normalize_viewport;
	normalize_viewport = glm::scale(normalize_viewport, vector2(2.f/1920.f, 2.f/1080.f));
	
	matrix3 transform_wall_1 = matrix3();
	transform_wall_1 = glm::translate(transform_wall_1, vector2(1800, 187.5));	
	
	matrix3 transform_wall_2 = matrix3();
	transform_wall_2 = glm::translate(transform_wall_2, vector2(100, 187.5));

	Texture2D wall_texture = *resource_manager->load_resource<Texture2D>("../../resources/Textures/brick_wall.jpg","wall", Texture::TexturePixelData::Load_RGB)->getSourcePtr();

	Sprite* sprite = resource_manager->load_resource<Sprite>("../../resources/Textures/Animation_1.png",
		 "animation_1",  uinfo_vector4(5,2,10, static_cast<unsigned int>(Texture::TexturePixelData::Load_RGBA)))->getSourcePtr();
	sprite->setMinFiltering(Texture::FilteringType::Linear);
	sprite->setMagFiltering(Texture::FilteringType::Linear);
	sprite->setWrapMode(Texture::WrapMode::ClampToEdge);

	SpriteAnimation* animation = new SpriteAnimation(sprite);
	SpriteAnimator* animator = new SpriteAnimator(animation, 1.f/20.f);


	AARectangle player = AARectangle(pos, vector2(140, 385.f/2.f));
	AARectangle wall_1 = AARectangle(vector2(1800, 187.5), vector2(137.25, 187.5));
	AARectangle wall_2 = AARectangle(vector2(100, 187.5), vector2(137.25, 187.5));

	animator->start(glfwGetTime());
	double max_cycle = 0;
	float sleepTime = 1000.f / 30.f;
	while (!glfwWindowShouldClose(frame->getWindow()))
	{
		float begin = glfwGetTime();
		glfwPollEvents();

		{
			if (keys[GLFW_KEY_RIGHT])
			{
				if (inverse_x)
					player_direction =  -player_direction;
				inverse_x = false;
				pos += player_speed * player_direction;
			}
			if (keys[GLFW_KEY_LEFT])
			{
				if(!inverse_x)
					player_direction = -player_direction;
				inverse_x = true;
				pos += player_speed * player_direction;
			}
		}
		player.setPosition(pos);
		matrix3 view;


		if(intersection::intersection(player, wall_1))
		{
			vector2 overlaps = intersection::getOverlaps(player, wall_1);
			pos += -player_direction * overlaps.x;
			player.setPosition(pos);
		}		
		
		if(intersection::intersection(player, wall_2))
		{
			vector2 overlaps = intersection::getOverlaps(player, wall_2);
			pos += -player_direction * overlaps.x;
			player.setPosition(pos);
		}


		view = glm::scale(view, vector2(1));
		view = glm::translate(view, -pos);

		matrix3 proj_view = normalize_viewport * view;
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		matrix3 transform = matrix3();
		transform = glm::translate(transform, pos);
		animator->animate(glfwGetTime());
		animation->bindSource();
		program->useProgram();
		glUniform1i(program->getUniformId("layer"), animation->getCurrentFrameNumber());
		glUniform1i(program->getUniformId("inverse_x"), inverse_x);
		glUniformMatrix3fv(program->getUniformId("normalize_vertexMatrix"), 1, false,glm::value_ptr(proj_view));
		glUniformMatrix3fv(program->getUniformId("transformMatrix"), 1, false,glm::value_ptr(transform));
		handler->drawIndexData(DrawDataMode::Triangles, 6, DrawDataType::UnsignedInt, nullptr);
		animator->animate(glfwGetTime());


		wall_shader.useProgram();
		glUniformMatrix3fv(wall_shader.getUniformId("normalize_vertexMatrix"), 1, false, glm::value_ptr(proj_view));
		glUniformMatrix3fv(wall_shader.getUniformId("transform"), 1, false, glm::value_ptr(transform_wall_1));
		wall_texture.bindTexture();
		wall_buffer.drawIndexData(DrawDataMode::Triangles, 6, DrawDataType::UnsignedInt, nullptr);

		glUniformMatrix3fv(wall_shader.getUniformId("transform"), 1, false, glm::value_ptr(transform_wall_2));
		wall_buffer.drawIndexData(DrawDataMode::Triangles, 6, DrawDataType::UnsignedInt, nullptr);

		glfwSwapBuffers(frame->getWindow());


		float end = glfwGetTime() - begin;
		if (end > max_cycle) max_cycle = end;
		Sleep(sleepTime);
		float realFPS = 1000.f / (sleepTime + end);
		std::string info = "Cycle time - ";
		info.append(std::to_string(end));
		info.append(" Max cycle time -").append(std::to_string(max_cycle));
		info.append(" Real FPS - ");
		info.append(std::to_string(realFPS));
	
		frame->setTitle(info.c_str());
	}

	delete frame;
	delete resource_manager;
	system("pause");
	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}
}