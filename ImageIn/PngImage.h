#ifndef PNGIMAGE_H
#define PNGIMAGE_H

#include "ImageFile.h"


namespace imagein
{
    class PngImage : public ImageFile
    {
        public:
            PngImage(std::string filename) : ImageFile(filename) {}

            unsigned int readHeight();
            unsigned int readWidth();
            unsigned int readNbChannels();
            unsigned int readDepth();
            char* readData();

            void writeData(char* data, unsigned int width, unsigned int height, unsigned int nChannels, unsigned int depth);

        private:
    };
}

#endif // PNGIMAGE_H
