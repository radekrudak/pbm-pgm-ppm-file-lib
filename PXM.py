import numpy
class value_too_big_error(Exception):
    pass


class pxm_file():
    what_type:str
    type_dyctionary = {
       "P1":"P1",
       "P2":"P2",
       "P3":"P3",
       "P4":"P4",
       "P5":"P5",
       "P6":"P6",
        "pbm":"P1",
        ".pbm":"P1",
        "pgm":"P2",
        ".pgm":"P2",
        "ppm":"P3",
        ".ppm":"P3",

    }
    width:int
    height:int
    max_value:float
    matrix= [[]]
    comment:str
    def __init__(self,width:int, height:int, default_value, max_value, what_type:str):
        self.width = width
        self.height =height
        self.max_value = max_value
        self.matrix = numpy.ones((self.height,self.width),numpy.int8)
        self.matrix *= default_value
        self.what_type = self.type_dyctionary[what_type]
        if self.type_dyctionary[what_type] == 'P1':
            self.max_value = 1
    def set_pixel(self,x,y,val:int):
        if val<= self.max_value:
            self.matrix[y][x] = val 
        else:
            raise value_too_big_error ("Given value is bgger than max value you chosen")       

    def get_pxiel(self,x,y):
        return self.matrix[y][x]
    

            
    def save_to_file(self,path:str, comment=''):
        self.comment = comment

        if int(self.what_type[1]) >=3:
            file = open(path, 'w')
            file.write('')
            file.close()

            file = open(path,'ba')
            
            file.write(bytes(self.what_type+'\n', 'utf-8'))
            file.write(bytes('#'+self.comment+"\n", 'utf-8'))
            file.write(bytes(str(self.width)+" "+str(self.height)+'\n', 'utf-8'))
            file.write(bytes(str(self.max_value)+'\n', 'utf-8'))

                    
            for y in range(self.height):
                    for x in range(self.width):
                        file.write(bytes(self.get_pxiel(x,y)))

        else:
            file = open(path, 'w')
            file.write('')
            file.close()

            file = open(path,'a')
            
            file.write(self.what_type+'\n')
            file.write('#'+self.comment+"\n")
            file.write(str(self.width)+" "+str(self.height)+'\n')
            file.write(str(self.max_value)+'\n')

                        
                
        
            for y in range(self.height):
                for x in range(self.width):
                    file.write(str(self.get_pxiel(x,y)))
                    file.write(' ')
                file.write('\n')


            file.close()
