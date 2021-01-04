> Use `make` to build the test `epd` executable.  
> Test successful build with `sudo ./epd`

This file is to help you use this routine.
A brief description of the use of this project is here:

1. Basic information:  
This routine has been verified using the e-paper Driver HAT module. 
You can view the corresponding test routines in the `\lib\Examples\`
of the project.

2. Pin connection:  
You can view the pin connection in DEV_Config.h in the `\lib\Config\` directory, it's repeated here:

    ```
    EPD    =>    Jetson Nano/RPI(BCM)
    VCC    ->    3.3
    GND    ->    GND
    DIN    ->    10(SPI0_MOSI)
    CLK    ->    11(SPI0_SCK)
    CS     ->    8(SPI0_CS0)
    DC     ->    25
    RST    ->    17
    BUSY   ->    24
    ```
    
3. Basic use:  

    ```
    make
    compile the program, will generate the executable file: epd
    Run: 
    sudo ./epd
    If you modify the program, you need to execute: 
    make clean
    make
    ```

4. Directory structure (selection):  
The API manual for the function can be downloaded from the Waveshare Wiki or requested as an after-sales at customer service. Here is a brief introduction:  
`Config\`: This directory is a hardware interface layer file. You can see many definitions in DEV_Config.c(.h), including:
	- type of data;
	- GPIO;
	- Read and write GPIO;
	- Delay: Note: This delay function does not use an oscilloscope to measure specific values.
	- Module Init and exit processing:
		- void DEV_Module_Init(void);
		- void DEV_Module_Exit(void);
		- Note:
			1. Here is the processing of some GPIOs before and after using the ink screen.
			2. For the PCB with Rev2.1, the entire module will enter low power consumption after DEV_Module_Exit(). After testing, the power consumption is basically 0;
			3. 
    `\lib\GUI\`: This directory contains some basic image processing functions (see in GUI_Paint.c[.h]):
	- Common image processing: creating graphics, flipping graphics, mirroring graphics, setting pixels, clearing screens, etc.
	- Common drawing processing: drawing points, lines, boxes, circles, Chinese characters, English characters, numbers, etc.;
	- Common time display: Provide a common display time function;
	- Commonly used display pictures: provide a function to display bitmaps;
    
    `\lib\Fonts\`: for some commonly used fonts:
	- Ascii:
		- Font8: 5*8
		- Font12: 7*12
		- Font16: 11*16
		- Font20: 14*20
		- Font24: 17*24
	- Chinese:
		- font12CN: 16*21
		- font24CN: 32*41
        
    `\lib\E-paper\`: This screen is the ink screen driver function;  
    `Examples\`: This is the test program for the ink screen. You can see the specific usage method in it.
