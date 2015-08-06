#include "simple_texture.h"

SimpleTexture::SimpleTexture() {}
SimpleTexture::~SimpleTexture() {}

SimpleTexture::SimpleTexture(GLuint texId, const SimpleImage* image, ImageOptions options) {
	loadImageData(texId, image, options);
}

SimpleTexture::SimpleTexture(GLuint texId, const float* pixels, int width, int height, ImageOptions options) {
	loadImageData(texId, pixels, width, height, options);
}

void SimpleTexture::loadImageData(GLuint texId, const SimpleImage* image, ImageOptions options) {
	loadImageData(texId, (float*)image->data(), image->width(), image->height(), options);
}

void SimpleTexture::loadImageData(GLuint texId, const float* pixels, int width, int height, ImageOptions options) {
	mWidth = width;
	mHeight = height;
	mTexId = texId;

    glBindTexture(GL_TEXTURE_2D, mTexId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    if (options == kGenerateMipmaps) {
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, mWidth, mHeight, GL_RGB, GL_UNSIGNED_BYTE, pixels);
    } else {
	    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mWidth, mHeight, 0, GL_RGB, GL_FLOAT, pixels);
	}
}

void SimpleTexture::bind() {
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, mTexId);
}

void SimpleTexture::unBind() {
	glDisable(GL_TEXTURE_2D);
}

void SimpleTexture::initialize() {}

// TODO
void SimpleTexture::setFilter(GLint magFilter, GLint minFilter) {}
void SimpleTexture::setWrap(GLint wrapS, GLint wrapT) {}