#include <cstdio>
#include <iostream>
#include <fstream>
#include "gost_hash.hpp"


int hexDig(char ch) {
  if ((ch >= '0') && (ch <= '9')) return ch - '0';
  if ((ch >= 'A') && (ch <= 'F')) return ch - 'A' + 10;
  if ((ch >= 'a') && (ch <= 'f')) return ch - 'a' + 10;
  return -1;
}

int main(int argc, const char * argv[]) {
    int len;
    byte hashed[32];
    int rounds = 32;
    Gost gost94(rounds);

    if (argc > 1) {
        byte buf[1024];
        std::ifstream input;
        input.open(argv[1]);
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
        

        while (scanf("%d", &len) != EOF) {
            for (int i = len - 1; i >= 0; --i) {
                char c1 = 0, c2 = 0;
                while (hexDig(c1) < 0) scanf("%c", &c1);
                while (hexDig(c2) < 0) scanf("%c", &c2);
                buf[i] = hexDig(c1) * 16 + hexDig(c2);
            }
            gost94.hash(buf, len, hashed);
            std::cout << "0x";
            for (int i = 31; i >= 0; --i)
              printf("%02X", hashed[i]);
            std::cout << "\n";
        }
    } else {
        len = 0;
        byte buf[] = "This is message, length=32 bytes";

        for (int i = 0; buf[i] != '\0'; ++i) {
            ++len;
            printf("%c", buf[i]);
        }
        printf("\n");
        gost94.hash(buf, len, hashed);

        std::cout << "0x";
        for (int i = 31; i >= 0; --i)
          printf("%02X", hashed[i]);
        std::cout << "\n";
    }

  return 0;
}
