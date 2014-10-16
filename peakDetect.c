#include "peakDetect.h"

// Private function typedefs
uint16_t BPMcalc(uint16_t);
void HeartBeatConverter (uint16_t BPM);


// peakDetect
void peakDetect(void) {
	static 	uint8_t		peakDetected	= FALSE;
			uint16_t 	adcValue 		= 0;
	static	uint16_t	timerTicks		= 0;
	static	uint8_t		ignorePeak		= FALSE;

	adcValue 	= adcGet();							// Get the latest heart beat value
//	UART_sendData(2, ((adcValue & 0xFF0) >> 4));
	//adcValue	= 0xf0;
	timerTicks 	++;									// Increase the timer ticks done

	if (peakDetected) {									// Check if there is a peakDetected active
		if (adcValue < TRIGGER_VALUE - TRIGGER_BUFFER) {// Min value (+ buffer) reached?
			peakDetected 	= FALSE;					// Peak has gone
		}
	}
	else {											// No peak detected
		if (adcValue >= TRIGGER_VALUE) {			// New peak detected
			peakDetected	= TRUE;					// New peak registered
			if (ignorePeak == FALSE) {
				uint16_t BPM = BPMcalc(timerTicks);	// Calculate the BPM according to the delta timer
				HeartBeatConverter(BPM);			// Convert BPM to analog level
				timerTicks		= 0;				// Reset timer ticks
/*DEBUG*/		UART_sendData(2, BPM);
				
				ignorePeak	= FALSE;					// Ignore the following peak
			}
			else
				ignorePeak	= FALSE;				// On the next peak calculate new BPM
		}
	}
}

uint16_t BPMcalc(uint16_t ticks) {
	uint32_t	BPM = TICKS_PER_MINUTE / ticks;	// Convert ticks to BPM
	return BPM;								// And return its value
}

void HeartBeatConverter (uint16_t bpm) {
	u32 addPerStep 	= MAX_DAC_VALUE / DELTA_BPM_LEVEL;
	u32	DACoutput	= (bpm - MIN_BPM_LEVEL) * addPerStep;
	dacPut (DACoutput);
}
