typedef struct pgm_file_raw_8bit pgm_file_raw_8bit;
struct pgm_file_raw_8bit{
    char* magick_number;
    int width;
    int height;
    int max_value;
    void* pixel_array;

};

typedef struct pbm_file_raw pbm_file;
typedef struct pbm_file_raw pbm_file_raw;
struct pbm_file_raw{

    int width;
    int height;
    
    u_int8_t* pixel_array;

};

void init_raw_pbm(pbm_file* pbm, int width,int height)
{

    pbm->width = width;
    pbm->height = height;
    // WARNING !!! THIS DOSN'T WORK AND DIMENSIONS THAT ARE NOT MULTIPLE OF 8 ARE NOT SUPPORTED
    //if deviding /8 gives even number(that is, width fit in even amout of bytes) ==no problem, 
    //if it isn't "round up"(in this case just divide to int and add one) and last bits shouldn't be used as file format specyfication states
    // if((float)pbm->width/8 == (int)pbm->width/8)
    pbm->pixel_array = (u_int8_t*)malloc(width*height);
    // else
    //     pbm->pixel_array = malloc( (pbm->width/8+1)*height);
}

void save_raw_pgm_to_file(char* path,pgm_file_raw_8bit * pgm )
{
    printf("%s: %i  \n", __FILE__, __LINE__ );
    FILE * file = fopen(path,"wb");

    //saves magic number to the first line (Px where x is number in aski defining type of file)
    fprintf(file,pgm->magick_number);
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

void save_raw_pbm_to_file(char* path,pbm_file * pbm )
{
   
    FILE * file_out = fopen(path,"wb");

    //saves magic number to the first line (Px where x is number in aski defining type of file)
    fprintf(file_out,"P4\n");

     printf("After magic number");

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