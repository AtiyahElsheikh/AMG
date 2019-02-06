#include "ad_deriv.h"

// for the abbriviated version, we use mxGet*(X_par) 
//#define data(X)  X->data

#define size(X)  X##_par->size  
#define ndims(X) X##_par->ndims  
#define nrows(X) X##_par->size[0]  
#define ncols(X) X##_par->size[1] 
#define numel(X) X##_par->numel   
#define class(X) X##_par->type

#define celldata(X,i)  X##_par->cell[i]->data
#define cellsize(X,i)  X##_par->cell[i]->size  
#define cellndims(X,i) X##_par->cell[i]->ndims  
#define cellnrows(X,i) X##_par->cell[i]->size[0]  
#define cellncols(X,i) X##_par->cell[i]->size[1] 
#define cellnumel(X,i) X##_par->cell[i]->numel   
#define cellclass(X,i) X##_par->cell[i]->type

#define iscell(X) X->type == mxCELL_CLASS

#define deriv(X,Y) set_deriv_type(X##_par,Y##_par)
#define grad(X)    grad_##X

typedef struct Mat MatObj ; 
struct Mat {

  void* data;       // the elements of the Mat.
  int numel;        // number of elements  
  int ndims;        // the number of dimensions 
  const int *size;  // the dimensions
  mxClassID class;  // the type 
  
  MatObj**  cell;   // the cells in case of cell array

  // mxComplexity complex;
  // void* imdata; 

};

void* create_identical_array_fast(MatObj *inptr,mxArray **outptr );
void  extract_all(const mxArray *ptr,MatObj *M);
int has_equal_dims(MatObj *m1, MatObj *m2);
int has_equal_size(MatObj *m,int* dims, int ndims);
int has_equal_type(MatObj *m1, MatObj *m2);
void*  create_scalar(mxArray **ptr,mxClassID class,mxComplexity type);
void*  create_matrix(mxArray **ptr,int m,int n,mxClassID class,mxComplexity type);
void*  create_matrix_fast(mxArray **ptr,int m,int n,mxClassID class,mxComplexity type);
void* create_array(mxArray **ptr, int ndims, const int *size, 
		   mxClassID class, mxComplexity type);
void* create_array_fast(mxArray **ptr, int ndims, const int *size, 
			mxClassID class, mxComplexity type);
void* create_identical_array_size(MatObj *inptr,mxArray **outptr,mxClassID class);
void* create_identical_array_size_fast(MatObj *inptr,mxArray **outptr, mxClassID class);
void* create_identical_array(MatObj *inptr,mxArray **outptr );
void* create_identical_array_fast(MatObj *inptr,mxArray **outptr );
int* get_cell(void *a,int index);
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
  M->class = mxGetClassID(ptr);

  if(mxIsCell(ptr)) { 
    M->cell = (MatObj **) mxMalloc( sizeof(MatObj *) * M->numel);
    ret_cell = (void **) mxMalloc( sizeof(void *) * M->numel);
    for(i=0;i< M->numel ;i++) { 
      M->cell[i] = (MatObj *) mxMalloc(sizeof(MatObj)) ; 
      p = mxGetCell(ptr,i);
      extract_all(p,M->cell[i]);
      ret_cell[i] =  M->cell[i]->data ;
    }
    M->data = ret_cell;
  }
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

/*
 * Whether 2 matlab objects are of the same shape
 */
int has_equal_type(MatObj *m1, MatObj *m2) { 
  return m1->class == m2->class ;
}
  
// create a double scalar ( this is the default if no 
// information is given about the output parameter 
void*  create_scalar(mxArray **ptr,
		     mxClassID class,
		     mxComplexity type) {  
  *ptr = mxCreateNumericMatrix(1,1,class,type); 
  return ( mxGetPr(*ptr)) ;
} 

/*
 * <p> Create an mxn double matrix. 
 * The default Type is double if the type of the output 
 * is not given . 
 * </p>  
 */
void*  create_matrix(mxArray **ptr,int m,int n,
		     mxClassID class,mxComplexity type) {
  *ptr = mxCreateNumericMatrix(m,n,class,type); 
  return (mxGetPr(*ptr));
}


/*
 * The same as above. but data are neither allocated nor initialized 
 */
void*  create_matrix_fast(mxArray **ptr,int m,int n,
			  mxClassID class,mxComplexity type) {
  void *ret;

  *ptr = mxCreateNumericMatrix(0,0,class,type); // no allocation
  mxSetM(*ptr,m);
  mxSetN(*ptr,n);
  if( (class == mxDOUBLE_CLASS)  || 
      (class == mxINT64_CLASS)   ||
      (class == mxUINT64_CLASS) )
    ret = mxMalloc(m*n*sizeof(double)); // no initialization 
  else if( (class == mxSINGLE_CLASS) ||
	(class == mxINT32_CLASS)  ||
	(class == mxUINT32_CLASS) )
    ret = mxMalloc(m*n*sizeof(int));
  else if( (class == mxCHAR_CLASS) ||
	   (class == mxLOGICAL_CLASS))
    ret = mxMalloc(m*n*sizeof(char));
  else 
    mexErrMsgTxt("unsupported type used, use -nofast");
         
  mxSetPr(*ptr,ret);
  return (ret);
}

/*
 * Create a MATLAB matrix object of size size[0] x size[1] x .. x size[ndims-1]  
 * class specifies the type and is of the form mx{x}_CLASS, where x : 
 * LOGICAL,CHAR,DOUBLE,SINGLE,INT{n},UNIT{n} where n = {8,16,32,64 }
 * 
 */
void* create_array(mxArray **ptr, int ndims, const int *size, 
		   mxClassID class, mxComplexity type) {
 
   *ptr = mxCreateNumericArray(ndims,size,class,type);
   return (mxGetPr(*ptr));
}

/*
 * The same as above. but data are neither allocated nor initialized
 */
void* create_array_fast(mxArray **ptr, int ndims, const int *size, 
		   mxClassID class, mxComplexity type) {
  void *ret;
  int n;

   *ptr = mxCreateNumericMatrix(0,0,class,type);
   mxSetDimensions(*ptr,size,ndims);
   n = mxGetNumberOfElements(*ptr);
   if( (class == mxDOUBLE_CLASS)  || 
       (class == mxINT64_CLASS)   ||
       (class == mxUINT64_CLASS) )
     ret = mxMalloc(n*sizeof(double));
   else if( (class == mxSINGLE_CLASS) ||
	    (class == mxINT32_CLASS)  ||
	    (class == mxUINT32_CLASS) )
     ret = mxMalloc(n*sizeof(int));
   else if( (class == mxCHAR_CLASS) ||
	    (class == mxLOGICAL_CLASS))
     ret = mxMalloc(n*sizeof(char));
   else { 
     mexErrMsgTxt("unsupported type used, use -nofast");
   }
   mxSetPr(*ptr,ret);
     
  return ret;
}

/*
 * Create a MATLAB matrix object of the same shape of 
 * a given Matlab object
 */
void* create_identical_array_size(MatObj *inptr,mxArray **outptr, mxClassID class) { 
   *outptr = mxCreateNumericArray(inptr->ndims,inptr->size,class,mxREAL);
   return (mxGetPr(*outptr));
}

/*
 * The same as above. but data are neither allocated nor initialized
 */
void* create_identical_array_size_fast(MatObj *inptr,mxArray **outptr,mxClassID class ) {
  int n;
  void* ret;
  void** ret_cell;  
  int i;
  mxArray *p;

  *outptr = mxCreateNumericMatrix(0,0,class,mxREAL);
  mxSetDimensions(*outptr,inptr->size,inptr->ndims);

  if( (class == mxDOUBLE_CLASS)  || 
      (class == mxINT64_CLASS)   ||
      (class == mxUINT64_CLASS) ) { 
     ret = mxMalloc( inptr->numel * sizeof(double));
     mxSetPr(*outptr,ret);
     return ret;
  }
  else if( (class == mxSINGLE_CLASS) ||
	   (class == mxINT32_CLASS)  ||
	   (class == mxUINT32_CLASS) ) { 
     ret = mxMalloc( inptr->numel * sizeof(int));
     mxSetPr(*outptr,ret); 
     return ret;
  }
  else if( (class == mxCHAR_CLASS) ||
	   (class == mxLOGICAL_CLASS)) { 
    ret = mxMalloc( inptr->numel * sizeof(char));
    mxSetPr(*outptr,ret); 
    return ret;
  }
  else if (class == mxCELL_CLASS) { 
    *outptr = mxCreateCellArray(inptr->ndims,inptr->size);
    ret_cell = (void **) mxMalloc( sizeof(void *) * inptr->numel);
    for(i=0;i<inptr->numel;i++) { 
     	ret_cell[i] =create_identical_array_fast(inptr->cell[i],&p);
	mxSetCell(*outptr,i,p);
    }
    return ret_cell;
  }
  else { 
    mexErrMsgTxt("unsupported type used, use -nofast");
  }

  return ret;
}

/*
 * Create a MATLAB matrix object of the same shape and type of 
 * a given Matlab object
 *
 * TO DO:
 *   should be updated to include cell arrays support.
 */
void* create_identical_array(MatObj *inptr,mxArray **outptr ) { 

   *outptr = mxCreateNumericArray(inptr->ndims,inptr->size,inptr->class,mxREAL);
   return (mxGetPr(*outptr));
}

/*
 * The same as above. but data are neither allocated nor initialized
 */
void* create_identical_array_fast(MatObj *inptr,mxArray **outptr ) { 
  void* ret;
  void** ret_cell;
  mxClassID class;
  int i;
  mxArray *p;

  class = inptr->class;
  if(class != mxCELL_CLASS) { 
    *outptr = mxCreateNumericMatrix(0,0,class,mxREAL);
    mxSetDimensions(*outptr,inptr->size,inptr->ndims);
  }

  if( (class == mxDOUBLE_CLASS)  || 
      (class == mxINT64_CLASS)   ||
      (class == mxUINT64_CLASS) ) { 
     ret = mxMalloc( inptr->numel * sizeof(double));
     mxSetPr(*outptr,ret);
     return ret;
  }
  else if( (class == mxSINGLE_CLASS) ||
	   (class == mxINT32_CLASS)  ||
	   (class == mxUINT32_CLASS) ) { 
     ret = mxMalloc( inptr->numel * sizeof(int));
     mxSetPr(*outptr,ret); 
     return ret;
  }
  else if( (class == mxCHAR_CLASS) ||
	   (class == mxLOGICAL_CLASS)) { 
    ret = mxMalloc( inptr->numel * sizeof(char));
    mxSetPr(*outptr,ret); 
    return ret;
  }
  else if (class == mxCELL_CLASS) { 
    *outptr = mxCreateCellArray(inptr->ndims,inptr->size);
    ret_cell = (void **) mxMalloc( sizeof(void *) * inptr->numel);
    for(i=0;i<inptr->numel;i++) { 
     	ret_cell[i] =create_identical_array_fast(inptr->cell[i],&p);
	mxSetCell(*outptr,i,p);
    }
    return ret_cell;
  }
  else { 
    mexErrMsgTxt("unsupported type used, use -nofast");
  }
 
  return mxGetPr(*outptr);
}

/*
 * Return a pointer to the data field of the cell 
 * of index 'index' 
 * assumption the data is stored in 32-bit addressing mode
 */
int *get_cell(void *a,int index) { 
  int *ret = (int *)a;
  return ret[index];
}

/*
 * The same as above, but 64-bit addressing mode.
 */
/* double *get_cell64(void *a,int index) {  */
/*   double *ret = (double *)a; */
/*   return ret[index]; */
/* } */

/*
 * TO DO :
 * create_identical_array_type, create_cell_array
 * rename create_identical_array_* create_identical_objects
 */

void display(MatObj* M[],int n) {
 
  int i,k;

  printf("nrhs = %d\n",n); 
 
  for(i=0;i<n;i++) {
    printf("arg %d \n\tsize : %d \n",i,M[i]->numel ); 
    printf("\tnumber of dimensions : %d\n\t\t",M[i]->ndims);
    for(k=0;k < M[i]->ndims; k++)
      printf("  %d",M[i]->size[k]);
    printf("\nnrows : %d  ncols : %d\n",M[i]->size[0],M[i]->size[1] );
    printf("\n\tdata:\n\t\t");
    double *p = (double *) M[i]->data ;
    for(k=0;k < M[i]->numel; k++)
      printf(" %lf\t", p[k]);
    printf("\n");
    
    if(M[i]->class == mxCELL_CLASS) { 
      printf("cells:\n======\n");
      display(M[i]->cell,M[i]->numel);
    }

  }

}

