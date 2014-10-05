#include "peakDetect.h"

// Private function typedefs
static uint8_t BPMcalc(uint16_t);


// peakDetect
void peakDetect(void) {
	static 	uint8_t		peakDetected	= FALSE;
			uint16_t 	adcValue 		= 0;
	static	uint16_t	timerTicks		= 0;


	adcValue = adcGet();

	if (peakDetected) {						// Check if there is a peakDetected active
		if (adcValue < TRIGGER_VALUE) {		// Threshold value reached?
			peakDetected = FALSE;			// Peak has gone
			BPMcalc(timerTicks);
		}
	}
	else {
		if (adcValue > TRIGGER_VALUE) {
			peakDetected = TRUE;
		}
	}
	
	timerTicks ++;
}

static uint8_t BPMcalc(uint16_t) {

	// ticks to BPM

	return 1;
}
