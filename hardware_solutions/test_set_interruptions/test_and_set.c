#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdatomic.h>

// Variable compartida
int contador = 0;

// Lock usando test-and-set
atomic_bool lock = ATOMIC_VAR_INIT(false);

// Implementación de Test-and-Set usando operaciones atómicas 
// 1. Lee el valor actual del lock
// 2. Lo establece en true
// 3. Retorna el valor anterior

bool test_and_set(atomic_bool *target) {
    return atomic_exchange_explicit(target, true, memory_order_acquire);
}


// Mientras test_and_set retorne true (lock ocupado),
// el proceso sigue intentando (espera activa/busy waiting)
void acquire_lock() {
    while (test_and_set(&lock)) {
        // Espera activa
    }
}

// Liberar el lock, lock = false
void release_lock() {
    atomic_store_explicit(&lock, false, memory_order_release);
}

// Sección crítica
void seccion_critica(int id_hilo) {
    printf("  -> Hilo %d en SECCIÓN CRÍTICA\n", id_hilo);
    printf("  -> Hilo %d: Incrementando contador de %d", id_hilo, contador);
    
    // Simular operación compleja
    int temp = contador;
    usleep(100000); // 100ms
    contador = temp + 1;
    
    printf(" a %d\n", contador);
}

// Proceso con protección usando test-and-set
void* proceso_protegido(void* arg) {
    int id = *(int*)arg;
    
    printf("\nHilo %d: Intentando adquirir el lock...\n", id);
    
    // Adquirir lock usando test-and-set
    acquire_lock();
    printf("Hilo %d: Lock ADQUIRIDO\n", id);
    
    // SECCIÓN CRÍTICA
    seccion_critica(id);
    // FIN SECCIÓN CRÍTICA
    
    // Liberar lock
    release_lock();
    printf("Hilo %d: Lock LIBERADO\n", id);
    
    return NULL;
}

// Demostración visual del funcionamiento de test-and-set


int main() {
    printf("\n");
    printf("===========================================================\n");
    printf("        SOLUCIÓN DE HARDWARE: INSTRUCCIÓN TEST-AND-SET    \n");
    printf("===========================================================\n\n");
    
    contador = 0;
    atomic_store(&lock, false);
    
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
    
    printf("\n===========================================================\n");
    printf("Contador final: %d (esperado: 3)\n", contador);
    if (contador == 3) {
        printf("Exclusión mutua exitosa\n");
    }
    printf("===========================================================\n\n");
    
    return 0;
}
