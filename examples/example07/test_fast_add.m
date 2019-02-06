A = rand(3,4);
B = rand(3,4);
C = A + B 
D = fast_add(A,B)
accuracy = norm(D-C)

A = rand(1000);
B = rand(1000);
tic; E = A + B; toc
tic; F = fast_add(A,B);toc
