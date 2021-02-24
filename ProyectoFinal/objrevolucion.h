// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Cubo.h

//
// #############################################################################

#ifndef OBJREVOLUCION_H_INCLUDED
#define OBJREVOLUCION_H_INCLUDED

#include "aux.h"
#include "malla.h"

typedef enum {ejeX, ejeY, ejeZ} Eje;


// *****************************************************************************
//
// clases derivadas de Malla3D (definen constructores específicos)
//
// *****************************************************************************

class ObjRevolucion : public Malla3D
{
 public:
	ObjRevolucion();
	ObjRevolucion(const std::string  & archivo, int num_instancias,
                  bool Tsup=true, bool Tinf=true, Eje eje=ejeY) ;
	ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias,
                  bool Tsup=true, bool Tinf=true, Eje eje=ejeY) ;
	void cambiaTapas();		//Cambia estado tapas mostrar/noMostrar


 private:
    void crearMalla(bool Tsup=true, bool Tinf=true);
	Tupla3f Rota(Tupla3f base, float alpha);
	void DetectaTapasX();
	void DetectaTapasY();
	void DetectaTapasZ();
	void DetectaOrden();
	void OrientarOrden();
	void CreaTapaSup();
	void CreaTapaInf();
	void EliminaTapas();


	int numf;		 //Número de faces
	int numfsinTapas;//Número de faces sin contar las tapas
	int num_instancias;
	std::vector<Tupla3f> vPerfil;	//Vértices del perfil

    bool hayTapaSup=true;
    bool hayTapaInf=true;

    Eje ejeRotacion;
} ;




#endif
