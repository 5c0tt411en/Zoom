#define pin 13

void setup() {
    Serial.begin(9600);
    pinMode(pin, OUTPUT);//relay
}

void loop() {
    byte incomingByte;
    incomingByte = Serial.read ();
    Serial.print("incoming byte is: ");
    Serial.println(incomingByte, DEC);
    switch (incomingByte) {
        case 1  :   digitalWrite(pin, HIGH);
                    break;
        case 2  :   digitalWrite(pin, LOW);
                    break;
        default :   
                    break;
    }
}
