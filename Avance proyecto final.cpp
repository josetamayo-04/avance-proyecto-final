#include <iostream>
#include <stdlib.h>

using namespace std;


struct corredor {
    int numero;
    char nombre[30];
    
    int tiempo = 0;
    int tiempototal = 0;
    int ronda = 0;
    corredor* sig;
};
corredor* cab_corredor = nullptr;
corredor* aux_corredor = nullptr;
corredor* aux2_corredor = nullptr;


struct promedio {
    float prom;
    promedio* sig;
    corredor* apunta;
};
promedio* cab_promedio = nullptr;
promedio* aux_promedio = nullptr;
promedio* aux2_promedio = nullptr;

int numerocorredor = 1;

int registrar() {
    
    aux_corredor = new corredor;
    aux_corredor->sig = nullptr;
    cout << "Proporcione el nombre del corredor: ";
    cin >> aux_corredor->nombre;
    aux_corredor->numero = numerocorredor;
    aux_corredor->ronda = aux_corredor->tiempo = 0;
    numerocorredor++;
    cout << "El numero asignado al corredor es: " << aux_corredor->numero;
    if (!cab_corredor) {
        cab_corredor = aux_corredor;
        aux_corredor = nullptr;
        free(aux_corredor);
    }
    else {
        aux2_corredor = cab_corredor;
        while (aux2_corredor->sig != nullptr) {
            aux2_corredor = aux2_corredor->sig;
        }
        aux2_corredor->sig = aux_corredor;
        aux_corredor = aux2_corredor = nullptr;
        free(aux_corredor);
        free(aux2_corredor);
    }

    return 0;
}

int mostrar() {
    for (aux_corredor = cab_corredor; aux_corredor != nullptr; aux_corredor = aux_corredor->sig) {
        cout << "El numero " << aux_corredor->numero << " es el corredor: " << aux_corredor->nombre << " (" << aux_corredor->ronda << ") :: " << aux_corredor->tiempo << endl;
    }
    return 0;
}

int mostrartiempos() {
    aux2_promedio = cab_promedio;
    while (aux2_promedio != nullptr) {
        cout << "Promedio " << aux2_promedio->apunta->nombre << " " << aux2_promedio->prom << endl;
        aux2_promedio = aux2_promedio->sig;
    }
    return 0;
}

int calcularpromedio() {
    float prom;
    int bandera = 0;
    prom = aux_corredor->tiempototal / aux_corredor->ronda;
    if (cab_promedio == nullptr) {
        cab_promedio = new promedio;
        cab_promedio->prom = prom;
        cab_promedio->sig = nullptr;
        cab_promedio->apunta = aux_corredor;
    }
    else {

for (aux_promedio = cab_promedio; aux_promedio != nullptr; aux_promedio = aux_promedio->sig) {
if (aux_promedio->apunta == aux_corredor) {
aux_promedio->prom = prom;
bandera = 1;
break;
}
}
if (bandera == 0) {
aux_promedio = new promedio;
aux_promedio->prom = prom;
aux_promedio->sig = nullptr;
aux_promedio->apunta = aux_corredor;
aux2_promedio = cab_promedio;
while (aux2_promedio->sig != nullptr) {
aux2_promedio = aux2_promedio->sig;
}
aux2_promedio->sig = aux_promedio;
aux_promedio = aux2_promedio = nullptr;
free(aux_promedio);
free(aux2_promedio);
}
}
return 0;
}

int registrartiempo() {
int numcorredor;
cout << "Ingrese el numero de corredor: ";
cin >> numcorredor;
for (aux_corredor = cab_corredor; aux_corredor != nullptr; aux_corredor = aux_corredor->sig) {
if (aux_corredor->numero == numcorredor) {
int tiempo;
cout << "Ingrese el tiempo para el corredor " << aux_corredor->nombre << ": ";
cin >> tiempo;
aux_corredor->tiempototal += tiempo;
aux_corredor->ronda++;
aux_corredor->tiempo = tiempo;
calcularpromedio();
break;
}
}
return 0;
}

int main() {
int opcion = 0;
while (opcion != 4) {
cout << "\nMenu de opciones\n";
cout << "1. Registrar corredor\n";
cout << "2. Registrar tiempo\n";
cout << "3. Mostrar tiempos promedios\n";
cout << "4. Salir\n";
cout << "Ingrese la opcion: ";
cin >> opcion;
    switch (opcion) {
    case 1:
        registrar();
        break;
    case 2:
        registrartiempo();
        break;
    case 3:
        mostrartiempos();
        break;
    case 4:
        break;
    default:
        cout << "Opcion invalida\n";
        break;
    }
}
return 0;
}