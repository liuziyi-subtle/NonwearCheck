union NonwearEntry {
  int missing;
  double fvalue;
  // float fvalue;
  int qvalue;
};

float PredictGreen(union NonwearEntry* data);
float PredictIr(union NonwearEntry* data);