import sys
import os
import string
import getopt
import random
import urllib.request as urq


def random_letters(amount):
    length_of_word = random.randint(3, 11)
    word = ''
    text = ''
    while len(text) < amount:
        for i in range(length_of_word):
            word += random.choice(string.ascii_letters)
        text += ' ' + word
    if len(text) > amount:
        text = text[:-(len(text) - amount)]
    return text


def random_words(amount):
    url = 'http://svnweb.freebsd.org/csrg/share/dict/words?view=co&content-type=text/plain'
    resp = urq.urlopen(url)
    words = resp.read().decode()
    words = words.splitlines()
    text = ''
    while len(text) < amount:
        text += ' ' + random.choice(words)
    if len(text) > amount:
        text = text[:-(len(text) - amount)]
    return text


def common_letters(text1, text2):
    count = 0
    for letter1, letter2 in zip(text1, text2):
        if (letter1.lower() == letter2.lower()):
            count += 1
    return count

def percentage_of_matching(text1, text2):
    return common_letters(text1, text2) / len(text1)

def first_var():
    print("1. Two meaningful natural language texts.")
    #Title: The Early Short Fiction of Edith Wharton, Part 1 (of 10)
    #Author: Edith Wharton
    url1 = 'http://www.gutenberg.org/files/295/295-0.txt'
    #Title: Heart of Darkness
    #Author: Joseph Conrad
    url2 = 'http://www.gutenberg.org/files/219/219-0.txt'
    resp = urq.urlopen(url1)
    text1 = resp.read().decode()
    resp = urq.urlopen(url2)
    text2 = resp.read().decode()
    matches = 0
    if (len(text1) > len(text2)):
        text1 = text1[:len(text2)]
    else:
        text2 = text2[:len(text1)]
    matches = percentage_of_matching(text1, text2)
    print("Text length: {0}".format(len(text1)))
    print("Match: {0}".format(matches))


def second_var():
    print("2. Meaningful text and text from random letters.")
    url1 = 'http://www.gutenberg.org/files/295/295-0.txt'
    resp = urq.urlopen(url1)
    text1 = resp.read().decode()
    matches = 0
    text2 = random_letters(len(text1))
    with open('/Users/linuxoid/Desktop/VUZICH/CRYPTO/lab4/tests/second_var_text_2', 'w') as file:
        file.write(text2)
    matches += percentage_of_matching(text1, text2)
    print("Text length: {0}".format(len(text1)))
    print("Match: {0}".format(matches))


def third_var():
    print("3. Meaningful text and text from random words.")
    url1 = 'http://www.gutenberg.org/files/295/295-0.txt'
    resp = urq.urlopen(url1)
    text1 = resp.read().decode()
    matches = 0
    number_of_texts = 1
    text2 = random_words(len(text1))
    with open('/Users/linuxoid/Desktop/VUZICH/CRYPTO/lab4/tests/third_var_text_2', 'w') as file:
        file.write(text2)
    matches += percentage_of_matching(text1, text2)
    print("Text length: {0}".format(len(text1)))
    print("Match: {0}".format(matches))


def fourth_var():
    print("4. Two texts from random letters.")
    matches = 0
    length_of_text = 10 ** 6
    text1 = random_letters(length_of_text)
    with open('/Users/linuxoid/Desktop/VUZICH/CRYPTO/lab4/tests/fourth_var_text1', 'w') as file:
        file.write(text1)
    text2 = random_letters(length_of_text)
    with open('/Users/linuxoid/Desktop/VUZICH/CRYPTO/lab4/tests/fourth_var_text2', 'w') as file:
        file.write(text2)
    matches += percentage_of_matching(text1, text2)
    print("Text length: {0}".format(length_of_text))
    print("Match: {0}".format(matches))


def fifth_var():
    print("5. Two texts from random words.")
    matches = 0
    length_of_text = 10 ** 6
    text1 = random_words(length_of_text)
    with open('/Users/linuxoid/Desktop/VUZICH/CRYPTO/lab4/tests/fifth_var_text1', 'w') as file:
        file.write(text1)
    text2 = random_words(length_of_text)
    with open('/Users/linuxoid/Desktop/VUZICH/CRYPTO/lab4/tests/fifth_var_text2', 'w') as file:
        file.write(text2)
    matches += percentage_of_matching(text1, text2)
    print("Text length: {0}".format(length_of_text))
    print("Match: {0}".format(matches))


if __name__ == '__main__':

    first_var()
    second_var()
    third_var()
    fourth_var()
    fifth_var()
