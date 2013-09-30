typedef struct Input {
  int pin;
  int key;
  boolean pressed;
  int sample_counter;
  boolean samples[NR_SAMPLES];
} Input;

