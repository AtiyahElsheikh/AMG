% a simple driver to test a mex file linked with adic 
% imagine that x is an intermidiate variable and there are 
% 2 independent variables,  say t1 and t2. assume that c 
% is a scalar. 

x = 2
% g_x = [dx/dt1 dx/dt2]
g_x = [ 1/3  2/3 ]'
c = 1/3 
% c is just a scalar
g_c = [ 0 0 ]'
[g_y,y] = g_times(g_c,c,g_x,x)
