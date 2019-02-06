A = rand(3,4);
A
A'
B = fast_transpose(A)

A = rand(1000);
tic;A';toc
tic;B = fast_transpose(A);toc
