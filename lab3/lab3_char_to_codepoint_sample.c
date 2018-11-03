#include <stdio.h>
#include "utf8.h"

int main() {
    char *str = "你好1Ω";
    unsigned char *pt;
    pt = (unsigned char *)str;
    int lenptr = 0;
    int codept = utf8_to_codepoint(pt, &lenptr);
    printf("你 -> %x [%d]\n", codept, lenptr);
    pt += lenptr;
    codept = utf8_to_codepoint(pt, &lenptr);
    printf("好 -> %x [%d]\n", codept, lenptr);
    pt += lenptr;
    codept = utf8_to_codepoint(pt, &lenptr);
    printf("1 -> %x [%d]\n", codept, lenptr);
    pt += lenptr;
    codept = utf8_to_codepoint(pt, &lenptr);
    printf("Ω -> %x [%d]\n", codept, lenptr);
    return 0;
}
