#include <stdio.h>
#include <gmp.h>
#include <time.h>
#include <bits/stdc++.h>
#include <chrono>
#include <omp.h>
using namespace std;

void parallelPrimeFactors(mpz_t num)
{
	mpz_t temp, numby2;
	mpz_init(temp);
	mpz_init(numby2);
	mpz_divexact_ui(numby2, num, 2);

#pragma omp parallel
	{
		while (mpz_even_p(num))
		{
#pragma omp critical
			{
				printf("fact : 2\n");
				mpz_divexact_ui(num, num, 2); // num = num / 2
			}
		}

		mpz_set_ui(temp, 3); // temp=3

		while (mpz_cmp(temp, numby2) < 0) // while temp++ < num/2
		{
#pragma omp critical
			// gmp_printf("temp : %Zd\n", temp);
			if (mpz_divisible_p(num, temp))
			{
#pragma omp critical

				gmp_printf("fact : %Zd\n", temp);
				mpz_divexact(num, num, temp);
				gmp_printf("fact : %Zd\n", num);
				break;
			}
			mpz_divexact_ui(numby2, num, 2);
			mpz_add_ui(temp, temp, 2);
#pragma omp barrier
		}

		if (mpz_cmp_ui(num, 2) > 0)
#pragma omp critical
			gmp_printf("fact : %Zd\n", num);
	}

	mpz_clear(temp);
}

int main()
{
	mpz_t a;
	mpz_init(a);

	gmp_randstate_t state;
	gmp_randinit_default(state);
	gmp_randseed_ui(state, time(NULL));

	// Generate random numbers with some size
	int bits;
	// cout << "enter number of bits : ";
	// cin >> bits;

	auto start = chrono::steady_clock::now();

	mpz_urandomb(a, state, bits);
	mpz_set_str(a, "999999440000031311", 10);
	// gmp_printf("Generated num : %Zd\n", a);
	parallelPrimeFactors(a);

	auto end = std::chrono::steady_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

	cout << "Runtime: " << duration << " milliseconds" << endl;
	return 0;
}
