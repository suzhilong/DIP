# -*- coding: utf-8 -*-
#http://www.zhongruitech.com/204199914.html
#基于直方图

from PIL import Image

def make_regalur_image(img, size = (256, 256)):
    return img.resize(size).convert('RGB')

def hist_similar(lh, rh):
    assert len(lh) == len(rh)
    return sum(1 - (0 if l == r else float(abs(l - r))/max(l, r)) for l, r in zip(lh, rh))/len(lh)

def calc_similar(li, ri):
    return hist_similar(li.histogram(), ri.histogram())

if __name__ == '__main__':
    img1 = Image.open('/home/su/code/DIP/Hw2/Chapter2_1.pgm')
    img1 = make_regalur_image(img1)
    for num in xrange(5):
	    img2 = Image.open('/home/su/code/DIP/Hw2/opt/rotatedBack_%s.jpg'%num)
	    img2 = make_regalur_image(img2)
	    print(num,calc_similar(img1, img2))

