#include <iostream>
#include <string>

struct Atleta {
    std::string nombre;
    int numero;
};

struct NodoArbol {
    double promedio;
    Atleta atleta;
    NodoArbol* izquierdo;
    NodoArbol* derecho;

    NodoArbol(double promedio, const Atleta& atleta)
        : promedio(promedio), atleta(atleta), izquierdo(nullptr), derecho(nullptr) {}
};

class ArbolAVL {
public:
    ArbolAVL() : raiz(nullptr) {}

    void Insertar(double promedio, const Atleta& atleta) {
        raiz = InsertarNodo(raiz, promedio, atleta);
    }

    void MostrarPromedios() {
        MostrarPromediosOrdenados(raiz);
    }

private:
    NodoArbol* raiz;

    NodoArbol* InsertarNodo(NodoArbol* nodo, double promedio, const Atleta& atleta) {
        if (nodo == nullptr) {
            return new NodoArbol(promedio, atleta);
        }

        if (promedio < nodo->promedio) {
            nodo->izquierdo = InsertarNodo(nodo->izquierdo, promedio, atleta);
        } else {
            nodo->derecho = InsertarNodo(nodo->derecho, promedio, atleta);
        }

        // Balancear el árbol después de la inserción
        int balance = ObtenerBalance(nodo);

        if (balance > 1 && promedio < nodo->izquierdo->promedio) {
            return RotacionDerecha(nodo);
        }

        if (balance < -1 && promedio > nodo->derecho->promedio) {
            return RotacionIzquierda(nodo);
        }

        if (balance > 1 && promedio > nodo->izquierdo->promedio) {
            nodo->izquierdo = RotacionIzquierda(nodo->izquierdo);
            return RotacionDerecha(nodo);
        }

        if (balance < -1 && promedio < nodo->derecho->promedio) {
            nodo->derecho = RotacionDerecha(nodo->derecho);
            return RotacionIzquierda(nodo);
        }

        return nodo;
    }

    int ObtenerBalance(NodoArbol* nodo) {
        if (nodo == nullptr) {
            return 0;
        }

        return AlturaNodo(nodo->izquierdo) - AlturaNodo(nodo->derecho);
    }

    int AlturaNodo(NodoArbol* nodo) {
        if (nodo == nullptr) {
            return 0;
        }

        int altura_izq = AlturaNodo(nodo->izquierdo);
        int altura_der = AlturaNodo(nodo->derecho);

        return 1 + std::max(altura_izq, altura_der);
    }

    NodoArbol* RotacionDerecha(NodoArbol* nodo) {
        NodoArbol* nuevo_raiz = nodo->izquierdo;
        NodoArbol* temp = nuevo_raiz->derecho;

        nuevo_raiz->derecho = nodo;
        nodo->izquierdo = temp;

        return nuevo_raiz;
    }

    NodoArbol* RotacionIzquierda(NodoArbol* nodo) {
        NodoArbol* nuevo_raiz = nodo->derecho;
        NodoArbol* temp = nuevo_raiz->izquierdo;

        nuevo_raiz->izquierdo = nodo;
        nodo->derecho = temp;

        return nuevo_raiz;
    }

    void MostrarPromediosOrdenados(NodoArbol* nodo) {
        if (nodo == nullptr) {
            return;
        }

        MostrarPromediosOrdenados(nodo->izquierdo);
        std::cout << "Nombre: " << nodo->atleta.nombre << ", Promedio: " << nodo->promedio << std::endl;
        MostrarPromediosOrdenados(nodo->derecho);
    }
};

int main() {
    ArbolAVL arbol;

    while (true) {
        std::string nombre;
        int numero;
        std::cout << "Ingrese el nombre del atleta (o 'salir' para terminar): ";
        std::getline(std::cin, nombre);

        if (nombre == "salir") {
            break;
        }

        std::cout << "Ingrese el número del atleta: ";
        std::cin >> numero;
        std::cin.ignore();  // Ignorar el salto de línea después de leer el número

        int total_vueltas;
        std::cout << "Ingrese el número total de vueltas realizadas por el atleta: ";
        std::cin >> total_vueltas;
        std::cin.ignore();  // Ignorar el salto de línea después de leer el número

        if (total_vueltas >= 2) {
            double tiempo_total = 0.0;
            for (int i = 1; i <= total_vueltas; i++) {
                double tiempo_vuelta;
                std::cout << "Ingrese el tiempo de la vuelta " << i << " (en segundos): ";
                std::cin >> tiempo_vuelta;
                std::cin.ignore();  // Ignorar el salto de línea después de leer el número

                tiempo_total += tiempo_vuelta;
            }

            double promedio_tiempo = tiempo_total / total_vueltas;
            Atleta atleta{nombre, numero};
            arbol.Insertar(promedio_tiempo, atleta);
        } else {
            std::cout << "El atleta debe realizar al menos dos vueltas para ser considerado en el promedio." << std::endl;
        }
    }

    std::cout << "\n--- Resultados de menor promedio a mayor ---" << std::endl;
    arbol.MostrarPromedios();

    return 0;
}
