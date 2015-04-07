struct note {
  int pitch;
  float duration;
};

// source http://www.musicnotes.com/sheetmusic/mtdFPE.asp?ppn=MN0035443
// all F are sharp
struct note melody[] = {
  {NOTE_D5, 0.5 + 0.125}, // sing
  {NOTE_B4, 0.125}, // in'
  {NOTE_A4, 0.125}, // in
  {NOTE_G4, 0.125},  // the
  {NOTE_E4, 0.5 + 0.25}, // rain
  {NOTE_D4, 0.25}, // just
  {NOTE_G4, 0.5 + 0.125}, //sing *
  {NOTE_G4, 0.125}, // in'
  {NOTE_A4, 0.125}, // in
  {NOTE_B4, 0.125}, // the
  {NOTE_D5, 0.5 + 0.25}, // rain
  {NOTE_D4, 0.125}, // what
  {NOTE_E4, 0.125}, // a
  {NOTE_G4, 0.5 + 0.125}, // glo
  {NOTE_A4, 0.125}, // ri
  {NOTE_B4, 0.25}, // ous
  {NOTE_D5, 0.5}, // feel
  {NOTE_B4, 0.25}, // ing
  {NOTE_D5, 0.25}, // I'm
  {NOTE_D5, 0.5 + 0.125}, // Hap
  {NOTE_B4, 0.125}, // py
  {NOTE_A4, 0.25}, // A
  {NOTE_E4, 0.5 + 0.25}, // gain

  {NOTE_D4, 0.25}, // I'm
  {NOTE_D5, 0.5 + 0.125}, // laugh
  {NOTE_B4, 0.125}, // ing
  {NOTE_A4, 0.25}, // at
  // repeat from *
  
};
