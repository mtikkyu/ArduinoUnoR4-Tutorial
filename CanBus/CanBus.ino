#include <R7FA4M1_CAN.h>

R7FA4M1_CAN can(10, 13);

union Float2Byte {
  float asFloat;
  uint8_t asUint8_t[4];
} foo;

uint8_t Buffer[8];
uint32_t time_sender = 0;

void setup() {
  Serial.begin(115200);
  can.begin(CanBitRate::BR_1000k);
}

void loop() {
  if (can.available()) {
    CanMsg msg;
    msg = can.read();
    memcpy(Buffer, msg.data, 8);

    foo.asUint8_t[0] = Buffer[4];
    foo.asUint8_t[1] = Buffer[5];
    foo.asUint8_t[2] = Buffer[6];
    foo.asUint8_t[3] = Buffer[7];

    Serial.println(foo.asFloat, 5);
  }

  if (millis() - time_sender > 20) {
    foo.asFloat = 0.15625f;

    Buffer[0] = 0x00;
    Buffer[1] = 0x00;
    Buffer[2] = 0x00;
    Buffer[3] = 0x00;
    Buffer[4] = foo.asUint8_t[0];
    Buffer[5] = foo.asUint8_t[1];
    Buffer[6] = foo.asUint8_t[2];
    Buffer[7] = foo.asUint8_t[3];

    CanMsg msg;
    msg.id = CanStandardId(0x201);
    msg.data_length = 8;
    memcpy(msg.data, Buffer, msg.data_length);

    can.write(msg);
  }
}
