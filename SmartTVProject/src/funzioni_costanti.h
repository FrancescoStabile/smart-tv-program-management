/*
 * funzioni_costanti.h
 *
 *  Created on: Sep 6, 2022
 *      Author: Francesco Stabile
 *
 */

#ifndef FUNZIONI_COSTANTI_H_
#define FUNZIONI_COSTANTI_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_NUM_CARATTERI 60	//costante che limita la lunghezza di tutte le stringhe in input nel programma
#define MAX_VALUTAZIONE 5
#define MIN_VALUTAZIONE 1

//Struct contenente le informazioni del profilo creato dall'utente (inserite in fase di creazione del profilo e successivamente modificabili)
typedef struct {
	char nome[MAX_NUM_CARATTERI];
	char email[MAX_NUM_CARATTERI];
	int eta;
} utente_t;

//struct per le categorie dei programmi tv (inserite in fase di creazione del profilo e successivamente modificabili)
typedef struct {
	int codice;
	char nome[MAX_NUM_CARATTERI];
} categorie_prog_utente;

//struct per le tipologie di programmi tv preferite dall'utente (inserite in fase di creazione del profilo e successivamente modificabili)
typedef struct {
	int codice;
	char nome[MAX_NUM_CARATTERI];
} tipi_prog_utente;

//struct contenente le informazioni di ciascun programma tv inserito dall'utente all'interno della smart tv
typedef struct {
	char nome[MAX_NUM_CARATTERI];
	char categoria[MAX_NUM_CARATTERI];	//campo contenente l'argomento di interesse del programma tv (cucina, natura, fantascienza, sport, ecc...)
	char tipo[MAX_NUM_CARATTERI];		//campo contenente la tipologia del programma tv (cinema, serie, intrattenimento, documentari, ecc...)
	int valutazione;					//valutazione assegnata dall'utente al programma tv (da 1 a 5, inizializzato a 0)
	int durata;							//durata espressa in minuti del programma tv
	int codice;							//codice ID del programma, utilizzato nel programma quando l'utente dovrá selezionare un programma in particolare da una lista a sua disposizione
	int proposto;						//utilizzato come flag all'interno del programma per riconoscere i programmi giá valutati e non riproporli all'utente
} programmi_smart_tv;

//funzioni per l'inserimento/modifica/cancellazione/lettura del profilo utente e delle categorie/tipologie preferite
void inserimento_utente(FILE *utente, FILE *catutente, FILE *tipiutente);
void modifica_utente(FILE *utente, FILE *catutente, FILE *tipiutente);
void modifica_cat_utente(FILE *catutente);
void modifica_tipi_utente(FILE *tipiutente);
void leggi_utente(FILE *utente, FILE *catutente, FILE *tipiutente);

//funzioni per l'inserimento/modifica/cancellazione/lettura dei programmi tv inseriti all'interno della smart tv da parte dell'utente
void inserimento_programmi_tv(FILE *programmitv);
void leggi_programmi_tv (FILE *programmitv);
void modifica_programmi_tv(FILE *programmitv);
void cancella_programmi_tv(FILE *programmitv);

//funzione di ricerca di uno specifico programma tv all'interno del sistema smart tv
void ricerca_programmi_tv(FILE *programmitv);

//funzione per la valutazione del programma televisivo scelto, chiamata dopo la ricerca o dopo il suggerimento da parte della smart tv di un programma
void valutazione_programmi_tv(FILE *programmitv, int codice_prog);


//funzione per il suggerimento di un programma tv da parte del sistema in base alle tipologie ed alle categorie inserite nel profilo utente
void suggerimento_programmi_tv(FILE *programmitv, FILE *catutente, FILE *tipiutente);

//funzione che genera un array di struct contenente tutti i programmi la cui categoria ha ricevuto un voto maggiore di 3, chiamata all'interno di "suggerimento_programmi_tv"
void categorie_suggerite (FILE *programmitv);

//funzioni che si occupano dell'ordinamento (crescente) dei programmi tv in base alla valutazione ricevuta utilizzato l'algoritmo avanzato quicksort
void ordinamento_programmi_tv(FILE *programmitv);
void quicksort(programmi_smart_tv programmi_array[], int dimensione);
void partizione (programmi_smart_tv programmi_array[], int l, int r);

//funzioni per la stampa dei menu di navigazione
void menu_iniziale(FILE *programmitv, FILE *utente, FILE *catutente, FILE *tipiutente);
void menu_utente(FILE *utente, FILE *catutente, FILE *tipiutente);
void menu_programmi(FILE *programmitv);

#endif /* FUNZIONI_COSTANTI_H_ */
