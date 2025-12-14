#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdatomic.h>

int contador = 0;
atomic_int lock = ATOMIC_VAR_INIT(0);  // 0 = libre, 1 = ocupado

// intercambia atómicamente el valor de target con value
int xchg(atomic_int *target, int value) {
    return atomic_exchange_explicit(target, value, memory_order_acquire);
}

// Intenta intercambiar el lock con el valor 1 (ocupado)
void acquire_lock() {
    int key = 1;  // lock en 1 (ocupado)
    
    // Mientras XCHG retorne 1 (lock ocupado), seguir intentando
    while (xchg(&lock, key) == 1) {
        // Espera activa (busy waiting)
    }
}

// Liberar el lock
void release_lock() {
    int key = 0; 
    xchg(&lock, key);
}

void seccion_critica(int id_hilo) {
    printf("  -> Hilo %d ejecutando SECCIÓN CRÍTICA\n", id_hilo);
    printf("  -> Hilo %d: contador = %d", id_hilo, contador);
    
    int temp = contador;
    usleep(80000); // 80ms
    contador = temp + 1;
    
    printf("  -> %d\n", contador);
}

void* proceso_protegido(void* arg) {
    int id = *(int*)arg;
    
    printf("\nHilo %d: Intentando adquirir lock...\n", id);
    
    acquire_lock(); // Adquirir lock
    printf("Hilo %d: Lock ADQUIRIDO (usando XCHG)\n", id);
    
    seccion_critica(id);
    
    release_lock(); // Liberar lock
    printf("Hilo %d: Lock LIBERADO\n", id);
    
    return NULL;
}

int main() {
    printf("\n");
    printf("==========================================================\n");
    printf("         SOLUCIÓN DE HARDWARE: INSTRUCCIÓN XCHG           \n");
    printf("==========================================================\n\n");
    
    contador = 0;
    atomic_store(&lock, 0);
    
    pthread_t hilos[3];
    int ids[3] = {1, 2, 3};
    
    // Crear hilos
    for (int i = 0; i < 3; i++) {
        pthread_create(&hilos[i], NULL, proceso_protegido, &ids[i]);
    }
    
    // Esperar a que terminen
    for (int i = 0; i < 3; i++) {
        pthread_join(hilos[i], NULL);
    }
    
    printf("\n==========================================================\n");
    printf("Contador final: %d (esperado: 3)\n", contador);
    if (contador == 3) {
        printf("Exclusión mutua exitosa\n");
    }
    printf("==========================================================\n\n");
    
    return 0;
}
