T = csvread('forMatlabh.csv');


x1 = T(:,1)
x1 = transpose(x1);
s = size(x1)
x1t = (0:1:s(2)-1);

plot(x1t,x1)
hold on;

x2 = T(:,2)
x2 = transpose(x2);
s2 = size(x2)
x2t = (0:1:s2(2)-1);

plot(x2t,x2)

x3 = T(:,3)
x3 = transpose(x3);
s3 = size(x3)
x3t = (0:1:s3(2)-1);

plot(x3t,x3)

x4 = T(:,4)
x4 = transpose(x4);
s4 = size(x4)
x4t = (0:1:s4(2)-1);

plot(x4t,x4)
