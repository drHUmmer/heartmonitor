#include "peakDetect.h"

// Private function typedefs
static uint16_t BPMcalc(uint16_t);
static void HeartBeatConverter (uint16_t BPM);


// peakDetect
void peakDetect(void) {
	static 	uint8_t		peakDetected	= FALSE;
			uint16_t 	adcValue 		= 0;
	static	uint16_t	timerTicks		= 0;


	adcValue 	= adcGet();						// Get the latest heart beat value
	timerTicks 	++;								// Increase the timer ticks done

	if (peakDetected) {									// Check if there is a peakDetected active
		if (adcValue < TRIGGER_VALUE - TRIGGER_BUFFER) {// Min value (+ buffer) reached?
			peakDetected 	= FALSE;					// Peak has gone
		}
	}
	else {										// No peak detected
		if (adcValue >= TRIGGER_VALUE) {		// New peak detected
			peakDetected	= TRUE;				// New peak registered
			uint16_t BPM = BPMcalc(timerTicks);	// Calculate the BPM according to the delta timer
			HeartBeatConverter(BPM);			// Convert BPM to analog level
			timerTicks		= 0;				// Reset timer ticks
/*DEBUG*/	UART_sendData(2, BPM, NO_WAIT);
		}
	}
}

static uint16_t BPMcalc(uint16_t ticks) {
	uint32_t	BPM = TICKS_PER_MINUTE / ticks;	// Convert ticks to BPM
	return BPM;								// And return its value
}

static void HeartBeatConverter (uint16_t bpm) {
	u32 addPerStep 	= MAX_DAC_VALUE / DELTA_BPM_LEVEL;
	u32	DACoutput	= (bpm - MIN_BPM_LEVEL) * addPerStep;
	dacPut (DACoutput);
}
