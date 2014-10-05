#ifndef PEAKDETECT_H
#define PEAKDETECT_H

// Includes
#include "ADC.h"
#include "DAC.h"

// Defines
#define TRIGGER_PERCENT		75			// trigger at 75 of max
#define MAX_ADC_VALUE		65535		// 16 bit - 1
#define TRIGGER_FREQ		1000		// Hz

#define	FALSE				0
#define TRUE				!(FALSE)

// Calculated defines
#define TRIGGER_VALUE       (MAX_ADC_VALUE * TRIGGER_PERCENT / 100)

// Prototype
void peakDetect(void);

#endif // PEAKDETECT_H

