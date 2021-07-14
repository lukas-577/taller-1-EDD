//TRABAJO 1# EDD LUKAS MEDINA ROZAS | RAFAEL FIGUEROA ARANEDA.SECCION:301. PROFESOR: FABIAN GONZALES
// linck del video : https://www.youtube.com/watch?v=Y_RnQM2mEiY


#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <sstream>
#include <iterator>


using namespace std;



struct datos_de_camas		//uso del struct
{
  int anho;
  int mes;
  int dia;
  int camas_totales;
  int camas_ocupadas;
};

//variable global que soporta una gran cantidad de datos
#define MAX_REGISTRO 100000
datos_de_camas lista[MAX_REGISTRO];

string nombreArchivo = "camas_csv.txt";

//DECLARATIVAS DE FUNCIONES

void Menu ();			//funcion menu

void lectura ();

void PasarAlVector (string nombreArchivo, datos_de_camas lista[],
		    int &cantidad);

void MostrarVector (datos_de_camas lista[], int cantidad);

void Calcula_Disponibilidad (datos_de_camas lista[],
			     string nombreArchivoSalida, int cantidad);

int Mayor_Ocupacion (int anho, int mes, datos_de_camas lista[], int cantidad);

int Menor_Disponibilidad (int anho, int mes, datos_de_camas lista[],
			  int cantidad);

float Promedio_Disponibilidad (int anho, int mes, datos_de_camas lista[],
			       int cantidad);

float Promedio_Camas_Ocupadas (int anho, int mes, datos_de_camas lista[],
			       int cantidad);

void Comparativa_Anual (int anho, int mes, datos_de_camas lista[],
			int cantidad);


//INICIO DE PROGRAMA
int
main ()
{

  //DeclaraciC3n de archivos.
  string nombreArchivo = "camas_csv.txt";
  string nombreArchivoSalida = "calcula_disponibilidad.txt";
  //Variables
  int cantidad = 0, mes, anho;

  cout << "PROGRAMA CAMAS UCI \n\n";	//Titulo


  //Llamado de Funciones

  lectura ();			//lee el archivo ifstream.

  PasarAlVector (nombreArchivo, lista, cantidad);	//guarda la informaciC3n del archivo al vector.

  //MostrarVector(lista, cantidad);//muestra el vector lista.

  Calcula_Disponibilidad (lista, nombreArchivoSalida, cantidad);	//crea un archivo ofstream



  //MENU
  int opc = 0;

  do
    {
      cout << "Ingrese anho de ocupacion entre el 2019 y 2020: ";
      cin >> anho;
      if (anho != 2019 && anho != 2020)
	{
	  cout << "\nError, vuelva a ingresar\n";
	}

    }
  while (anho != 2019 && anho != 2020);



  do
    {
      cout << "Ingrese mes de ocupacion entre el 1 y el 12: ";
      cin >> mes;

      if (mes > 1 && mes > 12)
	{
	  cout << "\nError, vuelva a ingresar\n";
	}

    }
  while (mes > 1 && mes > 12);






  do
    {
      cout << endl << endl;

      cout << "1.mayor ocupacion dentro de ese periodo\n";

      cout << "2.menor disponibilidad dentro de ese periodo\n";

      cout << "3.Promedio de camas totales del periodo\n";

      cout << "4.Salir\n";


      cout << "\nIngrese la opcion: ";
      cin >> opc;


      switch (opc)
	{

	case 1:
	  cout << "Mayor ocupacion es: " << Mayor_Ocupacion (anho, mes, lista,
							     cantidad);
	  break;

	case 2:
	  cout << "La menor disponibilidad dentro de ese periodo es: " <<
	    Menor_Disponibilidad (anho, mes, lista, cantidad);
	  break;

	case 3:
	  cout << "\nEl promedio de camas totales del periodo es:" <<
	    Promedio_Disponibilidad (anho, mes, lista, cantidad);
	  break;

	case 4:
	  cout << "Has salido con exito\n";
	  break;

	default:
	  cout << "ERROR, ingrese una opcion correcta\n";




	}

    }
  while (opc > 4);




  Comparativa_Anual (anho, mes, lista, cantidad);	//COMPARATIVA ANUAL.
  return 0;
}

//DESARROLLO DE FUNCIONES.

void
lectura ()
{

  ifstream archivo;

  //abrimos el modo lectura
  archivo.open ("camas_csv.txt", ios::in);

  if (archivo.is_open ())
    {

      string texto;

      while (getline (archivo, texto))
	{

	  //cout<<texto<<endl;

	}
    }
  else
    {
      cout << "error al abrir el archivo";
    }
}



void
PasarAlVector (string nombreArchivo, datos_de_camas lista[], int &cantidad)
{
  ifstream archivo;
  archivo.open (nombreArchivo.c_str (), ios::in);


  if (archivo.is_open ())
    {
      string linea;
      while (getline (archivo, linea, '\n'))
	{
	  vector < string > items;
	  stringstream ss (linea);
	  string temp;
	  while (getline (ss, temp, ';'))
	    items.push_back (temp);
	  //usamos un condicional para comparar el vector
	  if (cantidad > 0)
	    {
	      lista[cantidad].anho = atoi (items[0].c_str ());
	      lista[cantidad].mes = atoi (items[1].c_str ());
	      lista[cantidad].dia = atoi (items[2].c_str ());
	      lista[cantidad].camas_totales = atoi (items[3].c_str ());
	      lista[cantidad].camas_ocupadas = atoi (items[4].c_str ());
	    }
	  cantidad++;

	}
      //cerramos el archivo
      archivo.close ();
    }
  else
    {

      cout << "error en la apertura del archivo " + nombreArchivo + " ";

    }
  cout << "Se han cargado " << cantidad << " Registros" << endl << endl;
}

void
MostrarVector (datos_de_camas lista[], int cantidad)
{
  for (int i = 0; i < cantidad; i++)
    {
      cout << i << "->";
      cout << lista[i].anho << " ";
      cout << lista[i].mes << " ";
      cout << lista[i].dia << " ";
      cout << lista[i].camas_totales << " ";
      cout << lista[i].camas_ocupadas << " ";
      cout << "\n";


    }
  cout << cantidad;
}

void
Calcula_Disponibilidad (datos_de_camas lista[], string nombreArchivoSalida,
			int cantidad)
{


  ofstream archivo;
  archivo.open (nombreArchivoSalida, ios::out);
  int resta = 0;

  if (archivo.is_open ())
    {

      archivo << "anho; mes; dia; total_camas_disponibles" << endl;

      for (int i = 1; i < cantidad; i++)
	{
	  resta = lista[i].camas_totales - lista[i].camas_ocupadas;

	  //para escribrir dentro del archivo txt 
	  archivo << lista[i].anho << ";\t";
	  archivo << lista[i].mes << ";\t";
	  archivo << lista[i].dia << ";\t";
	  archivo << resta << endl;


	}

    }
  else
    {
      cout << "error al escribir el archivo";
    }
}

//FUNCION 1. MAYOR OCUPACION
int
Mayor_Ocupacion (int anho, int mes, datos_de_camas lista[], int cantidad)
{
  int n, mayor = 0;
  for (int i = 0; i < cantidad; i++)
    {
      if (lista[i].anho == anho && lista[i].mes == mes)
	{
	  if (lista[i].camas_ocupadas > mayor)
	    {

	      mayor = lista[i].camas_ocupadas;	//mayor = lista[i].camas_ocupadas
	    }
	}
    }
  //cout<<endl;
  return mayor;
}

//FUNCION 2. MENOR DISPONIBILIDAD
int
Menor_Disponibilidad (int anho, int mes, datos_de_camas lista[], int cantidad)
{
  int n, menor, disp = 0;
  for (int x = 0; x < cantidad - 2; x++)
    {
      if (lista[x].anho == anho && lista[x].mes == mes)
	{
	  disp = lista[x].camas_totales - lista[x].camas_ocupadas;
	  if (menor > disp)
	    {
	      menor = disp;
	    }
	}
    }
  return menor;
}



//FUNCION 3. PROMEDIO 
float
Promedio_Disponibilidad (int anho, int mes, datos_de_camas lista[],
			 int cantidad)
{
  float n = 0, suma = 0;
  for (int x = 0; x < cantidad - 2; x++)
    {
      if (lista[x].anho == anho && lista[x].mes == mes)
	{
	  int dispo;
	  dispo = lista[x].camas_totales - lista[x].camas_ocupadas;
	  suma += dispo;
	  n++;
	}
    }
  return suma / n;

}

//FUNCION 3A.PROMEDIO
float
Promedio_Camas_Ocupadas (int anho, int mes, datos_de_camas lista[],
			 int cantidad)
{
  float n = 0, suma = 0;
  for (int x = 0; x < cantidad - 2; x++)
    {
      if (lista[x].anho == anho && lista[x].mes == mes)
	{
	  int ocup;
	  ocup = lista[x].camas_ocupadas;
	  suma = suma + ocup;
	  n++;
	}

    }
  return suma / n;
}

//FUNCION 4. COMPARATIVO ANHO ACTUAL ANTERIOR 
void
Comparativa_Anual (int anho, int mes, datos_de_camas lista[], int cantidad)
{


  int j, j2, opc, result;
  cout << "\nIngrese el anho anterior: ";
  cin >> j;			//corresponde al anho anterior.
  cout << "\nIngrese el anho actual: ";
  cin >> j2;			//corresponde al anho actual.
  for (int i = 0; i < cantidad - 2; i++)
    {
      if (lista[i].anho == j || lista[i].anho == j2)
	{
	  result = 1;
	}
    }
  cout <<
    "\nque desea ver?\n1)Reporte de camas totales\n2)Reporte de camas ocupadas"
    << endl;
  cin >> opc;
  if (opc == 1)
    {
      for (int x = 1; x < 13; x++)
	{
	  cout << "\n\n";
	  if (x < 0)
	    {
	      cout << x << "/" << j << "  -> camas totales: " <<
		Promedio_Disponibilidad (j2, x, lista,
					 cantidad) << "  -> valor %: " << 100
		* (Promedio_Disponibilidad (j2, x, lista, cantidad) -
		   Promedio_Disponibilidad (j, x, lista,
					    cantidad)) /
		Promedio_Disponibilidad (j2, x, lista, cantidad) << endl;
	      cout << x << "/" << j2 << "  -> camas totales: " <<
		Promedio_Disponibilidad (j2, x, lista, cantidad) << endl;
	    }
	  else
	    {			//para cuando estan al reves.
	      cout << x << "/" << j << "  -> camas totales: " <<
		Promedio_Disponibilidad (j, x, lista,
					 cantidad) << "  -> VP%: " << 100 *
		(Promedio_Disponibilidad (j2, x, lista, cantidad) -
		 Promedio_Disponibilidad (j, x, lista,
					  cantidad)) /
		Promedio_Disponibilidad (j2, x, lista, cantidad) << endl;
	      cout << x << "/" << j2 << "  -> camas totales: " <<
		Promedio_Disponibilidad (j2, x, lista, cantidad) << endl;

	    }
	}
    }
  if (opc == 2)
    {
      for (int x = 1; x < 13; x++)
	{
	  cout << "\n\n";
	  if (x < 0)
	    {
	      cout << x << "/" << j << "  -> camas ocupadas: " <<
		Promedio_Camas_Ocupadas (j2, x, lista,
					 cantidad) << "  -> valor %: " << 100
		* (Promedio_Camas_Ocupadas (j2, x, lista, cantidad) -
		   Promedio_Camas_Ocupadas (j, x, lista,
					    cantidad)) /
		Promedio_Camas_Ocupadas (j2, x, lista, cantidad) << endl;
	      cout << x << "/" << j2 << "  -> camas ocupadas: " <<
		Promedio_Camas_Ocupadas (j2, x, lista, cantidad) << endl;
	    }
	  else
	    {
	      cout << x << "/" << j << "  -> camas ocupadas: " <<
		Promedio_Camas_Ocupadas (j, x, lista,
					 cantidad) << "  -> VP%: " << 100 *
		(Promedio_Camas_Ocupadas (j2, x, lista, cantidad) -
		 Promedio_Camas_Ocupadas (j, x, lista,
					  cantidad)) /
		Promedio_Camas_Ocupadas (j2, x, lista, cantidad) << endl;
	      cout << x << "/" << j2 << "  -> camas ocupadas: " <<
		Promedio_Camas_Ocupadas (j2, x, lista, cantidad) << endl;

	    }
	}
    }

}
