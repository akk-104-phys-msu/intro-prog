program rectquad
  implicit none
  real :: eps, dx1, dx2, s1, s2
  real, parameter :: pi = 4*atan(1.0)
  real, parameter :: a = pi/2
  real, parameter :: b = pi
  integer :: n1, n2, i

  read(*, *) eps
  n1 = 2
  dx1 = b - a
  s1 = f((a+b)/2)
  n2 = 4
  dx2 = dx1/2
  i = 1
  s2 = s1 + oddsum(a, dx2, n2)
  do while (abs(dx1*s1-dx2*s2) > eps)
     s1 = s2
     n1 = n2
     dx1 = dx2
     dx2 = dx2/2
     n2 = 2*n2
     s2 = s2 + oddsum(a, dx2, n2)
     i = i+1
  enddo
  write (*, *) i, dx2*s2
  
contains
  real elemental function f(x)
    real, intent(in) :: x
    f = sin(x)/sqrt(x)
  end function f
  real elemental function oddsum(a, dx, n)
    real, intent(in) :: a,dx
    integer, intent(in) :: n
    integer :: i
    oddsum = 0
    do i = 1, n-1, 2
       oddsum = oddsum + f(a+i*dx)
    enddo
  end function oddsum
end program rectquad
