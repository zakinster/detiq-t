#include <iostream>
#include <cmath>

#include "Image.h"

using namespace imagein;
using namespace std;

int main(int argc, char* argv[])
{
    /*
     * Test I/O jpg, bmp, png
     */
    
    //reference data
    int width = 512;
    int height = 255;
    int nbChannels = 3;
    unsigned char* dataRgb = new unsigned char[width * height * nbChannels];

    for(int j = 0 ; j < height ; ++j) {
        for(int i = 0 ; i < width ; ++i) { 
            unsigned char red = 255 - i;
            if(red < 0) red = 0;
            unsigned char green = 255 - abs(256-i);
            if(green < 0) green = 0;
            unsigned char blue = 255 - abs(512-i);
            if(blue < 0) blue = 0;
            
            dataRgb[j*width*nbChannels + i*nbChannels] = red;
            dataRgb[j*width*nbChannels + i*nbChannels + 1] = green;
            dataRgb[j*width*nbChannels + i*nbChannels + 2] = blue;
        }
    }
    Image ref(width, height, nbChannels, dataRgb);
    
    Image::const_iterator b1, b2, e1, e2;
    int nTest = 0, nFail = 0;
        
    cout << "Testing ImageFile I/O functions..." << endl;

    {//reading

        //Testing bmp reading
        nTest++;
        Image bmpTest("test/ref_image.bmp");
        
        b1 = ref.begin(); b2 = bmpTest.begin(); e1 = ref.end(); e2 = bmpTest.end();

        if(
                std::equal(b1, e1, b2) //Matrices are equals
             && (e2-b2 == e1-b1) //Matrices are same size
             && ref.getWidth() == bmpTest.getWidth() //Class attributes are equals
             && ref.getHeight() == bmpTest.getHeight()
             && ref.getNbChannels() == bmpTest.getNbChannels()
          ) {
            cout << "[OK]   bmp reading" << endl;
        }
        else {
            cerr << "[FAIL] bmp reading" << endl;
            nFail++;
        }

        //Testing png reading
        nTest++;
        Image pngTest("test/ref_image.png");
        
        b1 = ref.begin(); b2 = pngTest.begin(); e1 = ref.end(); e2 = pngTest.end();

        if(
                std::equal(b1, e1, b2) //Matrices are equals
             && (e2-b2 == e1-b1) //Matrices are same size
             && ref.getWidth() == pngTest.getWidth() //Class attributes are equals
             && ref.getHeight() == pngTest.getHeight()
             && ref.getNbChannels() == pngTest.getNbChannels()
          ) {
            cout << "[OK]   png reading" << endl;
        }
        else {
            cerr << "[FAIL] png reading" << endl;
            nFail++;
        }

    }

    {//writing

        //Testing bmp writing
        nTest++;
        ref.save("test/temp/test_bmp.bmp");
        Image bmpTest("test/temp/test_bmp.bmp");
        
        b1 = ref.begin(); b2 = bmpTest.begin(); e1 = ref.end(); e2 = bmpTest.end();

        if(
                std::equal(b1, e1, b2) //Matrices are equals
             && (e2-b2 == e1-b1) //Matrices are same size
             && ref.getWidth() == bmpTest.getWidth() //Class attributes are equals
             && ref.getHeight() == bmpTest.getHeight()
             && ref.getNbChannels() == bmpTest.getNbChannels()
          ) {
            cout << "[OK]   bmp writing" << endl;
        }
        else {
            cerr << "[FAIL] bmp writing" << endl;
            nFail++;
        }

        //Testing png writing
        nTest++;
        ref.save("test/temp/test_png.png");
        Image pngTest("test/temp/test_png.png");
        
        b1 = ref.begin(); b2 = pngTest.begin(); e1 = ref.end(); e2 = pngTest.end();

        if(
                std::equal(b1, e1, b2) //Matrices are equals
             && (e2-b2 == e1-b1) //Matrices are same size
             && ref.getWidth() == pngTest.getWidth() //Class attributes are equals
             && ref.getHeight() == pngTest.getHeight()
             && ref.getNbChannels() == pngTest.getNbChannels()
          ) {
            cout << "[OK]   png writing" << endl;
        }
        else {
            cerr << "[FAIL] png writing" << endl;
            nFail++;
        }

    }

    {//copy ctor

        //Testing copy constructor
        nTest++;
        
        Image test(ref);
        
        b1 = ref.begin(); b2 = test.begin(); e1 = ref.end(); e2 = test.end();

        if(
                std::equal(b1, e1, b2) //Matrices are equals
             && (e2-b2 == e1-b1) //Matrices are same size
             && ref.getWidth() == test.getWidth() //Class attributes are equals
             && ref.getHeight() == test.getHeight()
             && ref.getNbChannels() == test.getNbChannels()
          ) {
            cout << "[OK]   copy constructor" << endl;
        }
        else {
            cerr << "[FAIL] copy constructor" << endl;
            nFail++;
        }
    }
   
    { //crop

        //testing crop
        nTest++;
    
        //crop reference data
        int width = 128;
        int height = 128;
        int nbChannels = 3;
        unsigned char* dataCrop = new unsigned char[width * height * nbChannels];

        for(int j = 0 ; j < height ; ++j) {
            for(int i = 0 ; i < width ; ++i) { 
              
                unsigned char red, green, blue;

                if(     ((j == 27 || j == 100) && i > 3 && i < 42)
                    ||  ((i == 4 || i == 41) && j < 26 && j < 101)
                  ) {
                    
                    red = 1;
                    green = 2;
                    blue = 3;

                }
                else {
                    red = 255;
                    green = 255;
                    blue = 255;
                }

                dataCrop[j*width*nbChannels + i*nbChannels] = red;
                dataCrop[j*width*nbChannels + i*nbChannels + 1] = green;
                dataCrop[j*width*nbChannels + i*nbChannels + 2] = blue;
            }
        }

        //after crop reference data
        int cropWidth = 38;
        int cropHeight = 74;
        unsigned char* dataAfter = new unsigned char[cropWidth * cropHeight * nbChannels];

        for(int j = 0 ; j < cropHeight ; ++j) {
            for(int i = 0 ; i < cropWidth ; ++i) {
                
                unsigned char red, green, blue;
                
                if(i == 0 || i == cropWidth-1 || j == 0 || j == cropHeight) {
                    red = 1;
                    green = 2;
                    blue = 3;
                }
                else {
                    red = 255;
                    green = 255;
                    blue = 255;
                }
                dataAfter[j*width*nbChannels + i*nbChannels] = red;
                dataAfter[j*width*nbChannels + i*nbChannels + 1] = green;
                dataAfter[j*width*nbChannels + i*nbChannels + 2] = blue;
            }
        }

        Image in(width, height, nbChannels, dataCrop);
        Image *refCrop = in.crop(Rectangle(4, 27, 38, 74));
        Image testCrop(cropWidth, cropHeight, nbChannels, dataAfter);
        
        b1 = refCrop->begin(); b2 = testCrop.begin(); e1 = refCrop->end(); e2 = testCrop.end();

        if(
                std::equal(b1, e1, b2) //Matrices are equals
             && (e2-b2 == e1-b1) //Matrices are same size
             && refCrop->getWidth() == testCrop.getWidth() //Class attributes are equals
             && refCrop->getHeight() == testCrop.getHeight()
             && refCrop->getNbChannels() == testCrop.getNbChannels()
          ) {
            cout << "[OK]   crop" << endl;
        }
        else {
            cerr << "[FAIL] crop" << endl;
            nFail++;
        }
    }
}
