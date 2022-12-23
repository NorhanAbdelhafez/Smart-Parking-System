

#include <LiquidCrystal.h> 
#include <Keypad.h>



//______________________________ LCD________________________________
LiquidCrystal lcd(A0,A1,A2,A3,A4,A5); //4-bit mode; connect d0-d3 in addition for 8-bit mode
void lcd_setup()
{
    lcd.begin(16,2);
}
void lcd_loop(String line1, String line2 )
{
  
      lcd.setCursor(0,0); 
      lcd.print(line1); 
      lcd.setCursor(0,1); 
      lcd.print(line2); 

}
//___________________________________________________________________


//______________________________ keypad________________________________
const byte ROWS = 4;
const byte COLS = 4;
//Assign key values in 4x4 matrix
char keys[ROWS][COLS] = {
  {'1','2','A','3'},
  {'4','5','B','6'},
  {'7','8','C','9'},
  {'*','0','D','#'}
};
byte rowPins[ROWS] = {2, 3, 4, 5}; //R1,R2,R3,R4
//connect to the column pinouts of the keypad
byte colPins[COLS] = {6, 7, 8, 9};//C1,C2,C3,C4

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
String keypad_loop()
{
  
  char key = ' ';
  key = keypad.getKey();
  if (key) {
    Serial.println(key);

    lcd.clear();
    String s ="";
    s+=key;
    return s;
  }
  return "";

}

//___________________________________________________________________


//______________________________ ultrasonic 1 ________________________________


int trig =11;
int echo =10;
int ultrasonic_power = 12;
void ultrasonic1_setup()
{
  pinMode(trig , OUTPUT);
  pinMode(ultrasonic_power , OUTPUT);
  pinMode(echo , INPUT);
}
float dis_from_ultrasonic1()
{
  digitalWrite(ultrasonic_power,HIGH);
  digitalWrite(trig,LOW);
  delayMicroseconds(2);
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  float Zeit = pulseIn(echo,HIGH);
  float Strecke=Zeit*0.017;
  return Strecke ; 
}
//___________________________________________________________________

//______________________________main logic ________________________________
const int number_of_parking_slots =6;
int free_S[number_of_parking_slots] = {0};
int free_count =number_of_parking_slots;
float distance_threshhold = 35.0;
int first_free_index()
{
  for(int i=0 ; i<number_of_parking_slots ; i++)
  {
    if(free_S[i]==0)
    {
      return i;
    }
   
  }
}

void update_system_param(int index, String status)
{
  if(status == "in")
  {
    free_S[index]=1;
    free_count--;
  }
  else if(status == "out")
  {
    free_S[index]=0;
    free_count++;
  }
}
void main_logic()
{
    if(dis_from_ultrasonic1()<= distance_threshhold )
    {
      if(free_count)
      {
          int index= first_free_index()+1;
          String s1 = "Your Slot is: " + String(index);
          String s2 =  String(index)+ " To confirm";
          lcd_loop(s1 , s2);
          if(keypad_loop()==String(index))
          {
              send_data_to_mega(index);
              update_system_param(index-1 , "in");
              recive_data_from_mega();
              lcd.clear();
              lcd_loop("Welcome , go to" , "slote "+String(index));
              delay(5000);

          }

      }
      else
      {
         lcd_loop("I am Full :(" ,"Come Back later");
      }
    }
    else
    {
      lcd.clear();
    }
}
//___________________________________________________________________

//______________Connection between mega and arduino__________________
void send_data_to_mega(int indexOfCar){
  Serial.write(indexOfCar);
}
void recive_data_from_mega(){
 if (Serial.available()){
    char s = Serial.read();
     int ind = s -'0';
     update_system_param(ind , "out");
 }  
}
//___________________________________________________________________
void setup() 
{ 
  Serial.begin(9600);
  lcd_setup();
  ultrasonic1_setup();
} 

void loop() 
{ 
  main_logic();
} 
