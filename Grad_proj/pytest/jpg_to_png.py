from PIL import Image

input_file_path = '/home/wonjae/Desktop/GP/project/01_reference_code/1.Object_merge/fruits/target.txt'
output_file_path = '/home/wonjae/Desktop/GP/Mergetest/'

jpg_list = []

list_file = open(input_file_path, 'r')

files = list_file.readline()

while not (files == ""):
    jpg_list.append(files[:-1])
    files = list_file.readline()

for turn in jpg_list:
    img = Image.open(turn)
    img = img.convert("RGBA")
    datas = img.getdata()

    newData = []
    cutOff = 30

    for item in datas:
        if item[0] <= cutOff and item[1] <= cutOff and item[2] <= cutOff:
            newData.append((255, 255, 255, 0))

        else:
            newData.append(item)

    img.putdata(newData)
    img.save(turn.rstrip(".jpg") + ".png", "PNG")
    print('done')
