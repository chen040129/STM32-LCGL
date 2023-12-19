/*
//
// Created by csy on 2023/7/7 0007.
//

#include "FFT.h"

//传进来的FFT_TXNum的长度应是FFT_Num_buf的两倍，
//FFT_TXNum第一位是实数部分，第二位是虚数部分，以此类推

void FFT_Relnum(uint16_t *FFT_RxNum_buf,unsigned int *FFT_Num,uint16_t fftlen){
    float32_t FFT_TXNum[2*fftlen];
    float32_t FFT_Num_buf[fftlen];



    for (int i = 0; i < fftlen; ++i) {
        FFT_TXNum[2*i]=FFT_RxNum_buf[i]*3.3/4069;
        FFT_TXNum[2*i+1]=0;
    }

    arm_rfft_instance_f32 fft_set;
    arm_rfft_fast_init_f32(&fft_set,fftlen);
    arm_rfft_fast_f32(&fft_set,FFT_TXNum,FFT_Num_buf,0);


    for (int i = 0; i < fftlen; ++i) {
        FFT_Num[i]=FFT_Num_buf[i];
    }
};

*/
