#include <SoftwareSerial.h>


//_______________________________motors______________________________________
int in1A = 2;
int in2A = 3;
int in1B = 4;
int in2B = 5;
int enA =6;
int enB =7;

void motor_setup()
{
 pinMode(enA, OUTPUT);
 pinMode(in1A, OUTPUT);
 pinMode(in2A, OUTPUT);
 pinMode(enB, OUTPUT);
 pinMode(in1B, OUTPUT);
 pinMode(in2B, OUTPUT);
}
void open_motor_A(int duration)
{
analogWrite(enA,100);
digitalWrite(in1A, HIGH);
digitalWrite(in2A, LOW);
delay(70); 
digitalWrite(in1A, LOW);
digitalWrite(in2A, LOW);
delay(duration);
digitalWrite(in1A, LOW);
digitalWrite(in2A, HIGH);
delay(70);
digitalWrite(in1A, LOW);
digitalWrite(in2A, LOW);
}
void open_motor_B(int duration)
{
analogWrite(enB,100);
digitalWrite(in1B, LOW);
digitalWrite(in2B, HIGH);
delay(70);
digitalWrite(in1B, LOW);
digitalWrite(in2B, LOW);
delay(duration);
digitalWrite(in1B, HIGH);
digitalWrite(in2B, LOW);
delay(70);
digitalWrite(in1B, LOW);
digitalWrite(in2B, LOW);
}

//___________________________________________________________________________


//______________________________ ultrasonic 2 ________________________________


int trig =6;
int echo =7;
int ultrasonic_power = 12;
void ultrasonic2_setup()
{
  pinMode(trig , OUTPUT);
  pinMode(ultrasonic_power , OUTPUT);
  pinMode(echo , INPUT);
}
float dis_from_ultrasonic2()
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

//_______________trainmitting data to esp__________________________
int mega_Out_slots[] ={47,46,45,44,43,42};
int esp_In_slots[]= {48,49,50,51,52,53};
const int number_of_parking_slots =6;
int free_S[number_of_parking_slots] = {0,0,0,0,0,0};
int free_count =number_of_parking_slots;

void print_arr()
{
 Serial.print("Start ");
  for(int i = 0 ; i < 6 ; i++)
  {
    Serial.print(free_S[i]);
  }
 Serial.print("free : ");
  Serial.println(free_count);

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

void setup_transmitting_data(){
  for (int index=0 ; index < number_of_parking_slots ; index++){
   pinMode(esp_In_slots[index],INPUT);    
   pinMode(mega_Out_slots[index],OUTPUT);
   }  
}

void send_data_to_esp(){
  for(int i=0; i<number_of_parking_slots ;i++){
    if(free_S[i])
    digitalWrite(mega_Out_slots[i],HIGH);
    else
    digitalWrite(mega_Out_slots[i],LOW);
  }
}
void send_data_to_Uno(int ind)
{
   Serial.write(ind);
}
void get_data_from_esp(){
  for(int i=0 ; i<number_of_parking_slots ; i++){
    //Serial.println(digitalRead(esp_In_slots[i]));
    if(digitalRead(esp_In_slots[i]) != free_S[i] &&digitalRead(mega_Out_slots[i])==LOW)
    {
      update_system_param(i , "out");
      send_data_to_Uno(i);
      //open_motor_B(5000);
    }
  }
}
//________________________End__________________________


//____________________main logic____________________

void main_logic()
{
  if (Serial.available())
  {
    char s = Serial.read();
    
    int ind = s -'0';
    //open_motor_A(5000);
    if(ind >=1 && ind <=6){
      update_system_param(ind-1, "in");
       Serial.println(ind);
       print_arr();

    
    }
    
 }
send_data_to_esp();
 get_data_from_esp();
}

//__________________________________________________



void setup() {
  Serial.begin(9600);
  motor_setup();
  setup_transmitting_data();

}

void loop() {
main_logic();
}
