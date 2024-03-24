#include <MKRNB.h>
#include <ArduinoMqttClient.h>

const char PINNUMBER[] = "";

//MQTT configurations
const char broker[] = "test.mosquitto.org";
int port = 1883;
const char topic[] = "nbiot_test";
const char idListTopic[] = "nbiot_test_ids";
const char reception_delay[] = "nbiot_delay";

NBClient client;
GPRS gprs;
NB nbAccess;

MqttClient mqttClient(client);


int maxIds;             // Maximum number of IDs to store

char *messageIds; // Single string for message IDs
int numMessagesSent = 0;

unsigned long startTime = 0;
unsigned long sendTime = 0;
unsigned long receptionDelay = 0;

// Mission parameters
const int idLength = 6; // Adjust the length as needed
unsigned long messageInterval = 1000; // Interval between messages in milliseconds
unsigned long duration = 60000;       // Duration in milliseconds


void setup() {
  Serial.begin(9600);
  while (!Serial);

  boolean connected = false;
  while (!connected) {
    Serial.println("Connecting to NbIOT Network ... ");
    if ((nbAccess.begin(PINNUMBER) == NB_READY) &&
        (gprs.attachGPRS() == GPRS_READY)) {
      connected = true;
      Serial.println("Connected to NbIOT and GPRS network...");
    } else {
      Serial.println("Not connected");
      delay(1000);
    }
  }

  if (!mqttClient.connect(broker, port)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());
    while (1);
  }

  Serial.println("You're connected to the MQTT broker!");

  mqttClient.onMessage(onMqttMessage);

  // Subscribe to the topic for receiving ACKs or other messages related to the ID list
  //mqttClient.subscribe(idListTopic);
  mqttClient.subscribe(topic);

  startTime = millis(); // Record the start time

  // Calculate maxIds based on duration and messageInterval
  maxIds = duration / messageInterval;

  // Allocate memory for messageIds
  messageIds = (char *)malloc((idLength + 1) * maxIds * sizeof(char));
  messageIds[0] = '\0'; // Initialize the string
}

void loop() {
  mqttClient.poll();
  unsigned long currentTime = millis();
  unsigned long elapsedTime = currentTime - startTime;

  if (elapsedTime >= duration) {
    if (numMessagesSent > 0) {
      Serial.println("Duration elapsed, sending the list of IDs.");
      sendIdList();
    }
    return;
  }

  if (currentTime - sendTime >= messageInterval) {
    sendTime = currentTime;

    // Generate unique ID for this message
    char messageId[idLength + 1];
    generateUniqueId(messageId, idLength);

    // Append the ID to the messageIds string
    if (numMessagesSent > 0) {
      strcat(messageIds, " ");
    }
    strcat(messageIds, messageId);

    // Send the message with the ID as payload
    mqttClient.beginMessage(topic);
    mqttClient.print(messageId);
    mqttClient.endMessage();

    numMessagesSent++;

    // Calculate reception delay
    receptionDelay = millis() - sendTime;
    Serial.print("Reception Delay: ");
    Serial.print(receptionDelay);
    Serial.println(" milliseconds");
  }
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

  mqttClient.poll();
  delay(2000);
  mqttClient.beginMessage(reception_delay);
  mqttClient.print(receptionDelay);
  mqttClient.endMessage();

  Serial.println();
}

void generateUniqueId(char *buffer, int length) {
  const char charset[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
  for (int i = 0; i < length; i++) {
    buffer[i] = charset[random(sizeof(charset) - 1)];
  }
  buffer[length] = '\0';
}

void sendIdList() {
  // Send the list of IDs to a separate topic
  mqttClient.beginMessage(idListTopic);
  mqttClient.print(messageIds);
  mqttClient.endMessage();

  // Clear the messageIds string
  messageIds[0] = '\0';

  numMessagesSent = 0;
}
