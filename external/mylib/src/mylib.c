#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mylib.h"

typedef struct mylib_vector_t {
  int64_t n;
  float *data;
};

mylib_error_t mylib_vector_generate_random(const int64_t n,
                                           mylib_vector_t **v) {
  if (n <= 0 || v == NULL) {
    return MYLIB_ERROR_INVALID_ARG;
  }

  mylib_vector_t *new_vector = (mylib_vector_t *)malloc(sizeof(mylib_vector_t));
  if (new_vector == NULL) {
    return MYLIB_ERROR_OUT_OF_MEMORY;
  }

  new_vector->n = n;
  new_vector->data = (float *)malloc(n * sizeof(float));
  if (new_vector->data == NULL) {
    free(new_vector);
    return MYLIB_ERROR_OUT_OF_MEMORY;
  }

  for (int64_t i = 0; i < n; i++) {
    new_vector->data[i] = (float)rand() / RAND_MAX;
  }

  *v = new_vector;
  return MYLIB_ERROR_SUCCESS;
}

mylib_error_t mylib_vector_set_element(mylib_vector_t *v, const int64_t i,
                                       const float x) {
  if (v == NULL) {
    return MYLIB_ERROR_INVALID_ARG;
  }

  if (i < 0 || i >= v->n) {
    return MYLIB_ERROR_INVALID_DOMAIN;
  }

  v->data[i] = x;
  return MYLIB_ERROR_SUCCESS;
}

mylib_error_t mylib_vector_free(mylib_vector_t *v) {
  if (v == NULL) {
    return MYLIB_ERROR_INVALID_ARG;
  }

  free(v->data);
  free(v);
  return MYLIB_ERROR_SUCCESS;
}

mylib_error_t mylib_vector_dot_product(const mylib_vector_t *v1,
                                       const mylib_vector_t *v2,
                                       float *result) {
  if (v1 == NULL || v2 == NULL || result == NULL) {
    return MYLIB_ERROR_INVALID_ARG;
  }

  if (v1->n != v2->n) {
    return MYLIB_ERROR_INVALID_DOMAIN;
  }

  *result = 0.0f;
  for (int64_t i = 0; i < v1->n; i++) {
    *result += v1->data[i] * v2->data[i];
  }

  return MYLIB_ERROR_SUCCESS;
}
