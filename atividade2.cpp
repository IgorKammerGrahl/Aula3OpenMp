// Atividade 2 - Cláusula shared
//
// Funcionamento:
//   shared(lista) indica que as variáveis listadas são COMPARTILHADAS: existe
//   uma única instância na memória e todas as threads leem e escrevem nela.
//   Alterações feitas por uma thread são visíveis às demais e permanecem após
//   a região paralela. Por isso, escritas concorrentes na mesma posição exigem
//   sincronização (atomic, critical, reduction...) para evitar condição de corrida.
//   Variáveis declaradas fora da região são shared por padrão.
//
// Compilar: g++ -fopenmp atividade2.cpp -o atividade2

#include <iostream>
#include <omp.h>

int main() {
    const int N_THREADS = 4;
    int quadrados[N_THREADS] = {0};  // vetor compartilhado
    int contador = 0;                // contador compartilhado

    #pragma omp parallel shared(quadrados, contador) num_threads(N_THREADS)
    {
        int id = omp_get_thread_num();

        // Seguro sem sincronização: cada thread escreve em uma posição DIFERENTE
        quadrados[id] = id * id;

        // Todas as threads escrevem na MESMA variável: sem o atomic,
        // incrementos poderiam se perder (condição de corrida)
        #pragma omp atomic
        contador++;
    }

    // Os valores escritos pelas threads continuam disponíveis após a região
    for (int i = 0; i < N_THREADS; i++)
        std::cout << "quadrados[" << i << "] = " << quadrados[i] << "\n";
    std::cout << "Threads que incrementaram o contador: " << contador << "\n";
    return 0;
}
