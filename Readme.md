
#Practica 3A: Generación de una pagina web


##Codigo


```
#include <WiFi.h>
#include <WebServer.h>

// SSID & Password
const char* ssid = "MOVISTAR_A065";  // Enter your SSID here
const char* password = "A5H7v89Hl5";  //Enter your Password here

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
<h1>My Primera Pagina con ESP32 - Station Mode &#128522;</h1>\
</body>\
</html>";

// Handle root url (/)
void handle_root() {
 server.send(200, "text/html", HTML);
}
```

#Funcionamiento

Primeramente cargamos las dos librerias,  la primera `#include <WiFi.h&gt;` sirve para permitir que nuestra placa se conecte a internet, y la segunda librería `#include <WebServer.h&gt;` es para hacer un servidor web.

Despues de cargar las librerias , añadimos un char para poner el SSID de nuestro wifi y en el otro char la contraseña:


`const char* ssid = "MOVISTAR_A065";` 
`const char* password = "A5H7v89Hl5";`

En el void setup imprimimos por pantalla Try Connecting to:
MOVISTAR_A065, esto lo hacemos con este codigo:

`Serial.println("Try Connecting to ");`
`Serial.println(ssid);`

Una vez lo hayamos imprimido por pantalla, conectamos el modern wifi a la placa:

`WiFi.begin(ssid, password);`

Seguidamente comprobamos si el wifi esta conectado a la red wifi:

```
while (WiFi.status() != WL_CONNECTED) {
delay(1000);
Serial.print(".");
}
```

Con este bucle se consigue comprobar si esta conectado para poder imprimirlo por pantalla.

Ahora imprimimos por pantalla que el wifi esta correctamente conectado y tambien imprimimos la IP de nuestra placa.

```
Serial.println("");
Serial.println("WiFi connected successfully");
Serial.print("Got IP: ");
Serial.println(WiFi.localIP());
```
Despues utilizamos el void setup() donde empezaremos el servidor HTTP con:

```
server.begin();
Serial.println("HTTP server started");
delay(100);
```

En el loop llamamos la función `n handleClient()` para poder recibir las peticiones de los clientes y lanzar las funciones asociadas.

```
void loop() {
server.handleClient();
}
```

Antes de finalizar el programa, creamos un string de nombre HTML para poder mostrar el contenido en el servidor web:
```
String HTML = "<!DOCTYPE html&gt;\
<html&gt;\
<body&gt;\
<h1&gt;My Mi pagina con ESP32 - Station Mode &#128522;</h1&gt;\
body&gt;\
html&gt;";
```

Por ultimo, creamos la función `void handle_root()` que dentro de ella utilizaremos la función send que consta de 3 parametros: el primero es el código de respuesta (200, 301, 303, 404...), el segundo es el contenido HTTP (text/plain, text/html, text/json, image/png...) y el último es el contenido del cuerpo de la respuesta, que en
nuestro caso es el string HTML.

```
void handle_root() {
server.send(200, "text/html", HTML);
}
```
##Salida por el terminal

En la salida por el terminal no sale algo asi:

Try to connecting to
MOVISTAR_A065
.
WIFI connected succesfully
Got IP: 192.145.1.184
HTTP Server started

##Visualización de la conexión de mi pagina web con el navegador

![3](https://i.ibb.co/r6BCnm1/Visualizaci-n-Pagina-web.png)


#Segundo apartado


![1](https://i.ibb.co/6YNCJvf/Hoja-1-Rafa.jpg)
![2](https://i.ibb.co/TkzRDFk/Hoja-2-Rafa.jpg)


