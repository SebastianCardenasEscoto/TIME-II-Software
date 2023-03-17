char current_packet[200];
char current_status = '@';
//int current_temps[5];
//int sensor_port[5] = {15, 16, 17, 18, 19};
//TO DO: Wait until any writing is done to prevent bufferoverflow

void setup() {
  Serial.begin(115200);
  pinMode(13, OUTPUT);
}

void loop() {
  if (Serial.available()) {
    get_valid_packet();
    if (is_valid_packet()) {
      get_status();
      if (current_packet[0] == 'C') {
        digitalWrite(13, HIGH);
      }
    }
  }
}


void get_valid_packet() {
  Serial.readStringUntil('\0').toCharArray(current_packet, 200);
}

bool is_valid_packet() {
  bool is_not_empty = (strlen(current_packet) > 0);
  bool has_valid_first = ('@' <= current_packet[0] && current_packet[0] <= 'J');
  return (is_not_empty && has_valid_first);
}

void get_status() {
  current_status = current_packet[0];
}
