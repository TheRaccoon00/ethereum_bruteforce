# Ethereum bruteforce

Easy bruteforce ethereum wallet

## Requirements

Minimum:
+ [python3](https://www.python.org/)
+ [gcc](https://gcc.gnu.org/)
+ [linux](https://www.gnu.org/home.fr.html)
+ make

Python libraries required:
+ pip3 install coincurve
+ pip3 install pysha3

## Compilation

```
make
```

## Prep

Add your wordlists **in .txt format** in the folder:
```
./wordlists/
```

## Usage

Bruteforce targets from wordlists **previoulsy added**
```
./lets_crack [TARGETS_FILE] --reset
```

Bruteforce targets from wordlists **previoulsy added**, and display balance on the wallet (limited API !)
```
./lets_crack [TARGETS_FILE] --reset --balance
```

## Example

An example is available with some indian cities with the results in the "results" folder.

## Warning

**This project is only for FUN. Do not steal anything from any wallets you find. Be respectful.**
