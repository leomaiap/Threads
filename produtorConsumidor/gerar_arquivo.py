import random

def matriz(x, nome):
    nome = nome + str(x) + '.out'
    f2 = open(nome, 'w')
    for i in range(10):
        for j in range(9):
            f2.write(str(random.uniform(-10,+10))+' ')
        f2.write(str(random.uniform(-10,+10))+'\n')
    f2.close   


QUANTIDADE = 50
nome = 'm'

f1=open('entrada.in', 'w')
for i in range(QUANTIDADE):
    f1.write(nome+str(i)+'.in'+'\n')
    matriz(i, nome)
f1.close()
