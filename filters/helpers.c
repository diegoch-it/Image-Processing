#include "helpers.h"
#include "math.h"

uint8_t cap(float avg);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // loop over image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            uint8_t buffer = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = buffer;
            image[i][j].rgbtGreen = buffer;
            image[i][j].rgbtRed = buffer;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            uint8_t bufferg = cap(.168 * image[i][j].rgbtBlue + .686 * image[i][j].rgbtGreen + .349 * image[i][j].rgbtRed);

            uint8_t bufferr = cap(.189 * image[i][j].rgbtBlue + .769 * image[i][j].rgbtGreen + .393 * image[i][j].rgbtRed);

            uint8_t bufferb = cap(.131 * image[i][j].rgbtBlue + .534 * image[i][j].rgbtGreen + .272 * image[i][j].rgbtRed);

            image[i][j].rgbtGreen = bufferg;
            image[i][j].rgbtRed = bufferr;
            image[i][j].rgbtBlue = bufferb;
        }
    }
    return;
}

uint8_t cap(float avg)
{
    if (avg > 255)
        return 255;
    else
        return round(avg);
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < floor(width / 2.0); j++)
        {
            RGBTRIPLE tmp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i != 0 || i != height - 1 || j != 0 || j != width - 1)
            {
                image[i][j].rgbtGreen =
                    round((copy[i][j].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i + 1][j].rgbtGreen +
                           copy[i - 1][j - 1].rgbtGreen + copy[i + 1][j - 1].rgbtGreen + copy[i - 1][j + 1].rgbtGreen +
                           copy[i + 1][j + 1].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i][j - 1].rgbtGreen) /
                          9.0);
                image[i][j].rgbtRed = round((copy[i][j].rgbtRed + copy[i - 1][j].rgbtRed + copy[i + 1][j].rgbtRed +
                                             copy[i - 1][j - 1].rgbtRed + copy[i + 1][j - 1].rgbtRed + copy[i - 1][j + 1].rgbtRed +
                                             copy[i + 1][j + 1].rgbtRed + copy[i][j + 1].rgbtRed + copy[i][j - 1].rgbtRed) /
                                            9.0);
                image[i][j].rgbtBlue =
                    round((copy[i][j].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i - 1][j - 1].rgbtBlue +
                           copy[i + 1][j - 1].rgbtBlue + copy[i - 1][j + 1].rgbtBlue + copy[i + 1][j + 1].rgbtBlue +
                           copy[i][j + 1].rgbtBlue + copy[i][j - 1].rgbtBlue) /
                          9.0);
            }
            if (i == 0 && j != 0 && j != width - 1)
            {
                image[i][j].rgbtGreen = round((copy[i][j].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen +
                                               copy[i + 1][j - 1].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i][j - 1].rgbtGreen) /
                                              6.0);
                image[i][j].rgbtRed = round((copy[i][j].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed +
                                             copy[i + 1][j - 1].rgbtRed + copy[i][j + 1].rgbtRed + copy[i][j - 1].rgbtRed) /
                                            6.0);
                image[i][j].rgbtBlue = round((copy[i][j].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue +
                                              copy[i + 1][j - 1].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i][j - 1].rgbtBlue) /
                                             6.0);
            }
            if (i == height - 1 && j != 0 && j != width - 1)
            {
                image[i][j].rgbtGreen = round((copy[i][j].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen +
                                               copy[i][j + 1].rgbtGreen + copy[i - 1][j - 1].rgbtGreen + copy[i][j - 1].rgbtGreen) /
                                              6.0);
                image[i][j].rgbtRed = round((copy[i][j].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed +
                                             copy[i][j + 1].rgbtRed + copy[i - 1][j - 1].rgbtRed + copy[i][j - 1].rgbtRed) /
                                            6.0);
                image[i][j].rgbtBlue = round((copy[i][j].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue +
                                              copy[i][j + 1].rgbtBlue + copy[i - 1][j - 1].rgbtBlue + copy[i][j - 1].rgbtBlue) /
                                             6.0);
            }
            if (j == 0 && i != 0 && i != height - 1)
            {
                image[i][j].rgbtGreen = round((copy[i][j].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen +
                                               copy[i][j + 1].rgbtGreen + copy[i + 1][j + 1].rgbtGreen + copy[i + 1][j].rgbtGreen) /
                                              6.0);
                image[i][j].rgbtRed = round((copy[i][j].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed +
                                             copy[i][j + 1].rgbtRed + copy[i + 1][j + 1].rgbtRed + copy[i + 1][j].rgbtRed) /
                                            6.0);
                image[i][j].rgbtBlue = round((copy[i][j].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue +
                                              copy[i][j + 1].rgbtBlue + copy[i + 1][j + 1].rgbtBlue + copy[i + 1][j].rgbtBlue) /
                                             6.0);
            }
            if (j == width - 1 && i != 0 && i != height - 1)
            {
                image[i][j].rgbtGreen = round((copy[i][j].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j - 1].rgbtGreen +
                                               copy[i][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j - 1].rgbtGreen) /
                                              6.0);
                image[i][j].rgbtRed = round((copy[i][j].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j - 1].rgbtRed +
                                             copy[i][j - 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j - 1].rgbtRed) /
                                            6.0);
                image[i][j].rgbtBlue = round((copy[i][j].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j - 1].rgbtBlue +
                                              copy[i][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j - 1].rgbtBlue) /
                                             6.0);
            }
            if (i == 0 && j == 0)
            {
                image[i][j].rgbtGreen = round(
                    (copy[i][j].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen + copy[i][j + 1].rgbtGreen) /
                    4.0);
                image[i][j].rgbtRed = round(
                    (copy[i][j].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed + copy[i][j + 1].rgbtRed) / 4.0);
                image[i][j].rgbtBlue = round(
                    (copy[i][j].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue + copy[i][j + 1].rgbtBlue) / 4.0);
            }
            if (i == height - 1 && j == 0)
            {
                image[i][j].rgbtGreen = round(
                    (copy[i][j].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen + copy[i][j + 1].rgbtGreen) /
                    4.0);
                image[i][j].rgbtRed = round(
                    (copy[i][j].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed + copy[i][j + 1].rgbtRed) / 4.0);
                image[i][j].rgbtBlue = round(
                    (copy[i][j].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue + copy[i][j + 1].rgbtBlue) / 4.0);
            }
            if (i == 0 && j == width - 1)
            {
                image[i][j].rgbtGreen = round(
                    (copy[i][j].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j - 1].rgbtGreen + copy[i][j - 1].rgbtGreen) /
                    4.0);
                image[i][j].rgbtRed = round(
                    (copy[i][j].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j - 1].rgbtRed + copy[i][j - 1].rgbtRed) / 4.0);
                image[i][j].rgbtBlue = round(
                    (copy[i][j].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j - 1].rgbtBlue + copy[i][j - 1].rgbtBlue) / 4.0);
            }
            if (i == height - 1 && j == width - 1)
            {
                image[i][j].rgbtGreen = round(
                    (copy[i][j].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j - 1].rgbtGreen + copy[i][j - 1].rgbtGreen) /
                    4.0);
                image[i][j].rgbtRed = round(
                    (copy[i][j].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j - 1].rgbtRed + copy[i][j - 1].rgbtRed) / 4.0);
                image[i][j].rgbtBlue = round(
                    (copy[i][j].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j - 1].rgbtBlue + copy[i][j - 1].rgbtBlue) / 4.0);
            }
        }
    }
    return;
}