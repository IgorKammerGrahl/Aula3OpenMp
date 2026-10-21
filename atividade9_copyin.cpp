// Atividade 9 (parte 2) - Cláusula copyin
//
// Funcionamento:
//   copyin(lista) é usada em conjunto com variáveis threadprivate.
//   Uma variável threadprivate é global/estática, mas cada thread possui sua
//   própria cópia, que PERSISTE entre diferentes regiões paralelas (diferente
//   do private, que nasce e morre com a região).
//   Ao entrar em uma região paralela, as cópias das threads que não são a
//   mestre NÃO recebem o valor atual da mestre. A cláusula copyin resolve isso:
//   no início da região, copia o valor da cópia da thread MESTRE para as cópias
//   de todas as outras threads do time.
//
// Compilar: g++ -fopenmp atividade9_copyin.cpp -o atividade9_copyin

#include <iostream>
#include <omp.h>

// Variáveis threadprivate precisam ser globais ou static
int contador = 0;
#pragma omp threadprivate(contador)

double fatorEscala = 1.0;
#pragma omp threadprivate(fatorEscala)

// Exemplo 1 - comparação com e sem copyin
// A mestre altera seu contador para 5. Sem copyin, as outras threads continuam
// com o valor inicial (0); com copyin, todas começam com 5.
void exemploContador() {
    std::cout << "--- Exemplo 1: contador threadprivate ---\n";
    contador = 5;  // altera apenas a cópia da thread mestre

    std::cout << "Sem copyin:\n";
    #pragma omp parallel num_threads(4)
    {
        #pragma omp critical
        std::cout << "  Thread " << omp_get_thread_num()
                  << ": contador = " << contador << "\n";
    }

    std::cout << "Com copyin(contador):\n";
    #pragma omp parallel num_threads(4) copyin(contador)
    {
        // Todas partem de 5 e incrementam a própria cópia de forma independente
        contador += omp_get_thread_num();

        #pragma omp critical
        std::cout << "  Thread " << omp_get_thread_num()
                  << ": contador = " << contador << "\n";
    }
    std::cout << "\n";
}

// Exemplo 2 - distribuir uma configuração definida pela mestre
// A mestre define o fator de escala (poderia vir do usuário ou de um arquivo).
// copyin replica esse valor para todas as threads, que depois ajustam sua
// cópia individualmente. Como a variável é threadprivate, o ajuste de cada
// thread continua valendo na região paralela seguinte.
void exemploConfiguracao() {
    std::cout << "--- Exemplo 2: configuração replicada ---\n";
    fatorEscala = 2.5;  // definido pela mestre, fora da região paralela

    #pragma omp parallel num_threads(4) copyin(fatorEscala)
    {
        int id = omp_get_thread_num();
        fatorEscala *= (id + 1);  // cada thread personaliza a sua cópia
    }

    // Segunda região SEM copyin: cada thread ainda enxerga o valor que
    // ela mesma deixou na região anterior (persistência do threadprivate)
    #pragma omp parallel num_threads(4)
    {
        #pragma omp critical
        std::cout << "  Thread " << omp_get_thread_num()
                  << ": fatorEscala = " << fatorEscala << "\n";
    }
}

int main() {
    // A persistência de threadprivate entre regiões só é garantida com o
    // ajuste dinâmico de threads desligado e o mesmo número de threads
    omp_set_dynamic(0);

    exemploContador();
    exemploConfiguracao();
    return 0;
}
