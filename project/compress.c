#include <stdio.h>
#include "zlib/zlib.h"
#include "zlib/gzguts.h"


unsigned long file_size(char *filename)
{
    FILE *pFile = fopen(filename, "rb");
    fseek (pFile, 0, SEEK_END);
    unsigned long size = ftell(pFile);
    fclose (pFile);
    return size;
}

int compressImage(char* input_file_name, char* output_file_name)
{   
    FILE *infile = fopen(input_file_name, "rb");
    gzFile outfile = gzopen(output_file_name, "wb");
    
    if (!infile || !outfile)
    {
        return -1;
    }

    printf("Compressing %s to %s\n", input_file_name, output_file_name);

    char inbuffer[128];
    int num_read = 0;
    unsigned long total_read = 0;
    unsigned long total_wrote = 0;
    
    while ((num_read = fread(inbuffer, 1, sizeof(inbuffer), infile)) > 0)
    {
       total_read += num_read;
       gzwrite(outfile, inbuffer, num_read);
    }
    
    fclose(infile);
    gzclose(outfile);

    printf("Read %ld bytes, Wrote %ld bytes, Compression factor: %4.2f%%\n", total_read, file_size(output_file_name), (1.0-file_size(output_file_name)*1.0/total_read)*100.0);

}

int decompressImage(char *input_file_name, char *output_file_name)
{
    gzFile infile = gzopen(input_file_name, "rb");
    FILE *outfile = fopen(output_file_name, "wb");
    if (!infile || !outfile) return -1;

    char buffer[128];
    int num_read = 0;
    
    printf("Deompressing %s to %s\n", input_file_name, output_file_name);

    while ((num_read = gzread(infile, buffer, sizeof(buffer))) > 0)
    {
       fwrite(buffer, 1, num_read, outfile);
    }

    
    gzclose(infile);
    fclose(outfile);
}

int main()
{
    compressImage("pie.png","pieCompressed.png");
    compressImage("pie.jpg","pieCompressed.jpg");
    compressImage("pie_gray.png","pie_gray_Compressed.png");
    compressImage("pie_gray.jpg","pie_gray_Compressed.jpg");

    decompressImage("pieCompressed.png","pieDecompressed.png");
    decompressImage("pieCompressed.jpg","pieDecompressed.jpg");
    decompressImage("pie_gray_Compressed.png","pie_gray_Decompressed.png");
    decompressImage("pie_gray_Compressed.jpg","pie_gray_Decompressed.jpg");

    return 0;
}