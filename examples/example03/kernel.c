void kernel(double *x, int n, double *y) { 

  int i;
#ifdef _OPENMP
#pragma omp parallel for private(i) shared(x,y)
#endif
  for(i=0;i<n;i++)
    y[i] = x[i]*2;

}
