# -*- coding: utf-8 -*-
#http://www.zhongruitech.com/204199914.html
#SSIM（结构相似性度量）

from skimage.measure import compare_ssim
from scipy.misc import imread
import numpy as np

img1 = imread('/home/su/code/DIP/Hw2/Chapter2_1.pgm')
img2 = imread('/home/su/code/DIP/Hw2/opt/rotatedBack_0.jpg')

img2 = np.resize(img2, (img1.shape[0], img1.shape[1], img1.shape[2]))

print(img2.shape)
print(img1.shape)
ssim = compare_ssim(img1, img2, multichannel=True)

print(ssim)