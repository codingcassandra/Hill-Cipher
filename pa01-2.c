// Assignment: pa01 - Encrypting a plaintext file using the Hill cipher

// Author: Cassandra Morales
// Language: c

// To compile: 

// To Execute: c -> ./pa01 kX.txt pX.txt

// Class: CIS3360 - Security in Computing - Spring 2024
// Instructor: McAlpin
// Due Date: 2/25/24


#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
# define MAX 10

// reading in key matrix
void readKey(FILE *keyFile, int *n, int keyMatrix[MAX][MAX])
{
	fscanf(keyFile, "%d", n);
	
	for (int i = 0; i < *n; i++)
	{
		for (int j = 0; j < *n; j++)
		{
			fscanf(keyFile, "%d", &keyMatrix[i][j]);
		}
	}
}

// filtering plaintext
void readPlain(FILE *plaintextFile, char *plaintext)
{
	char c;
	int index = 0;
	
	while ((c = fgetc(plaintextFile)) != EOF)
	{
		if (isalpha(c))
		{
			plaintext[index++] = tolower(c);
		}
	}
	
	plaintext[index] = '\0';
}

// adding padding to plaintext
void pad(char *plaintext, int blockSize)
{
	int length = strlen(plaintext);
	int paddingLength = blockSize - (length % blockSize);
	
	for (int i = 0; i < paddingLength; i++)
		plaintext[length + i] = 'x';
		
	plaintext[length + paddingLength] = '\0';
}

void printPlain(char *plaintext)
{
	printf("Plaintext:\n%s\n", plaintext);
}

//creating key matrix
void printKey(int n, int keyMatrix[MAX][MAX])
{
	printf("Key matrix:\n");
	for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", keyMatrix[i][j]);
        }
        printf("\n");
    }
}

//producing hill cipher
void encrypt(char *plaintext, int keyMatrix[MAX][MAX], int n) 
{
  int length = strlen(plaintext);

  for (int i = 0; i < length; i += n) 
  {
    int sum[n];

    for (int j = 0; j < n; j++) 
    {
      sum[j] = 0;
      for (int k = 0; k < n; k++) 
      {
        sum[j] += keyMatrix[j][k] * (plaintext[i + k] - 'a');
      }
    }

    // Calculate encrypted value for each character in the block
    for (int j = 0; j < n; j++) 
    {
      plaintext[i + j] = (sum[j] % 26 + 26) % 26 + 'a';
    }
  }
}

int main(int argc, char **argv)
{
    // reading in files 
	FILE *plaintextFile, *keyFile;
	char *key, *plaintext, *ciphertext;
	int n, keyMatrix[MAX][MAX];
	
	if (((keyFile = fopen(argv[1], "r")) == NULL))
    {
        fprintf(stderr, "Could not open %s\n", argv[1]);
        exit(1);
    }
    if (((plaintextFile = fopen(argv[2], "r")) == NULL))
    {
        fprintf(stderr, "Could not open %s\n", argv[2]);
        exit(1);
    }
    
    // Read key matrix
    readKey(keyFile, &n, keyMatrix);
    fclose(keyFile);

    // Allocate memory for plaintext
    plaintext = malloc(sizeof(char) * 10000);

    // Read plaintext
    readPlain(plaintextFile, plaintext);
    fclose(plaintextFile);

    // Pad plaintext
    pad(plaintext, n);

    // Print key matrix and plaintext
    printKey(n, keyMatrix);
    printf("\n");
    printPlain(plaintext);
	  printf("\n");
	
    // Encrypt plaintext
    encrypt(plaintext, keyMatrix, n);

    // Print encrypted text
    int length = strlen(plaintext);
    printf("Encrypted Text:\n");
    for (int i = 0; i < length; i++)
    {
        if (i % 80 == 0 && i != 0)
            printf("\n");
        printf("%c", plaintext[i]);
    }
    printf("\n");


    // Free allocated memory
    free(plaintext);
	
	return 0;    
}
// I Cassandra Morales 4951701 affirm that this program is entirely my own work and that I have neither developed my code together with any other person, 
// nor copied any code from any other person, nor permitted my code to be copied or otherwise used by any other person, nor have I copied, modified, or
// otherwise use programs created by others. I acknowledge that any violation of the above terms will be treated as academic dishonesty.


