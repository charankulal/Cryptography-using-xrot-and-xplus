#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void xrot_encrypt(char *input, char *password, char *output)
{
    int len_input = strlen(input);
    int len_password = strlen(password);
    char *encrypted = malloc((len_input + 1) * sizeof(char));

    for (int i = 0; i < len_input; i++)
    {
        int shift = password[i % len_password] - '0';

        encrypted[i] = (input[i] + shift) % 256;
    }
    encrypted[len_input] = '\0';

    FILE *fp = fopen(output, "wb");
    fwrite(encrypted, sizeof(char), len_input, fp);
    fclose(fp);
    printf("\n\nEncryption completed.\n\n");
    printf("\n\nNumber of bytes modified. %d\n\n",len_input);

    free(encrypted);
}

void xrot_decrypt(char *input, char *password, char *output)
{
    int len_input = strlen(input);
    int len_password = strlen(password);
    char *decrypted = malloc((len_input + 1) * sizeof(char));

    for (int i = 0; i < len_input; i++)
    {
        int shift = password[i % len_password] - '0';
     
        decrypted[i] = (input[i] - shift + 256) % 256;
    }
    decrypted[len_input] = '\0';

    FILE *fp = fopen(output, "wb");
    fwrite(decrypted, sizeof(char), len_input, fp);
    printf("\n\nDecryption completed.\n\n");
    printf("\n\nNumber of bytes modified. %d\n\n",len_input);
    fclose(fp);

    free(decrypted);
}

void xplus_encrypt(char *input, char *password, char *output)
{
    int len_input = strlen(input);
    int len_password = strlen(password);
    char *encrypted = malloc((len_input + 1) * sizeof(char));

    for (int i = 0; i < len_input; i++)
    {

        int key = (password[i % len_password] - '0') * i;

        encrypted[i] = (input[i] + key) % 256;
    }
    encrypted[len_input] = '\0';

    FILE *fp = fopen(output, "wb");
    fwrite(encrypted, sizeof(char), len_input, fp);
    printf("\n\nEncryption completed.\n\n");
    printf("\n\nNumber of bytes modified. %d\n\n",len_input);
    fclose(fp);

    free(encrypted);
}

void xplus_decrypt(char *input, char *password, char *output)
{
    int len_input = strlen(input);
    int len_password = strlen(password);
    char *decrypted = malloc((len_input + 1) * sizeof(char));

    for (int i = 0; i < len_input; i++)
    {

        int key = (password[i % len_password] - '0') * i;

        decrypted[i] = (input[i] - key + 256) % 256;
    }
    decrypted[len_input] = '\0';

    FILE *fp = fopen(output, "wb");
    fwrite(decrypted, sizeof(char), len_input, fp);
    printf("\n\nDecryption completed.\n\n");
    printf("\n\nNumber of bytes modified. %d\n\n",len_input);
    fclose(fp);

    free(decrypted);
}

int main(int argc, char *argv[])
{
    if (argc != 6)
    {
        printf("\n\nUsage should be: %s --xrot or --xplus <encrypt or decrypt> <password> <input file> <output file>\n\n", argv[0]);
        return 1;
    }

    char *operation = argv[1];
    char *algorithm = argv[2];
    char *password = argv[3];

    for (int i = 0; i < strlen(password); i++)
    {
        if (!isdigit(password[i]))
        {
            printf("\n\nError: Password should only contain digits.\n\n");
            return 1;
        }
    }
    if (strlen(password)!=4)
    {
        printf("\n\nError: Password should only 4 digits.\n\n");
        return 1;
    }

    char *input_file = argv[4];
    char *output_file = argv[5];

    FILE *fp = fopen(input_file, "rb");
    if (fp == NULL)
    {

        printf("\n\nError: Cannot open input file.\n\n");
        return 1;
    }

    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    char *input_data = malloc((file_size + 1) * sizeof(char));
    fread(input_data, sizeof(char), file_size, fp);
    fclose(fp);
    input_data[file_size] = '\0';
    if (strcmp(algorithm, "--xrot") == 0)
    {
        if (strcmp(operation, "--encrypt") == 0)
        {
            xrot_encrypt(input_data, password, output_file);
            
        }
        else if (strcmp(operation, "--decrypt") == 0)
        {
            xrot_decrypt(input_data, password, output_file);
            // printf("\n\nDecryption completed.\n\n");
        }
        else
        {
            printf("\n\nInvalid operation. Use '--encrypt' or '--decrypt'.\n\n");
            return 1;
        }
    }
    else if (strcmp(algorithm, "--xplus") == 0)
    {
        if (strcmp(operation, "--encrypt") == 0)
        {

            xplus_encrypt(input_data, password, output_file);
            // printf("\n\nEncryption completed.\n\n");
        }
        else if (strcmp(operation, "--decrypt") == 0)
        {
            xplus_decrypt(input_data, password, output_file);
            // printf("\n\nDecryption completed.\n\n");
        }
        else
        {
            printf("\n\nInvalid operation. Use '--encrypt' or '--decrypt'.\n\n");
            return 1;
        }
    }
    else
    {
        printf("\n\nInvalid algorithm. Use '--xrot' or '--xplus.\n\n");
        return 1;
    }
    free(input_data);
    return 0;
}