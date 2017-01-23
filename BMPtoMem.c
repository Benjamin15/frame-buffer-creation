// super-simplified BMP read algorithm to pull out RGB data
 // read image for coloring scheme
 
#include <stdio.h>
 
int main(){
    int i,j;
 
    FILE *streamIn, *fsout_r, *fsout_g, *fsout_b;
    char* inputFile = "./img_test2.bmp";
    char* output_r = "output_r.txt";
    char* output_g = "output_g.txt";
    char* output_b = "output_b.txt";
 
    streamIn = fopen(inputFile, "r");
    if (streamIn == (FILE *)0){
        printf("File opening error ocurred. Exiting program.\n");
        return -1;
    }
 
    fseek(streamIn, 18, SEEK_SET); // nilai width bmp ada di offset 18 pd header
    int width = getc(streamIn);
    fseek(streamIn, 22, SEEK_SET); // nilai height bmp ada di offset 22 pd header
    int height = getc(streamIn);
 
    int bpp = 24;   //24 -> RGB, 32 -> RGBA
    int image[width*height][bpp/8]; // without header.
   
    fseek(streamIn, 54, SEEK_SET); // seek sream pointer to the end of bmp header
    // file bmp punya header, ukurannya 54 Bytes (fixed). tapi bisa berubah mengikuti perkembangan :v (katanya gitu)
   
    fsout_r = fopen(output_r, "w");
    fsout_g = fopen(output_g, "w");
    fsout_b = fopen(output_b, "w");
 
    for (i=1; i<=height; i++) {             // baris pixel, baris 1 paling bawah
        for (j=1; j<=width; j++){           // kolom pixel, kolom 1 paling kiri
            image[i][2] = getc(streamIn);   // use BMP 24bit with no alpha channel
            image[i][1] = getc(streamIn);   // BMP uses BGR but we want RGB, grab byte-by-byte
            image[i][0] = getc(streamIn);   // reverse-order array indexing fixes RGB issue...
 
            printf("pixel %d,%d : [%d,%d,%d]\n",i,j,image[i][0],image[i][1],image[i][2]);
 
            // print ke file
            fprintf(fsout_r, "%3d ", image[i][0]);
            fprintf(fsout_g, "%3d ", image[i][1]);
            fprintf(fsout_b, "%3d ", image[i][2]);
        }
        fprintf(fsout_r,"\n");
        fprintf(fsout_g,"\n");
        fprintf(fsout_b,"\n");
    }
 
    fclose(streamIn);
    fclose(fsout_r);
    fclose(fsout_g);
    fclose(fsout_b);
 
    printf("Image width: %d\n", width);
    printf("Image height: %d\n", height);
 
    return 0;
}