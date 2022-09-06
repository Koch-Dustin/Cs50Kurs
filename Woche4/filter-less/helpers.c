#include "helpers.h"
#include <math.h>

void grayscale();
int limit();
void sepia();
void reflect();
int getBlur();
void blur();

void grayscale(int height, int width, RGBTRIPLE image[height][width]) {
    float rgbGray;

    for (int i = 0; i < height; i ++) {
        for (int j = 0; j < width; j++) {
            rgbGray = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.00);

            image[i][j].rgbtBlue = rgbGray;
            image[i][j].rgbtGreen = rgbGray;
            image[i][j].rgbtRed = rgbGray;
        }
    }

    return;
}

int limit(int RGB) {
    if (RGB > 255) {
        RGB = 255;
    }

    return RGB;
}

void sepia(int height, int width, RGBTRIPLE image[height][width]) {

    int sepiaBlue;
    int sepiaRed;
    int sepiaGreen;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            RGBTRIPLE imgTriple = image[i][j];

            sepiaBlue = limit(round(0.272 * imgTriple.rgbtRed + 0.534 * imgTriple.rgbtGreen + 0.131 * imgTriple.rgbtBlue));
            sepiaGreen = limit(round(0.349 * imgTriple.rgbtRed + 0.686 * imgTriple.rgbtGreen + 0.168 * imgTriple.rgbtBlue));
            sepiaRed = limit(round(0.393 * imgTriple.rgbtRed + 0.769 * imgTriple.rgbtGreen + 0.189 * imgTriple.rgbtBlue));

            imgTriple.rgbtBlue = sepiaBlue;
            imgTriple.rgbtGreen = sepiaGreen;
            imgTriple.rgbtRed = sepiaRed;
        }
    }

    return;
}

void reflect(int height, int width, RGBTRIPLE image[height][width]) {
    RGBTRIPLE temp;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width / 2; j++) {
            temp.rgbtBlue = image[i][j].rgbtBlue;
            temp.rgbtGreen = image[i][j].rgbtGreen;
            temp.rgbtRed = image[i][j].rgbtRed;

            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;

            image[i][width - j - 1].rgbtBlue = temp.rgbtBlue;
            image[i][width - j - 1].rgbtGreen = temp.rgbtGreen;
            image[i][width - j - 1].rgbtRed = temp.rgbtRed;

        }
    }

    return;
}

int getBlur(int i, int j, int height, int width, RGBTRIPLE image[height][width] , int color_position) {
    float counter = 0;
    int sum = 0;

    for (int k = i - 1; k <  (i + 2); k++) {
        for (int l = j - 1; l < (j + 2); l ++) {
            if(k < 0 || l < 0 || k >= height || l >= width) {
                continue;
            }
            if (color_position == 0) {
                sum += image[k][l].rgbtRed;
            }
            else if (color_position == 1) {
                sum += image[k][l].rgbtGreen;
            }
            else {
                sum += image[k][l].rgbtBlue;
            }
            counter++;
        }
    }

    return round(sum /counter);
}

void blur(int height, int width, RGBTRIPLE image[height][width]) {
    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            image[i][j].rgbtRed = getBlur(i, j, height, width, copy, 0);
            image[i][j].rgbtGreen = getBlur(i, j, height, width, copy, 1);
            image[i][j].rgbtBlue = getBlur(i, j, height, width, copy, 2);
        }
    }
    
    return;
}
