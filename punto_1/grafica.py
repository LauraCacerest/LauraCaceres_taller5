from numpy import *
import matplotlib.pyplot as plt

D = genfromtxt("datos_placas.txt", delimiter=',')
II = ~any(isnan(D),0)
D = D[:,II] # Quitar Nans

print(shape(D))
n = int(size(D,0)/3)
II,JJ = meshgrid(linspace(0,n,n),linspace(0,n,n))


f = plt.figure()
plt.contourf(II,JJ,D[:n,:], 20)
plt.colorbar()
plt.streamplot(II,JJ,D[n:2*n,:],D[2*n:,:], 1.2)
plt.xlabel('x')
plt.ylabel('y')
f.savefig('placas.pdf')