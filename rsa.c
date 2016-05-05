//RSA.c
//A basic implementation of the RSA encryption protocol.

//Includes
#include <stdio.h>

//Function Prototypes
long encrypt(long message, int e, int n);
long decrypt(long ciphertext, int d, int n);
long modPower(long num, int pow, int mod);
long extGCD(int a, int b, int *s, int *t);
long multInv(int x, int n);

//Main function
int main() {
	int p, q;	//Prime numbers
	int n, e;	//Public key
	int rho, d;	//Private key

	//Hardcoded sample prime numbers
	//Easy to bruteforce; don't use these for anything secret!
	p = 5;
	q = 11;
	e = 37;

	//Calculate public key
	n = p * q;

	//Calculate private key
	rho = (p-1) * (q-1);
	d = multInv(e, rho);

	//Display values
	printf("Using primes: p=%d, q=%d\n", p, q);
	printf("Public key: e=%d, N=%d\n", e, n);
	printf("Private key: d=%d\n", d);

	//Main menu
	long input = 0;
	printf("Enter number to encrypt/decrypt: ");
	scanf("%lld", &input);
	if(input >= n) {
		printf("Input number too large!\n");
		printf("Message must be less than N.\n");
		return 0;
	}
	printf("RSA encrypted message: %ld\n", encrypt((long)input, e, n));
	printf("RSA decrypted message: %ld\n", decrypt((long)input, d, n));

	return 0;
}

//Encrypt a numeric message with RSA
long encrypt(long message, int e, int n) {
	return modPower(message, e, n);
}

//Decrypt a numeric message with RSA
long decrypt(long ciphertext, int d, int n) {
	return modPower(ciphertext, d, n);
}

//Recursive integer modular exponentiation function
long modPower(long num, int pow, int mod) {
	if(pow == 1) {
		return num;
	}

	//Mod at each level prevents integer overflow
	return ((num % mod) * (modPower(num, pow - 1, mod) % mod)) % mod;
}

//Calculate greatest common divisor (extended Euclidean algorithm)
long extGCD(int a, int b, int *s, int *t) {
	if(a == 0) {
		*s = 0;
		*t = 1;
		return b;
	}

	int stmp = 0;
	int ttmp = 0;
	long gcd = extGCD(b % a, a, &stmp, &ttmp);
	*s = ttmp - (b/a)*stmp;
	*t = stmp;

	return gcd;
}

//Calculate multiplicative inverse of x mod(n)
long multInv(int x, int n) {
	int s = 0;
	int t = 0;
	int gcd = extGCD(x, n, &s, &t);

	if(gcd != 1) {
		printf("Multiplicative inverse of %d mod %d does not exist! Exiting.\n", x, n);
	}

	//Handle negative values
	return ((s % n) + n) % n;
}
