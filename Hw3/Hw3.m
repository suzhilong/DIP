close all;%关闭所有窗口  
clear;%清除变量的状态数据  
clc;%清除命令行  
%原图
f = imread('Chapter3_1.pgm');
subplot(4,3,2),imshow(f);
title('origin')

%%sigma=0.6
%N=3
h1 = fspecial( 'log', 3, 0.6 );
log1 = imfilter(f,h1); 
level1=graythresh(log1);%使用graythresh计算灰度门槛
b1=im2bw(log1,level1);
subplot(4,3,4),imshow(b1);
title('LoG N=3  sigma=0.6')
%N=5
h1 = fspecial( 'log', 5, 0.6 );
log1 = imfilter(f,h1); 
level1=graythresh(log1);%使用graythresh计算灰度门槛
b1=im2bw(log1,level1);
subplot(4,3,5),imshow(b1);
title('LoG N=5  sigma=0.6')
%N=9
h1 = fspecial( 'log', 9, 0.6 );
log1 = imfilter(f,h1); 
level1=graythresh(log1);%使用graythresh计算灰度门槛
b1=im2bw(log1,level1);
subplot(4,3,6),imshow(b1);
title('LoG N=9  sigma=0.6')



%%sigma=1.2
%N=3
h2 = fspecial( 'log', 3, 1.2 );
log2 = imfilter(f,h2); 
level2=graythresh(log2);%使用graythresh计算灰度门槛
b2=im2bw(log2,level2);
subplot(4,3,7),imshow(b2);
title('LoG N=3  sigma=1.2')
%N=5
h2 = fspecial( 'log', 5, 1.2 );
log2 = imfilter(f,h2); 
level2=graythresh(log2);%使用graythresh计算灰度门槛
b2=im2bw(log2,level2);
subplot(4,3,8),imshow(b2);
title('LoG N=5  sigma=1.2')
%N=9
h2 = fspecial( 'log', 9, 1.2 );
log2 = imfilter(f,h2); 
level2=graythresh(log2);%使用graythresh计算灰度门槛
b2=im2bw(log2,level2);
subplot(4,3,9),imshow(b2);
title('LoG N=9  sigma=1.2')

%sigma=2.8
%N=3
h3 = fspecial( 'log', 3, 2.8 );
log2 = imfilter(f,h3); 
level3=graythresh(log2);%使用graythresh计算灰度门槛
b2=im2bw(log2,level3);
subplot(4,3,10),imshow(b2);
title('LoG N=3  sigma=2.8')
%N=5
h3 = fspecial( 'log', 9, 2.8 );
log2 = imfilter(f,h3); 
level3=graythresh(log2);%使用graythresh计算灰度门槛
b2=im2bw(log2,level3);
subplot(4,3,11),imshow(b2);
title('LoG N=5  sigma=2.8')
%N=9
h3 = fspecial( 'log', 9, 2.8 );
log2 = imfilter(f,h3); 
level3=graythresh(log2);%使用graythresh计算灰度门槛
b2=im2bw(log2,level3);
subplot(4,3,12),imshow(b2);
title('LoG N=9  sigma=2.8')






