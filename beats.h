#define WHOLE_NOTE        1
#define HALF_NOTE_TIE     20
#define HALF_NOTE         2
#define QUARTER_NOTE_TIE  40
#define QUARTER_NOTE      4
#define EIGHTH_NOTE_TIE   40
#define EIGHTH_NOTE       8

struct beat {
  int note;
  int duration;
};
