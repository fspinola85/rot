# ROT
Ceaser Cipher encryption/decryption

# Install - Linux
$ git clone https://github.com/fspinola85/ROT.git<br>
$ cd ROT<br>
$ gcc rot.c -o rot<br>

# Install - Windows
1. Download the zip file: https://github.com/fspinola85/ROT/archive/master.zip
2. Extract the content from the zip
3. Compile the C file using gcc compiler (Download: https://osdn.net/projects/mingw/downloads/68260/mingw-get-setup.exe)
4. Execute using cmd or powershell:
    > .\rot.exe
    
# Usage
./rot -f tester.txt -r 5 -e<br>
./rot -d -m "cxqmfq qaoelcg gtuf iqel nqmhgurhx yqffmsq, 274." -r 12<br>

# Help Page
Commands:<br>
        -r, --rotate [NUMBER]           Define the rotation number.<br>
        -h, --help                      Show this help page.<br>
        -m, --message [MESSAGE]         Specify the message you want to encrypt or decrypt.<br>
        -e, --encrypt                   Use encrypt mode.<br>
        -d, --decrypt                   Use decrypt mode.<br>
        -v, --version                   Show the version.<br>
        -f, --file [FILENAME]           Specify the input file you want to encrypt or decrypt<br>

# Release Notes
1.0 (04/10/2020)
- Encrypt/Decrypt any message
- Encrypt/Decrypt any text from an input file
- Allows rotation value customization
