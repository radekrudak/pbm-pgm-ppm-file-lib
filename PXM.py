class pxm_file():
    what_type:str
    type_dyctionary = {
       "P1":"P1",
       "P2":"P2",
       "P3":"P3",
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
    def __init__(self,width:int,height:int,default_value,max_value,what_type:str):
        self.width = width
        self.height =height
        self.max_value = max_value
        self.matrix = [[default_value]*self.width]*self.height
        self.what_type = self.type_dyctionary[what_type]
        if self.type_dyctionary[what_type] == 'P1':
            max_value = 1
    def SetPixel(self,x,y,val):
        pass
    def GetPixel(self,x,y):
        return self.matrix[y][x]
    def SaveToFile(self,path:str):
        file = open(path, 'w')
        file.write('')
        file.close()

        file = open(path,'a')

        file.write(self.what_type+'\n')
        file.write(str(self.width)+" "+str(self.height)+'\n')
        file.write(str(self.max_value)+'\n')

        for y in range(self.height):
            for x in range(self.width):
                file.write(str(self.GetPixel(x,y)))
                file.write(' ')
            file.write('\n')


        file.close()


a = pxm_file(2, 2, 10,20,'P2')
print(a.width)
print(a.height)
print(a.matrix)

a.SaveToFile("HelloWorld.pgm")