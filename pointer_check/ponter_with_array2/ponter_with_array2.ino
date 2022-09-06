
void setup()   
{
  int tmp;
  int *TestArray;
  Serial.begin(9600);
  TestArray = BuildArray(2);
    
         tmp = * TestArray + 1; 
         Serial.println (tmp);
       
 }

 void loop (){
  }

 int * BuildArray (int test)
{
    static int MyArray[10]={0,0,0,0};

    if(test == 1){

      MyArray[0] = 1;
      MyArray[1] = 2;
      MyArray[2] = 3;
      MyArray[3] = 4;
      return MyArray;
      
    }else if(test == 2){
      MyArray[0] = 6;
      MyArray[1] = 7;
      MyArray[2] = 8;
      MyArray[3] = 9;
      return MyArray;
    }
}   
