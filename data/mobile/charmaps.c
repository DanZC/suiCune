#include <stdint.h>
#include "charmaps.h"

const char Zipcode_CharPool_Ato9[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
const char Zipcode_CharPool_AtoZ[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char Zipcode_CharPool_0to9[] = "0123456789";
const char Zipcode_CharPool_Ato9_Blank[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ""0123456789"" ""-";
const char Zipcode_CharPool_AtoZ_2[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char Zipcode_CharPool_0to9_2[] = "0123456789";
const char Zipcode_CharPool_Blank[] = " ";
const char Zipcode_CharPool_Dash[] = "-";

#define Zipcode_CharPool_L Zipcode_CharPool_AtoZ + ('L'-'A')
#define Zipcode_CharPool_V Zipcode_CharPool_AtoZ + ('V'-'A')
#define Zipcode_CharPool_M Zipcode_CharPool_AtoZ + ('M'-'A')
#define Zipcode_CharPool_D Zipcode_CharPool_AtoZ + ('D'-'A')
#define Zipcode_CharPool_S Zipcode_CharPool_AtoZ + ('S'-'A')
#define Zipcode_CharPool_I Zipcode_CharPool_AtoZ + ('I'-'A')
#define Zipcode_CharPool_4 Zipcode_CharPool_0to9 + 4
#define Zipcode_CharPool_7 Zipcode_CharPool_0to9 + 7
#define Zipcode_CharPool_8 Zipcode_CharPool_0to9 + 8
#define Zipcode_CharPool_9 Zipcode_CharPool_0to9 + 9

const struct CharPool Zipcode_CharPools[] = {
	// address of the charpool,       char pool length in bytes
	{Zipcode_CharPool_0to9,       10}, // CHARPOOL_0_TO_9
	{Zipcode_CharPool_AtoZ,       26}, // CHARPOOL_A_TO_Z
	{Zipcode_CharPool_Ato9,       36}, // CHARPOOL_A_TO_9
	{Zipcode_CharPool_L,           1}, // CHARPOOL_L
	{Zipcode_CharPool_V,           1}, // CHARPOOL_V
	{Zipcode_CharPool_M,           1}, // CHARPOOL_M
	{Zipcode_CharPool_D,           1}, // CHARPOOL_D
	{Zipcode_CharPool_S,           1}, // CHARPOOL_S
	{Zipcode_CharPool_I,           1}, // CHARPOOL_I
	{Zipcode_CharPool_4,           1}, // CHARPOOL_4
	{Zipcode_CharPool_7,           1}, // CHARPOOL_7
	{Zipcode_CharPool_8,           1}, // CHARPOOL_8
	{Zipcode_CharPool_9,           1}, // CHARPOOL_9
	{Zipcode_CharPool_AtoZ_2,     26}, // CHARPOOL_A_TO_Z_2
	{Zipcode_CharPool_0to9_2,     10}, // CHARPOOL_0_TO_9_2
	{Zipcode_CharPool_Ato9_Blank, 37}, // CHARPOOL_BLANK_A_TO_Z
	{Zipcode_CharPool_Blank,       1}, // CHARPOOL_BLANK
	{Zipcode_CharPool_Dash,        1}, // CHARPOOL_DASH
};
