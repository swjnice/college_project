import os
import random
import glob
import enum
import numpy as np

current_dir = os.getcwd()

class Object(enum.Enum):
	APPLE = 0
	AVOCADO = 1
	PAPRI_Y = 2
	POCARI = 3
	PAPRI_R = 4
	COKE = 5
	SPRITE = 6
	G_APPLE = 7
	MUSTARD = 8
	KETCHUP = 9
	MILK = 10
	CIDER = 11
	CANTATA = 12
	CORNTEA= 13
	PRINGLE = 14

####Process

print("object", end="\t")
print("~0.08",end="\t")
print("~0.12",end="\t")
print("~0.16",end="\t")
print("~0.20",end="\t")
print("~0.24",end="\t")
print("~0.28",end="\t")
print("~0.32",end="\t")
print("~0.36",end="\t")
print("~0.4",end="\t")
print("~0.44",end="\t")
print("~0.48",end="\t")
print("0.48~")

for obj in Object:
	list = []
	for f_path in glob.iglob(os.path.join(current_dir, "*.jpg")):
        	title, ext = os.path.splitext(os.path.basename(f_path))
        	list.append(title)      	
	total_cnt = 0
	cnt = np.zeros(12, dtype=float)

	while list:
		name = random.choice(list)
		f = open(name+".txt", "r")
		txtfile = f.readlines()

		for line in txtfile:
			contents = line.split()
			if((int)((float)(contents[0])) == obj.value):	
				total_cnt += 1
				if(float(contents[3])*float(contents[4])<0.0064):
					cnt[0] += 1
				elif(float(contents[3])*float(contents[4])<0.0144):
					cnt[1] += 1
				elif(float(contents[3])*float(contents[4])<0.0256):
					cnt[2] += 1
				elif(float(contents[3])*float(contents[4])<0.04):
					cnt[3] += 1
				elif(float(contents[3])*float(contents[4])<0.0484):
					cnt[4] += 1
				elif(float(contents[3])*float(contents[4])<0.0784):
					cnt[5] += 1
				elif(float(contents[3])*float(contents[4])<0.1024):
					cnt[6] += 1
				elif(float(contents[3])*float(contents[4])<0.1296): 
					cnt[7] += 1
				elif(float(contents[3])*float(contents[4])<0.16): 
					cnt[8] += 1
				elif(float(contents[3])*float(contents[4])<0.1936): 
					cnt[9] += 1	
				elif(float(contents[3])*float(contents[4])<0.2304): 
					cnt[10] += 1				
				else:
					cnt[11] += 1	
		f.close()

		list.remove(name)

	print(obj.name, end="\t")
	if(total_cnt != 0):
		for i in range(12):
			print(format(cnt[i]/total_cnt,"4.2%"),end="\t")
	print()

input("Press Enter to exit...")
