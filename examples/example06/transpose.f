SUBROUTINE TRANSPOSE(A,M,N,B)
implicit none

integer :: M,N
double precision :: A(M,N)
double precision :: B(N,M)

integer :: i,j

      DO I=1,M
        DO J=1,N
           B(J,I) = A(I,J)
        END DO
     END DO

END SUBROUTINE TRANSPOSE
