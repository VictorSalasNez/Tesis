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

/* Estructura de datos para que contengan la información neceseria para la
ejecución del programa*/

struct Viajes{
	string postura;
	string orig;
	string dest;
	int st;
	int et;
	int km;
};

string Reemplazo(string cadena){
	char espacio=' ';
	for(int j=0;j<(int)cadena.length();j++){
		if(cadena[j]==espacio){
			cadena.replace(j,1,"_");
		}
	}
	return cadena;
}

//ORDENAR VIAJES POR TIEMPO DE SALIDA DEL ORIGEN
//bool sortBySt (const Viajes &lhs, const Viajes &rhs){return lhs.st < rhs.st;}
//ORDENAR VIAJES POR TIEMPO DE LLEGADA A DESTINO

bool sortByEt (const Viajes &lhs, const Viajes &rhs){return lhs.et < rhs.et;}

int main(int argc, char **argv){

/*    clock_t start, end; 
	start = clock();
	*/
/* En el archivo Velocidad_DiasProgramacion_HorasOcio.txt esta la siguiente 
informacion:
VELOCIDAD PROMEDIO DE DESPLAZAMIENTO DE LOS BUSES
DIAS TOTALES DE PROGRAMACION
PARAMETRO Pmax, QUE SON LAS HORAS QUE UN BUS/TRIPULACION PUEDEN ESTAR OCIOSOS */
	
	ifstream Datos ("Vel_DiasProg_Ocio.txt");
	string linea;
	int vel=0, DiaProg=0, Pmax=0, empr=0, rompe=0;
	string Empresa, nom_salida;
	if(Datos.is_open()){
		int ii=0, jj=0;
		while(getline(Datos,linea)){
			istringstream iss(linea);
            string L1nea;
            while (getline(iss,L1nea,';')){
				if(ii==0 && jj==0){
					vel=atol(L1nea.c_str());
				}
				if(ii==1 && jj==0){
					DiaProg=atol(L1nea.c_str());
				}
				if(ii==2 && jj==0){
					Pmax=atol(L1nea.c_str());
					Pmax=Pmax*60;
				}
				if(ii==3 && jj==0){
					nom_salida=L1nea;
				}
				if(ii>=4 && jj==0){
					Empresa=L1nea;
				}

				if(ii>=4 && jj==1){
					empr=atol(L1nea.c_str());
					if(empr==1){
						rompe=1;
						break;
					}
				}
				jj=jj+1;
			}
			if(rompe==1){
				break;
			}
			ii=ii+1;
			jj=0;
		}
	}

/* Importación de datos necesarios para el programa en las matrices ViajesI */	


// Lee cuantos servicios exiten en el archivo de la empresa seleccionada
	ifstream arch1 (Empresa.c_str());
    string line;
   
    int fil=0,col=0,serv=0;
  	if (arch1.is_open()){
    	while(getline ( arch1, line)){
              fil=fil+1;
         }
	}
	else cout << "Imposible abrir archivo "<<Empresa<<endl;
	serv=fil-1;
	fil=0;
	cout<<"La empresa realiza "<<serv<<" servicios diarios"<<endl;
    arch1.close();


	ifstream arch2 (Empresa.c_str());
    string line2;
/* Dos vectores de estructuras de datos con tal de hacer futuras comparaciones. 
Probablementesea necesario solo uno, en el momento de realizar comparaciones 
hacerlas entre elementos del mismo vector*/
	vector<Viajes> ViajesI(serv);
//	vector<Viajes> ViajesJ(serv);
  	if (arch2.is_open()){
  		int contarerror=0;
    	while(getline ( arch2, line2)){
              istringstream iss(line2);
              string result2;
              while (getline(iss,result2,',')){
				  if (fil>0){
/* Importación del ID del viaje*/
						if (col==1){
							ViajesI[fil-1].postura=result2;
//							ViajesJ[fil-1].postura=result2;
						}
/* Importación de la locación de origen del viaje*/
						if (col==2){
							ViajesI[fil-1].orig=result2;
//							ViajesJ[fil-1].orig=result2;
						}
/* Importación de la locación de destino del viaje*/						
						if (col==3){
							ViajesI[fil-1].dest=result2;
//							ViajesJ[fil-1].dest=result2;
						}
/*Importación de st*/
						if (col==4){
							ViajesI[fil-1].st=atol(result2.c_str());
							//cout << "Tiempo" <<ViajesI[fil-1].et << endl;
//							ViajesJ[fil-1].et=ViajesI[fil-1].et;							
						}
/* Importación del km */
                        if (col==5){
							ViajesI[fil-1].km=atol(result2.c_str());
//							ViajesJ[fil-1].st=ViajesI[fil-1].st;
//							ViajesJ[fil-1].et=ViajesI[fil-1].et;
						}
/* Importación et */ 
						if(col==6){
							ViajesI[fil-1].et=atol(result2.c_str());
						}
					}
					col=col+1;
              }
              fil=fil+1;
              col=0;
         }	
	}

	else cout << "Imposible abrir archivo " << Empresa << endl;
//ORDEN DE VECTORES VIAJES i Y VIAJES j, DE MENOR A MAYOR TIEMPO DE LLEGADA EL DESTINO
	//sort(ViajesI.begin(), ViajesI.end(), sortByEt);

//	sort(ViajesJ.begin(), ViajesJ.end(), sortByEt);


  	ifstream Dias_NoProgramar;	
   	Dias_NoProgramar.open(argv[1]);

   	string Basura;
   	getline(Dias_NoProgramar,Basura);

   	stringstream Dias(Basura);
   	Dias >> DiaProg;


   	vector<int> No_Programar;


   	int i,j,tmp, cantViajes = ViajesI.size();
   	char espacio1,espacio2;
   	//cout << "cantidad de viajes: "<<cantViajes << endl;

   	getline(Dias_NoProgramar, Basura);
   	int unomas=0;
   	while(!Basura.empty()){

   		stringstream IjNoProgramar(Basura);

   		IjNoProgramar >> i;
   		IjNoProgramar >> espacio1;
   		IjNoProgramar >> j;
   		IjNoProgramar >> espacio2;
   		
		tmp = i + cantViajes*j;
		//cout << tmp << endl;
		No_Programar.push_back(tmp);

   		getline(Dias_NoProgramar, Basura);
   		unomas++;
   	}
   	Dias_NoProgramar.close();

/*
   	cout << "----------------------------" << endl;
	for(i = 0 ; i < No_Programar.size() ; i++){
   		cout << No_Programar[i] << " ";
	}	
	cout << endl;


   	cout << "----------------------------" << endl;
*/

//CREACION DE VECTOR DE DEPOSITOS (Sin guardar repetidos)
	vector<string> depos;
	for(int i=0;i<ViajesI.size();i++){
			
		if(i>0){
			if( find(depos.begin() ,depos.end(), ViajesI[i].orig ) == depos.end() ){
				depos.push_back(ViajesI[i].orig);
			}
			if( find(depos.begin() ,depos.end(), ViajesI[i].dest ) == depos.end() ){
				depos.push_back(ViajesI[i].dest);
			}
		}
		else{
			
			depos.push_back(ViajesI[i].orig);
			depos.push_back(ViajesI[i].dest);
		}
	}

	cout<<"Se programarán los viajes de la empresa "<<Empresa<<endl;
	cout<<"La velocidad promedio de los buses es "<<vel<<" km/hr"<<endl;
	//cout<<"Los buses pueden estar ociosos "<<Pmax/60<<" horas"<<endl;

	

	if(unomas==0)
		cout<<"Se realizaran "<<DiaProg++<<" dias de programacion"<<endl;
	else
		cout<<"Se realizaran "<<DiaProg<<" dias de programacion"<<endl;
// TF= FRONTERA DE PROGRAMACION
	int TF=DiaProg*2400;

	cout<<"La empresa tiene "<<depos.size()<<" depositos o ciudades de origen/destino"<<endl;
/* Imprime los depositos y sus capacidades a un archivos .txt*/	
	int capacidad=1000;


	//Archivo para identificar los terminales
	ofstream IdenTerminales("Transformacion/IdenTerminales.dat");
	//ofstream params("params.txt");
	vector <string> sets;
	vector <string> params;
	sets.push_back("set D:=");
	int num_depot=0;
	params.push_back("param K:=");
	for(int i=0;i<depos.size();i++){
		stringstream ss1;
		ss1 << i;
		sets.push_back(ss1.str());
		num_depot++;
		stringstream ss2; //Convertir entero a string
		ss2 << capacidad;
		IdenTerminales << ss1.str() << " " << Reemplazo(depos[i]) << endl;
		params.push_back(ss1.str()+" "+ss2.str());
	}
	sets.push_back(";");
	params.push_back(";");
	sets.push_back(" ");
	params.push_back(" ");	
	IdenTerminales.close();
	vector<Viajes> TViajesI(1);

/* Copia la información de cada viaje de los vectores ViajesI y ViajesJ a los 
vectores TViajesI y TViajesJ, solo que se le suman multiplos de 2400 a los tiempos
de salida y de llegada de cada viaje 
	Además escribe información de los ID-día en un archivo .txt*/
	ofstream ViajesPosturas ("Transformacion/PosturasProgramacion.dat");

	vector<int>::iterator it;
	//cout << "a eliminar: "<<unomas << endl;
	int t=0,salir=0, eliminados=0;
	sets.push_back("set N:=");
	for(int i=0;i<DiaProg;i++){
		for(int j=0;j<ViajesI.size();j++){

			it = find(No_Programar.begin(), No_Programar.end(), t); // buscar si t existe ern el vector para no programarlo
			
			if( it != No_Programar.end()){
				//cout << "encontro " << *it << endl;
				t++;
				eliminados++;
			}
			else{

				TViajesI[t-eliminados].postura = ViajesI[j].postura;
	//			TViajesJ[t].postura=ViajesJ[j].postura;
				TViajesI[t-eliminados].orig = ViajesI[j].orig;
	//			TViajesJ[t].orig=ViajesJ[j].orig;
				TViajesI[t-eliminados].dest = ViajesI[j].dest;
	//			TViajesJ[t].dest=ViajesJ[j].dest;
				TViajesI[t-eliminados].st = ViajesI[j].st+2400*i;
	//			TViajesJ[t].st=ViajesJ[j].st+24*60*i;
				TViajesI[t-eliminados].et = ViajesI[j].et+2400*i;
				
	/*			if (TViajesI[t].et>TF){
					salir=1;
					break;
				}*/
				//cout << "Tiempo" << TViajesI[t].et << endl;
	//			TViajesJ[t].et=ViajesJ[j].et+24*60*i;
				//sets<<TViajesI[t].postura<<"_d_"<<i+1<<",1"<<endl;
				
				stringstream ss;
				ss << t-eliminados;
				sets.push_back(ss.str());

				ViajesPosturas << t-eliminados << " "
				               << TViajesI[t-eliminados].postura <<" "
				            //   <<TViajesI[t-eliminados].orig << " "
				            //   <<TViajesI[t-eliminados].dest<<" "
				               <<TViajesI[t-eliminados].st<<" "
				               <<TViajesI[t-eliminados].et<<endl;
				t=t+1;
				TViajesI.resize(t+1);
				//cout<<TViajesI[j*(i+1)].postura<<"-"<<TViajesI[j*(i+1)].orig<<"-"<<TViajesI[j*(i+1)].dest<<"-"<<TViajesI[j*(i+1)].st<<"-"<<TViajesI[j*(i+1)].et<<endl;
			}
		}
	/*	if(salir==1){
			break;
		}*/
	}
	sets.push_back(";");
	sets.push_back(" ");
	sets.push_back(" ");

	int aelimnar = 0;
	for(int i = TViajesI.size() ; i >= 0 ; i--){
		if (TViajesI[i].dest == "")
			aelimnar++;
		else
			break;
	}

	for(int i = aelimnar-3 ; i>=0 ;i--)
		TViajesI.pop_back();

/*
	for(int i =0 ; i < TViajesI.size(); i++){
		cout << i << endl;
		cout << "   " << TViajesI[i].postura << endl;
		cout << "   " << TViajesI[i].orig << endl;
		cout << "   " << TViajesI[i].dest << endl;
		cout << "   " << TViajesI[i].st << endl;
		cout << "   " << TViajesI[i].et << endl;
		cout << "   " << TViajesI[i].km << endl;
	}

	cout << "aeliminar: "<<aelimnar << endl;
*/
	TViajesI.pop_back();
	ViajesI.clear();
	ViajesPosturas.close();
//	ViajesJ.clear();
/*Este archivo contiene la información de las distancias por carretera de la 
mayoría de las ciudades de Chile. */
	ifstream arch3 ("Chile2011ParaTesis.csv");
    string line3;
    fil=0;
	col=0;
	int colt=0;
  	if (arch3.is_open()){
    	while(getline ( arch3, line3)){
              fil=fil+1;
         }
	}
	else cout << "Imposible abrir archivo Chile2011.csv"<<endl;	
	int km=fil-1;
/* Importación de los datos de las ciudades y de las distancias entre las ciudades*/
	ifstream arch4 ("Chile2011ParaTesis.csv");
    string line4;
    fil=0;
	col=0;
	vector<vector<int> > travIJ(km,vector<int> (km,0)) ;
	vector<string> ciudades(km);
  	if (arch4.is_open()){
    	while(getline ( arch4, line4)){
              istringstream iss(line4);
              string result4;
              while (getline(iss,result4,',')){
				  if (fil>0){
					  if (col==0){
							ciudades[fil-1]=result4;
					  }
/*Con el objetivo de poder calcular los DHTij, las distancias entre ciudades
se multiplica y se divide por 60 y por 90km/h, respectivamente, para obtener la 
duración de los DHTij en minutos.*/
						if (col>0){
							travIJ[fil-1][col-1]=atoi(result4.c_str());
							travIJ[fil-1][col-1]=travIJ[fil-1][col-1]*100/vel;
							//cout << "Tiempo" << travIJ[fil-1][col-1] << endl;
						}
					}
					col=col+1;
              }
              fil=fil+1;
              col=0;
         }
	}
	else cout << "Imposible abrir archivo Chile2011.csv"<<endl;
	int ERROR=0;
/* Matriz travDI contiene los tiempos de viaje entre los depositos y las 
locaciones de salida del origen de cada viaje. 
En el modelo matemático este sera el costo setsi*/
	vector<vector<int> > travDI(depos.size(),vector<int> (TViajesI.size(),0));
	int k,l;

	
	for(int i=0;i<depos.size();i++){
/* Encuentra cada deposito en el archivo de ciudades de Chile*/
		for (k=0;k<ciudades.size();k++){
			if (ciudades[k].compare(depos[i])==0){
				break;
			}
			if(k==ciudades.size()-1){
				cout<<"No se encontro "<< depos[i] <<endl;
				ERROR=1;
				break;
			}
		}
		if(ERROR==1){
			cout<<"ERROR"<<endl;
			break;
		}

/* Encuentra cada locación de origen de cada viaje en el archivo de ciudades de 
Chile*/
		for(int j=0;j<TViajesI.size();j++){	
			for (l=0;l<ciudades.size();l++){
				if (ciudades[l].compare(TViajesI[j].orig)==0){
					travDI[i][j]=travIJ[k][l];
					//cout<<depos[i]<<"-"<<ViajesI[j].orig<<":"<<travDI[i][j]<<endl;
					break;
				}
				if(l==ciudades.size()-1){
					cout<<"No se encontro "<<TViajesI[j].orig<<endl;
					ERROR=1;
					break;
				}
			}
			if(ERROR==1){
				cout<<"ERROR"<<endl;
				break;
			}
		}
		if(ERROR==1){
			cout<<"ERROR"<<endl;
			break;
		}
	}
/* Matriz travID contiene los tiempos de viaje entre las locaciones de llegada al 
destino de cada viaje y los depositos. El procedimiento es análogo al utilizado 
para obtener la matriz travDI.
En el modelo matemático este será el costo Cid*/

	vector<vector<int> > travID(TViajesI.size(),vector<int> (depos.size(),0));
	for(int i=0;i<TViajesI.size();i++){
		for (k=0;k<ciudades.size();k++){
			if (ciudades[k].compare(TViajesI[i].dest)==0){
				break;
			}
		}
		if(k>ciudades.size()){
			cout<<"No se encontro "<<TViajesI[i].dest<<endl;
			break;
		}
		for(int j=0;j<depos.size();j++){	
			for (l=0;l<ciudades.size();l++){
				if (ciudades[l].compare(depos[j])==0){
					travID[i][j]=travIJ[k][l];
					break;
				}
			}
		}
	}
/* Matriz DHij contiene los tiempos de viaje entre las locaciones de llegada al 
destino de cada viaje "i" y las locaciones de salida del origen de cada viaje "j". 
El procedimiento es análogo al utilizado para obtener las matrices travDI y travJD.
En el modelo matemático DHij será el Cij^d. El valor de DHij se copia para cada 
valor de d del costo Cij^d.*/

	vector<vector<int> > DH(TViajesI.size(), vector<int> (TViajesI.size(),0));
	for(int i=0;i<TViajesI.size();i++){
		for(k=0;k<ciudades.size();k++){
			if(ciudades[k].compare(TViajesI[i].dest)==0){
				break;
			}			
		}
		if(k>ciudades.size()){
			cout<<"No se encontro "<<TViajesI[i].dest<<endl;
			break;
		}
		for(int j=0;j<TViajesI.size();j++){
			for(l=0;l<ciudades.size();l++){
				if(ciudades[l].compare(TViajesI[j].orig)==0){
					DH[i][j]=travIJ[k][l];
				}
			}
		}
	}
/* NF es la matriz (conjunto) que contiene los pares ordenados {i,j} de viajes 
factibles */
	vector<vector<int> > NF(1,vector<int> (2,0));
/* Pmax es un parámetro para la reducción del conjunto NF. Se calibrará en un 
futuro.*/
/*	int Pmax=0; 
	cout<<"Ingrese la holgura (en horas) que los buses pueden estar ociosos: "<<endl;
	cin>>Pmax;
	Pmax=Pmax*60; */
	int contar=0, Wi=30;
/* Crea primera fila del archivo NF*/
	int diasP=1;
	for(int i=0;i<TViajesI.size();i++){
		if(i>serv*diasP-1){
			diasP=diasP+1;
		}
		//cNF<<","<<TViajesI[i].postura<<"_d_"<<diasP;
	}
	//cNF<<endl;
	diasP=1;
	sets.push_back("set NF:=");
	params.push_back("param Cij:=");
	for(int i=0;i<TViajesI.size();i++){
		if(i>serv*diasP-1){
			diasP=diasP+1;
		}
		//cNF<<TViajesI[i].postura<<"_d_"<<diasP;
/* Wi es  el tiempo de descanso de la tripulación (y por ende del bus)en un 
teminal. Este parámetro vale 8*60 si la duración del viaje es superior a 8 horas 
(8*60 minutos)*/
/*
		if(TViajesI[i].et-TViajesI[i].st>=8*60){
			Wi=0;
		}
		else Wi=0;
*/

		for(int k=0;k<i+1;k++){
			//cNF<<",";
		}
		for(int j=i+1;j<TViajesI.size();j++){
			//cNF<<",";


/* Si se cumplen las condiciones: (1) el tiempo de salida del origen del viaje 
"j" menos el tiempo de llegada del viaje "i" menos el Wi menos el tiempo de viaje
entre la locaciones de origen del viaje "j" y de destino del viaje "i" es mayor 
o igual a cero y (2) el tiempo de salida del origen del viaje "j" menos el tiempo 
de llegada del viaje "i" menos el Wi menos el tiempo de viaje entre la locaciones 
de origen del viaje "j" y de destino del viaje "i" es menor a Pmax; entonces se
agrega el par ordeno {i,j} al conjunto NF*/ 
			if(TViajesI[j].st-TViajesI[i].et-Wi-DH[i][j]>=0 && TViajesI[j].st-TViajesI[i].et-Wi-DH[i][j]<Pmax){
				NF[contar][0]=i;
				NF[contar][1]=j;
				contar=contar+1;
				int fDH=DH[i][j];
				if(fDH==0){
					fDH=1;
				}
				//cNF<<fDH << endl;
				stringstream ss, ss2, ss3; //convertir entero a string
				ss << i;
				ss2 << j;
				ss3 << fDH;
				sets.push_back("(" + ss.str() + "," + ss2.str() + ") ");
				params.push_back(ss.str() + " " + ss2.str() + " " + ss3.str());
				NF.resize(contar+1,vector<int> (2));
			}
			else{
				//sets.push_back(" ");
				//params.push_back(" ");
			} 
			
		}
		//sets.push_back(" ");
		//params.push_back(" ");
	}
	sets.push_back(";");
	params.push_back(";");
	sets.push_back(" ");
	params.push_back(" ");	
	NF.pop_back();
/**/
	contar=0;
	vector<vector<int> > D1(1,vector<int> (2,0));
	diasP=1;
	for(int i=0;i<TViajesI.size();i++){
		if(i>serv*diasP-1){
			diasP=diasP+1;
		}
		//sets1<<","<<TViajesI[i].postura<<"_d_"<<diasP;
	}
	sets.push_back(" ");
	params.push_back(" ");
	sets.push_back("set D1:="); 
	params.push_back("param Cdi:=");
	for(int i=0;i<depos.size();i++){
		//sets1<<depos[i];
		for(int j=0;j<TViajesI.size();j++){
			//sets1<<",";
/* */ 
			if(TViajesI[j].st-travDI[i][j]>=0 ){
				D1[contar][0]=i;
				D1[contar][1]=j;
				contar=contar+1;
				stringstream ss, ss2;
				ss << i;
				ss2 << j;
				sets.push_back("("+ss.str()+","+ss2.str()+") ");
				stringstream ss3; //Conversion de entero a string
				ss3 << travDI[i][j];
				params.push_back(ss.str()+" "+ss2.str()+" "+ss3.str());
				D1.resize(contar+1,vector<int> (2));
			}
			else{
				//sets.push_back(" ");
				//params.push_back(" ");
			} 
		}
		//sets.push_back(" ");
		//params.push_back(" ");
	}
	sets.push_back(";");
	params.push_back(";");
	sets.push_back(" ");
	params.push_back(" ");
	D1.pop_back();

/**/
	contar=0;
	vector<vector<int> > D2(1,vector<int> (2,0));
	diasP=1;
	for(int i=0;i<depos.size();i++){
		//sets2<<","<<depos[i];
	}
	sets.push_back(" ");
	params.push_back(" ");
	//cout << TViajesI.size() << endl;
	sets.push_back("set D2:=");
	params.push_back("param Cid:=");
	for(int i=0;i<TViajesI.size();i++){
		//sets2<<TViajesI[i].postura;
		for(int j=0;j<depos.size();j++){
			//sets2<<",";
/* */ 
			if(TViajesI[i].et+travID[i][j]<=TF ){
				D2[contar][0]=i;
				D2[contar][1]=j;
				contar=contar+1;
				stringstream ss, ss2;
				ss << i;
				ss2 << j;
				sets.push_back("("+ss.str()+","+ss2.str()+") ");
				stringstream ss3; //Conversion de entero a string
				ss3 << TF-TViajesI[i].et+travID[i][j];				
				params.push_back(ss.str()+" "+ss2.str()+" "+ss3.str());
				D2.resize(contar+1,vector<int> (2));
			}
			else {
				//sets.push_back(" ");
				//params.push_back(" ");
			}
		}
		//sets.push_back(" ");
		//params.push_back(" ");
	}
	sets.push_back(";");
	params.push_back(";");
	sets.push_back(" ");
	params.push_back(" ");
	D2.pop_back();
	
	ofstream salida (nom_salida.c_str());
	//salida << "#" << "D" << "=" << num_depot << endl;
	//salida << "#" << "N" << "=" << t << endl << endl;
	
	for(int i=0;i<sets.size();i++){
		salida<<sets[i]<<endl;		
	}
	salida << endl;
	for(int i=0;i<params.size();i++){
		salida<<params[i]<<endl;
	}
	salida << endl;
	salida.close();


    //system("PAUSE");
    return EXIT_SUCCESS;
}