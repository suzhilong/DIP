close all;%关闭所有窗口  
clear;%清除变量的状态数据  
clc;%清除命令行 

x=-50:1:50;
y=-50:1:50;
[X,Y]=meshgrid(x,y);

sigma3=3;
Z3=-((X.^2+Y.^2-2*sigma3^2)./(sigma3^4)).*exp(-(X.^2+Y.^2)./(2*sigma3^2));
subplot(321);mesh(X,Y,Z3);title('sigma=3')

sigma5=5;
Z=-((X.^2+Y.^2-2*sigma5^2)./(sigma5^4)).*exp(-(X.^2+Y.^2)./(2*sigma5^2));
subplot(322);mesh(X,Y,Z);title('sigma=5')

sigma7=7;
Z=-((X.^2+Y.^2-2*sigma7^2)./(sigma7^4)).*exp(-(X.^2+Y.^2)./(2*sigma7^2));
subplot(323);mesh(X,Y,Z);title('sigma=7')

sigma11=11;
Z=-((X.^2+Y.^2-2*sigma11^2)./(sigma11^4)).*exp(-(X.^2+Y.^2)./(2*sigma11^2));
subplot(324);mesh(X,Y,Z);title('sigma=11')

sigma13=13;
Z=-((X.^2+Y.^2-2*sigma13^2)./(sigma13^4)).*exp(-(X.^2+Y.^2)./(2*sigma13^2));
subplot(325);mesh(X,Y,Z);title('sigma=13')