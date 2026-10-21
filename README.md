# Aula 03 - Cláusulas do `#pragma omp parallel`

Aluno: Igor Kammer Grahl

| Arquivo | Conteúdo |
|---|---|
| `atividade1.cpp` | Cláusula `private` |
| `atividade2.cpp` | Cláusula `shared` |
| `atividade3.cpp` | Cláusula `firstprivate` |
| `atividade4.cpp` | Cláusula `reduction` |
| `atividade5.cpp` | Cláusula `if` |
| `atividade6.cpp` | N threads, cada uma gera 10 números aleatórios (0 a 1000) |
| `atividade7.cpp` | Igual à 6, com início e fim do intervalo informados pelo usuário |
| `atividade8.cpp` | Igual à 7, mostrando a somatória de todos os números gerados |
| `atividade9_default.cpp` | Cláusula `default`: dois exemplos (`default(shared)` e `default(none)`) |
| `atividade9_copyin.cpp` | Cláusula `copyin`: dois exemplos com variáveis `threadprivate` |

A explicação do funcionamento de cada cláusula está no comentário no topo de cada arquivo.

## Compilar e executar

Todos de uma vez:

```bash
make
./atividade1
```

Ou um arquivo por vez:

```bash
g++ -fopenmp atividade1.cpp -o atividade1
./atividade1
```
