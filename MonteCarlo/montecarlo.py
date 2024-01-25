import numpy as np
import matplotlib as mtp
import matplotlib.pyplot as plt

X,Y,Yth=np.loadtxt("histoprob.dat",unpack=True)
fig,ax=plt.subplots()
ax.set_title("Confronto istogramma dati-teorico")
ax.set_xlabel("X [m]")
ax.set_ylabel("$P(x)$")
width=(X[1]-X[0])
ax.bar(X,Y,label="dati",color="blue",width=width)
ax.bar(X,Yth,color="orange",alpha=0.1,width=width)
ax.bar(X,Yth,label="teorico",fill=False,edgecolor="red",width=width)
ax.legend()
fig.savefig("istogramma.png",dpi=300)

