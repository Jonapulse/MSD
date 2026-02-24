import random

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

def run():
    key = key_from_pw("password123")
    sub_tables = get_sub_table_of_tables()
    message = "Hello Mr"
    ciphertext = encrypt_message(message, sub_tables, key, 16)
    print("Ciphertext is " + str(ciphertext))
    decipheredtext = decrypt_message(ciphertext, sub_tables, key, 16)
    print("Decyphered text is " + str(decipheredtext))

run()