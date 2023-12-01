#include <iostream>
#include <vector>
#include <algorithm>

class Producto {
private:
    static int contadorID;

    int id;
    std::string nombre;
    std::string categoria;
    float precio;
    int cantidad;
    std::string marca;
    std::string proveedor;
    std::string fechaVencimiento;

public:
    // Constructor
    Producto(std::string nombre, std::string categoria, float precio, int cantidad,
             std::string marca, std::string proveedor, std::string fechaVencimiento)
        : id(contadorID++), nombre(nombre), categoria(categoria), precio(precio),
          cantidad(cantidad), marca(marca), proveedor(proveedor), fechaVencimiento(fechaVencimiento) {}

    // Métodos de lectura
    void imprimirPorId() const {
        std::cout << "ID: " << id+1 << " - Nombre: " << nombre << " - Cantidad: " << cantidad
                  << " - Precio: $" << precio << " - Marca: " << marca << " - Proveedor: " << proveedor
                  << " - Fecha de Vencimiento: " << fechaVencimiento << std::endl;
    }

    void imprimirPorNombre() const {
        std::cout << "Nombre: " << nombre << " - ID: " << id+1 << " - Cantidad: " << cantidad
                  << " - Precio: $" << precio << " - Marca: " << marca << " - Proveedor: " << proveedor
                  << " - Fecha de Vencimiento: " << fechaVencimiento << std::endl;
    }

    // Métodos de actualizacion
    void actualizarPrecio(float nuevoPrecio) {
        precio = nuevoPrecio;
    }

    void actualizarCantidad(int nuevaCantidad) {
        cantidad = nuevaCantidad;
    }

    // Método de eliminación
    void eliminar() {
        std::cout << "Producto con ID " << id+1 << " eliminado." << std::endl;
    }

    // Getter para el ID
    int getId() const {
        return id;
    }

    // Getter para el nombre
    std::string getNombre() const {
        return nombre;
    }

    // Getter para el contador de ID
    static int getContadorID() {
        return contadorID;
    }

    // Setter para el ID (solo accesible internamente)
    void asignarId(int nuevoId) {
        id = nuevoId;
    }

    // Operacion libre 1: Promedio de precios de todos los productos
    static float calcularPromedioPrecio(const std::vector<Producto>& productos) {
        if (productos.empty()) {
            return 0.0f;
        }

        float sumaPrecios = 0.0f;
        for (const auto& producto : productos) {
            sumaPrecios += producto.precio;
        }

        return sumaPrecios / productos.size();
    }

    // Operacion libre 2: Promedio de precios para productos con identificadores proporcionados
    static float calcularPromedioPrecioPorIds(const std::vector<Producto>& productos, const std::vector<int>& ids) {
        if (productos.empty() || ids.empty()) {
            return 0.0f;
        }

        float sumaPrecios = 0.0f;
        int productosContados = 0;

        for (const auto& producto : productos) {
            if (std::find(ids.begin(), ids.end(), producto.id) != ids.end()) {
                sumaPrecios += producto.precio;
                productosContados++;
            }
        }

        return (productosContados > 0) ? sumaPrecios / productosContados : 0.0f;
    }
};

// Inicializacion del contador de ID
int Producto::contadorID = 0;

// Funcion para buscar un producto por ID en un vector de productos
Producto* buscarPorId(const std::vector<Producto>& productos, int id) {
    for (auto& producto : productos) {
        if (producto.getId() == id-1) {
            return const_cast<Producto*>(&producto);
        }
    }
    return nullptr;
}

int main() {
    std::vector<Producto> inventario;

     // Menu de opciones
    int opcion;
    do {
        std::cout << "===== Abarrotes ''El Kevin'' =====" << std::endl;
        std::cout << "1. Agregar Producto" << std::endl;
        std::cout << "2. Mostrar Producto por ID" << std::endl;
        std::cout << "3. Mostrar Productos por Nombre" << std::endl;
        std::cout << "4. Actualizar Precio" << std::endl;
        std::cout << "5. Actualizar Cantidad" << std::endl;
        std::cout << "6. Eliminar Producto" << std::endl;
        std::cout << "7. Promedio de productos " << std::endl;
        std::cout << "8. Promedio de precios por identificarlos " << std::endl;
        std::cout << "0. Salir" << std::endl;
        std::cout << "Seleccione una opcion: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1: {
                // Operacion Create
                std::string nombre, categoria, marca, proveedor, fechaVencimiento;
                float precio;
                int cantidad;

                std::cout << "Nombre del Producto: ";
                std::cin >> nombre;
                std::cout << "Categoria: ";
                std::cin >> categoria;
                std::cout << "Precio: $";
                std::cin >> precio;
                std::cout << "Cantidad: ";
                std::cin >> cantidad;
                std::cout << "Marca: ";
                std::cin >> marca;
                std::cout << "Proveedor: ";
                std::cin >> proveedor;
                std::cout << "Fecha de Vencimiento: ";
                std::cin >> fechaVencimiento;

                inventario.emplace_back(nombre, categoria, precio, cantidad, marca, proveedor, fechaVencimiento);
                std::cout << "Producto agregado con ID " << Producto::getContadorID() << std::endl;
                break;
            }
            case 2: {
                // Operacion Read por ID
                int id;
                std::cout << "Ingrese el ID del producto: ";
                std::cin >> id;
                Producto* producto = buscarPorId(inventario, id);
                if (producto != nullptr) {
                    producto->imprimirPorId();
                } else {
                    std::cout << "Producto no encontrado." << std::endl;
                }
                break;
            }
            case 3: {
                // Operacion Read por Nombre
                std::string nombre;
                std::cout << "Ingrese el nombre del producto: ";
                std::cin >> nombre;

                // Filtrar productos con el nombre dado
                std::vector<Producto> productosConNombre;
                for (const auto& producto : inventario) {
                    if (producto.getNombre() == nombre) {
                        productosConNombre.push_back(producto);
                    }
                }

                // Imprimir productos encontrados
                if (!productosConNombre.empty()) {
                    std::cout << "Productos con nombre '" << nombre << "':" << std::endl;
                    for (const auto& producto : productosConNombre) {
                        producto.imprimirPorNombre();
                    }
                } else {
                    std::cout << "No se encontraron productos con ese nombre." << std::endl;
                }
                break;
            }
            case 4: {
                // Operacion Update Precio
                int id;
                float nuevoPrecio;
                std::cout << "Ingrese el ID del producto: ";
                std::cin >> id;
                Producto* producto = buscarPorId(inventario, id);
                if (producto != nullptr) {
                    std::cout << "Ingrese el nuevo precio: $";
                    std::cin >> nuevoPrecio;
                    producto->actualizarPrecio(nuevoPrecio);
                    std::cout << "Precio actualizado correctamente." << std::endl;
                } else {
                    std::cout << "Producto no encontrado." << std::endl;
                }
                break;
            }
            case 5: {
                // Operacipn Update Cantidad
                int id;
                int nuevaCantidad;
                std::cout << "Ingrese el ID del producto: ";
                std::cin >> id;
                Producto* producto = buscarPorId(inventario, id);
                if (producto != nullptr) {
                    std::cout << "Ingrese la nueva cantidad: ";
                    std::cin >> nuevaCantidad;
                    producto->actualizarCantidad(nuevaCantidad);
                    std::cout << "Cantidad actualizada correctamente." << std::endl;
                } else {
                    std::cout << "Producto no encontrado." << std::endl;
                }
                break;
            }
            case 6: {
                // Operacion Delete
                int id;
                std::cout << "Ingrese el ID del producto a eliminar: ";
                std::cin >> id;
                auto it = std::remove_if(inventario.begin(), inventario.end(),
                                         [id](const Producto& producto) { return producto.getId() == id-1; });
                if (it != inventario.end()) {
                    inventario.erase(it, inventario.end());
                    std::cout << "Producto eliminado correctamente." << std::endl;
                } else {
                    std::cout << "Producto no encontrado." << std::endl;
                }
                break;
            }
            case 7: {
                // Operación libre 1: Promedio de precios de todos los productos
                float PromedioPrecio = Producto::calcularPromedioPrecio(inventario);
                std::cout << "Promedio de precios de todos los productos: $" << PromedioPrecio << std::endl;
                break;
                }
            case 8: {
                // Operación libre 2: Promedio de precios por identificadores
                std::vector<int> ids;
                int numIds;
                std::cout << "Ingrese la cantidad de identificadores: ";
                std::cin >> numIds;
                for (int i = 0; i < numIds; ++i) {
                        int id;
                std::cout << "Ingrese el identificador " << i + 1 << ": ";
                std::cin >> id;
                ids.push_back(id-1);
                }
                float promedioPorIds = Producto::calcularPromedioPrecioPorIds(inventario, ids);
                std::cout << "Promedio de precios por identificadores: $" << promedioPorIds << std::endl;
                break;
            }


            case 0:
                std::cout << "Saliendo del programa." << std::endl;
                break;
            default:
                std::cout << "Opcion no válida. Inténtelo de nuevo." << std::endl;
        }

    } while (opcion != 0);

    return 0;
}
