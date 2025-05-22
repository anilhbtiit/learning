Enc:
openssl enc -bf -in plaintext.txt -out encrypted.txt -k mypassword
Dec:
openssl enc -bf -d -in encrypted.txt -out decrypted.txt -k mypassword
