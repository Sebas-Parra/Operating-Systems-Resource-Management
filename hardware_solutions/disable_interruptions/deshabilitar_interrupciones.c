#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>

int contador = 0;
pthread_mutex_t mutex_interrupciones = PTHREAD_MUTEX_INITIALIZER;

void deshabilitar_interrupciones() {
    pthread_mutex_lock(&mutex_interrupciones);
    printf("  [Interrupciones DESHABILITADAS - Proceso tiene control exclusivo]\n");
}

void habilitar_interrupciones() {
    printf("  [Interrupciones HABILITADAS - Otros procesos pueden ejecutar]\n");
    pthread_mutex_unlock(&mutex_interrupciones);
}

void seccion_critica(int id_hilo) {
    printf("Hilo %d: Incrementando contador de %d a %d\n", 
           id_hilo, contador, contador + 1);
    
    int temp = contador;
    usleep(100000); // 100ms - simula operación que toma tiempo
    contador = temp + 1;
    
    printf("Hilo %d: Contador actualizado a %d\n", id_hilo, contador);
}

// Función ejecutada por cada hilo
void* proceso_hilo(void* arg) {
    int id = *(int*)arg;
    
    printf("\nHilo %d: Intentando entrar a sección crítica\n", id);
    
    deshabilitar_interrupciones();
    
    seccion_critica(id);
    
    habilitar_interrupciones();
    
    printf("Hilo %d: Salió de sección crítica\n\n", id);
    
    return NULL;
}

int main() {
    printf("\n");
    printf("============================================================\n");
    printf("     SOLUCIÓN DE HARDWARE: DESHABILITAR INTERRUPCIONES     \n");
    printf("============================================================\n\n");
    
    contador = 0;
    pthread_t hilos[3];
    int ids[3] = {1, 2, 3};
    
    // Crear hilos
    for (int i = 0; i < 3; i++) {
        pthread_create(&hilos[i], NULL, proceso_hilo, &ids[i]);
    }
    
    // Esperar a que terminen
    for (int i = 0; i < 3; i++) {
        pthread_join(hilos[i], NULL);
    }
    
    printf("\n============================================================\n");
    printf("Contador final: %d (esperado: 3)\n", contador);
    if (contador == 3) {
        printf("Exclusión mutua exitosa\n");
    }
    printf("===========================================================\n\n");
    
    pthread_mutex_destroy(&mutex_interrupciones);
    return 0;
}
