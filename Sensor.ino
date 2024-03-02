#include "Plotter.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  p.Begin();
  p.AddTimeGraph( "Current AMP Graph", 1500, "AMP'S", current_Ia );
}

void loop() {
  // put your main code here, to run repeatedly:
  // read the input on analog pin 0:
  /*
  Reads the value from the specified analog pin. Arduino boards contain a multichannel, 10-bit analog to digital converter. 
  This means that it will map input voltages between 0 and the operating voltage(5V or 3.3V) into integer values between 0 and 1023. 
  On an Arduino UNO, for example, this yields a resolution between readings of: 5 volts / 1024 units or, 0.0049 volts (4.9 mV) per unit. 
  See the table below for the usable pins, operating voltage and maximum resolution for some Arduino boards.
  https://www.arduino.cc/reference/en/language/functions/analog-io/analogread/
  */
/*
The relationship between detection current and analog signal output is:
V0 = Vcc / 2 + Ia * K

95% confident it is a matter of solving for Ia

V0 is the analog signal output in Volts (what we get from the hall sensor)

Ia is current

Vcc seems to be the hall sensor's operating volts which should be 5v.
Vcc COULD be but DOES NOT SEEM to be the volts going through the wire.

K is linearity and the chinese documentation says that it should be:
K = 60mV/A
or K = 60volts / 1000 Amps


volts_output_val = Vcc / 2.0 + Ia * k
volts_output_val - (Vcc / 2.0) = Ia * k
Ia * k = volts_output_val - (Vcc / 2.0)
Ia = (volts_output_val - (Vcc / 2.0) ) / k
*/
  double board_operating_volts = 5.0; // map input voltages between 0 and the operating voltage(5V or 3.3V) into integer values between 0 and 1023. V
  int raw_sensor_value = analogRead(A0); // On an Arduino UNO, for example, this yields a resolution between readings of: 5 volts / 1024 units or, 0.0049 volts (4.9 mV) per unit.
  double volts_output_val = raw_sensor_value * (board_operating_volts / 1023.0); // at 0 current this should be 2.5

  double k = 66.0 / 1000.0; // Linearity? What does that even mean?
  double Vcc = 5.0; // If this is the operating volts for the Hall sensor it should be 5 volts.

  double calibrated_Vcc = 2.465;
  //double current_Ia = (volts_output_val - (Vcc / 2.0)) / k; // * k ?
  double current_Ia = (volts_output_val - (calibrated_Vcc)) / k; // * k ?
  // print out the value you read:
  Serial.println(current_Ia);
  delay(100);  // delay in between reads for stability
  // Plotting Code
  Plotter p;
  p.Plot();

  
  
}
