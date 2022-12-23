#include "WiFi.h"
#include "ESPAsyncWebServer.h"
const char index_html[] PROGMEM = R"rawliteral(

<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>3N&AMA Garage</title>
    <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
    <link
        href="https://fonts.googleapis.com/css2?family=Work+Sans:ital,wght@0,100;0,200;0,300;0,400;0,500;0,600;0,700;0,800;1,100;1,200;1,300;1,400;1,500;1,600;1,700&display=swap"
        rel="stylesheet">
</head>

<body>
    <div class="header">
    </div>

    <div class="header">

        <div class="container">
            <span style=" color: white;"><span style="color: #ff7b73;font-weight: bold; font-size: 50px;">3N&AMA</span>
                Premium Car Garage</span>
            <div class="number-of-cars">
                <span id="numberOfBusySlots">2</span>
            </div>
        </div>
    </div>

    <!-- slots cards -->
    <div class="garage-slots">
        <div class="container">

            <div class="card">
                <div class="box">
                    <div class="content">
                        <h2>01</h2>
                        <h3>Slot 1</h3>
                        <a class="slot1" id="slot1">FULL</a>
                    </div>
                </div>
            </div>

            <div class="card">
                <div class="box">
                    <div class="content">
                        <h2>02</h2>
                        <h3>Slot 2</h3>
                        <a class="slot2" id="slot2">Busy</a>
                    </div>
                </div>
            </div>

            <div class="card">
                <div class="box">
                    <div class="content">
                        <h2>03</h2>
                        <h3>Slot 3</h3>
                        <a class="slot3" id="slot3">Empty</a>
                    </div>
                </div>
            </div>

            <div class="card">
                <div class="box">
                    <div class="content">
                        <h2>04</h2>
                        <h3>Slot 4</h3>
                        <a class="slot4" id="slot4">Empty</a>
                    </div>
                </div>
            </div>

            <div class="card">
                <div class="box">
                    <div class="content">
                        <h2>05</h2>
                        <h3>Slot 5</h3>
                        <a class="slot5" id="slot5">Empty</a>
                    </div>
                </div>
            </div>

            <div class="card">
                <div class="box">
                    <div class="content">
                        <h2>06</h2>
                        <h3>Slot 6</h3>
                        <a class="slot6" id="slot6">Busy</a>
                    </div>
                </div>
            </div>
        </div>
    </div>


</body>
<style>
    :root {

        --full-color: #BA3B0A;
        --empty-color: #23c186;

    }

    * {
        margin: 0px;
        padding: 0px;
        -webkit-box-sizing: border-box;
        -moz-box-sizing: border-box;
        box-sizing: border-box;
    }

    html {
        scroll-behavior: smooth;
    }

    body {
        font-family: "Work Sans", sans-serif;
        background-color: black;
    }


    .container {
        width: 600px;
        padding-left: 15px;
        padding-right: 15px;
        margin-left: auto;
        margin-right: auto;
        background: black;
    }

    .header .container {
        display: flex;
        justify-content: space-between;
        align-items: center;
        padding-top: 10px;
    }

    .header .logo {
        width: 21%;
        height: auto;
        transition-duration: 0.5s;
    }

    /* Small */
    @media (min-width: 768px) {
        .container {
            width: 750px;
        }
    }

    /* Medium */
    @media (min-width: 992px) {
        .container {
            width: 970px;
        }
    }

    /* Large */
    @media (min-width: 1200px) {
        .container {
            width: 1170px;
        }
    }

    .garage-slots {
        padding-top: 60px;
        padding-bottom: 60px;
        background-color: black;
    }

    .garage-slots .container {

        display: grid;
        grid-template-columns: repeat(auto-fill, minmax(300px, 1fr));
        grid-gap: 0px;
    }

    .garage-slots .content {
        padding-left: 20px;
        padding-right: 20px;
        text-align: center;

    }



    body .container .card {
        position: relative;
        min-width: 320px;
        height: 200px;
        box-shadow: inset 5px 5px 5px rgba(0, 0, 0, 0.2),
            inset -5px -5px 15px rgba(255, 255, 255, 0.1),
            5px 5px 15px rgba(0, 0, 0, 0.3), -5px -5px 15px rgba(255, 255, 255, 0.1);
        border-radius: 15px;
        margin: 30px;
        transition: 0.5s;
    }


    .box a {
        background: var(--empty-color);
    }

    .box .slot2,
    .box .slot6 {
        background: var(--full-color);
    }

    body .container .card .box {
        position: absolute;
        top: 20px;
        left: 20px;
        right: 20px;
        bottom: 20px;
        background: #2a2b2f;
        border-radius: 15px;
        display: flex;
        justify-content: center;
        align-items: center;
        overflow: hidden;
        transition: 0.5s;
    }

    body .container .card .box:hover {
        transform: translateY(-22px);
    }

    body .container .card .box:before {
        content: "";
        position: absolute;
        top: 0;
        left: 0;
        width: 50%;
        height: 100%;
        background: rgba(255, 255, 255, 0.03);
    }

    body .container .card .box .content {
        padding: 20px;
        text-align: center;
    }

    body .container .card .box .content h2 {
        position: absolute;
        top: -10px;
        right: 30px;
        font-size: 8rem;
        color: rgba(255, 255, 255, 0.1);
    }

    body .container .card .box .content h3 {
        font-size: 1.8rem;
        color: #fff;
        z-index: 1;
        transition: 0.5s;
        margin-bottom: 15px;
    }

    body .container .card .box .content p {
        font-size: 1rem;
        font-weight: 300;
        color: rgba(255, 255, 255, 0.9);
        z-index: 1;
        transition: 0.5s;
    }

    body .container .card .box .content a {
        position: relative;
        display: inline-block;
        padding: 8px 20px;
        border-radius: 5px;
        text-decoration: none;
        color: white;
        margin-top: 20px;
        box-shadow: 0 10px 20px rgba(0, 0, 0, 0.2);
        transition: 0.5s;
    }

    body .container .card .box .content a:hover {
        box-shadow: 0 10px 20px rgba(0, 0, 0, 0.6);
        background: #fff;
        color: #000;
    }

    .buttons .container {
        margin-top: 20px;
        display: flex;
        justify-content: space-between;
        align-items: center;

    }

    .number-of-cars {
        margin-top: 20px;
        display: table;
        overflow: hidden;
        text-align: center;
        width: 120px;
        height: 120px;
        background-color: #000000;
        border-radius: 50%;
        box-shadow:
            inset 0 0 10px #fff,
            inset 10px 0 10px #000,
            inset -10px 0 10px #000,
            inset 10px 0 100px #000,
            inset -10px 0 100px #000,
            0 0 25px #fff,
            0 0 10px #fff,
            0 0 10px #000;


    }

    .number-of-cars span {
        display: table-cell;
        vertical-align: middle;
        font-size: 40px;
        font-weight: 400;
        color: rgb(255 255 255 /80%);
    }
</style>
<script>
    if (!!window.EventSource) {
        var source = new EventSource('/events');

        source.addEventListener('open', function (e) {
            console.log("Events Connected");
        }, false);
        source.addEventListener('error', function (e) {
            if (e.target.readyState != EventSource.OPEN) {
                console.log("Events Disconnected");
            }
        }, false);

        source.addEventListener('message', function (e) {
            console.log("message", e.data);
        }, false);

        source.addEventListener('busy', function (e) {
            console.log("busy", e.data);
            setBusy(e.data)
        }, false);

        source.addEventListener('empty', function (e) {
            console.log("empty", e.data);
            setEmpty(e.data)
        }, false);

        source.addEventListener('totlabusy', function (e) {
            console.log("totlabusy", e.data);
            getNumberOfBusy(e.data)
        }, false);

        function getNumberOfBusy(x) {
            document.getElementById("numberOfBusySlots").innerHTML = x;
        }
        function setBusy(x) {
            var slot = document.getElementById("slot" + x.toString());
            slot.style.backgroundColor = "#BA3B0A";
            slot.textContent = "Busy"
        }
        function setEmpty(x) {
            var slot = document.getElementById("slot" + x.toString());
            slot.style.backgroundColor = "#23c186";
            slot.textContent = "Empty"
        }

    }

</script>

</html>

)rawliteral";
 


const char customer_html[] PROGMEM = R"rawliteral(

<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>3N&AMA Garage</title>
    <link rel="stylesheet" href="css/customer.css">
    <link rel="stylesheet" href="css/normalize.css" <link rel="preconnect" href="https://fonts.googleapis.com">
    <link rel="stylesheet" href="css/all.min.css">
    <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
    <link
        href="https://fonts.googleapis.com/css2?family=Work+Sans:ital,wght@0,100;0,200;0,300;0,400;0,500;0,600;0,700;0,800;1,100;1,200;1,300;1,400;1,500;1,600;1,700&display=swap"
        rel="stylesheet">
</head>

<body>
    <div class="header">

        <div class="container">
            <span style=" color: white;"><span style="color: #ff7b73;font-weight: bold; font-size: 50px;">3N&AMA</span>
                Premium Car Garage</span>
            <div class="number-of-cars">
                <span>2</span>
            </div>
        </div>
    </div>
    <div class="header">

        <div class="container">
            <span class="landing-text">Welcome To Our Garage :)</span>
        </div>
        <div class="container">
            <span class="fees">Please Pay your Fees to open the gate</span>
        </div>

        <div class="container">

            <div class="container__item" id="inputContainer">
                <form action="/get">
                    <input type="number" class="form__field" placeholder="Enter Your Slot Number" name="input_integer"
                        id="paySlotText" required min="0" max="6" />
                    <input type="submit" onclick="a()" class="btn btn--primary btn--inside uppercase"
                        id="paySlotButton">Pay</input>
                </form>
            </div>



        </div>
        <div class="container">
            <span style="color: white; display: none;" id="thankMessage">Thank You, The Door Will Open!😊</span>
        </div>
</body>

<style>
    :root {

        --full-color: #BA3B0A;
        --empty-color: #23c186;

    }

    * {
        margin: 0px;
        padding: 0px;
        -webkit-box-sizing: border-box;
        -moz-box-sizing: border-box;
        box-sizing: border-box;
    }

    html {
        scroll-behavior: smooth;
    }

    body {
        font-family: "Work Sans", sans-serif;
        background-color: black;
    }


    .container {
        width: 600px;
        padding-left: 15px;
        padding-right: 15px;
        margin-left: auto;
        margin-right: auto;
        background: black;
    }

    .header .container {
        display: flex;
        justify-content: center;
        align-items: center;
        padding-top: 10px;
    }

    /* .logo:hover {
margin-top: 15px;
width: 22%;
} */

    /* Small */
    @media (min-width: 768px) {
        .container {
            width: 750px;
        }
    }

    /* Medium */
    @media (min-width: 992px) {
        .container {
            width: 970px;
        }
    }

    /* Large */
    @media (min-width: 1200px) {
        .container {
            width: 1170px;
        }
    }

    .landing-text {
        color: white;
        margin-top: 20px;
        font-weight: 800;

    }

    .fees {
        color: #b7b7b7;
        margin-top: 150px;
        font-weight: 400;
        margin-bottom: 50px;
    }


    .input-slot-number {

        font-weight: 300px;
        margin-bottom: 20px;
        width: 60px;
        border-radius: 5px;

    }

    .uppercase {
        text-transform: uppercase;
    }

    .btn {
        display: inline-block;
        background: transparent;
        color: inherit;
        font: inherit;
        border: 0;
        outline: 0;
        padding: 0;
        transition: all 200ms ease-in;
        cursor: pointer;
    }

    .btn--primary {
        background: #ff7b73;
        color: #fff;
        box-shadow: 0 0 10px 2px rgba(0, 0, 0, 0.1);
        border-radius: 2px;
        padding: 12px 36px;
    }

    .btn--primary:hover {
        background: #fa6a63;
    }

    .btn--primary:active {
        background: #ff7b73;
        box-shadow: inset 0 0 10px 2px rgba(0, 0, 0, 0.2);
    }

    .btn--inside {
        margin-left: -96px;
    }

    .form__field {
        width: 360px;
        background: #fff;
        color: black;
        font: inherit;
        box-shadow: 0 6px 10px 0 rgba(0, 0, 0, 0.1);
        border: 0;
        outline: 0;
        padding: 22px 18px;
    }
</style>
<script>
    function a() {
        var slot = document.getElementById("paySlotText").value;
        if (slot >= 1 && slot <= 6) {
        }
        console.log(slot)
        document.getElementById("inputContainer").style.display = "none";
        document.getElementById("thankMessage").style.display = "block";
        // var xhr = new XMLHttpRequest();
        // xhr.open("GET", "/" + "open", true);
        // xhr.send();

    }
</script>

</html>

)rawliteral";



const char* ssid = "Nora_EXT";
const char* password =  "KiKo201214*";
const char* input_parameter2 = "input_integer";
String input_message;
AsyncWebServer server1(80);
AsyncWebServer server2(81);

int slot1;
int slot2;
int slot3;
int slot4;
int slot5;
int slot6;
int busySlots;

void getSlotsReading() {
  slot1=0;
  slot2=0;
  slot3=1;
  slot4=1;
  slot5=0;
  slot6=0;

  busySlots=0;
}

AsyncEventSource events("/events");

unsigned long lastTime = 0;
unsigned long timerDelay = 10000;
 
//____________________transmitting data from mega to esp____________________

const int number_of_parking_slots =6;
int esp_out_slots[6]={23,22,1,3,21,19};
int mega_in_slots[6]={18,5,17,16,4,2};

int free_count =number_of_parking_slots;
int free_S[number_of_parking_slots] = {0};

void setup_transmitting_data(){
  for (int index=0;index<number_of_parking_slots;index++){
   pinMode(esp_out_slots[index],OUTPUT);    
   pinMode(mega_in_slots[index],INPUT);
   }  
}

void get_data_from_mega(){
  for(int i=0;i<number_of_parking_slots;i++){
    if(digitalRead(mega_in_slots[i])!=free_S[i] &&digitalRead(mega_in_slots[i])==HIGH ){
      free_S[i]=1;
      free_count--;
    }
  }
}
void send_data_to_mega(){
  for(int i=0; i<number_of_parking_slots ;i++){
    if(free_S[i])
    digitalWrite(esp_out_slots[i],HIGH);
    else
    digitalWrite(esp_out_slots[i],LOW);
  }
}

void main_logic()
{
  get_data_from_mega();
  send_data_to_mega();
  if(input_message != "" )
    {
       free_S [(input_message[0]-'0')-1]=0;  
       free_count++;  
    }
}
//__________________end section_______________
void setup(){
  setup_transmitting_data();
  Serial.begin(115200);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.println(WiFi.localIP());
 
  server1.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", index_html);
  });
 
  server2.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", customer_html);
  });

  events.onConnect([](AsyncEventSourceClient *client){
  if(client->lastId()){
    Serial.printf("Client reconnected! Last message ID that it got is: %u\n", client->lastId());
  }
    client->send("hello!", NULL, millis(), 10000);
  });


  server2.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String input_parameter;
    input_message = request->getParam(input_parameter2)->value();
    input_parameter = input_parameter2;
    Serial.println(input_message);
    request->send(200, "text/html", "HTTP GET request sent to your ESP on input field ("+ input_parameter + ") with value: " + input_message + "<br><a href=\"/\">Return to Home Page</a>");
  });
  server1.addHandler(&events);
  server1.begin();
  server2.begin();
}
 
void loop() {
  getSlotsReading();

  // Serial.printf("slot1: ", slot1);
  // Serial.printf("slot2: ", slot2);
  // Serial.printf("slot3: ", slot3);
  // Serial.printf("slot4: ", slot4);
  // Serial.printf("slot5: ", slot5);
  // Serial.printf("slot6: ", slot6);
  // Serial.printf("number of busy slots: ", busySlots);
  // Serial.println();
   main_logic();

/*
  events.send("test",NULL,millis());
  if(slot1==1) {
    events.send(String(1).c_str(),"empty",millis());
  }
  else {
    events.send(String(1).c_str(),"busy",millis());
  }

  if(slot2==1) {
    events.send(String(2).c_str(),"empty",millis());
  }
  else {
    events.send(String(2).c_str(),"busy",millis());
  }

  if(slot3==1) {
    events.send(String(3).c_str(),"empty",millis());
  }
  else {
    events.send(String(3).c_str(),"busy",millis());
  }
  if(slot4==1) {
    events.send(String(4).c_str(),"empty",millis());
  }
  else {
    events.send(String(4).c_str(),"busy",millis());
  }

  if(slot5==1) {
    events.send(String(5).c_str(),"empty",millis());
  }
  else {
    events.send(String(5).c_str(),"busy",millis());
  }

  if(slot6==1) {
    events.send(String(6).c_str(),"empty",millis());
  }
  else {
    events.send(String(6).c_str(),"busy",millis());
  }

  events.send(String(busySlots).c_str(),"totlabusy",millis());
*/
}
