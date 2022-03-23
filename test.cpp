#include "gtest/gtest.h"

extern "C" {
#include <avr/io.h>
#include "leds/led_driver.h"
#include "tmp_sensor/tmp36_driver.h"
}

class ThermometerTest : public ::testing::Test
{
protected :
	void SetUp() {
		init_leds();
	}
	void TearDown() {}
};

TEST_F(ThermometerTest, gtest) {
  EXPECT_EQ(0b11111111, PORTA);
}

TEST_F(ThermometerTest, Set_bit_in_PortA) {
	set_led(1, 1);
	EXPECT_EQ(0b11111110, PORTA);
}
TEST_F(ThermometerTest, Off_bit_in_PortA) {
	set_led(1, 0);
	EXPECT_EQ(0b11111111, PORTA);
}

TEST_F(ThermometerTest, Analog_To_Celsius) {
	ADCH = 0b00010011; //19 Celsius
	uint8_t read_T = ADCH;
	uint8_t temp_in_c = ((read_T * (5.0 / 1024.0)) - 500.0) / 10.0;
	EXPECT_FLOAT_EQ(temp_in_c, ADCH);
}
