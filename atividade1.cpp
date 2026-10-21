// Atividade 1 - Cláusula private
//
// Funcionamento:
//   private(lista) faz com que cada thread do time receba sua PRÓPRIA cópia
//   das variáveis listadas. Essas cópias:
//     - NÃO são inicializadas com o valor que a variável tinha antes da região
//       (o valor inicial é indefinido, então é preciso atribuir antes de ler);
//     - são descartadas ao fim da região paralela, ou seja, o valor da
//       variável original não é alterado pelo que as threads fizeram.
//   Variáveis declaradas DENTRO do bloco paralelo já são privadas por padrão.
//
// Compilar: g++ -fopenmp atividade1.cpp -o atividade1

#include <iostream>
#include <omp.h>

int main() {
    int x = 10;
    std::cout << "Antes da região paralela: x = " << x << "\n";

    // Cada uma das 4 threads terá sua própria variável x, independente das demais
    #pragma omp parallel private(x) num_threads(4)
    {
        int id = omp_get_thread_num();  // declarada dentro do bloco: já é privada

        // A cópia privada começa com lixo, então atribuímos um valor antes de usar.
        // Cada thread escreve apenas na sua cópia, sem condição de corrida.
        x = id * 100;

        // critical garante que apenas uma thread por vez escreva no console
        #pragma omp critical
        std::cout << "Thread " << id << ": x privado = " << x << "\n";
    }

    // As cópias privadas deixaram de existir: o x original continua valendo 10
    std::cout << "Depois da região paralela: x = " << x << "\n";
    return 0;
}
