// Atividade 8
// Igual à atividade 7, mas ao final mostra a somatória de todos os números
// gerados por todas as threads.
//
// Compilar: g++ -fopenmp atividade8.cpp -o atividade8

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
    if (inicio > fim) std::swap(inicio, fim);

    const int QTD_NUMEROS = 10;
    std::random_device rd;
    unsigned semente = rd();
    long long somaTotal = 0;  // long long para não estourar com muitos números grandes

    // reduction(+:somaTotal): cada thread acumula na sua cópia privada e,
    // ao final, o OpenMP soma todas as cópias na variável original
    #pragma omp parallel num_threads(nThreads) reduction(+:somaTotal)
    {
        int id = omp_get_thread_num();
        std::mt19937 gerador(semente + id);
        std::uniform_int_distribution<int> distribuicao(inicio, fim);

        for (int i = 0; i < QTD_NUMEROS; i++) {
            int numero = distribuicao(gerador);
            somaTotal += numero;  // soma na cópia privada: sem condição de corrida

            #pragma omp critical
            std::cout << "Thread " << id << " gerou: " << numero << "\n";
        }

        #pragma omp critical
        std::cout << "-> Subtotal da thread " << id << ": " << somaTotal << "\n";
    }

    std::cout << "\nSomatória de todos os " << nThreads * QTD_NUMEROS
              << " números gerados: " << somaTotal << "\n";
    return 0;
}
