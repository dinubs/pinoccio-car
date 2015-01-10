/**************************************************************************\
* Pinoccio Library                                                         *
* https://github.com/Pinoccio/library-pinoccio                             *
* Copyright (c) 2014, Pinoccio Inc. All rights reserved.                   *
* ------------------------------------------------------------------------ *
*  This program is free software; you can redistribute it and/or modify it *
*  under the terms of the MIT License as described in license.txt.         *
\**************************************************************************/
#include <SPI.h>
#include <Wire.h>
#include <Scout.h>
#include <GS.h>
#include <bitlash.h>
#include <lwm.h>
#include <js0n.h>

#include "version.h"

void setup() {
  Scout.setup(SKETCH_NAME, SKETCH_REVISION, SKETCH_BUILD);
  // Add custom setup code here
  addBitlashFunction("go", (bitlash_function)go);  
  addBitlashFunction("no", (bitlash_function)no);  
  addBitlashFunction("forward", (bitlash_function)forward);
  addBitlashFunction("backward", (bitlash_function)backward);
  addBitlashFunction("left", (bitlash_function)left);
  addBitlashFunction("right", (bitlash_function)right);
  addBitlashFunction("straight", (bitlash_function)straight);
}

void loop() {
  Scout.loop();
}
void go() {
  digitalWrite(2, HIGH);
}
void no() {
  digitalWrite(2, LOW);
}
void forward(int duration) {
  Serial.println(duration);
  digitalWrite(2, HIGH);
  digitalWrite(3, LOW);
  digitalWrite(4, HIGH);
}
void backward() {
  digitalWrite(2, HIGH);
  digitalWrite(4, LOW);
  digitalWrite(3, HIGH);
}
void straight() {
  digitalWrite(8, LOW); 
}
void left() {
  digitalWrite(8, HIGH);
  digitalWrite(6, LOW);
  digitalWrite(7, HIGH);
}
void right() {
  digitalWrite(8, HIGH);
  digitalWrite(7, LOW);
  digitalWrite(6, HIGH); 
}
