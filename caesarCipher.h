//
// Created by pawel on 21.04.2026.
//

#ifndef PPC_CAESARCIPHER_H
#define PPC_CAESARCIPHER_H

/**
 * Classical cesar cypher encryption implementation.
 *
 * Warning! Works only with english alphabet.
 *
 * @param pathIn path to input file
 * @param pathOut path to encrypted output file
 * @param key shift number
 */
int cesarCypherEncrypt(char *pathIn, char *pathOut, int key);

/**
 * Classical cesar cypher decryption implementation.
 *
 * Warning! Works only with english alphabet.
 *
 * @param pathIn path to encrypted input file
 * @param pathOut path to decrypted output file
 * @param key shift number
 */
int cesarCypherDecrypt(char *pathIn, char *pathOut, int key);

/**
 * Counts occurances of each character and tries to decipher encoded data based on occurance dictionary.
 *
 * @param pathIn
 * @param pathOut
 * @param dictionary string of 26 english alphabet sorted by frequency of langage. Example for english "etaoinsrhdlucmfywgpbvkxqjz"
 * @return
 */
int analyzeFrequency(char *pathIn, char *pathOut, const char dictionary[26]);

#endif //PPC_CAESARCIPHER_H