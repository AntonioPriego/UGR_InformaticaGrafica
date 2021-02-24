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
	ObjRevolucion(const std::string & archivo, int num_instancias, bool tapa_sup=true, bool tapa_inf=true, Eje eje=ejeY) ;
	ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias, bool tapa_sup=true, bool tapa_inf=true, Eje eje=ejeY) ;
	void cambiaTapas(bool tapa_sup=true, bool tapa_inf=true); // Modifica el vector de caras


   //void draw(bool inmediato=true, tipoDibujado dibujado=LINEAS,
   	         //bool tapa_sup=true, bool tapa_inf=true);

private:
    //void crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias);
		// yo he implementado perfil_original como la primera instancia de vertices de la propia malla
    void crearMalla(bool tapa_sup, bool tapa_inf);
	Tupla3f Rota(Tupla3f base, float alpha);
	void CreaTapaSup();
	void CreaTapaInf();


	int numf;	//Número de faces
	int numv;	//Número de vértices
	int num_instancias;
    std::vector<Tupla3f> vPerfil;	//Vértices del perfil
   
    // Variables Tapas
    std::vector<Tupla3i> fTapaSup; //Caras de Tapa superior
    std::vector<Tupla3i> fTapaInf; //Caras de Tapa inferior
    Tupla3f vTapaSup;	//Vértice de la tapa superior
    Tupla3f vTapaInf;	//Vértice de la tapa inferior

    Eje ejeRotacion;
} ;




#endif
