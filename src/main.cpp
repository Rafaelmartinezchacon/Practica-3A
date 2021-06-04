#include <WiFi.h>
#include <WebServer.h>

// SSID & Password
const char* ssid = "MOVISTAR_A065";  // Enter your SSID here
const char* password = "CLkJSAEU2fRwQxYrBh5A";  //Enter your Password here

WebServer server(80);  // Object of WebServer(HTTP port, 80 is defult)

void setup() {
 Serial.begin(115200);
 Serial.println("Try Connecting to ");
 Serial.println(ssid);

 // Connect to your wi-fi modem
 WiFi.begin(ssid, password);

 // Check wi-fi is connected to wi-fi network
 while (WiFi.status() != WL_CONNECTED) {
 delay(1000);
 Serial.print(".");
 }
 Serial.println("");
 Serial.println("WiFi connected successfully");
 Serial.print("Got IP: ");
 Serial.println(WiFi.localIP());  //Show ESP32 IP on serial

 server.on("/", handle_root);

 server.begin();
 Serial.println("HTTP server started");
 delay(100); 
}

void loop() {
 server.handleClient();
}

// HTML & CSS contents which display on web server
String HTML = "<!DOCTYPE html>\
<html>\
<body>\
<h1>My Practica A: Interupcion por GPIO</h1>\
<p>#include <Arduino.h></p>\
<p>struct Button {</p>\
<p>const uint8_t PIN;</p>\
<p>uint32_t numberKeyPresses;</p>\
<p>bool pressed;};</p>\
<p>Button button1 = {0, 0, false};</p>\
<p>void IRAM_ATTR isr() {</p>\
<p>button1.numberKeyPresses += 1;</p>\
<p>button1.pressed = true;}</p>\
<p>void setup() {</p>\
<p>Serial.begin(9600);</p>\
<p>pinMode(button1.PIN, INPUT_PULLUP);</p>\
<p>attachInterrupt(button1.PIN, isr, FALLING);}</p>\
<p>void loop() {</p>\
<p>if (button1.pressed) {</p>\
<p>Serial.printf(Button 1 has been pressed %u times\n, button1.numberKeyPresses);</p>\
<p>button1.pressed = false;}</p>\
<p>//Detach Interrupt after 1 Minute</p>\
<p>static uint32_t lastMillis = 0;</p>\
<p>if (millis() - lastMillis > 60000) {</p>\
<p>lastMillis = millis();</p>\
<p>detachInterrupt(button1.PIN);</p>\
<p>Serial.println(Interrupt Detached!);}}
</p>\


<h2>Funcionaminento de esta practica</h2>\

<p>Para hacer esta parte de la practica necesitamos utilizar la funcion attachInterrupt(GPIOPin, isr, Mode) .Con esta funcion lo que conseguiremos es una interrupcion en base a un pin por pin.</p>\
<p>
void setup() {</p>\
<p>Serial.begin(9600);</p>\
<p>pinMode(button1.PIN, input_pullup);</p>\
<p>attachInterrupt(button1.PIN, isr, falling);}
</p>\

<p>
En el apartado de button.pin establecemos la clavija GPIO que usaremos para su interrupcion. En Falling señalamos que los disparadores interrumpen cuando el pin va de High a Low. En isr llamos a la rutina de interrupcion con el siguiente codigo:
</p>\

<p>
void tram_attr isr() {
</p>\
<p>    
button1.numberKeyPresses += 1;
</p>\
<p>
button1.pressed = true;}
</p>\

<p>
Una vez llamada el isr, en este caso hacemos un loop donde cada vez que se pulse el button1, el monitos nos mostrara por pantalla Button 1 has been pressed %u times\n. En la parte que pone %u, pondremos las veces que se pulsado el boton. Seguidamente del loop tenemos el siguiente codigo:
</p>\

<p>
static uint32_t lastMillis = 0;</p>\
<p>if (millis() - lastMillis > 60000) {</p>\
<p>lastMillis = millis();</p>\
<p>detachInterrupt(button1.PIN);</p>\
<p>Serial.println(Interrupt Detached!);}
</p>\

<p>El funcionamiento de este ultimo codigo trata sobre que una vez llegue a pasar 1 minuto, de forma automatica desconectara la interrupción GPIO que tenemos asignada.</p>\
</body>\
</html>";

// Handle root url (/)
void handle_root() {
 server.send(200, "text/html", HTML);
}