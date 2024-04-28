# ArmSense

1. [Abstract](#abstract)
3. [Introduction](#introduction)
4. [Design](#design)
5. [Implementation](#implementation)
6. [Testing/Results](#testing/results)
8. [Conclusion](#conclusion)


## Abstract
A prominent area of research and development in medical technology today is rehabilitation robotics. This entails creating robotic devices to assist disabled individuals with improving or restoring the functionality of non-functional parts of their bodies. If we consider a robotic arm, its primary function is replicating the movement of a human arm. Traditionally, these arms are controlled using software suites, like ROS. This project dives deeper, looking at creating an arm band that reads forearm muscles to produce control signals that replicate that of a human hand.


## Introduction
This project has been an interest of mine for a long time, inspired by my time as a research assistant at Human Engineering Research Laboratories (HERL). In addition, I could see myself starting a medical device company one day, with an iteration of this project being the main product.

My main goal with this project was to create an armband that could read the signals from muscles in your forearm. On the market today, there is one dominant product called the Myo ArmBand, which reads 8 channels of signals in your forearm, predicting your hand movement and outputting it to an application. While this product has shown promise, it has a remarkably high price point. 


## Design
My design originates off of my first project in ECE 1895 (Junior Design), where I made an EMG sensing circuit to output a constant value (the strength of the signal). While this project utilizes a similar principle of measuring EMG signals, I had to redesign the circuit to get a clean output signal. 

### Reading EMG
For reading EMG, I chose to use a bipolar configuration. This means having 1 electrode as a ground on a non-muscly region of the arm, and 2 electrodes on the same muscle a small distance apart. This will measure the potential difference between the 2 electrodes on a muscle in reference to the ground. 

![9D1DBAB3-BD5C-46C8-81DE-E8786506BA1B_1_105_c](https://github.com/keshavshankar08/ECE1895-Project3/assets/86859516/81ffe495-fabf-4064-8685-3b8ec2a9b287)


### Processing EMG
To process the signal from the electrodes, I used a similar process from my prior designs, which has proven (via research online) to result in clear signals. 

First, we use apply a difference amplifier to suppress any noise in the signal. 

<img width="704" alt="Screenshot 2024-04-27 at 10 59 26 PM" src="https://github.com/keshavshankar08/ECE1895-Project3/assets/86859516/c7e7d2a7-b1da-460f-b04b-17922e5fb856">

From there, we can apply a high pass filter to get rid of low-frequency noise. 

<img width="703" alt="Screenshot 2024-04-27 at 10 59 58 PM" src="https://github.com/keshavshankar08/ECE1895-Project3/assets/86859516/92c7800a-3edc-4b1d-975f-f9ea10f62014">

Next, we can apply a full wave rectifier to stabilize and smooth the signal, as well as only take positive values.

<img width="701" alt="Screenshot 2024-04-27 at 11 00 16 PM" src="https://github.com/keshavshankar08/ECE1895-Project3/assets/86859516/689113a8-7a2c-43db-987a-6513a28cf6db">

Finally, we can apply a low pass filter to get rid of high-frequency noise.

<img width="706" alt="Screenshot 2024-04-27 at 11 00 29 PM" src="https://github.com/keshavshankar08/ECE1895-Project3/assets/86859516/031470bb-4866-4b9e-841b-cd26436cffc2">

At this point, the signal is well-filtered and scaled to be an analog value any device could read.

### Using EMG
With this EMG signal, I planned to read it into a microcontroller, specifically the esp32, using an analog pin. This would allow me to see the value and communicate it to other hardware to perform various operations. For this project, having the esp32 communicate to a laptop via Bluetooth to then display using a Python script would be enough.

### Combining Everything
For this device, I decided to use 7 channels of electrodes in a bipolar configuration. This means that there would be 7 muscle regions targeted around the forearm. The reference (ground) electrode would be placed on a part of the forearm that is bony (the back).

![31DEB9EC-25D8-495D-9CDA-DF795381D066_1_105_c](https://github.com/keshavshankar08/ECE1895-Project3/assets/86859516/34872f9a-69e3-44ed-9970-7ca5f97114b3)

As you can see, there are 7 total modules. 6 of them are EMG modules, and 1 is the controller module. Each EMG module contains a circuit to read the EMG signal via electrodes, process it, and output it. The controller module is the main unit that provides power to all the modules, as well as takes in the output signals from the EMG modules. 

All of these modules are housed in a PLA case, that was to be 3D printed. In addition, connecting the modules posed a unique problem, as I needed a flexible material for a "one size fits all" design. Furthermore, this band needed to be able to encase the wires inside of it to connect modules. For this, I decided to use TPU in a 3D printer. The entire band would have the capability to be powered by connecting it to a 5V source using the micro USB slot.

## Implementation
Implementation was very complicated for this project for a variety of reasons, such as 3D modeling, small-scale PCBs, and un-simulatable circuits. These issues took a lot of iterating to resolve, which resulted in hours and hours of work.

### Circuit Simulation
To begin, the circuits were tough to simulate. With such specific components, such as the voltage inverter and precision quad op-amps, there was no testing of the circuit in SPICE before creating the PCB. Additionally, since the input signal is essentially just noise from your muscles, it is incredibly hard to accurately replicate that in terms of an input to the circuit. This meant I had to rely solely on tests done by others for similar circuits online to validate my own. 
<img width="1001" alt="Screenshot 2024-04-11 at 3 29 12 PM (1)" src="https://github.com/keshavshankar08/ECE1895-Project3/assets/86859516/037d4ecc-e57e-4895-b972-5860e0bcde01">
<img width="681" alt="Screenshot 2024-04-11 at 3 28 46 PM" src="https://github.com/keshavshankar08/ECE1895-Project3/assets/86859516/4f7593ab-a95c-4c53-b55b-8f3d3c7cadea">

![stage1_instrumentationAmplifier](https://github.com/keshavshankar08/ECE1895-Project3/assets/86859516/e1013536-eeac-4aca-b81c-4eabe79b911c)
![stage2_invertingAmplifier](https://github.com/keshavshankar08/ECE1895-Project3/assets/86859516/9bf1c105-b060-4c32-ac68-7cc7f9c842da)
![stage3_acCoupling](https://github.com/keshavshankar08/ECE1895-Project3/assets/86859516/ac11deeb-6b29-4036-b659-38786f69d1ed)
![stage4_highPassFilter](https://github.com/keshavshankar08/ECE1895-Project3/assets/86859516/b5cd0a6d-8b0a-42a5-a70a-7e703dd53fa9)
![stage5_fullWaveRectifier](https://github.com/keshavshankar08/ECE1895-Project3/assets/86859516/961ddf84-ce88-438f-9de1-2dd5331b35ab)

### PCB's
PCBs were not as challenging but still posed considerable issues. Originally, I based the scale of this device on the dimensions of an esp-32 development board, as that was the chip I would be using. Unfortunately, as I built the PCB, it was realized to be much larger than anticipated. This meant having to redesign the original CAD model prototypes for the housing. Additionally, I had 7 channels of measurement, but because of the size, I had to cut it down to 6 channels. Lastly, I had planned to have an IMU sensor for positioning the band in space (for future use) but ended up not having space to put this in.

<img width="685" alt="Screenshot 2024-04-11 at 3 24 02 PM" src="https://github.com/keshavshankar08/ECE1895-Project3/assets/86859516/5c625af7-759a-4d9b-ab6b-d80b3f908cfe">
<img width="680" alt="Screenshot 2024-04-11 at 3 22 42 PM (1)" src="https://github.com/keshavshankar08/ECE1895-Project3/assets/86859516/1a1f58d7-efb1-4de7-9a56-211eb6cff326">


### CAD Modeling
What took the most time in this project was creating the enclosure for the device. Below I will go through the iterations I went through for this device.

Initially, I made a cardboard prototype. This was used to judge the scale of the band and device.

![BF065295-81FC-49F3-BD9A-010BE8248C81_1_105_c](https://github.com/keshavshankar08/ECE1895-Project3/assets/86859516/18c785a1-e417-4ce7-bd13-39723cfba50c)

After this, I liked the scale, so I did an initial 3D print of the cardboard modules, using tape to replicate a band. 

![09A99287-5D0D-4A26-9E86-08877ABC900F_1_105_c](https://github.com/keshavshankar08/ECE1895-Project3/assets/86859516/cf699a32-5f6f-4804-8968-debecf8e4d9d)

This turned out well, but around this time I made each module's pcb. In turn, I had to make the enclosure for each module larger to fit the PCB in it. This increased the size of the modules considerably. 

![F697DD50-8025-4AB5-9D1A-22EACA2AA17F_1_105_c](https://github.com/keshavshankar08/ECE1895-Project3/assets/86859516/624dc18e-5ae4-4d91-821a-f34fc3ebe3b4)

With the size of the modules set, now I sought to create a system for the band that would connect these modules. Something I realized is the difficulty of running wires through this band. I considered different types of connectors and ribbon cables but realized quickly that it was far too complex for a prototype device as such.

To solve this issue, I came across a material called thermoplastic polyurethane (TPU) which can be 3D printed. This seemed like the easiest option to easily integrate into my pre-existing 3D model for the modules. 

![F2CC09F0-B762-41BF-A962-83DB43CDF391_1_105_c](https://github.com/keshavshankar08/ECE1895-Project3/assets/86859516/debe3711-b402-4abd-8f8a-dfd9d0279392)

Above is the first iteration, where I printed the band in 2 halves, gluing them together. As seen, you can put the wires through the channels in the center of the band. This was however a very difficult process, as gluing the 2 halves of the band together perfectly was not simple. The reason I designed it this way was because I was unaware if 3D printers could print supports in TPU, because of its stretchy material. As a solution, I ended up printing the band as a whole, except leaving the top open, so that I could place wires in and just fill the channel closed with epoxy or glue.

![47350A08-F649-47FF-B671-FC1F9193143D_1_105_c](https://github.com/keshavshankar08/ECE1895-Project3/assets/86859516/778bd062-6073-4229-a611-89a9252ea6cf)

Additionally, for the electrodes themselves, I used stainless steel cubes, which I soldered wires to.

![6066D10F-8A22-4296-9DC3-8068A2197301_1_105_c](https://github.com/keshavshankar08/ECE1895-Project3/assets/86859516/d90a7395-c340-4efc-80dd-a21da83310b3)

## Testing/Results
Testing went very smoothly, thanks to the many hours spent designing and implementing. 

One small issue I had was forgetting to order the stencil for the surface mount PCBs, which led to a much longer time spent putting paste on pads and placing components. Additionally, I ordered some 0201 components, which were incredibly hard to place by hand due to the small scale. 

Another small issue was with programming the esp32 chip. Digikey did not have stock of a specific esp32 module which has a built-in D+ and D- pin for programming it using a USB. This lead to me ordering a basic esp32-wroom chip, which I had to program by connecting the Tx and Rx pins in parallel with an esp32-wroom development board. 

As far as testing the rest of the device, once it was assembled, I wrote simple code for the chip to transmit the sensor data serially via Bluetooth. I then wrote a simple python program to read this device and display the data, after the computer had connected to the Bluetooth device.

As far as physical testing, I performed 100 max stretches of the band material, and it sustained no deformation or damage. 

## Conclusion
Overall, this project was very successful and I am happy with the outcome. I believe that I iterated well on my design and that the project reached the intended goal. Moving forward, I would like to continue working on this project but improving the noise isolation from the sensors, as well as building on the communication via Bluetooth. From there, I plan to implement a training system to record a dataset of signals for each hand movement. I can then work on creating a machine learning classification model to accurately use real-time signals to predict the desired hand movement output. This could be useful for applications such as disabled individuals who lack fingers or a hand. 

Below is the final product:
![A1C61AD7-2C29-4DD5-ACF7-540074C5D4DB_1_105_c](https://github.com/keshavshankar08/ECE1895-Project3/assets/86859516/f7dfe2a8-d730-49d1-9fe0-fa8e1b0e17e7)

![A334BCDD-0C69-4528-BF55-BED304AD3C52_1_105_c](https://github.com/keshavshankar08/ECE1895-Project3/assets/86859516/ab554615-c346-40f2-9bd6-1d010acfb920)

Finally, here are some cool pictures from working on this project:
![40BD5189-B68E-4BB8-8037-18A26C659DC0_1_105_c](https://github.com/keshavshankar08/ECE1895-Project3/assets/86859516/f48c3061-9b78-4ed8-bc68-3ed216a27375)

![9A60B4CD-CE38-4E02-BFEE-C8EA00AE4670_1_105_c](https://github.com/keshavshankar08/ECE1895-Project3/assets/86859516/b1c386d3-4ed0-48e9-a3d6-c75625443b25)

![7A37476B-1852-4E86-8B23-EB4EB386A243_1_105_c](https://github.com/keshavshankar08/ECE1895-Project3/assets/86859516/86888d6a-c670-41fe-8ba4-c714bf76a68d)

![5B5ECA5B-0F0A-49E4-AA38-1DD418A3521E_1_105_c](https://github.com/keshavshankar08/ECE1895-Project3/assets/86859516/8901236d-65f0-40f8-ad92-0c540f8cb97d)

![0DC91D2B-45A0-4B9C-86C6-304A399A4314_1_105_c](https://github.com/keshavshankar08/ECE1895-Project3/assets/86859516/3d8babdb-741d-413a-84b8-9aaceddd5aa8)

![3BB3CCD8-2746-439C-853F-52260F091A09_1_105_c](https://github.com/keshavshankar08/ECE1895-Project3/assets/86859516/030b8163-665f-4b47-849a-2dc35c3bf0a5)

![0C364D26-5F13-4491-82C3-CB9765167DD0_1_105_c](https://github.com/keshavshankar08/ECE1895-Project3/assets/86859516/3c8e4c1a-bd3c-43d8-afaa-e8b77cef1e30)

<img width="675" alt="Screenshot 2024-04-27 at 11 14 21 PM" src="https://github.com/keshavshankar08/ECE1895-Project3/assets/86859516/213e3b0c-4578-44d2-9ab7-fa1417dc0dac">

<img width="561" alt="Screenshot 2024-04-27 at 11 14 39 PM" src="https://github.com/keshavshankar08/ECE1895-Project3/assets/86859516/c0b24738-ce23-4cc4-b4e0-5662d599e4fd">
