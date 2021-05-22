#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>

#include "gost_hash.hpp"


const char filename[] = "statistics";
const int rounds = 32;
const int tests = 100;
const int max_len = 70;
const bool console = false;


void string_xor_1(byte* string, int rand_len){
    string[rand_len - 1] ^= 0x80;
}

void random_strings(byte* text1, byte* text2, int rand_len){
    for (int i = 0; i < rand_len; ++i) {
        if (console) {
            text1[i] = 'a' + rand() % 26;
            continue;
        }
        text1[i] = (char)(rand() % 256);
    }
    text2 = text1;
    string_xor_1(text2, rand_len);
}

int count_diff(byte* y1, byte* y2) {
    int diff = 0;
    for (int i = 0; i < 32; ++i) {
        for(byte j = 0; j < 8; ++j){
            diff += ((y1[i] >> j) & (byte)1) ^ ((y2[i] >> j) & (byte)1);
        }
    }
    return diff;
}

void gen_stat(std::ofstream& output) {
    std::vector<int> diffs(rounds, 0);
    for (int i = 0; i < tests; ++i) {
        int rand_len = 1 + rand() % max_len;
        byte X1[rand_len], X2[rand_len];
        random_strings(X1, X2, rand_len);
        if (console) {
            std::cout << std::endl;
            std::cout << "Random string:" << std::endl;
            std::cout << X1 << std::endl;
        }
        for (int j = 0; j < rounds; j += 8){
            Gost gost(j + 8);
            byte Y1[32], Y2[32];
            gost.hash(X1, rand_len / 2, Y1);
            gost.hash(X2, rand_len / 2, Y2);
            diffs[j] += count_diff(Y1, Y2);
            if (console) {
                std::cout << "For round number: " << j + 8 << " bits differ count: " << count_diff(Y1, Y2) << std::endl;
            }
        }
    }

    for (int j = 0; j < rounds; j += 8) {
        output << j + 8 << ' ' << (diffs[j] / tests) << std::endl;
        if (console) {
            std::cout << std::endl;
            std::cout << "Middle value of different bits for " << j + 8 << " rounds: " << (diffs[j] / tests) << std::endl;
        }
    }
}


int main(){
    srand(time(0));
    std::ofstream output(filename);
    std::cout << "Differential crypto analysis" << std::endl;
    std::cout << std::endl;
    std::cout << "Number of test strings: " << tests << std::endl;
    std::cout << "Will explore round numbers from 1 to " << rounds << std::endl;
    std::cout << "statistics will be written into file: " << filename << std::endl;
    gen_stat(output);
    output.close();
    std::cout << std::endl;
    return 0;
}