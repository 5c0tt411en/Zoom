#include <Easing.h>
#include <L6470.h>

L6470* stepper = new L6470(11, 12, 13, 10, 9);
Easing* es = new Easing();

float t = 0, tStamp = 0, tThreToSeq = 610.0, tSeq = 0, tStampSeq = 0, from = 0, to = 0;
int npFrom = 0, npTo = 0;

enum State {
  P0,
  _P,
  PP,
  RANDOM
};

State st = P0;

void setup() {
  stepper->setup();
  stepper->resetDevice();
  stepper->goHome();

  to = random(0, 11000);
  npFrom = 0;
  npTo = random(0, 2);
}

void loop() {
  float elapsedTimef = float(millis()) / 1000.0;
  t = elapsedTimef - tStamp;
  tSeq = elapsedTimef - tStampSeq;

  switch (st) {
    case P0:
      if (t < 1.0) {
        stepper->run(0, es->easeInCubic(t, from, -from, 1.0));
      }
      if (t >= 10.0) {
        st = _P;
        tStamp = elapsedTimef;
        t = elapsedTimef - tStamp;
      }
      break;
    case _P:
      if (t < 4.0) {
        stepper->run(0, es->easeInCubic(t, 0, 11000, 4.0));
      }
      if (t >= 8.0 && t < 10.0) {
        stepper->run(0, es->easeInCubic(t - 8.0, 11000, -11000, 2.0));
      }
      if (t >= 10.0) {
        st = PP;
        tStamp = elapsedTimef;
        t = elapsedTimef - tStamp;
      }
      break;
    case PP:
      if (t < 8.0) {
        stepper->run(0, es->easeInCubic(t, 0, 5000, 8.0));
      }
      if (t >= 10.0) {
        st = RANDOM;
        tStamp = elapsedTimef;
        t = elapsedTimef - tStamp;

        from = 5000;
        to = random(0, 11000);
        npFrom = 1;
        npTo = random(0, 2);
      }
      break;
    case RANDOM:
      if (t < 1.0) {
        if (npFrom == npTo) {
          stepper->run(npTo, es->easeInCubic(t, from, to - from, 1.0));
        }
        else if (npFrom != npTo) {
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
        to = random(0, 11000);
        npFrom = npTo;
        npTo = random(0, 2);
      }
      break;
    default:
      break;
  }
  if (tSeq >= tThreToSeq) {
    st = P0;
    tStamp = elapsedTimef;
    t = elapsedTimef - tStamp;
    tStampSeq = elapsedTimef;
    tSeq = elapsedTimef - tStampSeq;

    from = to;
    to = random(0, 11000);
    npFrom = npTo;
    npTo = random(0, 2);
  }
}
