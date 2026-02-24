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

def encrypt_message(message, sub_tables, key, num_rounds):
    alg_state = [ord(c) for c in message[0:8]]
    for i in range(num_rounds):
        alg_state = [alg_byte ^ key_byte for alg_byte, key_byte in zip(alg_state, key)]
        for j in range(8):
            pass
    pass

def decrypt_message(key, sub_tables, message, num_rounds):
    pass

def run():
    key = key_from_pw("password123")
    sub_tables = get_sub_table_of_tables()
    message = "Let's test to see if this works"
    ciphertext = encrypt_message(message, sub_tables, key, 16)
    print("Ciphertext is " + str(ciphertext))
    decipheredtext = decrypt_message(ciphertext, sub_tables, key, 16)
    print("Decyphered text is " + str(decipheredtext))

run()