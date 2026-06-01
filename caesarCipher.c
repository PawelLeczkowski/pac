//
// Created by pawel on 21.04.2026.
//

#include "caesarCipher.h"

#include <stdlib.h>
#include <stdio.h>

#include "../pel/integer.h"

char rotateRight(int c, int n, int alpabetSize) {
	c -= 'a';
	c = (c + n) % alpabetSize;
	c += 'a';
	return (char)c;
}

char rotateLeft(int c, int n, int alpabetSize) {
	char a;
	if (islower(c)) {
		a = 'a';
	}
	else {
		a = 'A';
	}

	c -= a;
	c -= n;
	if (c < 0) {
		c += alpabetSize;
	}
	c += a;
	return (char)c;
}

FILE* openFileForRead(char *path) {
	FILE* f;
	f = fopen(path, "rb");
	return f;
}

FILE* openFileForWrite(char *path) {
	FILE* f;
	f = fopen(path, "wb");
	return f;
}

int cesarCypherEncrypt(char *pathIn, char *pathOut, int key) {
	if (pathIn == NULL) {
		return -1;
	}

	if (pathOut == NULL) {
		return -2;
	}

	FILE* fIn = openFileForRead(pathIn);
	if (fIn == NULL) {
		return -3;
	}

	FILE* fOut = openFileForWrite(pathOut);
	if (fOut == NULL) {
		return -4;
	}

	char c = 0;
	while ((c = (char)fgetc(fIn)) != EOF) {
		if (isalpha(c)) {
			c = rotateRight(c, key, 26);
		}

		fputc(c, fOut);
	}

	fclose(fIn);
	fclose(fOut);

	return 0;
}

int cesarCypherDecrypt(char *pathIn, char *pathOut, int key) {
	if (pathIn == NULL) {
		return -1;
	}

	if (pathOut == NULL) {
		return -2;
	}

	FILE* fIn = openFileForRead(pathIn);
	if (fIn == NULL) {
		return -3;
	}

	FILE* fOut = openFileForWrite(pathOut);
	if (fOut == NULL) {
		return -4;
	}

	char c = 0;
	while ((c = (char)fgetc(fIn)) != EOF) {
		if (isalpha(c)) {
			c = rotateLeft(c, key, 26);
		}

		fputc(c, fOut);
	}

	fclose(fIn);
	fclose(fOut);

	return 0;
}

int bestIndex(const long long* occurances) {
	int index = 0;
	for (int i = 0; i < 26; i++) {
		if (occurances[i] > occurances[index]) {
			index = i;
		}
	}
	return index;
}

char* setLetters(long long* occurances, const char best[26]) {
	char* letters = malloc(26 * sizeof(char));

	if (letters == NULL) {
		return NULL;
	}

	for (int i = 0; i < 26; i++) {
		const int index = bestIndex(occurances);
		letters[index] = best[i];
		occurances[index] = -1;
	}

	return letters;
}

void putLetters(FILE* fIn, FILE* fOut, const char* letters) {
	char c = 0;
	while ((c = (char)fgetc(fIn)) != EOF) {

		if (isalpha(c)) {
			c = letters[c - 'a'];
		}

		fputc(c, fOut);
	}

	fclose(fIn);
	fclose(fOut);
}

int analyzeFrequency(char *pathIn, char *pathOut, const char dictionary[26]) {
	if (pathIn == NULL) {
		return -1;
	}
	FILE* f = openFileForRead(pathIn);

	long long occurances[26] = {0};

	char c = 0;
	while ((c = (char)fgetc(f)) != EOF) {
		if (isalpha(c)) {
			c = (char)tolower(c);
			occurances[c - 'a']++;
		}
	}

	char* letters = setLetters(occurances, dictionary);
	if (letters == NULL) {
		return -2;
	}

	f = openFileForRead(pathIn);

	FILE* fo = openFileForWrite(pathOut);
	if (fo == NULL) {
		free(letters);
		return -3;
	}

	putLetters(f, fo, letters);

	free(letters);

	return 0;
}
