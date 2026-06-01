//
// Created by pawel on 22.04.2026.
//

#include "md5.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint32_t RotateLeft(uint32_t x, uint32_t n) {
	return (x << n) | (x >> (32 - n));
}

uint32_t F(uint32_t x, uint32_t y, uint32_t z) {
	return (x & y) | (~x & z);
}

uint32_t G(uint32_t x, uint32_t y, uint32_t z) {
	return (x & z) | (y & ~z);
}

uint32_t H(uint32_t x, uint32_t y, uint32_t z) {
	return x ^ y ^ z;
}

uint32_t I(uint32_t x, uint32_t y, uint32_t z) {
	return y ^ (x | ~z);
}

char * md5(char *message) {
	size_t length = strlen(message);
	uint64_t bitLength = length * 8;

	size_t totalLength = (length + 9 + 63) / 64 * 64;

	size_t elements = totalLength / sizeof(uint32_t);

	uint32_t *buffer = calloc(elements, sizeof(uint32_t));
	if (!buffer) {
		return NULL;
	}

	memcpy(buffer, message, length);

	((uint8_t*)buffer)[length] = 0x80;
	bitLength = length * 8;

	memcpy((uint8_t*)buffer + elements * sizeof(uint32_t) - 8, &bitLength,8);
	uint32_t A0 = 0x67452301;
	uint32_t B0 = 0xefcdab89;
	uint32_t C0 = 0x98badcfe;
	uint32_t D0 = 0x10325476;

	uint32_t K[] = {
		0xd76aa478,
		0xe8c7b756,
		0x242070db,
		0xc1bdceee,
		0xf57c0faf,
		0x4787c62a,
		0xa8304613,
		0xfd469501,
		0x698098d8,
		0x8b44f7af,
		0xffff5bb1,
		0x895cd7be,
		0x6b901122,
		0xfd987193,
		0xa679438e,
		0x49b40821,
		0xf61e2562,
		0xc040b340,
		0x265e5a51,
		0xe9b6c7aa,
		0xd62f105d,
		 0x2441453,
		0xd8a1e681,
		0xe7d3fbc8,
		0x21e1cde6,
		0xc33707d6,
		0xf4d50d87,
		0x455a14ed,
		0xa9e3e905,
		0xfcefa3f8,
		0x676f02d9,
		0x8d2a4c8a,
		0xfffa3942,
		0x8771f681,
		0x6d9d6122,
		0xfde5380c,
		0xa4beea44,
		0x4bdecfa9,
		0xf6bb4b60,
		0xbebfbc70,
		0x289b7ec6,
		0xeaa127fa,
		0xd4ef3085,
		 0x4881d05,
		0xd9d4d039,
		0xe6db99e5,
		0x1fa27cf8,
		0xc4ac5665,
		0xf4292244,
		0x432aff97,
		0xab9423a7,
		0xfc93a039,
		0x655b59c3,
		0x8f0ccc92,
		0xffeff47d,
		0x85845dd1,
		0x6fa87e4f,
		0xfe2ce6e0,
		0xa3014314,
		0x4e0811a1,
		0xf7537e82,
		0xbd3af235,
		0x2ad7d2bb,
		0xeb86d391
	};

	uint32_t S[] = {
		7,
		12,
		17,
		22,
		7,
		12,
		17,
		22,
		7,
		12,
		17,
		22,
		7,
		12,
		17,
		22,
		5,
		9,
		14,
		20,
		5,
		9,
		14,
		20,
		5,
		9,
		14,
		20,
		5,
		9,
		14,
		20,
		4,
		11,
		16,
		23,
		4,
		11,
		16,
		23,
		4,
		11,
		16,
		23,
		4,
		11,
		16,
		23,
		6,
		10,
		15,
		21,
		6,
		10,
		15,
		21,
		6,
		10,
		15,
		21,
		 6,
		10,
		15,
		21
	};

	for (size_t offset = 0; offset < elements; offset += 16) {
		uint32_t A = A0;
		uint32_t B = B0;
		uint32_t C = C0;
		uint32_t D = D0;

		uint32_t *M = buffer + offset;

		for (int i = 0; i < 64; i++) {
			uint32_t F_value, g;

			if (i < 16) {
				F_value = F(B, C, D);
				g = i;
			} else if (i < 32) {
				F_value = G(B, C, D);
				g = (5 * i + 1) % 16;
			} else if (i < 48) {
				F_value = H(B, C, D);
				g = (3 * i + 5) % 16;
			} else {
				F_value = I(B, C, D);
				g = (7 * i) % 16;
			}

			uint32_t temp = D;

			uint32_t sum = A + F_value + K[i] + M[g];

			D = C;
			C = B;
			B = B + RotateLeft(sum, S[i]);
			A = temp;
		}

		A0 += A;
		B0 += B;
		C0 += C;
		D0 += D;
	}

	char *result = malloc(33);
	if (!result) {
		free(buffer);
		return NULL;
	}

	uint32_t stages[4] = {A0, B0, C0, D0};
	int p = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			sprintf(&result[p], "%02x", (stages[i] >> (j * 8)) & 0xFF);
			p += 2;
		}
	}
	result[32] = '\0';

	free(buffer);
	return result;
}
