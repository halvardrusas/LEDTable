#include <IRremote.h>
#include "irremoteheader.h"
#include "LEDTable.h"
#include <SoftwareSerial.h>



int keyesRemoteReceived(IRrecv irrecv,decode_results results){
	int key = -1;
	if (irrecv.decode(&results)) {
    delay(10);
		long val = results.value;

		switch(val){
			case ZERO_0:  key = 0; break;
			case ONE_1:   key = 1; break;
			case TWO_2:   key = 2; break;
			case THREE_3: key = 3; break;
			case FOUR_4:  key = 4; break;
			case FIVE_5:  key = 5; break;
			case SIX_6:   key = 6; break;
			case SEVEN_7: key = 7; break;
			case EIGHT_8: key = 8; break;
			case NINE_9:  key = 9; break;
			case LEFT_10: key = 10; break;
			case UP_11:   key = 11; break;
			case RIGHT_12:key = 12; break;
			case DOWN_13: key = 13; break;
			case OK_14:   key = 14; break;
			case STAR_15: key = 15; break;
			case HASH_16: key = 16; break;
		}
		irrecv.resume(); // Receive the next value
		Serial.println(val, HEX);
	}

	return key;
}
