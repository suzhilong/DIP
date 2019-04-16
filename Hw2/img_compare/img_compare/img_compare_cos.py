# -*- coding: utf-8 -*-
#http://www.zhongruitech.com/204199914.html
#cosin相似度

from PIL import Image
from numpy import average, linalg, dot

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
            vector.append(average(pixel_tuple))
        vectors.append(vector)
        norms.append(linalg.norm(vector, 2))
    a, b = vectors
    a_norm, b_norm = norms
    res = dot(a / a_norm, b / b_norm)
    return res

image1 = Image.open('/home/su/code/DIP/Hw2/Chapter2_1.pgm')
for num in xrange(5):
    image2 = Image.open('/home/su/code/DIP/Hw2/opt/rotatedBack_%s.jpg'%num)
    cosin = image_similarity_vectors_via_numpy(image1, image2)
    print(num , cosin)