import numpy as np
import matplotlib.pyplot as plt

f=open("final.txt","r")
l=f.readlines()
pix=[]
for i in range(len(l)):
    li=[int(x) for x in l[i].split(", ")[:-1]]
    pix.append(li)

pix=np.array(pix)
print(pix.shape)
print(pix)
plt.imshow(pix, cmap="gray") 
plt.show() 