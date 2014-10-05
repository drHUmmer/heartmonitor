#ifndef PEAKDETECT_H
#define PEAKDETECT_H

// Includes
#include "ADC.h"
#include "DAC.h"
#include "UART.h"

// Defines
#define TRIGGER_PERCENT		75			// Trigger at 75 of max
#define TRIGGER_BUFFER		50			// Trigger buffer, to avoid jitter
#define TRIGGER_FREQ		10000		// Hz

#define MAX_ADC_VALUE		65535		// 16 bit - 1
#define MAX_DAC_VALUE		65535		// 16 bit - 1

#define MIN_BPM_LEVEL		40			// Min BPM (0V)
#define MAX_BPM_LEVEL		200			// Max BPM (3.3V)

#define	FALSE				0
#define TRUE				(!(FALSE))

// Calculated defines
#define TRIGGER_VALUE       (MAX_ADC_VALUE * TRIGGER_PERCENT / 100)
#define TICKS_PER_MINUTE	(TRIGGER_FREQ * 60)
#define DELTA_BPM_LEVEL		(MAX_BPM_LEVEL - MIN_BPM_LEVEL)

// Prototype
void peakDetect(void);

#endif // PEAKDETECT_H

