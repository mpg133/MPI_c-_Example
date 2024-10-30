#include <stdio.h>
#include "mpi.h"
#include <unistd.h>
#include <stdlib.h>

//argc= Puntero al número de argumentos 
//argv= Puntero al vector de argumentos



int sched_getcpu();
//int MPI_Init (int *argc, char ***argv)
using namespace std;
 
int main(int argc, char *argv[])
{
    //Declaración de variables
    int process_Rank, size_Of_Cluster, namelen;
    char processor_name[MPI_MAX_PROCESSOR_NAME];

    //inicializa todas las estructuras de datos necesarias 
    //para permitir la comunicación entre procesos basados en el envío de mensajes
    //Se tiene que llamar una sola vez antes de cualquier rutina MPI
    MPI_Init(&argc,&argv);

    //determina el tamaño del comunicador seleccionado
    //numero de procesos actualmente asociados a este
    MPI_Comm_size(MPI_COMM_WORLD,&size_Of_Cluster);

    //Determina el rango (identificador)
    // del proceso que lo llama dentro del comunicador seleccionado.
    MPI_Comm_rank(MPI_COMM_WORLD,&process_Rank);

    MPI_Get_processor_name(processor_name,&namelen);

    //Reparto de contenido
    //bucle principal del programa
    printf(" PID: %d Hello from process %d out of %d on %s processor %d \n",
                getppid(), process_Rank, size_Of_Cluster, processor_name, sched_getcpu());
    

    if(process_Rank==1){
        //código que ejecuta el proceso elegido unicamente
        printf("\nHola desde el procesador %d\n",process_Rank);
    }


    //Finaliza la comunicación paralela entre los procesos.
    //Tras esto no se pueden enviar mensajes entre ellos
    //sin esta instrucción al inicio.
    //Corta la comunicación entre los procesos 
    //y elimina los tipos de datos creados para ello.
    MPI_Finalize();


    return 0;
}


int sched_getcpu(){

    return 0;

}