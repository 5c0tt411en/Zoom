int pin1 = 10, pin2 = 11, pin3 = 12, pin4 = 13, count = 0;
float onT[4] = {0, 0, 0, 0}, offT[4] = {0, 0, 0, 0}, tRandom[4] = {0, 0, 0, 0}, tRandomStamp[4] = {0, 0, 0, 0};
float t = 0, tStamp = 0, tThreToSeq = 125.0, tSeq = 0, tStampSeq = 0, from = 0, to = 0;
float onP = 0.06, offP = 3.94, offP2 = 1.94;

enum State {
  SLOW_STEP,
  FAST_STEP,
  RANDOM
};

State st = SLOW_STEP;

void setup() {
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  pinMode(pin4, OUTPUT);
  onT[0] = onP;
  offT[0] = offP + onT[0];
  onT[1] = onP + offT[0];
  offT[1] = offP + onT[1];
  onT[2] = onP + offT[1];
  offT[2] = offP + onT[2];
  onT[3] = onP + offT[2];
  offT[3] = offP + onT[3];
}

void loop() {
  float elapsedTimef = float(millis()) / 1000.0;
  t = elapsedTimef - tStamp;
  tSeq = elapsedTimef - tStampSeq;

  switch (st) {
    case SLOW_STEP:
      if (t < onT[0]) {
        digitalWrite(pin1, HIGH);
        digitalWrite(pin2, LOW);
        digitalWrite(pin3, LOW);
        digitalWrite(pin4, LOW);
      }
      if (t >= onT[0] && t < offT[0]) {
        digitalWrite(pin1, LOW);
        digitalWrite(pin2, LOW);
        digitalWrite(pin3, LOW);
        digitalWrite(pin4, LOW);
      }
      if (t >= offT[0] && t < onT[1]) {
        digitalWrite(pin1, LOW);
        digitalWrite(pin2, HIGH);
        digitalWrite(pin3, LOW);
        digitalWrite(pin4, LOW);
      }
      if (t >= onT[1] && t < offT[1]) {
        digitalWrite(pin1, LOW);
        digitalWrite(pin2, LOW);
        digitalWrite(pin3, LOW);
        digitalWrite(pin4, LOW);
      }
      if (t >= offT[1] && t < onT[2]) {
        digitalWrite(pin1, LOW);
        digitalWrite(pin2, LOW);
        digitalWrite(pin3, HIGH);
        digitalWrite(pin4, LOW);
      }
      if (t >= onT[2] && t < offT[2]) {
        digitalWrite(pin1, LOW);
        digitalWrite(pin2, LOW);
        digitalWrite(pin3, LOW);
        digitalWrite(pin4, LOW);
      }
      if (t >= offT[2] && t < onT[3]) {
        digitalWrite(pin1, LOW);
        digitalWrite(pin2, LOW);
        digitalWrite(pin3, LOW);
        digitalWrite(pin4, HIGH);
      }
      if (t >= onT[3] && t < offT[3]) {
        digitalWrite(pin1, LOW);
        digitalWrite(pin2, LOW);
        digitalWrite(pin3, LOW);
        digitalWrite(pin4, LOW);
      }

      if (t >= offT[3]) {
        st = FAST_STEP;
        tStamp = elapsedTimef;
        t = elapsedTimef - tStamp;

        onT[0] = onP;
        offT[0] = offP2 + onT[0];
        onT[1] = onP + offT[0];
        offT[1] = offP2 + onT[1];
        onT[2] = onP + offT[1];
        offT[2] = offP2 + onT[2];
        onT[3] = onP + offT[2];
        offT[3] = offP2 + onT[3];
      }
      break;
    case FAST_STEP:
      if (t < onT[0]) {
        digitalWrite(pin1, HIGH);
        digitalWrite(pin2, LOW);
        digitalWrite(pin3, LOW);
        digitalWrite(pin4, LOW);
      }
      if (t >= onT[0] && t < offT[0]) {
        digitalWrite(pin1, LOW);
        digitalWrite(pin2, LOW);
        digitalWrite(pin3, LOW);
        digitalWrite(pin4, LOW);
      }
      if (t >= offT[0] && t < onT[1]) {
        digitalWrite(pin1, LOW);
        digitalWrite(pin2, HIGH);
        digitalWrite(pin3, LOW);
        digitalWrite(pin4, LOW);
      }
      if (t >= onT[1] && t < offT[1]) {
        digitalWrite(pin1, LOW);
        digitalWrite(pin2, LOW);
        digitalWrite(pin3, LOW);
        digitalWrite(pin4, LOW);
      }
      if (t >= offT[1] && t < onT[2]) {
        digitalWrite(pin1, LOW);
        digitalWrite(pin2, LOW);
        digitalWrite(pin3, HIGH);
        digitalWrite(pin4, LOW);
      }
      if (t >= onT[2] && t < offT[2]) {
        digitalWrite(pin1, LOW);
        digitalWrite(pin2, LOW);
        digitalWrite(pin3, LOW);
        digitalWrite(pin4, LOW);
      }
      if (t >= offT[2] && t < onT[3]) {
        digitalWrite(pin1, LOW);
        digitalWrite(pin2, LOW);
        digitalWrite(pin3, LOW);
        digitalWrite(pin4, HIGH);
      }
      if (t >= onT[3] && t < offT[3]) {
        digitalWrite(pin1, LOW);
        digitalWrite(pin2, LOW);
        digitalWrite(pin3, LOW);
        digitalWrite(pin4, LOW);
      }

      if (t >= offT[3]) {
        count++;
        tStamp = elapsedTimef;
        t = elapsedTimef - tStamp;
      }
      if (count == 2) {
        count = 0;
        st = RANDOM;
        tStamp = elapsedTimef;
        t = elapsedTimef - tStamp;

        onT[0] = float(random(4, 6)) / 100;
        offT[0] = float(random(10, 21)) / 10 + onT[0];
        onT[1] = float(random(4, 6)) / 100;
        offT[1] = float(random(10, 21)) / 10 + onT[1];
        onT[2] = float(random(4, 6)) / 100;
        offT[2] = float(random(10, 21)) / 10 + onT[2];
        onT[3] = float(random(4, 6)) / 100;
        offT[3] = float(random(10, 21)) / 10 + onT[3];
      }
      break;
    case RANDOM:
      for (int i = 0; i < 4; i++) {
        tRandom[i] = elapsedTimef - tRandomStamp[i];
      }
      if (tRandom[0] < onT[0]) {
        digitalWrite(pin1, HIGH);
      }
      if (tRandom[0] >= onT[0] && tRandom[0] < offT[0]) {
        digitalWrite(pin1, LOW);
      }
      if (tRandom[1] < onT[1]) {
        digitalWrite(pin2, HIGH);
      }
      if (tRandom[1] >= onT[1] && tRandom[1] < offT[1]) {
        digitalWrite(pin2, LOW);
      }
      if (tRandom[2] < onT[2]) {
        digitalWrite(pin3, HIGH);
      }
      if (tRandom[2] >= onT[2] && tRandom[2] < offT[2]) {
        digitalWrite(pin3, LOW);
      }
      if (tRandom[3] < onT[3]) {
        digitalWrite(pin4, HIGH);
      }
      if (tRandom[3] >= onT[3] && tRandom[3] < offT[3]) {
        digitalWrite(pin4, LOW);
      }

      for (int i = 0; i < 4; i++) {
        if (tRandom[i] >= offT[i]) {
          tRandomStamp[i] = elapsedTimef;
          tRandom[i] = elapsedTimef - tRandomStamp[i];
          onT[i] = float(random(4, 6)) / 100;
          offT[i] = float(random(10, 21)) / 10 + onT[i];
        }
      }
      break;
    default:
      break;
  }
  if (tSeq >= tThreToSeq) {
    st = SLOW_STEP;
    tStamp = elapsedTimef;
    t = elapsedTimef - tStamp;
    tStampSeq = elapsedTimef;
    tSeq = elapsedTimef - tStampSeq;

    onT[0] = onP;
    offT[0] = offP + onT[0];
    onT[1] = onP + offT[0];
    offT[1] = offP + onT[1];
    onT[2] = onP + offT[1];
    offT[2] = offP + onT[2];
    onT[3] = onP + offT[2];
    offT[3] = offP + onT[3];
  }
}
