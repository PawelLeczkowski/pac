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
	return  (x & y) | (~x & z);
}

uint32_t G(uint32_t x, uint32_t y, uint32_t z) {
	return  (x & z) | (y & ~z);
}

uint32_t H(uint32_t x, uint32_t y, uint32_t z) {
	return  x ^ y ^ z;
}

uint32_t I(uint32_t x, uint32_t y, uint32_t z) {
	return  y ^ (x | ~z);
}

uint64_t toBigEndian(uint64_t value)
{
	return (value & 0x00000000000000FFULL) << 56 |
		   (value & 0x000000000000FF00ULL) << 40 |
		   (value & 0x0000000000FF0000ULL) << 24 |
		   (value & 0x00000000FF000000ULL) << 8  |
		   (value & 0x000000FF00000000ULL) >> 8  |
		   (value & 0x0000FF0000000000ULL) >> 24 |
		   (value & 0x00FF000000000000ULL) >> 40 |
		   (value & 0xFF00000000000000ULL) >> 56;
}

char * md5(char *message) {
	// https://datatracker.ietf.org/doc/html/rfc1321?__cf_chl_tk=L50_UpHKfr3jlIFNICbpDp6joIWTte039XXpj9GiGxA-1779644585-1.0.1.1-P1XLy9BecVx1Y9E4DPPy.xjbM5_lpuNoDjR65df65DY
	size_t length = strlen(message);
	size_t bits = length * 8;
	size_t newLength = bits;

	if (length == 0) {
		newLength = 512;
	}

	while (newLength % 512 != 0) {
		newLength++;
	}

	size_t elements = newLength / 32;

	uint32_t *buffer = calloc(elements, sizeof(uint32_t));
	if (!buffer) {
		return NULL;
	}

	memcpy(buffer, message, length);

	((uint8_t*)buffer)[length] = 0x80;
	uint64_t bitLength = length * 8;

	memcpy(
		(uint8_t*)buffer + (elements * sizeof(uint32_t)) - 8,
		&bitLength,
		8
	);
	uint32_t A0 = 0x67452301;
	uint32_t B0 = 0xefcdab89;
	uint32_t C0 = 0x98badcfe;
	uint32_t D0 = 0x10325476;

	uint32_t K[] = {
		0xD76AA478,
		0xE8C7B756,
		0x242070DB,
		0xC1BDCEEE,
		0x0F57C0FA,
		0x4787C62A,
		0xA8304613,
		0xFD469501,
		0x698098D8,
		0x8B44F7AF,
		0xFFFF5BB1,
		0x895CD7BE,
		0x6B901122,
		0xFD987193,
		0xA679438E,
		0x49B40821,
		0xF61E2562,
		0xC040B340,
		0x265E5A51,
		0xE9B6C7AA,
		0xD62F105D,
		0x02441453,
		0xD8A1E681,
		0xE7D3FBC8,
		0x21E1CDE6,
		0xC33707D6,
		0xF4D50D87,
		0x455A14ED,
		0xA9E3E905,
		0xFCEFA3F8,
		0x676F02D9,
		0x8D2A4C8A,
		0xFFFA3942,
		0x8771F681,
		0x6D9D6122,
		0xFDE5380C,
		0xA4BEEA44,
		0x4BDECFA9,
		0xF6BB4B60,
		0xBEBFBC70,
		0x289B7EC6,
		0xEAA127FA,
		0xD4EF3085,
		0x04881D05,
		0xD9D4D039,
		0xE6DB99E5,
		0x1FA27CF8,
		0xC4AC5665,
		0xF4292244,
		0x432AFF97,
		0xAB9423A7,
		0xFC93A039,
		0x655B59C3,
		0x8F0CCC92,
		0xFFEFF47D,
		0x85845DD1,
		0x6FA87E4F,
		0xFE2CE6E0,
		0xA3014314,
		0x4E0811A1,
		0xF7537E82,
		0xBD3AF235,
		0x2AD7D2BB,
		0xEB86D391
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

	// todo debug and fix
	for (size_t offset = 0; offset < elements; offset += 16) {
		uint32_t A = A0;
		uint32_t B = B0;
		uint32_t C = C0;
		uint32_t D = D0;

		uint32_t *M = buffer + offset;

		for (int i = 0; i < 16; i++) {
			printf("M[%d] = %08x\n", i, M[i]);
		}

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

			printf(
				"A=%08x B=%08x C=%08x D=%08x F=%08x M=%08x\n",
				A,B,C,D,F_value,M[g]
			);

			uint32_t temp = D;

			uint32_t sum = A + F_value + K[i] + M[g];

			D = C;
			C = B;
			B = B + RotateLeft(sum, S[i]);
			A = temp;

			printf("%08x %08x %08x %08x\n", A, B, C, D);
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
