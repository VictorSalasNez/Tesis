//Bibliotecas SYMPHONY
	//#include "symphony.h"

//Bibliotecas C
	#include <stdio.h>
	#include <stdlib.h>

//Bibliotecas C++
	#include <iostream>
	#include <string>
	#include <fstream>
	#include <sstream>
	#include <map>
	#include <vector>

using namespace std;

/* Estructura de datos que sirva para la traducción de los número de las rutas*/

struct Viajes{
	string postura;
	string orig;
	string dest;
	int st;
	int et;
	int km;
};

//Estructura para guardar las traducciones
map<int,Viajes> id_viajes; 
map<int,string> id_terminales;



//Estructura para guardar datos de SYMPHONY
map<int,int> Xij;
map<int,int> Xid;
map<int,vector<int> > Xdi;

//Estructur Para guardar Rutas
map<int,vector<int> > Rutas;



int main(int argc, char **argv){    
     
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
 
	/*
	*
	*		INICIO OBTENCIÓN MATRICES ( Xij, Xid, Xdi ) A PARTIR DE RESULTADOS SYMPHONY
	*
	*/

	char char_X,
		 char_i,
		 char_j,
		 Corchete,
		 coma;

	int Viaje_i,
		Viaje_j;

   ifstream Res;	
   Res.open(argv[1]);

   //cout << "SE CAEEEEEE" << endl;

   // avanzar hasta que muestre los resultados de las MATRICES

	string Basura;
	getline(Res,Basura);
	while(Basura[0] != 'X')
		getline(Res,Basura);


   //obtención matriz Xij
	string datosMatriz = Basura;

	while(datosMatriz[2] == 'j'){ // j es la que va cambiando en los resultados mostrados por SYMPHONY

		stringstream Stream_Xij(datosMatriz);

		Stream_Xij >> char_X;
		Stream_Xij >> char_i;
		Stream_Xij >> char_j;
		Stream_Xij >> Corchete;
		
		Stream_Xij >> Viaje_i; //viaje i
		
		Stream_Xij >> coma;
		
		Stream_Xij >> Viaje_j; //viaje j
		
		Stream_Xij >> Basura;

		//cout << "Xij[ " << Viaje_i << " , " << Viaje_j << " ]" << endl;
		
		Xij[ Viaje_i ] = Viaje_j;

		getline(Res,datosMatriz);

		//if(datosMatriz == Basura) break;
	}

   //obtención matriz Xid

	while( datosMatriz[2] == 'd' ){

		stringstream Stream_Xid(datosMatriz);

		Stream_Xid >> char_X;
		Stream_Xid >> char_i;
		Stream_Xid >> char_j;
		Stream_Xid >> Corchete;

		Stream_Xid >> Viaje_i; // viaje i
		
		Stream_Xid >> coma;
		
		Stream_Xid >> Viaje_j; //deposito d
		
		Stream_Xid >> Basura;

		//cout << "Lectura: Xid[ " << Viaje_i << " , " << Viaje_j << " ]" << endl;

		Xid[Viaje_i] = Viaje_j;

		getline(Res,datosMatriz);

	}
	

   //obtención matriz Xdi
	stringstream anterior;
	int v_anterior = -999; //se inicia con este número para comenzar la comparación

	while( datosMatriz[2] == 'i' ){

		stringstream Stream_Xdi(datosMatriz);

		Stream_Xdi >> char_X;
		Stream_Xdi >> char_i;
		Stream_Xdi >> char_j;
		Stream_Xdi >> Corchete;

		Stream_Xdi >> Viaje_i; // deposito d
		
		Stream_Xdi >> coma;
		
		Stream_Xdi >> Viaje_j; //deposito i
		
		Stream_Xdi >> Basura;
		//cout << "Lectura: Xdi[ " << Viaje_i << " , " << Viaje_j << " ]" << endl;

		if(v_anterior == Viaje_j) break; // para que no se repitan viajes (debido el error de la doble lectura de una linea, por la linea en blanco)

		v_anterior = Viaje_j;

		Xdi[Viaje_i].push_back(Viaje_j);

		getline(Res,datosMatriz);

	}

	Res.close();


	//cout << "SE CAEEEEEE" << endl;
/*

	cout << "--------------------------------------------------" << endl;

	for(map<int,int>::iterator it = Xij.begin() ; it !=Xij.end() ; it++)
		cout << "Xij[" << it->first << "] = " << Xij[it->first] << endl;
	

	cout << "--------------------------------------------------" << endl;

	for(map<int,int>::iterator it = Xid.begin() ; it !=Xid.end() ; it++){
		cout << "Xid[" << it->first << "] = " << Xid[it->first] << endl;
	}

	cout << "--------------------------------------------------" << endl;


	for(map<int,vector<int> >::iterator it = Xdi.begin() ; it != Xdi.end() ; it++){
		cout << "Xdi[" << it->first << "]";
		for(vector<int>::iterator it2 = it->second.begin(); it2 != it->second.end() ; it2++){
			cout << "[" << *it2 << "]" << endl;
		}
	}


	cout << "--------------------------------------------------" << endl;

*/


	/*
	*
	*		FIN OBTENCIÓN MATRICES A PARTIR DE RESULTADOS SYMPHONY
	*
	*/
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------

	/*
	*
	*		INICIO CREACION RURTAS DE DESPLIEGUE Y ARCHIVO SALIDA
	*
	*/

	int Id_Ruta=0,
		tmp;
	
		//cout << "SE CAEEEEEE" << endl;

	map<int,int>::iterator Busca; //buscador de ruta

	for(map<int,vector<int> >::iterator it = Xdi.begin() ; it != Xdi.end() ; it++){

		
		for(vector<int>::iterator it2 = it->second.begin(); it2 != it->second.end() ; it2++){
			
			Rutas[Id_Ruta].push_back(it->first);
			
			//Se obtiene el deposito inicial	
			Rutas[Id_Ruta].push_back(*it2);


			//se comienza a armar la ruta
			Busca = Xij.find(*it2);
			tmp = Busca->second;
			Rutas[Id_Ruta].push_back(tmp);
			
			

			Busca = Xij.find(tmp);

			while( Busca != Xij.end()){
				tmp = Busca->second;
				Rutas[Id_Ruta].push_back(tmp);
				Busca = Xij.find(tmp);
			}
			//se coloca el deposito final
			tmp = Xid[ Rutas[Id_Ruta].back() ];

			Rutas[Id_Ruta++].push_back(tmp);
		}
	}
	
	//cout << "Creé las rutas" << endl;
	//cout << "SE CAEEEEEE" << endl;
	//cout << "SE CAEEEEEE ULTIMO " << endl;


	/*
	*
	*		FIN CREACION RURTAS DE DESPLIEGUE Y ARCHIVO SALIDA
	*
	*/

//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------



	/*
	*
	*		INICIO LECTURA ARCHIVOS DE TRADUCCION
	*
	*/




	//Comenzando con los terminales
			
	ifstream datos_viajes;
	string EntradaViajes = "Transformacion/PosturasProgramacion.dat";

	datos_viajes.open( EntradaViajes.c_str() );

	if (! datos_viajes.is_open() ){
		exit(-1);
	}

	string lineaDatos;

	
	int ID_Modelo,
		st_archivo,
		et_archvio;
		
	string postura;

	while(true){
		
		getline(datos_viajes,lineaDatos);
		stringstream flujo_Datos(lineaDatos);
		

		flujo_Datos >> ID_Modelo;
		flujo_Datos >> postura;
		flujo_Datos >> st_archivo;
		flujo_Datos >> et_archvio;
		
		id_viajes[ID_Modelo].postura = postura;
		id_viajes[ID_Modelo].st = st_archivo;
		id_viajes[ID_Modelo].et = et_archvio;

		//cout << ID_Modelo <<" " << postura <<" " << origen_archivo <<" ; " << destino_archivo <<" " <<st_archivo <<" " << et_archvio <<" " << km_totales<< endl; 

		if(datos_viajes.eof()) break;
	} 

	datos_viajes.close();

	// Seguimos con los terminales

	ifstream datos_terminales;
	string EntradaTerminales = "Transformacion/IdenTerminales.dat";

	datos_terminales.open( EntradaTerminales.c_str() );

	if (! datos_terminales.is_open() ){
		exit(-1);
	}

	string lineaDatos_terminales;

	
	int ID_Terminal;
	
	string nombre_terminal;
	
	while(true){
		
		getline(datos_terminales,lineaDatos_terminales);
		stringstream flujo_Datos_terminales(lineaDatos_terminales);
		

		flujo_Datos_terminales >> ID_Terminal;
		flujo_Datos_terminales >> nombre_terminal;
		
		id_terminales[ID_Terminal] = nombre_terminal;

		//cout << ID_Modelo <<" " << postura <<" " << origen_archivo <<" ; " << destino_archivo <<" " <<st_archivo <<" " << et_archvio <<" " << km_totales<< endl; 

		if(datos_terminales.eof()) break;
	} 

	datos_terminales.close();

	//Recorrido de las estructuras para asegurarse de los datos guardados correctamente

	//primero la de viajes
	

    
/*
	for(map<int,Viajes>::iterator it = id_viajes.begin() ; it != id_viajes.end() ; it++){

		cout << "id: " << it->first << endl;
		cout << "   " << it->second.postura << endl;
		cout << "   " << it->second.st << endl;
		cout << "   " << it->second.et << endl;
	}
*/


	// GENERARA ARCHIVO RUTAS GENERADAS
	string nombre_archivo = argv[2]; 
	string SalidaPostura = nombre_archivo.substr(6); //le quita Datos/ al string
	SalidaPostura = SalidaPostura.substr( 0 , SalidaPostura.size()-4 ); //le quito el .dat

	string Rutas_Generadas = "Rutas_Generadas/" + SalidaPostura + ".txt" ; 

	ofstream sal_viajes(Rutas_Generadas.c_str());
	
	for(map<int,vector<int> >::iterator it = Rutas.begin(); it != Rutas.end() ; it++){

		sal_viajes << "Id: " << it->first << endl;

		for(vector<int>::iterator it2 = it->second.begin(); it2 != it->second.end() ; it2++){
			
			if(it2 == it->second.begin()){ // para ver si está al principio
				sal_viajes << id_terminales[*it2] << endl;
				continue;
			}

			if(it2+2 == it->second.end()){ // para ver si son los dos ultimo (viaje - terminal)

				sal_viajes << id_viajes[*(it2++)].postura << endl;
				//sal_viajes << id_terminales[*it2] << endl;

				break;
			}
			else{ // ruta normal
				sal_viajes << id_viajes[*it2].postura << endl;
			}
		

		}
		sal_viajes << endl;
	}




	sal_viajes.close();


	/*
	*
	*		FIN LECTURA ARCHIVOS DE TRADUCCION
	*
	*/
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------

  return(0);
}  