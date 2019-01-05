#define WHOLE_NOTE     1
#define HALF_NOTE      2
#define QUARTER_NOTE   4
#define EIGHTH_NOTE    8

struct beat {
  int note;
  int duration;
};
