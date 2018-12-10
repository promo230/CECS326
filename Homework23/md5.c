/* to compile: gcc -Wall md5.c -lssl */
#include <string.h> /* strlen */
#include <stdio.h> /* printf */
#include <openssl/evp.h> /* md5 hash */
int main(int argc, char* argv[])
{
  /* Digest variables */
  EVP_MD_CTX md_context;
  const EVP_MD* md = EVP_md5();
  unsigned int md_length;
  unsigned char md_value[EVP_MAX_MD_SIZE];
  int i; /* loop variable */

  /* Initialise the digest */
  EVP_DigestInit(&md_context, md);

  /* Feed data into the digest */
  EVP_DigestUpdate(&md_context, argv[1], strlen(argv[1]));

  /* Get the digest and it's length */
  EVP_DigestFinal(&md_context, md_value, &md_length);

  /* Print the result */
  for (i = 0; i < md_length; i++)
  {
    printf("%x",md_value[i]);
  }
  printf("\n");
  return 0;
}
