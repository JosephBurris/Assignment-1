#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "../include/sys_prog.h"

// LOOK INTO OPEN, READ, WRITE, CLOSE, FSTAT/STAT, LSEEK
// GOOGLE FOR ENDIANESS HELP

bool bulk_read(const char *input_filename, void *dst, const size_t offset, const size_t dst_size)
{
	if(input_filename == NULL) {
		return false;
	}
	if(dst == NULL) {
		return false;
	}
	if(dst_size < offset) {
		return false;
	}
	if(dst_size <= 0) {
		return false;
	}
	if(strpbrk(input_filename, "\n")) {
		return false;
	}
	else if(strpbrk(input_filename, "\0")) {
		return false;
	}
	
	int file;
	int goodRead;

	file = open(input_filename, O_RDONLY, 0);
	if (file <= 0) {
		return false;
	}
	
	goodRead = read(file, dst, dst_size);
	if(goodRead < 0) {
		return false;
	}
	return true;
}

bool bulk_write(const void *src, const char *output_filename, const size_t offset, const size_t src_size)
{
	if(src == NULL) {
		return false;
	}
	if(output_filename == NULL) {
		return false;
	}
	if(src_size <= 0) {
		return false;
	}
	if(strpbrk(output_filename, "\n")) {
		return false;
	}
	else if(strpbrk(output_filename, "\0")) {
		return false;
	}

	int file;
	int check;
	
	file = open(output_filename, O_WRONLY, 0);
	if(file < 0) {
		return false;
	}
	check = write(file, src, src_size);
	if(check < 0) {
		return false;
	}
	return true;
}


bool file_stat(const char *query_filename, struct stat *metadata)
{
	if(query_filename == NULL) {
		return false;
	}
	if(metadata == NULL) {
		return false;
	}

	int check = stat(query_filename, metadata);
	
	if(check == -1) {
		return false;
	}
	else {
		return true;
	}
}

bool endianess_converter(uint32_t *src_data, uint32_t *dst_data, const size_t src_count)
{
	if(src_data == NULL) {
		return false;
	}
	if(dst_data == NULL) {
		return false;
	}
	if(src_count <= 0) {
		return false;
	}
	
	uint32_t b0,b1,b2,b3;

	b0 = (*src_data & 0x000000ff) << 24u;
	b1 = (*src_data & 0x0000ff00) << 8u;
	b2 = (*src_data & 0x00ff0000) >> 8u;
	b3 = (*src_data & 0xff000000) >> 24u;

	*dst_data  = b0 | b1 | b2 | b3;
	if(dst_data != NULL ) {
		return true;
	}
	return false;
}

