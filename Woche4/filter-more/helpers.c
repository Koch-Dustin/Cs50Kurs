#include "helpers.h"

void grayscale(int height, int width, RGBTRIPLE image[height][width]) {
    float rgbGray;

    for(int i = 0; i < height; i ++) {
        for(int j = 0; j < width; j++) {
            rgbGray = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.00);

            image[i][j].rgbtBlue = rgbGray;
            image[i][j].rgbtGreen = rgbGray;
            image[i][j].rgbtRed = rgbGray;

        }
    }

    return;
}

int limit(int RGB) {
    if(RGB > 255) {
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
    int temp[3];

    for (int i = 0; i < height; i++) {
        for(int j = 0; j < width / 2; j++) {
            temp[0] = image[i][j].rgbtBlue;
            temp[1] = image[i][j].rgbtGreen;
            temp[2] = image[i][j].rgbtRed;

            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;

            image[i][width - j - 1].rgbtBlue = temp[0];
            image[i][width - j - 1].rgbtGreen = temp[1];
            image[i][width - j - 1].rgbtRed = temp[2];

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
}

void edges(int height, int width, RGBTRIPLE image[height][width]) {
    RGBTRIPLE temp[height][width];
         
    int GxR, GyR, GxG, GyG, GxB, GyB;
        
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
        
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            GxR = GyR = GxG = GyG = GxB = GyB= 0;
    
            for (int h = -1; h < 2; h++) {
                for (int w = -1; w < 2; w++) {
                    if (i + h < 0 || i + h > height - 1) {
                        continue;
                    }
                        
                    if (j + w < 0 || j + w > width - 1) {
                        continue;
                    }

                    GxR += image[i + h][j + w].rgbtRed * Gx[h + 1][w + 1];
                    GxG += image[i + h][j + w].rgbtGreen * Gx[h + 1][w + 1];
                    GxB += image[i + h][j + w].rgbtBlue * Gx[h + 1][w + 1];

                    GyR += image[i + h][j + w].rgbtRed * Gy[h + 1][w + 1];
                    GyG += image[i + h][j + w].rgbtGreen * Gy[h + 1][w + 1];
                    GyB += image[i + h][j + w].rgbtBlue * Gy[h + 1][w + 1];
                }
            }
                
            temp[i][j].rgbtRed = round(sqrt((GxR * GxR  + GyR * GyR)));
            temp[i][j].rgbtGreen = round(sqrt((GxG * GxG + GyG * GyG)));
            temp[i][j].rgbtBlue = round(sqrt((GxB * GxB + GyB * GyB)));
                
            if (temp[i][j].rgbtRed > 255) {
                temp[i][j].rgbtRed = 255;
            }
                
            if (temp[i][j].rgbtGreen > 255) {
                temp[i][j].rgbtGreen = 255;
            }
                
            if (temp[i][j].rgbtBlue > 255) {
                temp[i][j].rgbtBlue = 255;
            }
        }
    }       

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            image[i][j] = temp[i][j];
        }
    }
        
    return;
}
