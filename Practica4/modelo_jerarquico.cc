#include "aux.h"
#include "modelo_jerarquico.h"

ModJerarquico::ModJerarquico(int tamCubo,int tamTetr,int muestreoObjRev)
{
	taza         = new ObjPLY("taza")      ;
	cubo         = new Cubo     (tamCubo)  ;
	cilindro_mad = new ObjRevolucion("cilindro", muestreoObjRev);
	cilindro_met = new ObjRevolucion("cilindro", muestreoObjRev);

	mat_metal  = new Material(Tupla4f(0.3, 0.3, 0.3, 1), Tupla4f(0.3, 0.3, 0.3, 1),
                              Tupla4f(0.2, 0.4, 0.3, 1), Tupla4f(0.3, 0.1, 0.3, 1), 0.8);

	mat_madera = new Material(Tupla4f(0.1, 0.1, 0.1, 1), Tupla4f(0.1, 0.1, 0.1, 1),
                              Tupla4f(0.1, 0.1, 0.1, 1), Tupla4f(0.1, 0.1, 0.1, 1), 0.4);

	mat_porcelana = new Material(Tupla4f(0.1, 0.1, 0.1, 1), Tupla4f(0.1, 0.1, 0.1, 1),
                                 Tupla4f(0.1, 0.1, 0.1, 1), Tupla4f(0.1, 0.1, 0.1, 1), 0.1);

	taza        ->setMaterial(*mat_porcelana);
	cubo        ->setMaterial(*mat_metal)    ;
	cilindro_mad->setMaterial(*mat_madera)   ;
	cilindro_met->setMaterial(*mat_metal)    ;

}

//----------------------------------------------------------------------------
// Dibuja el modelo jerárquico
void ModJerarquico::draw(bool dibujadoInmediato, tipoDibujado dibujado, tipoIluminacion iluminacion)
{
	glPushMatrix();
	
		base->draw();
		fondo->draw();
	


	// INI PORTAFILTROS
		glPushMatrix();
			glTranslatef(0,19.4,11);
	//1
			glPushMatrix();
				glTranslatef(-17,0,0);
				glPushMatrix();
					glScalef(10,3,10);
					glTranslatef(0,-0.4,-1.5);
					cilindro_met->draw(dibujadoInmediato, dibujado, iluminacion);
				glPopMatrix();

				glRotatef(270,1,0,0);
				glPushMatrix();
					glPushMatrix();
						glScalef(6,6,6);
						glTranslatef(0,-0.1,0);	// Evitar colisión madera/metal
						cilindro_mad->draw(dibujadoInmediato, dibujado, iluminacion);
					glPopMatrix();
					glPushMatrix();
						glScalef(4,12.2,4);
						cilindro_met->draw(dibujadoInmediato, dibujado, iluminacion);
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
	//2
			glPushMatrix();
			//glTranslatef(0,0,0);
				glPushMatrix();
					glScalef(10,3,10);
					glTranslatef(0,-0.4,-1.5);
					cilindro_met->draw(dibujadoInmediato, dibujado, iluminacion);
				glPopMatrix();

				glRotatef(270,1,0,0);
				glPushMatrix();
					glPushMatrix();
						glScalef(6,6,6);
						glTranslatef(0,-0.1,0);	// Evitar colisión madera/metal
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
					glScalef(10,3,10);
					glTranslatef(0,-0.4,-1.5);
					cilindro_met->draw(dibujadoInmediato, dibujado, iluminacion);
				glPopMatrix();

				glRotatef(270,1,0,0);
				glPushMatrix();
					glPushMatrix();
						glScalef(6,6,6);
						glTranslatef(0,-0.1,0);	// Evitar colisión madera/metal
						cilindro_mad->draw(dibujadoInmediato, dibujado, iluminacion);
					glPopMatrix();
					glPushMatrix();
						glScalef(4,12.2,4);
						cilindro_met->draw(dibujadoInmediato, dibujado, iluminacion);
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();

	// FIN PORTAFILTROS

	// INI FUNCIONAL

		glPushMatrix();

			glTranslatef(0,30,-3.5);
			glPushMatrix();
				glScalef(1,0.2,0.4);
				cubo->draw(dibujadoInmediato, dibujado, iluminacion);
			glPopMatrix();

			glPushMatrix();
				glPushMatrix();
					glTranslatef(-17,-9,0);
					glScalef(12,3.5,12);
					cilindro_met->draw(dibujadoInmediato, dibujado, iluminacion);
				glPopMatrix();
			glPopMatrix();

			glPushMatrix();
				glPushMatrix();
					glTranslatef(0,-9,0);
					glScalef(12,3.5,12);
					cilindro_met->draw(dibujadoInmediato, dibujado, iluminacion);
				glPopMatrix();
			glPopMatrix();

			glPushMatrix();
				glPushMatrix();
					glTranslatef(17,-9,0);
					glScalef(12,3.5,12);
					cilindro_met->draw(dibujadoInmediato, dibujado, iluminacion);
				glPopMatrix();
			glPopMatrix();

			glPushMatrix();
				glTranslatef(30,-18,8);
				glRotatef(25,0,0,1);
				glScalef(3,14,3);
				cilindro_met->draw(dibujadoInmediato, dibujado, iluminacion);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-30,-18,8);
				glRotatef(335,0,0,1);
				glScalef(3,14,3);
				cilindro_met->draw(dibujadoInmediato, dibujado, iluminacion);
			glPopMatrix();


		glPopMatrix();

	// FIN FUNCIONAL

	glPopMatrix();
}


void Base::draw()
{
	glPushMatrix();
		glTranslatef(0,0,-5);
		glPushMatrix();
			glScalef(1,0.2,0.4);
			cubo->draw(dibujadoInmediato, dibujado, iluminacion);
		glPopMatrix();


		glPushMatrix();
			glScalef(12,3.5,12);

//1
			glPushMatrix();
				glTranslatef(-1.7,-2.7,0.6);
				cilindro_met->draw(dibujadoInmediato, dibujado, iluminacion);
			glPopMatrix();
//2
			glPushMatrix();
				glTranslatef(1.7,-2.7,0.6);
				cilindro_met->draw(dibujadoInmediato, dibujado, iluminacion);
			glPopMatrix();
//3
			glPushMatrix();
				glTranslatef(-1.7,-2.7,-0.6);
				cilindro_met->draw(dibujadoInmediato, dibujado, iluminacion);
			glPopMatrix();
//4
			glPushMatrix();
				glTranslatef(1.7,-2.7,-0.6);
				cilindro_met->draw(dibujadoInmediato, dibujado, iluminacion);
			glPopMatrix();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(17,7,0);
			glScalef(70,60,70);
			taza->draw(dibujadoInmediato, dibujado, iluminacion);
		glPopMatrix();
	glPopMatrix();
}


void Fondo::draw()
{
	glPushMatrix();
		glTranslatef(0,15,-15);
		glScalef(1,0.7,0.1);
		cubo->draw(dibujadoInmediato, dibujado, iluminacion);
	glPopMatrix();

}