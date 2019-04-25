/*
 * copyFile.cpp
 *
 *  Created on: 2019Äê4ÔÂ24ÈÕ
 *      Author: 10071
 */

#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#define null_item NULL


char update_package_tmp[] ="F:\\LinkToDesktop\\2019.03.21_09.44.20\\ota.zip";
char update_package[] = "F:\\LinkToDesktop\\2019.03.21_09.44.20\\ota1.zip";
int pkg_copy_res = 0;

void file_copy_main() {
    FILE *src_fp,*dst_fp;
    const int buf_size = 1024;
    char buf[buf_size];
    double src_size;
    double dst_size;
    int size;
    src_fp = fopen(update_package_tmp, "rb");
    dst_fp = fopen(update_package, "wb");
    if(src_fp == null_item) {
        pkg_copy_res = -4;
        return;
    }
    if(dst_fp == null_item) {
        pkg_copy_res = -5;
        return;
    }
    fseek(src_fp,0,SEEK_END);
    src_size = ftell(src_fp);
    dst_size = 0;
    fseek(src_fp,0,SEEK_SET);
    fseek(dst_fp,0,SEEK_SET);
    printf("SKY copy package from %s to %s\n",update_package_tmp,update_package);
    while(true) {
    	size = fread(buf,sizeof(char),buf_size,src_fp);
    	if(size > 0) {
    		fwrite(buf,sizeof(char),size,dst_fp);
    		dst_size = dst_size  + size;
    	}
    	else {
    		printf("res = %d\n",size);
    		break;
    	}
    }
    if(src_size == dst_size) {
        printf("SKY src_size,dst_size = %f\n",src_size);
        pkg_copy_res = 0;
    }
    else {
        printf("SKY src_size = %f dst_size = %f\n", src_size, dst_size);
        pkg_copy_res = -6;
    }
    fclose(src_fp);
    fclose(dst_fp);
}

int main() {
	printf("Enter main\n");
	file_copy_main();
	printf("Exit main\n");
	return 0;
}

