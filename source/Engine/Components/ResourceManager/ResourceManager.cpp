#include "ResourceManager.h"
#include <Engine/Components/Texture/Texture2D.h>
#include <Engine/Components/Texture/Sprite.h>
#include <Engine/Components/Shaders/ShaderProgram.h>

#include "TextureLoader.h"
#include "ShaderProgramLoader.h"
#include "SpriteLoader.h"





ResourceManager::ResourceManager()
{
	register_resource_loader<Texture2D>(new TextureLoader());
	register_resource_loader<ShaderProgram>(new ShaderProgramLoader());
	register_resource_loader<Sprite>(new SpriteLoader());
}

ResourceManager::~ResourceManager()
{
	for (auto&[type, loader] : loader_list)
		delete loader;
	for (auto&[id, resource] : resources_list)
		delete resource;
}