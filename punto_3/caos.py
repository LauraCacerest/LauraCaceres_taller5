from numpy import *
import numpy as np
import matplotlib.pyplot as plt
#from matplotlib import animation


D = genfromtxt("datos_caos.txt", delimiter=' ')
#II = ~any(isnan(D),0)
#D = D[:,II] # Quitar Nans

print(shape(D))


#ymax = max(np.max(abs(D),0))
#
#dc = 1.0/(np.size(D,0)-1);
#
#def plotear_1(i):
	#plotcolor = (0.2,0.2,dc*i);
	#plt.cla()
	#if i > 3:
		#plotcolor2 = (0.2,0.2,dc*(i-2))
		#plt.plot(D[i-2,:], '.-', lw=2, c=plotcolor2, alpha=0.3)
	#plt.plot(D[i,:], '.-', lw=2, c=plotcolor)
	#plt.ylim([-ymax,ymax])
#	
#fig = plt.figure(figsize=(12,8))
#
#anim = animation.FuncAnimation(fig, plotear_1, frames=200, interval=200)
#anim.save('cuerda.gif', dpi=40, writer='imagemagick')