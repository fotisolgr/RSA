#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h> // Use of GMP library
 
int main(void)
{
    mpz_t temp1;	//4096 bits number
    mpz_t temp2;    	//4096 bits number
    mpz_t temp3;	//1
    mpz_t temp4;	//-1
    mpz_t p;		//prime p
    mpz_t q;		//prime q
    mpz_t e;        	//65537 for greater security
    mpz_t n;		//n= p*q
    mpz_t pp;		//p -1
    mpz_t qq;		//q-1
    mpz_t fn;       	//(p-1)*(q-1)
    mpz_t rop;	    	//rop=gcd(n,e)
    mpz_t d;        	//65537^(-1) mod fn
    mpz_t pt;       	//plaintext variable
    mpz_t ct;       	//chiphertext variable
   
   
    //Initialize integers

    mpz_init(pt);
    mpz_init(ct);
    mpz_init(p);
    mpz_init(q);
    mpz_init(n);
    mpz_init(e);
    mpz_init(pp);
    mpz_init(qq);
    mpz_init(fn);
    mpz_init(rop);
    mpz_init(d);

    mpz_ui_pow_ui(temp1,2,4096); //RSA-4096 bits  temp1=2^4096
    mpz_ui_pow_ui(temp2,2,4097); //RSA-4096 bits  temp2=2^4097

    mpz_init_set_str(temp3, "1", 10);  // temp3 = 1
    mpz_init_set_str(temp4, "-1", 10); // temp4 = -1


    mpz_nextprime (p, temp1);		    //Find 1st prime number greater than p
    gmp_printf("prime p is:   %Zd\n\n", p); //prime p
    mpz_nextprime (q, temp2);               //Find 1st prime number greater than q
    gmp_printf("prime q is:   %Zd\n\n", q); //prime q

    mpz_init_set_str(e, "65537", 10);

    mpz_mul(n, p, q);
    gmp_printf("n is:   %Zd\n\n", n);       //n=p*q 8192 bits


    mpz_sub(pp, p, temp3);            //pp=p-1
    mpz_sub(qq, q, temp3);            //qq=q-1
    mpz_mul(fn, pp, qq);              //f(n)=(p-1)*(q-1)

    gmp_printf("f(n) is:   %Zd\n\n", fn); //f(n)

    mpz_gcd(rop, n, e);                   //GCD between n & e
    gmp_printf("gcd is:   %Zd\n\n", rop); //gcd

    mpz_powm(d, e, temp4 , fn);           //d= (65537^-1) modn 
    gmp_printf("d is :   %Zd\n\n", d);

    //char plaintext;
    //printf("Enter your plaintext: ");
    //scanf("%s", plaintext);
   
   const char *plaintext = "RSA is one of the first practical public-key cryptosystems and is widely used for secure data transmission. In such a cryptosystem, the encryption key is public and differs from the decryption key which is kept secret. In RSA, this asymmetry is based on the practical difficulty of factoring the product of two large prime numbers, the factoring problem. RSA is made of the initial letters of the surnames of Ron Rivest, Adi Shamir, and Leonard Adleman, who first publicly described the algorithm in 1977. Clifford Cocks, an English mathematician working for the UK intelligence agency GCHQ, had developed an equivalent system in 1973, but it was not declassified until 1997.";

    mpz_import(pt, strlen(plaintext), 1, 1, 0, 0, plaintext); //Convert ASCII characters into integers
    gmp_printf("pt size is:   %Zd\n\n", pt);

    

    if (mpz_cmp(pt, n) > 0)         //Compare plain text with n. If pt>n, RSA encryption is impossible.
    exit(1);
 
    mpz_powm(ct, pt, e, n);	//ct = (pt^65537) mod n
    gmp_printf("Encrypted message:   %Zd\n\n", ct);  //cipher text
 
    mpz_powm(pt, ct, d, n);     //pt = (ct^d) mod n
    gmp_printf("Decrypted message:   %Zd\n\n", pt);  //plain text
 
    char buffer[100000];
    mpz_export(buffer, NULL, 1, 1, 0, 0, pt);
    printf("The actual text is: %s\n\n", buffer);   //Convert integers into ASCII characters
    return 0;
}
