from PIL import Image

sen = '/home/wonjae/Desktop/GP/Mergetest/image/coke_1.png\n'
sen.rstrip('\n')

print(sen)
s = Image.open(sen)
s.show()
