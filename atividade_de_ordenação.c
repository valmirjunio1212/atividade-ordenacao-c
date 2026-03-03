#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 1000

void copiarVetor(int o[], int d[], int n){
    int i;
    for(i = 0; i < n; i++) 
        d[i] = o[i];
}

void gerarVetor(int v[], int n, int tipo){
    int i;

    if(tipo == 1)
        for(i = 0; i < n; i++) 
            v[i] = rand() % 10000;
    else if(tipo == 2)
        for(i = 0; i < n; i++) 
            v[i] = i;
    else
        for(i = 0; i < n; i++) 
            v[i] = n - i;
}

void bubbleSort(int v[], int n){
    int i, j, temp;
    for(i = 0; i < n - 1; i++)
        for(j = 0; j < n - 1 - i; j++)
            if(v[j] > v[j+1]){
                temp = v[j];
                v[j] = v[j+1];
                v[j+1] = temp;
            }
}

void selectionSort(int v[], int n){
    int i, j, menor, temp;
    for(i = 0; i < n - 1; i++){
        menor = i;
        for(j = i + 1; j < n; j++)
            if(v[j] < v[menor]) 
                menor = j;

        temp = v[i];
        v[i] = v[menor];
        v[menor] = temp;
    }
}

void insertionSort(int v[], int n){
    int i, j, chave;
    for(i = 1; i < n; i++){
        chave = v[i];
        j = i - 1;

        while(j >= 0 && v[j] > chave){
            v[j+1] = v[j];
            j--;
        }
        v[j+1] = chave;
    }
}

int particiona(int v[], int inicio, int fim){
    int pivo = v[fim];
    int i = inicio - 1, j, temp;

    for(j = inicio; j < fim; j++){
        if(v[j] < pivo){
            i++;
            temp = v[i];
            v[i] = v[j];
            v[j] = temp;
        }
    }

    temp = v[i+1];
    v[i+1] = v[fim];
    v[fim] = temp;

    return i + 1;
}

void quickSort(int v[], int inicio, int fim){
    if(inicio < fim){
        int pos = particiona(v, inicio, fim);
        quickSort(v, inicio, pos - 1);
        quickSort(v, pos + 1, fim);
    }
}

void merge(int v[], int inicio, int meio, int fim){
    int i = inicio, j = meio + 1, k = 0;
    int temp[TAM];

    while(i <= meio && j <= fim){
        if(v[i] < v[j]) 
            temp[k++] = v[i++];
        else 
            temp[k++] = v[j++];
    }

    while(i <= meio) 
        temp[k++] = v[i++];
    while(j <= fim) 
        temp[k++] = v[j++];

    for(i = inicio, k = 0; i <= fim; i++, k++) 
        v[i] = temp[k];
}

void mergeSort(int v[], int inicio, int fim){
    if(inicio < fim){
        int meio = (inicio + fim) / 2;
        mergeSort(v, inicio, meio);
        mergeSort(v, meio + 1, fim);
        merge(v, inicio, meio, fim);
    }
}

void shellSort(int v[], int n){
    int gap, i, j, temp;

    for(gap = n/2; gap > 0; gap /= 2){
        for(i = gap; i < n; i++){
            temp = v[i];
            j = i;

            while(j >= gap && v[j-gap] > temp){
                v[j] = v[j-gap];
                j -= gap;
            }
            v[j] = temp;
        }
    }
}

void executar(int op, int original[], int n){
    int v[TAM];
    copiarVetor(original, v, n);

    clock_t inicio = clock();

    switch(op){
        case 1: bubbleSort(v, n); break;
        case 2: selectionSort(v, n); break;
        case 3: insertionSort(v, n); break;
        case 4: quickSort(v, 0, n-1); break;
        case 5: mergeSort(v, 0, n-1); break;
        case 6: shellSort(v, n); break;
    }

    clock_t fim = clock();
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("Tempo: %f segundos\n", tempo);
}

int main(){

    int original[TAM];
    int op, tipo;

    srand(time(NULL));

    printf("1 - Aleatorio\n2 - Ordenado\n3 - Inverso\n");
    scanf("%d", &tipo);

    gerarVetor(original, TAM, tipo);

    do{
        printf("\n1 - Bubble Sort\n");
        printf("2 - Selection Sort\n");
        printf("3 - Insertion Sort\n");
        printf("4 - Quick Sort\n");
        printf("5 - Merge Sort\n");
        printf("6 - Shell Sort\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &op);

        if(op >= 1 && op <= 6)
            executar(op, original, TAM);

    }while(op != 0);

    return 0;
}
