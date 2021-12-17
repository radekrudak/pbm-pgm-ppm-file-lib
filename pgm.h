typedef struct pgm_file_8bit pgm_file_8bit;
struct pgm_file_8bit{
  
    int width;
    int height;
    int max_value;
    u_int8_t* pixel_array;

};


void init_pgm(pgm_file_8bit* pgm, int width,int height, int max_value)
{

    pgm->width = width;
    pgm->height = height;
    pgm->max_value = max_value;
    pgm->pixel_array = (u_int8_t*)malloc(width*height);

}



void save_raw_8bit_pgm_to_file(char* path,pgm_file_8bit * pgm )
{
   
    FILE * file = fopen(path,"wb");

    //saves magic number to the first line 
    fprintf(file,"P5");
    fprintf(file,"\n");

    // temporary string to store line that contains width and height converted from int
    char width_height[1024];


    // converts width and height from int to C string
    sprintf(width_height,"%i %i\n",pgm->width,pgm->height);
    fprintf(file,width_height); // and them appends them to file


    // uses width_height string to store line containing nformation about max value sotred per pixel converted from int
    sprintf(width_height,"%i\n",pgm->max_value);
    fprintf(file,width_height);// them appends string to file

    // them append to file byte array of pixels pointed to by pgm->pixel_array
    fwrite(pgm->pixel_array,1,pgm->width*pgm->height,file);
    fclose(file); // close file
}







void write_byte(pgm_file_8bit *pgm,int x,int y, u_int8_t value)
{
    pgm->pixel_array[y*pgm->width+x] = value;
}