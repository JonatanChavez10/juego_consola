#pragma once

void CartelPrimeroArranca(std::string Nombre);
int DeterminarOrden();
void CartelTurnoDosJugadores(std::string JugadorRonda,std::string JugadorAnterior,int rondas, int PuntosJugadorAnterior, int PuntosJugadorRonda);
void ModoDosJugadores (int &Puntos,int &Puntos2, std::string &Nombre,std::string &Nombre2,int AnchoConsola);
void CartelFinDelJuego();
void UnJugador(int &Puntos, std::string &Nombre,int AnchoConsola);
void ModoSimulador(int &Puntos,int &Puntos2, std::string &Nombre,std::string &Nombre2,int AnchoConsola);
void LanzamientoDados(int v[],int TAm);
bool ComprobarEscalera(int v[],int TAm);
bool ComprobarSexteto6(int v[],int TAm);
bool ComprobarSexteto(int v[],int TAm);
void MostrarIntento(int v[],int TAm);
void EncabezadoJuego (std::string Nombre,int puntos,int Rondas,int AnchoConsola);
int sumarVector(int v[], int tam );
int maximoVector(int v[], int tam);
void CartelGanador(std::string Nombre,int Puntos);
void TablaPosiciones(int Puntos,std::string Nombre,int VPuntos[],std::string VNombres[]);
void MostrarTablaPosiciones(int VPuntos[],std::string VNombres[]);
void ElegirDados (int v[],int TAm);
void ordenarVector(int v[], int tam );
void copiarVector(int v[], int v2[],int tam );
int posicionNumeroEnVector(int v[],int tam, int numero);
void ordenarVectorDecreciente(int v1[],std::string v2[], int tam );
void CargarNombre(std::string v[],std::string Nombre);
void dibujarDado(int numero, int posx, int posy);
void dibujarCuadrado(int posx, int posy);
void CartelTurnoUnJugadores(std::string JugadorRonda,int rondas,int PuntosJugadorRonda);
void ponerCero(int v[], int tam);
void EfectoBarraCargando(int posX, int posY,std::string mensaje = "Sorteando jugador inicial");
char CantidadDeJugadores();
void RecuadrosJuego(int AnchoConsola);
void DadosMenu(int posx, int posy);
void Menu();

