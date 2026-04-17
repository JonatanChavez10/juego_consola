#include <iostream>
#include <iomanip>
#include "Funciones.h"
#include "rlutil.h"
using namespace std;

void CartelPrimeroArranca(string Nombre)//Recibe como parametro un string que luego muestra por pantalla quien arranca la partida
{
    rlutil::hidecursor();
    rlutil::locate(66,10);
    cout<<"Comienza: "<<Nombre<<endl;
    rlutil::locate(1,21);
    cout<<"Presione cualquier tecla para continuar"<<endl;
    rlutil::anykey();
    rlutil::cls();

}
int DeterminarOrden()//Retorna un valor aleatoria entre el 1 y 2
{
    return rand()%2+1;
}
void ModoDosJugadores(int &Puntos,int &Puntos2, string &Nombre,string &Nombre2,int AnchoConsola)//recibe 4 variables por referencia que se utiliza para desarrolla el juego para dos
{

    const int TAm1 = 6, TAm2 = 3;
    int ContRonda = 0, VDadosJugador1[TAm1] {}, VDadosJugador2[TAm1] {};
    int VIntentosJugador1[TAm2] {}, VIntentosJugador2[TAm2] {},VDuplicado[TAm1] {};
    int ContadorIntentosJugador1, ContadorIntentosJugador2;
    bool EscaleraJugador1, sexteto6Jugador1, sextetoJugador1;
    bool EscaleraJugador2, sexteto6Jugador2, sextetoJugador2;
    int RondaEmpate = 0;
    int IntentosEmpateJugador1 = 0, IntentosEmpateJugador2 = 0;
    int PosicionJugador1,PosicionJugador2,PrimeroEnComenzar,GanadorAleatorio;
    string VariabAuxNombre;
    rlutil::cls();
    rlutil::setColor(rlutil::BLACK);
    rlutil::setBackgroundColor(rlutil::GREEN);

    cout << "Ingrese nombre del Jugador 1: ";

    getline(cin, Nombre);

    cout << "Ingrese nombre del Jugador 2: ";
    getline(cin, Nombre2);

    system("cls");
    PrimeroEnComenzar=DeterminarOrden();// Determina quién comienza primero
    EfectoBarraCargando(61,10);//Simulamos el proceso de seleccion de quien comienza primero
    if(PrimeroEnComenzar==2)// Intercambia nombres si el segundo jugador comienza primero
    {
        VariabAuxNombre=Nombre;
        Nombre=Nombre2;
        Nombre2=VariabAuxNombre;
    }
    CartelPrimeroArranca(Nombre);// Muestra el cartel del jugador que comienza

    while ((Puntos < 100 && Puntos2 < 100) && ContRonda < 6)//ciclo que maneja la partida completa de los dos jugadores
    {
        ContRonda++;

        ContadorIntentosJugador1 = 0;

        if(ContRonda!=1)//Con este if evitamos el cartel al comienzo
        {
            CartelTurnoDosJugadores(Nombre,Nombre2,ContRonda,Puntos2,Puntos);

        }
        ponerCero(VIntentosJugador1, TAm2);// Inicializa el vector de intentos del jugador 1 a cero
        sexteto6Jugador1=false;
        while ((ContadorIntentosJugador1 < 3)&&(sexteto6Jugador1!=true) )// Ciclo para los intentos del jugador 1
        {


            LanzamientoDados(VDadosJugador1, TAm1);// Lanza los dados para el jugador 1
            //ElegirDados (VDadosJugador1,TAm1);
            EncabezadoJuego (Nombre,Puntos,ContRonda,AnchoConsola); // Muestra el encabezado del juego
            copiarVector(VDadosJugador1,VDuplicado,TAm1);// Copia el vector de dados a un duplicado
            EscaleraJugador1 = ComprobarEscalera(VDuplicado, TAm1);// Comprueba si hay una escalera
            sexteto6Jugador1 = ComprobarSexteto6(VDadosJugador1, TAm1);// Comprueba si hay un sexteto de 6
            sextetoJugador1 = ComprobarSexteto(VDadosJugador1, TAm1);// Comprueba si hay un sexteto

            if (EscaleraJugador1) // Si hay una escalera, actualiza los puntos, muestra el intento y finaliza el juego
            {



                if(ContadorIntentosJugador1>0)
                {
                    rlutil::locate(2,4);
                    cout<<"Maximo puntaje de la ronda: "<<VIntentosJugador1[PosicionJugador1]<<endl;
                }
                VIntentosJugador1 [ContadorIntentosJugador1]=100;
                PosicionJugador1 = maximoVector(VIntentosJugador1, TAm2);
                rlutil::locate(2,5);
                cout<<"Intento numero: "<<ContadorIntentosJugador1+1<<endl;
                rlutil::locate(2,8);
                cout<<"Presionar cualquier tecla para lanzar los dados"<<endl;
                rlutil::anykey();
                MostrarIntento(VDadosJugador1, TAm1);
                rlutil::locate(2,4);
                cout<<"Maximo puntaje de la ronda: "<<VIntentosJugador1[PosicionJugador1]<<endl;
                rlutil::locate(2,21);
                cout<<"Presionar cualquier tecla para continuar"<<endl;
                rlutil::anykey();
                Puntos += 100;
                CartelGanador(Nombre,Puntos);
                return;
            }
            else
            {
                if (sexteto6Jugador1)
                {


                    Puntos = 0;
                }
                else
                {
                    if (sextetoJugador1)
                    {
                        VIntentosJugador1[ContadorIntentosJugador1] = VDadosJugador1[ContadorIntentosJugador1] * 10;



                    }
                    else
                    {
                        VIntentosJugador1[ContadorIntentosJugador1] = sumarVector(VDadosJugador1, TAm1);



                    }
                }
            }

            if(ContadorIntentosJugador1>0)//solo muestro el puntaje maximo de la tirada si es su segundo inteto o mas
            {
                rlutil::locate(2,4);
                cout<<"Maximo puntaje de la ronda: "<<VIntentosJugador1[PosicionJugador1]<<endl;
            }
            PosicionJugador1 = maximoVector(VIntentosJugador1, TAm2);//busco el mayo valor que se guardo en el vector intento
            rlutil::locate(2,5);
            cout<<"Intento numero: "<<ContadorIntentosJugador1+1<<endl;


            rlutil::locate(2,8);
            cout<<"Presionar cualquier tecla para lanzar los dados"<<endl;
            rlutil::anykey();
            MostrarIntento(VDadosJugador1, TAm1);
            rlutil::locate(2,4);
            cout<<"Maximo puntaje de la ronda: "<<VIntentosJugador1[PosicionJugador1]<<endl;//vuelvo a usar la linea del maximo valor en el v intento para que en intento 1 me muestre junto a los dados su puntaje y en las siguientes se modifica si es necesario
            rlutil::locate(2,21);
            cout<<"Presionar cualquier tecla para continuar"<<endl;
            rlutil::anykey();
            rlutil::cls();
            ContadorIntentosJugador1++;
        }


        if (sexteto6Jugador1!=true)//evaluo si hay sexteto para no sumar ningun punto
        {
            Puntos += VIntentosJugador1[PosicionJugador1];
        }


        ContadorIntentosJugador2 = 0;//inicializo el contador de intento


        CartelTurnoDosJugadores(Nombre2,Nombre,ContRonda,Puntos,Puntos2);

        sexteto6Jugador2=false;
        ponerCero(VIntentosJugador2, TAm2);
        while ((ContadorIntentosJugador2 < 3)&&(sexteto6Jugador2!=true))
        {


            LanzamientoDados(VDadosJugador2, TAm1);
            //ElegirDados (VDadosJugador2,TAm1);
            EncabezadoJuego (Nombre2,Puntos2,ContRonda,AnchoConsola);
            copiarVector(VDadosJugador2,VDuplicado,TAm1);
            EscaleraJugador2 = ComprobarEscalera(VDuplicado, TAm1);
            sexteto6Jugador2 = ComprobarSexteto6(VDadosJugador2, TAm1);
            sextetoJugador2 = ComprobarSexteto(VDadosJugador2, TAm1);

            if (EscaleraJugador2)
            {

                if(ContadorIntentosJugador2>0)
                {
                    rlutil::locate(2,4);
                    cout<<"Maximo puntaje de la ronda: "<<VIntentosJugador2[PosicionJugador2]<<endl;
                }
                VIntentosJugador2 [ContadorIntentosJugador2]=100;
                PosicionJugador2 = maximoVector(VIntentosJugador2, TAm2);
                rlutil::locate(2,5);
                cout<<"Intento numero: "<<ContadorIntentosJugador2+1<<endl;
                rlutil::locate(2,8);
                cout<<"Presionar cualquier tecla para lanzar los dados"<<endl;
                rlutil::anykey();
                MostrarIntento(VDadosJugador2, TAm1);
                rlutil::locate(2,4);
                cout<<"Maximo puntaje de la ronda: "<<VIntentosJugador2[PosicionJugador2]<<endl;
                rlutil::locate(2,21);
                cout<<"Presionar cualquier tecla para continuar"<<endl;
                rlutil::anykey();
                Puntos2 += 100;
                CartelGanador(Nombre2,Puntos2);
                return;
            }
            else
            {
                if (sexteto6Jugador2)
                {


                    Puntos2 = 0;
                }
                else
                {
                    if (sextetoJugador2)
                    {
                        VIntentosJugador2[ContadorIntentosJugador2] = VDadosJugador2[ContadorIntentosJugador2] * 10;



                    }
                    else
                    {
                        VIntentosJugador2[ContadorIntentosJugador2] = sumarVector(VDadosJugador2, TAm1);



                    }
                }
            }

            if(ContadorIntentosJugador2>0)
            {
                rlutil::locate(2,4);
                cout<<"Maximo puntaje de la ronda: "<<VIntentosJugador2[PosicionJugador2]<<endl;
            }
            PosicionJugador2 = maximoVector(VIntentosJugador2, TAm2);
            rlutil::locate(2,5);
            cout<<"Intento numero: "<<ContadorIntentosJugador2+1<<endl;


            rlutil::locate(2,8);
            cout<<"Presionar cualquier tecla para lanzar los dados"<<endl;
            rlutil::anykey();
            MostrarIntento(VDadosJugador2, TAm1);
            rlutil::locate(2,4);
            cout<<"Maximo puntaje de la ronda: "<<VIntentosJugador2 [PosicionJugador2]<<endl;
            rlutil::locate(2,21);
            cout<<"Presionar cualquier tecla para continuar"<<endl;
            rlutil::anykey();
            rlutil::cls();

            ContadorIntentosJugador2++;
        }


        if (sexteto6Jugador2!=true)
        {
            Puntos2 += VIntentosJugador2[PosicionJugador2];
        }




        rlutil::cls();
    }


    if (ContRonda < 6)
    {
        if(Puntos2<100)
        {
            CartelGanador(Nombre, Puntos);
        }
        else
        {
            if (Puntos<100)
            {
                CartelGanador(Nombre2, Puntos2);
            }
            else
            {
                if (Puntos >= 100 && Puntos2 >= 100)
                {
                    RondaEmpate = ContRonda;
                    IntentosEmpateJugador1 = PosicionJugador1 + 1;
                    IntentosEmpateJugador2 = PosicionJugador2 + 1;
                    if (IntentosEmpateJugador1 < IntentosEmpateJugador2)
                    {
                        rlutil::locate(51,10);
                        cout << "Empate en la ronda " << RondaEmpate << " a 100 puntos!!!" << endl;
                        rlutil::anykey();
                        EfectoBarraCargando(40,10,"Calculando jugador con puntaje maximo en la menor cantidad de tiradas");
                        CartelGanador(Nombre, Puntos);
                    }
                    else
                    {
                        if (IntentosEmpateJugador2 < IntentosEmpateJugador1)
                        {
                            rlutil::locate(51,10);
                            cout << "Empate en la ronda " << RondaEmpate << " a 100 puntos!!!" << endl;
                            rlutil::anykey();
                            EfectoBarraCargando(40,10,"Calculando jugador con puntaje maximo en la menor cantidad de tiradas");
                            CartelGanador(Nombre2, Puntos2);
                        }
                        else
                        {
                            rlutil::locate(59,10);
                            cout << "Empate en la ronda " << RondaEmpate << " a 100 puntos" << endl;
                            rlutil::locate(56,11);
                            cout << "Empate en el numero maximo de intentos" << endl;
                            rlutil::locate(2,21);
                            cout<<"Presione cualquier tecla para continuar"<<endl;
                            rlutil::anykey();
                            EfectoBarraCargando(55,10,"Sorteando el ganador de manera aleatoria");
                            GanadorAleatorio=DeterminarOrden();
                            if(GanadorAleatorio==1)
                            {
                                CartelGanador(Nombre, Puntos);
                            }
                            else
                            {
                                CartelGanador(Nombre2, Puntos2);
                            }

                        }
                    }
                }
            }
        }
    }
    else
    {
        if(Puntos>Puntos2)
        {
            CartelGanador(Nombre, Puntos);
        }
        else
        {
            if(Puntos2>Puntos)
            {
                CartelGanador(Nombre2, Puntos2);
            }
            else
            {
                if((Puntos2==Puntos)&&(Puntos!=0))
                {
                    rlutil::locate(43,10);
                    cout<<"Empate, el ganador se definira de manera aleatoria"<<endl;
                    rlutil::anykey();
                    EfectoBarraCargando(55,10,"Sorteando el ganador de manera aleatoria");
                    GanadorAleatorio=DeterminarOrden();
                    if(GanadorAleatorio==1)
                    {
                        CartelGanador(Nombre, Puntos);
                    }
                    else
                    {
                        CartelGanador(Nombre2, Puntos2);
                    }

                }
                else
                {
                    rlutil::locate(48,10);
                    cout<<"Los dos jugadores perdieron por no sumar ningun punto"<<endl;
                    rlutil::anykey();
                }

            }
        }

    }



}


void ordenarVectorCreciente(int v[], int tam )
{
    int i,j, posmin, aux;
    for(i=0; i<tam-1; i++)
    {
        posmin=i;
        for(j=i+1; j<tam; j++)
        {
            if(v[j]<v[posmin]) posmin=j;
        }
        aux=v[i];
        v[i]=v[posmin];
        v[posmin]=aux;
    }
}
void CartelTurnoUnJugadores(std::string JugadorRonda,int rondas,int PuntosJugadorRonda)
{
    rlutil::cls();
    for(int x=40; x<=104; x++)
    {

        if(x==40)
        {
            rlutil::locate(x,9);
            cout<<(char)201;
            rlutil::locate(x,14);
            cout<<(char)200;
        }
        else
        {
            if(x==104)
            {
                rlutil::locate(x,9);
                cout<<(char)187;
                rlutil::locate(x,14);
                cout<<(char)188;
            }
            else
            {
                rlutil::locate(x,9);
                cout<<(char)205;
                rlutil::locate(x,14);
                cout<<(char)205;
            }
        }
        for(int y=10; y<=13; y++)
        {
            rlutil::locate(40,y);
            cout<<(char)186;
            rlutil::locate(104,y);
            cout<<(char)186;
        }
    }
    rlutil::locate(69,10);
    cout<<"Ronda: "<<rondas<<endl;
    rlutil::locate(60,11);
    cout<<"Nombre del jugador: "<<JugadorRonda<<endl;
    rlutil::locate(60,12);
    cout<<"Puntaje : "<<PuntosJugadorRonda<<" Puntos"<<endl;
    rlutil::locate(1,21);
    cout<<"Presione cualquier tecla para continuar"<<endl;
    rlutil::anykey();
    rlutil::cls();

}
void CartelTurnoDosJugadores(std::string JugadorRonda,std::string JugadorAnterior,int rondas, int PuntosJugadorAnterior, int PuntosJugadorRonda)
{
    rlutil::cls();
    for(int x=40; x<=104; x++)
    {

        if(x==40)
        {
            rlutil::locate(x,9);
            cout<<(char)201;
            rlutil::locate(x,14);
            cout<<(char)200;
        }
        else
        {
            if(x==104)
            {
                rlutil::locate(x,9);
                cout<<(char)187;
                rlutil::locate(x,14);
                cout<<(char)188;
            }
            else
            {
                rlutil::locate(x,9);
                cout<<(char)205;
                rlutil::locate(x,14);
                cout<<(char)205;
            }
        }
        for(int y=10; y<=13; y++)
        {
            rlutil::locate(40,y);
            cout<<(char)186;
            rlutil::locate(104,y);
            cout<<(char)186;
        }
    }

    rlutil::locate(69,10);
    cout<<"Ronda: "<<rondas<<endl;
    rlutil::locate(60,11);
    cout<<"Proximo turno "<<JugadorRonda<<endl;
    rlutil::locate(60,12);
    cout<<"Puntaje "<<JugadorAnterior<<": "<<PuntosJugadorAnterior<<" Puntos"<<endl;
    rlutil::locate(60,13);
    cout<<"Puntaje "<<JugadorRonda<<": "<<PuntosJugadorRonda<<" Puntos"<<endl;


    rlutil::locate(1,21);
    cout<<"Presione cualquier tecla para continuar"<<endl;
    rlutil::anykey();
    rlutil::cls();


}
void ordenarVectorDecreciente(int v1[],string v2[], int tam )
{
    int i,j, posmin, auxV1;
    string auxV2;
    for(i=0; i<tam-1; i++)
    {
        posmin=i;
        for(j=i+1; j<tam; j++)
        {
            if(v1[j]>v1[posmin]) posmin=j;
        }
        auxV1=v1[i];
        v1[i]=v1[posmin];
        v1[posmin]=auxV1;
        auxV2=v2[i];
        v2[i]=v2[posmin];
        v2[posmin]=auxV2;
    }
}

void ElegirDados (int v[],int TAm)
{
    rlutil::cls();
    for(int x=0; x<TAm; x++)
    {
        cout<<"Ingresar numero de dado: "<<endl;
        cin>>v[x];

    }
    rlutil::cls();
}
char CantidadDeJugadores()
{
    rlutil::cls();
    rlutil::setBackgroundColor(rlutil::GREEN);
    rlutil::setColor(rlutil::BLACK);
    char CantidadJugadores;
    cout<<"Indica la cantidad de jugadores (1-2)"<<endl;
    CantidadJugadores=rlutil::getkey();
    cin.sync();
    system ("cls");
    return CantidadJugadores;
}
void ModoSimulador(int &Puntos,int &Puntos2, string &Nombre,string &Nombre2,int AnchoConsola)
{
    rlutil::setBackgroundColor(rlutil::GREEN);
    rlutil::setColor(rlutil::BLACK);
    char CantidadJugadores;
    CantidadJugadores=CantidadDeJugadores();
    if(CantidadJugadores=='1')
    {
        const int TAm1=6,TAm2=3;
        int ContRonda=0,Posicion=0,VDados[TAm1] {},VIntentos[TAm2] {},VDuplicado[TAm1] {},ContadorIntentos;
        bool Escalera,sexteto6,sexteto;
        cout<<"Ingrese nombre: "<<endl;

        getline(cin, Nombre);

        rlutil::cls();


        while((Puntos<100)&&(ContRonda<6))
        {
            ContRonda++;

            ContadorIntentos=0;
            sexteto6=false;
            ponerCero(VIntentos,TAm2);
            while((ContadorIntentos<3)&&(sexteto6!=true))
            {

                //LanzamientoDados(VDados,TAm1);
                ElegirDados (VDados,TAm1);
                EncabezadoJuego (Nombre,Puntos,ContRonda,AnchoConsola);
                copiarVector(VDados,VDuplicado,TAm1);
                Escalera=ComprobarEscalera(VDuplicado,TAm1);
                sexteto6=ComprobarSexteto6(VDados,TAm1);
                sexteto=ComprobarSexteto(VDados,TAm1);




                if(Escalera)
                {

                    if(ContadorIntentos>0)
                    {
                        rlutil::locate(2,4);
                        cout<<"Maximo puntaje de la ronda: "<<VIntentos[Posicion]<<endl;
                    }

                    VIntentos[ContadorIntentos]=100;
                    Posicion=maximoVector(VIntentos,TAm2);
                    rlutil::locate(2,5);
                    cout<<"Intento numero: "<<ContadorIntentos+1<<endl;
                    rlutil::locate(2,8);
                    cout<<"Presionar cualquier tecla para lanzar los dados"<<endl;
                    rlutil::anykey();
                    MostrarIntento(VDados,TAm1);
                    Puntos += 100;
                    rlutil::locate(2,4);
                    cout<<"Maximo puntaje de la ronda: "<<VIntentos[Posicion]<<endl;
                    rlutil::locate(2,21);
                    cout<<"Presionar cualquier tecla para continuar"<<endl;
                    rlutil::anykey();
                    CartelGanador(Nombre,Puntos);
                    return;
                }
                else
                {
                    if(sexteto6)
                    {
                        Puntos=0;
                        CartelGanador(Nombre,Puntos);
                        return;

                    }
                    else
                    {
                        if(sexteto)
                        {
                            VIntentos[ContadorIntentos]=VDados[ContadorIntentos]*10;
                        }
                        else
                        {
                            VIntentos[ContadorIntentos]=sumarVector(VDados,TAm1);
                        }
                    }
                }

                if(ContadorIntentos>0)
                {
                    rlutil::locate(2,4);
                    cout<<"Maximo puntaje de la ronda: "<<VIntentos[Posicion]<<endl;
                }
                Posicion=maximoVector(VIntentos,TAm2);
                rlutil::locate(2,5);
                cout<<"Intento numero: "<<ContadorIntentos+1<<endl;


                rlutil::locate(2,8);
                cout<<"Presionar cualquier tecla para lanzar los dados"<<endl;
                rlutil::anykey();
                MostrarIntento(VDados,TAm1);

                rlutil::locate(2,4);
                cout<<"Maximo puntaje de la ronda: "<<VIntentos[Posicion]<<endl;
                rlutil::locate(2,21);
                cout<<"Presionar cualquier tecla para continuar"<<endl;
                rlutil::anykey();
                ContadorIntentos++;

            }
            if(sexteto6!=true)
            {


                Puntos += VIntentos[Posicion];
            }
            if(Puntos<100)
            {
                CartelTurnoUnJugadores(Nombre,ContRonda,Puntos);
            }

        }

        if(Puntos>0)
        {
            CartelGanador(Nombre,Puntos);
        }
        else
        {
            rlutil::locate(58,10);
            cout<<"Perdiste por no sumar ningun punto"<<endl;
            rlutil::anykey();

        }


    }
    else
    {
        const int TAm1 = 6, TAm2 = 3;
        int ContRonda = 0, VDadosJugador1[TAm1] {}, VDadosJugador2[TAm1] {};
        int VIntentosJugador1[TAm2] {}, VIntentosJugador2[TAm2] {},VDuplicado[TAm1] {};
        int ContadorIntentosJugador1, ContadorIntentosJugador2;
        bool EscaleraJugador1, sexteto6Jugador1, sextetoJugador1;
        bool EscaleraJugador2, sexteto6Jugador2, sextetoJugador2;
        int RondaEmpate = 0;
        int IntentosEmpateJugador1 = 0, IntentosEmpateJugador2 = 0;
        int PosicionJugador1,PosicionJugador2,PrimeroEnComenzar,GanadorAleatorio;
        string VariabAuxNombre;

        cout << "Ingrese nombre del Jugador 1: ";

        getline(cin, Nombre);

        cout << "Ingrese nombre del Jugador 2: ";
        getline(cin, Nombre2);

        rlutil::cls();
        PrimeroEnComenzar=DeterminarOrden();
        EfectoBarraCargando(61,10);
        if(PrimeroEnComenzar==2)
        {
            VariabAuxNombre=Nombre;
            Nombre=Nombre2;
            Nombre2=VariabAuxNombre;
        }
        CartelPrimeroArranca(Nombre);
        while ((Puntos < 100 && Puntos2 < 100) && ContRonda < 6)
        {
            ContRonda++;

            ContadorIntentosJugador1 = 0;

            if(ContRonda!=1)
            {
                CartelTurnoDosJugadores(Nombre,Nombre2,ContRonda,Puntos2,Puntos);

            }
            ponerCero(VIntentosJugador1, TAm2);
            sexteto6Jugador1=false;
            while ((ContadorIntentosJugador1 < 3)&&(sexteto6Jugador1!=true) )
            {


                //LanzamientoDados(VDadosJugador1, TAm1);
                ElegirDados (VDadosJugador1,TAm1);
                EncabezadoJuego (Nombre,Puntos,ContRonda,AnchoConsola);
                copiarVector(VDadosJugador1,VDuplicado,TAm1);
                EscaleraJugador1 = ComprobarEscalera(VDuplicado, TAm1);
                sexteto6Jugador1 = ComprobarSexteto6(VDadosJugador1, TAm1);
                sextetoJugador1 = ComprobarSexteto(VDadosJugador1, TAm1);

                if (EscaleraJugador1)
                {



                    if(ContadorIntentosJugador1>0)
                    {
                        rlutil::locate(2,4);
                        cout<<"Maximo puntaje de la ronda: "<<VIntentosJugador1[PosicionJugador1]<<endl;
                    }
                    VIntentosJugador1 [ContadorIntentosJugador1]=100;
                    PosicionJugador1 = maximoVector(VIntentosJugador1, TAm2);
                    rlutil::locate(2,5);
                    cout<<"Intento numero: "<<ContadorIntentosJugador1+1<<endl;
                    rlutil::locate(2,8);
                    cout<<"Presionar cualquier tecla para lanzar los dados"<<endl;
                    rlutil::anykey();
                    MostrarIntento(VDadosJugador1, TAm1);
                    rlutil::locate(2,4);
                    cout<<"Maximo puntaje de la ronda: "<<VIntentosJugador1[PosicionJugador1]<<endl;
                    rlutil::locate(2,21);
                    cout<<"Presionar cualquier tecla para continuar"<<endl;
                    rlutil::anykey();
                    Puntos += 100;
                    CartelGanador(Nombre,Puntos);
                    return;
                }
                else
                {
                    if (sexteto6Jugador1)
                    {


                        Puntos = 0;
                    }
                    else
                    {
                        if (sextetoJugador1)
                        {
                            VIntentosJugador1[ContadorIntentosJugador1] = VDadosJugador1[ContadorIntentosJugador1] * 10;



                        }
                        else
                        {
                            VIntentosJugador1[ContadorIntentosJugador1] = sumarVector(VDadosJugador1, TAm1);



                        }
                    }
                }

                if(ContadorIntentosJugador1>0)
                {
                    rlutil::locate(2,4);
                    cout<<"Maximo puntaje de la ronda: "<<VIntentosJugador1[PosicionJugador1]<<endl;
                }
                PosicionJugador1 = maximoVector(VIntentosJugador1, TAm2);
                rlutil::locate(2,5);
                cout<<"Intento numero: "<<ContadorIntentosJugador1+1<<endl;


                rlutil::locate(2,8);
                cout<<"Presionar cualquier tecla para lanzar los dados"<<endl;
                rlutil::anykey();
                MostrarIntento(VDadosJugador1, TAm1);
                rlutil::locate(2,4);
                cout<<"Maximo puntaje de la ronda: "<<VIntentosJugador1[PosicionJugador1]<<endl;
                rlutil::locate(2,21);
                cout<<"Presionar cualquier tecla para continuar"<<endl;
                rlutil::anykey();

                ContadorIntentosJugador1++;

            }


            if (sexteto6Jugador1!=true)
            {
                Puntos += VIntentosJugador1[PosicionJugador1];
            }



            ContadorIntentosJugador2 = 0;


            CartelTurnoDosJugadores(Nombre2,Nombre,ContRonda,Puntos,Puntos2);


            ponerCero(VIntentosJugador2, TAm2);
            sexteto6Jugador2=false;
            while ((ContadorIntentosJugador2 < 3)&&(sexteto6Jugador2!=true) )
            {


                //LanzamientoDados(VDadosJugador1, TAm1);
                ElegirDados (VDadosJugador2,TAm1);
                EncabezadoJuego (Nombre2,Puntos2,ContRonda,AnchoConsola);
                copiarVector(VDadosJugador2,VDuplicado,TAm1);
                EscaleraJugador2 = ComprobarEscalera(VDuplicado, TAm1);
                sexteto6Jugador2 = ComprobarSexteto6(VDadosJugador2, TAm1);
                sextetoJugador2 = ComprobarSexteto(VDadosJugador2, TAm1);

                if (EscaleraJugador2)
                {

                    if(ContadorIntentosJugador2>0)
                    {
                        rlutil::locate(2,4);
                        cout<<"Maximo puntaje de la ronda: "<<VIntentosJugador2[PosicionJugador2]<<endl;
                    }
                    VIntentosJugador2 [ContadorIntentosJugador2]=100;
                    PosicionJugador2 = maximoVector(VIntentosJugador2, TAm2);
                    rlutil::locate(2,5);
                    cout<<"Intento numero: "<<ContadorIntentosJugador2+1<<endl;
                    rlutil::locate(2,8);
                    cout<<"Presionar cualquier tecla para lanzar los dados"<<endl;
                    rlutil::anykey();
                    MostrarIntento(VDadosJugador2, TAm1);
                    rlutil::locate(2,4);
                    cout<<"Maximo puntaje de la ronda: "<<VIntentosJugador2[PosicionJugador2]<<endl;
                    rlutil::locate(2,21);
                    cout<<"Presionar cualquier tecla para continuar"<<endl;
                    rlutil::anykey();
                    Puntos2 += 100;

                    CartelGanador(Nombre2,Puntos2);

                    return;
                }
                else
                {
                    if (sexteto6Jugador2)
                    {


                        Puntos2 = 0;
                    }
                    else
                    {
                        if (sextetoJugador2)
                        {
                            VIntentosJugador2[ContadorIntentosJugador2] = VDadosJugador2[ContadorIntentosJugador2] * 10;



                        }
                        else
                        {
                            VIntentosJugador2[ContadorIntentosJugador2] = sumarVector(VDadosJugador2, TAm1);



                        }
                    }
                }

                if(ContadorIntentosJugador2>0)
                {
                    rlutil::locate(2,4);
                    cout<<"Maximo puntaje de la ronda: "<<VIntentosJugador2[PosicionJugador2]<<endl;
                }
                PosicionJugador2 = maximoVector(VIntentosJugador2, TAm2);
                rlutil::locate(2,5);
                cout<<"Intento numero: "<<ContadorIntentosJugador2+1<<endl;


                rlutil::locate(2,8);
                cout<<"Presionar cualquier tecla para lanzar los dados"<<endl;
                rlutil::anykey();
                MostrarIntento(VDadosJugador2, TAm1);
                rlutil::locate(2,4);
                cout<<"Maximo puntaje de la ronda: "<<VIntentosJugador2 [PosicionJugador2]<<endl;
                rlutil::locate(2,21);
                cout<<"Presionar cualquier tecla para continuar"<<endl;
                rlutil::anykey();
                ContadorIntentosJugador2++;
            }


            if (sexteto6Jugador2!=true)
            {
                Puntos2 += VIntentosJugador2[PosicionJugador2];
            }




            rlutil::cls();
        }


        if (ContRonda < 6)
        {
            if(Puntos2<100)
            {
                CartelGanador(Nombre, Puntos);
            }
            else
            {
                if (Puntos<100)
                {
                    CartelGanador(Nombre2, Puntos2);
                }
                else
                {
                    if (Puntos >= 100 && Puntos2 >= 100)
                    {
                        RondaEmpate = ContRonda;
                        IntentosEmpateJugador1 = PosicionJugador1 + 1;
                        IntentosEmpateJugador2 = PosicionJugador2 + 1;
                        if (IntentosEmpateJugador1 < IntentosEmpateJugador2)
                        {
                            rlutil::locate(51,10);
                            cout << "Empate en la ronda " << RondaEmpate << " a 100 puntos!!!" << endl;
                            rlutil::anykey();
                            EfectoBarraCargando(40,10,"Calculando jugador con puntaje maximo en la menor cantidad de tiradas");
                            CartelGanador(Nombre, Puntos);
                        }
                        else
                        {
                            if (IntentosEmpateJugador2 < IntentosEmpateJugador1)
                            {
                                rlutil::locate(59,10);
                                cout << "Empate en la ronda " << RondaEmpate << " a 100 puntos!!!" << endl;
                                rlutil::anykey();
                                EfectoBarraCargando(40,10,"Calculando jugador con puntaje maximo en la menor cantidad de tiradas");

                                CartelGanador(Nombre2, Puntos2);
                            }
                            else
                            {
                                rlutil::locate(59,10);
                                cout << "Empate en la ronda " << RondaEmpate << " a 100 puntos" << endl;
                                rlutil::locate(56,11);
                                cout << "Empate en el numero maximo de intentos" << endl;
                                rlutil::locate(2,21);
                                cout<<"Presionar cualquier tecla para continuar"<<endl;//
                                rlutil::anykey();
                                EfectoBarraCargando(55,10,"Sorteando el ganador de manera aleatoria");
                                GanadorAleatorio=DeterminarOrden();
                                if(GanadorAleatorio==1)
                                {
                                    CartelGanador(Nombre, Puntos);
                                }
                                else
                                {
                                    CartelGanador(Nombre2, Puntos2);
                                }

                            }
                        }
                    }
                }
            }
        }
        else
        {
            if(Puntos>Puntos2)
            {
                CartelGanador(Nombre, Puntos);
            }
            else
            {
                if(Puntos2>Puntos)
                {
                    CartelGanador(Nombre2, Puntos2);
                }
                else
                {
                    if((Puntos2==Puntos)&&(Puntos!=0))
                    {
                        rlutil::locate(43,10);
                        cout<<"Empate, el ganador se definira de manera aleatoria"<<endl;
                        rlutil::anykey();
                        EfectoBarraCargando(55,10,"Sorteando el ganador de manera aleatoria");
                        GanadorAleatorio=DeterminarOrden();
                        if(GanadorAleatorio==1)
                        {
                            CartelGanador(Nombre, Puntos);
                        }
                        else
                        {
                            CartelGanador(Nombre2, Puntos2);
                        }

                    }
                    else
                    {
                        rlutil::locate(48,10);
                        cout<<"Los dos jugadores perdieron por no sumar ningun punto"<<endl;
                        rlutil::anykey();
                    }
                }
            }

        }


    }

}
int posicionNumeroEnVector(int v[],int tam, int numero)
{
    int i;
    for(i=0; i<tam; i++)
    {
        if(v[i]==numero) return i;
    }
    return -1;
}
void CartelFinDelJuego()
{
    rlutil::cls();
    rlutil::locate(66,10);
    cout<<"Gracias por jugar"<<endl;
    rlutil::locate(1,21);
    cout<<"Presionar cualquier tecla para finalizar"<<endl;
    rlutil::anykey();
    rlutil::cls();

}
void MostrarTablaPosiciones(int VPuntos[],string VNombres[])
{
    rlutil::cls();
    rlutil::locate(55,1);
    cout<<"RANKING DE LAS 10 MEJORES PUNTUACIONES:"<<endl;
    for(int x=0; x<10; x++)
    {
        if(VPuntos[x]!=0)
        {
            rlutil::locate(56,x+2);
            cout<<"#"<<(x+1)<<" "<<setfill('-')<<setw(24)<<left<<VNombres[x]<<" "<<VPuntos[x]<<" Puntos"<<endl;
        }
    }
    rlutil::anykey();
    rlutil::cls();
}
void TablaPosiciones(int Puntos,string Nombre,int VPuntos[],string VNombres[])
{
    int Posicion;
    Posicion=posicionNumeroEnVector(VPuntos,10,0);
    if(Posicion!=(-1))
    {
        VPuntos[Posicion]=Puntos;
        VNombres[Posicion]=Nombre;
    }
    else
    {
        if(Puntos>VPuntos[10])
        {
            VPuntos[10]=Puntos;
            VNombres[10]=Nombre;
        }
    }
    ordenarVectorDecreciente(VPuntos,VNombres,11);
}
void UnJugador(int &Puntos, string &Nombre,int AnchoConsola)
{
    rlutil::cls();
    rlutil::setBackgroundColor(rlutil::GREEN);
    rlutil::setColor(rlutil::BLACK);
    const int TAm1=6,TAm2=3;
    int ContRonda=0,Posicion=0,VDados[TAm1] {},VIntentos[TAm2] {},VDuplicado[TAm1] {},ContadorIntentos;
    bool Escalera,sexteto6,sexteto;
    cout<<"Ingrese nombre: "<<endl;

    getline(cin,Nombre);
    system ("cls");


    while((Puntos<100)&&(ContRonda<6))
    {
        ContRonda++;

        ContadorIntentos=0;
        sexteto6=false;
        ponerCero(VIntentos,TAm2);
        while((ContadorIntentos<3)&&(sexteto6!=true))
        {

            EncabezadoJuego (Nombre,Puntos,ContRonda,AnchoConsola);//Muestra en la parte superior el nombre del jugador, ronda, puntos y dibuja el recuadro del juego
            LanzamientoDados(VDados,TAm1);//Guarda numeros aleatorios del 1-6 en todo el vector
            copiarVector(VDados,VDuplicado,TAm1);//Hacemos un duplicado del vector
            Escalera=ComprobarEscalera(VDuplicado,TAm1);//Usamos la copia del vector para ordenarlo y verificar si hay escalera(esto nos evita alterar el vectr original)
            sexteto6=ComprobarSexteto6(VDados,TAm1);
            sexteto=ComprobarSexteto(VDados,TAm1);




            if(Escalera)
            {
                if(ContadorIntentos>0)
                {
                    rlutil::locate(1,4);
                    cout<<"Maximo puntaje de la ronda: "<<VIntentos[Posicion]<<endl;

                }

                VIntentos[ContadorIntentos]=100;
                Posicion=maximoVector(VIntentos,TAm2);
                rlutil::locate(2,5);
                cout<<"Intento numero: "<<ContadorIntentos+1<<endl;
                rlutil::locate(2,8);
                cout<<"Presionar cualquier tecla para lanzar los dados"<<endl;
                rlutil::anykey();
                MostrarIntento(VDados,TAm1);
                rlutil::locate(2,4);
                cout<<"Maximo puntaje de la ronda: "<<VIntentos[Posicion]<<endl;
                rlutil::locate(2,21);
                cout<<"Presionar cualquier tecla para continuar"<<endl;
                rlutil::anykey();
                Puntos += 100;
                CartelGanador(Nombre,Puntos);
                return;
            }
            else
            {
                if(sexteto6)
                {
                    Puntos=0;
                    CartelGanador(Nombre,Puntos);
                    return;

                }
                else
                {
                    if(sexteto)
                    {
                        VIntentos[ContadorIntentos]=VDados[ContadorIntentos]*10;
                    }
                    else
                    {
                        VIntentos[ContadorIntentos]=sumarVector(VDados,TAm1);
                    }
                }
            }

            if(ContadorIntentos>0)//Este if hace que constantemente me aparezca la maxima tirada y luego se modifique si es necesario en la linea 1200
            {

                rlutil::locate(2,4);
                cout<<"Maximo puntaje de la ronda: "<<VIntentos[Posicion]<<endl;


            }

            Posicion=maximoVector(VIntentos,TAm2);//Se guarda en la variable Posicion el valor maximo que se encuentra en el V[] de intentos
            rlutil::locate(2,5);
            cout<<"Intento numero: "<<ContadorIntentos+1<<endl;
            rlutil::locate(2,8);
            cout<<"Presionar cualquier tecla para lanzar los dados"<<endl;
            rlutil::anykey();
            MostrarIntento(VDados,TAm1);//Mostramos el intento dibujando los dados , a su vez el nombre del juego de dados y su puntuacion
            rlutil::locate(2,4);
            cout<<"Maximo puntaje de la ronda: "<<VIntentos[Posicion]<<endl;
            rlutil::locate(2,21);
            cout<<"Presionar cualquier tecla para continuar"<<endl;
            rlutil::anykey();
            rlutil::cls();
            ContadorIntentos++;


        }

        if(sexteto6!=true)
        {
            Puntos += VIntentos[Posicion];
        }
        if(Puntos<100)
        {
            CartelTurnoUnJugadores(Nombre,ContRonda,Puntos);
        }

    }


    if(Puntos>0)
    {
        CartelGanador(Nombre,Puntos);
    }
    else
    {
        rlutil::locate(58,10);
        cout<<"Perdiste por no sumar ningun punto"<<endl;
        rlutil::anykey();
    }



}
void copiarVector(int v[], int v2[],int tam )
{
    int i;
    for(i=0; i<tam; i++)
    {
        v2[i]=v[i];
    }
}
void CartelGanador(string Nombre,int Puntos)
{
    rlutil::cls();
    for(int i=1; i<30; i++)
    {

        if(i%2==0)
        {
            rlutil::setColor(rlutil::YELLOW);
            rlutil::setBackgroundColor(rlutil::BLUE);
        }
        else
        {
            rlutil::setColor(rlutil::BLUE);
            rlutil::setBackgroundColor(rlutil::YELLOW);
        }
        rlutil::locate(66,10);
        cout<<"GANADOR "<<Nombre<<" !!!"<<endl;
        rlutil::locate(66,11);
        cout<<"Puntuacion: "<<Puntos<<endl;

        rlutil::msleep(100);

    }
    rlutil::setColor(rlutil::BLACK);
    rlutil::setBackgroundColor(rlutil::GREEN);
    rlutil::locate(66,10);
    cout<<"GANADOR "<<Nombre<<" !!!"<<endl;
    rlutil::locate(66,11);
    cout<<"Puntuacion: "<<Puntos<<endl;
    rlutil::anykey();


}
int maximoVector(int v[], int tam)
{
    int i, posMax=0;
    for(i=1; i<tam; i++)
    {
        if(v[i]>v[posMax])
        {
            posMax=i;
        }
    }
    return posMax;
}

int sumarVector(int v[], int tam )
{
    int i, suma=0;
    for(i=0; i<tam; i++)
    {
        suma+=v[i];
    }
    return suma;
}
void EncabezadoJuego (string Nombre,int puntos,int Rondas, int AnchoConsola)
{

    rlutil::locate(2,2);
    cout<<"Jugador actual: "<<Nombre;
    rlutil::locate(56,2);
    cout<<"|"<<"\t"<<"Ronda: "<<Rondas;
    rlutil::locate(111,2);
    cout<<"|"<<"\t"<<"Puntos: "<<puntos<<endl;
    RecuadrosJuego(AnchoConsola);

}
void MostrarIntento(int v[],int TAm)
{
    bool Sexteto6,Sexteto,Escalera;
    rlutil::saveDefaultColor();


    rlutil::hidecursor();

    for(int x=1; x<=TAm; x++)
    {

        dibujarDado(v[x-1],x*20,rand()%6+11);
        rlutil::msleep(500);

    }


    rlutil::resetColor();
    rlutil::setBackgroundColor(rlutil::GREEN);
    rlutil::setColor(rlutil::BLACK);

    Sexteto6=ComprobarSexteto6(v,TAm);
    Escalera=ComprobarEscalera(v,TAm);
    Sexteto=ComprobarSexteto(v,TAm);
    rlutil::locate(2,20);
    if(Sexteto6)
    {

        cout<<"Sexteto de 6    Perdiste los intentos de la ronda y tu puntuacion vuelve a 0"<<endl;

    }
    else
    {
        if(Escalera)
        {

            cout<<"Escalera     Puntos de la tirada: 100    Ganasteeeeeeeeeeeeeeeeeeeeee!!!"<<endl;

        }
        else
        {
            if(Sexteto)
            {

                cout<<"Sexteto de "<<v[0]<<"    Puntos de la tirada: "<<v[0]*10<<endl;

            }
            else
            {

                cout<<"Suma de dados     Puntos de la tirada: "<<sumarVector(v,TAm)<<endl;

            }
        }
    }

}
void LanzamientoDados(int v[],int TAm)
{
    for(int x=0; x<TAm; x++)
    {
        v[x]=rand()%6+1;
    }
}
bool ComprobarEscalera(int v[],int TAm)
{
    bool flag=true;
    ordenarVectorCreciente(v,TAm);
    for(int x=0; x<TAm; x++)
    {
        if(v[x]!=(x+1))
        {
            flag=false;
        }
    }
    return flag;
}
bool ComprobarSexteto6(int v[],int TAm)
{
    bool flag;
    int contador=0;
    for(int x=0; x<TAm; x++)
    {
        if(v[x]==6)
        {
            contador++;
        }
    }
    if(contador==6)
    {
        flag=true;
    }
    else
    {
        flag=false;
    }
    return flag;
}
void dibujarCuadrado(int posx, int posy)
{
    rlutil::setColor(rlutil::WHITE);
    for(int x=posx; x<=posx+6; x++)
    {
        for(int y=posy; y<=posy+2; y++)
        {
            rlutil::locate(x,y);
            cout<<(char) 219;
        }

    }
}
void dibujarDado(int numero, int posx, int posy)
{
    dibujarCuadrado(posx,posy);

    rlutil::setColor(rlutil::BLACK);
    rlutil::setBackgroundColor(rlutil::WHITE);

    switch(numero)
    {
    case 1:
        rlutil::locate(posx+3,posy+1);
        cout<<(char) 254;
        break;
    case 2:
        rlutil::locate(posx+1,posy);
        cout<<(char) 220;
        rlutil::locate(posx+5,posy+2);
        cout<<(char) 223;
        break;
    case 3:
        rlutil::locate(posx+3,posy+1);
        cout<<(char) 254;
        rlutil::locate(posx+1,posy);
        cout<<(char) 220;
        rlutil::locate(posx+5,posy+2);
        cout<<(char) 223;
        break;
    case 4:
        rlutil::locate(posx+1,posy);
        cout<<(char) 220;
        rlutil::locate(posx+5,posy);
        cout<<(char) 220;
        rlutil::locate(posx+1,posy+2);
        cout<<(char) 223;
        rlutil::locate(posx+5,posy+2);
        cout<<(char) 223;
        break;
    case 5:
        rlutil::locate(posx+3,posy+1);
        cout<<(char) 254;
        rlutil::locate(posx+1,posy);
        cout<<(char) 220;
        rlutil::locate(posx+5,posy);
        cout<<(char) 220;
        rlutil::locate(posx+1,posy+2);
        cout<<(char) 223;
        rlutil::locate(posx+5,posy+2);
        cout<<(char) 223;
        break;
    case 6:
        rlutil::locate(posx+1,posy);
        cout<<(char) 220;
        rlutil::locate(posx+3,posy);
        cout<<(char) 220;
        rlutil::locate(posx+5,posy);
        cout<<(char) 220;
        rlutil::locate(posx+1,posy+2);
        cout<<(char) 223;
        rlutil::locate(posx+3,posy+2);
        cout<<(char) 223;
        rlutil::locate(posx+5,posy+2);
        cout<<(char) 223;
        break;
    }

}

bool ComprobarSexteto(int v[], int TAm)
{
    bool flag=true;
    for(int x=0; x<TAm; x++)
    {
        if(v[x]!=v[0])
        {
            flag=false;
        }
    }
    return flag;
}
void ponerCero(int v[], int tam)
{
    int i;
    for(i=0; i<tam; i++)
    {
        v[i]=0;
    }
}
void EfectoBarraCargando(int posX, int posY,string mensaje)
{
    rlutil::cls();
    rlutil::hidecursor();
    int i=0,Cargando=0;
    do
    {
        Cargando += rand()%30;

        rlutil::locate(posX,posY);
        if(i==0)
        {
            cout<<mensaje<<"   ";
        }
        else if(i==1)
        {
            cout<<mensaje<<".  ";
        }
        else if(i==2)
        {
            cout<<mensaje<<".. ";
        }
        else if(i==3)
        {
            cout<<mensaje<<"...";
            i=-1;
        }
        i++;
        rlutil::msleep(500);

    }
    while(Cargando<100);
    rlutil::setBackgroundColor(rlutil::GREEN);
    rlutil::setColor(rlutil::BLACK);
    rlutil::showcursor();
    rlutil::cls();

}
void RecuadrosJuego(int AnchoConsola)
{

    for(int x=1; x<=(AnchoConsola*2)+1; x++)
    {

        rlutil::locate(x,1);
        cout<<(char)205;
        rlutil::locate(x,3);
        cout<<(char)205;
        rlutil::locate(x,6);
        cout<<(char)205;
        rlutil::locate(x,22);
        cout<<(char)205;

    }

}
void DadosMenu(int posx, int posy)
{
    int VDados[6] {1,2,3,4,5,6};
    rlutil::saveDefaultColor();

    for(int x=1; x<=6; x++)
    {
        dibujarDado(VDados[x-1],x*23,4);
        //rlutil::msleep(300);
    }
    rlutil::resetColor();

}
void Menu()
{
    const int TAm=11;
    int Opcion;
    int VPuntos[TAm] {},AnchoMedio,AltoMedio, y=0;
    string VNombres[TAm] {" "};

    AltoMedio=rlutil::trows()/2;
    AnchoMedio=rlutil::tcols()/2;
    rlutil::hidecursor();
    bool Bandera=true;
    while(true)
    {

        rlutil::setBackgroundColor(rlutil::BLUE);
        rlutil::setColor(rlutil::WHITE);

        if(Bandera==true)
        {
            rlutil::cls();
            Bandera=false;

        }


        //DadosMenu(1,1);
        rlutil::locate(AnchoMedio-22,AltoMedio-9);
        cout<<"---------------------------------------------"<<endl;
        rlutil::locate(AnchoMedio-15,AltoMedio-8);
        cout<<"Menu del juego cien o escalera "<<endl;
        rlutil::locate(AnchoMedio-22,AltoMedio-7);
        cout<<"---------------------------------------------"<<endl;
        rlutil::locate(AnchoMedio-10,AltoMedio-5);
        cout<<"Modo 1 jugador "<<endl;
        rlutil::locate(AnchoMedio-10,AltoMedio-3);
        cout<<"Modo 2 jugadores "<<endl;
        rlutil::locate(AnchoMedio-10,AltoMedio-1);
        cout<<"Mostrar tabla de puntuacion"<<endl;
        rlutil::locate(AnchoMedio-10,AltoMedio+1);
        cout<<"Modo simulador"<<endl;
        rlutil::locate(AnchoMedio-10,AltoMedio+3);
        cout<<"Cerrar juego"<<endl;
        rlutil::locate(AnchoMedio-12,AltoMedio-5+y);
        cout<<(char)175<<endl;
        switch(rlutil::getkey())
        {
        case 14://arriba
            rlutil::locate(AnchoMedio-12,AltoMedio-5+y);
            cout<<"  "<<endl;
            y -=2;
            if(y<0)
            {
                y=0;
            }
            break;
        case 15://abajo
            rlutil::locate(AnchoMedio-12,AltoMedio-5+y);
            cout<<"  "<<endl;
            y +=2;
            if(y>8)
            {
                y=8;
            }
            break;
        case 1://enter
            switch(y)
            {
            case 0:
                Opcion= 1;
                break;
            case 2:
                Opcion= 2;
                break;
            case 4:
                Opcion= 3;
                break;
            case 6:
                Opcion= 4;
                break;
            case 8:
                Opcion= 0;
                break;
            }
            break;
        }
        switch(Opcion)
        {
        case 1:
        {
            int Puntos=0;
            string Nombre;
            EfectoBarraCargando(AnchoMedio-4,AltoMedio,"Cargando");
            UnJugador(Puntos,Nombre,AnchoMedio);
            TablaPosiciones(Puntos,Nombre,VPuntos,VNombres);
            Bandera=true;

        }
        break;
        case 2:
        {

            int Puntos=0,Puntos2=0;
            string Nombre, Nombre2;
            EfectoBarraCargando(AnchoMedio-4,AltoMedio,"Cargando");
            ModoDosJugadores (Puntos,Puntos2,Nombre,Nombre2,AnchoMedio);
            TablaPosiciones(Puntos,Nombre,VPuntos,VNombres);
            TablaPosiciones(Puntos2,Nombre2,VPuntos,VNombres);
            Bandera=true;


        }

        break;
        case 3:
            MostrarTablaPosiciones(VPuntos,VNombres);
            break;
        case 4:
        {

            int Puntos=0,Puntos2=0;
            string Nombre, Nombre2;
            EfectoBarraCargando(AnchoMedio-4,AltoMedio,"Cargando");
            ModoSimulador(Puntos,Puntos2,Nombre,Nombre2,AnchoMedio);
            TablaPosiciones(Puntos,Nombre,VPuntos,VNombres);
            TablaPosiciones(Puntos2,Nombre2,VPuntos,VNombres);
            Bandera=true;



        }
        break;
        case 0:
            CartelFinDelJuego();
            return ;
            break;
        }
        Opcion=' ';

    }


}
