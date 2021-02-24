#include "aux.h"
#include "malla.h"

// *****************************************************************************
//
// Clase Malla3D
//
// *****************************************************************************

// -----------------------------------------------------------------------------
// Crea VBO y le atribuye un identificador

GLuint Malla3D::CrearVBO(GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid *puntero_ram)
{
	GLuint id_vbo ;						// resultado: identificador de VBO
	glGenBuffers( 1, &id_vbo );			// crear nuevo VBO, obtener identificador (nunca 0)
	glBindBuffer( tipo_vbo, id_vbo );	// activar el VBO usando su identificador
	
	// esta instrucción hace la transferencia de datos desde RAM hacia GPU
	glBufferData( tipo_vbo, tamanio_bytes, puntero_ram, GL_STATIC_DRAW );
	
	glBindBuffer( tipo_vbo, 0 );		// desactivación del VBO (activar 0)
	return id_vbo ;						// devolver el identificador resultado
}

// -----------------------------------------------------------------------------
// Visualización en modo inmediato con 'glDrawElements'
 
void Malla3D::draw_ModoInmediato()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, v.data()); 

	for (unsigned int i=0; i<f.size(); i++)	
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, &f[i] ) ;	// Cada triangulo
}

// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)

void Malla3D::draw_ModoDiferido()
{
	// (la primera vez, se deben crear los VBOs y guardar sus identificadores en el objeto)
	if (id_vbo_ver == 0  ||  id_vbo_tri == 0) {
		id_vbo_ver = CrearVBO(GL_ARRAY_BUFFER        , 3*v.size()*sizeof(float), v.data());
		id_vbo_tri = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, 3*f.size()*sizeof(int),   f.data());
	}

	// especificar localización y formato de la tabla de vértices, habilitar tabla
	glBindBuffer( GL_ARRAY_BUFFER, id_vbo_ver ); 			// activar VBO de vértices
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri ); 	// activar VBO de triángulos

	glEnableClientState( GL_VERTEX_ARRAY );			// habilitar tabla de vértices

	glVertexPointer( 3, GL_FLOAT, 0, 0 );			// especifica formato y offset (=0)


	// visualizar triángulos con glDrawElements (puntero a tabla == 0)
	glDrawElements( GL_TRIANGLES, 3*f.size(), GL_UNSIGNED_INT, 0 ) ;

	glBindBuffer( GL_ARRAY_BUFFER, 0 );				// desactivar VBO de vértices.
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );		// desactivar VBO de triángulos

	// desactivar uso de array de vértices
	glDisableClientState( GL_VERTEX_ARRAY );
}

// -----------------------------------------------------------------------------
// Visualización en modo Ajedrez (inmediato)
void Malla3D::draw_ModoAjedrez()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, v.data());
	glColorPointer (3, GL_FLOAT, 0, c.data());
	glShadeModel(GL_FLAT);		// Hacer que las caras tengan su color uniforme

	for (unsigned int i=0; i<=f.size(); i+=2)	
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, &f[i] ); // Cada triangulo par
	for (unsigned int i=1; i<=f.size(); i+=2)	
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, &f[i] ); // Cada triangulo impar

	glShadeModel(GL_SMOOTH);	// Restaurar estado predeterminado
}

// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido

void Malla3D::draw(bool inmediato, tipoDibujado dibujado)
{
	if      (dibujado == PUNTOS)
		glPolygonMode(GL_FRONT, GL_POINT);
	else if (dibujado == LINEAS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else if (dibujado == SOLIDO  ||  dibujado == AJEDREZ)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	
	if (dibujado==AJEDREZ){
		glShadeModel(GL_FLAT);
		glColorPointer (3, GL_FLOAT, 0, c.data());
		draw_ModoInmediato();
		glShadeModel(GL_SMOOTH);
	}
	else if (inmediato)
		draw_ModoInmediato();
	else if (!inmediato)
		draw_ModoDiferido ();
	
}

void Malla3D::setColorPuntos() {}
void Malla3D::setColorLineas() {} 
void Malla3D::setColorSolido() {}