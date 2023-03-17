// Flight status
#define PRELAUNCH 0
#define LIFTOFF 1
#define MGRAV_BEGIN 2
#define MGRAV_END 3
#define LANDING 4
#define FINISHED 5

#define END_CHAR ']'

int currentStatus = PRELAUNCH;
double flightTime = 0;
char statuschar = "@";

bool is_input() {
  return (Serial.available());
}

bool is_ended(char end_char){
  return (end_char == ']');
}

void wait_until_char(char begin_char) {
  while (Serial.read() != begin_char); // wait until begin_char
}



char get_packet(int pos_input) {
  char contents[100];
  //wait until beginning char
  wait_until_char('[');
  for(int i = 0; i < 99; i++){
    contents[i] = char(Serial.read());
    if(is_ended(contents[i])){
      contents[i] = '\0';
      break;
    }
  }
  Serial.println("GOT HERE");
  //check until past comma tracker and get until next comma flag
  int status_index = 0;
  char contents_buffer[100];
  char statusChar[1];
  char timeChar[10];
  while (contents[index] != ',') {
    while (contents[index] != ',') {
      statusChar[index] = contents[index];
      index += 1;
    }
    timeChar[index] = contents[index];
    index += 1;
  }
  //current contents_buffer contains char for currentStatus
  
  
  for(comma_tracker = 0; comma_tracker <= pos_input; )
}

int pollStatus() {
  
}

double experimentTime() {
  
}

void setup() {
  Serial.begin(115200);
}
 
void loop() {
  if (! is_input()){
    return;
  }
  Serial.println(get_packet());
  //Serial.println("YOLO"); // printed yolo without input, perhaps because of Serial.begin???
}
