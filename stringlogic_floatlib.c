/*
============================================================
StringLogicFloatLib
============================================================

Ever run into a situation where you have string reggies
but no numeric ones? I got you covered, boi.

String-based gate logic arithmetic library.

Features:
- Logic gates
- Binary add/sub
- Hex conversion
- Simplified float packing
- No atoi()
- No strtol()
- No numeric parsing helpers

Educational / VM / emulator oriented.
============================================================
*/

#include <stdio.h>
#include <string.h>

/* =========================================================
   LOGIC GATES
========================================================= */

char NOT_GATE(char a)
{
    if (a == '0')
    {
        return '1';
    }

    return '0';
}

char AND_GATE(char a, char b)
{
    if (a == '1')
    {
        if (b == '1')
        {
            return '1';
        }
    }

    return '0';
}

char OR_GATE(char a, char b)
{
    if (a == '1')
    {
        return '1';
    }

    if (b == '1')
    {
        return '1';
    }

    return '0';
}

char XOR_GATE(char a, char b)
{
    if (a != b)
    {
        return '1';
    }

    return '0';
}

/* =========================================================
   HALF ADDER
========================================================= */

void HALF_ADDER(char a, char b, char* sum, char* carry)
{
    *sum = XOR_GATE(a, b);
    *carry = AND_GATE(a, b);
}

/* =========================================================
   FULL ADDER
========================================================= */

void FULL_ADDER(char a, char b, char cin, char* sum, char* carry)
{
    char s1;
    char c1;

    char s2;
    char c2;

    HALF_ADDER(a, b, &s1, &c1);
    HALF_ADDER(s1, cin, &s2, &c2);

    *sum = s2;
    *carry = OR_GATE(c1, c2);
}

/* =========================================================
   PAD BINARY STRINGS
========================================================= */

void PAD_BITS(char* a, char* b)
{
    static char tempA[256];
    static char tempB[256];

    int lenA = strlen(a);
    int lenB = strlen(b);

    int maxLen = lenA;

    if (lenB > maxLen)
    {
        maxLen = lenB;
    }

    int i;

    for (i = 0; i < maxLen - lenA; i++)
    {
        tempA[i] = '0';
    }

    strcpy(tempA + i, a);

    for (i = 0; i < maxLen - lenB; i++)
    {
        tempB[i] = '0';
    }

    strcpy(tempB + i, b);

    strcpy(a, tempA);
    strcpy(b, tempB);
}

/* =========================================================
   BINARY ADD
========================================================= */

void BINARY_ADD(char* a, char* b, char* out)
{
    char A[256];
    char B[256];

    strcpy(A, a);
    strcpy(B, b);

    PAD_BITS(A, B);

    int len = strlen(A);

    char carry = '0';

    out[len + 1] = '\0';

    int i;

    for (i = len - 1; i >= 0; i--)
    {
        char sum;

        FULL_ADDER(A[i], B[i], carry, &sum, &carry);

        out[i + 1] = sum;
    }

    out[0] = carry;

    if (carry == '0')
    {
        memmove(out, out + 1, len + 1);
    }
}

/* =========================================================
   TWOS COMPLEMENT
========================================================= */

void TWOS_COMPLEMENT(char* bits, char* out)
{
    char inverted[256];

    int len = strlen(bits);

    int i;

    for (i = 0; i < len; i++)
    {
        inverted[i] = NOT_GATE(bits[i]);
    }

    inverted[len] = '\0';

    char one[256];

    for (i = 0; i < len - 1; i++)
    {
        one[i] = '0';
    }

    one[len - 1] = '1';
    one[len] = '\0';

    BINARY_ADD(inverted, one, out);

    if (strlen(out) > len)
    {
        memmove(out, out + 1, len + 1);
    }
}

/* =========================================================
   SUBTRACTION
========================================================= */

void BINARY_SUB(char* a, char* b, char* out)
{
    char twos[256];

    TWOS_COMPLEMENT(b, twos);

    BINARY_ADD(a, twos, out);

    int len = strlen(a);

    if (strlen(out) > len)
    {
        memmove(out, out + 1, len + 1);
    }
}

/* =========================================================
   DECIMAL DIGIT -> BINARY NIBBLE
========================================================= */

void DIGIT_TO_BIN(char digit, char* out)
{
    if (digit == '0') strcpy(out, "0000");
    else if (digit == '1') strcpy(out, "0001");
    else if (digit == '2') strcpy(out, "0010");
    else if (digit == '3') strcpy(out, "0011");
    else if (digit == '4') strcpy(out, "0100");
    else if (digit == '5') strcpy(out, "0101");
    else if (digit == '6') strcpy(out, "0110");
    else if (digit == '7') strcpy(out, "0111");
    else if (digit == '8') strcpy(out, "1000");
    else if (digit == '9') strcpy(out, "1001");
    else strcpy(out, "0000");
}

/* =========================================================
   DECIMAL STRING -> BINARY STRING
========================================================= */

void DECIMAL_TO_BINARY(char* decimal, char* out)
{
    out[0] = '\0';

    int i;

    for (i = 0; i < strlen(decimal); i++)
    {
        char nibble[5];

        DIGIT_TO_BIN(decimal[i], nibble);

        strcat(out, nibble);
    }
}

/* =========================================================
   NIBBLE -> HEX
========================================================= */

char NIBBLE_TO_HEX(char* nibble)
{
    if (strcmp(nibble, "0000") == 0) return '0';
    if (strcmp(nibble, "0001") == 0) return '1';
    if (strcmp(nibble, "0010") == 0) return '2';
    if (strcmp(nibble, "0011") == 0) return '3';
    if (strcmp(nibble, "0100") == 0) return '4';
    if (strcmp(nibble, "0101") == 0) return '5';
    if (strcmp(nibble, "0110") == 0) return '6';
    if (strcmp(nibble, "0111") == 0) return '7';
    if (strcmp(nibble, "1000") == 0) return '8';
    if (strcmp(nibble, "1001") == 0) return '9';
    if (strcmp(nibble, "1010") == 0) return 'A';
    if (strcmp(nibble, "1011") == 0) return 'B';
    if (strcmp(nibble, "1100") == 0) return 'C';
    if (strcmp(nibble, "1101") == 0) return 'D';
    if (strcmp(nibble, "1110") == 0) return 'E';
    if (strcmp(nibble, "1111") == 0) return 'F';

    return '?';
}

/* =========================================================
   BINARY -> HEX
========================================================= */

void BINARY_TO_HEX(char* binary, char* out)
{
    out[0] = '\0';

    int len = strlen(binary);

    int i;

    for (i = 0; i < len; i += 4)
    {
        char nibble[5];

        strncpy(nibble, binary + i, 4);

        nibble[4] = '\0';

        char h = NIBBLE_TO_HEX(nibble);

        int outLen = strlen(out);

        out[outLen] = h;
        out[outLen + 1] = '\0';
    }
}

/* =========================================================
   SIMPLE FLOAT PACK
========================================================= */

void PACK_FLOAT(char* decimal, char* out)
{
    char sign = '0';

    char working[256];

    strcpy(working, decimal);

    if (working[0] == '-')
    {
        sign = '1';

        memmove(working, working + 1, strlen(working));
    }

    char binary[256];

    DECIMAL_TO_BINARY(working, binary);

    strcpy(out, "");

    int outLen = strlen(out);

    out[outLen] = sign;
    out[outLen + 1] = '\0';

    strcat(out, "10000000");

    int i;

    for (i = 0; i < 23; i++)
    {
        if (i < strlen(binary))
        {
            int len = strlen(out);

            out[len] = binary[i];
            out[len + 1] = '\0';
        }
        else
        {
            strcat(out, "0");
        }
    }
}

/* =========================================================
   DEMO
========================================================= */

int main()
{
    char addOut[256];
    char subOut[256];

    char binary[256];
    char hex[256];

    char floatBits[256];

    printf("======== STRING LOGIC FLOAT LIB ========\n\n");

    BINARY_ADD("00001111", "00000001", addOut);

    printf("ADD:\n");
    printf("%s\n\n", addOut);

    BINARY_SUB("00001111", "00000001", subOut);

    printf("SUB:\n");
    printf("%s\n\n", subOut);

    DECIMAL_TO_BINARY("1234", binary);

    printf("BINARY:\n");
    printf("%s\n\n", binary);

    BINARY_TO_HEX(binary, hex);

    printf("HEX:\n");
    printf("%s\n\n", hex);

    PACK_FLOAT("1234", floatBits);

    printf("FLOAT BITS:\n");
    printf("%s\n\n", floatBits);

    return 0;
}
