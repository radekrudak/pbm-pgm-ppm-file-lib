#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pbm.h"
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



    }
    ret_array[0].x = size/sizeof(struct Vector2) +1 ; //array_stack_ptr-1;
    return ret_array;
}
// p1 = top-left point, p2, bottom point, p3= right-top one.
void draw_triangle(pbm_file* bit_map, Vector2 p1,Vector2 p2,Vector2 p3)
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
            write_bit(bit_map,point.x,point.y,1);

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
            write_bit(bit_map,point.x,point.y,1);
        }
    }

    free (wall1);
    free (wall2);
}


void draw_sierp_triangle(pbm_file * pbm,Vector2 p1, Vector2 p2, Vector2 p3)
{

    Vector2 one = between_points(p1.x,p1.y,p2.x,p2.y);
    Vector2 two  = between_points(p1.x,p1.y,p3.x,p3.y);
    Vector2 three =between_points(p3.x,p3.y,p2.x,p2.y);

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



int main (int argc, char *argv[])
{   int resolution=0;
    for (int i=0;i<argc;i++)
    {   
        printf("%s \n",argv[i]);
    }
    if (argc>=1)
    {
        printf("\n%i",atoi(argv[1]));
        resolution =( ((int)(atoi(argv[1])/8))*8 ) ;
         printf("\n%i\n",resolution);
        
    }
    
    
    pbm_file pbm;
    

    init_pbm(&pbm,resolution,resolution);

    draw_sierp_triangle(&pbm,(Vector2){0,pbm.height-1},(Vector2){pbm.width/2,0},(Vector2){pbm.width-1,pbm.height-1}  );

    save_raw_pbm_to_file("example.pbm",&pbm);


    for(int y=0; y<pbm.height;y++)
    {
        for(int x=0;x<pbm.width;x++)
        {
            write_bit(&pbm,x,y,get_bit(&pbm,x,y));
        }

    }
    save_raw_pbm_to_file("test.pbm",&pbm);
    save_plain_pbm_to_file("test_plain.pbm",&pbm);

    return 0;
}