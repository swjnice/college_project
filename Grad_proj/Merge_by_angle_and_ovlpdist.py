'''
################################# HOW TO USE ################################
** Needed FILE : target.txt(list of image), target2.txt(list of text)
** path should be fixed! : Merger.input_file_path , Merger.output_file_path

0. cfg
Merger.angle = angle(degree - 0 ~ 360) list used while merging (ex [45, 180, 315 ...])
Merger.overlap_distance = overlap_distance(%) used while merging (ex [5, 10, 25, 50])

1. two_merge
Merger.two_merge(class1 = [], class2 = [], num = 1, index = '000')
class1 = the list of class of item which be on the centered 
    [] = random
    ex) [2, 3, 5] or [], ...
class2 = the list of class of item which be around the centered item
    [] = random
    ex) same with class1
num = iteration
index = prefix of created image and text file

2. multi_merge
Merger.multi_merge(classes = [], item_num = 2, num = 1, index = '000')
classes = the list of list can be merged
    the length lf list should be same with item_num(except [])
    [] = all random
    ex) classes = [[2],[3],[1]], item_num = 3 -> class of 2, 3 ,1 items will be merged in one image file.
item_num = the number of items which would be merged
num = iteration
index = prefix of created image and text file


the example code is below the code!!
######################################################################################
'''
import random
import math
import numpy as np
from PIL import Image, ImageDraw
import cv2 as cv

def box_first_point(box):
    '''
    find (x_rate, y_rate) of input box
    Input : [class, x, y, width, height]
    Output : (rate_x, rate_y)
    '''
    rate_x = box[1]-box[3]/2
    rate_y = box[2]-box[4]/2
    return [rate_x, rate_y]

def box_last_point (box):
    '''
    find under_right point of box
    Input : [class, x, y, width, height] (rate)
    Output : (rate_x, rate_y)
    '''
    rate_x = box[1]+box[3]/2
    rate_y = box[2]+box[4]/2
    return [rate_x, rate_y]


## class - Merger ##
class Merger():
    def __init__(self, input_file_path = "", output_file_path = ""):
        
        if input_file_path == "" or output_file_path == "":
            print("Default file path setted")
            ## FIXME
            ################################ file_path ########################################
            ##self.input_file_path ="/home/wonjae/Desktop/GP/project/Mergetest/image/"
            ##self.output_file_path ="/home/wonjae/Desktop/GP/project/Mergetest/merge_test_out/"
            self.input_file_path ="/data2/HJY/data_classplus/targets/orig/"
            self.output_file_path ="/home/intern19/wonjae/py_merge/result/"
            ################################ file_path ########################################
         
        ## get image, text file list
        self._merge_image_set = [] 
        self._merge_text_set = [] 
        self.get_file_list()

        self.merge_set_num = [] ## index of merged image in list
        self.merge_set_box = [] ## boxes of merged image
        self.angle = [0, 45, 90, 135, 180, 225, 270, 315,] ## Overlap angle
        self.overlap_distance = [5, 25, 50] ## Overlap distance

    def get_file_list(self):
        '''
        get the list of input image, text file
        this function is done in Constructor of Class 'Merge'
        '''
        image_list = []
        text_list = []
        image_file = open(self.input_file_path + 'orig_target.txt', 'r')
        text_file = open(self.input_file_path + 'orig_target2.txt', 'r')
        while True:
            line = image_file.readline()
            if line == "":
                break
            image_list.append(line[:-1]) ## read except '\n'
        while True:
            line2 = text_file.readline()
            if line2 == "":
                break
            text_list.append(line2[:-1]) ## read exceipt '\n'
        image_file.close()
        text_file.close()

        self._merge_image_set = image_list
        self._merge_text_set = text_list

        return

    def two_merge(self, class1 = [], class2 = [], num = 1, index = 0):
        '''
        Merge two items. Class2 item is on class1 item.
        Input : class1 - class number array ex) [1, 3, 5]
                class2 - class number array ex) [1, 4, 6]
                num - the number of package you want (1 package has 24 merged images)
                index - the index you want to append in front of filename(prefix number) ex) 'merged_(index)132'
        '''
        cnt = 0
        for iterate in range(num):
            for angle in self.angle:
                for overlap_distance in self.overlap_distance:
                    cnt+=1
                    ## Decide two index to merge
                    merge_index = self.pick_two_index(class1, class2)
                    self.inspect_box(merge_index) 

                    ## fixed_item_box
                    fixed_item_box = [[]]
                    for i in range(len(self.merge_set_box[0])):
                        fixed_item_box[0].append(self.merge_set_box[0][i])
                    self.find_fixed_box([angle], [overlap_distance], fixed_item_box)
                    
                    ## inspect image size and move
                    fplp = self.image_fp_lp(fixed_item_box)
                    width = fplp[2] - fplp[0]
                    height = fplp[3] - fplp[1]
                    if width > 1 or height  > 1:
                        cnt -= 1
                        self.merge_set_box = []
                        self.merge_set_num = []
                        continue
                    target_lp_pos = (width + (1-width)*random.random(), height + (1-height)*random.random())
                    move_amount = (target_lp_pos[0] -fplp[2], target_lp_pos[1] - fplp[3])

                    ## move text
                    self.text_move(move_amount, fixed_item_box)

                    ## find paste_point
                    destination = self.find_destination(fixed_item_box)

                    ## first_image 
                    background = Image.new("RGBA", (640, 480), (0, 0, 0))
                    input_image = Image.open(self._merge_image_set[merge_index[0]]).convert("RGBA")
                    background.paste(input_image, destination[0], input_image)
                    
                    ## merge second image 
                    input_image = Image.open(self._merge_image_set[merge_index[1]]).convert("RGBA")
                    before_paste = background.copy()
                    shifted_bg = Image.new("RGBA", (640,480), (0,0,0))
                    shifted_bg.paste(input_image, destination[1], input_image)
                    self.new_bound(background, shifted_bg, fixed_item_box, 1)

                    self.bg_transparent(before_paste)
                    self.bg_transparent(shifted_bg)

                    background.paste(shifted_bg, (0,0), shifted_bg)
                    background.paste(before_paste,(0,0),before_paste)

                    ## Draw bounding Box
                    '''            
                    include_bounding_box = ImageDraw.Draw(background)
                    for box in fixed_item_box:
                        if box != []:
                            include_bounding_box.rectangle([box_first_point(box)[0]*640, box_first_point(box)[1]*480, (box_first_point(box)[0]+box[3])*640, (box_first_point(box)[1]+box[4])*480])
                    '''

                    out_filename = "merged_" + str(index) + str(iterate) + "_A:" + str(angle) + "_D:" + str(overlap_distance) + "_C:" + str(int(self.merge_set_box[0][0])) + str(int(self.merge_set_box[1][0]))

                    ## save image file
                    background = background.convert("RGB")
                    background.save(self.output_file_path + out_filename + ".png")
                    ##print(out_filename)

                    ## save txt file 
                    out_file = open(self.output_file_path + out_filename + ".txt" , 'w')
                    for i in range(len(fixed_item_box)):
                        if fixed_item_box[i][0] < 0:
                            continue
                        for j in range(len(fixed_item_box[i])):
                            out_file.write(str(fixed_item_box[i][j])+" ")
                        out_file.write("\n")
                    out_file.close()
                    
                    background.close()
                    self.merge_set_num = []
                    self.merge_set_box = []
                    if cnt % 100 == 0:
                        print(cnt)
        print(cnt, "two item merged image created")
        return cnt
    
    def multi_merge(self, classes = [], item_num = 2, num = 1, index = '00000'):
        '''
        merge many items
        input : classes, item_num = 2, index = 000
        output : save merged image
        '''
        cnt = 0 ## image count
        if item_num == 0:
            item_num = random.randint(3,9)

        ## default set
        for iterate in range(num):
            cnt+=1
            if classes == []:
                for i in range(item_num):
                    classes.append([])

            ## select merge_item
            merge_index = []
            for i in range(item_num):
                if classes[i] == []:
                    idx = random.randrange(len(self._merge_image_set))
                    merge_index.append(idx)
                else:
                    idx_class = -1
                    while not idx_class in classes[i]:
                        idx = random.randrange(len(self._merge_image_set))
                        txt_file = open(self._merge_text_set[idx], "r") 
                        txt_line = txt_file.readline()
                        txt_line_split = txt_line.split()
                        idx_class = int(txt_line_split[0])
                        txt_file.close()
                    merge_index.append(idx)
            self.inspect_box(merge_index)

            ## select angle, overlap
            angle_list = []
            ovlp_list = []
            for i in range(item_num-1):
                ovlp_list.append(random.choice(self.overlap_distance))
            angle_list = random.sample(self.angle, item_num-1)
            
            ## fixed_item_box
            fixed_item_box = []
            fixed_item_box.append([])
            for i in range(len(self.merge_set_box[0])):
                fixed_item_box[0].append(self.merge_set_box[0][i])
            self.find_fixed_box(angle_list, ovlp_list, fixed_item_box)
            
            ### inspect image size and move ###
            fplp= self.image_fp_lp(fixed_item_box)
            width = fplp[2] - fplp[0]
            height = fplp[3] - fplp[1]
            ## if size bigger than window
            if width > 1 or height > 1: 
                cnt -= 1
                self.merge_set_box = []
                self.merge_set_num = []
                continue
            target_lp_pos = (width + (1-width)*random.random(), height + (1-height)*random.random())
            move_amount = (target_lp_pos[0] - fplp[2], target_lp_pos[1] - fplp[3])
            ## move text
            self.text_move(move_amount, fixed_item_box)

            ## find paste_point
            destination = self.find_destination(fixed_item_box)

            ## first_image
            background = Image.new("RGBA", (640, 480), (0,0,0))
            input_image = Image.open(self._merge_image_set[merge_index[0]]).convert("RGBA")
            background.paste(input_image, destination[0], input_image)

            ## merge other images
            for i in range(1, item_num):
                input_image = Image.open(self._merge_image_set[merge_index[i]]).convert("RGBA")
                before_paste = background.copy()
                shifted_bg = Image.new("RGBA", (640,480), (0,0,0)).convert("RGBA")
                shifted_bg.paste(input_image, destination[i], input_image)
                self.new_bound(background, shifted_bg, fixed_item_box, i)

                self.bg_transparent(before_paste)
                self.bg_transparent(shifted_bg)

                background.paste(shifted_bg,(0,0), shifted_bg)
                background.paste(before_paste, (0,0), before_paste)

            ## Draw bounding Box
            '''                       
            include_bounding_box = ImageDraw.Draw(background)
            for box in fixed_item_box:
                if box != []:
                    include_bounding_box.rectangle([box_first_point(box)[0]*640, box_first_point(box)[1]*480, (box_last_point(box)[0])*640, (box_last_point(box)[1])*480])
            ''' 
            

            out_filename = "merged_N"+str(item_num)+"_"+str(index) +"_"+str(cnt)

            ## save image file
            background = background.convert("RGB")
            background.save(self.output_file_path + out_filename + ".png")
            ##print(out_filename)

            ## save txt file 
            out_file = open(self.output_file_path + out_filename + ".txt" , 'w')
            for i in range(len(fixed_item_box)):
                if fixed_item_box[i][0] < 0:
                    continue
                for j in range(len(fixed_item_box[i])):
                    out_file.write(str(fixed_item_box[i][j])+" ")
                out_file.write("\n")
            out_file.close()
            
            background.close()
            self.merge_set_num = []
            self.merge_set_box = []
            if cnt % 100 == 0:
                print(cnt)
        print(cnt, "merged image", item_num, "item merging created")
        return cnt

    def pick_two_index(self, class1 = [], class2 = []):
        '''
        Pick two index which are in right class ( one in class1, one in class2 )
        Input : class1, class2 (Array)
        Output : [index1, index2]
        '''
        index_set = []
        if class1 == []:
            idx1 = random.randrange(len(self._merge_image_set))
            index_set.append(idx1)
        else:
            idx_class = -1
            while not idx_class in class1:
                idx = random.randrange(len(self._merge_image_set))
                txt_file = open(self._merge_text_set[idx], "r") 
                txt_line = txt_file.readline()
                txt_line_split = txt_line.split()
                idx_class = int(txt_line_split[0])
                txt_file.close()
            index_set.append(idx)
        if class2==[]:
            idx2 = random.randrange(len(self._merge_image_set))
            index_set.append(idx2)
        else:
            idx_class = -1
            while not idx_class in class2:
                idx = random.randrange(len(self._merge_image_set))
                txt_file = open(self._merge_text_set[idx], "r") 
                txt_line = txt_file.readline()
                txt_line_split = txt_line.split()
                idx_class = int(txt_line_split[0])
                txt_file.close()
            index_set.append(idx)
        return index_set

    def inspect_box(self, index_set = []):
        '''
        Make the box list of merge set 
        Input : index_set (index array)
        Output : self.merge_set_box
        '''
        if index_set == []:
            return -1
        
        for idx in index_set:
            txt_file = open(self._merge_text_set[idx], "r")
            txt_line = txt_file.readline()
            txt_line_split = txt_line.split()
            for i in range(len(txt_line_split)):
                if i==0:
                    txt_line_split[i] = int(txt_line_split[i])
                    continue
                txt_line_split[i] = float(txt_line_split[i])
            self.merge_set_box.append(txt_line_split)
            txt_file.close()

    def find_fixed_box(self, angle_list, ovlp_list, fixed_item_box):
        '''
        Find boxes by angle list and overlap distance list
        Input : angle list, overlap distance list, box list for return
        Output : fixed_item_box list 
        '''
        standard_item_box = fixed_item_box[0]
        for index in range(len(angle_list)):
            angle = angle_list[index]
            overlap_distance = ovlp_list[index]
            toadd_item_box = [self.merge_set_box[index+1][i] for i in range(len(self.merge_set_box[index+1]))]
            toadd_item_first_point = box_first_point(toadd_item_box)
            center_slope = standard_item_box[4]/standard_item_box[3]
            toadd_slope = toadd_item_box[4]/standard_item_box[3]
            if angle in [0, 180]:
                stand_radius = standard_item_box[3]/2
                toadd_radius = toadd_item_box[3]/2
                dest_y = standard_item_box[2]
                if angle == 0:
                    dest_x = standard_item_box[1] + stand_radius*(50 - overlap_distance)/50 + toadd_radius
                else:
                    dest_x = standard_item_box[1] - stand_radius*(50 - overlap_distance)/50 - toadd_radius
            elif angle in [90, 270]:
                stand_radius = standard_item_box[4]/2
                toadd_radius = toadd_item_box[4]/2
                dest_x = standard_item_box[1]
                if angle == 90:
                    dest_y = standard_item_box[2] - stand_radius*(50 - overlap_distance)/50 - toadd_radius
                else:
                    dest_y = standard_item_box[2] + stand_radius*(50 - overlap_distance)/50 + toadd_radius
            else:
                rad_angle = math.radians(angle)
                tan_angle = math.tan(rad_angle)
                if abs(tan_angle) < toadd_slope:
                    toadd_radius = toadd_item_box[3]/2/abs(math.cos(rad_angle))
                else:
                    toadd_radius = toadd_item_box[4]/2/abs(math.sin(rad_angle))
                if abs(tan_angle) < center_slope:
                    stand_radius = standard_item_box[3]/2/abs(math.cos(rad_angle))
                else:
                    stand_radius = standard_item_box[4]/2/abs(math.sin(rad_angle))
                if angle > 0 and angle < 90:
                    dest_x = standard_item_box[1] + abs(math.cos(rad_angle)*(toadd_radius + stand_radius*(50-overlap_distance)/50))
                    dest_y = standard_item_box[2] - abs(math.sin(rad_angle)*(toadd_radius + stand_radius*(50-overlap_distance)/50))
                elif angle > 90 and angle < 180:
                    dest_x = standard_item_box[1] - abs(math.cos(rad_angle)*(toadd_radius + stand_radius*(50-overlap_distance)/50))
                    dest_y = standard_item_box[2] - abs(math.sin(rad_angle)*(toadd_radius + stand_radius*(50-overlap_distance)/50))
                elif angle > 180 and angle < 270:
                    dest_x = standard_item_box[1] - abs(math.cos(rad_angle)*(toadd_radius + stand_radius*(50-overlap_distance)/50))
                    dest_y = standard_item_box[2] + abs(math.sin(rad_angle)*(toadd_radius + stand_radius*(50-overlap_distance)/50))
                else:
                    dest_x = standard_item_box[1] + abs(math.cos(rad_angle)*(toadd_radius + stand_radius*(50-overlap_distance)/50))
                    dest_y = standard_item_box[2] + abs(math.sin(rad_angle)*(toadd_radius + stand_radius*(50-overlap_distance)/50))
            
            toadd_item_box[1] = round(dest_x,6)
            toadd_item_box[2] = round(dest_y,6)
            fixed_item_box.append(toadd_item_box)

    def find_destination(self, fixed_item_box):
        '''
        find destination point in list
        input : fixed_item_box
        output : destination point for paste in list
        '''
        destination = []
        for i in range(len(fixed_item_box)):
            orig_center = (self.merge_set_box[i][1], self.merge_set_box[i][2])
            fixed_center = (fixed_item_box[i][1], fixed_item_box[i][2])
            paste_point = (int(640*(fixed_center[0]-orig_center[0])), int(480*(fixed_center[1]-orig_center[1])))
            destination.append(paste_point)
        return destination

    def image_fp_lp(self, merge_set_box):
        '''
        Get the first point and last point of whole merged image
        input : (array)merge_set_box
        output : first point, last point
        '''
        w_fp = [0,0]
        w_lp = [0,0]
        for i in range(len(merge_set_box)):
            fp = box_first_point(merge_set_box[i])
            lp = box_last_point(merge_set_box[i])
            if i == 0:
                w_fp[0] = fp[0]
                w_fp[1] = fp[1]
                w_lp[0] = lp[0]
                w_lp[1] = lp[1]
                continue
            if fp[0] < w_fp[0]:
                w_fp[0] = fp[0]
            if fp[1] < w_fp[1]:
                w_fp[1] = fp[1]
            if lp[0] > w_lp[0]:
                w_lp[0] = lp[0]
            if lp[1] > w_lp[1]:
                w_lp[1] = lp[1]
        return [w_fp[0], w_fp[1], w_lp[0], w_lp[1]]

    def text_move(self, move_amount, merge_set_box):
        '''
        modify text file information by the moving amount
        '''
        for i in range(len(merge_set_box)):
            merge_set_box[i][1]+= move_amount[0]
            merge_set_box[i][2]+= move_amount[1]

    def bg_transparent(self, input_image):
        '''
        Make image background transparent from black
        Parameter: input_image
        '''
        
        origin_data = input_image.getdata()
        newData = []
        cutoff = 12
        for item in origin_data:
            if item[0] <= cutoff and item[1] <= cutoff and item[2] <= cutoff:
                newData.append((255,255,255,0))
            else:
                newData.append(item)
        input_image.putdata(newData)
 
    def new_bound(self, fground, bground, fixed_item_box, index):
        '''
        make new bounding box of bground
        Parameter : image-foreground, image - background, box_array -  fixed_box
        '''
        ## find foreground, background mask
        cv_fground = cv.cvtColor(np.array(fground), cv.COLOR_RGB2BGR)
        cv_bground = cv.cvtColor(np.array(bground), cv.COLOR_RGB2BGR)
        fground_gray = cv.cvtColor(cv_fground, cv.COLOR_BGR2GRAY)
        bground_gray = cv.cvtColor(cv_bground, cv.COLOR_BGR2GRAY)
        ret_b, bground_mask = cv.threshold(bground_gray, 10, 255, cv.THRESH_BINARY)
        ret, fground_mask = cv.threshold(fground_gray, 20, 255, cv.THRESH_BINARY)
        fground_mask_inv = cv.bitwise_not(fground_mask)
        
        ## find occluded mask of new image(background)
        occluded_bground = cv_bground*(fground_mask_inv[:,:,None].astype(cv_bground.dtype))
        occluded_bground = occluded_bground*(bground_mask[:,:,None].astype(occluded_bground.dtype))
        occld_bg_gray = cv.cvtColor(occluded_bground, cv.COLOR_BGR2GRAY)
        ret2, occld_bg_mask = cv.threshold(occld_bg_gray, 20, 255, cv.THRESH_BINARY)
        
        ## contour of original new image
        b_image, b_contours, b_hierachy = cv.findContours(bground_mask, cv.RETR_EXTERNAL, cv.CHAIN_APPROX_NONE)
        b_lc_a = 0
        b_lc = []
        for b_contour in b_contours: ## find largest
            if cv.contourArea(b_contour) > b_lc_a:
                b_lc_a = cv.contourArea(b_contour)
                b_lc = b_contour

        ## find contour of occluded image
        image, contours, hierachy = cv.findContours(occld_bg_mask, cv.RETR_EXTERNAL, cv.CHAIN_APPROX_NONE)
        lc_a = 0
        lc = []
        for contour in contours: ## find largest 
            if cv.contourArea(contour) > lc_a:
                lc_a = cv.contourArea(contour)
                lc = contour
        if lc == []:
           fixed_item_box[index] = [-1, -1, -1, -1, -1]
           return
        
        ## if too much occluded
        orig_area = cv.contourArea(b_lc)
        occluded_area = cv.contourArea(lc)
        if occluded_area/orig_area < 0.5:
            fixed_item_box[index] = [-1, -1, -1, -1, -1]
            return
        
        ## find bounding box
        x,y,w,h = cv.boundingRect(lc)
        cl = fixed_item_box[index][0]
        fixed_item_box[index] = [cl, (x+w/2)/640, (y+h/2)/480, w/640, h/480]
        for i in range(1,len(fixed_item_box[1])):
            fixed_item_box[index][i] = round(fixed_item_box[index][i],6)
    
################ Code to RUN #############################################    
test = Merger()
test.two_merge([],[], 10, '000')
test.multi_merge([], 10, '000')
'''
----------------------------------------------------code example----------------------------------
# two all merge
cnt = 0
index = '20000'
test.angle = [i*45 for i in range(10)]
test.angle.append(60)
test.overlap_distance = [5, 15, 25, 35, 45]
for i in range(15):
    for j in range(15):
        test.two_merge([i],[j],1,index)
        index = str(int(index)+1)

# two random merge
cnt = 0
index = '40000'
for i in range(2500):
    test.angle = [random.randint(0, 360)]
    test.overlap_distance = [random.randint(0, 51)]
    test.two_merge([], [], 1, index)
    index = str(int(index)+1)


# multi merge
cnt = 0
index = '30000'
test.angle = [0, 45, 90, 135, 180, 225, 270, 315]
test.overlap_distance = [10, 20, 30]
while cnt < 5000:
    cnt += test.multi_merge([], 0, 1, index)
    index = str(int(index)+1)
----------------------------------------------------------------------------------------------------
'''
