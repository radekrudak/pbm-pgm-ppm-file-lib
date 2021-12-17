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
    fprintf(file,"%i %i\n",pgm->width,pgm->height); // appends width and height to a file + white characters




    fprintf(file,"%i\n",pgm->max_value);// them appends max_value+'\n' to file

    // them append to file byte array of pixels pointed to by pgm->pixel_array
    fwrite(pgm->pixel_array,1,pgm->width*pgm->height,file);
    fclose(file); // close fil
}


void save_plain_8bit_pgm_to_file(char* path,pgm_file_8bit * pgm )
{
   
    FILE * file = fopen(path,"wb");

    //saves magic number to the first line 
    fprintf(file,"P2");
    fprintf(file,"\n");

    // temporary string to store line that contains width and height converted from int




    fprintf(file,"%i %i\n",pgm->width,pgm->height); // appends width and height to a file + white characters




    fprintf(file,"%i\n",pgm->max_value);// them appends max_value+'\n' to file

    
    for(int y=0; y<pgm->height;y++)
    {
        for(int x=0; x < pgm->width; x++)
        {
            fprintf(file,"%i ",pgm->pixel_array[y*pgm->width+x]);
        }
        fprintf(file,"\n");
    }
    fclose(file); // close file
}




void write_byte(pgm_file_8bit *pgm,int x,int y, u_int8_t value)
{
    pgm->pixel_array[y*pgm->width+x] = value;
}