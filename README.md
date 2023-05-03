# RsaKey-Gen

This is a C++ program that generates RSA keys using the gmp library. It provides a command-line interface (CLI) to generate RSA keys, encrypt and decrypt messages. 

## Dependencies

The program has the following dependencies:

- `gmp library`: You can download it from https://gmplib.org
- C++ compiler

## Getting Started

### Compiling

To compile the project on a Mac M1, use the following command:

```bash
clang++ -I/opt/homebrew/Cellar/gmp/6.2.1_1/include -L/opt/homebrew/Cellar/gmp/6.2.1_1/lib -lgmp -lgmpxx  main.cpp utils/*
```

### Usage

**Generating RSA Keys**:

To generate a key, use the following command:

```bash
❯ ./a.out -h
Rev 0.1a | Last update 09 mar 2022
(c) 2023 Aubertin Emmanuel (aka aTHO_)

RSA
Usage:RSA| [-h | --help] | [-v | --version]  
                -h  Help
                -v  Version
                -s  RSA key gen with bits size

Example : ./RSA -s 1024
```

**CLI Mode**:

To launch the CLI mode, use the `-cli` argument:

```bash
./a.out -cli
```

To see the help in CLI, type `help`:

```bash
>help
Rev 0.1a | Last update 22 mar 2023
(c) 2023 Aubertin Emmanuel (aka aTHO_)

RsaKey cli
Contrl+c for exit
List of all available commands:
        keygen          Generates RSA key
        crypt           Encrypts a message with the current key. You need to generate a key first.
        decrypt         Decrypts a message with the current key. You need to generate a key first.
```

The first step is to generate a key. To do this, use the following command:

```bash
>keygen -s 16
Create New key : 
Key has been created
Compute time for key generation : 0.001092
##############################################
| Key length : 16
|----------------------------------------------
| public key    ==> 583167853
| private key   ==> 100945765
|----------------------------------------------
| Extra info : 
|       n = 1974137141
|       phi(n) = 1974045312
|       p = 57493
|       q = 34337
##############################################
```

You can see the usage of `keygen` with `-h`.

To encrypt and decrypt messages, use the `crypt` and `decrypt` commands respectively. Here is an example:

```bash
>crypt -m jesuisceri
1327030971 1496702623 288121575 1151377270 1755681820 702415140 998537965 221146567 702415140 366773913 1755681820 841717706 221146567 288121575 


>decrypt -m 1327030971 1496702623 288121575 1151377270 1755681820 702415140 998537965 221146567 702415140 366773913 1755681820 841717706 221146567 288121575
-m jesuisceri 
```

## License

This program is licensed under the MIT License. Please see the `LICENSE` file for more details.
