#include <iostream>
#include <string>
#include <vector>

struct Atleta {
    std::string nombre;
    std::string nacionalidad;
    int numero;
    std::vector<double> tiempos;
    double promedio_tiempo;

    Atleta(const std::string& nombre, const std::string& nacionalidad, int numero)
        : nombre(nombre), nacionalidad(nacionalidad), numero(numero), promedio_tiempo(0.0) {}
};

struct NodoArbol {
    Atleta atleta;
    NodoArbol* izquierdo;
    NodoArbol* derecho;

    NodoArbol(const Atleta& atleta)
        : atleta(atleta), izquierdo(nullptr), derecho(nullptr) {}
};

class ArbolAVL {
public:
    ArbolAVL() : raiz(nullptr) {}

    void Insertar(const Atleta& atleta) {
        raiz = InsertarNodo(raiz, atleta);
    }

    void RegistrarVueltas() {
        int numero;
        std::cout << "Ingrese el número del corredor: ";
        std::cin >> numero;
        std::cin.ignore();

        NodoArbol* corredor = BuscarPorNumero(raiz, numero);
        if (corredor != nullptr) {
            int total_vueltas;
            std::cout << "Ingrese el número total de vueltas realizadas por el corredor: ";
            std::cin >> total_vueltas;
            std::cin.ignore();

            std::vector<double> tiempos;
            for (int i = 1; i <= total_vueltas; i++) {
                double tiempo_vuelta;
                std::cout << "Ingrese el tiempo de la vuelta " << i << " (en segundos): ";
                std::cin >> tiempo_vuelta;
                std::cin.ignore();

                tiempos.push_back(tiempo_vuelta);
            }

            corredor->atleta.tiempos = tiempos;
            corredor->atleta.promedio_tiempo = CalcularPromedioTiempos(tiempos);

            std::cout << "Vueltas registradas correctamente." << std::endl;
        } else {
            std::cout << "No se encontró ningún corredor con ese número." << std::endl;
        }
    }

    void BuscarPorNombre(const std::string& nombre) {
        NodoArbol* corredor = BuscarPorNombre(raiz, nombre);
        if (corredor != nullptr) {
            std::cout << "Nombre: " << corredor->atleta.nombre << std::endl;
            std::cout << "Nacionalidad: " << corredor->atleta.nacionalidad << std::endl;
            std::cout << "Número: " << corredor->atleta.numero << std::endl;
            MostrarTiempos(corredor->atleta.tiempos);
            std::cout << "Promedio de tiempos: " << corredor->atleta.promedio_tiempo << " segundos" << std::endl;
        } else {
            std::cout << "No se encontró ningún corredor con ese nombre." << std::endl;
        }
    }

    void MostrarPromedios() {
        MostrarPromediosOrdenados(raiz);
    }

private:
    NodoArbol* raiz;

    NodoArbol* InsertarNodo(NodoArbol* nodo, const Atleta& atleta) {
        if (nodo == nullptr) {
            return new NodoArbol(atleta);
        }

        if (atleta.numero < nodo->atleta.numero) {
            nodo->izquierdo = InsertarNodo(nodo->izquierdo, atleta);
        } else {
            nodo->derecho = InsertarNodo(nodo->derecho, atleta);
        }

        return nodo;
    }

    NodoArbol* BuscarPorNumero(NodoArbol* nodo, int numero) {
        if (nodo == nullptr || nodo->atleta.numero == numero) {
            return nodo;
        }

        if (numero < nodo->atleta.numero) {
            return BuscarPorNumero(nodo->izquierdo, numero);
        } else {
            return BuscarPorNumero(nodo->derecho, numero);
        }
    }

    NodoArbol* BuscarPorNombre(NodoArbol* nodo, const std::string& nombre) {
        if (nodo == nullptr || nodo->atleta.nombre == nombre) {
            return nodo;
        }

        NodoArbol* resultado_izq = BuscarPorNombre(nodo->izquierdo, nombre);
        if (resultado_izq != nullptr) {
            return resultado_izq;
        }

        NodoArbol* resultado_der = BuscarPorNombre(nodo->derecho, nombre);
        if (resultado_der != nullptr) {
            return resultado_der;
        }

        return nullptr;
    }

    double CalcularPromedioTiempos(const std::vector<double>& tiempos) {
        double suma = 0.0;
        for (double tiempo : tiempos) {
            suma += tiempo;
        }
        return suma / tiempos.size();
    }

    void MostrarTiempos(const std::vector<double>& tiempos) {
        std::cout << "Tiempos registrados: ";
        for (double tiempo : tiempos) {
            std::cout << tiempo << "s ";
        }
        std::cout << std::endl;
    }

    void MostrarPromediosOrdenados(NodoArbol* nodo) {
        if (nodo == nullptr) {
            return;
        }

        MostrarPromediosOrdenados(nodo->izquierdo);
        std::cout << "Nombre: " << nodo->atleta.nombre << ", Nacionalidad: " << nodo->atleta.nacionalidad << ", Promedio: " << nodo->atleta.promedio_tiempo << " segundos" << std::endl;
        MostrarPromediosOrdenados(nodo->derecho);
    }
};

int main() {
    ArbolAVL arbol;

    int opcion;
    do {
        std::cout << "\n--- Menú ---" << std::endl;
        std::cout << "1. Registrar corredor" << std::endl;
        std::cout << "2. Registrar vueltas" << std::endl;
        std::cout << "3. Buscar corredor por nombre" << std::endl;
        std::cout << "4. Mostrar promedios" << std::endl;
        std::cout << "5. Salir" << std::endl;
        std::cout << "Ingrese una opción: ";
        std::cin >> opcion;
        std::cin.ignore();

        switch (opcion) {
            case 1: {
                std::string nombre;
                std::string nacionalidad;
                int numero;
                std::cout << "Ingrese el nombre del corredor: ";
                std::getline(std::cin, nombre);

                std::cout << "Ingrese la nacionalidad del corredor: ";
                std::getline(std::cin, nacionalidad);

                std::cout << "Ingrese el número del corredor: ";
                std::cin >> numero;
                std::cin.ignore();

                Atleta atleta(nombre, nacionalidad, numero);
                arbol.Insertar(atleta);

                std::cout << "Corredor registrado correctamente." << std::endl;
                break;
            }
            case 2:
                arbol.RegistrarVueltas();
                break;
            case 3: {
                std::string nombre;
                std::cout << "Ingrese el nombre del corredor: ";
                std::getline(std::cin, nombre);

                arbol.BuscarPorNombre(nombre);
                break;
            }
            case 4:
                std::cout << "\n--- Resultados de menor promedio a mayor ---" << std::endl;
                arbol.MostrarPromedios();
                break;
            case 5:
                std::cout << "Saliendo del programa..." << std::endl;
                break;
            default:
                std::cout << "Opción inválida. Intente nuevamente." << std::endl;
                break;
        }
    } while (opcion != 5);

    return 0;
}


