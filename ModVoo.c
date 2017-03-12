#include "HeaderVoo.h"
#include <ctype.h>

int BuscarVoo(FILE * arq, char cod[]) {
	int cont = -1, status;
	TVoo v;

	fseek(arq, 0, 0);
	while (1) {
		status = fread(&v, sizeof(TVoo), 1, arq);
		if (status != 1) {
			if (!feof(arq))
				return -2;
			else
				return -1;
		}
		else {
			cont++;
			if (v.status == 1 && strcmp(v.codVoo, cod) == 0)
				return cont;
		}
	}

}

int ValidaCodVoo(char cod[]) {
	int i;

	for (i = 0; i < 3; i++) {
		if (isalpha(cod[i]) == 0) {
			return 0;
		}
	}

	for (i = 3; i < 7; i++) {
		if (isdigit(cod[i]) == 0) {
			return 0;
		}
	}

	return 1;
}

int ValidaData(char data[]) {
	int i;

	for (i = 0; i < 2; i++) {
		if (isdigit(data[i]) == 0) {
			return 0;
		}
	}

	if (data[i] != '/') {
		return 0;
	}

	for (i = 3; i < 5; i++) {
		if (isdigit(data[i]) == 0) {
			return 0;
		}
	}

	if (data[i] != '/') {
		return 0;
	}

	if (data[6] != '2')
		return 0;
	if (data[7] != '0')
		return 0;
	if (data[8] != '1')
		return 0;
	if (data[9] != '7')
		return 0;

	return 1;
}

int ValidaHora(char hora[]) {
	int i;

	for (i = 0; i < 2; i++) {
		if (isdigit(hora[i]) == 0) {
			return 0;
		}
	}

	if (hora[i] != ':') {
		return 0;
	}

	for (i = 3; i < 5; i++) {
		if (isdigit(hora[i]) == 0) {
			return 0;
		}
	}

	return 1;
}