typedef struct pbm_file pbm_file;
struct pbm_file{

    int width;
    int height;
    
    u_int8_t* pixel_array;

};

void init_pbm(pbm_file* pbm, int width,int height)
{

    pbm->width = width;
    pbm->height = height;

    pbm->pixel_array = (u_int8_t*)malloc(width/8*height);

}





void save_raw_pbm_to_file(char* path,pbm_file * pbm )
{
   
    FILE * file_out = fopen(path,"wb");

    //saves magic number to the first line (Px where x is number in aski defining type of file)
    fprintf(file_out,"P4\n");

    // temporary string to store line that contains width and height converted from int
    char width_height[1024];


    // converts width and height from int to C string
    sprintf(width_height,"%i %i\n",pbm->width,pbm->height);
    fprintf(file_out,width_height);

    // them append to file_out byte array of pixels pointed to by pbm->pixel_array
    fwrite(pbm->pixel_array,1,pbm->width/8*pbm->height,file_out);

    fclose(file_out);
}


void write_bit(pbm_file *pbm,int x, int y, int value)
{
    if (value == 0)
    {
        ((u_int8_t*)pbm->pixel_array)[(int)y/8+(int)(x/8)] &=  ~(1>>x%8);
    }
    else
    {
        ((u_int8_t*)pbm->pixel_array)[y*pbm->width/8+(int)(x/8)] |= 0b10000000>>x%8;

    }
}