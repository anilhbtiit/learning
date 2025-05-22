#include <iostream>
#include <bitset>
#include <cstdlib> // rand
#include <ctime> // timer

inline unsigned long get_time_in_ms()
{
    return (unsigned long)((double(clock()) / CLOCKS_PER_SEC) * 1000);
}


void one_sec_delay()
{
    unsigned long end_time = get_time_in_ms() + 1000;

    while(get_time_in_ms() < end_time)
    {
    }
}

struct Bitfield {
    unsigned char a:1, b:1, c:1, d:1, e:1, f:1, g:1, h:1;
};

struct Bitset {
    std::bitset<8> bits;
};

int main(int argc, char **argv)
{
    printf("sizeof(Bitfield) = %zd\n", sizeof(Bitfield));
    printf("sizeof(Bitset) = %zd\n", sizeof(Bitset));
    printf("sizeof(std::bitset<1>) = %zd\n", sizeof(std::bitset<1>));
    printf("sizeof(std::bitset<4>) = %zd\n", sizeof(std::bitset<4>));
    printf("sizeof(std::bitset<8>) = %zd\n", sizeof(std::bitset<8>));
    printf("sizeof(std::bitset<12>) = %zd\n", sizeof(std::bitset<12>));
    printf("sizeof(std::bitset<32>) = %zd\n", sizeof(std::bitset<32>));
    printf("sizeof(std::bitset<64>) = %zd\n", sizeof(std::bitset<64>));

    srand(get_time_in_ms());

    using namespace std;

    bitset<5000000> bits;
    bool *bools = new bool[5000000];

    unsigned long current_time, difference1, difference2;
    double total;

    one_sec_delay();

    total = 0;
    current_time = get_time_in_ms();

    for (unsigned int num = 0; num != 200000000; ++num)
    {
        bools[rand() % 5000000] = rand() % 2;
    }

    difference1 = get_time_in_ms() - current_time;
    current_time = get_time_in_ms();

    for (unsigned int num2 = 0; num2 != 100; ++num2)
    {
        for (unsigned int num = 0; num != 5000000; ++num)
        {
            total += bools[num];
        }
    }   

    difference2 = get_time_in_ms() - current_time;

    cout << "Bool:" << endl << "sum total = " << total << ", random access time = " << difference1 << ", sequential access time = " << difference2 << endl << endl;


    one_sec_delay();

    total = 0;
    current_time = get_time_in_ms();

    for (unsigned int num = 0; num != 200000000; ++num)
    {
        bits[rand() % 5000000] = rand() % 2;
    }

    difference1 = get_time_in_ms() - current_time;
    current_time = get_time_in_ms();

    for (unsigned int num2 = 0; num2 != 100; ++num2)
    {
        for (unsigned int num = 0; num != 5000000; ++num)
        {
            total += bits[num];
        }
    }   

    difference2 = get_time_in_ms() - current_time;

    cout << "Bitset:" << endl << "sum total = " << total << ", random access time = " << difference1 << ", sequential access time = " << difference2 << endl << endl;

    delete [] bools;

    //cin.get();

    return 0;
}
