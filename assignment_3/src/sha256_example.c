/*
 * Example program on how to use OpenSSL's SHA256 capabilities.
 * This is mostly useful if you are working in C or C++. Many other languages have built-in ways of creating a SHA256 digest.
 *
 * Author: Wiebe-Marten Wijnja, written for the Information Security course at the Rijksuniversiteit Groningen, 2019.
 *
 * Compile/link this code with the `-lssl -lcrypto` flags, to ensure we can use OpenSSL.
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

#define HEXDIGEST_SIZE 64

char *compute_sha256(char const *str) {
  // Computes the SHA256 hash.
  unsigned char hash[SHA256_DIGEST_LENGTH];
  SHA256_CTX hashing_context;
  SHA256_Init(&hashing_context);
  SHA256_Update(&hashing_context, str, strlen(str));
  SHA256_Final(hash, &hashing_context);

  // Turns the resulting raw byte buffer into a string of 64 hexadecimal characters.
  // (extra 1 char for null terminator!)
  char *hexdigest = malloc(sizeof(char) * (HEXDIGEST_SIZE + 1));
  for(size_t i = 0; i < SHA256_DIGEST_LENGTH; ++i)
    sprintf(hexdigest+2*i, "%.2x", hash[i]);

  return hexdigest;
}

// Example usage:
int main() {
  char *input = "Hello, world!";
  char *hexdigest = compute_sha256(input);
  printf("The hexadecimal SHA256 hash of `%s` is %s\n", input, hexdigest);
  free(hexdigest);
}