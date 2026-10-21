// Atividade 3 - Cláusula firstprivate
//
// Funcionamento:
//   firstprivate(lista) funciona como private (cada thread tem sua própria
//   cópia, descartada ao fim da região), com uma diferença: cada cópia é
//   INICIALIZADA com o valor que a variável original tinha imediatamente
//   antes da região paralela. Útil quando todas as threads precisam partir
//   de um mesmo valor inicial e depois modificá-lo de forma independente.
//
// Compilar: g++ -fopenmp atividade3.cpp -o atividade3

#include <iostream>
#include <omp.h>

int main() {
    int base = 50;
    std::cout << "Antes da região paralela: base = " << base << "\n";

    // Cada thread recebe uma cópia de base já valendo 50
    #pragma omp parallel firstprivate(base) num_threads(4)
    {
        int id = omp_get_thread_num();
        int inicial = base;  // todas as threads leem 50 aqui

        base += id;          // cada thread altera apenas a sua cópia

        #pragma omp critical
        std::cout << "Thread " << id << ": base inicial = " << inicial
                  << ", base final = " << base << "\n";
    }

    // Assim como no private, a variável original não é alterada
    std::cout << "Depois da região paralela: base = " << base << "\n";
    return 0;
}
