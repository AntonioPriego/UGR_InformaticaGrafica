// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Cubo.h

//
// #############################################################################

#ifndef TEXTURA_H
#define TEXTURA_H

#include "aux.h"
#include "jpg_imagen.h"
#include "jpg_readwrite.h"


// *****************************************************************************
//
// clase textura
//
// *****************************************************************************

class Textura {
 private:
	GLuint textura_id;
	std::vector<unsigned char> data;
	int width   ;
	int height  ;
	float brillo;
	jpg::Imagen *imagen_tex=nullptr;

 public:
	Textura();
	void set(const std::string &archivo);
	void activar();
	void desactivaTextura();
	unsigned char* getColores();
	bool establecida();
	unsigned long getTamX();
	unsigned long getTamY();
};

#endif