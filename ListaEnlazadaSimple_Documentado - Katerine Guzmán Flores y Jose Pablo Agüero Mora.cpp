// Tecnologico de Costa Rica - Laboratorio listas enlazadas - Jose Pablo Aguero Mora (2021126372) - Katerine Guzman Flores (2019390523) - Prof: Victor Garro Abarca
// ListaSimple_Documentado

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



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
// Recibe una lista que va a ser modifica por lo tanto es un parametro por referencia de tipo PtrArticulo
// Ademas se recibe un puntero llamado nuevo que tambien es un parametro por referencia de tipo PtrArticulo
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



void main(int argc, char* argv[])
{
	//************************************************************************
	// nombres en plural son colecciones
	PtrTArticulo Llantas; // se va a tener n elementos en una coleccion
	PtrTArticulo Abarrotes;
	PtrTArticulo Nuevo; // elemento individual a los que puede apuntar
	PtrTArticulo Prueba;

	//************************************************************************	
	InicializarInventario(Abarrotes); // se le da un valor inicial a la coleccion abarrotes de 100 hasta 200

	for (int i = 100; i <= 200; i++)
	{
		Nuevo = CrearArticulo(i, i, i); // Lo que me devuelve el return de pieza se le asigna al puntero nuevo
		AgregarInicioInventario(Abarrotes, Nuevo); // Al inicio de abarrotes se le agrega nuevo. Todo se va metiendo al inicio pero al lista queda invertida. Va de derecha(primer elemento) a izquierda(ultimo elemmento)
	}
	// se hace una prueba con la lista de abarrotes
	GuardarInventario(Abarrotes); // Llama a la función GuardarInventario
	ListarInventario(Abarrotes); // Llama a la función ListarInventario
	DestruirInventario(Abarrotes); // Llama a la función DestruirInventario
	system("cls");
	//*************************PRUEBA DE CARGAR********************************
	InicializarInventario(Prueba);
	CargarInventario(Prueba);
	ListarInventario(Prueba);
	system("pause");
	DestruirInventario(Prueba);
	//************************************************************************
	InicializarInventario(Abarrotes);
	for (i = 200; i <= 300; i++)
	{
		// Se crea un nuevo espacio en memoria y se hace un nuevo nodo y se le inicializan los datos, incluso al puntero siguiente se le da un valor
		// Una vez que ese nuevo nodo esta listo a traves de la funcion crear articulo, nos va a devolver el puntero a esa variable anonima y se lo va a devolver al puntero llamado nuevo
		// Con el puntero nuevo apuntando a esa variable anonima, se invoca a la funcion Agregar al Inicio del inventario y agrega al inicio de la lista pero de forma invertida
		Nuevo = CrearArticulo(i, i, i); // se le pasa codigo, cantidad, y precio
		AgregarFinalInventario(Abarrotes, Nuevo); // se le pasa el puntero de la variable anonima recien creada en TArticulo
	}
	ListarInventario(Abarrotes);
	DestruirInventario(Abarrotes);




	//************************************************************************	
	InicializarInventario(Llantas);
	for (i = 100; i <= 200; i++)
	{
		Nuevo = CrearArticulo(i, i, i);
		AgregarInicioInventario(Llantas, Nuevo);
	}
	ListarInventario(Llantas);
	DestruirInventario(Llantas);

	//************************************************************************
	InicializarInventario(Llantas);
	for (i = 200; i <= 300; i++)
	{
		Nuevo = CrearArticulo(i, i, i);
		AgregarFinalInventario(Llantas, Nuevo);
	}
	ListarInventario(Llantas);
	DestruirInventario(Llantas);


	//************************ Prueba de BuscarArticulo ************************************************
	ListarInventario(Abarrotes);
	Prueba = BuscarArticulo(Abarrotes, 150); // Se llama a la función BuscarArticulo con los parámetros respectivos, la dirección resultante se guarda en Prueba

	if (Prueba != NULL) // Condicional para mostrar resultado de búsqueda
		printf("%i", Prueba->Disponible);
	else
		printf("no encontrado !!");

	Prueba = BuscarArticulo(Abarrotes, 300); // Prueba 2

	if (Prueba != NULL) // Condicional para mostrar resultado de búsqueda
		printf("%i", Prueba->Disponible);
	else
		printf("no encontrado !!");
}

/* En consola se muestran los datos, segun codigo, nombre, precio, disponibilidad
 1 200 Pieza200  200  200.000000
  2 199 Pieza199  199  199.000000
  3 198 Pieza198  198  198.000000
  4 197 Pieza197  197  197.000000
  5 196 Pieza196  196  196.000000
  6 195 Pieza195  195  195.000000
  7 194 Pieza194  194  194.000000
  8 193 Pieza193  193  193.000000
  9 192 Pieza192  192  192.000000
  10 191 Pieza191  191  191.000000
  11 190 Pieza190  190  190.000000
  12 189 Pieza189  189  189.000000
  13 188 Pieza188  188  188.000000
  14 187 Pieza187  187  187.000000
  15 186 Pieza186  186  186.000000
  16 185 Pieza185  185  185.000000
  17 184 Pieza184  184  184.000000
  18 183 Pieza183  183  183.000000
  19 182 Pieza182  182  182.000000
  20 181 Pieza181  181  181.000000
  21 180 Pieza180  180  180.000000
  22 179 Pieza179  179  179.000000
  23 178 Pieza178  178  178.000000
  24 177 Pieza177  177  177.000000
  25 176 Pieza176  176  176.000000
  26 175 Pieza175  175  175.000000
  27 174 Pieza174  174  174.000000
  28 173 Pieza173  173  173.000000
  29 172 Pieza172  172  172.000000
  30 171 Pieza171  171  171.000000
  31 170 Pieza170  170  170.000000
  32 169 Pieza169  169  169.000000
  33 168 Pieza168  168  168.000000
  34 167 Pieza167  167  167.000000
  35 166 Pieza166  166  166.000000
  36 165 Pieza165  165  165.000000
  37 164 Pieza164  164  164.000000
  38 163 Pieza163  163  163.000000
  39 162 Pieza162  162  162.000000
  40 161 Pieza161  161  161.000000
  41 160 Pieza160  160  160.000000
  42 159 Pieza159  159  159.000000
  43 158 Pieza158  158  158.000000
  44 157 Pieza157  157  157.000000
  45 156 Pieza156  156  156.000000
  46 155 Pieza155  155  155.000000
  47 154 Pieza154  154  154.000000
  48 153 Pieza153  153  153.000000
  49 152 Pieza152  152  152.000000
  50 151 Pieza151  151  151.000000
  51 150 Pieza150  150  150.000000
  52 149 Pieza149  149  149.000000
  53 148 Pieza148  148  148.000000
  54 147 Pieza147  147  147.000000
  55 146 Pieza146  146  146.000000
  56 145 Pieza145  145  145.000000
  57 144 Pieza144  144  144.000000
  58 143 Pieza143  143  143.000000
  59 142 Pieza142  142  142.000000
  60 141 Pieza141  141  141.000000
  61 140 Pieza140  140  140.000000
  62 139 Pieza139  139  139.000000
  63 138 Pieza138  138  138.000000
  64 137 Pieza137  137  137.000000
  65 136 Pieza136  136  136.000000
  66 135 Pieza135  135  135.000000
  67 134 Pieza134  134  134.000000
  68 133 Pieza133  133  133.000000
  69 132 Pieza132  132  132.000000
  70 131 Pieza131  131  131.000000
  71 130 Pieza130  130  130.000000
  72 129 Pieza129  129  129.000000
  73 128 Pieza128  128  128.000000
  74 127 Pieza127  127  127.000000
  75 126 Pieza126  126  126.000000
  76 125 Pieza125  125  125.000000
  77 124 Pieza124  124  124.000000
  78 123 Pieza123  123  123.000000
  79 122 Pieza122  122  122.000000
  80 121 Pieza121  121  121.000000
  81 120 Pieza120  120  120.000000
  82 119 Pieza119  119  119.000000
  83 118 Pieza118  118  118.000000
  84 117 Pieza117  117  117.000000
  85 116 Pieza116  116  116.000000
  86 115 Pieza115  115  115.000000
  87 114 Pieza114  114  114.000000
  88 113 Pieza113  113  113.000000
  89 112 Pieza112  112  112.000000
  90 111 Pieza111  111  111.000000
  91 110 Pieza110  110  110.000000
  92 109 Pieza109  109  109.000000
  93 108 Pieza108  108  108.000000
  94 107 Pieza107  107  107.000000
  95 106 Pieza106  106  106.000000
  96 105 Pieza105  105  105.000000
  97 104 Pieza104  104  104.000000
  98 103 Pieza103  103  103.000000
  99 102 Pieza102  102  102.000000
  100 101 Pieza101  101  101.000000
  101 100 Pieza100  100  100.000000
  101 100 Pieza100  100  100.000000
  1 200 Pieza200  200  200.000000
  2 201 Pieza201  201  201.000000
  3 202 Pieza202  202  202.000000
  4 203 Pieza203  203  203.000000
  5 204 Pieza204  204  204.000000
  6 205 Pieza205  205  205.000000
  7 206 Pieza206  206  206.000000
  8 207 Pieza207  207  207.000000
  9 208 Pieza208  208  208.000000
  10 209 Pieza209  209  209.000000
  11 210 Pieza210  210  210.000000
  12 211 Pieza211  211  211.000000
  13 212 Pieza212  212  212.000000
  14 213 Pieza213  213  213.000000
  15 214 Pieza214  214  214.000000
  16 215 Pieza215  215  215.000000
  17 216 Pieza216  216  216.000000
  18 217 Pieza217  217  217.000000
  19 218 Pieza218  218  218.000000
  20 219 Pieza219  219  219.000000
  21 220 Pieza220  220  220.000000
  22 221 Pieza221  221  221.000000
  23 222 Pieza222  222  222.000000
  24 223 Pieza223  223  223.000000
  25 224 Pieza224  224  224.000000
  26 225 Pieza225  225  225.000000
  27 226 Pieza226  226  226.000000
  28 227 Pieza227  227  227.000000
  29 228 Pieza228  228  228.000000
  30 229 Pieza229  229  229.000000
  31 230 Pieza230  230  230.000000
  32 231 Pieza231  231  231.000000
  33 232 Pieza232  232  232.000000
  34 233 Pieza233  233  233.000000
  35 234 Pieza234  234  234.000000
  36 235 Pieza235  235  235.000000
  37 236 Pieza236  236  236.000000
  38 237 Pieza237  237  237.000000
  39 238 Pieza238  238  238.000000
  40 239 Pieza239  239  239.000000
  41 240 Pieza240  240  240.000000
  42 241 Pieza241  241  241.000000
  43 242 Pieza242  242  242.000000
  44 243 Pieza243  243  243.000000
  45 244 Pieza244  244  244.000000
  46 245 Pieza245  245  245.000000
  47 246 Pieza246  246  246.000000
  48 247 Pieza247  247  247.000000
  49 248 Pieza248  248  248.000000
  50 249 Pieza249  249  249.000000
  51 250 Pieza250  250  250.000000
  52 251 Pieza251  251  251.000000
  53 252 Pieza252  252  252.000000
  54 253 Pieza253  253  253.000000
  55 254 Pieza254  254  254.000000
  56 255 Pieza255  255  255.000000
  57 256 Pieza256  256  256.000000
  58 257 Pieza257  257  257.000000
  59 258 Pieza258  258  258.000000
  60 259 Pieza259  259  259.000000
  61 260 Pieza260  260  260.000000
  62 261 Pieza261  261  261.000000
  63 262 Pieza262  262  262.000000
  64 263 Pieza263  263  263.000000
  65 264 Pieza264  264  264.000000
  66 265 Pieza265  265  265.000000
  67 266 Pieza266  266  266.000000
  68 267 Pieza267  267  267.000000
  69 268 Pieza268  268  268.000000
  70 269 Pieza269  269  269.000000
  71 270 Pieza270  270  270.000000
  72 271 Pieza271  271  271.000000
  73 272 Pieza272  272  272.000000
  74 273 Pieza273  273  273.000000
  75 274 Pieza274  274  274.000000
  76 275 Pieza275  275  275.000000
  77 276 Pieza276  276  276.000000
  78 277 Pieza277  277  277.000000
  79 278 Pieza278  278  278.000000
  80 279 Pieza279  279  279.000000
  81 280 Pieza280  280  280.000000
  82 281 Pieza281  281  281.000000
  83 282 Pieza282  282  282.000000
  84 283 Pieza283  283  283.000000
  85 284 Pieza284  284  284.000000
  86 285 Pieza285  285  285.000000
  87 286 Pieza286  286  286.000000
  88 287 Pieza287  287  287.000000
  89 288 Pieza288  288  288.000000
  90 289 Pieza289  289  289.000000
  91 290 Pieza290  290  290.000000
  92 291 Pieza291  291  291.000000
  93 292 Pieza292  292  292.000000
  94 293 Pieza293  293  293.000000
  95 294 Pieza294  294  294.000000
  96 295 Pieza295  295  295.000000
  97 296 Pieza296  296  296.000000
  98 297 Pieza297  297  297.000000
  99 298 Pieza298  298  298.000000
  100 299 Pieza299  299  299.000000
  101 300 Pieza300  300  300.000000
 no encontrado !!no encontrado !!
 Presione una tecla para continuar . . .

*/




