/* This files provides address values that exist in the system */

/* Memory */
			.equ	DDR_START,					0x00000000
			.equ	DDR_END,						0x3FFFFFFF
			.equ	A9_ONCHIP_START, 			0xFFFF0000
			.equ	A9_ONCHIP_END,				0xFFFFFFFF
			.equ	SDRAM_START,				0xC0000000
			.equ	SDRAM_END,					0xC3FFFFFF
			.equ	FPGA_ONCHIP_START,		0xC8000000
			.equ	FPGA_ONCHIP_END,			0xC8003FFF
			.equ	FPGA_CHAR_START,			0xC9000000
			.equ	FPGA_CHAR_END,				0xC9001FFF

/* Cyclone V FPGA devices */
			.equ	LEDR_BASE, 					0xFF200000
			.equ	HEX3_HEX0_BASE, 			0xFF200020
			.equ	HEX5_HEX4_BASE, 			0xFF200030
			.equ	SW_BASE,						0xFF200040
			.equ	KEY_BASE, 					0xFF200050
			.equ	JTAG_UART_BASE, 			0xFF201000
			.equ	TIMER_BASE, 				0xFF202000

/* Cyclone V HPS devices */
			.equ	HPS_GPIO1_BASE,			0xFF709000
			.equ	HPS_TIMER0_BASE,			0xFFC08000
			.equ	HPS_TIMER1_BASE,			0xFFC09000
			.equ	HPS_TIMER2_BASE,			0xFFD00000
			.equ	HPS_TIMER3_BASE,			0xFFD01000
			.equ	FPGA_BRIDGE, 				0xFFD0501C

/* ARM A9 MPCORE devices */
			.equ	PERIPH_BASE, 				0xFFFEC000       	// base address of peripheral devices

			/* Interrupt controller (GIC) CPU interface(s) */
			.equ	MPCORE_GIC_CPUIF,    	0xFFFEC100			// PERIPH_BASE + 0x100
			.equ	ICCICR,						0x00					// CPU interface control register
			.equ	ICCPMR,						0x04					// interrupt priority mask register
			.equ	ICCIAR,						0x0C					// interrupt acknowledge register
			.equ	ICCEOIR,						0x10					// end of interrupt register
			/* Interrupt controller (GIC) distributor interface(s) */
			.equ	MPCORE_GIC_DIST,     	0xFFFED000			// PERIPH_BASE + 0x1000
			.equ	ICDDCR,						0x00					// distributor control register
			.equ	ICDISER,						0x100					// interrupt set-enable registers
			.equ	ICDICER,						0x180					// interrupt clear-enable registers
			.equ	ICDIPTR,						0x800					// interrupt processor targets registers
			.equ	ICDICFR,						0xC00					// interrupt configuration registers

			/* Private timer interface(s) */
			.equ	MPCORE_PRIV_TIMER,		0xFFFEC600			// PERIPH_BASE + 0x0600
