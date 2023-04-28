# dna-code
This project will read the bytes of a file, and encode each byte into a string representation of a DNA strand, and then encode the DNA strand back into the bytes for of the file


# setup
```bash
make
```


# use
encode a file
```bash
./dna encode sample_data/message.txt
```
output:
```
encoding file: sample_data/message.txt
DNA Encoded string: 
ACCTTTCTAGCTAGCTGGCT
```

decode a file:
```bash
./dna decode decoded_data/decoded_message.txt ACCTTTCTAGCTAGCTGGCT
```
output: 
```
decoding sequence to file decoded_data/decoded_message.txt:
```
