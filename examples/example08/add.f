SUBROUTINE ADD(A,N,B,C)
implicit none

integer :: N
double precision :: A(N)
double precision :: B(N)
double precision :: C(N)
integer :: i
      DO I=1,N
         C(I) = A(I) + B(I)
      END DO

END SUBROUTINE ADD
