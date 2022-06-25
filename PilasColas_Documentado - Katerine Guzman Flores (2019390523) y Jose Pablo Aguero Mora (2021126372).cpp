// Tecnologico de Costa Rica - Laboratorio Pilas y Colas - Jose Pablo Aguero Mora (2021126372) - Katerine Guzman Flores (2019390523) - Prof: Victor Garro Abarca
// Pila_Cola.cpp: define el punto de entrada de la aplicación de consola.

// Se importan las librerías
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>


using namespace std;
//******************************************

typedef struct TArticulo // nueva estructura de tipo TArticulo. Se pueden crear variables anonimas de tipo TArticulo
{
	int Codigo;
	char Nombre[20];
	int Disponible;
	float Precio;
	TArticulo* Siguiente; // puntero que apunta al siguiente TArticulo
}*PtrTArticulo; // se puede usar como un puntero que apunta el primero de la lista de tipo TArticulo
				// se puede poner Ptr Auxiliar y luego asignarle un nuevo articulo. 
				//Ejemplo: Auxiliar = new(TArticulo)


//******************************************

int i;  //parametro global

// Recibe una lista ejemplo abarrotes, que es un parametro por referencia que tiene la forma tipo PtrTArticulo. Lo que se le haga al puntero lista se le asigna al puntero que se le envia de afuera
void InicializarInventario(PtrTArticulo& Lista)
{
	Lista = NULL; // puntero interno de lista apunta a null
}
// va matando el primer elemento de la lista
void DestruirInventario(PtrTArticulo& Lista) // se le pasa por referencia porque va a salir modificado
{
	PtrTArticulo Aux;
	Aux = Lista; // el auxiliar apunta al inicio de la lista
	while (Aux != NULL) // mientras el auxiliar apunte a alguien
	{
		Lista = Lista->Siguiente; // a lista lo ponemos a apuntar al segundo elemento
		delete(Aux); // ya que lista apunta al segundo podemos matar el primero
		Aux = Lista; // se limpia la referencia que tenia aux y lo dejamos apuntando al segundo
	}
}
PtrTArticulo CrearArticulo(int NCodigo, int NDisponible, float NPrecio)
{
	PtrTArticulo Pieza = new(TArticulo); // crea variable local pieza de tipo PtrTArticulo y se le asigna una declaracion de variable anonima con new 
	char buffer[5];

	// Asignacion de valores según cada ciclo
	Pieza->Codigo = NCodigo;
	Pieza->Disponible = NDisponible;
	Pieza->Precio = NPrecio;

	strcpy_s(Pieza->Nombre, "Pieza");
	_itoa_s(NCodigo, buffer, 10); // convertirlo a string 
	strcat_s(Pieza->Nombre, buffer); // concatenacion de nombre con numero. Ejemplo Pieza100

	Pieza->Siguiente = NULL; // De una vez ya tiene su propio puntero siguiente apuntando a null 
	return Pieza; // Pieza es local entonces ocupamos retornar donde está la direccion de la variable anonima (puntero)
}
void AgregarInicioInventario(PtrTArticulo& Lista, PtrTArticulo& Nuevo)
{	// enlace entre piezas o listas
	Nuevo->Siguiente = Lista; // nuevo elemento la variable anonima puntero siguiente ahora va a apuntar donde antes apuntaba lista
	Lista = Nuevo; // apunta donde apunta nuevo elemento
}
void AgregarFinalInventario(PtrTArticulo& Lista, PtrTArticulo& Nuevo)
{
	PtrTArticulo Aux; // Se inicializa un auxiliar puntero
	Aux = Lista; // Apunta al inicio de la lista
	if (Aux != NULL) // si hay al menos un elemento
	{    // auxuliar frena en el ultimo elemento antes de saltar a nulo
		// si el siguente puntero no es null
		while (Aux->Siguiente != NULL) // pregunta si esta en el ultimo nodo
		{
			Aux = Aux->Siguiente; // se le asigna el siguiente nodo
		}

		Aux->Siguiente = Nuevo; // si ya llegamos a null llegamos al ultimo elemento y se engancha al final
	}
	else // si la lista esta vacia
	{
		Lista = Nuevo; // aqui agrega Nuevo al "final" que es el inicio porque la lista esta vacia
	}


}
// Subrutina que se comporta como procedimiento, no devuelve nada y recibe parametro lista por referencia, aunque puede ser por valor porque no se va a modificar la lista, solo se recorre
void ListarInventario(PtrTArticulo& Lista)
{
	int Contador = 1;
	PtrTArticulo Aux; // variable local que servira para ir saltando de nodo en nodo
	Aux = Lista; // Apunta donde apunta lista(primer elemento)
	while (Aux != NULL) // pregunta si se salio de la lista o esta vacia
	{
		// se imprime la informacion de cada pieza
		printf(" %d ", Contador);
		printf("%d ", Aux->Codigo);
		printf("%s ", Aux->Nombre);
		printf(" %d ", Aux->Disponible);
		printf(" %f\n ", Aux->Precio);
		Aux = Aux->Siguiente; // se pasa al siguiente nodo
		Contador++;
	}
}

PtrTArticulo BuscarArticulo(PtrTArticulo& Lista, int cual)
{
	bool encontro = false; // tipo de dato booleano que se inicializa en false sino ha encontrado el articulo
	PtrTArticulo Aux; // puntero auxiliar para llevar el orden
	Aux = Lista; // se iguala lista para accesar posteriormente los datos

	while (!encontro == true && Aux != NULL) // si no se ha encontrado el elemento y no se ha llegado al final de la lista
	{
		if (Aux->Codigo == cual) // si el codigo coincide con el buscado se pone en true el booleano
			encontro = true;
		else
			Aux = Aux->Siguiente; // se avanza al siguiente elemento
	}
	return Aux;
}


// toma la lista que le pasen
void GuardarInventario(PtrTArticulo Lista) {
	FILE* archivo; // puntero de tipo file
	fopen_s(&archivo, "ARCHIVO.txt", "w+"); // comando para abrir archivo, con ese nombre, w+ se crea y se guarda la info
	if (NULL == archivo) { // si el archivo es vacio
		printf("No se pudo abrir el archivo."); // validacion
	}
	else {
		PtrTArticulo AUX = Lista; // se crea auxiliar que da direccion de lista
		while (AUX != NULL) { // mientras tenga un elemento se imprime 
			fprintf(archivo, "%i\n", AUX->Codigo); // codigo
			fprintf(archivo, "%s\n", AUX->Nombre); // nombre
			fprintf(archivo, "%i\n", AUX->Disponible); // disponibilidad
			fprintf(archivo, "%f\n", AUX->Precio); // precio
			AUX = AUX->Siguiente; // se va moviendo al siguiente elemento
		}


	}
	fclose(archivo); // se cierra el archivo
}

void CargarInventario(PtrTArticulo& Lista) {
	PtrTArticulo Nuevo; // me envia por cual elemnto va leyendo
	FILE* archivo; // puntero file
	fopen_s(&archivo, "ARCHIVO.txt", "r"); // abre el archivo y lo lee
	if (NULL == archivo) {
		printf("No se pudo abrir el archivo"); // valida
	}
	else {


		while (!feof(archivo)) { // mientras no sea el final del archivo, el ciclo se repite hasta que llegue a la ultima fila
			Nuevo = new(TArticulo); // nueva variable anonima que representa elemento TArticulo
			char Cadena[20];
			// fscan lee en el archivo
			fscanf_s(archivo, "%i\n", &Nuevo->Codigo); // se saca la direccion de codigo
			fscanf_s(archivo, "%s\n", Cadena, 20); // saca todo lo que esta en la linea
			fscanf_s(archivo, "%i\n", &Nuevo->Disponible);
			fscanf_s(archivo, "%f\n", &Nuevo->Precio);
			strcpy_s(Nuevo->Nombre, Cadena); // concatena cadena con nombre
			Nuevo->Siguiente = NULL; // apunta a null para que se vaya escribiendo uno por uno con el agregar inventario
			AgregarFinalInventario(Lista, Nuevo); // se agrega el ultimo elemento en orden

		}
	}
	fclose(archivo); // se cierra el archivo
}




// Pilas / LIFO
void Push(PtrTArticulo& Lista, PtrTArticulo Nuevo) { // Simplemente llama a la función AgregarInicioInventario
	AgregarInicioInventario(Lista, Nuevo); // Añade cada nodo al inicio de la lista
}
PtrTArticulo Top(PtrTArticulo& Lista) { // Devuelve el primer nodo de la lista (el tope de la pila)
	return Lista;
}
PtrTArticulo Pop(PtrTArticulo& Lista) { // Desvincula el nodo del tope de la pila
	PtrTArticulo Aux = Lista; // El puntero auxiliar apunta al inicio de la lista
	Lista = Lista->Siguiente; // Se le dice al puntero del inicio de la lista que apunte al segundo nodo
	Aux->Siguiente = NULL; // Al primer nodo se le asigna un valor de siguiente NULL
	return Aux; // Retorna la dirección al nodo extraído
}

// Colas / FIFO
void Encolar(PtrTArticulo& Lista, PtrTArticulo Nuevo) { // Simplemente llama a la función AgregarFinalInventario
	AgregarFinalInventario(Lista, Nuevo); // Añade cada nodo al final de la lista
}

PtrTArticulo Primero(PtrTArticulo& Lista) { // Devuelve el primer nodo de la lista (el tope de la lista)
	return Lista;
}
PtrTArticulo Descolar(PtrTArticulo& Lista) { // Tiene la misma función de Pop / Desvincula el nodo del tope de la pila
	PtrTArticulo Aux = Lista; // El puntero auxiliar apunta al inicio de la lista
	Lista = Lista->Siguiente; // Se le dice al puntero del inicio de la lista que apunte al segundo nodo
	Aux->Siguiente = NULL; // Al primer nodo se le asigna un valor de siguiente NULL
	return Aux; // Retorna la dirección al nodo extraído
}







void main(int argc, char* argv[])
{
	//************************************************************************
	PtrTArticulo Pila_Llantas; // referencia de tipo Tarticulo 
	PtrTArticulo Cola_Pasajeros; // referencia de tipo Tarticulo
	PtrTArticulo Nuevo; // referencia de tipo Tarticulo
	int i; // contador para los ciclos

	//************************************************************************	


	InicializarInventario(Pila_Llantas); // Se referencia lista a Null
	InicializarInventario(Cola_Pasajeros); // Se referencia lista a Null
	int opc;
	bool menu = true;
	while (menu) {
		system("CLS"); // se limpia pantalla y se imprime para elegir la opcion a ejecutar ya sea pila o cola
		cout << " ********* Menu de pila *********" << endl << endl;
		cout << "  1. Usar Pila" << endl;
		cout << "  2. Usar cola" << endl;
		cout << "  3. Salir" << endl;
		cout << endl << "	Digite la opcion: ";
		cin >> opc; // Se obtiene la opcion del teclado
		switch (opc) {
		case 1: {
			int opc;
			bool menu = true;
			while (menu) {
				system("CLS");
				cout << " ********* Submenu de pila *********" << endl << endl; // se muestran las opciones en el caso de pila
				cout << "  1. Push de 100 elementos" << endl; // agregar 100 elementos al inicio
				cout << "  2. Top" << endl;
				cout << "  3. Pop" << endl; // sacar elemento
				cout << "  4. Salir" << endl;
				cout << endl << "	Digite la opcion: "; // se pide nuevamente la opcion a elegir
				cin >> opc; // se pide opcion del teclado
				switch (opc) {
				case 1: {// INSERTANDO CON PUSH
					system("CLS");
					cout << "Haciendo Push de 100 elementos" << endl; // se muestra que se estan agregando los 100 elementos como se hacia con agregar al inicio

					for (i = 1; i <= 100; i++) // se hace un ciclo donde se agregan los 100 elementos
					{
						Nuevo = CrearArticulo(i, i, i); // primero se van creando los elementos
						Push(Pila_Llantas, Nuevo); // luego se van metiendo en la pila 
						cout << "Se acaba de hacer PUSH, el Top de la Pila ahora es: " << endl << Top(Pila_Llantas)->Codigo << endl; // se imprime el top de la lista en pila
					}
					system("pause");
					break;
				}
				case 2: {// PREGUNTANDO POR EL TOP
					system("CLS");
					if (Top(Pila_Llantas) != NULL) // si no ha llegado al final del documento
						cout << "El Top de la Pila es: " << endl << Top(Pila_Llantas)->Codigo << endl; // utiliza la funcion de top pilas e imprime en pantalla el elemento que se encuentra mas arriba de la lista
					else
						cout << "El Top de la Pila es: NULO " << endl; // en caso de que sea nulo envia el mensaje correspondiente

					system("pause"); // espera por tecla
					break;
				}
				case 3: { //SACANDO CON POP
					system("CLS");
					PtrTArticulo Aux = Pop(Pila_Llantas); // Se crea variable auxiliar que es el elemento que devuelve al hacer return en pop y se ejecuta la funcion
					if (Top(Pila_Llantas) != NULL) // si no se ha llegado al final de la lista
						cout << "Se acaba de hacer POP, el Top de la Pila ahora es: " << endl << Top(Pila_Llantas)->Codigo << endl; // se imprime el primer elemento despues de haber hecho el pop
					else
						cout << "Se acaba de hacer POP, el Top de la Pila ahora es:  NULO " << endl; // mensaje de nulo si ya se llego al final de la lista

					system("pause");
					break;
				}
				case 4: {// SALIENDO Y DEVOLVIENDO MEMORIA DINAMICA
					system("CLS"); // limpia pantalla
					menu = false; // Se sale del ciclo
					system("CLS");
					cout << "Liberando memoria ... " << endl << endl << endl; // imprime liberacion de memoria
					DestruirInventario(Pila_Llantas); // se van liberando las referencias una a una hasta que todo quede limpio
					system("Pause");
					break;
				}
				}
			}
			system("pause");
			break;
		}
		case 2: { // caso que se haya elegido ejecutar el menu por cola 
			int opc;
			bool menu = true;
			while (menu) {
				system("CLS");
				cout << " ********* Submenu de cola *********" << endl << endl; // Se indican las opciones que se pueden ejecutar
				cout << "  1. Encolar" << endl; // agregar elemento al final
				cout << "  2. Primero" << endl; // indica cual es el primer elemento en la lista
				cout << "  3. Descolar" << endl; // se saca el elemento
				cout << "  4. Salir" << endl;
				cout << endl << "	Digite la opcion: ";
				cin >> opc; // obtiene la opcion presionada
				switch (opc) {
				case 1: {// ENCOLAR
					system("CLS");
					cout << "Haciendo Encolar de 50 elementos" << endl; 

					for (i = 1; i <= 50; i++) // Se van agregando los elementos del 1 al 50 en este ciclo
					{
						Nuevo = CrearArticulo(i, i, i); // se crean loe elementos primero
						Encolar(Cola_Pasajeros, Nuevo); // se van incluyendo en la lista de cola uno a uno
						cout << "Se acaba de hacer ENCOLAR al final de la Cola de : " << Nuevo->Codigo << endl; // se imprime cual se acaba de encolar
					}

					system("pause"); // espera tecla por usuario
					break;
				}
				case 2: {// PRIMERO
					system("CLS");
					cout << "El primero que va a ser atendido de la cola es : " << Primero(Cola_Pasajeros)->Codigo << endl; // se envia el primero de la lista en el orden de llegada
					system("pause"); // espera tecla por usuario
					break;
				}
				case 3: {// DESCOLAR
					system("CLS");

					PtrTArticulo Aux = Descolar(Cola_Pasajeros); // se crea variable auxiliar donde se guarda la referencia el elemento sacado de la lista

					if (Primero(Cola_Pasajeros) != NULL)
						cout << "Se acaba de hacer DESCOLAR, el nuevo primero  de la Cola ahora es: " << endl << Primero(Cola_Pasajeros)->Codigo << endl; // se indica cual es el primero de la lista despues de sacarlo
					else
						cout << "Se acaba de hacer DESCOLAR, el primero de la Cola ahora es:  NULO " << endl;

					system("pause"); // espera tecla por usuario
					break;
				}
				case 4: {// SALIENDO Y DEVOLVIENDO MEMORIA DINAMICA
					menu = false;
					system("CLS");
					cout << "Liberando memoria ... " << endl << endl << endl;
					DestruirInventario(Cola_Pasajeros); // se van liberando uno a uno las referencias de la lista de cola
					system("Pause"); // espera tecla por usuario
					break;
				}
				}
			}
			system("pause"); // espera tecla por usuario
			break;
		}
		case 3: {
			menu = false;
			system("CLS");
			cout << "Opcion 5: saliendo . . ." << endl << endl << endl; // envia mensaje de saliendo del sistema
			cout << "ADIOS!!!" << endl; // imprime adios
			system("Pause"); // espera tecla por usuario
		}
		}
	}
}
/*  ************************************************* Al compilarlo se muestra lo siguiente ******************************************************
 ********* Menu de pila *********

  1. Usar Pila
  2. Usar cola
  3. Salir

		Digite la opcion:

 ********* Submenu de pila *********

  1. Push de 100 elementos
  2. Top
  3. Pop
  4. Salir

		Digite la opcion:

 ********* Submenu de cola *********

  1. Encolar
  2. Primero
  3. Descolar
  4. Salir

		Digite la opcion:

*/