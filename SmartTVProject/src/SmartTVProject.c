/*
 ============================================================================
 Name        : SmartTVProject.c
 Author      : Stabile Francesco
 Copyright   : Your copyright notice
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "funzioni_costanti.h"

int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0);

	FILE *file_utente;
	FILE *file_categorie_utente;
	FILE *file_tipi_utente;
	FILE *file_programmitv;

	file_utente = fopen("utente.dat", "rb+");
	file_programmitv = fopen("programmitv.dat", "rb+");
	file_categorie_utente = fopen("catutente.dat", "rb+");
	file_tipi_utente = fopen("tipiutente.dat", "rb+");

	if (file_utente == NULL || file_programmitv == NULL || file_categorie_utente == NULL || file_tipi_utente == NULL) {
		printf("\nImpossibile aprire il file, il sistema verrá avviato con dei file vuoti appena creati!\n");
		file_utente = fopen("utente.dat", "wb+");
		file_programmitv = fopen("programmitv.dat", "wb+");
		file_categorie_utente = fopen("catutente.dat", "wb+");
		file_tipi_utente = fopen("tipiutente.dat", "wb+");
	}
	else {
		printf("\nInizio programma\n");
		menu_iniziale(file_programmitv, file_utente, file_categorie_utente, file_tipi_utente);
	}

	// Chiusura dei file
	fclose(file_utente);
	fclose(file_programmitv);
	fclose(file_categorie_utente);
	fclose(file_tipi_utente);

	return EXIT_SUCCESS;
}

