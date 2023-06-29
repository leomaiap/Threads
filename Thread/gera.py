import random
f1=open('a_d.in', 'w')
for i in range(2000): f1.write(str(random.uniform(-10,+10))+'\n')
#for i in range(2000): f1.write(str(1)+'\n')
f1.close()