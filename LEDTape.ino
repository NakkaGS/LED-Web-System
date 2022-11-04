//////////////////////////////////
//Library CrazyLED and ShowTeam///
//By Nakata///////////////////////
//////////////////////////////////

#define FASTLED_ESP8266_RAW_PIN_ORDER
#define FASTLED_ESP8266_NODEMCU_PIN_ORDER
#define FASTLED_ESP8266_D1_PIN_ORDER

#include <FastLED.h>

#define NUM_LEDS 12 //Amount of LEDS
#define NUM_COLORS 3 //Colors Numbers for Random Colors
#define DATA_PIN 2 //Digital PIN~
#define FADE_EFFECT 15 //Used into the for

//MENU OPTIONS
typedef enum {
    SHOWTEAM = 1,
    SHOWTEAM_RANDOM = 2,
    CRAZYLED_ALLRANDOM,
    CRAZYLED_EACHRANDOM,
    CRAZYLED_RANDOMLED,
    CRAZYLED_SHAZAMALL,
    CRAZYLED_SHAZAMEACH,
    FADE
} menu;

//TEAM STRUCT
typedef struct{
	int R_1; //RGB 1
	int G_1; //RGB 1
	int B_1; //RGB 1

	int R_2; //RGB 2
	int G_2; //RGB 2
	int B_2; //RGB 2

	int R_3; //RGB 3
	int G_3; //RGB 3
	int B_3; //RGB 3
}Teams;

////////////////////////////// TEAMS ///////////////////////////////
///////////////   RBG_1,       RGB_2,     RGB_3   //////////////////

Teams Galant = {0,200,255, 120,130,150, 200,50,0};
Teams Jackson = {200,0,200, 50,10,50, 0,0,255};

////////////////////////////////////////////////////////////////////
//ShowTeam(int Pos,Teams *T, CRGB *led)
//Pos - Position in the LEDS Array. Every for 4 LEDS. The last is off
//T - It is the name of the Team
//Led - Leds Array
//Descrition: It turns ON the light for the footbal helmet in the specific position

void ShowTeam(int Pos,Teams *T, CRGB *led){
	int init = Pos*4;
	 
	led[init-4]=CRGB(T->R_1,T->G_1,T->B_1);
	led[init-3]=CRGB(T->R_2,T->G_2,T->B_2);
	led[init-2]=CRGB(T->R_3,T->G_3,T->B_3);

	FastLED.show();
	//delay(200);
} 

////////////////////////////////////////////////////////////////////
//ShowTeamRandom(int Pos, CRGB *led)
//Pos - Position in the LEDS Array. Every for 4 LEDS. The last is off
//Led - Leds Array
//Descrition: It turns ON the light with random colors in the specific position

void ShowTeamRandom(int Pos, CRGB *led){
	int init = Pos*4;
 
	int k = random(200);
	Teams Random = {k,k-50,k-100 , k,k-50,k-100, k,k-50,k-100};

	led[init-4]=CRGB(Random.R_1, Random.G_1, Random.B_1);
	led[init-3]=CRGB(Random.R_2, Random.G_2, Random.B_2);
	led[init-2]=CRGB(Random.R_3,Random.G_3,Random.B_3);

	FastLED.show();
	delay(500);
} 
 
////////////////////////////////////////////////////////////////////
//CrazyLEDEachRandom(CRGB *led)
//led - Leds Array
//Descrition: Turn on each LED in the tape in order and with random color

void CrazyLEDAllRandom(CRGB *led){
    for (int i= 0; i<NUM_LEDS;i++){
      led[i]=CRGB(random(200),random(200)-50,random(200)-100);
    }
    FastLED.show();
    delay(250);
}

////////////////////////////////////////////////////////////////////
//CrazyLEDEachRandom(CRGB *led)
//led - Leds Array
//Descrition: Turn on each LED in the tape in order and with random color

void CrazyLEDEachRandom(CRGB *led){
    for (int i= 0; i<NUM_LEDS;i++){
      led[i]=CRGB(random(200),random(200)-50,random(200)-100);
      FastLED.show();
      delay(250);
    }
}

////////////////////////////////////////////////////////////////////
//CrazyLEDRandomLED(CRGB *led)
//led - Leds Array
//colors - corls Array
//Descrition: Turn on one random LED with random color

void CrazyLEDRandomLED(CRGB *led){
	int x = random(200);
	int y = random(200)-50;
	int z = random(200)-100;

	led[random(NUM_LEDS)]=CRGB(x,y,z);
	FastLED.show();
    delay(100);

	x = random(200);
	y = random(200);
	z = random(200);

	led[random(NUM_LEDS)]=CRGB(x,y,z);
	FastLED.show();
	delay(100);
}

////////////////////////////////////////////////////////////////////
//CrazyLED_ShazamAll(CRGB *led, CRGB *colors)
//led - Leds Array
//colors - corls Array
//Descrition: Turn on one random LED with the colors that are in the colors array

void CrazyLED_ShazamAll(CRGB *led, CRGB *colors){
  int j = random(NUM_COLORS);
  for (int i= 0; i<NUM_LEDS;i++){
    led[random(NUM_LEDS)] = colors[j];
    FastLED.show();
    delay(250);
  }
}

////////////////////////////////////////////////////////////////////
//CrazyLED_ShazamEach(CRGB *led, CRGB *colors)
//led - Leds Array
//colors - corls Array
//Descrition: Turn on all LEDS with the colors that are in the colors array

void CrazyLED_ShazamEach(CRGB *led, CRGB *colors){
  int j = random(NUM_COLORS);
  for (int i= 0; i<NUM_LEDS;i++){
    led[i] = colors[j];
  }
  FastLED.show();
  delay(500);
}

////////////////////////////////////////////////////////////////////
//CrazyLED_Fade(CRGB *led)
//led - Leds Array
//Descrition: Pre selected color with fade effect

void CrazyLED_Fade(CRGB *led){
  int R = 20; //Green
  int G = 255; //Red
  int B = 140; //Blue
  //RGB->GRB
    
	for (int j = 0; j<=FADE_EFFECT; j++){
		G = G-j;
    
		for (int i = 0; i<NUM_LEDS; i++){
		  led[i].setRGB( R, G, B);
      FastLED.show();
      delay(25);
    }
  }
  
  for (int j = 0; j<=FADE_EFFECT; j++){
    G = G+j;

    for (int i = 0; i<NUM_LEDS; i++){
      led[i].setRGB( R, G, B);
      FastLED.show();
      delay(25);
    }
  }
}
////////////////////////////////////////////////////////////////////
//ShowMenu()
//Descrition: Show menu with the functions options
void ShowMenu(){
  Serial.println("\n");
  Serial.println("Select Function");
  Serial.println("1 - ShowTeam");
  Serial.println("2 - ShowTeamRandom");
  Serial.println("3 - CrazyLEDAllRandom");
  Serial.println("4 - CrazyLEDEachRandom");
  Serial.println("5 - CrazyLEDRandomLED");
  Serial.println("6 - CrazyLED_ShazamAll");
  Serial.println("7 - CrazyLED_ShazamEach");
  Serial.println("8 - Fade");
  Serial.println("\n");
}


/////////////////////////   ARDUINO CODE    ////////////////////////
////////////////////////////////////////////////////////////////////


#ifdef ESP32
#include <WiFi.h>
#include <AsyncTCP.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#endif
#include <ESPAsyncWebServer.h>

#include "FS.h" //Library for ESP8266 Flash Memory (4MB)

// Replace with your network credentials
const char* ssid = "wifiname";
const char* password = "password";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

void notFound(AsyncWebServerRequest *request); // function prototypes for HTTP handlers


// Import required libraries
CRGB colors[NUM_COLORS]; //pre selected colors
CRGB leds[NUM_LEDS]; //vetor for each position from the Tape

String readString; //for serial

int choose; //for menu
menu options; //enum menu
int flag = 0; //for stop repeat

void setup() {

  Serial.begin(115200); //Open Serial connection

  // Initialize SPIFFS
  if(!SPIFFS.begin()){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());


  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", "text/html");
  });
  
  // Route to load style.css file
  server.on("/css/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/css/style.css", "text/css");
  });

  // Route to load mian.js file
  server.on("/js/main.js", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/js/main.js", "text/javascript");
  });
  
  // Route to set GPIO to HIGH
  server.on("/randomLED", HTTP_POST, [](AsyncWebServerRequest *request){
    Serial.println("Function");
    options = CRAZYLED_RANDOMLED;    
    request->send(SPIFFS, "/index.html", "text/html");
  });
  
  // Route to set GPIO to LOW
  server.on("/makeLove", HTTP_POST, [](AsyncWebServerRequest *request){
    Serial.println("Function");
    options = FADE; 
    request->send(SPIFFS, "/index.html", "text/html");
  });

  // Route to set GPIO to LOW
  server.on("/stormLED", HTTP_POST, [](AsyncWebServerRequest *request){
    Serial.println("Function");
    options = CRAZYLED_EACHRANDOM;    
    request->send(SPIFFS, "/index.html", "text/html");
  });
  
  server.onNotFound(notFound);        // When a client requests an unknown URI (i.e. something other than "/"), call function "handleNotFound"

  server.begin(); //Start the server

  Serial.println("Server listening");
  
  //ShowMenu(); //Optional: just to execute this program using the Console.
  
  delay(500);

  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);

  //PRE SELECTED COLORS
  /////////////////////////   G - R - B    ///////////////////////
  colors[NUM_COLORS-NUM_COLORS] = CRGB(20, 255, 147);   //DarkPink
  colors[NUM_COLORS-NUM_COLORS+1] = CRGB(69, 255 , 0);   //OrangeRed
  colors[NUM_COLORS-NUM_COLORS+2] = CRGB(20, 177, 255);  //BlueViolet

}

void loop() {

  
//	while (Serial.available()) {
//		delay(2);
//		char c = Serial.read();
//		readString += c;
//	}
  
  
//  if(choose > 8){
//    Serial.println("-------NO PROGRAM SELECTED-------");
//    readString="";
//    flag = 0;
//    ShowMenu();
//  }
  
//  choose = readString.toInt();

  switch(options){
    case SHOWTEAM:
      ShowTeam(1,&Jackson, leds);
      if(flag == 0){
        Serial.println("------ShowTeam-------");
        flag = 1;
      }
      break;

    case SHOWTEAM_RANDOM:
      ShowTeamRandom(1, leds);
      if(flag == 0){
        Serial.println("-------ShowTeamRandom------");
        flag = 1;
      }
      break;

    case CRAZYLED_ALLRANDOM:
      CrazyLEDAllRandom(leds);
      if(flag == 0){
        Serial.println("-------CrazyLEDAllRandom------");
        flag = 1;
      }
      break;

    case CRAZYLED_EACHRANDOM:
      CrazyLEDEachRandom(leds);
      if(flag == 0){
        Serial.println("-------CrazyLEDEachRandom------");
        flag = 1;
      }
      break;

    case CRAZYLED_RANDOMLED:
      CrazyLEDRandomLED(leds);
      if(flag == 0){
        Serial.println("-------CrazyLEDRandomLED------");
        flag = 1;
      }
      break;

    case CRAZYLED_SHAZAMALL:
      CrazyLED_ShazamAll(leds, colors);
      if(flag == 0){
        Serial.println("-------CrazyLED_ShazamAll------");
        flag = 1;
      }
      break;

    case CRAZYLED_SHAZAMEACH:
      CrazyLED_ShazamEach(leds, colors);
      if(flag == 0){
        Serial.println("-------CrazyLED_ShazamEach------");
        flag = 1;
      }
      break;

    case FADE:
      CrazyLED_Fade(leds);
      if(flag == 0){
        Serial.println("-------Fade------");
        flag = 1;
      }
      break;
      
    default:
      break;
  }
  
}

void notFound(AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
}
