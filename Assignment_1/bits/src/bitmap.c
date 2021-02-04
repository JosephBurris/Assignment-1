#include "../include/bitmap.h"

// data is an array of uint8_t and needs to be allocated in bitmap_create
//      and used in the remaining bitmap functions. You will use data for any bit operations and bit logic
// bit_count the number of requested bits, set in bitmap_create from n_bits
// byte_count the total number of bytes the data contains, set in bitmap_create


bitmap_t *bitmap_create(size_t n_bits)
{
	int size;
	if(n_bits <= 0) {
		bitmap_t *map = NULL;
		return map;
	}
	else {
		if(n_bits%8 == 0) {
			size = n_bits/8;
		}
		else {
			size = (n_bits/8)+1;
		}

		bitmap_t *map = (bitmap_t*)malloc(sizeof(bitmap_t));
		map->data = (uint8_t*)calloc(size, sizeof(uint8_t));
		map->bit_count = n_bits;
		map->byte_count = size;
		return map;
	}
}

bool bitmap_set(bitmap_t *const bitmap, const size_t bit)
{
	if(bitmap == NULL) {
		return false;
	}
	if(bit < 0) {
		return false;
	}	
	if(bit > 255) {
		return false;
	}
	
	int i = bit/8;
	int index = bit%8;
	unsigned int f = 1;
	f = f << index;
	bitmap->data[i] = bitmap->data[i] | f;
	
	return true;
}

bool bitmap_reset(bitmap_t *const bitmap, const size_t bit)
{
	if(bitmap == NULL) {
                return false;
        }
        if(bit < 0) {
                return false;
        }
        if(bit > 255) {
                return false;
        }
	
	int i = bit/8;
        int index = bit%8;
        unsigned int f = 1;
        f = f << index;
	f = ~f;
	bitmap->data[i] = bitmap->data[i] & f;
	
	return true;
}

bool bitmap_test(const bitmap_t *const bitmap, const size_t bit)
{
	if(bitmap == NULL) {
                return false;
        }
        if(bit < 0) {
                return false;
        }
        if(bit > 255) {
                return false;
        }
	
	int i = bit/8;
        int index = bit%8;
        unsigned int f = 1;
        f = f << index;
	if(bitmap->data[i] & f) {
		return true;
	}
	else {
		return false;
	}
}

size_t bitmap_ffs(const bitmap_t *const bitmap)
{
	if(bitmap == NULL) {
                return SIZE_MAX;
        }
	size_t max = bitmap->bit_count;
	size_t count;
	for(count= 0; count < max; count++) {
		if(bitmap_test(bitmap, count)) {
			return count;
		}
	}
	return SIZE_MAX;
}

size_t bitmap_ffz(const bitmap_t *const bitmap)
{
	if(bitmap == NULL) {
                return SIZE_MAX;
        }
	size_t max = bitmap->bit_count;
	size_t count = 0;
	for(count= 0; count < max; count++) {
                if(bitmap_test(bitmap, count) == false) {
                        return count;
                }
        }
        return SIZE_MAX;
}

bool bitmap_destroy(bitmap_t *bitmap)
{
	if(bitmap == NULL) {
		return false;
	}
	else {
		free(bitmap->data);
		free(bitmap);
		return true;
	}
}
