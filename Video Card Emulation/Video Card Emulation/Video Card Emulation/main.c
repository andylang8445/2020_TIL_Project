//
//  main.c
//  Video Card Emulation
//
// This Program is Built by assuming the time required for processing is 0.0 Nano Second
//
//  Created by Hongjun Yun on 2020-07-14.
//  Copyright © 2020 Hongjun Yun. All rights reserved.
//

#include <stdio.h>
#include <time.h>

/*Pins on VGA Connector*/
int Pin1_Red, Pin2_Green, Pin3_Blue; //RGB Data pins
int Pin5_GND, Pin6_RGND, Pin7_GGND, Pin8_BGND, Pin10_SGND;// GND Pins for 5V, RGB, and Sync
int Pin4_RES;//Reserved Pin
int Pin9_5V_VDC;// 5V DC Power
int Pin11_ID0;// Monitor ID Bit 0 (optional)
int Pin12_SDA, Pin15_SCL;// DDC Serial Data Line and DDC Data Clock Line
int Pin13_HSync, Pin14_VSync;// Horizontal Sync and Vertical Sync

/*Constants*/
const int NotConnected=-2;
const int Grounded=-1;
const int High_5V_DC=5;
const int Low_Pin=-5;

void initialization(){
    Pin5_GND = Pin6_RGND = Pin7_GGND = Pin8_BGND = Pin10_SGND = Grounded;
    Pin4_RES = Pin11_ID0 = Pin12_SDA = NotConnected;
    Pin9_5V_VDC = High_5V_DC;
}

int PulseGenerator_10MHz(){//Need to sleep every 100 nano second
    struct timespec req = {0}, remaining = {0};
    req.tv_sec = 0;
    req.tv_nsec = 1;
    
    /*struct timespec startx, endx;
    clock_gettime(CLOCK_MONOTONIC, &startx);*/
    if(nanosleep(&req, &remaining)<0){
        printf("\n\tPulse Generator Failure\n");
        return -1;
    }
    /*clock_gettime(CLOCK_MONOTONIC, &endx);
    printf("(%d)(%d)\n",startx.tv_sec,startx.tv_nsec);
    printf("(%d)(%d)\n",endx.tv_sec,endx.tv_nsec);
    printf("\treq: (%d)(%d)\n",req.tv_sec,req.tv_nsec);
    printf("\tremaining(%d)(%d)\n",remaining.tv_sec,remaining.tv_nsec);*/
    return 0;
}

int main(int argc, const char * argv[]) {
    printf("10MHz Pulse Generator\n");
    struct timespec startx, endx;
    clock_gettime(CLOCK_MONOTONIC, &startx);
    while(1){
        for(int i=0;i<628;i++){
            if(i<600){//display period
                for(int j=0;j<264;j++){
                    PulseGenerator_10MHz();
                    if(j<200){//display period
                        
                    }
                    else if(j<210){//Front Porch
                        
                    }
                    else if(j<242){//Sync Pulse
                        
                    }
                    else{//Back Porch
                        
                    }
                }
            }
            else if(i<601){//Front Porch
                for(int j=0;j<264;j++){
                    PulseGenerator_10MHz();
                }
            }
            else if(i<605){//Sync Pulse
                for(int j=0;j<264;j++){
                    PulseGenerator_10MHz();
                }
            }
            else{//Back Porch
                for(int j=0;j<264;j++){
                    PulseGenerator_10MHz();
                }
            }
        }
    }
    return 0;
}
