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

int main(){
  nodoPaquete* inicio = nullptr;
  int opcion;
  
  do{
  
   //MOSTRAMOS EL MENU DE OPCIONES
   cout << "\n===== GESTOR DE PAQUETES =====\n";
        cout << "1. Registrar paquete\n";
        cout << "2. Mostrar paquetes\n";
        cout<< "3. Buscar paquete (codigo)\n";
        cout << "4. Salir\n";
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
		
		
		
		//CREAMOS UN PUNTERO QUE GUARDARA EL RETORNOO DE LA FUNCION
		nodoPaquete* encontrado = buscarPaquete(inicio,codigo);
		if(encontrado != nullptr){
			cout<<"\n==PAQUETE ENCONTRADO=="<<endl;
			cout<<"\nNombre: "<<encontrado->dato.nombre<<endl;
			cout<<"\nVersion: "<<encontrado->dato.version<<endl;
		}else{
			cout<<"\nEl paquete no existe"<<endl;
		}
	}
	}while(opcion!= 4);
	
	
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

















































//ALISSON: CONTROLAR SITUACIONES COMO SOLICITUDES REPETIDAS, CANCELACIONES Y ERRORES DURANTE EL PROCESO