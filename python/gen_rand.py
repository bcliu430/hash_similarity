from random import *

def gen_rand():
    item = []

    for x in range(0,10):
        item.append(random())

    for i in item:
        print (i)

    shuffle(item)

    for i in item:
        print(i)


if __name__ == '__main__':
    gen_rand()
