#include <WiFi101.h>
// needs to be version 13.0

// TODO: Change these into constants
// server to connect to
IPAddress server(192, 168, 43, 168); //Server IP
IPAddress ip(192, 168, 1, 177); //PSat IP
//
//char ssid[] = "psatnetwork";
//char pass[] = "nopenope";
char ssid[] = "JonathanAP";
char pass[] = "nopenope";
int port = 1619;

int status = WL_IDLE_STATUS;
WiFiClient client;


int WiFi_setup() {
    Serial.begin(9600);
    Serial.println("WiFi starting up");

    // required for Adafruit Feather M0 Wifi board
    WiFi.setPins(8, 7, 4, 2);

    // is a wifi unit attached?
    Serial.println("Checking for wifi hardware...");
    if (WiFi.status() == WL_NO_SHIELD) {
      Serial.println("- none found, quitting...");
      return -1;
    }
    Serial.println("- found");
    
    // attempt to connect to WiFi twork:
    Serial.print("Attempting to connect to: \"");
    Serial.print(ssid);
    Serial.println("\"");
    // WiFi.config(ip);
    status = WiFi.begin(ssid, pass);
    delay(2000);                     // wait 2 sec for connection

    // Wait for connection completion
    while(status == WL_IDLE_STATUS){
        status = WiFi.status();
        delay(2000);
    }
   

   if(status == WL_CONNECT_FAILED){
      Serial.println("Initial WiFi Connection Failed");
      return 0; // Indicating semi-fail state
   } else if (status == WL_CONNECTED){
      Serial.println("WiFi Connected");
      return 1;
   }

   if (status == WL_DISCONNECTED){
    Serial.println("no");
   }
   Serial.println("something I just want to know if this line is running");
    return 1;
}
    
int checkconnection_() {
  status = WiFi.status();
  if (status == WL_CONNECTED) { // connected
    Serial.println("Connected to wifi");
    return 1;
  } else if (status == WL_IDLE_STATUS) {
    Serial.print("Still Attempting Connection");
    return 0; // Connecting
  } else if (status == WL_DISCONNECTED || status == WL_CONNECTION_LOST){
    Serial.println("Wifi Disconnected");
    attempt_wifi_connection();
    return -1;
  } else if(status == WL_CONNECT_FAILED) {
    Serial.println("Wifi Connection Failed");
    attempt_wifi_connection();
    return -2;
  }
}

void attempt_wifi_connection(){
  Serial.print("Attempting to connect to: \"");
  Serial.print(ssid);
  Serial.println("\"");
  status = WiFi.begin(ssid, pass);
}

int checkserver_() {
  if (status != WL_CONNECTED){
    return -1;
  }
  if (client.connected()) { // connected
    Serial.println("Connected To client");
    return 1;
  } else {
    client.stop();
    Serial.println("Not connected to client");        
    return client.connect(server, port);
  }
}

int transmit_(String data) {
  if (checkconnection_() == 1 && checkserver_() == 1) {
    client.print(data);
    client.stop();
    return 1;
  }
  return -1;
}

int endtransmission_() {
  // disconnect when done
  Serial.println("Disconnecting from server...");
  client.stop();
  Serial.println("- bye!");
  return 1;
}

void setup(){
  WiFi_setup();
  // attempt_wifi_connection();
}

void loop() {
  // put your main code here, to run repeatedly:
  checkconnection_();
  checkserver_();
  transmit_("Testing 123");

  delay(1000);

  

}
