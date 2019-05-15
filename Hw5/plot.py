# -*-coding:utf-8 -*-
import codecs
from matplotlib import pyplot as plt

def main():
	fileName = "/Users/sousic/code/cpp/DIP/Hw5/opt/ballsDis.txt"
	reader = codecs.open(fileName,'r',encoding='utf-8')
	lines = reader.readlines()

	n = []
	balls = []

	for i in range(len(lines)):
		n.append(int(lines[i].split(':')[0]))
		balls.append(int(lines[i].split(':')[1]))
	
	#plt.plot(n,balls)
	plt.bar(left=n, height=balls, width=2.5, alpha=0.7, label="")
	plt.xlim(0, 50)     # y轴取值范围
	plt.xlabel("size")
	plt.ylabel("numbers")

	plt.xticks([index for index in n], n)
	plt.title('Distribution')
	plt.show()


if __name__ == '__main__':
	main()