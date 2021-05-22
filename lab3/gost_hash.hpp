#ifndef gost_hash_hpp
#define gost_hash_hpp


typedef unsigned char byte; // Объявляем тип byte = unsigned char

// byte arr[] - ссылка на область памяти - хэшируемые данные
// int len - длина этой области в байтах
// byte res[] - ссылка на существуюший массив размером 32 байта - результат хэширования

typedef byte Block[32]; // Block - массив из 32х байтов (256 бит)
typedef byte Block32[4]; // Block32 - массив из 4х байтов (32 бита)

class Gost {
public:
    Gost();
    Gost(int user_rounds);
    ~Gost(){};

    // ГОСТ 28147-89
    void E(byte  D[], byte K[], byte R[]);
    
    // Функция f в ГОСТ 28147-89
    void E_f(byte A[], byte K[], byte R[]);
    
    void f(byte H[], byte M[], byte newH[]);
    
    // GOST R 34.11-94
    void A(byte Y[], byte R[]);

    int fi(int arg);
    void P(byte Y[], byte R[]);
    void psi(byte arr[]);
    void psi(byte arr[], int p);

    void hash(byte* buf, int len, byte* result);

private:
    int rounds;
};


#endif /* gost_hash_hpp */
