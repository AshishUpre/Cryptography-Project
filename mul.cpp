#include <gmp.h>
#include <iostream>

int main()
{
	mpz_t a, b, ans;
	mpz_inits(a, b, ans, NULL);			   // terminate with null
	mpz_set_str(a, "100123456789", 10);	   // Set base to 10
	mpz_set_str(b, "347811194367163", 10); // Set base to 10
	mpz_mul(ans, a, b);
	gmp_printf("mul ans : %Zd\n", ans);
	mpz_clears(a, b, ans, NULL);

	if (mpz_millerrabin(ans, 40))
	{
		gmp_printf("%Zd is prime\n");
	}
	return 0;
}
