//#include <iostream>
#include <stdio.h>
//#include <fstream>
//#include <cstring>
//#include <cstddef>
#include <stdint.h>
#include <dirent.h>
#include <stdbool.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
//#include "png.h"
//#include "zpng.h" // from https://github.com/facebook/zstd - facebook's library containing png compression
#include "zlib/zlib.h" // https://github.com/madler/zlib for compression

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "stb_image.h" // from https://github.com/nothings/stb - for reading the png file 
#include "stb_image_write.h" // from https://github.com/nothings/stb - for writing the altered files

//using namespace std;

void makeJpg()
{
    int width;
    int height;
    int channels;

    unsigned char *img = stbi_load("pie.png", &width, &height, &channels, 0);
    if(img == NULL) 
    {
        printf("Error: Cannot Load Image\n");
        exit(1);
    }


    //printf("Image has width of %dpx, height of %dpx and %d channels\n", width, height, channels);


    printf("Making Jpg Image\n");

    //printf("dsadsa\n");
    
    stbi_write_jpg("pie.jpg", width, height, channels, img, 100);
    //printf("dsadsa\n");

    stbi_image_free(img);

    return;
}


void makeGrayScale()
{
    int width;
    int height;
    int channels;

    unsigned char *img = stbi_load("pie.png", &width, &height, &channels, 0);
    if(img == NULL) 
    {
        printf("Error: Cannot Load Image\n");
        exit(1);
    }


    //printf("Image has width of %dpx, height of %dpx and %d channels\n", width, height, channels);


    printf("Making GrayScale Images\n");

    size_t img_size = width * height * channels;
    int gray_channels = channels == 4 ? 2 : 1;
    size_t gray_img_size = width * height * gray_channels;
    unsigned char *gray_img = malloc(gray_img_size);
    
    if(gray_img == NULL) 
    {
        printf("Cannot to allocate memory.\n");
        exit(1);
    }


    for(unsigned char *p = img, *pg = gray_img; p != img + img_size; p += channels, pg += gray_channels) 
    {
        *pg = (uint8_t)((*p + *(p + 1) + *(p + 2))/3.0);
        if(channels == 4) 
        {
            *(pg + 1) = *(p + 3);
        }
    }

    stbi_write_png("pie_gray.png",width, height, gray_channels, gray_img, width*gray_channels);
    //printf("dsadsa\n");
    
    stbi_write_jpg("pie_gray.jpg", width, height, gray_channels, gray_img, 100);
    //printf("dsadsa\n");

    stbi_image_free(gray_img);
    stbi_image_free(img);

    return;

}

/*
unsigned long file_size(char *filename)
{
    FILE *pFile = fopen(filename, "rb");
    fseek (pFile, 0, SEEK_END);
   unsigned long size = ftell(pFile);
    fclose (pFile);
    return size;
}

int compressImage(char *input_file_name, char *output_file_name)
{   
    FILE *infile = fopen(input_file_name, "rb");
    gzFile outfile = gzopen(output_file_name, "wb");
    if (!infile || !outfile)
    {
        return -1;
    }

    char inbuffer[128];
    int num_read = 0;
    unsigned long total_read = 0, total_wrote = 0;
    while ((num_read = fread(inbuffer, 1, sizeof(inbuffer), infile)) > 0) {
       total_read += num_read;
       gzwrite(outfile, inbuffer, num_read);
    }
    fclose(infile);
    gzclose(outfile);

    printf("Read %ld bytes, Wrote %ld bytes, Compression factor %4.2f%%\n",total_read, file_size(output_file_name), (1.0-file_size(output_file_name)*1.0/total_read)*100.0);

}
*/

int main()
{
    makeJpg();
    
    makeGrayScale();


    //compressImage("pie.png","pieCompressed.png");
    //compressImage("pie.jpg","pieCompressed.jpg");
    //compressImage("pie_gray.png","pie_gray_Compressed.png");
    //compressImage("pie_gray.jpg","pie_gray_Compressed.jpg");

    return 0;
}