
//Bibliotecas SYMPHONY
	#include "symphony.h"


//Bibliotecas C
	#include <stdio.h>
	//#include <stdlib.h>

//Bibliotecas C++
	#include <algorithm> 
	#include <cassert> 
	#include <cstdlib>
	#include <fstream>
	#include <iostream>
	#include <iterator>
	#include <ostream>
	#include <sstream>
	#include <stdio.h>
	#include <string>
	#include <time.h>
	#include <vector>

	using namespace std;


int main(int argc, char **argv){    

//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------

	/*
	*
	*		INICIO CARGAR EL PROBLEMA Y RESOLVERLO
	*
	*/

	int num_cols, 
		num_rows,
		num_elements;   
   
   char *modelfile = argv[1]; //cambiar el archivo si se desea otro modelo
   char *datafile  = argv[2] ; //cmambiar datos si se desea probar con otro
   
   sym_environment *env = sym_open_environment(); //crea el ambiente para resolver el problema
   sym_read_gmpl(env, modelfile,datafile); // lee el modelo (,mod) y los datos (.dat).

   //sym_parse_command_line(env, argc, argv); // esta funcion permite leer los archivos pero con los comandos desde terminal ( -F modelo.mod -D datos.dat) 
   //sym_load_problem(env);
   
   sym_solve(env); //resulve el problema
   

	/*
	*
	*		FIN CARGAR EL PROBLEMA Y RESOLVERLO
	*
	*/

//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------

/*
   //obtener algunos datos
   sym_get_num_cols(env, &num_cols);
   printf("Número de colomnas =  %d\n",num_cols );
   
   sym_get_num_rows(env, &num_rows);
   printf("Número de filas =  %d\n",num_rows );
   
   sym_get_num_elements(env, &num_elements);
   printf("Número de elementos =  %d\n",num_elements );
*/
   sym_close_environment(env);
   
   return(0);
} 