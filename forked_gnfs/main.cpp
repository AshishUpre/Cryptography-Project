#include <iostream>
#include <NTL/ZZ.h>
#include <NTL/RR.h>
#include <NTL/ZZX.h>
#include <NTL/ZZXFactoring.h>
#include <vector>
#include <NTL/mat_GF2.h>
#include <fstream>
#include <gmpxx.h>

#include "GNFS.h"

// #define TEST

using namespace NTL;
using namespace std;

int main(int argc, char *argv[])
{
    try
    {

#ifdef TEST

        std::string filename = "test.csv";
        std::ofstream myfile;
        myfile.open(filename);
        myfile << "exp,time,\n";
        ZZ x, y, factor;
        for (long i = 1L; i <= 10; ++i)
        {
            if (i == 1L)
            {
                x = 50;
            }
            else
            {
                x = NextPrime(power(ZZ(10L), i));
            }
            y = NextPrime(10 * power(ZZ(10L), i));
            auto start = std::chrono::system_clock::now();
            for (long j = 0; j < 5; ++j)
            {
                x = NextPrime(x + 1);
                y = NextPrime(y + 1);
                factor = GNFS(x * y);
                std::cout << "**********************************************************************************\n"
                          << factor << " * " << x * y / factor << " = " << x * y << "\n"
                          << "**********************************************************************************\n";
            }
            auto diff = std::chrono::system_clock::now() - start;
            auto sec = std::chrono::duration_cast<std::chrono::seconds>(diff);
            myfile << i << "," << sec.count() << ",\n";
            std::cout << i << " : " << sec.count() << "\n\n";
        }
        myfile.close();

#endif

#ifndef TEST
        if (argc != 2)
        {
            std::cerr << "Usage: " << argv[0] << " <number>" << std::endl;
            return 1;
        }
        if (argc > 1)
        {
            mpz_class bignum(argv[1]);
            ZZ n(atoll(argv[1])), factor;

            // gmp_printf("bignum : %Zd\n", bignum);
            std::cout << "number : " << n << std::endl;
            auto start = std::chrono::system_clock::now();

            factor = GNFS(n);

            cout << "fact : " << factor << endl
                 << "fact : " << n / factor << endl;

            auto diff = std::chrono::system_clock::now() - start;
            auto millisec = std::chrono::duration_cast<std::chrono::milliseconds>(diff);
            std::cout << "\nduration: " << millisec.count() << " milliseconds" << std::endl;
        }

#endif
    }
    catch (const char *e)
    {
        std::cerr << e;
    }

    return 0;
}