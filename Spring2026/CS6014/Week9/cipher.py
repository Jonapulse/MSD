import random

##########################
## (bad) block cipher   ##
##########################

#pw is a string
def key_from_pw(pw):
    key = [0] * 8
    for i, char in enumerate(pw):
        key[i % 8] ^= ord(pw[i])
    return key

def get_sub_table_of_tables():
    sub_table_of_tables = []
    for i in range(8):
        subs = []
        for i in range(256):
            subs.append(i)
        subs = fisher_yates_shuffle(subs)
        sub_table_of_tables.append(subs)
    return sub_table_of_tables

def fisher_yates_shuffle(arr):
    """
    Shuffles an array in-place using the Fisher-Yates algorithm.
    """
    n = len(arr)
    # Iterate from the last element down to the second (index 1)
    for i in range(n - 1, 0, -1):
        # Pick a random index 'j' from 0 to 'i' inclusive
        j = random.randint(0, i)
        # Swap the element at the current index 'i' with the element at index 'j'
        arr[i], arr[j] = arr[j], arr[i]
    return arr

def bitshift_wrap(data, goLeft):
    n = int.from_bytes(data, byteorder='big')
    bit_count = len(data) * 8
    if goLeft:
        shifted = ((n << 1) | (n >> (bit_count - 1))) & ((1 << bit_count) - 1) #the & gives us a 64-bit mask of 1s to trim back down to the original size of data
    else: 
        shifted = ((n >> 1) | (n << (bit_count - 1))) & ((1 << bit_count) - 1)
    return list(shifted.to_bytes(len(data), byteorder='big'))

def encrypt_message(message, sub_tables, key, num_rounds):
    alg_state = [ord(c) for c in message[0:8]]
    for round in range(num_rounds):
        #xor with key
        alg_state = [alg_byte ^ key_byte for alg_byte, key_byte in zip(alg_state, key)] 
        #substitute from table
        for i in range(8):
            alg_state[i] = sub_tables[i][alg_state[i]] 
        #rotate state 1 bit to the left
        alg_state = bitshift_wrap(alg_state, True)
    ciphertext = ""
    for c in alg_state:
        ciphertext += chr(c)
    return ciphertext; #this only works for the first 8 characters. I think I'd need to do repeat every 8 chars to make this a true blue cipher? And we're intentionally not changing the key?

def decrypt_message(ciphertext, sub_tables, key, num_rounds):
    alg_state = [ord(c) for c in ciphertext[0:8]]
    for round in range(num_rounds):
        #rotate state 1 bit to the right
        alg_state = bitshift_wrap(alg_state, False)
        #substitute backwards from table
        for i in range(8):
            alg_state[i] = sub_tables[i].index(alg_state[i])
        #xor with key
        alg_state = [alg_byte ^ key_byte for alg_byte, key_byte in zip(alg_state, key)] 
    plaintext = ""
    for c in alg_state:
        plaintext += chr(c)
    return plaintext

##########################
##       RC4            ##
##########################

#There are much better ways than global vars to do this, but I've never seen professional 
#python code and this is how I wrote it before consulting a robot, so... Next time.
rc4Table = []
rc4_i = 0
rc4_j = 0

#key is a string, typically 5 to 16 bytes
def initializeRC4(key):
    global rc4Table, rc4_i, rc4_j
    rc4Table = list(range(256))
    j = 0
    for i in range(256):
        j = (j + rc4Table[i] + ord(key[i % len(key)])) % 256
        rc4Table[i], rc4Table[j] = rc4Table[j], rc4Table[i]
    rc4_i = 0
    rc4_j = 0

def next_byte():
    global rc4Table, rc4_i, rc4_j 
    rc4_i = (rc4_i + 1) % 256
    rc4_j = (rc4_j + rc4Table[rc4_i]) % 256
    rc4Table[rc4_i], rc4Table[rc4_j] = rc4Table[rc4_j], rc4Table[rc4_i]
    return rc4Table[(rc4Table[rc4_i] + rc4Table[rc4_j]) % 256] 

def encryptOrDecryptRC4(message, key):
    initializeRC4(key)
    rc4ByteStream = ""
    for c in message:
        rc4ByteStream += chr(next_byte())
    return xorStrings(message, rc4ByteStream)

#returns xored string the length of smaller string
def xorStrings(s1, s2):
    xored = ""
    for i in range(min(len(s1), len(s2))):
        xored += chr(ord(s1[i]) ^ ord(s2[i]))
    return xored

##########################
##    running the HW    ##
##########################
def run():

    ##Bad block 
    key = key_from_pw("password123")
    sub_tables = get_sub_table_of_tables()
    message = "Hello Mr"
    ciphertext = encrypt_message(message, sub_tables, key, 16)
    print("Ciphertext is " + ciphertext)
    decipheredtext = decrypt_message(ciphertext, sub_tables, key, 16)
    print("Decyphered text is " + decipheredtext)

    # one-bit check
    ciphertextbitflip = ciphertext[:4] + chr(ord(ciphertext[4]) ^ 128) + ciphertext[5:]
    print(ciphertextbitflip)
    print("Decyphered text with one bit flipped is " + decrypt_message(ciphertextbitflip, sub_tables, key, 16))

    ##RC4
    rc4Message = "Hello, how are you?"
    print("RC4 time!\n\tMessage: \"" + rc4Message + "\"")
    sharedKey = "Kablooey!"
    rc4Ciphered = encryptOrDecryptRC4(rc4Message, sharedKey)
    rc4Deciphered = encryptOrDecryptRC4(rc4Ciphered, sharedKey)
    rc4DecipheredWrongKey = encryptOrDecryptRC4(rc4Ciphered, "fake")
    print("\tIt encrypts to: \"" + rc4Ciphered + "\" which decrypts to \"" + rc4Deciphered 
          + "\" or, with wrong key \"fake\": \"" + rc4DecipheredWrongKey + "\"")
    
    
    ##RC4 - key re-use danger
    zeroMask = ""
    for i in range(len(rc4Message)):
        zeroMask += chr(0)
    rc4CipheredOneMask = encryptOrDecryptRC4(zeroMask, sharedKey)
    print("Xoring with zeroes: " + xorStrings(zeroMask, rc4Message))
    print("Xoring our ciphered onemask with same key message: \"" + xorStrings(rc4Ciphered, rc4CipheredOneMask))
    # #Oh that is effective

    ##RC4 - integrity attack
    salaryString = "Your salary is $1000"
    targetedAttack = ""
    for i in range(16):
        targetedAttack += chr(0)
    targetedAttack += chr(8)
    for i in range(3):
        targetedAttack += chr(9)
    print("Xoring with our attack: " + xorStrings(salaryString, targetedAttack))
    newKey = "password123"
    cipheredSalary = encryptOrDecryptRC4(salaryString, newKey)
    attackedCipheredSalary = xorStrings(cipheredSalary, targetedAttack)
    print("Decrypted message: " + encryptOrDecryptRC4(cipheredSalary, newKey) 
          + "\nDecrypted attacked message: " + encryptOrDecryptRC4(attackedCipheredSalary, newKey))
    #Well, dang.

run()