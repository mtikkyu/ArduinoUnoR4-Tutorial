#define PWM_A D3
#define DIR_A D12
#define BRAKE_A  D9  // For brake motor.

#define PWM_B D11
#define DIR_B D13
#define BRAKE_B D8  // For brake motor.

#define MAXIMUM_DUTY 255

void setup() {
  Serial.begin(115200);

  pinMode(PWM_A, OUTPUT);
  pinMode(DIR_A, OUTPUT);
  pinMode(BRAKE_A, OUTPUT);

  pinMode(PWM_B, OUTPUT);
  pinMode(DIR_B, OUTPUT);
  pinMode(BRAKE_B, OUTPUT);
}

void loop() {

}

void MotorA(int16_t _duty) {
  if(_duty > MAXIMUM_DUTY) _duty = MAXIMUM_DUTY;
  else if(_duty < - MAXIMUM_DUTY) _duty = -MAXIMUM_DUTY;

  digitalWrite(BRAKE_A, 0);

  if(_duty > 0)      digitalWrite(DIR_A, 0);
  else if(_duty < 0) digitalWrite(DIR_A, 1);
  else { digitalWrite(DIR_A, 0); digitalWrite(BRAKE_A, 1); }

  analogWrite(PWM_A, abs(_duty));
}

void MotorB(int16_t _duty) {
  if(_duty > MAXIMUM_DUTY) _duty = MAXIMUM_DUTY;
  else if(_duty < - MAXIMUM_DUTY) _duty = -MAXIMUM_DUTY;

  digitalWrite(BRAKE_B, 0);

  if(_duty > 0)      digitalWrite(DIR_B, 0);
  else if(_duty < 0) digitalWrite(DIR_B, 1);
  else { digitalWrite(DIR_B, 0); digitalWrite(BRAKE_B, 1); }

  analogWrite(PWM_B, abs(_duty));
}

void Motor(int16_t _duty_a, int16_t _duty_b) {
  MotorA(_duty_a); MotorB(_duty_b);
}
