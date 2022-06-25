// Tecnologico de Costa Rica - Estructuras de Datos Gr02 - Laboratorio3 - Extra Lista Doble - Jose Pablo Aguero Mora 2021126372 - Katerine Guzman Flores 2019390523 - Prof: Victor Garro Abarca

#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <string>
#include <stdio.h>
#include <iostream>

using namespace std;


//LISTA ENLAZADA DOBLE : tienen dos punteros para recorrer la lista de adelante a atras o viceversa

// Se crea estructura con los valores para cada variable anónima
typedef struct TArticulo {
	int Codigo;
	char Nombre[20];
	int Disponible;
	double Precio;
	TArticulo* Anterior; // se crea un puntero a nodo predecesor
	TArticulo* Siguiente; // se crea un puntero a nodo sucesor 
}X;
typedef TArticulo* PtrTArticulo;



void InicializarInventario(PtrTArticulo& Lista) {
	Lista = NULL; // para inicializar el inventario se apunta el primer elemento a Null, porque está vacía
}

PtrTArticulo CrearArticulo(int NCodigo, int NDisponible, double NPrecio) {
	PtrTArticulo Nuevo = new(TArticulo); // Se crea un nuevo puntero de tipo tArticulo
	char buffer[5];

	// se asignan los valores que se van introduciendo
	Nuevo->Codigo = NCodigo;
	Nuevo->Disponible = NDisponible;
	Nuevo->Precio = NPrecio;


	strcpy_s(Nuevo->Nombre, "Pieza"); // se le asigna el nombre de Pieza
	_itoa_s(NCodigo, buffer, 10); // se convierte codigo a string
	strcat_s(Nuevo->Nombre, buffer); // se concatena el nombre

	Nuevo->Anterior = NULL; // se apuntan ambos punteros a null
	Nuevo->Siguiente = NULL;
	return Nuevo; // se retorna el puntero con la información ingresada
}

void AgregarFinalInventario(PtrTArticulo& Lista, PtrTArticulo& Nuevo) {
	PtrTArticulo Aux; // puntero aux para ir recorriendo la lista
	Aux = Lista;
	if (Aux == NULL) { // si no hay elementos
		Lista = Nuevo; // a lista se le asigna el nuevo elemento
	}
	else {
		while (Aux->Siguiente != NULL) { // mientras no se llegue al ultimo nodo 
			Aux = Aux->Siguiente; // se le asigna el siguiente nodo
		}
		Aux->Siguiente = Nuevo; // si llega al final se hace el enganche al nodo siguiente
		Nuevo->Anterior = Aux; // se hace el enganche al nodo anterior
	}
}


void AgregarInicioInventario(PtrTArticulo& Lista, PtrTArticulo& Nuevo) {


	if (Lista == NULL) { // si no hay elementos 
		Lista = Nuevo; // se agrega el primer elemento
	}
	else
	{
		Nuevo->Siguiente = Lista; // puntero siguiente apunta donde estaba lista
		Lista->Anterior = Nuevo; // nuevo elemento ahora será el anterior
		Lista = Nuevo; // apunta donde esta nuevo elemento
	}
}

void Listar_Inicio_a_Final(PtrTArticulo& Lista) {
	PtrTArticulo Aux;
	Aux = Lista;
	while (Aux != NULL) { // si no se ha llegado al final de los nodos
		cout << "["; // se imprime [
		cout << Aux->Codigo << ","; // se agrega el codigo, y una coma
		cout << Aux->Nombre << ","; // se agrega el nombre y una coma
		cout << Aux->Precio << "] - "; // se agrega el precio + ] y un guion
		Aux = Aux->Siguiente; // se pasa al siguiente nodo
	}
	system("pause"); // se pide presionar una tecla
}

void Listar_Final_a_Inicio(PtrTArticulo& Lista) {
	PtrTArticulo Aux;
	Aux = Lista;
	while (Aux->Siguiente != NULL)  Aux = Aux->Siguiente; // mientras no se haya llegado al final, se pasa al siguiente nodo

	while (Aux != NULL) { // si hay al menos un elemento se despliegan los valores del articulo dentro de parentesis cuadrados y separados por comas
		cout << "[";
		cout << Aux->Codigo << ",";
		cout << Aux->Nombre << ",";
		cout << Aux->Precio << "] - ";
		Aux = Aux->Anterior; // se pasa al nodo anterior
	}
	system("pause"); // se pide tecla para continuar
}



void DestruirInventario(PtrTArticulo& Lista)
{
	PtrTArticulo Aux; // puntero para recorrer cada nodo
	Aux = Lista; // el auxiliar apunta al inicio del inventario
	while (Aux != NULL) // mientras aun exista al menos un elemento
	{
		Lista = Lista->Siguiente; // se pasa lista al siguiente nodo
		delete(Aux); // se borra la referencia al nodo anterior
		Aux = Lista; // lo dejamos apuntando al segundo elemento
	}
}

// Función borrar
void BorrarArticulo(PtrTArticulo& Lista, int codigoArticulo)
{
	bool encontro = false; // tipo de dato booleano que se inicializa en false sino ha encontrado el articulo
	PtrTArticulo Aux; // puntero auxiliar para llevar el orden
	Aux = Lista; // se iguala lista para accesar posteriormente los datos

	while (!encontro == true && Aux != NULL) // si no se ha encontrado el elemento y no se ha llegado al final de la lista
	{
		if (Aux->Codigo == codigoArticulo) // si el codigo coincide con el buscado se pone en true el booleano
			encontro = true;
		else
			Aux = Aux->Siguiente; // se avanza al siguiente elemento
	}
	// Bypass
	// Casos donde se apunta el nodo
	if (Aux == Lista) { // Es el primer nodo
		if (Aux->Anterior) Lista = Aux->Anterior;
		else Lista = Aux->Siguiente;
	}

	if (Aux->Anterior) { // NO primer nodo
		Aux->Anterior->Siguiente = Aux->Siguiente;
	}

	if (Aux->Siguiente) { // NO ultimo nodo
		Aux->Siguiente->Anterior = Aux->Anterior;
	}

	delete(Aux); // Se elimina el nodo una vez que se han modificado sus vínculos
}


void main() {
	// creacion  de variables
	PtrTArticulo Nuevo;
	PtrTArticulo Abarrotes;

	// Carga en la lista codigos del 1 al 100, luego los lista del inicio al final y luego del final al inicio.  Finalmente destruye la lista.
	//INICIO PILOTO AGREGANDO AL INICIO EN LISTA DOBLE
	InicializarInventario(Abarrotes);

	for (int i = 1; i <= 100; i++) // creay y agrega elementos de abarrotes del 1 al 100
	{
		Nuevo = CrearArticulo(i, i, i);
		AgregarInicioInventario(Abarrotes, Nuevo);
	}

	system("pause"); // pide una tecla
	system("cls"); // se limpia pantalla
	cout << "Listando elementos del Inicio al Final de una lista creada con insercion al inicio" << endl;
	Listar_Inicio_a_Final(Abarrotes); // se muestra los elementos del 100 al 1
	cout << "Listando elementos del Final al Inicio de una lista creada con insercion al inicio" << endl;

	BorrarArticulo(Abarrotes, 55); // Prueba de borrar el artículo 55

	Listar_Final_a_Inicio(Abarrotes); // se mustran los elementos del 1 al 100
	DestruirInventario(Abarrotes); // se borra el inventario de memoria
	//FIN PILOTO AGREGANDO AL INICIO EN LISTA DOBLE

	//INICIO PILOTO AGREGANDO AL FINAL EN LISTA DOBLE
	InicializarInventario(Abarrotes);

	for (int i = 500; i <= 600; i++) // se imprimen los numros entre 500 y 600
	{
		Nuevo = CrearArticulo(i, i, i);
		AgregarFinalInventario(Abarrotes, Nuevo);
	}

	system("pause");
	system("cls");
	cout << "Listando elementos del Inicio al Final de una lista creada con insercion al final" << endl;
	Listar_Inicio_a_Final(Abarrotes); // se imprime del 600 al 500
	cout << "Listando elementos del Final al Inicio de una lista creada con insercion al final" << endl;
	Listar_Final_a_Inicio(Abarrotes); // se imprime del 500 al 600
	DestruirInventario(Abarrotes); // se elimina nuevamente el inventario
	//FIN PILOTO AGREGANDO AL FINAL EN LISTA DOBLE

}