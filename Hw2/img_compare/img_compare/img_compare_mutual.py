# -*- coding: utf-8 -*-
#http://www.zhongruitech.com/204199914.html
#基于互信息（Mutual Information）

from sklearn import metrics as mr
from scipy.misc import imread
import numpy as np

img1 = imread('/home/su/code/DIP/Hw2/Chapter2_1.pgm')
img2 = imread('/home/su/code/DIP/Hw2/opt/rotatedBack_0.jpg')

img2 = np.resize(img2, (img1.shape[0], img1.shape[1], img1.shape[2]))

img1 = np.reshape(img1, -1)
img2 = np.reshape(img2, -1)
print(img2.shape)
print(img1.shape)
mutual_infor = mr.mutual_info_score(img1, img2)

print(mutual_infor)