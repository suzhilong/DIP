# -*- coding: utf-8 -*-
#http://www.zhongruitech.com/204199914.html
#http://www.ruanyifeng.com/blog/2011/07/principle_of_similar_image_search.html

import math
from PIL import Image
from scipy.misc import imread
import numpy as np

import matplotlib.pyplot as plt
import matplotlib

####hash
def avhash(im):
    if not isinstance(im, Image.Image):
        im = Image.open(im)
    im = im.resize((8, 8), Image.ANTIALIAS).convert('L')
    avg = reduce(lambda x, y: x + y, im.getdata()) / 64.
    return reduce(lambda x, (y, z): x | (z << y),
                  enumerate(map(lambda i: 0 if i < avg else 1, im.getdata())),
                  0)

def hamming(h1, h2):
    h, d = 0, h1 ^ h2
    while d:
        h += 1
        d &= d - 1
    return h

def hash(img1,img2):
    h1 = avhash(img1)
    h2 = avhash(img2)
    ham_dist = hamming(h1, h2)
    return ham_dist
		
###cos
def get_thumbnail(image, size=(132, 135), greyscale=False):
    image = image.resize(size, Image.ANTIALIAS)
    if greyscale:
        image = image.convert('L')
    return image

def image_similarity_vectors_via_numpy(image1, image2):
    image1 = get_thumbnail(image1)
    image2 = get_thumbnail(image2)
    images = [image1, image2]
    vectors = []
    norms = []
    for image in images:
        vector = []
        for pixel_tuple in image.getdata():
            vector.append(np.average(pixel_tuple))
        vectors.append(vector)
        norms.append(np.linalg.norm(vector, 2))
    a, b = vectors
    a_norm, b_norm = norms
    res = np.dot(a / a_norm, b / b_norm)
    return res

###直方图
def make_regalur_image(img, size = (132, 135)):
    return img.resize(size).convert('RGB')

def hist_similar(lh, rh):
    assert len(lh) == len(rh)
    return sum(1 - (0 if l == r else float(abs(l - r))/max(l, r)) for l, r in zip(lh, rh))/len(lh)

def calc_similar(li, ri):
    return hist_similar(li.histogram(), ri.histogram())

#https://blog.csdn.net/breezero/article/details/82285188
#PSNR
def psnr(target, ref, scale):
    # target:目标图像  ref:参考图像  scale:尺寸大小
    # assume RGB image
    target_data = np.array(target)
    target_data = target_data[scale:-scale,scale:-scale]
 
    ref_data = np.array(ref)
    ref_data = ref_data[scale:-scale,scale:-scale]
 
    diff = ref_data - target_data
    diff = diff.flatten('C')
    rmse = math.sqrt(np.mean(diff ** 2.))
    return 20*math.log10(1.0/rmse)

if __name__ == '__main__':
	image1 = Image.open('/home/su/code/DIP/Hw2/Chapter2_1.pgm')
	cmp_list = {}
	for x in xrange(5):
		image2 = Image.open('/home/su/code/DIP/Hw2/opt/rotatedBack_%s.jpg'%x)
		#hash_cmp = hash(image1,image2)#图片小效果不好，都是0
		cosin = image_similarity_vectors_via_numpy(image1, image2)
		histogram = calc_similar(image1, image2)
		#psnr_cmp = psnr(image1,image2,132*135)
		#print '%s cosin:'%x,cosin
		#print '%s histogram:'%x,histogram
		cmp_list['%scosin'%x] = cosin
		cmp_list['%shistogram'%x] = histogram
	#print sorted(cmp_list.items(),key=lambda x:x[0],reverse=False)

	# 设置中文字体和负号正常显示
	matplotlib.rcParams['font.sans-serif'] = ['SimHei']
	matplotlib.rcParams['axes.unicode_minus'] = False

	label_list = ['nearest', 'bilinear', 'bicubic', 'area-based', 'Lanczos']    # 横坐标刻度显示值
	num_list1 = [1000*cmp_list['0cosin'],1000*cmp_list['1cosin'],1000*cmp_list['2cosin'],1000*cmp_list['3cosin'],1000*cmp_list['4cosin']]      # 纵坐标值1
	num_list2 = [1000*cmp_list['0histogram'],1000*cmp_list['1histogram'],1000*cmp_list['2histogram'],1000*cmp_list['3histogram'],1000*cmp_list['4histogram']]      # 纵坐标值2
	x = range(len(num_list1))
	"""
	绘制条形图
	left:长条形中点横坐标
	height:长条形高度
	width:长条形宽度，默认值0.8
	label:为后面设置legend准备
	"""
	rects1 = plt.bar(left=x, height=num_list1, width=0.4, alpha=0.8, color='red', label="cosin")
	rects2 = plt.bar(left=[i + 0.4 for i in x], height=num_list2, width=0.4, color='green', label="histogram")
	plt.ylim(0, 1100)     # y轴取值范围
	plt.ylabel("value")
	"""
	设置x轴刻度显示值
	参数一：中点坐标
	参数二：显示值
	"""
	plt.xticks([index + 0.2 for index in x], label_list)
	plt.xlabel("mathods")
	plt.title("similar after rotate")
	plt.legend()     # 设置题注
	# 编辑文本
	for rect in rects1:
	    height = rect.get_height()
	    plt.text(rect.get_x() + rect.get_width() / 2, height+1, str(height), ha="center", va="bottom")
	for rect in rects2:
	    height = rect.get_height()
	    plt.text(rect.get_x() + rect.get_width() / 2, height+1, str(height), ha="center", va="bottom")
	plt.show()