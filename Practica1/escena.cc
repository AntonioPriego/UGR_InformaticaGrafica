

#include "aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "malla.h" // objetos: Cubo y otros....
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

	 ejes.changeAxisSize( 5000 );

	 // crear los objetos de la escena....
	 cubo      = new Cubo     (40);
	 tetraedro = new Tetraedro(60);
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
	 ejes.draw();

	if (screenCubo) 
		cubo->draw     (dibujadoInmediato, dibujado);

	if (screenTetr) 
		tetraedro->draw(dibujadoInmediato, dibujado);


	 glutSwapBuffers();		  
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
		break;
		case 'Q' :
			if (modoMenu!=NADA)
				modoMenu=NADA;
			else 
				salir=true ;
				coutMenu("(⏎) Volviendo a Menu Principal");
		break ;
		case 'O' :
			modoMenu=SELOBJETO;
			coutMenu("(⎆) Entrando a Menu Objetos");
		break ;
		case 'V' :
			modoMenu=SELVISUALIZACION;
			coutMenu("(⎆) Entrando a Menu Visualizacion");
		break ;
		case 'D' :
			modoMenu=SELDIBUJADO;
			coutMenu("(⎆) Entrando a Menu Dibujado");
		break ;
		case 'C' : //Visualiza/Oculta cubo
			if (modoMenu==SELOBJETO)
				if (screenCubo){
					screenCubo=false;
					coutMenu("Oculta Cubo");
				}
				else {
					screenCubo=true;
					coutMenu("Visualiza Cubo");
				}
		break;
		case 'T' : //Visualiza/Oculta tetraedro
			if (modoMenu==SELOBJETO)
				if (screenTetr){
					screenTetr=false;
					coutMenu("Oculta Tetraedro");
				}
				else{
					screenTetr=true;
					coutMenu("Visualiza Tetraedro");
				}
		break;
		case 'P' : //Activa/Desactiva visualización modo puntos
			if (modoMenu==SELVISUALIZACION)
				dibujado = PUNTOS;
		break;
		case 'L' : //Activa/Desactiva visualización modo líneas
			if (modoMenu==SELVISUALIZACION)
				dibujado = LINEAS;
		break;
		case 'S' : //Activa/Desactiva visualización modo solido (x defecto)
			if (modoMenu==SELVISUALIZACION)
				dibujado = SOLIDO;
		break;
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