// SDL Libraries
#include <SDL.h>

// BakedEngine Libraries
#include "BakedEngine/BakedEngine.h"
#include "BakedEngine/SdlError.h"
#include "BakedEngine/Glyph.h"
#include "BakedEngine/GLTexture.h"
#include "BakedEngine/ResourceManager.h"
#include "BakedEngine/SpriteBatch.h"

// Game Libraries
#include "Game/MainGame.h"

MainGame::MainGame()
{
	if (!BakedEngine::init())
	{
		BakedEngine::CustomSdlError::DisplayError(SDL_MessageBoxFlags::SDL_MESSAGEBOX_ERROR, "Main Game Init", "Could not initialize SDL", nullptr);
	}

	if (!gameWindow.create("Test Window", 480, 480, 0))
	{
		BakedEngine::CustomSdlError::DisplayError(SDL_MessageBoxFlags::SDL_MESSAGEBOX_ERROR, "Main Game Init", "Could not initialize gameWindow", nullptr);
	}


	std::cerr << "Initializing Shaders" << std::endl;
	m_colorShaderProgram.compileShaders("resources/Shaders/colorShader.vert", "resources/Shaders/colorShader.frag");
	m_colorShaderProgram.addAttribute("vertexPosition");
	m_colorShaderProgram.addAttribute("vertexColor");
	m_colorShaderProgram.addAttribute("vertexUV");
	m_colorShaderProgram.linkShaders();

	isRunning = true;
}

void MainGame::run()
{
	while (isRunning)
	{
		// Set the base depth to 1.0
		glClearDepth(1.0);

		// Clear the color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Glsl
		m_colorShaderProgram.use();

		GLint textureLocation = m_colorShaderProgram.getUniformLocation("mySampler");
		if (textureLocation == -1)
		{
			BakedEngine::CustomSdlError::DisplayError(SDL_MessageBoxFlags::SDL_MESSAGEBOX_ERROR, "Main Game Run", "Could not find Texture location", nullptr);
		}
		glUniform1i(textureLocation, 0);

		glm::vec4 pos(0.0f, 0.0f, 50.0f, 50.0f);
		glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
		BakedEngine::GLTexture texture = BakedEngine::ResourceManager::getTexture("resources/Characters/BakedProductionGuy.png");
		BakedEngine::ColorRGBA8 color;
		color.red = 255;
		color.green = 0;
		color.blue = 0;
		color.alpha = 255;

		BakedEngine::SpriteBatch spriteBatch;
		spriteBatch.draw(pos, uv, texture.id, 0.0f, color);
		spriteBatch.render();

		gameWindow.swapBuffer();

		// Glsl
		m_colorShaderProgram.unuse();

		m_inputManager.update();


		SDL_Event evnt;
		while (SDL_PollEvent(&evnt))
		{
			switch (evnt.type)
			{
				case SDL_QUIT:
					isRunning = false;
					break;
				case SDL_KEYDOWN:
					m_inputManager.pressKey(evnt.key.keysym.sym);
					break;
				case SDL_KEYUP:
					m_inputManager.releaseKey(evnt.key.keysym.sym);
					break;
				case SDL_MOUSEBUTTONDOWN:
					m_inputManager.pressKey(evnt.button.button);
					break;
				case SDL_MOUSEBUTTONUP:
					m_inputManager.releaseKey(evnt.button.button);
					break;
				case SDL_MOUSEMOTION:
					m_inputManager.setMouseCoords((float)evnt.motion.x, (float)480 - (float)evnt.motion.y);
					break;
			}
		}
	}

	// SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Test" , "This is a test Window using SDL2", nullptr);
}

void MainGame::stop()
{
	isRunning = false;
}
