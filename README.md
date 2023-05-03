# RsaKey-Gen

RSA key generator in C++ using gmp library.

## Dependecies

Here is the list of all dependecies :

`gmp lib` : see https://gmplib.org
C++ compiler.

## Get started

### Compile
This porject has devolped on a Mac M1. Here is the line to compile the project :

```bash
clang++ -I/opt/homebrew/Cellar/gmp/6.2.1_1/include -L/opt/homebrew/Cellar/gmp/6.2.1_1/lib -lgmp -lgmpxx  main.cpp utils/*

```

### Usage

**Generate a key** :
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

**CLI mode** :

To launch the CLI mode you just need to use the `-cli`arg :
```bash
./a.out -cli
```

To see the help in CLI you just need to write help :
``bash
>help
Rev 0.1a | Last update 22 mar 2023
(c) 2023 Aubertin Emmanuel (aka aTHO_)


RsaKey cli
Contrl+c for exit
List of all avaible commande :
        keygen          Generation of RSA key
        crypt           crypt a message with the current key. You need to do keygen before.
        decrypt         decrypt a message with the current key. You need to do keygen before.
```
The step is to gen a key, soo for that you just need to do :
```
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
You can see usage of keygen with `-h`

For crypt and decrypt you must do like that :
```

>crypt -m jesuisceri
1327030971 1496702623 288121575 1151377270 1755681820 702415140 998537965 221146567 702415140 366773913 1755681820 841717706 221146567 288121575 


>decrypt -m 1327030971 1496702623 288121575 1151377270 1755681820 702415140 998537965 221146567 702415140 366773913 1755681820 841717706 221146567 288121575
-m jesuisceri 
```


