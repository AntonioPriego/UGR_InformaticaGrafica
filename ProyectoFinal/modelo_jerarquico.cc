#include "aux.h"
#include "modelo_jerarquico.h"

ModJerarquico::ModJerarquico(int tamCubo, int muestreoObjRev)
{
	base           = new Base(tamCubo, muestreoObjRev);
	fondo          = new Fondo         (tamCubo);
	portafiltros   = new Portafiltros  (muestreoObjRev);
	parteFuncional = new ParteFuncional(tamCubo, muestreoObjRev);
}

//----------------------------------------------------------------------------
// Dibuja el modelo jerárquico
void ModJerarquico::draw(bool dibujadoInmediato, tipoDibujado dibujado, tipoIluminacion iluminacion, bool primerPlano)
{
	glPushMatrix();
		if (primerPlano) glTranslatef(0,20,10);
		else {           glTranslatef(-100,20,-70);
                         glRotatef(90,0,1,0);
		}
		glPushMatrix();
		
			base->draw          (dibujadoInmediato, dibujado, iluminacion);
			fondo->draw         (dibujadoInmediato, dibujado, iluminacion);
			portafiltros->draw  (dibujadoInmediato, dibujado, iluminacion);
			parteFuncional->draw(dibujadoInmediato, dibujado, iluminacion);

		glPopMatrix();
	glPopMatrix();
}

//----------------------------------------------------------------------------
// Constructor de Base
Base::Base(int tamCubo, int muestreoObjRev)
{
	taza         = new ObjPLY   ("taza")   ;
	cubo         = new Cubo     (tamCubo)  ;
	cilindro_mad = new ObjRevolucion("cilindro", muestreoObjRev);
	cilindro_met = new ObjRevolucion("cilindro", muestreoObjRev);



	taza        ->setColor(Tupla3f(0.5,0.5,0.5));
	cubo        ->setColor(Tupla3f(0.5,0.5,0.5));
	cilindro_mad->setColor(Tupla3f(0.5,0.5,0.5));
	cilindro_met->setColor(Tupla3f(0.5,0.5,0.5));

	taza        ->setMaterial(*mat_porcelana);
	cubo        ->setMaterial(*mat_metal)    ;
	cilindro_mad->setMaterial(*mat_madera)   ;
	cilindro_met->setMaterial(*mat_metal)    ;

	taza        ->setTextura("porcelana")  ;
	cubo        ->setTextura("metal")      ;
	cilindro_mad->setTextura("text-madera");
	cilindro_met->setTextura("text-madera");
}

//----------------------------------------------------------------------------
// Método de dibujado de Base
void Base::draw(bool dibujadoInmediato, tipoDibujado dibujado, tipoIluminacion iluminacion)
{
	glPushMatrix();

		glPushMatrix();
			glScalef(1,0.2,0.4);
			cubo->draw(dibujadoInmediato, dibujado, iluminacion);
		glPopMatrix();

		glPushMatrix();
//1
			glPushMatrix();
				glTranslatef(-20,-8.5,8);
				glScalef(12,3.5,12);
				cilindro_met->draw(dibujadoInmediato, dibujado, iluminacion);
			glPopMatrix();
//2
			glPushMatrix();
				glTranslatef(20,-8.5,8);
				glScalef(12,3.5,12);
				cilindro_met->draw(dibujadoInmediato, dibujado, iluminacion);
			glPopMatrix();
//3
			glPushMatrix();
				glTranslatef(-20,-8.5,-8);
				glScalef(12,3.5,12);
				cilindro_met->draw(dibujadoInmediato, dibujado, iluminacion);
			glPopMatrix();
//4
			glPushMatrix();
				glTranslatef(20,-8.5,-8);
				glScalef(12,3.5,12);
				cilindro_met->draw(dibujadoInmediato, dibujado, iluminacion);
			glPopMatrix();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(17,7,0);
			glScalef(70,60,70);
			glRotatef(259*anim_rotacion,0,1,0);
			taza->draw(dibujadoInmediato, dibujado, iluminacion);
		glPopMatrix();
	glPopMatrix();
}

//----------------------------------------------------------------------------
// Constructor de Fondo
Fondo::Fondo(int tamCubo)
{
	cubo = new Cubo(tamCubo);


	cubo->setColor(Tupla3f(0.5,0.5,0.5));
	cubo->setMaterial(*mat_metal);
	cubo->setTextura("metal");
}	

//----------------------------------------------------------------------------
// Método de dibujado de Fondo
void Fondo::draw(bool dibujadoInmediato, tipoDibujado dibujado, tipoIluminacion iluminacion)
{
	glPushMatrix();
		glTranslatef(0,15,-15);
		glScalef(1,0.7,0.1);
		cubo->draw(dibujadoInmediato, dibujado, iluminacion);
	glPopMatrix();
}


//----------------------------------------------------------------------------
// Constructor de Portafiltros
Portafiltros::Portafiltros(int muestreoObjRev)
{
	cilindro_mad = new ObjRevolucion("cilindro", muestreoObjRev);
	cilindro_met = new ObjRevolucion("cilindro", muestreoObjRev);

	cilindro_mad->setColor(Tupla3f(0.5,0.5,0.5));
	cilindro_met->setColor(Tupla3f(0.5,0.5,0.5));

	cilindro_mad->setMaterial(*mat_madera);
	cilindro_met->setMaterial(*mat_metal) ;

	cilindro_mad->setTextura("text-madera");
	cilindro_met->setTextura("metal") ;
}

//----------------------------------------------------------------------------
// Método de dibujado de Portafiltros
void Portafiltros::draw(bool dibujadoInmediato, tipoDibujado dibujado, tipoIluminacion iluminacion)
{
	glPushMatrix();
		glTranslatef(0,19.4,11);
//1
		glPushMatrix();
			glTranslatef(-17 -(20 * anim_traslacion_x),-3.5 * anim_traslacion_y ,0);
			glRotatef(180 * anim_rotacion ,0,0,1);
			glPushMatrix();
				glPushMatrix();
					glTranslatef(0,-1,-14.8);
					glScalef(10,3,10);
					cilindro_met->draw(dibujadoInmediato, dibujado, iluminacion);
				glPopMatrix();

				glRotatef(270,1,0,0);
				glPushMatrix();
					glPushMatrix();
						glTranslatef(0,-0.3,0);	// Evitar colisión madera/metal
						glScalef(6,6,6);
						cilindro_mad->draw(dibujadoInmediato, dibujado, iluminacion);
					glPopMatrix();
					glPushMatrix();
						glScalef(4,12.2,4);
						cilindro_met->draw(dibujadoInmediato, dibujado, iluminacion);
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
//2
		glPushMatrix();
		//glTranslatef(0,0,0);
			glPushMatrix();
					glTranslatef(0,-1,-14.8);
					glScalef(10,3,10);
				cilindro_met->draw(dibujadoInmediato, dibujado, iluminacion);
			glPopMatrix();

			glRotatef(270,1,0,0);
			glPushMatrix();
				glPushMatrix();
					glTranslatef(0,-0.3,0);	// Evitar colisión madera/metal
					glScalef(6,6,6);
					cilindro_mad->draw(dibujadoInmediato, dibujado, iluminacion);
				glPopMatrix();
				glPushMatrix();
					glScalef(4,12.2,4);
					cilindro_met->draw(dibujadoInmediato, dibujado, iluminacion);
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
//3
		glPushMatrix();
		glTranslatef(17,0,0);
			glPushMatrix();
					glTranslatef(0,-1,-14.8);
					glScalef(10,3,10);
				cilindro_met->draw(dibujadoInmediato, dibujado, iluminacion);
			glPopMatrix();

			glRotatef(270,1,0,0);
			glPushMatrix();
				glPushMatrix();
					glTranslatef(0,-0.3,0);	// Evitar colisión madera/metal
					glScalef(6,6,6);
					cilindro_mad->draw(dibujadoInmediato, dibujado, iluminacion);
				glPopMatrix();
				glPushMatrix();
					glScalef(4,12.2,4);
					cilindro_met->draw(dibujadoInmediato, dibujado, iluminacion);
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}


//----------------------------------------------------------------------------
// Constructor de ParteFuncional
ParteFuncional::ParteFuncional(int tamCubo, int muestreoObjRev)
{
	cubo         = new Cubo     (tamCubo)  ;
	cilindro_met = new ObjRevolucion("cilindro", muestreoObjRev);

	cubo        ->setColor(Tupla3f(0.5,0.5,0.5));
	cilindro_met->setColor(Tupla3f(0.5,0.5,0.5));

	cubo        ->setMaterial(*mat_metal);
	cilindro_met->setMaterial(*mat_metal);

	cubo        ->setTextura("metal");
	cilindro_met->setTextura("metal");
}

//----------------------------------------------------------------------------
// Método de dibujado de ParteFuncional
void ParteFuncional::draw(bool dibujadoInmediato, tipoDibujado dibujado, tipoIluminacion iluminacion)
{
	glPushMatrix();

		glTranslatef(0,30,-3.5);
		glPushMatrix();
			glScalef(1,0.2,0.4);
			cubo->draw(dibujadoInmediato, dibujado, iluminacion);
		glPopMatrix();
//1
		glPushMatrix();
			glPushMatrix();
				glTranslatef(17,-9,0);
				glScalef(12,3.5,12);
				cilindro_met->draw(dibujadoInmediato, dibujado, iluminacion);
			glPopMatrix();
		glPopMatrix();
//2
		glPushMatrix();
			glPushMatrix();
				glTranslatef(0,-9,0);
				glScalef(12,3.5,12);
				cilindro_met->draw(dibujadoInmediato, dibujado, iluminacion);
			glPopMatrix();
		glPopMatrix();
//3
		glPushMatrix();
			glPushMatrix();
				glTranslatef(-17,-9,0);
				glScalef(12,3.5,12);
				cilindro_met->draw(dibujadoInmediato, dibujado, iluminacion);
			glPopMatrix();
		glPopMatrix();
//1
		glPushMatrix();
			glTranslatef(27,-4,8);
			glRotatef(25*anim_rotacion,0,1,1);
			glScalef(3,-14,3);
			cilindro_met->draw(dibujadoInmediato, dibujado, iluminacion);
		glPopMatrix();
//2
		glPushMatrix();
			glTranslatef(-36,-10,8);
			glRotatef(290,0,0,1);
			glScalef(3,14,3);
			cilindro_met->draw(dibujadoInmediato, dibujado, iluminacion);
		glPopMatrix();


	glPopMatrix();
}


void Portafiltros::animar()
{
	if (ida) {	// Ida
		if (anim_traslacion_y<0.99999) 
			anim_traslacion_y+=velocidad;

		else if (anim_traslacion_x<0.99999) 
			anim_traslacion_x+=velocidad;
		
		else if (anim_rotacion<0.99999)
			anim_rotacion+=velocidad;

		else 
			ida = false;
	}
	else {		// Vuelta
		if (anim_rotacion>0)
			anim_rotacion-=velocidad;

		else if (anim_traslacion_x>0.00009) 
			anim_traslacion_x-=velocidad;

		else if (anim_traslacion_y>0.00009) 
			anim_traslacion_y-=velocidad;

		else 
			ida = true;
	}
	
}

void ParteFuncional::animar()
{
	if (ida) {	// Ida
		if (anim_rotacion<0.99999) 
			anim_rotacion+=velocidad;
		else 
			ida = false;
	}
	else {		// Vuelta
		if (anim_rotacion>0.00009)
			anim_rotacion-=velocidad;
		else 
			ida = true;
	}
}

void Base::animar()
{
	if (ida) {	// Ida
		if (anim_rotacion<0.99999) 
			anim_rotacion+=velocidad;
		else 
			ida = false;
	}
	else {		// Vuelta
		if (anim_rotacion>0.00009)
			anim_rotacion-=velocidad;
		else 
			ida = true;
	}
	
}

void ModJerarquico::animar(bool dibujadoInmediato, tipoDibujado dibujado, tipoIluminacion iluminacion, bool primerPlano, int gradoL)
{
	glPushMatrix();
		if (primerPlano) glTranslatef(0,20,10);
		else {           glTranslatef(-100,20,-70);
                         glRotatef(90,0,1,0);
		}
		glPushMatrix();
		
			base->draw          (dibujadoInmediato, dibujado, iluminacion);
/*			if (gradoL==0 || gradoL==1)*/                   base->animar();
			fondo->draw         (dibujadoInmediato, dibujado, iluminacion);
			portafiltros->draw  (dibujadoInmediato, dibujado, iluminacion);
/*			if (gradoL==0 || gradoL==2)*/           portafiltros->animar();
			parteFuncional->draw(dibujadoInmediato, dibujado, iluminacion);
/*			if (gradoL==0 || gradoL==3)*/         parteFuncional->animar();

		glPopMatrix();
	glPopMatrix();
}


void Portafiltros::masVelocidad()
{
	velocidad+=0.00015;
}

void Portafiltros::menosVelocidad()
{
	if (velocidad>0.00009) velocidad-=0.0001;
}

void ParteFuncional::masVelocidad()
{
	velocidad+=0.00015;
}

void ParteFuncional::menosVelocidad()
{
	if (velocidad>0.00009) velocidad-=0.0001;
}

void Base::masVelocidad()
{
	velocidad+=0.00015;
}

void Base::menosVelocidad()
{
	if (velocidad>0.00009) velocidad-=0.0001;
}

void ModJerarquico::masVelocidad(int gradoL)
{
	if (gradoL==0) {	// Aumento general
		portafiltros->masVelocidad();
		parteFuncional->masVelocidad();
		base->masVelocidad();
	}
	else if (gradoL==1)
		portafiltros->masVelocidad();
	else if (gradoL==2)
		parteFuncional->masVelocidad();
	else if (gradoL==3)
		base->masVelocidad();
}

void ModJerarquico::menosVelocidad(int gradoL)
{
	if (gradoL==0) {	// Aumento general
		portafiltros->menosVelocidad();
		parteFuncional->menosVelocidad();
		base->menosVelocidad();
	}
	else if (gradoL==1)
		portafiltros->menosVelocidad();
	else if (gradoL==2)
		parteFuncional->menosVelocidad();
	else if (gradoL==3)
		base->menosVelocidad();
}