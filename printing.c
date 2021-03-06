#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>

#include "utils.h"
#include "tree_operations.h"

/****************************MAIN*MENU*****************************************/
/* Return number of menu selection. */

int mainMenu() {
	int selection = -1; /* -1 represent invalid selection. Which will be changed only when user input is integer. */
	char temp[CHAR_MAX];

	printf ("Valitse toiminto valikosta:\n"
			"1) Lisää luku(ja) puuhun\n"
			"2) Tulosta puu\n"
			"3) Etsi luku\n"
			"4) Tyhjennä puu\n"
            "5) Säädä asetuksia\n"
			"0) Lopeta\n"
			"Valintasi: ");

	fgets(temp, sizeof(temp), stdin);

	if (strncmp("0", temp, 1) == 0) {
		/* Check if string first character is 0 and then assume wanted number is 0 .*/
		selection = 0;

	} else if (atoi(temp)) { /* When input is integer -> selection is set to be this integer. */
		selection = atoi(temp);
	}

	printf("\n");
	return selection;
}


/****************************ADDING*MENU***************************************/
/* Return adding type selection. */

int addMenu() {
	int sel = 1;
	char temp[CHAR_MAX];

	printf ("Valitse lisäys metodi:\n"
			"1) Lisää luvut tiedostosta\n"
			"0) Lisää vapaa valintaisia lukuja\n"
			"Valintasi: ");

	fgets(temp, sizeof(temp), stdin);
	/*sel = (atoi(temp) == 1) ? 1 : 0;*/
	sel = (atoi(temp));
	return sel;
}

/****************************OPTIONS*PRINT*************************************/
/* Prints options and each option's value. 1 =´means ON and 0 menas OFF.*/

void printOptions(tdOptions *pOpt) {
	printf("Asetukset ovat:\n"
	"Tiedostoon tulostus:\t%d\n"
	"Konsoliin tulostus:\t%d\n"
	"Rakentumisen tulostus:\t%d\n"
	"Pystyyn tulostus:\t%d\n\n", pOpt->bFile, pOpt->bConsol, pOpt->bBuilding, pOpt->bVertical);
	/* OFF version of vertical is horizontal printing. */
}

/****************************OPTIONS*MENU**************************************/
/* Return options selections. */

void optionsMenu(tdOptionsPointer *pOpt) {
	char temp[CHAR_MAX];
/*	tdOptions *temOpt;

	if ((tempOpt = (tdOptions*)malloc(sizeof(tdOptions))) == NULL) {
		perror("Muistinvaraus epäonnistui );\n");
		exit(1);
	}*/

    printf("Vastausformaatti: [Y/N] tai [K/E] /tai [1/0]\n\n");
	/* Code checks 1, Y, y, K and k. If one of them is selected value == 1.
	Every other situations makes selection to be 0 which means OFF. */

    printf("Tulostetaanko tiedostoon? ");
    fgets(temp, sizeof(temp), stdin);

    if (temp[0] == '1' || temp[0] == 'Y' || temp[0] == 'y' ||
    temp[0] == 'K' || temp[0] == 'k') {

        (*pOpt)->bFile = 1;

	} else {
		(*pOpt)->bFile = 0;
	}

    printf("Tulostetaanko konsoliin? ");
	fgets(temp, sizeof(temp), stdin);

    if (temp[0] == '1' || temp[0] == 'Y' || temp[0] == 'y' ||
    temp[0] == 'K' || temp[0] == 'k') {

		(*pOpt)->bConsol = 1;

    } else {
		(*pOpt)->bConsol = 0;
	}

    printf("Tulostetaanko rakentuminen? ");
	fgets(temp, sizeof(temp), stdin);

    if (temp[0] == '1' || temp[0] == 'Y' || temp[0] == 'y' ||
    temp[0] == 'K' || temp[0] == 'k') {

		(*pOpt)->bBuilding = 1;

	} else {
		(*pOpt)->bBuilding = 0;
	}

    printf("Tulostetaanko pystyy (K) vai vaakaan (E)? ");
	fgets(temp, sizeof(temp), stdin);

    if (temp[0] == '1' || temp[0] == 'Y' || temp[0] == 'y' ||
    temp[0] == 'K' || temp[0] == 'k') {

		(*pOpt)->bVertical = 1;

	} else {
		(*pOpt)->bVertical = 0;
	}

	printOptions(*pOpt); /* Lastly prints set options. */
}

/****************************PRINTING*HORIZONTAL*******************************/
/* Print nodes of binary tree postorder, right, node itself and left. */

void printTree(tdTree *pRoot, FILE* pToFile, tdOptions *pOpt, int i) {
	i++;
	if (pRoot != NULL) {
		printTree(pRoot->pRight, pToFile, pOpt, i);

        if (pOpt->bConsol) {
			/*Prints number and then to superscipt its balance indicator using UTF-8 escape sequences. */
    		printf("%*d", i*6, pRoot->iNum);
			if (pRoot->iBalance == -1) {
				printf("%s\n", "\xe2\x82\x8b\xc2\xb9"); /*printf("%c%c%c%c%c\t\t", 0342, 0201, 0273, 0302, 0271);*/

			} else if (pRoot->iBalance == 1) {
				printf("%s\n", "\xc2\xb9"); /*printf("%c%c\t\t", 0302, 0271);*/

			} else {
				printf("%s\n", "\xe2\x81\xb0"); /*printf("%c%c%c\t\t", 0342, 0201, 0260);*/
			}
        }

        if (pOpt->bFile) {
            fprintf(pToFile, "%*d", i*6, pRoot->iNum);
			if (pRoot->iBalance == -1) {
				fprintf(pToFile, "%s\n", "\xe2\x82\x8b\xc2\xb9");

			} else if (pRoot->iBalance == 1) {
				fprintf(pToFile, "%s\n", "\xc2\xb9");

			} else {
				fprintf(pToFile, "%s\n", "\xe2\x81\xb0");
			}
        }

		printTree(pRoot->pLeft, pToFile, pOpt, i);

	} /*else {
		if (pOpt->bConsol) {
			printf("%*s\n", i*6 + 1, "NULL");
		}

		if (pOpt->bFile) {
			fprintf(pToFile, "%*s\n", i*6 + 1, "NULL");
		}
	} */
}


/****************************PRINT*TABS****************************************/
/* Prints given amount of tabulators. */
void printTab(int tab, FILE *pToFile, tdOptions *pOpt) {
	int i;
	if (pOpt->bFile) {
		for (i = 0; i < tab/2; i++) {
			fprintf(pToFile, "\t");
		}
	}

	if (pOpt->bConsol) {
		for(i = 0; i < tab/2; i++) {
			printf("\t");
		}
	}
}

/****************************PRINT*LINES***************************************/
/* Prints lines between layers of vertical printed tree using UTF-8 escape sequences.
Used lines are box drawing charactes. ┏ ━ ┻ ━ ┓ */

void printLines(FILE *pToFile, tdOptions *pOpt, int *height, int layer, int lineCount) {
	int i, k, j;
if (layer != *height-1) {
	if (pOpt->bFile) {
		for(i = 0; i < (lineCount-1)/2; i++) {
			fprintf(pToFile, "\t");
		}

		if(layer < *height) {

			for(j = 0; j < pow(2,layer); j++) {
				fprintf(pToFile, "  %s", "\xe2\x94\x8f");	/* ┏ */				/*"  %c%c%c", 0342, 0224, 0217*/

				for(k = 0; k <= 4 * lineCount + 1; k++) {						/*"%c%c%c", 0342, 0224, 0201*/
					fprintf(pToFile, "%s", "\xe2\x94\x81");	/* ━ */
				}

				fprintf(pToFile, "%s", "\xe2\x94\xbb"); /* ┻ */					/*"%c%c%c", 0342, 0224, 0273*/

				for(k = 0; k <= 4 * lineCount + 1; k++) {
					fprintf(pToFile, "%s", "\xe2\x94\x81"); /* ━ */
				}

				fprintf(pToFile, "%s", "\xe2\x94\x93");	/* ┓ */					/*"%c%c%c", 0342, 0224, 0223*/

				for(i = 0; i <= lineCount; i++) {
					fprintf(pToFile, "\t");
				}
			}
		}
	}

	if (pOpt->bConsol) {
		for(i = 0; i < (lineCount-1)/2; i++) {
			printf("\t");
		}

		if(layer + 1 < *height) {

			for(j = 0; j < pow(2,layer); j++) {
				printf("  %s", "\xe2\x94\x8f");	/* ┏ */							/*"  %c%c%c", 0342, 0224, 0217*/

				for(k = 0; k <= 4 * lineCount + 1; k++) {						/*"%c%c%c", 0342, 0224, 0201*/
					printf("%s", "\xe2\x94\x81");	/* ━ */
				}

				printf("%s", "\xe2\x94\xbb"); /* ┻ */							/*"%c%c%c", 0342, 0224, 0273*/

				for(k = 0; k <= 4 * lineCount + 1; k++) {						/*"%c%c%c", 0342, 0224, 0201*/
					printf("%s", "\xe2\x94\x81");	/* ━ */
				}

				printf("%s", "\xe2\x94\x93");	/* ┓ */							/*"%c%c%c", 0342, 0224, 0223*/

				for(i = 0; i <= lineCount; i++) {
					printf("\t");
				}
			}
		}
	}
}
}

/****************************PRINTING*LAYER*******************************/
/* Print one layer of binary tree at the time. Starts at layer 0, the root. */

void printLayer(tdTree *pParent, FILE *pToFile, tdOptions *pOpt, int *height, int layer, int current, int tabCount) {
	if (pParent && current == layer) { /* When are in right layer and node exist. */
		printTab(tabCount, pToFile, pOpt);
/*Prints number and then to superscipt its balance indicator using UTF-8 escape sequences. */

		if (pOpt->bFile) {
    		fprintf(pToFile, "%d", pParent->iNum);

			if (pParent->iBalance == -1) {
				fprintf(pToFile, "%s\t\t", "\xe2\x82\x8b\xc2\xb9");

			} else if (pParent->iBalance == 1) {
				fprintf(pToFile, "%s\t\t", "\xc2\xb9");

			} else {
				fprintf(pToFile, "%s\t\t", "\xe2\x81\xb0");
			}
		}

		if (pOpt->bConsol) {

			printf("%d", pParent->iNum);

			if (pParent->iBalance == -1) {
				printf("%s\t\t", "\xe2\x82\x8b\xc2\xb9"); /*printf("%c%c%c%c%c\t\t", 0342, 0201, 0273, 0302, 0271);*/

			} else if (pParent->iBalance == 1) {
				printf("%s\t\t", "\xc2\xb9"); /*printf("%c%c\t\t", 0302, 0271);*/

			} else {
				printf("%s\t\t", "\xe2\x81\xb0"); /*printf("%c%c%c\t\t", 0342, 0201, 0260);*/
			}
		}
		printTab(tabCount, pToFile, pOpt);

	} else if (pParent && current < layer) { /* When in too low layer and node exist. */

        printLayer(pParent->pLeft, pToFile, pOpt, height, layer, current + 1, tabCount);
        printLayer(pParent->pRight, pToFile, pOpt, height, layer, current + 1, tabCount);

	} else if (!pParent && current == layer) { /* When in right layer but node don't exist. */
		printTab(tabCount, pToFile, pOpt);

		if (pOpt->bFile) {
			fprintf(pToFile, "%s\t\t", "NULL");
		}

		if (pOpt->bConsol) {
			printf("%s\t\t", "NULL");
		}

		printTab(tabCount, pToFile, pOpt);

	} else if (!pParent && current < layer) { /* When are in too low layer and node don't exist. */
/*fprintf(pToFile, "l:%d c:%d", layer, current);*/
		printTab((int)pow(2.0, (double)(*height-(current-1))), pToFile, pOpt);

		/*if (pOpt->bFile) {
			fprintf(pToFile, "\t.\t.\t.\t");

		}

		if (pOpt->bConsol) {

			printf("\t\t\t\t");
		}*/
	}
}

/****************************PRINT*CONTROLLER**********************************/
/* Controls what is printed and where depending on options. */
void printController(tdTree *pRoot, FILE* pToFile, tdOptions *pOpt, int *height, int i) {

    if (pOpt->bVertical) { /* Print vertical if it's set ON. */
		int layer, help;

		for (layer = 0; layer < *height; layer++) { /* Goes trought tree one layer at the time. */
			help = (int)pow(2.0, (double)((*height)-layer)) - 1;

        	printLayer(pRoot, pToFile, pOpt, height, layer, i, help);

			if (pOpt->bConsol) {
				printf("\n");
			}

			if (pOpt->bFile) {
				fprintf(pToFile, "\n");
			}

			printLines(pToFile, pOpt, height, layer, help/2);

			if (pOpt->bConsol) {
				printf("\n\n");
			}
			if (pOpt->bFile) {
				fprintf(pToFile, "\n\n");
			}
		}
    } else { /* If not vetical print then horizontal print. */
        printTree(pRoot, pToFile, pOpt, i);
        if (pOpt->bConsol) { /* underline lines are used to make trees be separetd from each other. */
            printf("_______________________________________________________\n");
        }
        if (pOpt->bFile) {
            fprintf(pToFile, "_______________________________________________________\n");
        }
    }
}

/* EOF */
