// Atividade 6
// Pede ao usuário a quantidade de threads; cada thread gera 10 números
// aleatórios entre 0 e 1000 e mostra seu id junto de cada número gerado.
//
// Compilar: g++ -fopenmp atividade6.cpp -o atividade6

#include <iostream>
#include <random>
#include <omp.h>

int main() {
    int nThreads;
    std::cout << "Quantas threads deseja criar? ";
    if (!(std::cin >> nThreads) || nThreads < 1) {
        std::cerr << "Informe um número inteiro maior que zero.\n";
        return 1;
    }

    const int QTD_NUMEROS = 10;
    std::random_device rd;
    unsigned semente = rd();  // semente base, compartilhada (apenas leitura)

    // num_threads cria exatamente a quantidade informada pelo usuário
    #pragma omp parallel num_threads(nThreads)
    {
        int id = omp_get_thread_num();

        // rand() não é seguro entre threads; por isso cada thread tem seu
        // próprio gerador, com semente diferente (base + id)
        std::mt19937 gerador(semente + id);
        std::uniform_int_distribution<int> distribuicao(0, 1000);

        for (int i = 0; i < QTD_NUMEROS; i++) {
            int numero = distribuicao(gerador);

            // critical evita que as linhas de threads diferentes se misturem
            #pragma omp critical
            std::cout << "Thread " << id << " gerou: " << numero << "\n";
        }
    }
    return 0;
}
