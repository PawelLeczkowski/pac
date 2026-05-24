//
// Created by pawel on 21.04.2026.
//

#ifndef PPC_CAESARCIPHER_H
#define PPC_CAESARCIPHER_H

/**
 * todo docs
 * Classical cesar cypher encryption implementation.
 *
 * Warning! Works only with english alphabet.
 *
 * @param pathIn
 * @param pathOut
 * @param key
 */
int cesarCypherEncrypt(char *pathIn, char *pathOut, int key);

/**
 * todo docs
 * Classical cesar cypher decryption implementation.
 *
 * Warning! Works only with english alphabet.
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