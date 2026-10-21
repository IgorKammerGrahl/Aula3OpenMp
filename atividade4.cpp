// Atividade 4 - Cláusula reduction
//
// Funcionamento:
//   reduction(operador : lista) cria uma cópia privada da variável para cada
//   thread, inicializada com o elemento neutro do operador (0 para +, 1 para *,
//   etc.). Cada thread acumula seus resultados parciais na própria cópia e, ao
//   final da região, o OpenMP combina todas as cópias com o operador indicado
//   e grava o resultado na variável original. Assim obtemos um acúmulo paralelo
//   correto sem precisar de critical/atomic a cada operação.
//   Operadores comuns: +, -, *, &, |, ^, &&, ||, min, max.
//
// Compilar: g++ -fopenmp atividade4.cpp -o atividade4

#include <iostream>
#include <omp.h>

int main() {
    const long long N = 1000000;
    long long soma = 0;

    // Cada thread soma uma parte dos números de 1 a N na sua cópia de "soma"
    #pragma omp parallel reduction(+:soma) num_threads(4)
    {
        int id = omp_get_thread_num();
        int nThreads = omp_get_num_threads();

        // Divisão cíclica manual: a thread 0 soma 1, 5, 9...; a thread 1 soma 2, 6, 10...
        for (long long i = id + 1; i <= N; i += nThreads)
            soma += i;  // escreve apenas na cópia privada: sem condição de corrida

        #pragma omp critical
        std::cout << "Thread " << id << ": soma parcial = " << soma << "\n";
    }
    // Aqui o OpenMP já somou as parciais de todas as threads em "soma"

    std::cout << "Soma total (paralela): " << soma << "\n";
    std::cout << "Valor esperado n(n+1)/2: " << N * (N + 1) / 2 << "\n";
    return 0;
}
