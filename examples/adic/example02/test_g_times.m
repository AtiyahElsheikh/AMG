% a simple driver to test a mex file linked with adic 
% imagine that x is an intermidiate variable and there are 
% 2 independent variables,  say t1 and t2. assume that c 
% is a scalar. 

for i = 1:5
x(i) = 2 / i ;
g_x(2*i)   = (2*i-1)/3;
g_x(2*i-1) = i/3;
end
g_x = g_x'
c = 1/3; 
g_c = [ 0 0 ]';
[g_y,y] = g_times(g_c,c,g_x,x);
x
g_x'
y
g_y'

