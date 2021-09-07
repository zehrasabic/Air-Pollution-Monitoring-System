#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <ThingSpeak.h>
#include <ESP8266WebServer.h>
String kljuc = "KU91TFRQI2C26LXF"; 

const char* imemreze = "AndroidAP8D7A";
const char* sifra = "aldina123"; //šifra mreže
const char* server = "api.thingspeak.com";

unsigned long channel=823295; 
char* kljuczacitanje="SSHE97ZCWTPEA8YV";  

float a=2.25E-02;
float b=2.25E-02;
float c=2.25E-02;
float d=2.25E-02;
float e=2.25E-02;
unsigned int Field1=1; 
unsigned int Field2=3;
unsigned int Field3=4; 
unsigned int Field4=5; 
unsigned int Field5=6; 
WiFiClient client; 
ESP8266WebServer server1(80); 
void setup()
{
Serial.begin(115200);
delay(10);
WiFi.begin(imemreze, sifra); 
Serial.println();
Serial.println();
Serial.print("Konektovanje na mrezu: "); 
Serial.println(imemreze);
WiFi.begin(imemreze, sifra);
while (WiFi.status() != WL_CONNECTED)
{
delay(500);
Serial.print(".");
}
Serial.println("");
Serial.println("Konekcija uspjesna!!!");
Serial.print("IP adresa: ");
Serial.println(WiFi.localIP()); 
Serial.println("");
ThingSpeak.begin(client);

a=readData(channel,Field1);
b=readData(channel,Field2);
c=readData(channel,Field3);
d=readData(channel,Field4);
e=readData(channel,Field5);

server1.on("/",handle_OnConnect);
server1.onNotFound(handle_NotFound);
server1.begin();Serial.println("HTTP server pokrenut!!!");
Serial.println("");
delay(1000);
}

void handle_OnConnect(){
a=readData(channel,Field1);
b=readData(channel,Field2);
c=readData(channel,Field3);
d=readData(channel,Field4);
e=readData(channel,Field5);
server1.send(200,"text/html",SendHTML(a,b,c,d,e));
}

void handle_NotFound() {
server1.send(404,"text/plain","Not found");
}

float readData(long TSChannel, unsigned int TSField) {
float podaci=ThingSpeak.readFloatField(TSChannel, TSField, kljuczacitanje);
Serial.println("Podaci procitani sa ThingSpeak: "+String(podaci,2));
return podaci;
}

String SendHTML(int temperatura,int vlaznost,float co,float co2,float nh4){
String s = "<!DOCTYPE html> <html>\n";
s+="<html>";
s+="<meta charset=\"utf-8\">";
s+="<meta http-equiv=\"refresh\" content=\"3\">";
s+="<meta name=\"viewport\" content=\"width=device-width,initial-scale=1.0\">";
s+="<meta http-equiv=\"X-UA-Compatible\" content=\"ie=edge\">";s+="<link rel=\"stylesheet\" href=\"https://use.fontawesome.com/releases/v5.7.2/css/all.css\" integrity=\"sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr\" crossorigin=\"anonymous\">";
s+="<title>ANALIZA ZRAKA</title>";
s+="<style>";
s+="* {";
s+="margin:0;";
s+="padding:0;";
s+="}";
s+="body {";
s+="background:url(\"http://www.galaxyjeevandhara.com/extra-images/banner-1.jpg\") no-repeat center center fixed;";
s+="-webkit-background-size:cover;";
s+="}";
s+="#header {";
s+="width:100%;";
s+="height:80px;";
s+="background-color:#0009;";
s+="line-height:80px;";
s+="opacity:0.5;";
s+="}";
s+=".temp {";
s+="display: flex;";
s+="justify-content: space-beteen;";
s+="}";
s+="footer {";
s+="text-align:center;";
s+="background-color:#0009;";
s+="padding:15px;";
s+="position:absolute;";s+="width:100%;";
s+="bottom:0;";
s+="position:fixed;";
s+="color:#fff;";
s+="text-shadow:2px 2px 4px #000000;";
s+="}";
s+="</style>";
s+="<script type=\"text/javascript\" src=\"https://www.gstatic.com/charts/loader.js\"></script>";
s+="<script type=\"text/javascript\">";
s+="google.charts.load('current', {'packages':['gauge']});";
s+="google.charts.setOnLoadCallback(drawChart);";
s+="function drawChart() {";
s+=" var data = google.visualization.arrayToDataTable([";
s+="['Label', 'Value'],";
s+="['°C', ";
s+=temperatura;
s+=" ], ";
s+="]);";
s+="var options = {";
s+="min:0,";
s+="max:50,";
s+=" width: 450, height: 180,";
s+="greenFrom: 0, greenTo: 50,";
s+="};";
s+="var chart = new google.visualization.Gauge(document.getElementById('chart_div1'));";
s+="chart.draw(data, options);";
s+="setInterval(function() {";
s+=" data.setValue(0, 0, 40 + Math.round(60 * Math.random()));";
s+="chart.draw(data, options);";
s+="}, 13000);";s+="}";
s+="</script>";
s+="<script type=\"text/javascript\" src=\"https://www.gstatic.com/charts/loader.js\"></script>";
s+="<script type=\"text/javascript\">";
s+="google.charts.load('current', {'packages':['gauge']});";
s+="google.charts.setOnLoadCallback(drawChart);";
s+="function drawChart() {";
s+=" var data = google.visualization.arrayToDataTable([";
s+="['Label', 'Value'],";
s+="['%', ";
s+=vlaznost;
s+=" ], ";
s+="]);";
s+="var options = {";
s+="min:0,";
s+="max:100,";
s+=" width: 450, height: 180,";
s+="greenFrom: 0, greenTo: 100,";
s+="};";
s+="var chart = new google.visualization.Gauge(document.getElementById('chart_div2'));";
s+="chart.draw(data, options);";
s+="setInterval(function() {";
s+=" data.setValue(0, 0, 40 + Math.round(60 * Math.random()));";
s+="chart.draw(data, options);";
s+="}, 13000);";
s+="}";
s+="</script>";
s+="<script type=\"text/javascript\" src=\"https://www.gstatic.com/charts/loader.js\"></script>";
s+="<script type=\"text/javascript\">";s+="google.charts.load('current', {'packages':['gauge']});";
s+="google.charts.setOnLoadCallback(drawChart);";
s+="function drawChart() {";
s+=" var data = google.visualization.arrayToDataTable([";
s+="['Label', 'Value'],";
s+="['ppm', ";
s+=co;
s+=" ], ";
s+="]);";
s+="var options = {";
s+="min:0,";
s+="max:1000,";
s+=" width: 450, height: 180,";
s+="greenFrom: 0, greenTo: 1000,";
s+="};";
s+="var chart = new google.visualization.Gauge(document.getElementById('chart_div3'));";
s+="chart.draw(data, options);";
s+="setInterval(function() {";
s+=" data.setValue(0, 0, 40 + Math.round(60 * Math.random()));";
s+="chart.draw(data, options);";
s+="}, 13000);";
s+="}";
s+="</script>";
s+="<script type=\"text/javascript\" src=\"https://www.gstatic.com/charts/loader.js\"></script>";
s+="<script type=\"text/javascript\">";
s+="google.charts.load('current', {'packages':['gauge']});";
s+="google.charts.setOnLoadCallback(drawChart);";
s+="function drawChart() {";
s+=" var data = google.visualization.arrayToDataTable([";
s+="['Label', 'Value'],";s+="['ppm', ";
s+=co2;
s+=" ], ";
s+="]);";
s+="var options = {";
s+="min:0,";
s+="max:20000,";
s+=" width: 450, height: 180,";
s+="greenFrom: 0, greenTo: 20000,";
s+="};";
s+="var chart = new google.visualization.Gauge(document.getElementById('chart_div4'));";
s+="chart.draw(data, options);";
s+="setInterval(function() {";
s+=" data.setValue(0, 0, 40 + Math.round(60 * Math.random()));";
s+="chart.draw(data, options);";
s+="}, 13000);";
s+="}";
s+="</script>";
s+="<script type=\"text/javascript\" src=\"https://www.gstatic.com/charts/loader.js\"></script>";
s+="<script type=\"text/javascript\">";
s+="google.charts.load('current', {'packages':['gauge']});";
s+="google.charts.setOnLoadCallback(drawChart);";
s+="function drawChart() {";
s+=" var data = google.visualization.arrayToDataTable([";
s+="['Label', 'Value'],";
s+="['ppm', ";
s+=nh4;
s+=" ], ";
s+="]);";
s+="var options = {";s+="min:0,";
s+="max:1000,";
s+=" width: 450, height: 180,";
s+="greenFrom: 0, greenTo: 1000,";
s+="};";
s+="var chart = new google.visualization.Gauge(document.getElementById('chart_div5'));";
s+="chart.draw(data, options);";
s+="setInterval(function() {";
s+=" data.setValue(0, 0, 40 + Math.round(60 * Math.random()));";
s+="chart.draw(data, options);";
s+="}, 13000);";
s+="}";
s+="</script>";
s+="</script>";
s+="</head>";
s+="<body>";
s+="<div id=\"main\">";
s+="<div id=\"header\">";
s+="<h1 style=\"text-shadow:2px 2px 4px #000000;color:#fff;text-align:center\">ANALIZA ZAGAĐENOSTI ZRAKA</h1>";
s+="</div>";
s+="<table cellspacing=\"120\">";
s+="<tr>";
s+="<td>";
s+="<div class=\"temp\">";
s+="<i class=\"fas fa-thermometer-three-quarters\" style=\"text-shadow: 2px 2px 4px #000000;color:#4EB475;font-size:50px;\"></i>";
s+="<h2 style=\"text-shadow:2px 2px 4px #000000;margin top:10%;color:white;opacity:0.7\">Temperatura</h2>";
s+="</div>";
s+="<h2 style=\"text-shadow:2px 2px 4px #000000;margintop:10%;color:white;opacity:0.7;text-align:center\">";
s+=int(temperatura);
s+=" &#8451</h2>";
s+="</td>";
s+="<td>";
s+="<div class=\"temp\">";
s+="<i class=\"fas fa-tint\" style=\"text-shadow: 2px 2px 4px #000000;color:#4EB475;font size:50px;\"></i>";
s+="<h2 style=\"text-shadow:2px 2px 4px #000000;margin top:10%;color:white;opacity:0.7\">Vla&#382nost</h2>";
s+="</div>";
s+="<h2 style=\"text-shadow:2px 2px 4px #000000;margin top:10%;color:white;opacity:0.7;text-align:center\">";
s+=int(vlaznost);
s+=" %</h2>";
s+="</td>";
s+="<td>";
s+="<div class=\"temp\">";
s+="<i class=\"fas fa-cloud\" style=\"text-shadow: 2px 2px 4px #000000;color:#4EB475;font size:50px;\"></i>";
s+="<h2 style=\"text-shadow:2px 2px 4px #000000;margin top:10%;color:white;opacity:0.7\">CO level</h2>";
s+="</div>";
s+="<h2 style=\"text-shadow:2px 2px 4px #000000;margin top:10%;color:white;opacity:0.7;text-align:center\">";
s+=float(co);
s+=" ppm</h2>";
s+="</td>";
s+="<td>";
s+="<div class=\"temp\">";
s+="<i class=\"fas fa-cloud\" style=\"text-shadow: 2px 2px 4px #000000;color:#4EB475;fontsize:50px;\"></i>";
s+="<h2 style=\"text-shadow:2px 2px 4px #000000;margin top:10%;color:white;opacity:0.7\">CO2 level</h2>";
s+="</div>";
s+="<h2 style=\"text-shadow:2px 2px 4px #000000;margin top:10%;color:white;opacity:0.7;text-align:center\">";
s+=float(co2);
s+=" ppm</h2>";
s+="</td>";
s+="<td>";
s+="<div class=\"temp\">";
s+="<i class=\"fas fa-cloud\" style=\"text-shadow: 2px 2px 4px #000000;color:#4EB475;font size:50px;\"></i>";
s+="<h2 style=\"text-shadow:2px 2px 4px #000000;margin top:10%;color:white;opacity:0.7\">NH4 level</h2>";
s+="</div>";
s+="<h2 style=\"text-shadow:2px 2px 4px #000000;margin top:10%;color:white;opacity:0.7;text-align:center\">";
s+=float(nh4);
s+=" ppm</h2>";
s+="</td>";
s+="</tr>";
s+="<tr>";
s+="<td>";
s+="<div id=\"chart_div1\" style=\"text-shadow:2px 2px 4px #000000;margin-top:0;width: 120px; height: 120px;opacity:0.5;\"></div>";
s+="</td>";
s+="<td>";
s+="<div id=\"chart_div2\" style=\"text-shadow:2px 2px 4px #000000;margin-top:0;width: 120px; height: 120px;opacity:0.5;\"></div>";
s+="</td>";s+="<td>";
s+="<div id=\"chart_div3\" style=\"text-shadow:2px 2px 4px #000000;margin-top:0;width: 120px; height: 120px;opacity:0.5;\"></div>";
s+="</td>";
s+="<td>";
s+="<div id=\"chart_div4\" style=\"text-shadow:2px 2px 4px #000000;margin-top:0;width: 120px; height: 120px;opacity:0.5;\"></div>";
s+="</td>";
s+="<td>";
s+="<div id=\"chart_div5\" style=\"text-shadow:2px 2px 4px #000000;margin-top:0;width: 120px; height: 120px;opacity:0.5;\"></div>";
s+="</td>";
s+="</tr>";
s+="</table>";
s+="</div>";
s+="</main>";
s+="<footer>";
s+="<p style=\"opacity:0.5;\">Copyright &copy; 2019, Sistemi u realnom vremenu</p>";
s+="</footer>";
s+="</body>";
s+="</html>";
return s;
}
int data1; 
int data2; 
int data3; 
float data4;
float data5; 
float data6; 
void loop()
{

if (Serial.available() > 0)
{
delay(100);
while (Serial.available() > 0)
{

StaticJsonBuffer<1000> jsonBuffer;
JsonObject& root = jsonBuffer.parseObject(Serial);
if (root == JsonObject::invalid()) {
return;
}

Serial.println("************PODACI************");
root.prettyPrintTo(Serial);
Serial.print("Temperatura (°C): ");
data1 = root["temp"];
Serial.print(data1);
Serial.println(" °C");
Serial.print("Temperatura (F): ");
data2 = root["tempf"];
Serial.print(data2);
Serial.println(" F");
Serial.print("Vlaznost (%): ");
data3 = root["vlaz"];
Serial.print(data3);
Serial.println(" %");
Serial.print("CO level (ppm): ");data4 = root["co"];
Serial.print(data4);
Serial.println(" ppm");
Serial.print("CO2 level (ppm): ");
data5 = root["co2"];
Serial.print(data5);
Serial.println(" ppm");
Serial.print("NH4 level (ppm): ");
data6 = root["nh4"];
Serial.print(data6);
Serial.println(" ppm");
Serial.println("******************************");
}
}

if (client.connect(server, 80))
{
String postaviString = kljuc;
postaviString += "&field1="; 
postaviString += int(data1);
postaviString += "&field2="; 
postaviString += int(data2);
postaviString += "&field3="; 
postaviString += int(data3);
postaviString += "&field4="; 
postaviString += float(data4);
postaviString += "&field5="; 
postaviString += float(data5);
postaviString += "&field6="; 
postaviString += float(data6);
postaviString += "\r\n\r\n";
client.print("POST /update HTTP/1.1\n");
client.print("Host: api.thingspeak.com\n");
client.print("Connection: close\n");
client.print("X-THINGSPEAKAPIKEY: " + kljuc + "\n");
client.print("Content-Type: application/x-www-form-urlencoded\n");
client.print("Content-Length: ");
client.print(postaviString.length());
client.print("\n\n");
client.print(postaviString);
Serial.println(postaviString);
}
client.stop();
Serial.println("Cekanje...");
server1.handleClient();
delay(6000);
}
