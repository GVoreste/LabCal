import numpy as np
import matplotlib as mtp
import matplotlib.pyplot as plt

X,Y,Yth=np.loadtxt("histoprob.dat",unpack=True)
fig,ax=plt.subplots()
ax.set_title("Confronto istogramma dati-teorico")
ax.set_xlabel("X [m]")
ax.set_ylabel("$P(x)$")
ax.bar(X,Y,label="data",color="orange",alpha=0.5)
ax.bar(X,Yth,label="teorico",alpha=0,edgecolor="red")
ax.legend()
fig.savefig("istogramma.png",dpi=300)

