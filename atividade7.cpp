// Atividade 7
// Igual à atividade 6, mas o usuário também informa o início e o fim do
// intervalo dos números aleatórios.
//
// Compilar: g++ -fopenmp atividade7.cpp -o atividade7

#include <iostream>
#include <random>
#include <utility>
#include <omp.h>

int main() {
    int nThreads, inicio, fim;

    std::cout << "Quantas threads deseja criar? ";
    if (!(std::cin >> nThreads) || nThreads < 1) {
        std::cerr << "Informe um número inteiro maior que zero.\n";
        return 1;
    }
    std::cout << "Valor inicial do intervalo: ";
    std::cin >> inicio;
    std::cout << "Valor final do intervalo: ";
    std::cin >> fim;
    if (!std::cin) {
        std::cerr << "Informe valores inteiros para o intervalo.\n";
        return 1;
    }
    // Se o usuário digitar o intervalo invertido, apenas trocamos os valores
    if (inicio > fim) std::swap(inicio, fim);

    const int QTD_NUMEROS = 10;
    std::random_device rd;
    unsigned semente = rd();

    // inicio e fim são lidos por todas as threads (shared, somente leitura)
    #pragma omp parallel num_threads(nThreads)
    {
        int id = omp_get_thread_num();

        // Gerador próprio por thread, agora com o intervalo informado
        std::mt19937 gerador(semente + id);
        std::uniform_int_distribution<int> distribuicao(inicio, fim);

        for (int i = 0; i < QTD_NUMEROS; i++) {
            int numero = distribuicao(gerador);

            #pragma omp critical
            std::cout << "Thread " << id << " gerou: " << numero << "\n";
        }
    }
    return 0;
}
