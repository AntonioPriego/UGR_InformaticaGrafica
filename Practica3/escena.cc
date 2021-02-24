

#include "aux.h"	// includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "malla.h"	// objetos: Cubo y otros....
#include "objrevolucion.h"
#include <iostream>
using namespace std;

//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************

Escena::Escena()
{
	Front_plane       = 50.0;
	Back_plane        = 2000.0;
	Observer_distance = 4*Front_plane;
	Observer_angle_x  = 0.0 ;
	Observer_angle_y  = 0.0 ;

	mat1 = new Material(Tupla4f(0.0, 0.5, 0.6, 1), Tupla4f(0.7, 0.5, 0.3, 1),
                                 Tupla4f(0.7, 0.3, 0.3, 1), Tupla4f(0.0, 0.0, 0.6, 1), 0.1);

	ejes.changeAxisSize( 5000 );

	// crear los objetos de la escena....
	espacio   = new Espacio             ;
	ply_obj   = new ObjPLY("ant")       ;
	barra_cafe= new ObjPLY("barra")     ;
	taburete  = new ObjPLY("taburete")  ;
	cubo      = new Cubo     (tamCubo)  ;
	tetraedro = new Tetraedro(tamTetr)  ;

	luzPosi = new LuzPosicional() ;
	luzDire = new LuzDireccional();
	
	//Constructor ObjRevolucion por ply
	objrev    = new ObjRevolucion("peon", muestreoObjRev);
	//Constructor ObjRevolucion por vector de vertices
	//objrev    = new ObjRevolucion(debugVectorObjRev(), muestreoObjRev, tapaSup, tapaInf);
	objrev->setColor(Tupla3f(0.5,0,0));

	objrev->setMaterial (*mat1);
	espacio->setMaterial(*mat1);


	cout << "\n\tPRESIONE \'H\' PARA MOSTRAR AYUDA\n\n";
}

//**************************************************************************
// inicialización de la escena (se ejecuta cuando ya se ha creado la ventana, por
// tanto sí puede ejecutar ordenes de OpenGL)
// Principalmemnte, inicializa OpenGL y la transf. de vista y proyección
//**************************************************************************

void Escena::inicializar( int UI_window_width, int UI_window_height )
{
	glClearColor( 1.0, 1.0, 1.0, 1.0 );// se indica cual sera el color para limpiar la ventana	(r,v,a,al)

	//glEnable( GL_DEPTH_TEST );	// se habilita el z-bufer
	glEnable( GL_CULL_FACE );

	Width  = UI_window_width/10;
	Height = UI_window_height/10;

	change_projection( float(UI_window_width)/float(UI_window_height) );
	glViewport( 0, 0, UI_window_width, UI_window_height );
}



// **************************************************************************
//
// función de dibujo de la escena: limpia ventana, fija cámara, dibuja ejes,
// y dibuja los objetos
//
// **************************************************************************

void Escena::dibujar()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
	change_observer();
	

/////////////////////////////  EJES  ///////////////////////////////
	ejes.draw();


/////////////////////////////  LUCES  //////////////////////////////
	if (iluminacion!=DESACTIVADO) {
		luzPosi->activar();
		luzDire->activar();
	}


////////////////////////////  PAREDES  /////////////////////////////
	espacio->draw(dibujadoInmediato, dibujado, iluminacion);


////////////////////////////  ATREZZO  /////////////////////////////
	dibujarAtrezzo();


////////////////////////////  CUBO  ////////////////////////////////
	if (!modoParalelo) {
		glPushMatrix();
			glTranslatef(50,0,-40);
			cubo->draw (dibujadoInmediato, dibujado, iluminacion);
		glPopMatrix();
	}
	else 
		dibujadoParalelo(cubo);


////////////////////////////  TETRAEDRO  ///////////////////////////
	if (!modoParalelo) {
		glPushMatrix();
			glTranslatef(-50,0,70);
			tetraedro->draw (dibujadoInmediato, dibujado, iluminacion);
		glPopMatrix();
	}
	else 
		dibujadoParalelo(tetraedro);	


////////////////////////////   PLY   ///////////////////////////////
	glPushMatrix();
		glTranslatef(50,40,-40);
		ply_obj->draw(dibujadoInmediato, dibujado, iluminacion);
	glPopMatrix();
	

////////////////////////////  OBJREV  //////////////////////////////
	glPushMatrix();
		glTranslatef(0,0,60);
		glScalef(20,20,20);
		objrev->draw(dibujadoInmediato, dibujado, iluminacion);
	glPopMatrix();


	glutSwapBuffers();		  

	// Reinicia el contador de instancias usando el modo paralelo
	instanciasEnParalelo=0;
}


void Escena::dibujarAtrezzo()
{

	// BARRA CAFE
	glPushMatrix();
		glTranslatef(-60,-9,-40);
		glRotatef(270, 0, 1, 0);
		glScalef(29,30,15);
		barra_cafe->draw(dibujadoInmediato, dibujado, iluminacion);
	glPopMatrix();	


	// TABURETES BARRA
	glPushMatrix();
		glTranslatef(10,-27,-85);
		glScalef(1.4,1.4,1.4);
		glRotatef(270, 0, 1, 0);
		taburete->draw(dibujadoInmediato, dibujado, iluminacion);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(10,-27,-45);
		glScalef(1.4,1.4,1.4);
		glRotatef(270, 0, 1, 0);
		taburete->draw(dibujadoInmediato, dibujado, iluminacion);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(10,-27,-5);
		glScalef(1.4,1.4,1.4);
		glRotatef(270, 0, 1, 0);
		taburete->draw(dibujadoInmediato, dibujado, iluminacion);
	glPopMatrix();

}


// Dibuja el objeto en modo paralelo (Puntos, Líneas y Sólido simultáneamente)
void Escena::dibujadoParalelo(Malla3D *malla)
{
	glPushMatrix();
		glTranslatef(50,0,-40+instanciasEnParalelo*65);
		malla->draw (dibujadoInmediato, SOLIDO);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(50,0,-40+instanciasEnParalelo*65);
		glScalef(1.05,1.05,1.05);
		malla->draw (dibujadoInmediato, LINEAS);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(50,0,-40+instanciasEnParalelo*65);
		glScalef(1.1,1.1,1.1);
		malla->draw (dibujadoInmediato, PUNTOS);
	glPopMatrix();
	

	instanciasEnParalelo++;
}


//**************************************************************************
//
// función que se invoca cuando se pulsa una tecla
// Devuelve true si se ha pulsado la tecla para terminar el programa (Q),
// devuelve false en otro caso.
//
//**************************************************************************

bool Escena::teclaPulsada( unsigned char tecla, int x, int y )
{
	cout << "Tecla pulsada (" << modoMenutoChar() << "):\t'" << tecla << "'" << endl;
	bool salir=false;

	switch( toupper(tecla) )
	{
		case 'H' :
			AyudaComandos();
		break ;
		case 'Q' :
			if (modoMenu!=NADA)
				modoMenu=NADA;
			else 
				salir=true ;
				coutMenu("(⏎) Volviendo a Menu Principal");
		break ;
		case 'O' :
			if (modoMenu==NADA) {
				modoMenu=SELOBJETO;
				coutMenu("(⎆) Entrando a Menu Objetos");
			}
		break ;
		case 'V' :
			if (modoMenu==NADA) {
				modoMenu=SELVISUALIZACION;
				coutMenu("(⎆) Entrando a Menu Visualizacion");
			}
		break ;
		case 'D' :
			if (modoMenu==NADA) {
				modoMenu=SELDIBUJADO;
				coutMenu("(⎆) Entrando a Menu Dibujado");
			}
		break ;
		case 'P' : //Activa/Desactiva visualización modo puntos
			if (modoMenu==SELVISUALIZACION) {
				dibujado = PUNTOS;
				modoParalelo=false;
			}
		break;
		case 'L' : //Activa/Desactiva visualización modo líneas
			if (modoMenu==SELVISUALIZACION) {
				dibujado = LINEAS;
				modoParalelo=false;
			}
		break;
		case 'S' : //Activa/Desactiva visualización modo solido (x defecto)
			if (modoMenu==SELVISUALIZACION) {
				dibujado = SOLIDO;
				modoParalelo=false;
			}
		break;
		case ',' : //Activa/Desactiva Tapa Superior ObjRevolucion
			if (modoMenu==SELVISUALIZACION) {
				//tapaSup = !tapaSup;
				objrev->cambiaTapas();
			}
		break;
		/*
		case '.' : //Activa/Desactiva Tapa Inferior ObjRevolucion
			if (modoMenu==SELVISUALIZACION) {
				tapaInf = !tapaInf;
				objrev->muestraTapas(tapaSup, tapaInf);
			}
		break;
		*/
		case 'A' : //Activa/Desactiva visualización modo ajedrez
			if (modoMenu==SELVISUALIZACION)
				dibujado=AJEDREZ;
		break;
		case '1' : //Se activa la visualización usando glDrawElements
			if (modoMenu==SELDIBUJADO)
				dibujadoInmediato=true;
		break;
		case '2' : //Se activa la visualización usando VBOs
			if (modoMenu==SELDIBUJADO)
				dibujadoInmediato=false;
		break;
		case '3' : //Activa/Desactiva visualización modo paralelo (todas las 3 visualizaciones)
			if (modoMenu==SELVISUALIZACION)
				modoParalelo = !modoParalelo;
		break;
		case '0' : //Se activa la iluminacion

			if (iluminacion==DESACTIVADO) {
				iluminacion=SUAVE;
			}
			else {
				glDisable(GL_LIGHTING);
				
				luzPosi->Desactivar();
				luzDire->Desactivar();

				iluminacion=DESACTIVADO;
			}
		break;
	}

	return salir;
}
//**************************************************************************

void Escena::teclaEspecial( int Tecla1, int x, int y )
{
	switch ( Tecla1 )
	{
		case GLUT_KEY_LEFT:
			Observer_angle_y-- ;
			break;
		case GLUT_KEY_RIGHT:
			Observer_angle_y++ ;
			break;
		case GLUT_KEY_UP:
			Observer_angle_x-- ;
			break;
		case GLUT_KEY_DOWN:
			Observer_angle_x++ ;
			break;
		case GLUT_KEY_PAGE_UP:
			Observer_distance *=1.2 ;
			break;
		case GLUT_KEY_PAGE_DOWN:
			Observer_distance /= 1.2 ;
			break;
	}

	//std::cout << Observer_distance << std::endl;
}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//
// ratio_xy : relacción de aspecto del viewport ( == ancho(X) / alto(Y) )
//
//***************************************************************************

void Escena::change_projection( const float ratio_xy )
{
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	const float wx = float(Height)*ratio_xy ;
	glFrustum( -wx, wx, -Height, Height, Front_plane, Back_plane );
}
//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************

void Escena::redimensionar( int newWidth, int newHeight )
{
	Width  = newWidth/10;
	Height = newHeight/10;
	change_projection( float(newHeight)/float(newWidth) );
	glViewport( 0, 0, newWidth, newHeight );
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void Escena::change_observer()
{
	// posicion del observador
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef( 0.0, 0.0, -Observer_distance );
	glRotatef( Observer_angle_y, 0.0 ,1.0, 0.0 );
	glRotatef( Observer_angle_x, 1.0, 0.0, 0.0 );
}

//**************************************************************************
// Funcion para mostrar en consola el proceso en ejecución
//***************************************************************************

void Escena::coutMenu(char *mensaje)
{
	cout << "\t" << mensaje << "... Ok\n";
}

//**************************************************************************
// Funcion que devuelve la cadena de char del 'modoMenu'
//***************************************************************************
char* Escena::modoMenutoChar()
{
	if      (modoMenu==NADA)
		return "Menu Principal";
	else if (modoMenu==SELOBJETO)
		return "Menu Objetos";
	else if (modoMenu==SELVISUALIZACION)
		return "Menu Visualizacion";
	else if (modoMenu==SELDIBUJADO)
		return "Menu Dibujado";
	else {
		cerr << "Error en modoMenu";
		exit(99);
	}
}

void Escena::AyudaComandos()
{
  std::cout << "\n\n//////////////////// MENU AYUDA /////////////////////////\n//\n";	
	std::cout << "//\t\'Q\': Salir del menu actual/Terminar ejecucion\n";
	std::cout << "//\t\'O\': Menu Seleccion de objeto\n";
	std::cout << "//\t\'V\': Menu Seleccion de visualizacion\n";
		std::cout << "//\t\t\'P\': Dibujado Puntos\n";
		std::cout << "//\t\t\'L\': Dibujado Lineas\n";
		std::cout << "//\t\t\'S\': Dibujado Solido\n";
		std::cout << "//\t\t\'A\': Dibujado Ajedrez\n";
		std::cout << "//\t\t\',\': Dibujado tapas en objRev\n";
		std::cout << "//\t\t\'3\': Modo dibujado paralelo\n";
	std::cout << "//\t\'D\': Menu Seleccion de dibujado\n";
		std::cout << "//\t\t\'1\': Modo dibujado inmediato\n";
		std::cout << "//\t\t\'2\': Modo dibujado VBOs\n";
	std::cout << "//\t\'0\': Activar/Desactivar iluminacion\n";
  std::cout << "//\n////////////////////////////////////////////////////////\n\n";	
}

//Funcion debug para crear vector de vertices
//Para probar constructor de objRevolucion
std::vector<Tupla3f> Escena::debugVectorObjRev()
{
	std::vector<Tupla3f> archivo;
		archivo.push_back(Tupla3f(1.0, -1.4, 0.0));
		archivo.push_back(Tupla3f(1.0, -1.1, 0.0));
		archivo.push_back(Tupla3f(0.5, -0.7, 0.0));
		archivo.push_back(Tupla3f(0.4, -0.4, 0.0));
		archivo.push_back(Tupla3f(0.4,  0.5, 0.0));
		archivo.push_back(Tupla3f(0.5,  0.6, 0.0));
		archivo.push_back(Tupla3f(0.3,  0.6, 0.0));
		archivo.push_back(Tupla3f(0.5,  0.8, 0.0));
		archivo.push_back(Tupla3f(0.55, 1.0, 0.0));
		archivo.push_back(Tupla3f(0.5,  1.2, 0.0));
		archivo.push_back(Tupla3f(0.3,  1.4, 0.0));

	return archivo;
}