void setup() {
  Serial.begin(9600);

}

void loop() {
  Serial.println(acos(.5) * (180/3.14));
}
