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

// *****************************************************************************
// Cubo con centro en el origen y lado unidad por defecto
// (tiene 9 vertices y 6 caras)

class ObjRevolucion : public Malla3D
{
   public:
	ObjRevolucion();
	ObjRevolucion(const std::string  & archivo, int num_instancias,
                  bool Tsup=true, bool Tinf=true, Eje eje=ejeY) ;
	ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias,
                  bool Tsup=true, bool Tinf=true, Eje eje=ejeY) ;
	void cambiaTapas();		//Cambia estado tapas mostrar/noMostrar
	void generaColor(Tupla3f color=Tupla3f(0.5,0.5,0.5));

	//void muestraTapas(bool sup, bool inf);

   //void draw(bool inmediato=true, tipoDibujado dibujado=LINEAS,
   	         //bool tapa_sup=true, bool tapa_inf=true);

private:
    void crearMalla(bool Tsup=true, bool Tinf=true);
	Tupla3f Rota(Tupla3f base, float alpha);
	void DetectaTapasX();
	void DetectaTapasY();
	void DetectaTapasZ();
	void CreaTapaSup();
	void CreaTapaInf();
	void EliminaTapas();


	int numf;		//Número de faces
	int numfTapas;	//Número de faces de tapas
	int num_instancias;
	std::vector<Tupla3f> vPerfil;	//Vértices del perfil

	//std::vector<Tupla3i> CarasTapaSup;
    //std::vector<Tupla3i> CarasTapaInf;

    bool hayTapaSup=true;
    bool hayTapaInf=true;

   
    Eje ejeRotacion;
} ;




#endif
