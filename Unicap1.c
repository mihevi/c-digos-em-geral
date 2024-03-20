#include <stdio.h>
#include <stdlib.h>
int estaPresente(int *vetor, int tamanho, int elemento) {
    for (int i = 0; i < tamanho; i++) {
        if (vetor[i] == elemento) {
            return 1;
        }
    }
    return 0;
}
int main() {
    int tamanho;
    printf("Digite o tamanho dos vetores: ");
    scanf("%d", &tamanho);
    int *vetorA = (int *)malloc(tamanho * sizeof(int));
    int *vetorB = (int *)malloc(tamanho * sizeof(int));
    int *vetorC = (int *)malloc(2 * tamanho * sizeof(int));
    int *vetorAminusB = (int *)malloc(tamanho * sizeof(int));
    int *vetorBminusA = (int *)malloc(tamanho * sizeof(int));
    if (vetorA == NULL || vetorB == NULL || vetorC == NULL || vetorAminusB == NULL || vetorBminusA == NULL) {
        printf("Erro ao alocar memória\n");
        return 1;
    }
    printf("Digite os valores para o vetor A:\n");
    for (int i = 0; i < tamanho; i++) {
        printf("Elemento %d: ", i);
        scanf("%d", &vetorA[i]);
    }
    printf("Digite os valores para o vetor B:\n");
    for (int i = 0; i < tamanho; i++) {
        printf("Elemento %d: ", i);
        scanf("%d", &vetorB[i]);
    }
    int tamanhoC = 0;
    for (int i = 0; i < tamanho; i++) {
        if (!estaPresente(vetorC, tamanhoC, vetorA[i])) {
            vetorC[tamanhoC] = vetorA[i];
            tamanhoC++;
        }
        if (!estaPresente(vetorC, tamanhoC, vetorB[i])) {
            vetorC[tamanhoC] = vetorB[i];
            tamanhoC++;
        }
    }
    int tamanhoAminusB = 0;
    for (int i = 0; i < tamanho; i++) {
        if (!estaPresente(vetorB, tamanho, vetorA[i])) {
            vetorAminusB[tamanhoAminusB] = vetorA[i];
            tamanhoAminusB++;
        }
    }
    int tamanhoBminusA = 0;
    for (int i = 0; i < tamanho; i++) {
        if (!estaPresente(vetorA, tamanho, vetorB[i])) {
            vetorBminusA[tamanhoBminusA] = vetorB[i];
            tamanhoBminusA++;
        }
    }
    printf("\nVetor soma (elementos únicos):\n");
    for (int i = 0; i < tamanhoC; i++) {
        printf("%d ", vetorC[i]);
    }
    printf("\n");
    printf("\nDiferença vetorA - vetorB:\n");
    for (int i = 0; i < tamanhoAminusB; i++) {
        printf("%d ", vetorAminusB[i]);
    }
    printf("\n");
    printf("\nDiferença vetorB - vetorA:\n");
    for (int i = 0; i < tamanhoBminusA; i++) {
        printf("%d ", vetorBminusA[i]);
    }
    printf("\n");
    free(vetorA);
    free(vetorB);
    free(vetorC);
    free(vetorAminusB);
    free(vetorBminusA);
    return 0;
}