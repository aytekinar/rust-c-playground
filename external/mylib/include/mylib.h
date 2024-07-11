#ifndef __MYLIB_H_
#define __MYLIB_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef enum mylib_error_t {
  MYLIB_ERROR_SUCCESS = 0,
  MYLIB_ERROR_OUT_OF_MEMORY,
  MYLIB_ERROR_INVALID_ARG,
  MYLIB_ERROR_INVALID_DOMAIN,
  MYLIB_ERROR_UNKNOWN,
} mylib_error_t;

typedef struct mylib_vector_t mylib_vector_t;

mylib_error_t mylib_vector_generate_random(const int64_t n, mylib_vector_t **v);
mylib_error_t mylib_vector_set_element(mylib_vector_t *v, const int64_t i,
                                       const float x);
mylib_error_t mylib_vector_free(mylib_vector_t *v);
mylib_error_t mylib_vector_dot_product(const mylib_vector_t *v1,
                                       const mylib_vector_t *v2, float *result);

#ifdef __cplusplus
}
#endif

#endif
