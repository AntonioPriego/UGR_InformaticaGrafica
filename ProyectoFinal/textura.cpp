#include "textura.h"

// *****************************************************************************
//
// Clase Textura
//
// *****************************************************************************


// -----------------------------------------------------------------------------
// Constructor de textura
Textura::Textura()
{

}

// -----------------------------------------------------------------------------
// Set de textura
void Textura::set(const std::string &archivo)
{
	imagen_tex = new jpg::Imagen(archivo);

	glGenTextures(1, &textura_id);
	glBindTexture(GL_TEXTURE_2D, textura_id);
}

// -----------------------------------------------------------------------------
// Aplica la textura
void Textura::activar()
{
    if (imagen_tex != NULL) {
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, imagen_tex->tamX(), imagen_tex->tamY(), GL_RGB,GL_UNSIGNED_BYTE, imagen_tex->leerPixels());
		//O bien: 
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imagen_tex->tamX(), imagen_tex->tamY(), 0, GL_RGB, GL_UNSIGNED_BYTE, imagen_tex->leerPixels());
	}
}

// -----------------------------------------------------------------------------
// Aplica la textura
void Textura::desactivaTextura()
{
    glDisable(GL_TEXTURE_2D);
}

unsigned char* Textura::getColores()
{
	return imagen_tex->leerPixels();
}

bool Textura::establecida()
{
	return imagen_tex!=NULL;
}

unsigned long Textura::getTamX()
{
	return imagen_tex->tamX();
}

unsigned long Textura::getTamY()
{
	return imagen_tex->tamY();
}
