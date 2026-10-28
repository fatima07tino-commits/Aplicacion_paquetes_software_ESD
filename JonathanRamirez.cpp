#include<iostream>
using namespace std;

//COMENZADO PRUEBA 
//CREAMOS LA ESTRUCTURA QUE ALMACENARA LOS DATOS DEL PAQUETE DE SOFTWARE

struct paquete{
	int codigo;
	string nombre;
	string version;
	bool instalado;
};

//CREAMOS EL NODO A LA LISTA ENLAZADA
struct nodoPaquete{
	paquete dato;
	nodoPaquete* siguiente;
};

//ACA CREE EL PUNTERO DE INICIO
//nodoPaquete *inicio = nullptr;

//METODOS CREADOS
void registrarPaquete(nodoPaquete*& inicio);
void mostrarPaquete(nodoPaquete* inicio);
nodoPaquete* buscarPaquete(nodoPaquete* inicio,int codigo);

// METODOS PARA ADMINISTRAR SOLICITUDES
void menuSolicitudes(nodoPaquete* inicio);
void liberarPendientes();

int main(){
  nodoPaquete* inicio = nullptr;
  int opcion;
  
  do{
  
   //MOSTRAMOS EL MENU DE OPCIONES
   cout << "\n===== GESTOR DE PAQUETES =====\n";
        cout << "1. Registrar paquete\n";
        cout << "2. Mostrar paquetes\n";
        cout<< "3. Buscar paquete (codigo)\n";
        cout << "4. Administrar solicitudes\n";
        cout << "5. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        
    if(opcion == 1){
    	registrarPaquete(inicio);
	}
	if(opcion == 2){
		mostrarPaquete(inicio);
	}
	if(opcion == 3){
		int codigo;
		cout << "Ingrese el codigo del paquete: "<<endl;
		cin >> codigo;
		
		//CREAMOS UN PUNTERO QUE GUARDARA EL RETORNO DE LA FUNCION
		nodoPaquete* encontrado = buscarPaquete(inicio,codigo);
		if(encontrado != nullptr){
			cout<<"\n==PAQUETE ENCONTRADO=="<<endl;
			cout<<"\nNombre: "<<encontrado->dato.nombre<<endl;
			cout<<"\nVersion: "<<encontrado->dato.version<<endl;
		}else{
			cout<<"\nEl paquete no existe"<<endl;
		}
	}
	if(opcion == 4){
		menuSolicitudes(inicio);
	}
	}while(opcion!= 5);
	liberarPendientes();
	
return 0;	
}

//METODO PARA REGISTRAR UN PAQUETE
void registrarPaquete(nodoPaquete*& inicio){
	
	//CONSULTAR SI SE PUEDE HACER
	//nodoPaquete* nuevo = (nodoPaquete*) malloc(sizeof(nodoPaquete));
	nodoPaquete* nuevo = new nodoPaquete;
	
	//PEDIMOS LA INFORMACION DEL PAQUETE DE SOFWARE
	cout<<"Ingrese el codigo: "<< endl;
	cin>>nuevo->dato.codigo;
	
	//VERIFICAMOS QUE EL PAQUETE NO EXISTA YA
	nodoPaquete* encontrado = buscarPaquete(inicio,nuevo->dato.codigo);
	if(encontrado != nullptr){
		cout<<"ERROR: YA EXISTE UN PAQUETE CON ESE CODIGO.."<<endl;
		
		//CONSULTAR ACA DUDA //
	}
	
	cout<<"Ingrese el nombre: "<<endl;
	cin>>nuevo->dato.nombre;
	
	cout<<"Ingrese la version del paquete: "<<endl;
	cin>> nuevo->dato.version;
	
	nuevo->dato.instalado = false;
	nuevo->siguiente = nullptr;
	
	if(inicio == nullptr){
		inicio = nuevo;
		
	}else{
		nodoPaquete* auxiliar = inicio;
		
		while(auxiliar->siguiente!= nullptr){
			auxiliar = auxiliar->siguiente;
		}
		auxiliar->siguiente = nuevo;
		
	}
	
	cout<<"Paquete registrado correctamente.\n"<<endl;
	
	
}

//METODO PARA MOSTRAR LOS PAQUETES REGISTRADOS
void mostrarPaquete(nodoPaquete* inicio){
	nodoPaquete* auxiliar = inicio;
	
	while(auxiliar != nullptr){
		//MOSTRAMOS LOS DATOS
		cout<<"\n====PAQUETES REGISTRADOS===="<<endl;
		cout<<"\nCodigo: "<<auxiliar->dato.codigo<<endl;
		cout<<"\nNombre: "<<auxiliar->dato.nombre<<endl;
		cout<<"\nVersion: "<<auxiliar->dato.version<<endl;
		cout<<"\nInstalado: "<<auxiliar->dato.instalado<<endl;
		
		auxiliar = auxiliar->siguiente;
		
	}
}

//METODO PARA BUSCAR UN PAQUETE POR SU CODIGO
nodoPaquete* buscarPaquete(nodoPaquete *inicio,int codigo){
	
	nodoPaquete* auxiliar = inicio;
	while(auxiliar != nullptr){
		if(auxiliar->dato.codigo == codigo){
			return auxiliar;
		}
		auxiliar = auxiliar->siguiente;
	}
	return nullptr;
}


//ISAMARA: HACER EL CODIGO DE LA PARTE DE REGISTRAR SOLICITUDES DE INSTALACION Y ELIMINACION

















































//FATIMA: HACER LA PARTE DE ADMINISTRAR LOS ELEMENTOS PENDIENTES DE PROCESAMIENTOS, MANEJAR DIFERENTES NIVELES DE PRIORIDAD
enum Prioridad{ //Enumeración de prioridades
	Baja = 1,
	Media = 2,
	Alta = 3
};

struct nodoSolicitud{ //Nodo cola dinamica
	int codigo;
	unsigned char tipo; //instalar y eliminar
	unsigned char prioridad; //1,2,3
	nodoSolicitud* siguiente;
};

struct ColaPendientes {
	nodoSolicitud* frente;
	nodoSolicitud* final;
};

ColaPendientes cola= {nullptr, nullptr}; //inicializar cola

bool colaVacia() { //verificar que no esta vacia
	return cola.frente == nullptr;
}

void mostrarPrioridad(int prioridad) {
    if (prioridad == Alta)
        cout << "Alta";
    else if (prioridad == Media)
        cout << "Media";
    else
        cout << "Baja";
}

bool buscarSolicitud(int codigo, int tipo) { //verificar solicitudes repetidas
    nodoSolicitud* aux = cola.frente;
    while (aux != nullptr) {
        if (aux->codigo == codigo && aux->tipo == tipo)
            return true;
        aux = aux->siguiente;
    }
    return false;
}

void insertarSolicitud(nodoPaquete* inicio) { //según prioridad

    int codigo, tipo, prioridad;
    cout << "\nNUEVA SOLICITUD\n";
    cout << "Codigo del paquete: ";
    if (!(cin >> codigo)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Codigo invalido.\n";
        return;
    }
    nodoPaquete* p = buscarPaquete(inicio, codigo);
    if (p == nullptr) {
        cout << "El paquete no existe.\n";
        return;
    }
    cout << "1. Instalar\n2. Eliminar\nOpcion: ";
    if (!(cin >> tipo) || tipo < 1 || tipo > 2) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Tipo invalido.\n";
        return;
    }
    if (buscarSolicitud(codigo, tipo)) {
        cout << "La solicitud ya existe.\n";
        return;
    }
    if ((tipo == 1 && p->dato.instalado) ||
        (tipo == 2 && !p->dato.instalado)) {
        cout << "Operacion no valida para el estado actual.\n";
        return;
    }
    cout << "1. Baja\n2. Media\n3. Alta\nPrioridad: ";
    if (!(cin >> prioridad) || prioridad < 1 || prioridad > 3) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Prioridad invalida.\n";
        return;
    }

    nodoSolicitud* nuevo = new nodoSolicitud; //reservar memoria solo al confirmar los datos
    nuevo->codigo = codigo;
    nuevo->tipo = tipo;
    nuevo->prioridad = prioridad;
    nuevo->siguiente = nullptr;

    if (colaVacia() || prioridad > cola.frente->prioridad) { //insertar al frente
        nuevo->siguiente = cola.frente;
        cola.frente = nuevo;
        if (cola.final == nullptr)
            cola.final = nuevo;
    } else {
        nodoSolicitud* aux = cola.frente;

        while (aux->siguiente != nullptr && aux->siguiente->prioridad >= prioridad) { //buscar posición según prioridad
            aux = aux->siguiente;
        }
        nuevo->siguiente = aux->siguiente;
        aux->siguiente = nuevo;
        if (nuevo->siguiente == nullptr)
            cola.final = nuevo;
    }
    cout << "Solicitud agregada correctamente.\n";
}

void mostrarPendientes() {
    if (colaVacia()) {
        cout << "\nNo hay solicitudes pendientes.\n";
        return;
    }
    nodoSolicitud* aux = cola.frente;
    int numero = 1;
    cout << "\nSOLICITUDES PENDIENTES\n";
    while (aux != nullptr) {
        cout << "\nSolicitud: " << numero++;
        cout << "\nCodigo: " << aux->codigo;
        cout << "\nTipo: "
             << (aux->tipo == 1 ? "INSTALAR" : "ELIMINAR");
        cout << "\nPrioridad: ";
        mostrarPrioridad(aux->prioridad);
        cout << endl;
        aux = aux->siguiente;
    }
}

int cantidadPendientes() {
    int cantidad = 0;
    nodoSolicitud* aux = cola.frente;
    while (aux != nullptr) {
        cantidad++;
        aux = aux->siguiente;
    }
    return cantidad;
}

void consultarSiguiente() { //la próxima solicitud sin eliminar
    if (colaVacia()) {
        cout << "\nNo hay solicitudes pendientes.\n";
        return;
    }
    cout << "\nSIGUIENTE SOLICITUD\n";
    cout << "Codigo: " << cola.frente->codigo;
    cout << "\nTipo: "<< (cola.frente->tipo == 1 ? "INSTALAR" : "ELIMINAR");
    cout << "\nPrioridad: ";
	mostrarPrioridad(cola.frente->prioridad);
    cout << endl;
}

void procesarSolicitud(nodoPaquete* inicio) { //y retirar la siguiente solicitud
    if (colaVacia()) {
        cout << "\nNo hay solicitudes pendientes.\n";
        return;
    }
    nodoSolicitud* aux = cola.frente;
    nodoPaquete* p = buscarPaquete(inicio, aux->codigo);
    if (p == nullptr) {
        cout << "Error: paquete inexistente.\n";
    } else {
        bool instalar = (aux->tipo == 1);
        if (p->dato.instalado == instalar) {
            cout << "Error: estado incompatible.\n";
        } else {
            p->dato.instalado = instalar;
            cout << "\nPaquete: " << p->dato.nombre;
            cout << (instalar ? " instalado.\n"
                             : " desinstalado.\n");
        }
    }

    cola.frente = aux->siguiente; //extraer nodo

    if (cola.frente == nullptr)
        cola.final = nullptr;
    delete aux;
}

void liberarPendientes() { //liberar toda la memoria de la cola
    while (!colaVacia()) {
        nodoSolicitud* aux = cola.frente;
        cola.frente = aux->siguiente;
        delete aux;
    }
    cola.final = nullptr;
}

void menuSolicitudes(nodoPaquete* inicio) { // MENU PARA ADMINISTRAR SOLICITUDES
    int opcion;
    do {
        cout << "\n=== MENU DE SOLICITUDES ===\n";
        cout << "1. Registrar solicitud\n";
        cout << "2. Mostrar pendientes\n";
        cout << "3. Procesar solicitud\n";
        cout << "4. Consultar siguiente\n";
        cout << "5. Contar pendientes\n";
        cout << "6. Regresar\n";
        cout << "Opcion: ";

        if (!(cin >> opcion)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Opcion invalida.\n";
            continue;
        }

        switch (opcion) {

            case 1:
                insertarSolicitud(inicio);
                break;

            case 2:
                mostrarPendientes();
                break;

            case 3:
                procesarSolicitud(inicio);
                break;

            case 4:
                consultarSiguiente();
                break;

            case 5:
                cout << "Pendientes: "
                     << cantidadPendientes() << endl;
                break;

            case 6:
                break;

            default:
                cout << "Opcion invalida.\n";
        }

    } while (opcion != 6);
}

//ALISSON: CONTROLAR SITUACIONES COMO SOLICITUDES REPETIDAS, CANCELACIONES Y ERRORES DURANTE EL PROCESO