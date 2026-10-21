// Atividade 9 (parte 1) - Cláusula default
//
// Funcionamento:
//   default(...) define o escopo PADRÃO das variáveis que são usadas dentro da
//   região paralela mas não aparecem em nenhuma cláusula explícita
//   (private, shared, firstprivate, reduction...). Em C/C++ as opções são:
//     - default(shared): variáveis externas não listadas são compartilhadas.
//       É o comportamento implícito do OpenMP quando a cláusula é omitida.
//     - default(none): NÃO existe escopo padrão. Toda variável externa usada na
//       região precisa ser listada explicitamente; caso contrário o compilador
//       acusa erro. É considerada boa prática, pois obriga o programador a
//       decidir conscientemente o que é compartilhado e o que é privado,
//       evitando condições de corrida acidentais.
//   (O OpenMP 5.1 também permite default(private) e default(firstprivate) em
//   C/C++, mas o suporte varia entre compiladores.)
//
// Compilar: g++ -fopenmp atividade9_default.cpp -o atividade9_default

#include <iostream>
#include <omp.h>

// Exemplo 1 - default(shared)
// As variáveis "vetor" e "tamanho" não aparecem em nenhuma cláusula, mas são
// compartilhadas por causa do default(shared). Só "id" precisa ser privada,
// e por ter sido declarada dentro do bloco ela já é.
void exemploDefaultShared() {
    std::cout << "--- Exemplo 1: default(shared) ---\n";
    const int TAM = 8;
    int vetor[TAM];
    int tamanho = TAM;

    #pragma omp parallel default(shared) num_threads(4)
    {
        int id = omp_get_thread_num();
        int nThreads = omp_get_num_threads();

        // Cada thread preenche posições diferentes do vetor compartilhado
        for (int i = id; i < tamanho; i += nThreads)
            vetor[i] = i * 10;
    }

    for (int i = 0; i < TAM; i++) std::cout << vetor[i] << " ";
    std::cout << "\n\n";
}

// Exemplo 2 - default(none)
// Aqui somos obrigados a declarar o escopo de TODAS as variáveis externas.
// Se removermos "limite" da cláusula shared, por exemplo, o código não compila:
//   error: 'limite' not specified in enclosing 'parallel'
void exemploDefaultNone() {
    std::cout << "--- Exemplo 2: default(none) ---\n";
    int limite = 100;  // lido por todas as threads -> shared
    int soma = 0;      // acumulado de todas as threads -> reduction
    int temp;          // rascunho de cada thread -> private

    #pragma omp parallel default(none) shared(limite, std::cout) private(temp) \
                         reduction(+:soma) num_threads(4)
    {
        int id = omp_get_thread_num();
        int nThreads = omp_get_num_threads();

        for (int i = id + 1; i <= limite; i += nThreads) {
            temp = i * 2;  // cada thread usa sua própria cópia de temp
            soma += temp;
        }

        #pragma omp critical
        std::cout << "Thread " << id << " somou " << soma << "\n";
    }

    std::cout << "Soma dos dobros de 1 a " << limite << ": " << soma
              << " (esperado: " << limite * (limite + 1) << ")\n\n";
}

int main() {
    exemploDefaultShared();
    exemploDefaultNone();
    return 0;
}
