// Tecnologico de Costa Rica - Laboratorio listas enlazadas - Jose Pablo Aguero Mora - Katerine Guzman Flores
// Importación de librerías
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <cctype> 
#include <cstdlib>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include <stdlib.h> 
#include <math.h>
#include <sstream>
#include <random>
using namespace std;

//T_Votante
typedef struct T_Votante { //Se define la estructura para los votantes
	char cedula[10]; // Se establecen las variables char que almacenarán los datos separados del archivo txt y sus respectivos rangos de caracteres
	char codelec[7];
	char sexo;
	char fecha[9];
	char numjun[6];
	char nombre[31];
	char papellido[27];
	char sapellido[27];
	T_Votante* PtrSiguiente; // Se indica un puntero que se dirige al siguiente nodo de la lista (a su dirección en memoria)
}*PtrT_Votante; // Puntero que apunta el primero de la lista de tipo T_Votante

//Funcion para agregar un votante, recibe como parametro la lista de votantes y la LINEA DE TEXTO del padron electoral
//extrae cada uno de los atributos de la linea y los almacena en un nodo de la lista de votantes
void agregarvotante(PtrT_Votante& ListaV, char agregado[118]) {
	PtrT_Votante Aux = new (T_Votante); // Se usa el puntero como un auxiliar que apunta a una nueva variable anónima de tipo T_Votante
	Aux->PtrSiguiente = ListaV; // Se le asigna a siguiente el primer elemento al que apunta en la lista
	ListaV = Aux; // Al primer nodo apuntado de la lista se le asigna la dirección del nuevo nodo

	for (int ce = 0; ce < 9; ce++) { // Ciclo que toma desde el caracter 0 hasta el caracter 9. Lo almacena en cedula
		ListaV->cedula[ce] = agregado[ce]; // Se agrega caracter por caracter
	}
	ListaV->cedula[9] = '\0'; // String terminator

	for (int co = 10; co < 16; co++) { // Ciclo que toma desde el caracter 10 hasta el caracter 16. Lo almacena en codelec
		ListaV->codelec[co - 10] = agregado[co];
	}
	ListaV->codelec[6] = '\0'; // String terminator

	ListaV->sexo = agregado[17]; // Se agrega únicamente el caracter 17 al valor de sexo. Lo almacena en sexo


	for (int fe = 19; fe < 27; fe++) { // Ciclo que toma desde el caracter 19 hasta el caracter 27. Lo almacena en fecha
		ListaV->fecha[fe - 19] = agregado[fe];
	}
	ListaV->fecha[8] = '\0'; // String terminator

	for (int nu = 28; nu < 33; nu++) { // Ciclo que toma desde el caracter 28 hasta el caracter 33. Lo almacena numjun
		ListaV->numjun[nu - 28] = agregado[nu];
	}
	ListaV->numjun[5] = '\0'; // String terminator

	for (int nom = 34; nom < 64; nom++) { // Ciclo que toma desde el caracter 34 hasta el caracter 64. Lo almacena en nombre
		ListaV->nombre[nom - 34] = agregado[nom];
	}
	ListaV->nombre[30] = '\0'; // String terminator

	for (int pa = 65; pa < 91; pa++) { // Ciclo que toma desde el caracter 65 hasta el caracter 91. Lo almacena en papellido
		ListaV->papellido[pa - 65] = agregado[pa];
	}
	ListaV->papellido[26] = '\0'; // String terminator

	for (int sa = 92; sa < 118; sa++) { // Ciclo que toma desde el caracter 92 hasta el caracter 118. Lo almacena en sapellido
		ListaV->sapellido[sa - 92] = agregado[sa];
	}
	ListaV->sapellido[26] = '\0'; // String terminator

}

//Funcion para cargar los votantes, se encarga de tomar cada una de las lineas
//directo del archivo de texto y enviarlo a la funci�n encargada de extraer cad uno
// de los datos e incorporarlos en un nodo de la lista.
void CargarVotantes(PtrT_Votante& ListaV) {
	int cont = 1;
	time_t inicio, fin; // Se declaran variables de tipo tiempo para medir la duración del proceso
	inicio = time(NULL); // Declaración de variable para medir el tiempo inicial
	FILE* archivo; // Se declara un puntero para manejar los datos del archivo
	fopen_s(&archivo, "PADRON_COMPLETO.txt", "r"); // Se abre el txt con la función de leer ("r")
	if (NULL == archivo) { // Condición en caso de que no exista el archivo o no se pueda abrir
		printf("No se pudo abrir el archivo");
	}
	else { // Caso en el que sí existe el archivo txt
		char agregado[119]; // Se crea una variable de tipo char que contendrá cada línea del archivo txt (una por una)
		while (fgets(agregado, 119, archivo) != NULL) { // Ciclo para recorrer todas las líneas del txt y cargar datos en variable agregado
			if (cont % 2 != 0) { // Esta instrucción existe por una ineficiencia del código que leía de forma duplicada a los votantes / Esto evita que se repitan
				agregarvotante(ListaV, agregado); // Utiliza los datos cargador en agregado para pasarlos como parámetro a agregarvotante()
			}
			cont++; // Aumenta el contador
		}
		fclose(archivo); // Cierra el uso de la variable archivo al txt
	}

	fin = time(NULL); // Declaración de variable para medir el tiempo final
	cout << "----------------------------Padron cargado--------------------------------" << endl;
	printf("\nEl cargado del padron ha tardado : %f segundos.\n", difftime(fin, inicio)); // Se imprime la diferencia entre el tiempo inicial y el tiempo final
	cout << "----------------------------Padron cargado--------------------------------" << endl;
	system("pause");
}


//Funcion para liberar los votantes en estructuras de memoria dinamica de la lista enlazada hasta dejar la lista en NULL

void LiberarVotantes(PtrT_Votante& ListaV) {
	PtrT_Votante Aux = ListaV; // Se crea una variable auxiliar para recorrer la lista enlazada
	time_t inicio, fin; // Se declaran variables de tipo tiempo para medir la duración del proceso

	inicio = time(NULL); // Declaración de variable para medir el tiempo inicial

	while (Aux != NULL) { // Ciclo que se repite hasta que la lista enlazada no tenga más nodos
		ListaV = ListaV->PtrSiguiente; // Apunta al siguiente nodo en la lista
		delete(Aux); // Elimina el nodo
		//Globalfree(Aux);
		Aux = ListaV; // Actualiza la dirección del auxiliar (siguiente nodo)
	}

	fin = time(NULL); // Declaración de variable para medir el tiempo final

	cout << "----------------------------Padron liberado--------------------------------" << endl;
	printf("\nLa liberacion del padron ha tardado : %f segundos.\n", difftime(fin, inicio)); // Se imprime la diferencia entre el tiempo inicial y el tiempo final
	cout << "----------------------------Padron liberado--------------------------------" << endl;
	system("pause");
}


//Funci�n para inicializar la lista de votantes
void inicializarvotantes(PtrT_Votante& ListaV) {
	ListaV = NULL; // Inicializa la lista enlazada. El puntero principal apunta a NULL
}

PtrT_Votante BuscarVotante(PtrT_Votante& Lista, char cual[9])
{
	bool encontro = false; // Se establece un flag booleano en false
	PtrT_Votante Aux; // Se inicializa un puntero
	Aux = Lista; // Se le asigna la dirección del primer elemento en la lista

	while ((!encontro == true) && (Aux != NULL)) // Ciclo que recorre toda la lista hasta que encuentre el elemento o termine la lista
	{
		if (strncmp(Aux->cedula, cual, 9) == 0) // Condición en donde se encuentra el elemento
			encontro = true; // Cambia la variable flag a true
		else
			Aux = Aux->PtrSiguiente; // El otro caso donde no lo encuentra en el nodo actual entonces pasa a buscar al siguiente
	}
	return Aux; // Retorna la dirección del último nodo analizado, es decir, donde se encontró el elemento buscado
}



void main() {
	// bool realizado = false;
	// bool ciclo = true;
	// int opcion = 0;
	PtrT_Votante ListaV; // Se declara una variable puntero que apunta al tipo de struct creado al inicio del código
	inicializarvotantes(ListaV); // Se llama a la función que genera la estructura inicial de la lista
	cout << "Por favor espere mientras se carga el Padron" << endl;
	CargarVotantes(ListaV); // Llama a la función para leer el archivo txt y crear todos los nodos respectivos dentro de la lista enlazada
	char buscado[] = "118480918"; // Se define una variable estática que tiene el objetivo de ser el elemento buscado maás adelante
	PtrT_Votante Encontrado = NULL; // Se inicializa el puntero Encontrado apuntando a NULL
	Encontrado = BuscarVotante(ListaV, buscado); // Llama a la función BuscarVotante con el objetivo de guardar la dirección respectiva en Encontrado
	if (Encontrado != NULL) { // Condición para cuando se encontró el votante buscado
		cout << endl << "Encontre' al Votante!! " << endl << endl;

		cout << "Ce'dula: " << Encontrado->cedula << endl;
		cout << "Nombre: " << Encontrado->nombre << endl;
		cout << "Primer Apellido: " << Encontrado->papellido << endl;
		cout << "Segundo Apellido: " << Encontrado->sapellido << endl;
		cout << "Sexo: " << Encontrado->sexo << endl;
		cout << "Fecha: " << Encontrado->fecha << endl;
		cout << "Co'digo Electoral:  " << Encontrado->codelec << endl;
		cout << "Nu'mero Junta: " << Encontrado->numjun << endl;
	}
	else
		cout << " No se encontro al votante !!! " << endl; // Condición para cuando no se encontró el votante buscado

	LiberarVotantes(ListaV); // Se llama a la función LiberarVotantes para limpiar o eliminar todos los nodos de la lista

	cout << "Finalizado" << endl;

	system("pause");
}

// ¿Cuánto dura cargando?: La carga del padrón duró 14 segundos. La liberación de los votantes duró 0 segundos
// ¿Que pasaría si agrega al final?: Se podría haber usado la misma estrategia pero sería más eficiente en el ordenamiento de los datos
// En este contexto, ¿cuál sería una mejora a la función agregar al final?: Cambiar el sistema de carga de votantes donde se lee cada uno de ellos de forma duplicada


/* Salida del programa : 
Por favor espere mientras se carga el Padron
----------------------------Padron cargado--------------------------------

El cargado del padron ha tardado : 14.000000 segundos. (Cargar)
----------------------------Padron cargado--------------------------------
Presione una tecla para continuar . . .

Encontre' al Votante!! (Buscar)

Ce'dula: 118480918
Nombre: JOSE PABLO
Primer Apellido: AGUERO
Segundo Apellido: MORA
Sexo:
Fecha: 20300720
Co'digo Electoral:  119011
Nu'mero Junta: 00000
----------------------------Padron liberado--------------------------------

La liberacion del padron ha tardado : 0.000000 segundos. (Liberar)
----------------------------Padron liberado--------------------------------
Presione una tecla para continuar . . . */
