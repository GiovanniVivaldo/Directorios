#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Nodo
{
    char Nombre[50];
    int Hijos;

    struct _Nodo *primerHijo;
    struct _Nodo *siguiente;
    struct _Nodo *ultimoHijo;
}
Nodo;

Nodo *Insertar(char Nombre[50])
{
    Nodo *nuevo;
    nuevo=(Nodo*)malloc(sizeof(Nodo));

	strcpy(nuevo->Nombre, Nombre);
    nuevo->Hijos=0;
	nuevo->primerHijo=NULL;
    nuevo->siguiente=NULL;
    nuevo->ultimoHijo=NULL;

    return nuevo;
}

Nodo* insertarRaiz(Nodo* nodo, char Nombre[50])
{
    Nodo* Raiz=NULL;
    Nodo* Nuevo;

    Nuevo=Insertar(Nombre);
    Raiz=Nuevo;
    nodo=Raiz;

    return Nuevo;
}

Nodo* insertarNodo(Nodo *nodo, char NombreR[50],char NombreN[50])
{
    if(strcmp(NombreR, nodo->Nombre)==0)
    {
        Nodo *nuevo;
        nuevo=Insertar(NombreN);

        if(nodo->Hijos==0)
        {
            nodo->Hijos=nodo->Hijos+1;
            nodo->primerHijo=nuevo;
            nodo->ultimoHijo=nuevo;
        }
        else
        {
            nodo->Hijos=nodo->Hijos+1;
            nodo->ultimoHijo->siguiente=nuevo;
            nodo->ultimoHijo=nuevo;
        }
    }
    else
    {
        if(nodo->Hijos>0)
        {
            Nodo *i=nodo->primerHijo;

            while(i !=NULL)
            {
                insertarNodo(i, NombreR, NombreN);
                i=i->siguiente;
            }
        }
        else
        {
            printf("La Carpeta Donde Quiere Guardar No Existe\n\n");
            system("pause");
        }
    }
}

void borrarNodo(Nodo *nodo, char Nombre[25])
{
    if(strcmp(Nombre, nodo->primerHijo->Nombre)==0)
    {
        Nodo * aux;

        aux=nodo->primerHijo->siguiente;
        nodo->primerHijo=NULL;
        nodo->Hijos=nodo->Hijos-1;
        nodo->primerHijo=aux;
    }
    else
    {
        if(nodo->Hijos>0)
        {
            Nodo *aux2;
            aux2=nodo->siguiente;

            while(aux2!=NULL)
            {
                borrarNodo(aux2, Nombre);
                aux2=aux2->siguiente;
            }
        }
    }
}

void ver(Nodo *nodo)
{
    printf("%s\n", nodo->Nombre);

    if(nodo->Hijos>0)
    {
        Nodo *aux=nodo->primerHijo;

        while(aux!=NULL)
        {
            printf("\n%s contiene el directorio ", nodo->Nombre);
            ver(aux);

            aux=aux->siguiente;
        }
    }
}

int main()
{
    Nodo *nodo=NULL;
    char Opcion;
    char Hijo[50], Padre[50];

    printf("Nombrar Raiz\n");
    fflush(stdin);
    gets(Padre);

    nodo=insertarRaiz(nodo, Padre);
    system("cls");

    do
    {
        printf("Raiz: ");
        ver(nodo);

        printf("\n*****MENU*****\n");
        printf("1.-Crear Directorio\n");
        printf("2.-Borrar Un Directorio\n");
        printf("3.-Salir\n");

        fflush( stdin );
        scanf("%c", &Opcion);

        switch(Opcion)
        {
            case '1':
                printf("\nNombre del Directorio Donde Desea Guardar:");

                fflush(stdin);
                gets(Padre);

                printf("\nNombre Del Dierctorio Nuevo:");

                fflush(stdin);
                gets(Hijo);

                insertarNodo(nodo, Padre, Hijo);

                system("cls");
            break;

            case '2':
                printf("\nNombre del Directorio que quiere borrar:");

                fflush(stdin);
                gets(Padre);

                borrarNodo(nodo,Padre);

                system("cls");
            break;

            default:
                if(Opcion!='3')
                {
                    printf("Opcion No Valida \n");

                    system("pause");
                    system("cls");
                }
            break;
        }
    }

    while (Opcion!='3');

    return 0;
}
