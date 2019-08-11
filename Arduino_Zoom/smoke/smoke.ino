#include <Easing.h>
#include <L6470.h>

L6470* stepper = new L6470(11, 12, 13, 10, 9);
Easing* es = new Easing();

float t = 0, tStamp = 0, tThreToSeq = 237.0, tSeq = 0, tStampSeq = 0, from = 0, to = 0;
int npFrom = 0, npTo = 0, count = 0;

enum State {
  SEQ,
  WAIT
};

State st = WAIT;

void setup() {
  stepper->setup();
  stepper->resetDevice();
  stepper->goHome();

  to = random(0, 1000);
  npFrom = 0;
  npTo = random(0, 2);
}

void loop() {
  float elapsedTimef = float(millis()) / 1000.0;
  t = elapsedTimef - tStamp;
  tSeq = elapsedTimef - tStampSeq;

  switch (st) {
    case SEQ:
      if (1.0) {
        stepper->run(0, 600);
      }
      if (t >= 1.0 && t < 2.0) {
        stepper->run(0, 0);
      }
      if (t >= 2.0) {
        count++;
        tStamp = elapsedTimef;
        t = elapsedTimef - tStamp;
      }
      if (count >= 30) {
        count = 0;
        st = WAIT;
        tStamp = elapsedTimef;
        t = elapsedTimef - tStamp;
      }
      break;
    case WAIT:
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
        to = random(0, 1000);
        npFrom = npTo;
        npTo = random(0, 2);
      }
      break;
    default:
      break;
  }
  if (tSeq >= tThreToSeq) {
    st = SEQ;
    tStamp = elapsedTimef;
    t = elapsedTimef - tStamp;
    tStampSeq = elapsedTimef;
    tSeq = elapsedTimef - tStampSeq;

    from = to;
    to = random(0, 1000);
    npFrom = npTo;
    npTo = random(0, 2);
  }
}
