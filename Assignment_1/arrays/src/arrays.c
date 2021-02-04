#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "../include/arrays.h"

// LOOK INTO MEMCPY, MEMCMP, FREAD, and FWRITE

bool array_copy(const void *src, void *dst, const size_t elem_size, const size_t elem_count)
{
	if(src == NULL) {
		return false;
	}
	else if(dst == NULL) {
		return false;
	}
	else if(elem_count <= 0) {
		return false;
	}
	else if(elem_size <= 0) {
		return false;
	}
	else {
		memcpy(dst,src,(int)elem_count * (sizeof(elem_size)));
		return true;
	}
}

bool array_is_equal(const void *data_one, void *data_two, const size_t elem_size, const size_t elem_count)
{
	if(data_one == NULL || data_two == NULL || elem_count <= 0 || elem_size <= 0) {
		return false;
	}

	int compare = memcmp(data_one, data_two, elem_count);

	if(compare == 0) {
		return true;
	}
	else {
		return false;
	}
}

ssize_t array_locate(const void *data, const void *target, const size_t elem_size, const size_t elem_count)
{
	if(data == NULL || target == NULL || elem_size <= 0 || elem_count <= 0) {
		return -1;
	}

	size_t x;
	int y;
	

	for(x = 0; x < elem_count; x++) {
		y = memcmp(data, target, elem_size);
		if (y == 0) {
			return x;
		}
		data = data + elem_size;
	}
	return -1;
}

bool array_serialize(const void *src_data, const char *dst_file, const size_t elem_size, const size_t elem_count)
{
	if(src_data == NULL || dst_file == NULL || elem_size <= 0 || strlen(dst_file) <= 0 || elem_count <= 0) {
		return false;
	}

	FILE *f;
	f = fopen(dst_file, "w");

	if(f == NULL) {
		return false;
	}
	else if(ferror(f) != 0) {
		return false;
	}

	else if(strpbrk(dst_file, "\n")) {
		return false;
	}
	else {
		fwrite(src_data, elem_size, elem_count, f);
		fclose(f);
		return true;
	}
}

bool array_deserialize(const char *src_file, void *dst_data, const size_t elem_size, const size_t elem_count)
{
	if(NULL == src_file || NULL == dst_data || 0 >= elem_size || 0 >= elem_count || 0 >= strlen(src_file))
		{
			return false;
		}
	FILE* f;
	f = fopen(src_file, "r");
	if(f == NULL){
		return false;
	}
	else if(ferror(f) != 0)
	{
		return false;
	}
	else if(strpbrk(src_file, "\n")){
		return false;
	}
	else{
		fread(dst_data, elem_size, elem_count, f);
		fclose(f);
		return true;
	}
}

