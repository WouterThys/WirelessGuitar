/******************************************************************************/
/* System Level #define Macros                                                */
/******************************************************************************/


/* Microcontroller MIPs (FCY) */
#define SYS_FREQ        140000000L
#define FCY             SYS_FREQ/2



/******************************************************************************/
/* System Function Prototypes                                                 */
/******************************************************************************/

/* Custom oscillator configuration funtions, reset source evaluation
functions, and other non-peripheral microcontroller initialization functions
go here. */

void ConfigureOscillator(void); /* Handles clock switching/osc initialization */
void PLLset(void); /* Sets the PLL */

