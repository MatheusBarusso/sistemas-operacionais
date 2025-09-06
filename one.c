#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <limits.h>

#define N 1000
long long int A[N];
long long int E;

long long int calc(long long int a, long long int b) {
    while (b != 0) {
        long long int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

void *MDC(void* arg) {
    int j = (int)(long)arg;
    if (j > E){
        long long int result = calc(E, A[j]);
        printf("%lld \n", result);
    }
    return NULL;
}

int main() {
    int rc;
    pthread_t  threads[N];

    scanf("%lld", &E);

    for (int j = 0; j < N; j++) {
        A[j] = LLONG_MAX - j;
        rc = pthread_create(&threads[j], NULL, MDC, (void*)(long)j);
        if (rc) {
            printf("Erro! Código %d \n", rc);
            exit(-1);
        }
    }

    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}