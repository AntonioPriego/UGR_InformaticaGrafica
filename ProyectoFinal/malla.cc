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
	glEnableClientState (GL_VERTEX_ARRAY);
	glVertexPointer (3, GL_FLOAT, 0, v.data()); 
	
	glEnableClientState(GL_COLOR_ARRAY);      
	glColorPointer (3, GL_FLOAT, 0, c.data());

	glDrawElements(GL_TRIANGLES, 3*f.size()-strideFinal*3, GL_UNSIGNED_INT, f[0]);
	
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY );
}

// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)
void Malla3D::draw_ModoDiferido()
{
	if (id_vbo_ver == 0  ||  id_vbo_tri == 0  ||  id_vbo_col == 0  ||  id_vbo_tex == 0) {
		if (v.size())
			id_vbo_ver = CrearVBO(GL_ARRAY_BUFFER        , 3*v.size()*sizeof(float),  v.data());
		if (f.size())
			id_vbo_tri = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, 3*f.size()*sizeof(int),    f.data());
		if (c.size())
			id_vbo_col = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, 3*c.size()*sizeof(float),  c.data());
		if (ct.size())
			id_vbo_tex = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, 2*ct.size()*sizeof(float),ct.data());
	}

	glBindBuffer(GL_ARRAY_BUFFER, id_vbo_ver); 	// activar VBO de vértices
	glVertexPointer(3, GL_FLOAT, 0, 0);			// especifica formato y offset (=0)
	glBindBuffer(GL_ARRAY_BUFFER, 0); 			// desactivar VBO de vértices
	glEnableClientState( GL_VERTEX_ARRAY );		// habilitar tabla de vértices

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri); 	// activar VBO de triángulos
	
	glBindBuffer(GL_ARRAY_BUFFER, id_vbo_col);
	glColorPointer(3, GL_FLOAT, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glEnableClientState(GL_COLOR_ARRAY);

	if (!material_activo  &&  tex.establecida()) { // !material_activo==textura_activa
		glEnable (GL_TEXTURE_2D);
		glBindBuffer(GL_ARRAY_BUFFER, id_vbo_tex);
		glTexCoordPointer(2, GL_FLOAT, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		tex.activar();
	}


	// visualizar triángulos con glDrawElements (puntero a tabla == 0)
	glDrawElements(GL_TRIANGLES, 3*f.size(), GL_UNSIGNED_INT, 0) ;

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);			// desactivar VBO de triángulos

	// desactivar uso de array de vértices
	glDisableClientState(GL_VERTEX_ARRAY       );
	glDisableClientState(GL_COLOR_ARRAY        );
	if (!material_activo  &&  tex.establecida()) { // !material_activo==textura_activa
		glDisableClientState(GL_TEXTURE_COORD_ARRAY );
		glDisable(GL_TEXTURE_2D);
	}
}

// -----------------------------------------------------------------------------
// Visualización en modo Ajedrez (inmediato)
void Malla3D::draw_ModoAjedrez()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, v.data());
	
	glShadeModel(GL_FLAT);		// Hacer que las caras tengan su color uniforme


	glColorPointer (3, GL_FLOAT, 0, cA.data());	// Color indicado para modoAjedrez (1)
	glDrawElements(GL_TRIANGLES, f.size() *3, GL_UNSIGNED_INT, f[0] ); 


	glShadeModel(GL_SMOOTH);	// Restaurar estado predeterminado

	glDisableClientState( GL_VERTEX_ARRAY );
	glDisableClientState( GL_COLOR_ARRAY );
}


// -----------------------------------------------------------------------------
// Visualización Iluminado Inmediato
void Malla3D::draw_Iluminado_Inmediato()
{
	glNormalPointer    ( GL_FLOAT, 0, nv.data() );
	glEnableClientState( GL_NORMAL_ARRAY );

	glEnable(GL_NORMALIZE);

	if (!material_activo  &&  tex.establecida()) { // !material_activo==textura_activa
		glEnable (GL_TEXTURE_2D);
		glEnableClientState (GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer (2, GL_FLOAT, 0, ct.data());
		tex.activar();
	}

	draw_ModoInmediato();
	
	glDisableClientState( GL_NORMAL_ARRAY );
	glDisable( GL_NORMALIZE  );	
	if (!material_activo  &&  tex.establecida()) { // !material_activo==textura_activa
		glDisableClientState(GL_TEXTURE_COORD_ARRAY );
		glDisable(GL_TEXTURE_2D);
	}
}

// -----------------------------------------------------------------------------
// Visualización Iluminado Diferido
void Malla3D::draw_Iluminado_Diferido()
{
	if (id_vbo_nor == 0  &&  nv.size()) 
		id_vbo_nor = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, 3*nv.size()*sizeof(float),  nv.data());


	glBindBuffer(GL_ARRAY_BUFFER, id_vbo_nor);
	glNormalPointer(GL_FLOAT, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glEnableClientState(GL_NORMAL_ARRAY);
	
	glEnable(GL_NORMALIZE);

	draw_ModoDiferido();

	glDisable(GL_NORMALIZE);

	glDisableClientState(GL_NORMAL_ARRAY);
}

// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido

void Malla3D::draw(bool inmediato, tipoDibujado dibujado, tipoIluminacion iluminacion)
{
	if (!normales_calculadas) 
		normales_calculadas = calcular_normales();

	if (!coordtex_calculadas) 
		coordtex_calculadas = calcular_coorTexturaCilindrica();

	if (iluminacion==MATERIAL) material_activo=true;

	if (dibujado==AJEDREZ) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		draw_ModoAjedrez();
	}
	else if (iluminacion==DESACTIVADO) {
		if      (dibujado == PUNTOS) {
			glPolygonMode(GL_FRONT, GL_POINT);
			glPointSize(2);
		}
		else if (dibujado == LINEAS) 
			glPolygonMode(GL_FRONT_AND_BACK	, GL_LINE);
		else if (dibujado == SOLIDO)
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		
		if (inmediato)
			draw_ModoInmediato();

		else if (!inmediato)
			draw_ModoDiferido ();

	}
	else { // (iluminacion==SUAVE || iluminacion==PLANA || iluminacion==MATERIAL)
		m.aplicar();	// Aplica el material
		
		if (iluminacion==SUAVE  ||  iluminacion==MATERIAL)
			glShadeModel(GL_SMOOTH);
		else
			glShadeModel(GL_FLAT);

	
		(inmediato) ? draw_Iluminado_Inmediato() : draw_Iluminado_Diferido();
	}

	material_activo=false;
}

// -----------------------------------------------------------------------------
// Establece el color principal
void Malla3D::setColor(Tupla3f color)
{
	c.resize(v.size());

	for (int i=0; i<c.size(); i++) 
		c[i] = color;

	// Da unos colores por defecto a Ajedrez
	setColoresAjedrez();
}

// -----------------------------------------------------------------------------
// Establece el color secundario
void Malla3D::setColoresAjedrez(Tupla3f color1, Tupla3f color2)
{
	cA.resize(v.size());

	for (int i=0; i+1<=v.size(); i+=2) {
		cA[i] = color1;
	}

	for (int i=1; i+1<=v.size(); i+=2) 
		cA[i] = color2;
}


// -----------------------------------------------------------------------------
// Calcula las normales de cada vértice para la iluminación
bool Malla3D::calcular_normales() 
{
	nc.resize(f.size());

	// Calcular normales a las caras
	for (int i=0;i<f.size();i++) {
		Tupla3f a = v[f[i][1]]-v[f[i][0]];
		Tupla3f b = v[f[i][2]]-v[f[i][0]];
		Tupla3f normal = a.cross(b);

		nc[i] = normal.normalized();
	}	

	// Calcular normales de vértices
	nv.resize(v.size());

	for (int i=0; i<v.size(); i++)
		nv[i] = Tupla3f(0.0,0.0,0.0);

	for (int i=0; i<f.size(); i++) {
		nv[f[i][0]][0] +=nc[i][0];
		nv[f[i][0]][1] +=nc[i][1];
		nv[f[i][0]][2] +=nc[i][2];

		nv[f[i][1]][0] +=nc[i][0];
		nv[f[i][1]][1] +=nc[i][1];
		nv[f[i][1]][2] +=nc[i][2];

		nv[f[i][2]][0] +=nc[i][0];
		nv[f[i][2]][1] +=nc[i][1];
		nv[f[i][2]][2] +=nc[i][2];
	}

	for (int i=0; i<v.size(); i++)
		nv[i].normalized();

	return true;
}

// -----------------------------------------------------------------------------
// Calcula las coordenadas de la textura Cilíndricas
bool Malla3D::calcular_coorTexturaCilindrica()
{
	Tupla3f pMax = v[0];

	// Se recorren todos los vértices
	for (int i=1; i<v.size(); i++) {
		if(v[i][0]>pMax[0]) //x
			pMax[0] = v[i][0];
		
		if(v[i][1]>pMax[1]) // y
			pMax[1] = v[i][1];
		
		if(v[i][2]>pMax[2]) // z
			pMax[2] = v[i][2];
	}

	Tupla3f pMin = v[0];

	// Se recorren todos los vértices
	for (int i=1; i<v.size(); i++) {
		if(v[i][0]<pMax[0]) // x
			pMax[0] = v[i][0];
		
		if(v[i][1]<pMax[1]) // y
			pMax[1] = v[i][1];
		
		if(v[i][2]<pMax[2]) // z
			pMax[2] = v[i][2];
	}

	//Se calcula alfa u y v como indica la teoría
	for (int i=0; i<v.size(); i++){

		// Se crea alfa
		float alfa = atan2(v[i][2], v[i][0]);

		// u = 0.5 + alfa/2PI
		float u = 0.5 + (alfa/(2*PI));

		// w = altura-altura mínima / altura máxima-altura mínima
		float w = (v[i][1]-pMin[1]) / (pMax[1]-pMin[1]);

		// Se guardan los valores en ct
		ct.push_back(Tupla2f(u,w));

	}

	return true;
}

bool Malla3D::calcular_coorTextura(bool mosaico)
{
	Tupla3f pMax = v[0];

	// Se recorren todos los vértices
	for (int i=1; i<v.size(); i++) {
		if(v[i][0]>pMax[0]) //x
			pMax[0] = v[i][0];
		
		if(v[i][1]>pMax[1]) // y
			pMax[1] = v[i][1];
		
		if(v[i][2]>pMax[2]) // z
			pMax[2] = v[i][2];
	}

	Tupla3f pMin = v[0];

	// Se recorren todos los vértices
	for (int i=1; i<v.size(); i++) {
		if(v[i][0]<pMax[0]) // x
			pMax[0] = v[i][0];
		
		if(v[i][1]<pMax[1]) // y
			pMax[1] = v[i][1];
		
		if(v[i][2]<pMax[2]) // z
			pMax[2] = v[i][2];
	}

	for (int i=0; i<v.size(); i++) {
		float u = (v[i][0]-pMin[0]) / (pMax[0]-pMin[0]);

		float w = (v[i][1]-pMin[1]) / (pMax[1]-pMin[1]);

		// Se guardan los valores en ct
		ct.push_back(Tupla2f(u,w));

	}
	return true; 
}


void Malla3D::setMaterial (Tupla4f _emision, Tupla4f _difuso,
                           Tupla4f _especular, Tupla4f _ambiente, float _brillo)
{
	m.set (_emision, _difuso, _especular, _ambiente, _brillo);
}

void Malla3D::setMaterial (Material _m)
{
	m.set (_m);
}

void Malla3D::setTextura(const std::string &archivo)
{
	tex.set(archivo);
}