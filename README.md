# ArmSense

1. [Abstract](#abstract)
3. [Introduction](#introduction)
4. [Design](#design)
5. [Implementation](#implementation)
6. [Testing and Results](#testingandresults)
8. [Conclusion](#conclusion)


## Abstract
A prominent area of research and development in medical technology today is rehabilitation robotics. This entails creating robotic devices to assist disabled individuals with improving or restoring the functionality of non-functional parts of their bodies. If we consider a robotic arm, its primary function is replicating the movement of a human arm. Traditionaly, these arms are controlled using software suites, like ROS. This project dives deeper, looking at creating an arm band that reads forearm muscles to produce control signals that repicate that of a human hand.


## Introduction
This project has been an interest of mine for a long time, inspired by my time as a research assistant at Human Engineering Research Laboratories (HERL). In addition, I could see myself starting a medical device company one day, with an iteration of this project being a main product.

My main goal with this project was to create an armband that could read the signals from muscles in your forearm. On the market today, there is one dominant product called the Myo ArmBand, which reads 8 channels of signals in your forearm, predicting your hand movement and outputting it to an application. While this product has shown promise, it has a remarkably high price point. 


## Design
My design originates off of my first project in ECE 1895 (Junior Design), where I made an EMG sensing circuit to output a constant value (the strength of the signal). While this project utilizes a similar principle of measuring EMG signals, I had to redesign the circuit to get a clean output signal. 

### Reading EMG
For reading EMG, I chose to use a bipolar configuration. This means having 1 electrode as a ground on a non-muscly region of the arm, and 2 electrdoes on the same muscle a small distance apart. This will measure the potential difference between the 2 electrodes on a muscle in reference to the ground. 

"image of bipolar configuration"

### Processing EMG
To process the signal from the electrodes, I used a similiar process from my prior designs, which has proven (via research online) to result in clear signals. 

First, we use a apply a difference amplifier to suppress any noise in the signal. 

"image of diff amp"

From there, we can apply a high pass filter to get rid of low frequency noise. 

"image of high pass"

Next, we can apply a full wave rectifier to stabelize and smooth the signal, as well as only take positive values.

"image of full wave"

Finally, we can apply a low pass filter to get rid of high frequency noise.

"iamge of low pass"

At this point, the signal is well filtered and scaled to be an analog value any device could read.

### Using EMG
With this EMG signal, I planned to read it into a microcontroller, specifically the esp32, using an analog pin. This would allow me to see the value and communicate it to other hardware to perform various operations. For this project, having the esp32 communicate to a laptop via bluetooth to then display using a python script would be enough.

### Combining Everything
For this device, I decided to use 7 channels of electrodes in bipolar configuration. This means that there would be 7 muscle regions targeted around the forearm. The reference (ground) electrode would be placed on a part of the forearm that is bony (the back).

"image of configuration"

As you can see, there are 8 total modules. 7 of them are EMG modules, and 1 is the controller module. Each EMG module contains a circuit to read the EMG signal via electodes, process it, and output it. The controller module is the main unit that provides power to all the modules, as well as takes in the output signals from the EMG modules. 

All of these modules are housed in a PLA case, that were to be 3D printed. In addition, connected the modules posed a unique problem, as I needed a flexible material for a "one size fits all" design. Furthermore, this band needed to be able to encase the wires inside of it to connect modules to each other. For this, I decided to use TPU in a 3D printer. The entire band would have the capability to be powered by connecting it to a 5V source using the micro usb slot.

## Implementation
Implementation was very complicated for this project for a variety of reasons, such as 3D modeling, small scale pcb's, and un-simulateable circuits. These issues took a lot of iterating to resolve, which resulted in hours and hours of work.

### Circuit Simulation
To begin, the circuits were very hard to simulate. With such specific components, such as the voltage inverter and precision quad op-amps, there was no testing the circuit in SPICE before creating the PCB. Additionally, since the input signal is essentially just noise from your muscles, it is incredibly hard to accurate replicate that in terms of an input to the circuit. This meant I had to rely solely on tests done by others for similar circuits online to validate my own. 

### PCB's
PCB's were not as challenging, but still posed considerable issues. Originally, I based the scale of this device on the dimensions of an esp-32 development board, as that was the chip I would be using. Unfortunately, as I built the PCB, it realized to be much larger than anticipated. This meant having to redesign original CAD model prototypes for the housing. Additionally, I had 7 channels of measurement, but because of the size, I had to cut it down to 6 channels. Lastly, I had planned to have an IMU sensor for positioning of the band in space (for future use), but ended up not having space to put this in.

### CAD Modeling
What took the most time in this project was creating the enclosure for the device. Below I will go through the iterations I went through for this device.

Initially, I made cardboard prototype. This was used to judge the scale of the band and device.


After this, I liked the scale, so I did an initial 3D print of the cardboard modules, using tape to replicate a band. 


This turned out well, but around this time I made each modules' pcb. In turn, I had to make the enclosure for each module larger in order to fit the PCB in it. This increased the size of the modules considerably. 


With the size of the modules set, now I sought to create a system for the band that will connect these modules together. Something I realized is the difficulty of running wires through this band. I considered different types of connectors and ribbon cables, but realized quickly that it was far too complex for a prototype device as such.

To solve this issue, I came across a material called thermoplastic polyurethane (TPU) which can be 3D printed. This seemed like the easiest option to easily integrate into my pre-existing 3D model for the modules. 

Above is the first iteration, where I printed the band in 2 halves, glueing them together. As seen, you can put the wires through the channels in the center of the band. This was however a very difficult process, as gluing the 2 halves of the band together perfectly was not simple. The reason I designed it this way was because I was unaware if 3D printers could print supports in TPU, because of its stretchy material. As a solution, I ended up printing the band as a whole, except leaving the top open, so that I could place wires in and just fill the channel closed with epoxy or glue.



## Testing and Results
Testing went very smoothly, thanks to the many hours spent designing and implementing. 

One small issue I had was forgetting to order the stencil for the surface mount PCB's, which lead to a much longer time spent putting paste on pads and placing componenets. Additionally, I ordered some 0201 components, which were incredibly hard to place by hand due to the small scale. 

Another small issue was with programming the esp32 chip. Digikey did not have stock of a specific esp32 module which has a built in D+ and D- pin for programming it using a usb. This lead to me ordering a basic esp32-wroom chip, which I had to program by connecting the Tx and Rx pins in parallel with an esp32-wroom development board. 

As far as testing the rest of the device, once it was assembled, I wrote simple code for the chip to transmit the sensor data serially via bluetooth. I then wrote a simple python program to read this device and display the data, after the computer had connected to the bluetooth device.

As far as physical testing, I performed 100 max stretches of the band material, and it sustained no deformation or damage. 

## Conclusion
Overall, this project was very successful and I am happy with the outcome. I believe that I iterated well on my design and that the project reached the intended goal. Moving forward, I would like to continue working on this project but improving the noise isolation from the sensors, as well as building on the communication via bluetooth. From there, I plan to implement a training system to record a dataset of signals for each hand movement. I can then work on creating a machine learning classification model to accurately use realtime signals to predict the desired hand movement output. This could be useful for applications such as disabled individuals who lack fingers or a hand. 