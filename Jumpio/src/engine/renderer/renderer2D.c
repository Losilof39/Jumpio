#include "renderer2D.h"
#include "engine/log.h"


typedef struct RenderState
{
	GLuint VAO;
	GLuint screenVAO;
	Shader flatColorShader;
	Shader spriteShader;
	Shader fbShader;
	mat4 camOrtho;
	SDL_Window* pWindow;
	SDL_GLContext glContext;
}RenderState;

// 2D draw command
typedef struct twodcommand
{
	unsigned int glTexture;
	vec3 position;
	vec2 size;
	float light;
	struct twodcommand* next;
}twodcommand;

static RenderState RState;
static twodcommand* head_command = NULL;

void GLAPIENTRY
MessageCallback(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam)
{
	/*fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
		(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
		type, severity, message);*/
	log_error(message);
}

void Renderer2D_StartOpenGL()
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);

	RState.glContext = SDL_GL_CreateContext(RState.pWindow);

	if (RState.glContext == NULL)
	{
		log_error("Failed to create an OpenGL context!\n");
	}

	SDL_GL_MakeCurrent(RState.pWindow, RState.glContext);

	if (gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress) < 0)
	{
		log_error("Failed to load OpenGL library!\n");
	}

	log_debug("OpenGL 4.6 context created successfully");

	// enable OpenGL 4.6 debug features
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(MessageCallback, 0);

	log_debug("Debug Output feature is enabled");
}

void Renderer2D_Init(SDL_Window* window)
{
	RState.pWindow = window;

	Renderer2D_StartOpenGL();

	// configure VAO/VBO
	unsigned int VBO;
	float vertices[] = {
		// pos      // tex
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
	};

	glGenVertexArrays(1, &RState.VAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(RState.VAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	// REMEMBER TO REIMPLEMENT THIS IF YOU WANNA SEE SMTH!!

	RState.flatColorShader = Shader_Create("flatcolor", "shaders/flatcolor.vs", "shaders/flatcolor.ps");
	//s_Data.spriteShader = Shader_Create("sprite", "shader_files/sprite.vs", "shader_files/sprite.ps");

	glm_ortho(0.0f,
		(float)WINDOW_WIDTH,
		(float)WINDOW_HEIGHT,
		0.0f,
		-1.0f,
		1.0f,
		RState.camOrtho);

	/*Shader_Use(s_Data.spriteShader);
	Shader_SetMat4(renderState.spriteShader, "u_Ortho", renderState.camOrtho);
	Shader_SetInt(renderState.spriteShader, "image", 0);
	Shader_Unbind();

	Shader_Use(s_Data.flatColorShader);
	Shader_SetMat4(renderState.flatColorShader, "u_Ortho", renderState.camOrtho);
	Shader_Unbind();*/

	Shader_Use(RState.flatColorShader);
	Shader_SetMat4(RState.flatColorShader, "u_Ortho", RState.camOrtho);
	Shader_Unbind();

}

void Renderer2D_Cleanup()
{
}

void R2D_StartRendition(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void R2D_StopRendition(void)
{
	SDL_GL_SwapWindow(RState.pWindow);
}

void R2D_DrawColoredQuad(vec3 position, vec2 size, vec3 color)
{
	mat4 model, translate, scale;

	glm_mat4_identity(model);
	glm_mat4_identity(translate);
	glm_mat4_identity(scale);

	glm_scale(scale, size);
	glm_translate(translate, position);
	glm_mat4_mul(translate, scale, model);

	Shader_Use(RState.flatColorShader);
	Shader_SetVec3(RState.flatColorShader, "u_Color", color);
	Shader_SetMat4(RState.flatColorShader, "u_Model", model);

	glBindVertexArray(RState.VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);


	Shader_Unbind();
}

//void R2D_DrawSprite(vec3* position, vec2 size, GLTexData* tex)
//{
//	twodcommand* newNode = (twodcommand*)malloc(sizeof(twodcommand));
//
//	if (head_command == NULL) {
//		// If the list is empty, set the new node as the head
//		head_command = newNode;
//	}
//	else {
//		// Traverse to the end of the list and append the new node
//		twodcommand* current = head_command;
//		while (current->next != NULL) {
//			current = current->next;
//		}
//		current->next = newNode;
//	}
//
//	glm_vec3_copy(position, &newNode->position);
//	glm_vec3_copy(size, &newNode->size);
//
//	newNode->glTexture = tex->TexName;
//	newNode->light = -1;
//
//	newNode->next = NULL;
//}
//
//void R2D_DrawSpriteFromName(vec3* position, vec2 size, const char* name)
//{
//	twodcommand* newNode = (twodcommand*)malloc(sizeof(twodcommand));
//	GLTexData	tex;
//
//	GL_MakeSpriteTexture(W_CacheLumpName(name, PU_CACHE), &tex, false);
//
//	if (head_command == NULL) {
//		// If the list is empty, set the new node as the head
//		head_command = newNode;
//	}
//	else {
//		// Traverse to the end of the list and append the new node
//		twodcommand* current = head_command;
//		while (current->next != NULL) {
//			current = current->next;
//		}
//		current->next = newNode;
//	}
//
//	glm_vec3_copy(position, &newNode->position);
//	glm_vec3_copy(size, &newNode->size);
//
//	newNode->glTexture = tex.TexName;
//	newNode->light = -1;
//
//	newNode->next = NULL;
//}
//
//void R2D_DrawColoredQuad(vec3* position, vec3* size, vec3* color)
//{
//	/*mat4 model, translate, scale;
//
//	glm_mat4_identity(model);
//	glm_mat4_identity(translate);
//	glm_mat4_identity(scale);
//
//	glm_scale(scale, size);
//	glm_translate(translate, position);
//	glm_mat4_mul(translate, scale, model);
//
//	Shader_Use(s_Data.flatColorShader);
//	Shader_SetVec3(s_Data.flatColorShader, "u_Color", color);
//	Shader_SetMat4(s_Data.flatColorShader, "u_Model", model);
//
//	glBindVertexArray(s_Data.VAO);
//	glDrawArrays(GL_TRIANGLES, 0, 6);
//	glBindVertexArray(0);
//
//
//	Shader_Unbind();*/
//}
//
//void R2D_DrawLightSprite(vec3* position, vec2 size, GLTexData* tex, float light)
//{
//	twodcommand* newNode = (twodcommand*)malloc(sizeof(twodcommand));
//
//	if (head_command == NULL) {
//		// If the list is empty, set the new node as the head
//		head_command = newNode;
//	}
//	else {
//		// Traverse to the end of the list and append the new node
//		twodcommand* current = head_command;
//		while (current->next != NULL) {
//			current = current->next;
//		}
//		current->next = newNode;
//	}
//
//	glm_vec3_copy(position, &newNode->position);
//	glm_vec3_copy(size, &newNode->size);
//
//	newNode->glTexture = tex->TexName;
//	newNode->light = light;
//
//	newNode->next = NULL;
//}
//
//void R2D_StartRendition(void)
//{
//}
//
//void R2D_StopRendition(void)
//{
//	glDisable(GL_DEPTH_TEST);
//
//	twodcommand* cur, * nextNode;
//	mat4 model;
//
//	cur = head_command;
//
//	Shader_Use(s_Data.spriteShader);
//
//	while (cur != NULL)
//	{
//		glm_mat4_identity(model);
//
//		glm_translate(model, cur->position);
//		glm_scale(model, cur->size);
//
//		Shader_SetMat4(s_Data.spriteShader, "u_Model", model);
//		Shader_SetFloat(s_Data.spriteShader, "light", cur->light);
//
//		glActiveTexture(GL_TEXTURE0);
//		glBindTexture(GL_TEXTURE_2D, cur->glTexture);
//
//		glBindVertexArray(s_Data.VAO);
//		glDrawArrays(GL_TRIANGLES, 0, 6);
//
//		glBindVertexArray(0);
//		glBindTexture(GL_TEXTURE_2D, 0);
//
//		cur = cur->next;
//	}
//
//	Shader_Unbind();
//
//	cur = head_command;
//
//	// Free each node in the list
//	while (cur != NULL) {
//		nextNode = cur->next;
//		free(cur);
//		cur = nextNode;
//	}
//
//	// Set the head to NULL to indicate an empty list
//	head_command = NULL;
//}