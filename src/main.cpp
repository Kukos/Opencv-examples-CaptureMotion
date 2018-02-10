#include <cstdio>
#include <webcam.hpp>
#include <unistd.h>
#include <iostream>


int main(void)
{
    Webcam *webcam = new Webcam();
    webcam->start();

    /* 60s demo */
    sleep(60);
    
    webcam->end();
    delete webcam;

	return 0;
}
