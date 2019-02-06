A = rand(3,4);
A
A'
B = slow_transpose(A)

A = rand(1000);
tic;A';toc
tic;B = slow_transpose(A);toc
