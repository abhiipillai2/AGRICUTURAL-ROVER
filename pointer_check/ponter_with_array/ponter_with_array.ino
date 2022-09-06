int * BuildArray (void)
{
    static int MyArray[10]={0,1,2,3,4,5,6,7,8,9};
    return MyArray;
}   

void setup()   
{
  int tmp;
  int *TestArray;
  Serial.begin(9600);
  TestArray = BuildArray();
    
         tmp = * TestArray + 2; 
         Serial.println (tmp);
       
 }

 void loop (){
  }
 
