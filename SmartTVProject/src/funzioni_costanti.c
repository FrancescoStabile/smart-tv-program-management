/*
 ============================================================================
 Name        : funzioni_costanti.c
 Author      : Stabile Francesco
 Copyright   : Your copyright notice
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "funzioni_costanti.h"

void inserimento_utente(FILE *utente, FILE *catutente, FILE *tipiutente) {
	utente_t profilo_utente = {"", "", 0};	// Struct per il profilo utente
	tipi_prog_utente tipi_utente;	// Struct per le tipologie di programmi preferite dall'utente
	categorie_prog_utente cat_utente;	// Struct per le categorie di programmi preferite dall'utente
	int j = -1, i = 0;	// Variabili di controllo
	char risposta;

	int flag = 0;
	printf("\n*********************************************************** CREAZIONE NUOVO PROFILO UTENTE ***********************************************************");
	while (flag == 0) {
		printf("\nInserire il nome utente --> ");
		scanf(" %[^\n]s", profilo_utente.nome);

		if (strlen(profilo_utente.nome) <= MAX_NUM_CARATTERI && strlen(profilo_utente.nome) > 0) {
			flag = 1;
			// Inserimento dell'età e verifica della validità
			for (i = 0; profilo_utente.nome[i] != '\0'; i++) {
				profilo_utente.nome[i] = tolower(profilo_utente.nome[i]);
			}
			printf("\nInserire indirizzo email --> ");
			scanf("%s", profilo_utente.email);

			while (profilo_utente.eta == 0) {
				printf("\nInserire l'età --> ");
				scanf("%d", &profilo_utente.eta);

				if (profilo_utente.eta > 1 && profilo_utente.eta < 135) {
					// Inserimento dell'età e verifica della validità
					printf("\nProfilo utente compilato correttamente %s", profilo_utente.nome);
					// Salvataggio del profilo utente nel file "utente"
					fseek(utente, 0, SEEK_SET);
					fwrite(&profilo_utente, sizeof(profilo_utente), 1, utente);
				} else {
					printf("\nL'età inserita non è corretta!");
					profilo_utente.eta = 0;
				}
			}
		} else {
			printf("\nIl nome utente inserito non è valido, limite: 50 caratteri");
		}
	}

	risposta = '\0';
	do {
		flag = 0;
		while (flag == 0) {
			// Inserimento delle categorie preferite dall'utente
			printf("\nInserire la categoria di programmi televisivi preferita (cucina, sport, fantasy...) --> ");
			printf("\nNome categoria --> ");
			scanf(" %[^\n]s", cat_utente.nome);

			if (strlen(cat_utente.nome) <= MAX_NUM_CARATTERI && strlen(cat_utente.nome) > 0) {
				j = j + 1;
				cat_utente.codice = j + 1;
				flag = 1;
				// Trasformazione del nome della categoria in minuscolo
				for (i = 0; cat_utente.nome[i] != '\0'; i++) {
					cat_utente.nome[i] = tolower(cat_utente.nome[i]);
				}
				// Salva la categoria nel file "catutente"
				fseek(catutente, j * sizeof(categorie_prog_utente), SEEK_SET);
				fwrite(&cat_utente, sizeof(categorie_prog_utente), 1, catutente);
			} else {
				printf("\nIl nome per la categoria inserito non è valido, limite: 50 caratteri");
			}
		}
		printf("\n-----------------------------------------------------------Elemento inserito correttamente!-----------------------------------------------------------");
		printf("\nInserire un'altra categoria tra i preferiti? (s/n) --> ");
		scanf(" %c", &risposta);
	} while (risposta == 's' || risposta == 'S');
	printf("Categorie preferite inserite correttamente!");

	risposta = '\0';
	j = -1;
	do {
		flag = 0;
		while (flag == 0) {
			// Inserimento delle tipologie di programmi preferite dall'utente
			printf("\nInserire le tipologie di programmi televisivi preferiti (documentari, serie, film, bambini...) --> ");
			printf("\nNome tipo --> ");
			scanf(" %[^\n]s", tipi_utente.nome);

			if (strlen(tipi_utente.nome) <= MAX_NUM_CARATTERI && strlen(tipi_utente.nome) > 0) {
				j = j + 1;
				tipi_utente.codice = j + 1;
				flag = 1;
				// Trasformazione del nome del tipo in minuscolo
				for (i = 0; tipi_utente.nome[i] != '\0'; i++) {
					tipi_utente.nome[i] = tolower(tipi_utente.nome[i]);
				}
				// Salva il tipo nel file "tipiutente"
				fseek(tipiutente, j * sizeof(tipi_prog_utente), SEEK_SET);
				fwrite(&tipi_utente, sizeof(tipi_prog_utente), 1, tipiutente);
			} else {
				printf("\nIl nome inserito non è valido, limite: 50 caratteri");
			}
		}
		printf("\n-----------------------------------------------------------Elemento inserito correttamente!-----------------------------------------------------------");
		printf("\nInserire un altro tipo di programma tra i preferiti? (s/n) --> ");
		scanf(" %c", &risposta);
	} while (risposta == 's' || risposta == 'S');
	printf("\n************************************************************* CREAZIONE PROFILO TERMINATA ************************************************************");
}

void leggi_utente(FILE *utente, FILE *catutente, FILE *tipiutente) {
	utente_t profilo_utente;  // Struct per il profilo utente
	tipi_prog_utente tipi_utente;  // Struct per le tipologie di programmi preferite dall'utente
	categorie_prog_utente cat_utente;  // Struct per le categorie di programmi preferite dall'utente

	rewind(utente);  // Riporta il puntatore del file "utente" all'inizio
	rewind(catutente);  // Riporta il puntatore del file "catutente" all'inizio
	rewind(tipiutente);  // Riporta il puntatore del file "tipiutente" all'inizio

	printf("\n******************************************************************* PROFILO UTENTE *******************************************************************");
	printf("\n%-50s %-50s %-50s\n", "Nome utente", "Email", "Etá");

	// Legge e stampa tutti i profili utente presenti nel file "utente"
	while (fread(&profilo_utente, sizeof(utente_t), 1, utente) == 1) {
		printf("\n%-50s %-50s %-50d\n", profilo_utente.nome, profilo_utente.email, profilo_utente.eta);
	}

	printf("\n------------------------------------------------------------------Categorie preferite-----------------------------------------------------------------");

	// Legge e stampa tutte le categorie preferite presenti nel file "catutente"
	while (fread(&cat_utente, sizeof(categorie_prog_utente), 1, catutente) == 1) {
		printf("\n%s\n", cat_utente.nome);
	}

	printf("\n--------------------------------------------------------------------Tipi preferiti--------------------------------------------------------------------");

	// Legge e stampa tutti i tipi preferiti presenti nel file "tipiutente"
	while (fread(&tipi_utente, sizeof(tipi_prog_utente), 1, tipiutente) == 1) {
		printf("\n%s\n", tipi_utente.nome);
	}

	printf("\n************************************************************** PROFILO UTENTE TERMINATO **************************************************************");
}

void modifica_utente(FILE *utente, FILE *catutente, FILE *tipiutente) {
	utente_t profilo_utente = {"", "", 0};  // Struct per il profilo utente
	int i = 0, flag = 0;

	leggi_utente(utente, catutente, tipiutente);  // Stampa il profilo utente attuale

	printf("\n----------------------------------------------------------------Modifica Profilo Utente---------------------------------------------------------------");

	fseek(utente, 0, SEEK_SET);  // Riporta il puntatore del file "utente" all'inizio
	fread(&profilo_utente, sizeof(profilo_utente), 1, utente);  // Legge il profilo utente dal file "utente"

	if (!feof(utente)) {  // Se il file "utente" non è vuoto
		while (flag == 0) {
			printf("\nNome --> ");
			scanf(" %[^\n]s", profilo_utente.nome);

			if (strlen(profilo_utente.nome) <= MAX_NUM_CARATTERI && strlen(profilo_utente.nome) > 0) {
				flag = 1;

				for (i = 0; profilo_utente.nome[i] != '\0'; i++) {
					profilo_utente.nome[i] = tolower(profilo_utente.nome[i]);  // Converte il nome utente in minuscolo
				}

				printf("\nEmail --> ");
				scanf("%s", profilo_utente.email);
				profilo_utente.eta = 0;

				while (profilo_utente.eta == 0) {
					printf("\nEtá --> ");
					scanf("%d", &profilo_utente.eta);

					if (profilo_utente.eta > 1 && profilo_utente.eta < 135) {
						printf("\nProfilo utente compilato correttamente %s", profilo_utente.nome);
						fseek(utente, 0, SEEK_SET);
						fwrite(&profilo_utente, sizeof(profilo_utente), 1, utente);  // Aggiorna il profilo utente nel file "utente"
					} else {
						printf("\nL'età inserita non è corretta!");
						profilo_utente.eta = 0;
					}
				}
			} else {
				printf("\nIl nome utente inserito non è valido, limite: 50 caratteri");
			}
		}
	} else {
		printf("\nProfilo utente non ancora registrato!");
	}

	modifica_cat_utente(catutente);  // Modifica le categorie preferite dell'utente
	modifica_tipi_utente(tipiutente);  // Modifica i tipi preferiti dell'utente

	leggi_utente(utente, catutente, tipiutente);  // Stampa il profilo utente aggiornato
}

void modifica_cat_utente(FILE *catutente) {
	categorie_prog_utente cat_utente = {0, ""};  // Struct per la categoria utente
	int i = 0, flag = 0, dimensione = 0;
	char risposta;

	printf("\n-------------------------------------------------------------Modifica categorie preferite-------------------------------------------------------------");

	do {
		rewind(catutente);  // Riporta il puntatore del file "catutente" all'inizio
		flag = 0;

		printf("\n%-50s %-50s\n", "ID", "Categoria");

		while (fread(&cat_utente, sizeof(categorie_prog_utente), 1, catutente) == 1) {
			printf("\n%d %s", cat_utente.codice, cat_utente.nome);  // Stampa le categorie esistenti
		}

		printf("\nInserire il codice ID della categoria da modificare (-1 per aggiungere un nuovo elemento) --> ");
		scanf("%d", &cat_utente.codice);

		if (cat_utente.codice > 0) {
			fseek(catutente, (cat_utente.codice - 1) * sizeof(categorie_prog_utente), SEEK_SET);  // Posiziona il puntatore del file sulla categoria selezionata
			fread(&cat_utente, sizeof(categorie_prog_utente), 1, catutente);  // Legge la categoria dal file

			if (!feof(catutente) && cat_utente.codice != 0) {
				while (flag == 0) {
					printf("\nNome categoria --> ");
					scanf(" %[^\n]s", cat_utente.nome);

					if (strlen(cat_utente.nome) <= MAX_NUM_CARATTERI && strlen(cat_utente.nome) > 0) {
						flag = 1;

						for (i = 0; cat_utente.nome[i] != '\0'; i++) {
							cat_utente.nome[i] = tolower(cat_utente.nome[i]);  // Converte il nome categoria in minuscolo
						}

						printf("\n----------------------------------------------------Categoria modificata correttamente nel profilo!---------------------------------------------------");
						fseek(catutente, (cat_utente.codice - 1) * sizeof(categorie_prog_utente), SEEK_SET);
						fwrite(&cat_utente, sizeof(categorie_prog_utente), 1, catutente);  // Aggiorna la categoria nel file "catutente"
					} else {
						printf("\nIl nome inserito non è valido, limite: 50 caratteri");
					}
				}

				printf("\nVuoi modificare un'altra categoria? (s/n) --> ");
				scanf(" %c", &risposta);
			}
		} else if (cat_utente.codice == -1) {
			fseek(catutente, 0, SEEK_END);  // Posiziona il puntatore del file alla fine
			dimensione = ftell(catutente) / sizeof(categorie_prog_utente);  // Calcola la dimensione attuale del file

			while (flag == 0) {
				printf("\nInserire la categoria di programmi televisivi preferita (cucina, sport, fantasy...) --> ");
				printf("\nNome categoria --> ");
				scanf(" %[^\n]s", cat_utente.nome);

				if (strlen(cat_utente.nome) <= MAX_NUM_CARATTERI && strlen(cat_utente.nome) > 0) {
					cat_utente.codice = dimensione + 1;  // Assegna un nuovo codice alla categoria
					flag = 1;

					for (i = 0; cat_utente.nome[i] != '\0'; i++) {
						cat_utente.nome[i] = tolower(cat_utente.nome[i]);  // Converte il nome categoria in minuscolo
					}

					printf("\n-----------------------------------------------------Categoria aggiunta correttamente al profilo!-----------------------------------------------------");
					fseek(catutente, (cat_utente.codice - 1) * sizeof(categorie_prog_utente), SEEK_SET);
					fwrite(&cat_utente, sizeof(categorie_prog_utente), 1, catutente);  // Aggiunge la nuova categoria al file "catutente"
				} else {
					printf("\nIl nome per la categoria inserito non è valido, limite: 50 caratteri");
				}
			}

			printf("\nVuoi modificare o aggiungere un'altra categoria di programmi nel profilo? (s/n) --> ");
			scanf(" %c", &risposta);
		} else {
			printf("\nID inserito errato!");
		}
	} while ((risposta == 's') || (risposta == 'S'));
}

void modifica_tipi_utente(FILE *tipiutente) {
	tipi_prog_utente tipi_utente = {0, ""};  // Struct per la tipologia utente
	int i = 0, flag = 0, dimensione = 0;
	char risposta;

	printf("\n-------------------------------------------------------------Modifica tipologie preferite-------------------------------------------------------------");

	do {
		rewind(tipiutente);  // Riporta il puntatore del file "tipiutente" all'inizio
		flag = 0;

		printf("\n%-50s %-50s\n", "ID", "Tipologia di programma");

		while (fread(&tipi_utente, sizeof(tipi_prog_utente), 1, tipiutente) == 1) {
			printf("\n%d %s", tipi_utente.codice, tipi_utente.nome);  // Stampa le tipologie esistenti
		}

		printf("\nInserire il codice ID della tipologia di programma da modificare (-1 per aggiungere un nuovo elemento) --> ");
		scanf("%d", &tipi_utente.codice);

		if (tipi_utente.codice > 0) {
			fseek(tipiutente, (tipi_utente.codice - 1) * sizeof(tipi_prog_utente), SEEK_SET);  // Posiziona il puntatore del file sulla tipologia selezionata
			fread(&tipi_utente, sizeof(tipi_prog_utente), 1, tipiutente);  // Legge la tipologia dal file

			if (!feof(tipiutente) && tipi_utente.codice != 0) {
				while (flag == 0) {
					printf("\nNome categoria --> ");
					scanf(" %[^\n]s", tipi_utente.nome);

					if (strlen(tipi_utente.nome) <= MAX_NUM_CARATTERI && strlen(tipi_utente.nome) > 0) {
						flag = 1;

						for (i = 0; tipi_utente.nome[i] != '\0'; i++) {
							tipi_utente.nome[i] = tolower(tipi_utente.nome[i]);  // Converte il nome tipologia in minuscolo
						}

						printf("\n----------------------------------------------------Tipologia modificata correttamente nel profilo!---------------------------------------------------");
						fseek(tipiutente, (tipi_utente.codice - 1) * sizeof(tipi_prog_utente), SEEK_SET);
						fwrite(&tipi_utente, sizeof(tipi_prog_utente), 1, tipiutente);  // Aggiorna la tipologia nel file "tipiutente"
					} else {
						printf("\nIl nome inserito non è valido, limite: 50 caratteri");
					}
				}

				printf("\nVuoi modificare un'altra tipologia di programmi nel profilo? (s/n) --> ");
				scanf(" %c", &risposta);
			}
		} else if (tipi_utente.codice == -1) {
			fseek(tipiutente, 0, SEEK_END);  // Posiziona il puntatore del file alla fine
			dimensione = ftell(tipiutente) / sizeof(tipi_prog_utente);  // Calcola la dimensione attuale del file

			while (flag == 0) {
				printf("\nInserire la tipologia di programmi televisivi preferita (documentari, serie, film, bambini...) --> ");
				printf("\nNome tipologia --> ");
				scanf(" %[^\n]s", tipi_utente.nome);

				if (strlen(tipi_utente.nome) <= MAX_NUM_CARATTERI && strlen(tipi_utente.nome) > 0) {
					tipi_utente.codice = dimensione + 1;  // Assegna un nuovo codice alla tipologia
					flag = 1;

					for (i = 0; tipi_utente.nome[i] != '\0'; i++) {
						tipi_utente.nome[i] = tolower(tipi_utente.nome[i]);  // Converte il nome tipologia in minuscolo
					}

					printf("\n-----------------------------------------Tipologia di programma televisivo aggiunta correttamente al profilo!-----------------------------------------");
					fseek(tipiutente, (tipi_utente.codice - 1) * sizeof(tipi_prog_utente), SEEK_SET);
					fwrite(&tipi_utente, sizeof(tipi_prog_utente), 1, tipiutente);  // Aggiunge la nuova tipologia al file "tipiutente"
				} else {
					printf("\nIl nome per la tipologia inserito non è valido, limite: 50 caratteri");
				}
			}

			printf("\nVuoi modificare o aggiungere un'altra tipologia di programmi nel profilo? (s/n) --> ");
			scanf(" %c", &risposta);
		} else {
			printf("\nID inserito errato!");
		}
	} while ((risposta == 's') || (risposta == 'S'));
}

void inserimento_programmi_tv(FILE *programmitv) {
	programmi_smart_tv prog_tv = {"", "", "", 0, 0, 0, 0};  // Struct per il programma TV
	int j = -1, i = 0;  // Variabili contatore
	char risposta;

	printf("\nCreazione programma televisivo:");

	do {
		int flag = 0;  // Flag per il controllo della validità dell'input

		while (flag == 0) {
			printf("\nInserire il nome del programma televisivo --> ");
			scanf(" %[^\n]s", prog_tv.nome);

			if (strlen(prog_tv.nome) <= MAX_NUM_CARATTERI && strlen(prog_tv.nome) > 0) {
				flag = 1;

				for (i = 0; prog_tv.nome[i] != '\0'; i++) {
					prog_tv.nome[i] = tolower(prog_tv.nome[i]);  // Converte il nome del programma in minuscolo
				}
			} else {
				printf("\nIl nome inserito non è valido, limite: 50 caratteri");
			}
		}

		flag = 0;

		while (flag == 0) {
			printf("\nInserire la categoria di appartenenza del programma televisivo (cucina, sport, fantasy...) --> ");
			scanf(" %[^\n]s", prog_tv.categoria);

			if (strlen(prog_tv.categoria) <= MAX_NUM_CARATTERI && strlen(prog_tv.categoria) > 0) {
				flag = 1;

				for (i = 0; prog_tv.categoria[i] != '\0'; i++) {
					prog_tv.categoria[i] = tolower(prog_tv.categoria[i]);  // Converte il nome della categoria in minuscolo
				}
			} else {
				printf("\nNome categoria inserito non valido, limite: 50 caratteri");
			}
		}

		flag = 0;

		while (flag == 0) {
			printf("\nInserire la tipologia di appartenenza del programma televisivo (documentari, serie, film, bambini...) --> ");
			scanf(" %[^\n]s", prog_tv.tipo);

			if (strlen(prog_tv.tipo) <= MAX_NUM_CARATTERI && strlen(prog_tv.tipo) > 0) {
				flag = 1;

				for (i = 0; prog_tv.tipo[i] != '\0'; i++) {
					prog_tv.tipo[i] = tolower(prog_tv.tipo[i]);  // Converte il nome della tipologia in minuscolo
				}
			} else {
				printf("\nIl nome inserito per la tipologia di programma non é valido, limite: 50 caratteri");
			}
		}

		prog_tv.valutazione = 0;  // Inizializza la valutazione a 0
		prog_tv.proposto = 0;  // Inizializza il flag "proposto" a 0
		prog_tv.durata = 0;  // Inizializza la durata a 0

		while (prog_tv.durata == 0) {
			printf("\nInserire la durata del programma (in minuti) --> ");
			scanf("%d", &prog_tv.durata);

			if (prog_tv.durata > 1 && prog_tv.durata < 239) {  // Verifica che la durata sia compresa tra 1 e 238 minuti
				printf("\nIl programma é stato inserito con successo nella smart tv!");
				j++;
				prog_tv.codice = j + 1;  // Assegna un nuovo codice al programma
				fseek(programmitv, j * sizeof(programmi_smart_tv), SEEK_SET);
				fwrite(&prog_tv, sizeof(programmi_smart_tv), 1, programmitv);  // Scrive il programma nel file "programmitv"
				printf("\nInserire un altro programma nella Smart TV? (s/n) --> ");
				scanf(" %c", &risposta);
			} else {
				printf("\nLa durata del programma inserita non è corretta!");
				prog_tv.durata = 0;
			}
		}
	} while ((risposta == 's') || (risposta == 'S'));
}

void leggi_programmi_tv(FILE *programmitv) {
	programmi_smart_tv prog_tv;  // Variabile per leggere i programmi TV dal file

	rewind(programmitv);  // Riporta il puntatore del file all'inizio

	printf("\n***************************************************************** PROGRAMMI SMART TV ****************************************************************************************************");
	printf("\n%-50s %-50s %-50s %-20s %-20s\n", "Nome", "Categoria", "Tipologia", "Durata (minuti)", "Valutazione");

	while (!feof(programmitv)) {
		fread(&prog_tv, sizeof(programmi_smart_tv), 1, programmitv);  // Legge un programma TV dal file

		if (!feof(programmitv)) {  // Verifica se il file non è terminato
			printf("\n%-50s %-50s %-50s %-20d %-20d\n", prog_tv.nome, prog_tv.categoria, prog_tv.tipo, prog_tv.durata, prog_tv.valutazione);  // Stampa i dettagli del programma TV
		}
	}
}

void modifica_programmi_tv(FILE *programmitv) {
	programmi_smart_tv prog_tv = {"", "", "", 0, 0, 0, 0};  // Variabile per leggere/modificare i programmi TV nel file
	int flag = 0, i = 0, temp_valutazione = 0, temp_proposto = 0;
	char risposta;

	printf("\n----------------------------------------------------------------Modifica Programmi Smart TV----------------------------------------------------------------------------------------------");

	do {
		rewind(programmitv);  // Riporta il puntatore del file all'inizio
		flag = 0;

		printf("\n%-50s %-50s %-50s %-50s %-20s %-20s\n", "ID", "Nome", "Categoria", "Tipologia", "Durata (minuti)", "Valutazione");

		while (!feof(programmitv)) {
			fread(&prog_tv, sizeof(programmi_smart_tv), 1, programmitv);  // Legge un programma TV dal file

			if (!feof(programmitv)) {  // Verifica se il file non è terminato
				printf("\n%-50d %-50s %-50s %-50s %-20d %-20d\n", prog_tv.codice, prog_tv.nome, prog_tv.categoria, prog_tv.tipo, prog_tv.durata, prog_tv.valutazione);  // Stampa i dettagli del programma TV
			}
		}

		printf("\nInserire il codice ID del programma da modificare --> ");
		scanf("%d", &prog_tv.codice);

		if (prog_tv.codice > 0) {
			fseek(programmitv, (prog_tv.codice - 1) * sizeof(programmi_smart_tv), SEEK_SET);  // Posiziona il puntatore del file all'inizio del programma selezionato
			fread(&prog_tv, sizeof(programmi_smart_tv), 1, programmitv);  // Legge il programma selezionato dal file

			temp_valutazione = prog_tv.valutazione;  // Salva temporaneamente il valore di valutazione originale
			temp_proposto = prog_tv.proposto;  // Salva temporaneamente il valore di proposto originale

			if (!feof(programmitv) && prog_tv.codice != 0) {  // Verifica se il programma selezionato esiste
				flag = 0;

				while (flag == 0) {
					printf("\nInserire il nome del programma televisivo --> ");
					scanf(" %[^\n]s", prog_tv.nome);

					if (strlen(prog_tv.nome) <= MAX_NUM_CARATTERI && strlen(prog_tv.nome) > 0) {
						flag = 1;

						for (i = 0; prog_tv.nome[i] != '\0'; i++) {
							prog_tv.nome[i] = tolower(prog_tv.nome[i]);  // Converte il nome del programma in minuscolo
						}
					} else {
						printf("\nIl nome inserito non è valido, limite: 50 caratteri");
					}
				}

				flag = 0;

				while (flag == 0) {
					printf("\nInserire la categoria di appartenenza del programma televisivo (cucina, sport, fantasy...) --> ");
					scanf(" %[^\n]s", prog_tv.categoria);

					if (strlen(prog_tv.categoria) <= MAX_NUM_CARATTERI && strlen(prog_tv.categoria) > 0) {
						flag = 1;

						for (i = 0; prog_tv.categoria[i] != '\0'; i++) {
							prog_tv.categoria[i] = tolower(prog_tv.categoria[i]);  // Converte il nome della categoria in minuscolo
						}
					} else {
						printf("\nNome categoria inserito non valido, limite: 50 caratteri");
					}
				}

				flag = 0;

				while (flag == 0) {
					printf("\nInserire la tipologia di appartenenza del programma televisivo (documentari, serie, film, bambini...) --> ");
					scanf(" %[^\n]s", prog_tv.tipo);

					if (strlen(prog_tv.tipo) <= MAX_NUM_CARATTERI && strlen(prog_tv.tipo) > 0) {
						flag = 1;

						for (i = 0; prog_tv.tipo[i] != '\0'; i++) {
							prog_tv.tipo[i] = tolower(prog_tv.tipo[i]);  // Converte il nome della tipologia in minuscolo
						}
					} else {
						printf("\nIl nome inserito per la tipologia di programma non é valido, limite: 50 caratteri");
					}
				}

				prog_tv.valutazione = temp_valutazione;  // Ripristina il valore di valutazione originale
				prog_tv.proposto = temp_proposto;  // Ripristina il valore di proposto originale
				prog_tv.durata = 0;

				while (prog_tv.durata == 0) {
					printf("\nInserire la durata del programma (in minuti) --> ");
					scanf("%d", &prog_tv.durata);

					if (prog_tv.durata > 1 && prog_tv.durata < 239) {
						printf("\nIl programma é stato inserito con successo nella smart tv!");
						fseek(programmitv, (prog_tv.codice - 1) * sizeof(programmi_smart_tv), SEEK_SET);  // Posiziona il puntatore del file all'inizio del programma selezionato
						fwrite(&prog_tv, sizeof(prog_tv), 1, programmitv);  // Scrive il programma modificato nel file
						printf("\n--------------------------------------------------------------------MODIFICA TERMINATA----------------------------------------------------------------");
						printf("\nInserire un altro programma nella Smart TV? (s/n) --> ");
						scanf(" %c", &risposta);
					} else {
						printf("\nLa durata del programma inserita non è corretta!");
						prog_tv.durata = 0;
					}
				}
			}
		}
	} while ((risposta == 's') || (risposta == 'S'));
}

void cancella_programmi_tv(FILE *programmitv) {
	programmi_smart_tv prog_tv, prog_tv_reset = {"", "", "", 0, 0, 0, 0};  // Variabile per leggere il programma TV da cancellare, variabile per ripristinare i valori di default
	int codice = 0;
	char risposta;

	do {
		rewind(programmitv);  // Riporta il puntatore del file all'inizio
		printf("\n---------------------------------------------------------------Cancella Programmi Smart TV------------------------------------------------------------");
		printf("\n%-50s %-50s %-50s %-50s %-20s %-20s\n", "ID", "Nome", "Categoria", "Tipologia", "Durata (minuti)", "Valutazione");

		while (!feof(programmitv)) {
			fread(&prog_tv, sizeof(programmi_smart_tv), 1, programmitv);  // Legge un programma TV dal file

			if (!feof(programmitv)) {  // Verifica se il file non è terminato
				printf("\n%-50d %-50s %-50s %-50s %-20d %-20d\n", prog_tv.codice, prog_tv.nome, prog_tv.categoria, prog_tv.tipo, prog_tv.durata, prog_tv.valutazione);  // Stampa i dettagli del programma TV
			}
		}

		printf("\nInserire il codice ID del programma tv da cancellare --> ");
		scanf("%d", &prog_tv.codice);

		if (prog_tv.codice > 0) {
			fseek(programmitv, (prog_tv.codice - 1) * sizeof(programmi_smart_tv), SEEK_SET);  // Posiziona il puntatore del file all'inizio del programma selezionato
			fread(&prog_tv, sizeof(programmi_smart_tv), 1, programmitv);  // Legge il programma selezionato dal file

			if (!feof(programmitv) && prog_tv.codice != 0) {  // Verifica se il programma selezionato esiste
				codice = prog_tv.codice;
				prog_tv = prog_tv_reset;  // Assegna i valori di default al programma da cancellare
				fseek(programmitv, (codice - 1) * sizeof(programmi_smart_tv), SEEK_SET);  // Posiziona il puntatore del file all'inizio del programma selezionato
				fwrite(&prog_tv, sizeof(prog_tv), 1, programmitv);  // Scrive il programma modificato (cancellato) nel file
				printf("\nProgramma TV eliminato dalla Smart TV!");
				printf("\n-----------------------------------------------------------------CANCELLAZIONE TERMINATA--------------------------------------------------------------");
				printf("\nCancellare un altro programma dalla Smart TV? (s/n) --> ");
				scanf(" %c", &risposta);
			}
		}
	} while ((risposta == 's') || (risposta == 'S'));
}

void ricerca_programmi_tv(FILE *programmitv) {
	programmi_smart_tv prog_tv;

	char risposta;
	char programma_ric[MAX_NUM_CARATTERI];
	int i = 0, flag = 0, codice = 0;

	do {
		rewind(programmitv);  // Riporta il puntatore del file all'inizio
		flag = 0;
		printf("\n----------------------------------------------------------------Ricerca Programmi Smart TV------------------------------------------------------------");
		printf("\nDigita il nome del programma da cercare nella Smart TV --> ");
		scanf(" %[^\n]s", programma_ric);

		for (i = 0; programma_ric[i] != '\0'; i++) {  // Converte il nome del programma ricercato in lettere minuscole
			programma_ric[i] = tolower(programma_ric[i]);
		}

		if ((strlen(programma_ric) <= MAX_NUM_CARATTERI) && (strlen(programma_ric) > 0)) {  // Controlla la validità della lunghezza del nome ricercato
			while (!feof(programmitv)) {
				fread(&prog_tv, sizeof(programmi_smart_tv), 1, programmitv);  // Legge un programma TV dal file

				if (!feof(programmitv) && (flag == 0)) {
					if (strcmp(prog_tv.nome, programma_ric) == 0) {  // Confronta la stringa ricercata con i nomi dei programmi presenti
						flag = 1;
						codice = prog_tv.codice;
						printf("\n***Il programma %s è presente nella Smart TV!***", programma_ric);
						valutazione_programmi_tv(programmitv, codice);  // Chiama la funzione per visualizzare la valutazione del programma TV
						break;
					}
				}
			}

			if (flag == 0) {
				printf("\nIl programma %s NON è stato trovato!", programma_ric);
			}
		} else {
			printf("\nIl nome del programma inserito non è valido, limite: 50 caratteri");
		}

		printf("\n-------------------------------------------------------------------RICERCA TERMINATA------------------------------------------------------------------");
		printf("\nCercare un altro programma nella Smart TV? (s/n) --> ");
		scanf(" %c", &risposta);
	} while ((risposta == 's') || (risposta == 'S'));
}

void valutazione_programmi_tv(FILE *programmitv, int codice_prog) {
	programmi_smart_tv prog_tv;
	rewind(programmitv);  // Riporta il puntatore del file all'inizio
	int flag = 0;

	printf("\n-----------------------------------------------------------------Valutazione Programma TV-------------------------------------------------------------");
	fseek(programmitv, (codice_prog - 1) * sizeof(programmi_smart_tv), SEEK_SET);  // Si posiziona sul programma da valutare
	fread(&prog_tv, sizeof(programmi_smart_tv), 1, programmitv);

	while (flag == 0) {
		printf("\nInserisci una valutazione per il programma appena visualizzato --> ");
		scanf("%d", &prog_tv.valutazione);

		if (prog_tv.valutazione >= MIN_VALUTAZIONE && prog_tv.valutazione <= MAX_VALUTAZIONE) {  // Verifica della validità dell'input
			printf("\nValutazione effettuata correttamente, con un voto di %d/5", prog_tv.valutazione);
			prog_tv.proposto = 1;  // Imposta il flag "proposto" a 1 per indicare che il programma è stato valutato
			fseek(programmitv, (codice_prog - 1) * sizeof(programmi_smart_tv), SEEK_SET);  // Torna alla posizione del programma nel file
			fwrite(&prog_tv, sizeof(prog_tv), 1, programmitv);  // Scrive la valutazione e il flag nel file
			flag = 1;
		} else {
			printf("\nIl voto inserito non è corretto! (deve essere un valore da 1 a 5)");
		}
	}
}

void categorie_suggerite(FILE *programmitv) {
	programmi_smart_tv prog_tv;

	int dimensione = 0, num_prog = 0, i = 0, j = 0;

	// Calcola la dimensione dell'array cat_voto_alto contando il numero di programmi con valutazione superiore a 3
	rewind(programmitv);
	while (!feof(programmitv)) {
		fread(&prog_tv, sizeof(programmi_smart_tv), 1, programmitv);
		if (!feof(programmitv)) {
			if (prog_tv.valutazione > 3) {
				dimensione++;
			}
		}
	}

	char cat_voto_alto[dimensione][MAX_NUM_CARATTERI];
	memset(cat_voto_alto, '\0', sizeof(cat_voto_alto)); // Inizializza l'array cat_voto_alto con caratteri null

	// Riempie l'array cat_voto_alto con le categorie dei programmi con valutazione superiore a 3
	rewind(programmitv);
	while (!feof(programmitv)) {
		fread(&prog_tv, sizeof(programmi_smart_tv), 1, programmitv);
		if (!feof(programmitv)) {
			if (prog_tv.valutazione > 3) {
				strcpy(cat_voto_alto[j], prog_tv.categoria);
				j++;
			}
		}
	}

	rewind(programmitv);
	fseek(programmitv, 0, SEEK_END);
	num_prog = ftell(programmitv) / sizeof(prog_tv); // Calcola il numero totale di programmi nel file
	rewind(programmitv);

	printf("\n******************************************************* Suggeriti in base alle tue valutazioni ******************************************************************************************");

	// Scorre i programmi nel file e stampa quelli che hanno una categoria presente in cat_voto_alto e non sono ancora stati proposti
	while (!feof(programmitv) && i < num_prog) {
		fread(&prog_tv, sizeof(programmi_smart_tv), 1, programmitv);
		if (!feof(programmitv)) {
			for (j = 0; j < dimensione; j++) {
				if (strcmp(prog_tv.categoria, cat_voto_alto[j]) == 0 && prog_tv.proposto == 0) {
					printf("\n%-50d %-50s %-50s %-50s %-20d %-20d\n", prog_tv.codice, prog_tv.nome, prog_tv.categoria, prog_tv.tipo, prog_tv.durata, prog_tv.valutazione);
					break;
				}
			}
		}
		i++;
	}
}


void suggerimento_programmi_tv(FILE *programmitv, FILE *catutente, FILE *tipiutente) {
	programmi_smart_tv prog_tv;
	categorie_prog_utente cat_utente;
	tipi_prog_utente tipi_utente;

	int dimensione = 0, i = 0, codice = 0;

	// Calcola la dimensione del file programmitv in termini di numero di programmi
	fseek(programmitv, 0, SEEK_END);
	dimensione = ftell(programmitv) / sizeof(prog_tv);
	rewind(programmitv);

	printf("\n--------------------------------------------------------------Programmi suggeriti da Smart TV--------------------------------------------------------------------------------------------");
	printf("\n%-50s %-50s %-50s %-50s %-20s %-20s\n", "ID", "Nome", "Categoria", "Tipologia", "Durata (minuti)", "Valutazione");

	// Scorre i programmi nel file programmitv
	while (!feof(programmitv) && i < dimensione) {
		fread(&prog_tv, sizeof(programmi_smart_tv), 1, programmitv);
		rewind(catutente);
		rewind(tipiutente);
		i++;
		int flag = 0;

		// Scorre le categorie utente nel file catutente e le tipologie utente nel file tipiutente
		while (!feof(catutente) || !feof(tipiutente)) {
			fread(&cat_utente, sizeof(categorie_prog_utente), 1, catutente);
			fread(&tipi_utente, sizeof(tipi_prog_utente), 1, tipiutente);

			if (flag == 0) {
				// Se il programma corrente ha la stessa categoria o tipologia di una categoria o tipologia utente e non è ancora stato proposto, lo stampa
				if (strcmp(prog_tv.categoria, cat_utente.nome) == 0 && prog_tv.proposto == 0) {
					flag = 1;
					printf("\n%-50d %-50s %-50s %-50s %-20d %-20d\n", prog_tv.codice, prog_tv.nome, prog_tv.categoria, prog_tv.tipo, prog_tv.durata, prog_tv.valutazione);
					break;
				} else if (strcmp(prog_tv.tipo, tipi_utente.nome) == 0 && prog_tv.proposto == 0) {
					flag = 1;
					printf("\n%-50d %-50s %-50s %-50s %-20d %-20d\n", prog_tv.codice, prog_tv.nome, prog_tv.categoria, prog_tv.tipo, prog_tv.durata, prog_tv.valutazione);
					break;
				}
			}
		}
	}

	// Stampa le categorie suggerite in base alle valutazioni degli utenti
	categorie_suggerite(programmitv);

	int flag = 0;
	while (flag == 0) {
		printf("\nInserire il codice ID del Programma TV scelto --> ");
		scanf("%d", &prog_tv.codice);
		if (prog_tv.codice > 0) {
			codice = prog_tv.codice;
			// Esegue la valutazione del programma scelto dall'utente
			valutazione_programmi_tv(programmitv, codice);
			flag = 1;
		} else {
			printf("\nCodice ID inserito errato!");
		}
	}

	printf("\n------------------------------------------------------------SUGGERIMENTO PROGRAMMI TERMINATO----------------------------------------------------------");
}

void partizione(programmi_smart_tv programmi_array[], int l, int r) {
	int pivot, j = 0, i = 0;
	programmi_smart_tv temp;

	pivot = programmi_array[(l + r) / 2].valutazione; // Scelta del pivot come valore di valutazione del punto medio
	i = l;
	j = r;

	do {
		while ((programmi_array[i].valutazione < pivot) && (i < r)) {
			i++; // Sposta l'indice `i` verso destra finché l'elemento è minore del pivot
		}
		while ((programmi_array[j].valutazione > pivot) && (j > l)) {
			j--; // Sposta l'indice `j` verso sinistra finché l'elemento è maggiore del pivot
		}
		if (i <= j) {
			temp = programmi_array[i]; // Scambia gli elementi in posizione `i` e `j`
			programmi_array[i] = programmi_array[j];
			programmi_array[j] = temp;
			i++; // Sposta gli indici verso il centro
			j--;
		}
	} while (i <= j);

	if (l < j) {
		partizione(programmi_array, l, j); // Richiama la partizione sulla parte sinistra
	}
	if (i < r) {
		partizione(programmi_array, i, r); // Richiama la partizione sulla parte destra
	}
}

void quicksort(programmi_smart_tv programmi_array[], int dimensione) {
	partizione(programmi_array, 0, dimensione - 1); // Richiama la funzione di partizione per eseguire l'ordinamento QuickSort
}

void ordinamento_programmi_tv(FILE *programmitv) {
	programmi_smart_tv prog_tv;
	rewind(programmitv);
	int i = 0, dimensione = 0;

	fseek(programmitv, 0, SEEK_END);
	dimensione = (ftell(programmitv) / sizeof(prog_tv));
	/*Fseek posiziona il puntatore alla fine del file ed ftell restituisce un intero in byte pari alla dimensione del file dall'inizio alla posizione corrente,
	 * dividendo la dimensione ottenuta con la dimensione della struct otteniamo il numero di elementi (programmi) presenti all'interno del file
	 */
	programmi_smart_tv programmi_array[dimensione]; // array di struct utilizzato per ordinare i programmi presenti all'interno della smart tv

	memset(programmi_array, '\0', sizeof(programmi_array)); // inizializzazione a 0 dell'array
	rewind(programmitv);

	while (!feof(programmitv)) {
		// copia all'interno dell'array di struct tutti i programmi presenti nella smart tv
		fread(&prog_tv, sizeof(programmi_smart_tv), 1, programmitv);
		if (!feof(programmitv)) {
			programmi_array[i] = prog_tv;
			i++;
		}
	}
	i = 0;
	quicksort(programmi_array, dimensione);
	printf("----------------------------------------------------Visualizzazione Programmi TV (ORDINE DI VALUTAZIONE)-------------------------------------------------------------------------------------");
	printf("\n%-50s %-50s %-50s %-20s %-20s\n", "Nome", "Categoria", "Tipologia", "Durata (minuti)", "Valutazione");
	for (i = 0; i < dimensione; i++) {
		printf("\n %-50s %-50s %-50s %-20d %-20d\n", programmi_array[i].nome, programmi_array[i].categoria, programmi_array[i].tipo, programmi_array[i].durata, programmi_array[i].valutazione);
	}
}

void menu_iniziale(FILE *programmitv, FILE *utente, FILE *catutente, FILE *tipiutente){
	char risposta;
	while(risposta != '6'){
		printf("+--------------------------------------------+\n");
		printf("|                     SMART TV               |\n");
		printf("+--------------------------------------------+\n");
		printf("|  1 - Menu Utente                           |\n");
		printf("|  2 - Menu Programmi                        |\n");
		printf("|  3 - Ricerca Programmi TV                  |\n");
		printf("|  4 - Programmi suggeriti da Smart TV       |\n");
		printf("|  5 - Programmi tv in ordine di valutazione |\n");
		printf("|  6 - Esci                                  |\n");
		printf("+--------------------------------------------+\n");
		printf("\nInserire il codice numerico della voce del menu scelta: ");
		scanf(" %c", &risposta);
		switch(risposta){
		case '1':
			menu_utente(utente, catutente, tipiutente);
			break;
		case '2':
			menu_programmi(programmitv);
			break;
		case '3':
			ricerca_programmi_tv(programmitv);
			break;
		case '4':
			suggerimento_programmi_tv(programmitv, catutente, tipiutente);
			break;
		case '5':
			ordinamento_programmi_tv(programmitv);
			break;
		case '6':
			printf("\nPROGRAMMA TERMINATO");
			break;
		default:
			printf("\nCodice inserito errato!");
			menu_iniziale(programmitv, utente, catutente,tipiutente);
			break;
		}
	}
}

void menu_utente(FILE *utente, FILE *catutente, FILE *tipiutente){
	char risposta;
	while(risposta != '4'){
		printf("+--------------------------------------------+\n");
		printf("|                SMART TV                    |\n");
		printf("+--------------------------------------------+\n");
		printf("|  1 - Crea profilo utente                   |\n");
		printf("|  2 - Modifica profilo utente               |\n");
		printf("|  3 - Visualizza profilo utente             |\n");
		printf("|  4 - Esci                                  |\n");
		printf("|                                            |\n");
		printf("|                                            |\n");
		printf("+--------------------------------------------+\n");
		printf("\nInserire il codice numerico della voce del menu scelta: ");
		scanf(" %c", &risposta);
		switch(risposta){
		case '1':
			inserimento_utente(utente, catutente, tipiutente);
			break;
		case '2':
			modifica_utente(utente, catutente, tipiutente);
			break;
		case '3':
			leggi_utente(utente, catutente, tipiutente);
			break;
		case '4':
			break;
		default:
			printf("\nCodice inserito errato!");
			break;
		}
	}
}

void menu_programmi(FILE *programmitv){
	char risposta;
	while(risposta != '5'){
		printf("+--------------------------------------------+\n");
		printf("|                SMART TV                    |\n");
		printf("+--------------------------------------------+\n");
		printf("|  1 - Inserimento programmi tv              |\n");
		printf("|  2 - Modifica programmi tv                 |\n");
		printf("|  3 - Cancella programmi tv                 |\n");
		printf("|  4 - Visualizza tutti i programmi tv       |\n");
		printf("|  5 - Esci                                  |\n");
		printf("|                                            |\n");
		printf("+--------------------------------------------+\n");
		printf("\nInserire il codice numerico della voce del menu scelta: ");
		scanf(" %c", &risposta);
		switch(risposta){
		case '1':
			inserimento_programmi_tv(programmitv);
			break;
		case '2':
			modifica_programmi_tv(programmitv);
			break;
		case '3':
			cancella_programmi_tv(programmitv);
			break;
		case '4':
			leggi_programmi_tv(programmitv);
			break;
		case '5':
			break;
		default:
			printf("\nCodice inserito errato!");
			break;
		}
	}
}
