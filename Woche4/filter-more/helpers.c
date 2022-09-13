#include "helpers.h"
#include <math.h>

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

            sepiaBlue = limit(round(0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue));
            sepiaGreen = limit(round(0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue));
            sepiaRed = limit(round(0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue));

            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtRed = sepiaRed;
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
            if (k < 0 || l < 0 || k >= height || l >= width) continue;

            RGBTRIPLE imageTriple = image[k][i];

            if (color_position == 0) {
                sum += imageTriple.rgbtRed;
            } else if (color_position == 1) {
                sum += imageTriple.rgbtGreen;
            } else {
                sum += imageTriple.rgbtBlue;
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
}

void edges(int height, int width, RGBTRIPLE image[height][width]) {
    RGBTRIPLE temp[height][width];
         
    int GxR;
    int GyR;
    int GxG;
    int GyG;
    int GxB;
    int GyB;
        
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
        
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            GxR = 0;
            GyR = 0;
            GxG = 0;
            GyG = 0;
            GxB = 0;
            GyB = 0;
    
            for (int h = -1; h < 2; h++) {
                for (int w = -1; w < 2; w++) {
                    if (i + h < 0 || i + h > height - 1) continue;
                        
                    if (j + w < 0 || j + w > width - 1) continue;

                    RGBTRIPLE imageTriple = image[i + h][j + w];

                    int GxValue = Gx[h + 1][w + 1];
                    int GyValue = Gy[h + 1][w + 1];

                    GxR += imageTriple.rgbtRed * GxValue;
                    GxG += imageTriple.rgbtGreen * GxValue;
                    GxB += imageTriple.rgbtBlue * GxValue;

                    GyR += imageTriple.rgbtRed * GyValue;
                    GyG += imageTriple.rgbtGreen * GyValue;
                    GyB += imageTriple.rgbtBlue * GyValue;
                }
            }
            
            temp[i][j].rgbtRed = limit(round((GxR * GxR  + GyR * GyR)))
            temp[i][j].rgbtGreen = limit(round((GxG * GxG  + GyG * GyG)))
            temp[i][j].rgbtBlue = limit(round((GxB * GxB  + GyB * GyB)))
        }
    }       

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            image[i][j] = temp[i][j];
        }
    }
        
    return;
}
