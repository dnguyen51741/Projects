#include "mbed.h"
#include "MMA8452.h"
#include "PinDetect.h"
#include "States.cpp"
#include <cstdlib>
#include "FftComplex.hpp"

//Set Up LED and Pushbuttons
DigitalOut myled1(LED1), myled2(LED2), myled3(LED3), myled4(LED4); //check for pushbutton
PinDetect pb_test(p16); //test for interrupt
DigitalIn pb(p15); //constantly check to see if pressed within interrupt
Serial pc(USBTX,USBRX); //to print out stuff to terminal
MMA8452 acc(p28, p27, 100000); //accelerometer

int count = 0, start, logging = 0;
double x, y, z, xThr, yThr, zThr, thr = 0.2;
int x_int, y_int, z_int;

// state 1 = left, right
int state = 1;

//Pushbutton Interrupt
void pb_pressed(void);

// Comparing Array to model
int compare(int vec[], int size);

int main(){ //use for interrupt
    pb_test.mode(PullUp);
    wait(.01); // Delay for initial pullup to take effect
    pb_test.attach_deasserted(&pb_pressed); //connect interrupt method to pushbutton
    pb_test.setSampleFrequency(5000); // Start sampling pb inputs using interrupts, sample period in uSeconds
    while(1){ //waits for button to be pushed
        myled2 = !myled2; //used to verify the program is still running
        wait(.5);
    }
    return 0; //never reached
}

void pb_pressed(void){ //button is pressed

    acc.readXYZGravity(&xThr,&yThr,&zThr); // get data from accelerometer
    pc.printf("x threshold: %5.2f\n", xThr);
    pc.printf("y threshold: %5.2f\n", yThr);
    pc.printf("z threshold: %5.2f\n", zThr);
    
    bool comp = false;

    while(pb == 0 && count < 600){
        myled1 = 1;
        acc.readXYZGravity(&x,&y,&z); // get data from accelerometer

        if(logging == 0 && (fabs(x-xThr) > thr || fabs(y-yThr) > thr || fabs(z-zThr) > thr)){
            int xVec[(600-count)];
            int yVec[(600-count)];
            int zVec[(600-count)];
            pc.printf("size of new vectors: %d\n",600-count);
            start = count;
            pc.printf("start: %d\n",start);

            xVec[0] = (int) (100*x);
            yVec[0] = (int) (100*y);
            zVec[0] = (int) (100*z);

            pc.printf("xVec[0] is %d\n", xVec[(count-start)]);
            pc.printf("yVec[0] is %d\n", yVec[(count-start)]);
            pc.printf("zVec[0] is %d\n", zVec[(count-start)]);
            
            count++;
            logging++;

            while(pb == 0 && count < 600){
                acc.readXYZGravity(&x,&y,&z); //get data from accelerometer

                xVec[(count-start)] = (int) (100*x);
                yVec[(count-start)] = (int) (100*y);
                zVec[(count-start)] = (int) (100*z);
                pc.printf("xVec[%d] is %d\n",(count-start), xVec[(count-start)]);
                pc.printf("yVec[%d] is %d\n",(count-start), yVec[(count-start)]);
                pc.printf("zVec[%d] is %d\n",(count-start), zVec[(count-start)]);
                
                count++;
                logging++;
                wait(.005);
                
                comp = true;
                
            }
            
            if (comp) {
                int state = compare(xVec, count-start);
                //compare(yVec, count-start);
                //compare(zVec, count-start);
                pc.printf("State is: %d", state);
                
                
                comp = false;
            }
        }
        
        count++;
        wait(.005);
    }

    // 600 samples have been taken in total, with xVec, yVec, and zVec logging
    // samples after the first instance of one of the accelerometer readings
    // breaks their respective threshold
    pc.printf("logging: %d\n", logging);

    //"logging" measures the size of the vectors from when the threshold was
    //broken to when the button was released/600 samples were taken

    myled1 = 0;
    count = 0;
    logging = 0;
}

// Outputs what line matches the most of the model files
int compare(int vec[], int size) {
    LocalFileSystem local("local");
    int counting = 0;
    int foundNum = 0;
    bool found = false;
    FILE *fpx = fopen("/local/modelX.txt", "r");  
    double scale = size/10;
    //FILE *fpy = fopen("/local/modelY.txt", "r"); 
    //FILE *fpz = fopen("/local/modelZ.txt", "r"); 
    
    // Counts to see how many characters modelX is (should be 20 per line)
    int counter = 0;
    for(int i = 0; 1; i++) {
        if(fgetc(fpx) == EOF) {
            break;
        } else {counter++;}    
    }
    
    // Moves to first line in modelX
    fseek(fpx, 0, SEEK_SET);
    
    // Allocates space for characters in models
    char *out = (char*) malloc(sizeof(char) * counter+1);
    
    // Points to a string that is stored in out
    fscanf(fpx, "%s", out);
    int i = 2;
    int scaling = 0;
    
    // Checks if line had 90% of matched points within vec[] or runs out of characters
    while (found == false || counting != counter) {
        foundNum = 0;
        
        // Checks every point in vec[]
        for (int j = 0; j < size; j++) {
            counting++;
            
            // Saves previous and current character as an integer (since i starts at 2, guarentees that will not be out of bounds)
            int newVec = atoi(out + i);
            int preVec = atoi(out + i - 2);

            // If previous point and current point are not the same then must change comparison
            double varVec = (newVec - preVec) / scale; 
            if (preVec != newVec) {
                newVec = newVec + varVec * scale;
            } 
            
            // If recorded number is 10% within ideal model number than is intended 
            float thres = newVec*.10; 
            if (vec[j] >= newVec-thres && vec[j] <= newVec+thres) { // If the point or new point is within thrusthold then adds to comparison counter
                foundNum++;
            }
            scaling++;
                
            // If reached next point 
            if (scaling >= scale) {
                i += 2;
                scaling = 0;
                
                // Goes to next line once goes through all scaled points
                // Now comparison are done on next line and for loop is renewed
                double f = fmod((double)i, 20);
                if (f == 0) {
                    // If vec[] and model vec match by 90% should return first number on line
                    if ((foundNum / size) >= 0.90) {
                        return *out;
                    } 
                    j = 0;
                    fscanf(fpx, "\n%s", out);
                }
            }
        }
    }
    return 0;
}

