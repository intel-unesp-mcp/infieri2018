#include <iostream>
#include <sstream>
#include <omp.h>

using namespace std;

omp_lock_t lck;

void sum(char* output, const long unsigned int d, const long unsigned int n) {
	long unsigned int digits[d + 11];
	for (long unsigned int digit = 0; digit < d + 11; ++digit) {
		digits[digit] = 0;
	}
       #pragma omp parallel for	
       for (long unsigned int i = 1; i <= n; ++i) {
		long unsigned int remainder = 1;
		for (long unsigned int digit = 0; digit < d + 11 && remainder; ++digit) {
			long unsigned int div = remainder / i;
			long unsigned int mod = remainder % i;
                        omp_set_lock(&lck); 
			digits[digit] += div;
                        omp_unset_lock(&lck); 
			remainder = mod * 10;
		}
	}
	for (long unsigned int i = d + 11 - 1; i > 0; --i) {
		digits[i - 1] += digits[i] / 10;
		digits[i] %= 10;
	}
	if (digits[d + 1] >= 5) {
		++digits[d];
	}
	for (long unsigned int i = d; i > 0; --i) {
		digits[i - 1] += digits[i] / 10;
		digits[i] %= 10;
	}
	stringstream stringstreamA;
	stringstreamA << digits[0] << ".";
	for (long unsigned int i = 1; i <= d; ++i) {
		stringstreamA << digits[i];
	}
	stringstreamA << '\0';
	string stringA = stringstreamA.str();
	stringA.copy(output, stringA.size());
}

int main() {

	long unsigned int d, n;

	cin >> d >> n;

	char output[d + 10]; // extra precision due to possible error
//omp_init_lock(&lck);
omp_init_lock_with_hint(&lck, omp_lock_hint_speculative);
	sum(output, d, n);
omp_destroy_lock(&lck);
	cout << output << endl;

	return 0;
}
