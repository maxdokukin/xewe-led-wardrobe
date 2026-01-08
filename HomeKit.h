// HomeKit server configuration
extern "C" homekit_server_config_t config;
static uint32_t next_heap_millis = 0;

// Desk Lights Characteristics
extern "C" homekit_characteristic_t on, bright, sat, hue, switch_on;


// Function Declarations
void syncValuesHomekit();
void setupHomeKit();
void homeKitLoop();

// Desk Lights Functions
void switch_on_setter(const homekit_value_t value) {
  Serial.println("Switch 1");
  switch_on.value.bool_value = value.bool_value;
  lights->setMode(value.bool_value ? PERLIN : SOLID_COLOR);
}

void set1_on(const homekit_value_t value) {
  Serial.println("Light 1 ON/OFF");
  on.value.bool_value = value.bool_value;
  value.bool_value ? lights->turnOn() : lights->turnOff();
}

void set1_hue(const homekit_value_t value) {
  Serial.println("Light 1 Hue");
  hue.value.float_value = value.float_value;
  lights->setHue(value.float_value);
}

void set1_sat(const homekit_value_t value) {
  Serial.println("Light 1 Saturation");
  sat.value.float_value = value.float_value;
  lights->setSat(value.float_value);
}

void set1_bright(const homekit_value_t value) {
  Serial.println("Light 1 Brightness");
  bright.value.int_value = value.int_value;
  lights->setBrightness(value.int_value);
}


// Synchronize all values
void syncValuesHomekit() {
  on.value.bool_value = lights->getState();
  bright.value.int_value = lights->getTargetBrightness();
  sat.value.float_value = lights->getSat();
  hue.value.float_value = lights->getHue();
  switch_on.value.bool_value = lights->getMode();
}

// HomeKit Setup
void setupHomeKit() {
  on.setter = set1_on;
  bright.setter = set1_bright;
  sat.setter = set1_sat;
  hue.setter = set1_hue;
  switch_on.setter = switch_on_setter;

  arduino_homekit_setup(&config);
}

// HomeKit Loop
void homeKitLoop() {
  arduino_homekit_loop();
  uint32_t currentTime = millis();
  if (currentTime > next_heap_millis) {
    next_heap_millis = currentTime + 5000;
  }
}
