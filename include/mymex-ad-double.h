#include "ad_deriv.h"

#define size(X)  X##_par->size  
#define ndims(X) X##_par->ndims  
#define nrows(X) X##_par->size[0]  
#define ncols(X) X##_par->size[1] 
#define numel(X) X##_par->numel   

#define deriv(X,Y) set_deriv_type(X##_par,Y##_par)
#define grad(X)    grad_##X

typedef struct Mat MatObj ; 
struct Mat {

  void* data;       // the elements of the Mat.
  int numel;        // number of elements  
  int ndims;        // the number of dimensions 
  const int *size;  // the dimensions

  //mxClassID class;  // the type 
  // mxComplexity complex;
  // void* imdata; 
};

void* create_identical_array_fast(MatObj *inptr,mxArray **outptr );
void  extract_all(const mxArray *ptr,MatObj *M);
int has_equal_dims(MatObj *m1, MatObj *m2);
int has_equal_size(MatObj *m,int* dims, int ndims);
void*  create_scalar(mxArray **ptr);
void*  create_matrix(mxArray **ptr,int m,int n);
void*  create_matrix_fast(mxArray **ptr,int m,int n);
void* create_array(mxArray **ptr, int ndims, const int *size);
void* create_array_fast(mxArray **ptr, int ndims, const int *size);
void* create_identical_array(MatObj *inptr,mxArray **outptr );
void* create_identical_array_fast(MatObj *inptr,mxArray **outptr );
DERIV_TYPE* set_deriv_type(MatObj *val,MatObj *grad);
void get_value(DERIV_TYPE* x,int nx,double* out);
void get_grad(DERIV_TYPE* x,int nx,int ngrad,double *gout);
void display(MatObj* M[],int n); 

/*
 * get the values of a derivative objects 
 */
void get_value(DERIV_TYPE* x,int nx,double* out) { 
  int i;
  for(i=0;i<nx;i++) 
    out[i] = DERIV_val(x[i]);
}

/*
 * get the derivative values of a derivative objects 
 */
void get_grad(DERIV_TYPE* x,int nx,int ngrad,double* gout) { 
  int i,j;
  for(i=0;i<nx;i++) 
    for(int j=0;j<ngrad;j++)
      gout[i*ngrad+j] = DERIV_grad(x[i])[j];
}


/*
 * gevin 2 the values and the gradient of a parameter
 * create a derivative object of type DERIV_TYPE 
 * for adic
 */
DERIV_TYPE* set_deriv_type(MatObj *val,MatObj *grad) { 
  
  DERIV_TYPE* ret;
  int i,j,k;
  int ngrad = grad->numel / val->numel ; 
  double *data,*gdata;

  ret = (DERIV_TYPE *) malloc( val->numel * sizeof(DERIV_TYPE));
  data = val->data;
  gdata = grad->data;
  k=0;
  for(i=0;i<val->numel;i++) { 
    DERIV_val(ret[i]) = data[i];
    for(j=0;j<ngrad;j++)
      DERIV_grad(ret[i])[j] = gdata[k++]; 
  }

  return ret;
}   

/*
 * Extract all info & data about a Matlab object
 * 
 */
void  extract_all(const mxArray *ptr,MatObj *M) 
{
  int i;
  mxArray *p;
  void **ret_cell;

  M->data  = mxGetData(ptr) ;
  M->numel = mxGetNumberOfElements(ptr) ;
  M->ndims = mxGetNumberOfDimensions(ptr);
  M->size  = mxGetDimensions(ptr);
 
  //M->class = mxGetClassID(ptr);
}

/*
 * Whether 2 matlab objects are of the same shape
 */
int has_equal_dims(MatObj *m1, MatObj *m2) { 
  int i;
  if(m1->ndims != m2->ndims) return 0; 
  for(i=0;i<m1->ndims;i++) 
    if(m1->size[i] != m2->size[i]) 
      return 0; 
  return 1;
}

/*
 * Whether the matlab object m has the given shape
 */
int has_equal_size(MatObj *m,int* size, int ndims) { 
  int i;
  if(m->ndims != ndims) return 0; 
  for(i=0;i<ndims;i++) 
    if(m->size[i] != size[i]) 
      return 0; 
  return 1;
}


// create a double scalar ( this is the default if no 
// information is given about the output parameter 
void*  create_scalar(mxArray **ptr) {  
  *ptr = mxCreateDoubleMatrix(1,1,mxREAL); 
  return ( mxGetPr(*ptr)) ;
} 

/*
 * <p> Create an mxn double matrix. 
 * The default Type is double if the type of the output 
 * is not given . 
 * </p>  
 */
void*  create_matrix(mxArray **ptr,int m,int n) {
  *ptr = mxCreateDoubleMatrix(m,n,mxREAL); 
  return (mxGetPr(*ptr));
}

/*
 * The same as above. but data are neither allocated nor initialized 
 */
void*  create_matrix_fast(mxArray **ptr,int m,int n) {
  void *ret;

  *ptr = mxCreateDoubleMatrix(0,0,mxREAL); // no allocation
  mxSetM(*ptr,m);
  mxSetN(*ptr,n);
  ret = mxMalloc(m*n*sizeof(double)); // no initialization  
  mxSetPr(*ptr,ret);
  return (ret);
}

/*
 * Create a MATLAB matrix object of size size[0] x size[1] x .. x size[ndims-1]  
 * class specifies the type and is of the form mx{x}_CLASS, where x : 
 * LOGICAL,CHAR,DOUBLE,SINGLE,INT{n},UNIT{n} where n = {8,16,32,64 }
 * 
 */
void* create_array(mxArray **ptr, int ndims, const int *size) {
 
   *ptr = mxCreateNumericArray(ndims,size,mxDOUBLE_CLASS,mxREAL);
   return (mxGetPr(*ptr));
}

/*
 * The same as above. but data are neither allocated nor initialized
 */
void* create_array_fast(mxArray **ptr, int ndims, const int *size) {
  void *ret;
  int n;

   *ptr = mxCreateNumericMatrix(0,0,mxDOUBLE_CLASS,mxREAL);
   mxSetDimensions(*ptr,size,ndims);
   n = mxGetNumberOfElements(*ptr);
   ret = mxMalloc(n*sizeof(double));
   mxSetPr(*ptr,ret);
   return ret;
}

/*
 * Create a MATLAB matrix object of the same shape and type of 
 */
void* create_identical_array(MatObj *inptr,mxArray **outptr ) { 
   *outptr = mxCreateNumericArray(inptr->ndims,inptr->size,
				  mxDOUBLE_CLASS,mxREAL);
   return (mxGetPr(*outptr));
}

/*
 * The same as above. but data are neither allocated nor initialized
 */
void* create_identical_array_fast(MatObj *inptr,mxArray **outptr ) { 
  void* ret;
  int i;

  *outptr = mxCreateDoubleMatrix(0,0,mxREAL);
  mxSetDimensions(*outptr,inptr->size,inptr->ndims);
  ret = mxMalloc( inptr->numel * sizeof(double));
  mxSetPr(*outptr,ret);
  return ret;
}

void display(MatObj* M[],int n) {
 
  printf("nrhs = %d\n",n); 
 
  for(int i=0;i<n;i++) {
    printf("arg %d \n\tsize : %d \n",i,M[i]->numel ); 
    printf("\tnumber of dimensions : %d\n\t\t",M[i]->ndims);
    for(int k=0;k < M[i]->ndims; k++)
      printf("  %d",M[i]->size[k]);
    printf("\nnrows : %d  ncols : %d\n",M[i]->size[0],M[i]->size[1] );
    printf("\n\tdata:\n\t\t");
    double *p = (double *) M[i]->data ;
    for(int k=0;k < M[i]->numel; k++)
      printf(" %lf\t", p[k]);
    printf("\n");

  }
}
