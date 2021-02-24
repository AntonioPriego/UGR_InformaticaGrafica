#include "material.h"

// *****************************************************************************
//
// Clase Material
//
// *****************************************************************************

// -----------------------------------------------------------------------------
// 	
Material::Material (Tupla4f _emision, Tupla4f _difuso, Tupla4f _especular, Tupla4f _ambiente, float _brillo )
{
	emision   = _emision;
	difuso    = _difuso;
	especular = _especular;
	ambiente  = _ambiente;
	brillo    = _brillo;
}

void Material::aplicar()
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION , emision  );
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE  , difuso   );
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR , especular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT  , ambiente );
	glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, brillo   );
        
	glShadeModel(GL_SMOOTH);
}

Tupla4f Material::getEmision  ()
{
	return emision;
}

Tupla4f Material::getDifuso   ()
{
	return difuso;
}

Tupla4f Material::getEspecular()
{
	return especular;
}

Tupla4f Material::getAmbiente ()
{
	return ambiente;
}

float   Material::getBrillo   ()
{
	return brillo;
}


void Material::setEmision  (Tupla4f _emision)  
{
	emision   = _emision;
}

void Material::setDifuso   (Tupla4f _difuso)   
{
	difuso    = _difuso;
}

void Material::setEspecular(Tupla4f _especular)
{
	especular = _especular;

}

void Material::setAmbiente (Tupla4f _ambiente) 
{
	ambiente  = _ambiente;
}

void Material::setBrillo   (float   _brillo)   
{
	brillo    = _brillo;
}


void Material::set (Tupla4f _emision, Tupla4f _difuso,
          Tupla4f _especular, Tupla4f _ambiente,float _brillo)
{
	emision   = _emision;
	difuso    = _difuso;
	especular = _especular;
	ambiente  = _ambiente;
	brillo    = _brillo;
}

void Material::set (Material _m)
{
	emision   = _m.getEmision()  ;
	difuso    = _m.getDifuso()   ;
	especular = _m.getEspecular();
	ambiente  = _m.getAmbiente() ;
	brillo    = _m.getBrillo()   ;
}