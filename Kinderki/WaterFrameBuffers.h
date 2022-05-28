#pragma once

#include "GameManager.h"

class WaterFrameBuffers {
private:
	unsigned int reflectionFrameBuffer;
	unsigned int reflectionTexture;
	unsigned int reflectionRBO;

	unsigned int waterRefractionFbo;
	unsigned int refractiontexture;
	unsigned int refractionRBO;
public:
	const int REFLECTION_WIDTH = 320;
	const int REFLECTION_HEIGHT = 180;

	const int REFRACTION_WIDTH = 1280;
	const int REFRACTION_HEIGHT = 720;
	WaterFrameBuffers()
	{
		initialiseRefractionBuffer();
		initialiseReflectionBuffer();
	}

	unsigned int getRefractionTexture()
	{
		return refractiontexture;
	}

	unsigned int getReflectionTexture()
	{
		return reflectionTexture;
	}

	void bindRefraction() {//call before rendering to this FBO
		glBindFramebuffer(GL_FRAMEBUFFER, waterRefractionFbo);
	}

	void bindReflection() {//call before rendering to this FBO
		glBindFramebuffer(GL_FRAMEBUFFER, reflectionFrameBuffer);
	}

	void unbindBuffer() {//call to switch to default frame buffer
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void initialiseRefractionBuffer()
	{
		glGenFramebuffers(1, &waterRefractionFbo);
		glBindFramebuffer(GL_FRAMEBUFFER, waterRefractionFbo);

		glGenTextures(1, &refractiontexture);
		glBindTexture(GL_TEXTURE_2D, refractiontexture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, REFRACTION_WIDTH, REFRACTION_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, refractiontexture, 0);

		glGenRenderbuffers(1, &refractionRBO);
		glBindRenderbuffer(GL_RENDERBUFFER, refractionRBO);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, REFRACTION_WIDTH, REFRACTION_HEIGHT); // use a single renderbuffer object for both a depth AND stencil buffer.
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, refractionRBO); // now actually attach it
		// now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void initialiseReflectionBuffer()
	{
		glGenFramebuffers(1, &reflectionFrameBuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, reflectionFrameBuffer);

		glGenTextures(1, &reflectionTexture);
		glBindTexture(GL_TEXTURE_2D, reflectionTexture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, REFLECTION_WIDTH, REFLECTION_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, reflectionTexture, 0);

		glGenRenderbuffers(1, &reflectionRBO);
		glBindRenderbuffer(GL_RENDERBUFFER, reflectionRBO);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, REFLECTION_WIDTH, REFLECTION_HEIGHT); // use a single renderbuffer object for both a depth AND stencil buffer.
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, reflectionRBO); // now actually attach it
		// now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}


	//void bindReflectionFrameBuffer() {//call before rendering to this FBO
	//	bindFrameBuffer(reflectionFrameBuffer, REFLECTION_WIDTH, REFLECTION_HEIGHT);
	//}

	//int getRefractionDepthTexture() {//get the resulting depth texture
	//	return refractionDepthTexture;
	//}

	//void initialiseReflectionFrameBuffer() {
	//	reflectionFrameBuffer = createFrameBuffer();
	//	reflectionTexture = createTextureAttachment(REFLECTION_WIDTH, REFLECTION_HEIGHT);
	//	reflectionDepthBuffer = createDepthBufferAttachment(REFLECTION_WIDTH, REFLECTION_HEIGHT);
	//	unbindCurrentFrameBuffer();
	//}

	//void initialiseRefractionFrameBuffer() {
	//	refractionFrameBuffer = createFrameBuffer();
	//	refractionTexture = createTextureAttachment(REFRACTION_WIDTH, REFRACTION_HEIGHT);
	//	refractionDepthTexture = createDepthTextureAttachment(REFRACTION_WIDTH, REFRACTION_HEIGHT);
	//	unbindCurrentFrameBuffer();
	//}

	//void bindFrameBuffer(int frameBuffer, int width, int height) {
	//	glBindTexture(GL_TEXTURE_2D, 0);//To make sure the texture isn't bound
	//	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
	//	glViewport(0, 0, width, height);
	//}

	//int createFrameBuffer() {
	//	int frameBuffer;
	//	glGenFramebuffers(1, &frameBuffer);
	//	//generate name for frame buffer
	//	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
	//	//create the framebuffer
	//	glDrawBuffer(GL_COLOR_ATTACHMENT0);
	//	//indicate that we will always render to color attachment 0
	//	return frameBuffer;
	//}

	//int createTextureAttachment(int width, int height) {
	//	int texture = glGenTextures();
	//	glBindTexture(GL_TEXTURE_2D, texture);
	//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height,
	//		0, GL_RGB, GL_UNSIGNED_BYTE, (ByteBuffer)null);
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
	//		texture, 0);
	//	return texture;
	//}

	//int createDepthTextureAttachment(int width, int height) {
	//	int texture = glGenTextures();
	//	glBindTexture(GL_TEXTURE_2D, texture);
	//	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height,
	//		0, GL_DEPTH_COMPONENT, GL_FLOAT, (ByteBuffer)null);
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
	//		texture, 0);
	//	return texture;
	//}

	//int createDepthBufferAttachment(int width, int height) {
	//	int depthBuffer = glGenRenderbuffers();
	//	glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
	//	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width,
	//		height);
	//	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
	//		GL_RENDERBUFFER, depthBuffer);
	//	return depthBuffer;
	//}
};