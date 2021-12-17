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

    //saves magic number to the first line 
    fprintf(file_out,"P4\n");

    // converts width and height from int to C string and put it to file with white spaces
    fprintf(file_out,"%i %i\n",pbm->width,pbm->height);

    // them append to file_out byte array of pixels pointed to by pbm->pixel_array
    fwrite(pbm->pixel_array,1,pbm->width/8*pbm->height,file_out);

    fclose(file_out);
}
int get_bit (pbm_file *pbm,int x, int y);
void save_plain_pbm_to_file(char* path,pbm_file * pbm )
{
   
    FILE * file_out = fopen(path,"wb");

    //saves magic number to the first line 
    fprintf(file_out,"P1\n");

    // converts width and height from int to C string and put it to file with white spaces
    fprintf(file_out,"%i %i\n",pbm->width,pbm->height);

    // them append to file_out byte array of pixels pointed to by pbm->pixel_array
    for(int y=0; y<pbm->height;y++)
    {
        for(int x=0; x < pbm->width; x++)
        {
           fprintf(file_out,"%i ",get_bit(pbm,x,y));
        }
        fprintf(file_out,"\n");
    }

    fclose(file_out);
}


// write value to bit x at row y in pbm(file) struct.
void write_bit(pbm_file *pbm,int x, int y, int value)
{
    if (value == 0)
    {   
        // since 1 bit = 1 pixel but computers store data in bytes there is a bit of flex to acces indyvidual pixels/bits
        ((u_int8_t*)pbm->pixel_array)[y * pbm->width/8+(int)(x/8)] &=  ~(0b10000000>>x%8);
    }
    else
    {

        ((u_int8_t*)pbm->pixel_array)[y * pbm->width/8+(int)(x/8)] |= 0b10000000>>x%8;

    }
}

int get_bit (pbm_file *pbm,int x, int y)
{
    
    if(((u_int8_t*)pbm->pixel_array)[y * pbm->width/8+(int)(x/8)] & 0b10000000>>x%8)
        return 1;
    else 
        return 0;
    
}