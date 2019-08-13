#include <Easing.h>
#include <L6470.h>

L6470* stepper = new L6470(11, 12, 13, 10, 9);
Easing* es = new Easing();

float t = 0, tStamp = 0, tThreToSeq = 502.0, tSeq = 0, tStampSeq = 0, from = 0, to = 0;
int npFrom = 0, npTo = 0;

enum State {
  P00,
  PP0,
  PPP,
  NPP,
  NNP,
  NNN,
  RANDOM
};

State st = P00;

void setup() {
  stepper->setup();
  stepper->resetDevice();
  stepper->goHome();

  to = random(0, 14000);
  npFrom = 0;
  npTo = random(0, 2);
}

void loop() {
  float elapsedTimef = float(millis()) / 1000.0;
  t = elapsedTimef - tStamp;
  tSeq = elapsedTimef - tStampSeq;

  switch (st) {
    case P00:
      if (t < 4.0) {
        stepper->run(0, es->easeInCubic(t, 0, 14000, 4.0));
      }
      if (t >= 10.0) {
        st = PP0;
        tStamp = elapsedTimef;
        t = elapsedTimef - tStamp;
      }
      break;
    case PP0:
      if (t >= 10.0) {
        st = PPP;
        tStamp = elapsedTimef;
        t = elapsedTimef - tStamp;
      }
      break;
    case PPP:
      if (t >= 10.0) {
        st = NPP;
        tStamp = elapsedTimef;
        t = elapsedTimef - tStamp;
      }
      break;
    case NPP:
      if (t < 1.0) {
        stepper->run(0, es->easeInCubic(t, 14000, -14000, 1.0));
      }
      if (t >= 1.0 && t < 2.0) {
        stepper->run(1, es->easeInCubic(t - 1.0, 0, 14000, 1.0));
      }
      if (t >= 4.0) {
        st = NNP;
        tStamp = elapsedTimef;
        t = elapsedTimef - tStamp;
      }
      break;
    case NNP:
      if (t >= 4.0) {
        st = NNN;
        tStamp = elapsedTimef;
        t = elapsedTimef - tStamp;
      }
      break;
    case NNN:
      if (t >= 4.0) {
        st = RANDOM;
        tStamp = elapsedTimef;
        t = elapsedTimef - tStamp;
        from = 14000;
        to = random(0, 14000);
        npFrom = 1;
        npTo = random(0, 2);
      }
      break;
    case RANDOM:
      if (t < 1.0) {
        if (npFrom == npTo) {
          stepper->run(npTo, es->easeInCubic(t, from, to - from, 1.0));
        }
        if (npFrom != npTo) {
          if (t < 0.5) {
            stepper->run(npFrom, es->easeInCubic(t, from, - from, 0.5));
          }
          else if (t >= 0.5 && t < 1.0) {
            stepper->run(npTo, es->easeInCubic(t - 0.5, 0, to, 0.5));
          }
        }
      }
      if (t >= 3.0) {
        tStamp = elapsedTimef;
        t = elapsedTimef - tStamp;
        
        from = to;
        to = random(0, 14000);
        npFrom = npTo;
        npTo = random(0, 2);
      }
      break;
    default:
      break;
  }
  if (tSeq >= tThreToSeq) {
    st = P00;
    tStamp = elapsedTimef;
    t = elapsedTimef - tStamp;
    tStampSeq = elapsedTimef;
    tSeq = elapsedTimef - tStampSeq;

    from = to;
    to = random(0, 14000);
    npFrom = npTo;
    npTo = random(0, 2);
  }
}
