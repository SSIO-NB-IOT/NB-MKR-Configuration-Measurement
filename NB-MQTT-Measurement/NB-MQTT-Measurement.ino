// libraries
#include <MKRNB.h>
#include <ArduinoMqttClient.h>

// The MKRNB lib needs this even if it's blank
const char PINNUMBER[] = "";

// Broker details
const char broker[] = "test.mosquitto.org";
int port = 1883;
const char topic[] = "nbiot_test";

// Initialize the library instances
NBClient client;
GPRS gprs;
NB nbAccess;

MqttClient mqttClient(client);

// Timestamp variables
unsigned long sendTime = 0;
unsigned long receptionDelay = 0;

void setup() {
  // initialize serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.println("Warming up....");

  // connection state
  boolean connected = false;

  Serial.println("Connecting to NbIOT and GPRS network...");

  while (!connected) {
    if ((nbAccess.begin(PINNUMBER) == NB_READY) &&
        (gprs.attachGPRS() == GPRS_READY)) {
      connected = true;
      Serial.println("Connected to NbIOT and GPRS network...");
    } else {
      Serial.println("Not connected");
      delay(1000);
    }
  }

  Serial.println("Connecting to the MQTT broker...");

  Serial.println(broker);

  if (!mqttClient.connect(broker, port)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());

    while (1);
  }

  Serial.println("You're connected to the MQTT broker!");
  Serial.println();

  mqttClient.onMessage(onMqttMessage);

  Serial.print("Subscribing to topic: ");
  Serial.println(topic);
  Serial.println();

  // subscribe to a topic
  mqttClient.subscribe(topic);
}

void loop() {
  mqttClient.poll();
  delay(2000);

  // Record the time just before sending the message
  sendTime = millis();

  mqttClient.beginMessage(topic);
  mqttClient.print("NB IOT Example");
  mqttClient.endMessage();
}

void onMqttMessage(int messageSize) {
  // We received a message, print out the topic and contents
  Serial.println("Received a message with topic '");
  Serial.print(mqttClient.messageTopic());
  Serial.print("', length ");
  Serial.print(messageSize);
  Serial.println(" bytes:");

  // Use the Stream interface to print the contents
  while (mqttClient.available()) {
    Serial.print((char)mqttClient.read());
  }
  Serial.println();

  // Calculate reception delay
  receptionDelay = millis() - sendTime;
  Serial.print("Reception Delay: ");
  Serial.print(receptionDelay);
  Serial.println(" milliseconds");

  Serial.println();
}
