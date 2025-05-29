#ifndef HOST_UTILS_H
#define HOST_UTILS_H
int vector_read_hex_u32(
    FILE *fp,                          // Vector Input file data type
    int *dPtr,                         // Pointer to output array
    int num);                          // Number of elements
int vector_diff_u32(
    uint32_t *scalar1,                 // point to an array of unsigned 32-bit values
    uint32_t *scalar2,                 // point to an array of unsigned 32-bit values
    int error,                         // error tolerance
    int num_elements,                  // number of samples
    int debug);                        // debug flag
#endif
