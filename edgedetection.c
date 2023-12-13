#include <stdio.h>
#include <stdlib.h>

#define WIDTH 256
#define HEIGHT 256

int main() {
    FILE *inputFile, *outputFile;
    unsigned char inputImage[WIDTH][HEIGHT], outputImage[WIDTH][HEIGHT];
    int i, j;

    inputFile = fopen("C:\Users\Administrator\Desktop\c project\img.raw", "rb");
    if (!inputFile) {
        printf("Error opening input image file.\n");
        return -1;
    }

    fread(inputImage, sizeof(unsigned char), WIDTH * HEIGHT, inputFile);
    fclose(inputFile);

    // Edge detection algorithm (e.g., using simple gradient operators)

    // Example: Sobel operator for gradient computation
    int sobel_x[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int sobel_y[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (i = 1; i < WIDTH - 1; i++) {
        for (j = 1; j < HEIGHT - 1; j++) {
            int gx = 0, gy = 0;

            for (int k = -1; k <= 1; k++) {
                for (int l = -1; l <= 1; l++) {
                    gx += inputImage[i + k][j + l] * sobel_x[k + 1][l + 1];
                    gy += inputImage[i + k][j + l] * sobel_y[k + 1][l + 1];
                }
            }

            outputImage[i][j] = (unsigned char)(sqrt(gx * gx + gy * gy));
        }
    }

    outputFile = fopen("output_edge.raw", "wb");
    if (!outputFile) {
        printf("Error opening output image file.\n");
        return -1;
    }

    fwrite(outputImage, sizeof(unsigned char), WIDTH * HEIGHT, outputFile);
    fclose(outputFile);

    return 0;
}
