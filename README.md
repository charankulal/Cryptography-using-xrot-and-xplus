# Cryptography using XROT and XPLUS algorithm

## Cryptography project built using C by using xrot and xplus algorithm during night-out coding event held at INSIGNIA-2K23, SDMCET Dharwad

## Commands

### To compile

```text
gcc crypt.c -o crypt
```

### To run

The format is

```text
./crypt  <--encrypt or --decrypt> <--xrot or --xplus> <password> <input file> <output file>
```

Example: To  encrypt a message:

```text
./crypt --encrypt --xrot 1234  .\plain.txt .\output.txt  
```
