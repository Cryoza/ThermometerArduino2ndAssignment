#include "gtest/gtest.h"

extern "C" {
#include <avr/io.h>
#include "leds/led_driver.h"
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