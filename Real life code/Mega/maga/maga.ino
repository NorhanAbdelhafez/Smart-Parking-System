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
// Serial.println("in");
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
delay(duration);

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
delay(duration);


}

//___________________________________________________________________________


//______________________________ ultrasonic 2 ________________________________


int trig =6;
int echo =7;
int ultrasonic_power = 12;
//48 --> 53
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

//____________________main logic____________________
const int number_of_parking_slots =6;
int free_S[number_of_parking_slots] = {0};
long time[number_of_parking_slots]={0};
int free_count =number_of_parking_slots;
float distance_threshhold = 35.0;
void up_date_system(int ind)
{
  free_S[ind]=1;
  time[ind]=millis();
  free_count--;
}
void up_date_system_From_esp(int ind){
  free_S[ind]=0;
  free_count++;

}
void main_logic()
{
if (Serial.available()){
  char s = Serial.read();
  int ind = s -'0';
  Serial.println(ind);
  open_motor_A(5000);
  up_date_system(ind);
}
}

//__________________________________________________
//_______________trainmitting data to esp__________________________
int mega_parking_slots[] ={47,46,45,44,43,42};
int esp_parking_slots[]= {48,49,50,51,52,53};
void setup_transmitting_data(){
  for (int index=0;index<6;index++){
   pinMode(esp_parking_slots[index],INPUT);    
   pinMode(mega_parking_slots[index],OUTPUT);
   }  
}
void send_data_to_esp(){
  for(int i=0;i<number_of_parking_slots;i++){
    if(free_S[i])
    digitalWrite(mega_parking_slots[i],HIGH);
    else
    digitalWrite(mega_parking_slots[i],LOW);
  }
}
int changes_in_esp_parking_slots[6]={0};
void get_data_from_esp(){
  for(int i=0;i<number_of_parking_slots;i++){
    if(digitalRead(esp_parking_slots[i])!=changes_in_esp_parking_slots[i]){
      up_date_system_From_esp(i);
      changes_in_esp_parking_slots[i]=esp_parking_slots[i];
      open_motor_A(5000);
    }
  }
}
//________________________End__________________________



void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
motor_setup();
setup_transmitting_data();

}

void loop() {
  // put your main code here, to run repeatedly:
main_logic();
//open_motor_A(5000);
//open_motor_B(5000);


}
