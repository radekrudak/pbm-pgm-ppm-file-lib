#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pgm.h"
#ifndef RAYLIB
    typedef struct Vector2  Vector2;
    struct Vector2{
        float x;
        float y;
    } ;
   
#endif
struct array_of_2dpoints{
    size_t size_of_array;
    struct Vector2 * array[];
};



float distance(float p1x,float p1y,float p2x,float p2y)
{
    return  sqrt(( (p2x-p1x) * (p2x-p1x) ) + ((p2y-p1y)*(p2y-p1y)));
}


//vector between points(not normalized)
 Vector2 vector(float p1x,float p1y,float p2x,float p2y)
{  
     Vector2 ret;
    ret.x = (p2x-p1x)/distance(p1x,p1y,p2x,p2y);
    ret.y = (p2y-p1y)/distance(p1x,p1y,p2x,p2y) ;
    //[,   ]
    return ret;
}

// return 2d coordinates of point between p1 and p2 
Vector2 between_points(float p1x,float p1y,float p2x,float p2y)
{
    Vector2 ret_vec;
    ret_vec.x = (p1x+p2x)/2;
    ret_vec.y = (p1y+p2y)/2;
    return ret_vec;//(Vector2) { (p1x+p2x)/2 , (p1y+p2y)/2 } ;
}

Vector2* get_path(float p1x,float p1y,float p2x,float p2y)
{
    struct Vector2 vec = vector(p1x,p1y,p2x,p2y);
    struct Vector2 point = {p1x,p1y};

    // this work as a stack, points are pushed on it and them returned
    Vector2 *ret_array = (Vector2*)malloc((int)distance(p1x,p1y,p2x,p2y)*(sizeof(struct Vector2))*4  );
    size_t size = distance(p1x,p1y,p2x,p2y)*(sizeof(struct Vector2))+4 ;
   
    size_t array_stack_ptr =1;


    while (distance(point.x,point.y,p2x,p2y   )>1.0f  )
    {
        point.x += vec.x;
        point.y += vec.y;
        
        ret_array[array_stack_ptr] = point;
        array_stack_ptr++;
        // if(array_stack_ptr>=size)
        // {
        //     size+=sizeof(struct Vector2);
        //     if(realloc(ret_array,size)== 0)
        //     {
        //         void * free_later = ret_array;
        //        ret_array = memcpy(malloc(size),array_stack_ptr,size);
        //         free(free_later);

        //     }
        //    // malloc
        // }


    }
    ret_array[0].x = size/sizeof(struct Vector2) +1 ; //array_stack_ptr-1;
    return ret_array;
}

void draw_triangle(pgm_file_8bit* bit_map, Vector2 p1,Vector2 p2,Vector2 p3)
{
    Vector2 *wall1 = get_path(p1.x,p1.y,p2.x,p2.y);
    Vector2 *wall2 = get_path(p3.x,p3.y,p2.x,p2.y);
    for(int i =0; i<(int)(wall1[0].x);i++)
    {   
        // printf("loop %i \n",i);
        Vector2 point;
        point.x = wall1[i].x;
        point.y = wall1[i].y;
        while(point.y>p1.y && point.y>p3.y)
        {
            point.y--;
            // printf("%f, %f, %i, %f  ",point.x, point.y,i,wall1[0].x);
            write_byte(bit_map,point.x,point.y,255);

            // printf("Bit written \n");
        }
    }
    //    printf("End of loops\n");

    for(int i =0; i<wall2[0].x;i++)
    {   Vector2 point;
        point.x = wall2[i].x;
        point.y = wall2[i].y;
        while(point.y>p1.y && point.y>p3.y)
        {
            point.y--;
            // printf("%f, %f \n",point.x, point.y);
            write_byte(bit_map,point.x,point.y,255);
        }
    }


    free (wall1);
    free (wall2);
}


void draw_sierp_triangle(pgm_file_8bit * pbm,Vector2 p1, Vector2 p2, Vector2 p3)
{

    Vector2 one = between_points(p1.x,p1.y,p2.x,p2.y);
     Vector2 two  = between_points(p1.x,p1.y,p3.x,p3.y);;
     Vector2 three =between_points(p3.x,p3.y,p2.x,p2.y);;
    draw_triangle(pbm, one,two,three);
    if (distance(p1.x,p1.y,p2.x,p2.y) > 50.0f)
    {   
        // draw left bottom triangle
        draw_sierp_triangle(pbm,p1, one, two);
        // draw right bottom triangle
        draw_sierp_triangle(pbm, two,three, p3);
        // draw top triangle
        draw_sierp_triangle(pbm, one,p2, three);
    }
}
void draw_gradient(pgm_file_8bit *pgm)
{
    for(int y=0; y < pgm->height; y++ )
    {
        for(int x=0; x< pgm->width; x++)
        {
            write_byte(pgm,x,y, x );
        }
    }
}


int main (int argc, char *argv[])
{   int resolution=5312;
    for (int i=0;i<argc;i++)
    {   
        printf("%s \n",argv[i]);
    }
    if (argc>1)
    {
        printf("\n%i",atoi(argv[1]));
        resolution =( ((int)(atoi(argv[1])/8))*8 ) ;
        printf("\n%i\n",resolution);
        
    }
    
    
    pgm_file_8bit pgm;
    
    
    init_pgm(&pgm,resolution,resolution,255);
    if(argc>1)
        draw_sierp_triangle(&pgm,(Vector2){0,pgm.height-1},(Vector2){pgm.width/2,0},(Vector2){pgm.width-1,pgm.height-1}  );
    else
        draw_gradient(&pgm);
    save_raw_8bit_pgm_to_file("test3.pgm",&pgm);



  


    return 0;
}