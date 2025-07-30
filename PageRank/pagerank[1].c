#include <stdio.h>
#include <math.h>

#define N 5  // Número de páginas (nós)
#define D 0.85  // Fator de amortecimento
#define TOLERANCE 0.0001  // Critério de convergência

// Função para calcular o PageRank
int calculatePageRank(double adjMatrix[N][N], double pageRank[N]) {
    int c = 0;
    double tempPageRank[N];
    double initialPR = 1.0 / N;  // Valor inicial de PageRank
    int converged = 0;
 
    // Inicializando os valores de PageRank
    for (int i = 0; i < N; i++) {

        pageRank[i] = initialPR;
    }

    // Iteração até a convergência
    while (!converged) {
        c++;
        
        printf("---------- %d ----------\n", c);
        for (int i = 0; i < N; i++) {
            printf("PageRank da pagina %d: %lf\n", i, pageRank[i]);
        }
        printf("---------- %d ----------\n\n", c);

        converged = 1;  // Presumimos convergência até que a diferença seja maior que a tolerância

        // Calculando novo PageRank para cada página
        for (int i = 0; i < N; i++) {
            tempPageRank[i] = (1.0 - D) / N;  // Componente de "teleportação"

            // Adicionando contribuições dos links recebidos
            for (int j = 0; j < N; j++) {
                if (adjMatrix[j][i] == 1) {  // Verificando se há link de j para i
                    int outLinks = 0;
                    for (int k = 0; k < N; k++) {
                        outLinks += adjMatrix[j][k];  // Contando links de saída da página j
                    }
                    if (outLinks > 0) {
                        tempPageRank[i] += D * (pageRank[j] / outLinks);  // Contribuição de j para i
                    }
                }
            }
        }

        // Verificando a convergência e atualizando os valores de PageRank
        for (int i = 0; i < N; i++) {
            if (fabs(tempPageRank[i] - pageRank[i]) > TOLERANCE) {
                converged = 0;
            }
            pageRank[i] = tempPageRank[i];
        }
    }
    return c;
}

int main() {
    // Matriz de adjacência representando o grafo da imagem
    double adjMatrix[N][N] = {
        {0, 1, 1, 0, 1},  // Página 0 tem links para páginas 1, 2 e 4
        {0, 0, 1, 1, 0},  // Página 1 tem links para páginas 2 e 3
        {0, 0, 0, 1, 1},  // Página 2 tem links para páginas 3 e 4
        {1, 0, 0, 0, 0},  // Página 3 tem link para página 0
        {1, 1, 0, 0, 0}   // Página 4 tem links para páginas 0 e 1
    };
    double pageRank[N];

    // Calculando o PageRank
    int c = calculatePageRank(adjMatrix, pageRank);

    // Exibindo os resultados
    for (int i = 0; i < N; i++) {
        printf("PageRank da pagina %d: %lf\n", i, pageRank[i]);
    }
        printf("Iteracoes: %d", c);

    return 0;
}
