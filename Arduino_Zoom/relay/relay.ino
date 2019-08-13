#define pin 12
#define pinLight 8

void setup() {
    Serial.begin(9600);
    pinMode(pin, OUTPUT);//relay
    pinMode(pinLight, OUTPUT);//light
}

void loop() {
    byte incomingByte;
    incomingByte = Serial.read();
//    Serial.print("incoming byte is: ");
//    Serial.println(incomingByte, DEC);
    switch (incomingByte) {
        case 3  :  digitalWrite(pinLight, HIGH); 
        case 1  :   digitalWrite(pin, HIGH);
                    break;
        case 4  :  digitalWrite(pinLight, LOW); 
        case 2  :   digitalWrite(pin, LOW);
                    break;
        default :   
                    break;
    }
}
