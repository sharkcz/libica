/* This program is released under the Common Public License V1.0
 *
 * You should have received a copy of Common Public License V1.0 along with
 * with this program.
 */

/* (C) COPYRIGHT International Business Machines Corp. 2011          */
#include <fcntl.h>
#include <sys/errno.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include "ica_api.h"
#include "testcase.h"

#define NR_TESTS 12
#define AES_BLOCK_SIZE 16

/* GCM data - 1*/
unsigned char NIST_KEY_GCM_E1[] = {
	0xfe, 0xff, 0xe9, 0x92, 0x86, 0x65, 0x73, 0x1c,
	0x6d, 0x6a, 0x8f, 0x94, 0x67, 0x30, 0x83, 0x08,
};

unsigned char NIST_TEST_DATA_GCM_E1[] = {
	0xd9, 0x31, 0x32, 0x25, 0xf8, 0x84, 0x06, 0xe5,
	0xa5, 0x59, 0x09, 0xc5, 0xaf, 0xf5, 0x26, 0x9a,
	0x86, 0xa7, 0xa9, 0x53, 0x15, 0x34, 0xf7, 0xda,
	0x2e, 0x4c, 0x30, 0x3d, 0x8a, 0x31, 0x8a, 0x72,
	0x1c, 0x3c, 0x0c, 0x95, 0x95, 0x68, 0x09, 0x53,
	0x2f, 0xcf, 0x0e, 0x24, 0x49, 0xa6, 0xb5, 0x25,
	0xb1, 0x6a, 0xed, 0xf5, 0xaa, 0x0d, 0xe6, 0x57,
	0xba, 0x63, 0x7b, 0x39, 0x1a, 0xaf, 0xd2, 0x55,
};

unsigned char NIST_AAD_GCM_E1[] = {
};

unsigned char NIST_IV_GCM_E1[] = {
	0xca, 0xfe, 0xba, 0xbe, 0xfa, 0xce, 0xdb, 0xad,
	0xde, 0xca, 0xf8, 0x88,
};

unsigned char NIST_TAG_GCM_E1[] = {
	0x4d, 0x5c, 0x2a, 0xf3, 0x27, 0xcd, 0x64, 0xa6,
	0x2c, 0xf3, 0x5a, 0xbd, 0x2b, 0xa6, 0xfa, 0xb4,
};

unsigned char NIST_TEST_RESULT_GCM_E1[] = {
	0x42, 0x83, 0x1e, 0xc2, 0x21, 0x77, 0x74, 0x24,
	0x4b, 0x72, 0x21, 0xb7, 0x84, 0xd0, 0xd4, 0x9c,
	0xe3, 0xaa, 0x21, 0x2f, 0x2c, 0x02, 0xa4, 0xe0,
	0x35, 0xc1, 0x7e, 0x23, 0x29, 0xac, 0xa1, 0x2e,
	0x21, 0xd5, 0x14, 0xb2, 0x54, 0x66, 0x93, 0x1c,
	0x7d, 0x8f, 0x6a, 0x5a, 0xac, 0x84, 0xaa, 0x05,
	0x1b, 0xa3, 0x0b, 0x39, 0x6a, 0x0a, 0xac, 0x97,
	0x3d, 0x58, 0xe0, 0x91, 0x47, 0x3f, 0x59, 0x85,
};

unsigned char NIST_CHUNKS_GCM_E1[] = { 16, 16, 16, 16 };

/* GCM data - 2*/
unsigned char NIST_KEY_GCM_E2[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

unsigned char NIST_TEST_DATA_GCM_E2[] = {
};

unsigned char NIST_AAD_GCM_E2[] = {
};

unsigned char NIST_IV_GCM_E2[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
};

unsigned char NIST_TAG_GCM_E2[] = {
	0x58, 0xe2, 0xfc, 0xce, 0xfa, 0x7e, 0x30, 0x61,
	0x36, 0x7f, 0x1d, 0x57, 0xa4, 0xe7, 0x45, 0x5a
};

unsigned char NIST_TEST_RESULT_GCM_E2[] = {
};

unsigned char NIST_CHUNKS_GCM_E2[] = { };

/* GCM data - 3*/
unsigned char NIST_KEY_GCM_E3[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

unsigned char NIST_TEST_DATA_GCM_E3[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

unsigned char NIST_AAD_GCM_E3[] = {
};

unsigned char NIST_IV_GCM_E3[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
};

unsigned char NIST_TAG_GCM_E3[] = {
	0xab, 0x6e, 0x47, 0xd4, 0x2c, 0xec, 0x13, 0xbd,
	0xf5, 0x3a, 0x67, 0xb2, 0x12, 0x57, 0xbd, 0xdf,
};

unsigned char NIST_TEST_RESULT_GCM_E3[] = {
	0x03, 0x88, 0xda, 0xce, 0x60, 0xb6, 0xa3, 0x92,
	0xf3, 0x28, 0xc2, 0xb9, 0x71, 0xb2, 0xfe, 0x78,
};

unsigned char NIST_CHUNKS_GCM_E3[] = { 16 };

/* GCM data - 4*/
unsigned char NIST_KEY_GCM_E4[] = {
	0xfe, 0xff, 0xe9, 0x92, 0x86, 0x65, 0x73, 0x1c,
	0x6d, 0x6a, 0x8f, 0x94, 0x67, 0x30, 0x83, 0x08,
};

unsigned char NIST_TEST_DATA_GCM_E4[] = {
	0xd9, 0x31, 0x32, 0x25, 0xf8, 0x84, 0x06, 0xe5,
	0xa5, 0x59, 0x09, 0xc5, 0xaf, 0xf5, 0x26, 0x9a,
	0x86, 0xa7, 0xa9, 0x53, 0x15, 0x34, 0xf7, 0xda,
	0x2e, 0x4c, 0x30, 0x3d, 0x8a, 0x31, 0x8a, 0x72,
	0x1c, 0x3c, 0x0c, 0x95, 0x95, 0x68, 0x09, 0x53,
	0x2f, 0xcf, 0x0e, 0x24, 0x49, 0xa6, 0xb5, 0x25,
	0xb1, 0x6a, 0xed, 0xf5, 0xaa, 0x0d, 0xe6, 0x57,
	0xba, 0x63, 0x7b, 0x39,
};

unsigned char NIST_AAD_GCM_E4[] = {
	0xfe, 0xed, 0xfa, 0xce, 0xde, 0xad, 0xbe, 0xef,
	0xfe, 0xed, 0xfa, 0xce, 0xde, 0xad, 0xbe, 0xef,
	0xab, 0xad, 0xda, 0xd2,
};

unsigned char NIST_IV_GCM_E4[] = {
	0xca, 0xfe, 0xba, 0xbe, 0xfa, 0xce, 0xdb, 0xad,
	0xde, 0xca, 0xf8, 0x88,
};

unsigned char NIST_TAG_GCM_E4[] = {
	0x5b, 0xc9, 0x4f, 0xbc, 0x32, 0x21, 0xa5, 0xdb,
	0x94, 0xfa, 0xe9, 0x5a, 0xe7, 0x12, 0x1a, 0x47,
};

unsigned char NIST_TEST_RESULT_GCM_E4[] = {
	0x42, 0x83, 0x1e, 0xc2, 0x21, 0x77, 0x74, 0x24,
	0x4b, 0x72, 0x21, 0xb7, 0x84, 0xd0, 0xd4, 0x9c,
	0xe3, 0xaa, 0x21, 0x2f, 0x2c, 0x02, 0xa4, 0xe0,
	0x35, 0xc1, 0x7e, 0x23, 0x29, 0xac, 0xa1, 0x2e,
	0x21, 0xd5, 0x14, 0xb2, 0x54, 0x66, 0x93, 0x1c,
	0x7d, 0x8f, 0x6a, 0x5a, 0xac, 0x84, 0xaa, 0x05,
	0x1b, 0xa3, 0x0b, 0x39, 0x6a, 0x0a, 0xac, 0x97,
	0x3d, 0x58, 0xe0, 0x91,
};

unsigned char NIST_CHUNKS_GCM_E4[] = { 16, 16, 16, 12 };

/* GCM data - 5 - AES 192 - Test Case 7*/
unsigned char NIST_KEY_GCM_E5[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

unsigned char NIST_TEST_DATA_GCM_E5[] = {
};

unsigned char NIST_AAD_GCM_E5[] = {
};

unsigned char NIST_IV_GCM_E5[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
};

unsigned char NIST_TAG_GCM_E5[] = {
	0xcd, 0x33, 0xb2, 0x8a, 0xc7, 0x73, 0xf7, 0x4b,
	0xa0, 0x0e, 0xd1, 0xf3, 0x12, 0x57, 0x24, 0x35,
};

unsigned char NIST_TEST_RESULT_GCM_E5[] = {
};

unsigned char NIST_CHUNKS_GCM_E5[] = { };

/* GCM data - 6 - AES 192 - Test Case 8*/
unsigned char NIST_KEY_GCM_E6[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

unsigned char NIST_TEST_DATA_GCM_E6[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

unsigned char NIST_AAD_GCM_E6[] = {
};

unsigned char NIST_IV_GCM_E6[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
};

unsigned char NIST_TAG_GCM_E6[] = {
	0x2f, 0xf5, 0x8d, 0x80, 0x03, 0x39, 0x27, 0xab,
	0x8e, 0xf4, 0xd4, 0x58, 0x75, 0x14, 0xf0, 0xfb,
};

unsigned char NIST_TEST_RESULT_GCM_E6[] = {
	0x98, 0xe7, 0x24, 0x7c, 0x07, 0xf0, 0xfe, 0x41,
	0x1c, 0x26, 0x7e, 0x43, 0x84, 0xb0, 0xf6, 0x00,
};

unsigned char NIST_CHUNKS_GCM_E6[] = { 16 };

/* GCM data - 7 - AES 192 - Test Case 9*/
unsigned char NIST_KEY_GCM_E7[] = {
	0xfe, 0xff, 0xe9, 0x92, 0x86, 0x65, 0x73, 0x1c,
	0x6d, 0x6a, 0x8f, 0x94, 0x67, 0x30, 0x83, 0x08,
	0xfe, 0xff, 0xe9, 0x92, 0x86, 0x65, 0x73, 0x1c,
};

unsigned char NIST_TEST_DATA_GCM_E7[] = {
	0xd9, 0x31, 0x32, 0x25, 0xf8, 0x84, 0x06, 0xe5,
	0xa5, 0x59, 0x09, 0xc5, 0xaf, 0xf5, 0x26, 0x9a,
	0x86, 0xa7, 0xa9, 0x53, 0x15, 0x34, 0xf7, 0xda,
	0x2e, 0x4c, 0x30, 0x3d, 0x8a, 0x31, 0x8a, 0x72,
	0x1c, 0x3c, 0x0c, 0x95, 0x95, 0x68, 0x09, 0x53,
	0x2f, 0xcf, 0x0e, 0x24, 0x49, 0xa6, 0xb5, 0x25,
	0xb1, 0x6a, 0xed, 0xf5, 0xaa, 0x0d, 0xe6, 0x57,
	0xba, 0x63, 0x7b, 0x39, 0x1a, 0xaf, 0xd2, 0x55,
};

unsigned char NIST_AAD_GCM_E7[] = {
};

unsigned char NIST_IV_GCM_E7[] = {
	0xca, 0xfe, 0xba, 0xbe, 0xfa, 0xce, 0xdb, 0xad,
	0xde, 0xca, 0xf8, 0x88,
};

unsigned char NIST_TAG_GCM_E7[] = {
	0x99, 0x24, 0xa7, 0xc8, 0x58, 0x73, 0x36, 0xbf,
	0xb1, 0x18, 0x02, 0x4d, 0xb8, 0x67, 0x4a, 0x14,
};

unsigned char NIST_TEST_RESULT_GCM_E7[] = {
	0x39, 0x80, 0xca, 0x0b, 0x3c, 0x00, 0xe8, 0x41,
	0xeb, 0x06, 0xfa, 0xc4, 0x87, 0x2a, 0x27, 0x57,
	0x85, 0x9e, 0x1c, 0xea, 0xa6, 0xef, 0xd9, 0x84,
	0x62, 0x85, 0x93, 0xb4, 0x0c, 0xa1, 0xe1, 0x9c,
	0x7d, 0x77, 0x3d, 0x00, 0xc1, 0x44, 0xc5, 0x25,
	0xac, 0x61, 0x9d, 0x18, 0xc8, 0x4a, 0x3f, 0x47,
	0x18, 0xe2, 0x44, 0x8b, 0x2f, 0xe3, 0x24, 0xd9,
	0xcc, 0xda, 0x27, 0x10, 0xac, 0xad, 0xe2, 0x56,
};

unsigned char NIST_CHUNKS_GCM_E7[] = { 16, 16, 16, 16 };

/* GCM data - 8 - AES 192 - Test Case 10*/
unsigned char NIST_KEY_GCM_E8[] = {
	0xfe, 0xff, 0xe9, 0x92, 0x86, 0x65, 0x73, 0x1c,
	0x6d, 0x6a, 0x8f, 0x94, 0x67, 0x30, 0x83, 0x08,
	0xfe, 0xff, 0xe9, 0x92, 0x86, 0x65, 0x73, 0x1c,
};

unsigned char NIST_TEST_DATA_GCM_E8[] = {
	0xd9, 0x31, 0x32, 0x25, 0xf8, 0x84, 0x06, 0xe5,
	0xa5, 0x59, 0x09, 0xc5, 0xaf, 0xf5, 0x26, 0x9a,
	0x86, 0xa7, 0xa9, 0x53, 0x15, 0x34, 0xf7, 0xda,
	0x2e, 0x4c, 0x30, 0x3d, 0x8a, 0x31, 0x8a, 0x72,
	0x1c, 0x3c, 0x0c, 0x95, 0x95, 0x68, 0x09, 0x53,
	0x2f, 0xcf, 0x0e, 0x24, 0x49, 0xa6, 0xb5, 0x25,
	0xb1, 0x6a, 0xed, 0xf5, 0xaa, 0x0d, 0xe6, 0x57,
	0xba, 0x63, 0x7b, 0x39,
};

unsigned char NIST_AAD_GCM_E8[] = {
	0xfe, 0xed, 0xfa, 0xce, 0xde, 0xad, 0xbe, 0xef,
	0xfe, 0xed, 0xfa, 0xce, 0xde, 0xad, 0xbe, 0xef,
	0xab, 0xad, 0xda, 0xd2,
};

unsigned char NIST_IV_GCM_E8[] = {
	0xca, 0xfe, 0xba, 0xbe, 0xfa, 0xce, 0xdb, 0xad,
	0xde, 0xca, 0xf8, 0x88,
};

unsigned char NIST_TAG_GCM_E8[] = {
	0x25, 0x19, 0x49, 0x8e, 0x80, 0xf1, 0x47, 0x8f,
	0x37, 0xba, 0x55, 0xbd, 0x6d, 0x27, 0x61, 0x8c,
};

unsigned char NIST_TEST_RESULT_GCM_E8[] = {
	0x39, 0x80, 0xca, 0x0b, 0x3c, 0x00, 0xe8, 0x41,
	0xeb, 0x06, 0xfa, 0xc4, 0x87, 0x2a, 0x27, 0x57,
	0x85, 0x9e, 0x1c, 0xea, 0xa6, 0xef, 0xd9, 0x84,
	0x62, 0x85, 0x93, 0xb4, 0x0c, 0xa1, 0xe1, 0x9c,
	0x7d, 0x77, 0x3d, 0x00, 0xc1, 0x44, 0xc5, 0x25,
	0xac, 0x61, 0x9d, 0x18, 0xc8, 0x4a, 0x3f, 0x47,
	0x18, 0xe2, 0x44, 0x8b, 0x2f, 0xe3, 0x24, 0xd9,
	0xcc, 0xda, 0x27, 0x10,
};

unsigned char NIST_CHUNKS_GCM_E8[] = { 16, 16, 16, 12 };

/* GCM data - 9 - AES 256 - Test Case 13*/
unsigned char NIST_KEY_GCM_E9[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

unsigned char NIST_TEST_DATA_GCM_E9[] = {
};

unsigned char NIST_AAD_GCM_E9[] = {
};

unsigned char NIST_IV_GCM_E9[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
};

unsigned char NIST_TAG_GCM_E9[] = {
	0x53, 0x0f, 0x8a, 0xfb, 0xc7, 0x45, 0x36, 0xb9,
	0xa9, 0x63, 0xb4, 0xf1, 0xc4, 0xcb, 0x73, 0x8b,
};

unsigned char NIST_TEST_RESULT_GCM_E9[] = {
};

unsigned char NIST_CHUNKS_GCM_E9[] = { };

/* GCM data - 10 - AES 256 - Test Case 14*/
unsigned char NIST_KEY_GCM_E10[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

unsigned char NIST_TEST_DATA_GCM_E10[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

unsigned char NIST_AAD_GCM_E10[] = {
};

unsigned char NIST_IV_GCM_E10[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
};

unsigned char NIST_TAG_GCM_E10[] = {
	0xd0, 0xd1, 0xc8, 0xa7, 0x99, 0x99, 0x6b, 0xf0,
	0x26, 0x5b, 0x98, 0xb5, 0xd4, 0x8a, 0xb9, 0x19,
};

unsigned char NIST_TEST_RESULT_GCM_E10[] = {
	0xce, 0xa7, 0x40, 0x3d, 0x4d, 0x60, 0x6b, 0x6e,
	0x07, 0x4e, 0xc5, 0xd3, 0xba, 0xf3, 0x9d, 0x18,
};

unsigned char NIST_CHUNKS_GCM_E10[] = { 16 };

/* GCM data - 11 - AES 256 - Test Case 15*/
unsigned char NIST_KEY_GCM_E11[] = {
	0xfe, 0xff, 0xe9, 0x92, 0x86, 0x65, 0x73, 0x1c,
	0x6d, 0x6a, 0x8f, 0x94, 0x67, 0x30, 0x83, 0x08,
	0xfe, 0xff, 0xe9, 0x92, 0x86, 0x65, 0x73, 0x1c,
	0x6d, 0x6a, 0x8f, 0x94, 0x67, 0x30, 0x83, 0x08,
};

unsigned char NIST_TEST_DATA_GCM_E11[] = {
	0xd9, 0x31, 0x32, 0x25, 0xf8, 0x84, 0x06, 0xe5,
	0xa5, 0x59, 0x09, 0xc5, 0xaf, 0xf5, 0x26, 0x9a,
	0x86, 0xa7, 0xa9, 0x53, 0x15, 0x34, 0xf7, 0xda,
	0x2e, 0x4c, 0x30, 0x3d, 0x8a, 0x31, 0x8a, 0x72,
	0x1c, 0x3c, 0x0c, 0x95, 0x95, 0x68, 0x09, 0x53,
	0x2f, 0xcf, 0x0e, 0x24, 0x49, 0xa6, 0xb5, 0x25,
	0xb1, 0x6a, 0xed, 0xf5, 0xaa, 0x0d, 0xe6, 0x57,
	0xba, 0x63, 0x7b, 0x39, 0x1a, 0xaf, 0xd2, 0x55,
};

unsigned char NIST_AAD_GCM_E11[] = {
};

unsigned char NIST_IV_GCM_E11[] = {
	0xca, 0xfe, 0xba, 0xbe, 0xfa, 0xce, 0xdb, 0xad,
	0xde, 0xca, 0xf8, 0x88,
};

unsigned char NIST_TAG_GCM_E11[] = {
	0xb0, 0x94, 0xda, 0xc5, 0xd9, 0x34, 0x71, 0xbd,
	0xec, 0x1a, 0x50, 0x22, 0x70, 0xe3, 0xcc, 0x6c,
};

unsigned char NIST_TEST_RESULT_GCM_E11[] = {
	0x52, 0x2d, 0xc1, 0xf0, 0x99, 0x56, 0x7d, 0x07,
	0xf4, 0x7f, 0x37, 0xa3, 0x2a, 0x84, 0x42, 0x7d,
	0x64, 0x3a, 0x8c, 0xdc, 0xbf, 0xe5, 0xc0, 0xc9,
	0x75, 0x98, 0xa2, 0xbd, 0x25, 0x55, 0xd1, 0xaa,
	0x8c, 0xb0, 0x8e, 0x48, 0x59, 0x0d, 0xbb, 0x3d,
	0xa7, 0xb0, 0x8b, 0x10, 0x56, 0x82, 0x88, 0x38,
	0xc5, 0xf6, 0x1e, 0x63, 0x93, 0xba, 0x7a, 0x0a,
	0xbc, 0xc9, 0xf6, 0x62, 0x89, 0x80, 0x15, 0xad,
};

unsigned char NIST_CHUNKS_GCM_E11[] = { 16, 16, 16, 16 };

/* GCM data */
unsigned char NIST_KEY_GCM_E12[] = {
	0xfe, 0xff, 0xe9, 0x92, 0x86, 0x65, 0x73, 0x1c,
	0x6d, 0x6a, 0x8f, 0x94, 0x67, 0x30, 0x83, 0x08,
	0xfe, 0xff, 0xe9, 0x92, 0x86, 0x65, 0x73, 0x1c,
	0x6d, 0x6a, 0x8f, 0x94, 0x67, 0x30, 0x83, 0x08,
};

unsigned char NIST_TEST_DATA_GCM_E12[] = {
	0xd9, 0x31, 0x32, 0x25, 0xf8, 0x84, 0x06, 0xe5,
	0xa5, 0x59, 0x09, 0xc5, 0xaf, 0xf5, 0x26, 0x9a,
	0x86, 0xa7, 0xa9, 0x53, 0x15, 0x34, 0xf7, 0xda,
	0x2e, 0x4c, 0x30, 0x3d, 0x8a, 0x31, 0x8a, 0x72,
	0x1c, 0x3c, 0x0c, 0x95, 0x95, 0x68, 0x09, 0x53,
	0x2f, 0xcf, 0x0e, 0x24, 0x49, 0xa6, 0xb5, 0x25,
	0xb1, 0x6a, 0xed, 0xf5, 0xaa, 0x0d, 0xe6, 0x57,
	0xba, 0x63, 0x7b, 0x39,
};

unsigned char NIST_AAD_GCM_E12[] = {
	0xfe, 0xed, 0xfa, 0xce, 0xde, 0xad, 0xbe, 0xef,
	0xfe, 0xed, 0xfa, 0xce, 0xde, 0xad, 0xbe, 0xef,
	0xab, 0xad, 0xda, 0xd2,
};

unsigned char NIST_IV_GCM_E12[] = {
	0xca, 0xfe, 0xba, 0xbe, 0xfa, 0xce, 0xdb, 0xad,
	0xde, 0xca, 0xf8, 0x88,
};

unsigned char NIST_TAG_GCM_E12[] = {
	0x76, 0xfc, 0x6e, 0xce, 0x0f, 0x4e, 0x17, 0x68,
	0xcd, 0xdf, 0x88, 0x53, 0xbb, 0x2d, 0x55, 0x1b,
};

unsigned char NIST_TEST_RESULT_GCM_E12[] = {
	0x52, 0x2d, 0xc1, 0xf0, 0x99, 0x56, 0x7d, 0x07,
	0xf4, 0x7f, 0x37, 0xa3, 0x2a, 0x84, 0x42, 0x7d,
	0x64, 0x3a, 0x8c, 0xdc, 0xbf, 0xe5, 0xc0, 0xc9,
	0x75, 0x98, 0xa2, 0xbd, 0x25, 0x55, 0xd1, 0xaa,
	0x8c, 0xb0, 0x8e, 0x48, 0x59, 0x0d, 0xbb, 0x3d,
	0xa7, 0xb0, 0x8b, 0x10, 0x56, 0x82, 0x88, 0x38,
	0xc5, 0xf6, 0x1e, 0x63, 0x93, 0xba, 0x7a, 0x0a,
	0xbc, 0xc9, 0xf6, 0x62,
};

unsigned char NIST_CHUNKS_GCM_E12[] = { 16, 16, 16, 12 };

void dump_gcm_data(unsigned char *iv, unsigned int iv_length,
		   unsigned char *aad, unsigned int aad_length,
		   unsigned char *key, unsigned int key_length,
		   unsigned char *input_data, unsigned int data_length,
		   unsigned char *output_data,
		   unsigned char *t, unsigned int t_size)
{
	VV_(printf("IV \n"));
	dump_array(iv, iv_length);
	VV_(printf("AAD \n"));
	dump_array(aad, aad_length);
	VV_(printf("Key \n"));
	dump_array(key, key_length);
	VV_(printf("Input Data\n"));
	dump_array(input_data, data_length);
	VV_(printf("Output Data\n"));
	dump_array(output_data, data_length);
	VV_(printf("T\n"));
	dump_array(t, t_size);
}

void get_sizes(unsigned int *aad_length, unsigned int *data_length,
	       unsigned int *t_length, unsigned int *iv_length,
	       unsigned int *key_length, unsigned int *num_chunks,
		   unsigned int iteration)
{
	switch (iteration) {
		case 1:
			*aad_length = sizeof(NIST_AAD_GCM_E1);
			*data_length = sizeof(NIST_TEST_DATA_GCM_E1);
			*t_length = sizeof(NIST_TAG_GCM_E1);
			*iv_length = sizeof(NIST_IV_GCM_E1);
			*key_length = sizeof(NIST_KEY_GCM_E1);
			*num_chunks = sizeof(NIST_CHUNKS_GCM_E1);
			break;
		case 2:
			*aad_length = sizeof(NIST_AAD_GCM_E2);
			*data_length = sizeof(NIST_TEST_DATA_GCM_E2);
			*t_length = sizeof(NIST_TAG_GCM_E2);
			*iv_length = sizeof(NIST_IV_GCM_E2);
			*key_length = sizeof(NIST_KEY_GCM_E2);
			*num_chunks = sizeof(NIST_CHUNKS_GCM_E2);
			break;
		case 3:
			*aad_length = sizeof(NIST_AAD_GCM_E3);
			*data_length = sizeof(NIST_TEST_DATA_GCM_E3);
			*t_length = sizeof(NIST_TAG_GCM_E3);
			*iv_length = sizeof(NIST_IV_GCM_E3);
			*key_length = sizeof(NIST_KEY_GCM_E3);
			*num_chunks = sizeof(NIST_CHUNKS_GCM_E3);
			break;
		case 4:
			*aad_length = sizeof(NIST_AAD_GCM_E4);
			*data_length = sizeof(NIST_TEST_DATA_GCM_E4);
			*t_length = sizeof(NIST_TAG_GCM_E4);
			*iv_length = sizeof(NIST_IV_GCM_E4);
			*key_length = sizeof(NIST_KEY_GCM_E4);
			*num_chunks = sizeof(NIST_CHUNKS_GCM_E4);
			break;
		case 5:
			*aad_length = sizeof(NIST_AAD_GCM_E5);
			*data_length = sizeof(NIST_TEST_DATA_GCM_E5);
			*t_length = sizeof(NIST_TAG_GCM_E5);
			*iv_length = sizeof(NIST_IV_GCM_E5);
			*key_length = sizeof(NIST_KEY_GCM_E5);
			*num_chunks = sizeof(NIST_CHUNKS_GCM_E5);
			break;
		case 6:
			*aad_length = sizeof(NIST_AAD_GCM_E6);
			*data_length = sizeof(NIST_TEST_DATA_GCM_E6);
			*t_length = sizeof(NIST_TAG_GCM_E6);
			*iv_length = sizeof(NIST_IV_GCM_E6);
			*key_length = sizeof(NIST_KEY_GCM_E6);
			*num_chunks = sizeof(NIST_CHUNKS_GCM_E6);
			break;
		case 7:
			*aad_length = sizeof(NIST_AAD_GCM_E7);
			*data_length = sizeof(NIST_TEST_DATA_GCM_E7);
			*t_length = sizeof(NIST_TAG_GCM_E7);
			*iv_length = sizeof(NIST_IV_GCM_E7);
			*key_length = sizeof(NIST_KEY_GCM_E7);
			*num_chunks = sizeof(NIST_CHUNKS_GCM_E7);
			break;
		case 8:
			*aad_length = sizeof(NIST_AAD_GCM_E8);
			*data_length = sizeof(NIST_TEST_DATA_GCM_E8);
			*t_length = sizeof(NIST_TAG_GCM_E8);
			*iv_length = sizeof(NIST_IV_GCM_E8);
			*key_length = sizeof(NIST_KEY_GCM_E8);
			*num_chunks = sizeof(NIST_CHUNKS_GCM_E8);
			break;
		case 9:
			*aad_length = sizeof(NIST_AAD_GCM_E9);
			*data_length = sizeof(NIST_TEST_DATA_GCM_E9);
			*t_length = sizeof(NIST_TAG_GCM_E9);
			*iv_length = sizeof(NIST_IV_GCM_E9);
			*key_length = sizeof(NIST_KEY_GCM_E9);
			*num_chunks = sizeof(NIST_CHUNKS_GCM_E9);
			break;
		case 10:
			*aad_length = sizeof(NIST_AAD_GCM_E10);
			*data_length = sizeof(NIST_TEST_DATA_GCM_E10);
			*t_length = sizeof(NIST_TAG_GCM_E10);
			*iv_length = sizeof(NIST_IV_GCM_E10);
			*key_length = sizeof(NIST_KEY_GCM_E10);
			*num_chunks = sizeof(NIST_CHUNKS_GCM_E10);
			break;
		case 11:
			*aad_length = sizeof(NIST_AAD_GCM_E11);
			*data_length = sizeof(NIST_TEST_DATA_GCM_E11);
			*t_length = sizeof(NIST_TAG_GCM_E11);
			*iv_length = sizeof(NIST_IV_GCM_E11);
			*key_length = sizeof(NIST_KEY_GCM_E11);
			*num_chunks = sizeof(NIST_CHUNKS_GCM_E11);
			break;
		case 12:
			*aad_length = sizeof(NIST_AAD_GCM_E12);
			*data_length = sizeof(NIST_TEST_DATA_GCM_E12);
			*t_length = sizeof(NIST_TAG_GCM_E12);
			*iv_length = sizeof(NIST_IV_GCM_E12);
			*key_length = sizeof(NIST_KEY_GCM_E12);
			*num_chunks = sizeof(NIST_CHUNKS_GCM_E12);
			break;
	}

}

void load_test_data(unsigned char *aad, unsigned int aad_length,
		    unsigned char *data, unsigned int data_length,
		    unsigned char *result,
		    unsigned char *t, unsigned int t_length,
		    unsigned char *iv, unsigned int iv_length,
		    unsigned char *key, unsigned int key_length,
		    unsigned char *chunks, unsigned int num_chunks,
		    unsigned int iteration)
{
	switch (iteration) {
		case 1:
			memcpy(iv, NIST_IV_GCM_E1, iv_length);
			memcpy(aad, NIST_AAD_GCM_E1, aad_length);
			memcpy(key, NIST_KEY_GCM_E1, key_length);
			memcpy(data, NIST_TEST_DATA_GCM_E1, data_length);
			memcpy(result, NIST_TEST_RESULT_GCM_E1, data_length);
			memcpy(t, NIST_TAG_GCM_E1, t_length);
			memcpy(chunks, NIST_CHUNKS_GCM_E1, num_chunks);
			break;
		case 2:
			memcpy(iv, NIST_IV_GCM_E2, iv_length);
			memcpy(aad, NIST_AAD_GCM_E2, aad_length);
			memcpy(key, NIST_KEY_GCM_E2, key_length);
			memcpy(data, NIST_TEST_DATA_GCM_E2, data_length);
			memcpy(result, NIST_TEST_RESULT_GCM_E2, data_length);
			memcpy(t, NIST_TAG_GCM_E2, t_length);
			memcpy(chunks, NIST_CHUNKS_GCM_E2, num_chunks);
			break;
		case 3:
			memcpy(iv, NIST_IV_GCM_E3, iv_length);
			memcpy(aad, NIST_AAD_GCM_E3, aad_length);
			memcpy(key, NIST_KEY_GCM_E3, key_length);
			memcpy(data, NIST_TEST_DATA_GCM_E3, data_length);
			memcpy(result, NIST_TEST_RESULT_GCM_E3, data_length);
			memcpy(t, NIST_TAG_GCM_E3, t_length);
			memcpy(chunks, NIST_CHUNKS_GCM_E3, num_chunks);
			break;
		case 4:
			memcpy(iv, NIST_IV_GCM_E4, iv_length);
			memcpy(aad, NIST_AAD_GCM_E4, aad_length);
			memcpy(key, NIST_KEY_GCM_E4, key_length);
			memcpy(data, NIST_TEST_DATA_GCM_E4, data_length);
			memcpy(result, NIST_TEST_RESULT_GCM_E4, data_length);
			memcpy(t, NIST_TAG_GCM_E4, t_length);
			memcpy(chunks, NIST_CHUNKS_GCM_E4, num_chunks);
			break;
		case 5:
			memcpy(iv, NIST_IV_GCM_E5, iv_length);
			memcpy(aad, NIST_AAD_GCM_E5, aad_length);
			memcpy(key, NIST_KEY_GCM_E5, key_length);
			memcpy(data, NIST_TEST_DATA_GCM_E5, data_length);
			memcpy(result, NIST_TEST_RESULT_GCM_E5, data_length);
			memcpy(t, NIST_TAG_GCM_E5, t_length);
			memcpy(chunks, NIST_CHUNKS_GCM_E5, num_chunks);
			break;
		case 6:
			memcpy(iv, NIST_IV_GCM_E6, iv_length);
			memcpy(aad, NIST_AAD_GCM_E6, aad_length);
			memcpy(key, NIST_KEY_GCM_E6, key_length);
			memcpy(data, NIST_TEST_DATA_GCM_E6, data_length);
			memcpy(result, NIST_TEST_RESULT_GCM_E6, data_length);
			memcpy(t, NIST_TAG_GCM_E6, t_length);
			memcpy(chunks, NIST_CHUNKS_GCM_E6, num_chunks);
			break;
		case 7:
			memcpy(iv, NIST_IV_GCM_E7, iv_length);
			memcpy(aad, NIST_AAD_GCM_E7, aad_length);
			memcpy(key, NIST_KEY_GCM_E7, key_length);
			memcpy(data, NIST_TEST_DATA_GCM_E7, data_length);
			memcpy(result, NIST_TEST_RESULT_GCM_E7, data_length);
			memcpy(t, NIST_TAG_GCM_E7, t_length);
			memcpy(chunks, NIST_CHUNKS_GCM_E7, num_chunks);
			break;
		case 8:
			memcpy(iv, NIST_IV_GCM_E8, iv_length);
			memcpy(aad, NIST_AAD_GCM_E8, aad_length);
			memcpy(key, NIST_KEY_GCM_E8, key_length);
			memcpy(data, NIST_TEST_DATA_GCM_E8, data_length);
			memcpy(result, NIST_TEST_RESULT_GCM_E8, data_length);
			memcpy(t, NIST_TAG_GCM_E8, t_length);
			memcpy(chunks, NIST_CHUNKS_GCM_E8, num_chunks);
			break;
		case 9:
			memcpy(iv, NIST_IV_GCM_E9, iv_length);
			memcpy(aad, NIST_AAD_GCM_E9, aad_length);
			memcpy(key, NIST_KEY_GCM_E9, key_length);
			memcpy(data, NIST_TEST_DATA_GCM_E9, data_length);
			memcpy(result, NIST_TEST_RESULT_GCM_E9, data_length);
			memcpy(t, NIST_TAG_GCM_E9, t_length);
			memcpy(chunks, NIST_CHUNKS_GCM_E9, num_chunks);
			break;
		case 10:
			memcpy(iv, NIST_IV_GCM_E10, iv_length);
			memcpy(aad, NIST_AAD_GCM_E10, aad_length);
			memcpy(key, NIST_KEY_GCM_E10, key_length);
			memcpy(data, NIST_TEST_DATA_GCM_E10, data_length);
			memcpy(result, NIST_TEST_RESULT_GCM_E10, data_length);
			memcpy(t, NIST_TAG_GCM_E10, t_length);
			memcpy(chunks, NIST_CHUNKS_GCM_E10, num_chunks);
			break;
		case 11:
			memcpy(iv, NIST_IV_GCM_E11, iv_length);
			memcpy(aad, NIST_AAD_GCM_E11, aad_length);
			memcpy(key, NIST_KEY_GCM_E11, key_length);
			memcpy(data, NIST_TEST_DATA_GCM_E11, data_length);
			memcpy(result, NIST_TEST_RESULT_GCM_E11, data_length);
			memcpy(t, NIST_TAG_GCM_E11, t_length);
			memcpy(chunks, NIST_CHUNKS_GCM_E11, num_chunks);
			break;
		case 12:
			memcpy(iv, NIST_IV_GCM_E12, iv_length);
			memcpy(aad, NIST_AAD_GCM_E12, aad_length);
			memcpy(key, NIST_KEY_GCM_E12, key_length);
			memcpy(data, NIST_TEST_DATA_GCM_E12, data_length);
			memcpy(result, NIST_TEST_RESULT_GCM_E12, data_length);
			memcpy(t, NIST_TAG_GCM_E12, t_length);
			memcpy(chunks, NIST_CHUNKS_GCM_E12, num_chunks);
			break;
	}

}

int test_gcm_kat(int iteration)
{
	unsigned int aad_length;
	unsigned int data_length;
	unsigned int t_length;
	unsigned int iv_length;
	unsigned int key_length;
	unsigned int num_chunks;

	get_sizes(&aad_length, &data_length, &t_length, &iv_length,
		  &key_length, &num_chunks, iteration);

	unsigned char iv[iv_length];
	unsigned char input_data[data_length];
	unsigned char encrypt[data_length];
	unsigned char decrypt[data_length];
	unsigned char result[data_length];
	unsigned char aad[aad_length];
	unsigned char key[key_length];
	unsigned char t[t_length];
	unsigned char t_result[t_length];
	unsigned char chunks[num_chunks];

	int rc = 0;

	VV_(printf("Test Parameters for iteration = %i\n", iteration));
	VV_(printf("key length = %i, data length = %i, tag length = %i,"
	    "iv length = %i aad_length = %i\n", key_length, data_length,
	    t_length, iv_length, aad_length));

	load_test_data(aad, aad_length, input_data, data_length, result,
		       t_result, t_length, iv, iv_length, key, key_length,
			   chunks, num_chunks, iteration);

	rc = ica_aes_gcm(input_data, data_length,
			 encrypt,
			 iv, iv_length,
			 aad, aad_length,
			 t, t_length,
			 key, key_length,
			 1);
	if (rc == EPERM) {
		VV_(printf("ica_aes_gcm returns with EPERM (%d).\n", rc));
		VV_(printf("Operation is not permitted on this machine. Test skipped!\n"));
		return 0;
	}
	if (rc) {
		VV_(printf("ica_aes_gcm encrypt failed with rc = %i\n", rc));
		dump_gcm_data(iv, iv_length, aad, aad_length, key, key_length,
			      input_data, data_length, encrypt, t, t_length);
	}
	if (!rc) {
		VV_(printf("Encrypt:\n"));
		dump_gcm_data(iv, iv_length, aad, aad_length, key, key_length,
			      input_data, data_length, encrypt, t,
			      t_length);
	}

	if (memcmp(result, encrypt, data_length)) {
		VV_(printf("Encryption Result does not match the known ciphertext!\n"));
		VV_(printf("Expected data:\n"));
		dump_array(result, data_length);
		VV_(printf("Encryption Result:\n"));
		dump_array(encrypt, data_length);
		rc++;
	}
	if (memcmp(t, t_result, t_length)) {
		VV_(printf("Tag result does not match the expected tag!\n"));
		VV_(printf("Expected tag:\n"));
		dump_array(t_result, t_length);
		VV_(printf("Tag Result:\n"));
		dump_array(t, t_length);
		rc++;
	}
	if (rc) {
		VV_(printf("GCM test exited after encryption\n"));
		return rc;
	}
	rc = ica_aes_gcm(decrypt, data_length,
			 encrypt,
			 iv, iv_length,
			 aad, aad_length,
			 t, t_length,
			 key, key_length,
			 0);
	if (rc == EPERM) {
		VV_(printf("ica_aes_gcm returns with EPERM (%d).\n", rc));
		VV_(printf("Operation is not permitted on this machine. Test skipped!\n"));
		return 0;
	}
	if (rc) {
		VV_(printf("ica_aes_gcm decrypt failed with rc = %i\n", rc));
		dump_gcm_data(iv, iv_length, aad, aad_length, key, key_length,
			      encrypt, data_length, decrypt, t,
			      t_length);
	}


	if (!rc) {
		VV_(printf("Decrypt:\n"));
		dump_gcm_data(iv, iv_length, aad, aad_length, key, key_length,
			      encrypt, data_length, decrypt, t,
			      t_length);
	}

	if (memcmp(decrypt, input_data, data_length)) {
		VV_(printf("Decryption Result does not match the original data!\n"));
		VV_(printf("Original data:\n"));
		dump_array(input_data, data_length);
		VV_(printf("Decryption Result:\n"));
		dump_array(decrypt, data_length);
		rc++;
	}
	if (memcmp(t, t_result, t_length)) {
		VV_(printf("Tag result does not match the expected tag!\n"));
		VV_(printf("Expected tag:\n"));
		dump_array(t_result, t_length);
		VV_(printf("Tag Result:\n"));
		dump_array(t, t_length);
		rc++;
	}
	return rc;
}

int test_gcm_kat_update(int iteration)
{
	unsigned int aad_length;
	unsigned int aad_length_tmp;
	unsigned int data_length;
	unsigned int t_length;
	unsigned int iv_length;
	unsigned int key_length;
	unsigned int num_chunks;

	get_sizes(&aad_length, &data_length, &t_length, &iv_length,
		  &key_length, &num_chunks, iteration);

	unsigned char iv[iv_length];
	unsigned char input_data[data_length];
	unsigned char encrypt[data_length];
	unsigned char decrypt[data_length];
	unsigned char result[data_length];
	unsigned char aad[aad_length];
	unsigned char key[key_length];
	unsigned char t[t_length];
	unsigned char t_result[t_length];
	unsigned char chunks[num_chunks];
	unsigned int chunk_len;
	unsigned int offset;
	unsigned char *chunk_data;
	unsigned char icb[AES_BLOCK_SIZE];
	unsigned char ucb[AES_BLOCK_SIZE];
	unsigned char subkey[AES_BLOCK_SIZE];
	unsigned char running_tag[AES_BLOCK_SIZE];
	unsigned int  sum_A_len;
	unsigned int  sum_C_len;
	int rc = 0, i;

	VV_(printf("Test Parameters for iteration = %i\n", iteration));
	VV_(printf("key length = %i, data length = %i, tag length = %i,"
		"iv length = %i aad_length = %i\n", key_length, data_length,
		t_length, iv_length, aad_length));

	load_test_data(aad, aad_length, input_data, data_length, result,
		       t_result, t_length, iv, iv_length, key, key_length,
		       chunks, num_chunks, iteration);

	aad_length_tmp = aad_length;
	memset(running_tag, 0, AES_BLOCK_SIZE);
	rc = ica_aes_gcm_initialize(iv, iv_length, key, key_length,
								icb, ucb, subkey, 1);

	offset = 0;
	for (i = 0; i < num_chunks; i++) {
		chunk_len = chunks[i];
		chunk_data = input_data + offset;

		rc = ica_aes_gcm_intermediate(chunk_data, chunk_len, encrypt + offset,
									  ucb, aad, aad_length,
									  running_tag, AES_BLOCK_SIZE,
									  key, key_length, subkey, 1);
		/* clear aad_length after first run*/
		aad_length = 0;
		offset += chunk_len;
	}
	sum_A_len = aad_length_tmp;
	sum_C_len = offset;
	rc = ica_aes_gcm_last(icb, sum_A_len, sum_C_len, running_tag,
						  t, t_length, key, key_length, subkey, 1);

	if (rc == EPERM) {
		VV_(printf("ica_aes_gcm returns with EPERM (%d).\n", rc));
		VV_(printf("Operation is not permitted on this machine. Test skipped!\n"));
		return 0;
	}
	if (rc) {
		VV_(printf("ica_aes_gcm encrypt failed with rc = %i\n", rc));
		dump_gcm_data(iv, iv_length, aad, aad_length, key, key_length,
			      input_data, data_length, encrypt, t, t_length);
	}
	if (!rc) {
		VV_(printf("Encrypt:\n"));
		dump_gcm_data(iv, iv_length, aad, aad_length, key, key_length,
			      input_data, data_length, encrypt, running_tag,
			      t_length);
	}

	if (memcmp(result, encrypt, data_length)) {
		VV_(printf("Encryption Result does not match the known ciphertext!\n"));
		VV_(printf("Expected data:\n"));
		dump_array(result, data_length);
		VV_(printf("Encryption Result:\n"));
		dump_array(encrypt, data_length);
		rc++;
	}
	if (memcmp(running_tag, t_result, t_length)) {
		VV_(printf("Tag result does not match the expected tag!\n"));
		VV_(printf("Expected tag:\n"));
		dump_array(t_result, t_length);
		VV_(printf("Tag Result:\n"));
		dump_array(t, t_length);
		rc++;
	}
	if (rc) {
		VV_(printf("GCM test exited after encryption\n"));
		return rc;
	}

	aad_length = aad_length_tmp;
	memset(running_tag, 0, AES_BLOCK_SIZE);
	rc = ica_aes_gcm_initialize(iv, iv_length, key, key_length,
								icb, ucb, subkey, 0);

	offset = 0;
	for (i = 0; i < num_chunks; i++) {
		chunk_len = chunks[i];
		chunk_data = encrypt + offset;

		rc = ica_aes_gcm_intermediate(decrypt + offset, chunk_len, chunk_data,
									  ucb, aad, aad_length,
									  running_tag, AES_BLOCK_SIZE,
									  key, key_length, subkey, 0);

		/* clear aad_length after first run*/
		aad_length = 0;
		offset += chunk_len;
	}
	sum_A_len = aad_length_tmp;
	sum_C_len = offset;
	rc = ica_aes_gcm_last(icb, sum_A_len, sum_C_len, running_tag,
						  t_result, t_length, key, key_length, subkey, 0);


	if (rc == EPERM) {
		VV_(printf("ica_aes_gcm returns with EPERM (%d).\n", rc));
		VV_(printf("Operation is not permitted on this machine. Test skipped!\n"));
		return 0;
	}
	if (rc) {
		VV_(printf("ica_aes_gcm decrypt failed with rc = %i\n", rc));
		dump_gcm_data(iv, iv_length, aad, aad_length, key, key_length,
			      encrypt, data_length, decrypt, running_tag,
			      t_length);
	}


	if (!rc) {
		VV_(printf("Decrypt:\n"));
		dump_gcm_data(iv, iv_length, aad, aad_length, key, key_length,
			      encrypt, data_length, decrypt, running_tag,
			      t_length);
	}

	if (memcmp(decrypt, input_data, data_length)) {
		VV_(printf("Decryption Result does not match the original data!\n"));
		VV_(printf("Original data:\n"));
		dump_array(input_data, data_length);
		VV_(printf("Decryption Result:\n"));
		dump_array(decrypt, data_length);
		rc++;
	}
	if (memcmp(running_tag, t_result, t_length)) {
		VV_(printf("Tag result does not match the expected tag!\n"));
		VV_(printf("Expected tag:\n"));
		dump_array(t_result, t_length);
		VV_(printf("Tag Result:\n"));
		dump_array(t, t_length);
		rc++;
	}
	return rc;
}

/*
 * Performs GCM tests.
 */
int main(int argc, char **argv)
{
	int rc = 0;
	int error_count = 0;
	int iteration;

	set_verbosity(argc, argv);

	for(iteration = 1; iteration <= NR_TESTS; iteration++)	{
		rc = test_gcm_kat(iteration);
		if (rc) {
			V_(printf("test_gcm_kat failed with rc = %i\n", rc));
			error_count++;
		}

		rc = test_gcm_kat_update(iteration);
		if (rc) {
			V_(printf("test_gcm_kat_update failed with rc = %i\n", rc));
			error_count++;
		}
	}
	if (error_count)
		printf("%i of %i AES-GCM tests failed.\n", error_count, iteration);
	else
		printf("All AES-GCM tests passed.\n");
	return rc;
}
