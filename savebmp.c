#include <stdio.h>

const int bytesPerPixel = 3; /// red, green, blue
const int fileHeaderSize = 14;
const int infoHeaderSize = 40;

void generateBitmapImage(unsigned char *image, int height, int width, char *imageFileName);
unsigned char *createBitmapFileHeader(int height, int width, int paddingSize);
unsigned char *createBitmapInfoHeader(int height, int width);

int main()
{
    int height = 341;
    int width = 753;
    unsigned char image[height][width][bytesPerPixel];
    char *imageFileName = "bitmapImage.bmp";

    int i, j;
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            image[i][j][2] = (unsigned char)((double)i / height * 255);                 ///red
            image[i][j][1] = (unsigned char)((double)j / width * 255);                  ///green
            image[i][j][0] = (unsigned char)(((double)i + j) / (height + width) * 255); ///blue
        }
    }

    generateBitmapImage((unsigned char *)image, height, width, imageFileName);
    printf("Image generated!!");
}

void generateBitmapImage(unsigned char *image, int height, int width, char *imageFileName)
{

    unsigned char padding[3] = {0, 0, 0};
    int paddingSize = (4 - (width * bytesPerPixel) % 4) % 4;

    unsigned char *fileHeader = createBitmapFileHeader(height, width, paddingSize);
    unsigned char *infoHeader = createBitmapInfoHeader(height, width);

    FILE *imageFile = fopen(imageFileName, "wb");

    fwrite(fileHeader, 1, fileHeaderSize, imageFile);
    fwrite(infoHeader, 1, infoHeaderSize, imageFile);

    int i;
    for (i = 0; i < height; i++)
    {
        fwrite(image + (i * width * bytesPerPixel), bytesPerPixel, width, imageFile);
        fwrite(padding, 1, paddingSize, imageFile);
    }

    fclose(imageFile);
}

unsigned char *createBitmapFileHeader(int height, int width, int paddingSize)
{
    int fileSize = fileHeaderSize + infoHeaderSize + (bytesPerPixel * width + paddingSize) * height;

    static unsigned char fileHeader[11];

    fileHeader[0] = (unsigned char)('B');
    fileHeader[1] = (unsigned char)('M');
    fileHeader[2] = (unsigned char)(fileSize);
    fileHeader[3] = (unsigned char)(fileSize >> 8);
    fileHeader[4] = (unsigned char)(fileSize >> 16);
    fileHeader[5] = (unsigned char)(fileSize >> 24);
    fileHeader[10] = (unsigned char)(fileHeaderSize + infoHeaderSize);

    return fileHeader;
}

unsigned char *createBitmapInfoHeader(int height, int width)
{
    static unsigned char infoHeader[15];

    infoHeader[0] = (unsigned char)(infoHeaderSize);
    infoHeader[4] = (unsigned char)(width);
    infoHeader[5] = (unsigned char)(width >> 8);
    infoHeader[6] = (unsigned char)(width >> 16);
    infoHeader[7] = (unsigned char)(width >> 24);
    infoHeader[8] = (unsigned char)(height);
    infoHeader[9] = (unsigned char)(height >> 8);
    infoHeader[10] = (unsigned char)(height >> 16);
    infoHeader[11] = (unsigned char)(height >> 24);
    infoHeader[12] = (unsigned char)(1);
    infoHeader[14] = (unsigned char)(bytesPerPixel * 8);

    return infoHeader;
}