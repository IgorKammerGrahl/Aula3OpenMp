// Atividade 5 - Cláusula if
//
// Funcionamento:
//   if(expressão) torna a paralelização CONDICIONAL. Se a expressão for
//   verdadeira, a região é executada em paralelo normalmente; se for falsa,
//   a região é executada por apenas uma thread (a mestre), ou seja, de forma
//   sequencial. É usada para evitar o custo de criar threads quando o volume
//   de trabalho é pequeno demais para compensar (o overhead seria maior que
//   o ganho).
//
// Compilar: g++ -fopenmp atividade5.cpp -o atividade5

#include <iostream>
#include <omp.h>

// Abaixo deste tamanho não vale a pena paralelizar
const int LIMIAR = 1000;

void processar(int tamanho) {
    // Só cria o time de threads se o problema for grande o suficiente
    #pragma omp parallel if(tamanho > LIMIAR) num_threads(4)
    {
        // Apenas a thread 0 imprime, para não repetir a mensagem
        if (omp_get_thread_num() == 0) {
            std::cout << "Tamanho " << tamanho << ": "
                      << (omp_in_parallel() ? "executou em PARALELO" : "executou SEQUENCIALMENTE")
                      << " com " << omp_get_num_threads() << " thread(s)\n";
        }
    }
}

int main() {
    processar(100);     // condição falsa: 1 thread
    processar(100000);  // condição verdadeira: 4 threads
    return 0;
}
