// Project2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

//Structs
struct Pixel
{
    unsigned char blue;
    unsigned char green;
    unsigned char red;
};
struct Header
{
    char idLength;
    char colorMapType;
    char dataTypeCode;
    short colorMapOrigin;
    short colorMapLength;
    char colorMapDepth;
    short xOrigin;
    short yOrigin;
    short width;
    short height;
    char bitsPerPixel;
    char imageDescriptor;
};

//Functions to Read and Write 
void Read(string fileName, Header& headerObject,vector<Pixel>& p)
{
    //Open file
    ifstream inFile;
    inFile.open(fileName, ios_base::binary);

    
    //Read Data
    inFile.read(&headerObject.idLength, sizeof(headerObject.idLength));
    inFile.read(&headerObject.colorMapType, sizeof(headerObject.colorMapType));
    inFile.read(&headerObject.dataTypeCode, sizeof(headerObject.dataTypeCode));
    inFile.read((char*)&headerObject.colorMapOrigin, sizeof(headerObject.colorMapOrigin));
    inFile.read((char*)&headerObject.colorMapLength, sizeof(headerObject.colorMapLength));
    inFile.read(&headerObject.colorMapDepth, sizeof(headerObject.colorMapDepth));
    inFile.read((char*)&headerObject.xOrigin, sizeof(headerObject.xOrigin));
    inFile.read((char*)&headerObject.yOrigin, sizeof(headerObject.yOrigin));
    inFile.read((char*)&headerObject.width, sizeof(headerObject.width));
    inFile.read((char*)&headerObject.height, sizeof(headerObject.height));
    inFile.read(&headerObject.bitsPerPixel, sizeof(headerObject.bitsPerPixel));
    inFile.read(&headerObject.imageDescriptor, sizeof(headerObject.imageDescriptor));

    int imageSize = headerObject.width * headerObject.height;

    
    //Save pixels in vector
    for (unsigned int i = 0; i < imageSize; i++)
    {
        Pixel pixel;

        inFile.read((char*)&pixel.blue, sizeof(pixel.blue));
        inFile.read((char*)&pixel.green, sizeof(pixel.green));
        inFile.read((char*)&pixel.red, sizeof(pixel.red));

        p.push_back(pixel);
    }
}
void Write(string fileName, Header& headerObject, vector<Pixel>& p)
{
    //open file
    ofstream test(fileName, ios_base::binary);

    //write data to another file
    test.write(&headerObject.idLength, sizeof(headerObject.idLength));
    test.write(&headerObject.colorMapType, sizeof(headerObject.colorMapType));
    test.write(&headerObject.dataTypeCode, sizeof(headerObject.dataTypeCode));
    test.write((char*)&headerObject.colorMapOrigin, sizeof(headerObject.colorMapOrigin));
    test.write((char*)&headerObject.colorMapLength, sizeof(headerObject.colorMapLength));
    test.write(&headerObject.colorMapDepth, sizeof(headerObject.colorMapDepth));
    test.write((char*)&headerObject.xOrigin, sizeof(headerObject.xOrigin));
    test.write((char*)&headerObject.yOrigin, sizeof(headerObject.yOrigin));
    test.write((char*)&headerObject.width, sizeof(headerObject.width));
    test.write((char*)&headerObject.height, sizeof(headerObject.height));
    test.write(&headerObject.bitsPerPixel, sizeof(headerObject.bitsPerPixel));
    test.write(&headerObject.imageDescriptor, sizeof(headerObject.imageDescriptor));

    //write pixels to another file
    for (unsigned int i = 0; i < p.size(); i++)
    {
        test.write((char*)&p[i].blue, sizeof(p[i].blue));
        test.write((char*)&p[i].green, sizeof(p[i].green));
        test.write((char*)&p[i].red, sizeof(p[i].red));
    }
}

//Image Manipulations
void Multiply(vector<Pixel>& p, vector<Pixel>& p2, vector<Pixel>& newP)
{
    for (int i = 0; i < p2.size(); i++)
    {
        Pixel pixel;

        float firstBlue, secondBlue, newBlue;
        float firstGreen, secondGreen, newGreen;
        float firstRed, secondRed, newRed;
        int temp;

        //Multiply blue pixels together and save them
        firstBlue = (float)p[i].blue / 255;
        secondBlue = (float)p2[i].blue / 255;
        newBlue = (firstBlue * secondBlue) * 255;
        temp = (int)(newBlue + 0.5f);

        pixel.blue = (unsigned char)temp;

        //Multiply green pixels together and save them
        firstGreen = (float)p[i].green / 255;
        secondGreen = (float)p2[i].green / 255;
        newGreen = (firstGreen * secondGreen) * 255;
        temp = (int)(newGreen + 0.5f);

        pixel.green = (unsigned char)temp;

        //Multiply red pixels together and save them
        firstRed = (float)p[i].red / 255;
        secondRed = (float)p2[i].red / 255;
        newRed = (firstRed * secondRed) * 255;
        temp = (int)(newRed + 0.5f);

        pixel.red = (unsigned char)temp;

        //push back onto new vector
        newP.push_back(pixel);
    }
}
void Subtract(vector<Pixel>& p, vector<Pixel>& p2, vector<Pixel>& newP)
{
    for (int i = 0; i < p2.size(); i++)
    {
        Pixel pixel;

        float firstBlue, secondBlue, newBlue;
        float firstGreen, secondGreen, newGreen;
        float firstRed, secondRed, newRed;
        int temp;

        //Subtract blue pixels from each other and save them
        firstBlue = (float)p[i].blue;
        secondBlue = (float)p2[i].blue;
        newBlue = (firstBlue - secondBlue);
        temp = (int)(newBlue);

        //check for overflow
        if (temp < 0)
        {
            temp = 0;
        }
        else if (temp > 255)
        {
            temp = 255;
        }

        pixel.blue = (unsigned char)temp;

        //Subtract green pixels from each other and save them
        firstGreen = (float)p[i].green;
        secondGreen = (float)p2[i].green;
        newGreen = (firstGreen - secondGreen);
        temp = (int)(newGreen);

        //check for overflow
        if (temp < 0)
        {
            temp = 0;
        }
        else if (temp > 255)
        {
            temp = 255;
        }

        pixel.green = (unsigned char)temp;

        //Subtract red pixels from each other and save them
        firstRed = (float)p[i].red;
        secondRed = (float)p2[i].red;
        newRed = (firstRed - secondRed);
        temp = (int)(newRed);

        //check for overflow
        if (temp < 0)
        {
            temp = 0;
        }
        else if (temp > 255)
        {
            temp = 255;
        }

        pixel.red = (unsigned char)temp;

        //push back on new vector
        newP.push_back(pixel);
    }
}
void Overlay(vector<Pixel>& p, vector<Pixel>& p2, vector<Pixel>& newP)
{
    for (int i = 0; i < p2.size(); i++)
    {
        Pixel pixel;

        float firstBlue, secondBlue, newBlue;
        float firstGreen, secondGreen, newGreen;
        float firstRed, secondRed, newRed;
        int temp;


        //Check if blue pixel from second file is <= 0.5 to determine what to save in the new vector
        secondBlue = (float)p2[i].blue / 255;
        if (secondBlue <= 0.5)
        {
            firstBlue = (float)p[i].blue / 255;
            secondBlue = (float)p2[i].blue / 255;
            newBlue = (2 * firstBlue * secondBlue) * 255;
            temp = (int)(newBlue + 0.5f);
        }
        else
        {
            firstBlue = 1 - ((float)p[i].blue / 255);
            secondBlue = 1 - ((float)p2[i].blue / 255);
            newBlue = (1 - 2 * (firstBlue * secondBlue)) * 255;
            temp = (int)(newBlue + 0.5f);
        }

        pixel.blue = (unsigned char)temp;

        //Check if green pixel from second file is <= 0.5 to determine what to save in the new vector
        secondGreen = (float)p2[i].green / 255;
        if (secondGreen <= 0.5)
        {
            firstGreen = (float)p[i].green / 255;
            secondGreen = (float)p2[i].green / 255;
            newGreen = (2 * firstGreen * secondGreen) * 255;
            temp = (int)(newGreen + 0.5f);
        }
        else
        {
            firstGreen = 1 - ((float)p[i].green) / 255;
            secondGreen = 1 - ((float)p2[i].green) / 255;
            newGreen = (1 - 2 * (firstGreen * secondGreen)) * 255;
            temp = (int)(newGreen + 0.5f);
        }

        pixel.green = (unsigned char)temp;

        //Check if red pixel from second file is <= 0.5 to determine what to save in the new vector
        secondRed = (float)p2[i].red / 255;
        if (secondRed <= 0.5)
        {
            firstRed = (float)p[i].red / 255;
            secondRed = (float)p2[i].red / 255;
            newRed = (2 * firstRed * secondRed) * 255;
            temp = (int)(newRed + 0.5f);
        }
        else
        {
            firstRed = 1 - ((float)p[i].red) / 255;
            secondRed = 1 - ((float)p2[i].red) / 255;
            newRed = (1 - 2 * (firstRed * secondRed)) * 255;
            temp = (int)(newRed + 0.5f);
        }

        pixel.red = (unsigned char)temp;

        //puch back on new vector
        newP.push_back(pixel);
    }
}
void Screen(vector<Pixel>& p, vector<Pixel>& p2, vector<Pixel>& newP)
{
    for (int i = 0; i < p2.size(); i++)
    {
        Pixel pixel;

        float firstBlue, secondBlue, newBlue;
        float firstGreen, secondGreen, newGreen;
        float firstRed, secondRed, newRed;
        int temp;

        //Similar to multiplication function, except slight change in calculations

        firstBlue = 1 - ((float)p[i].blue / 255);
        secondBlue = 1 - ((float)p2[i].blue / 255);
        newBlue = (1 - (firstBlue * secondBlue)) * 255;
        temp = (int)(newBlue + 0.5f);

        pixel.blue = (unsigned char)temp;

        firstGreen = 1 - ((float)p[i].green) / 255;
        secondGreen = 1 - ((float)p2[i].green) / 255;
        newGreen = (1 - (firstGreen * secondGreen)) * 255;
        temp = (int)(newGreen + 0.5f);

        pixel.green = (unsigned char)temp;

        firstRed = 1 - ((float)p[i].red) / 255;
        secondRed = 1 - ((float)p2[i].red) / 255;
        newRed = (1 - (firstRed * secondRed)) * 255;
        temp = (int)(newRed + 0.5f);

        pixel.red = (unsigned char)temp;

        newP.push_back(pixel);
    }
}

//Test Function
bool Test(string fileName, string exampleFile)
{
    //Tests if file created is exactly the same as example file
    Header headerObject;
    vector<Pixel> p;
    Read(fileName, headerObject, p);

    Header headerObject2;
    vector<Pixel> p2;
    Read(exampleFile, headerObject2, p2);

    if (headerObject.idLength == headerObject2.idLength) 
    {
        if (headerObject.colorMapType == headerObject2.colorMapType)
        {
            if (headerObject.dataTypeCode == headerObject2.dataTypeCode)
            {
                if (headerObject.colorMapOrigin == headerObject2.colorMapOrigin)
                {
                    if (headerObject.colorMapLength == headerObject2.colorMapLength)
                    {
                        if (headerObject.colorMapDepth == headerObject2.colorMapDepth)
                        {
                            if (headerObject.xOrigin == headerObject2.xOrigin)
                            {
                                if (headerObject.yOrigin == headerObject2.yOrigin)
                                {
                                    if (headerObject.width == headerObject2.width)
                                    {
                                        if (headerObject.height == headerObject2.height)
                                        {
                                            if (headerObject.bitsPerPixel == headerObject2.bitsPerPixel)
                                            {
                                                if (headerObject.imageDescriptor == headerObject2.imageDescriptor)
                                                {
                                                    for (int i = 0; i < p.size(); i++)
                                                    {
                                                        if ((p[i].blue == p2[i].blue) && (p[i].green == p2[i].green) && (p[i].red == p2[i].red)) {
                                                            continue;
                                                        }
                                                        else
                                                        {
                                                            return false;
                                                            break;
                                                        }
                                                    }
                                                    return true;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}

//Part 1 - 10 Cases
void PartOne()
{
    //Part 1

    Header headerObject;
    vector<Pixel> p;
    Read("input/layer1.tga", headerObject, p);

    vector<Pixel> p2;
    Read("input/pattern1.tga", headerObject, p2);

    vector<Pixel> newP;

    Multiply(p, p2, newP);

    Write("output/part1.tga", headerObject, newP);


    if (Test("output/part1.tga", "examples/EXAMPLE_part1.tga"))
    {
        cout << "Test #1...... Passed!" << endl;
    }
    else
    {
        cout << "Test #1...... Failed!" << endl;
    }
}
void PartTwo()
{
    Header headerObject;

    vector<Pixel> p;
    Read("input/car.tga", headerObject, p);

    vector<Pixel> p2;
    Read("input/layer2.tga", headerObject, p2);

    vector<Pixel> newP;

    Subtract(p, p2, newP);

    Write("output/part2.tga", headerObject, newP);

    if (Test("output/part2.tga", "examples/EXAMPLE_part2.tga"))
    {
        cout << "Test #2...... Passed!" << endl;
    }
    else
    {
        cout << "Test #2...... Failed!" << endl;
    }

}
void PartThree()
{
    Header headerObject;
    vector<Pixel> p;
    Read("input/layer1.tga", headerObject, p);

    vector<Pixel> p2;
    Read("input/pattern2.tga", headerObject, p2);

    vector<Pixel> newP;

    Multiply(p, p2, newP);

    /////////////////////////////////////////////////////////

    vector<Pixel> p3;
    Read("input/text.tga", headerObject, p3);

    vector<Pixel> partThree;

    Screen(p3, newP, partThree);

    Write("output/part3.tga", headerObject, partThree);

    if (Test("output/part3.tga", "examples/EXAMPLE_part3.tga"))
    {
        cout << "Test #3...... Passed!" << endl;
    }
    else
    {
        cout << "Test #3...... Failed!" << endl;
    }
}
void PartFour()
{
    Header headerObject;
    vector<Pixel> p;
    Read("input/layer2.tga", headerObject, p);

    vector<Pixel> p2;
    Read("input/circles.tga", headerObject, p2);

    vector<Pixel> newP;

    Multiply(p, p2, newP);

    vector<Pixel> p3;
    Read("input/pattern2.tga", headerObject, p3);

    vector<Pixel> pResult;
    Subtract(newP, p3, pResult);

    Write("output/part4.tga", headerObject, pResult);

    if (Test("output/part4.tga", "examples/EXAMPLE_part4.tga"))
    {
        cout << "Test #4...... Passed!" << endl;
    }
    else
    {
        cout << "Test #4...... Failed!" << endl;
    }
}
void PartFive()
{
    Header headerObject;
    vector<Pixel> p;
    Read("input/layer1.tga", headerObject, p);

    vector<Pixel> p2;
    Read("input/pattern1.tga", headerObject, p2);

    vector<Pixel> newP;

    Overlay(p, p2, newP);

    Write("output/part5.tga", headerObject, newP);

    if (Test("output/part5.tga", "examples/EXAMPLE_part5.tga"))
    {
        cout << "Test #5...... Passed!" << endl;
    }
    else
    {
        cout << "Test #5...... Failed!" << endl;
    }
}
void PartSix()
{
    Header headerObject;
    vector<Pixel> p;
    Read("input/car.tga", headerObject, p);

    vector<Pixel> newP;

    for (int i = 0; i < p.size(); i++)
    {
        Pixel pixel;

        float firstGreen;

        pixel.blue = p[i].blue;

        firstGreen = ((float)p[i].green) + 200;
        if (firstGreen > 255)
        {
            firstGreen = 255;
        }

        pixel.green = (unsigned char)firstGreen;


        pixel.red = p[i].red;

        newP.push_back(pixel);
    }

    Write("output/part6.tga", headerObject, newP);

    if (Test("output/part6.tga", "examples/EXAMPLE_part6.tga"))
    {
        cout << "Test #6...... Passed!" << endl;
    }
    else
    {
        cout << "Test #6...... Failed!" << endl;
    }
}
void PartSeven()
{
    Header headerObject;
    vector<Pixel> p;
    Read("input/car.tga", headerObject, p);

    vector<Pixel> newP;

    for (int i = 0; i < p.size(); i++)
    {
        Pixel pixel;

        float firstBlue, secondBlue, newBlue;
        //float firstGreen, secondGreen, newGreen;
        float firstRed, secondRed, newRed;
        int temp;

        firstBlue = ((float)p[i].blue);
        newBlue = (firstBlue * 0);
        temp = (int)(newBlue);

        pixel.blue = (unsigned char)temp;

        pixel.green = p[i].green;

        firstRed = (float)p[i].red;
        newRed = (firstRed * 4);
        temp = (int)(newRed + 0.5f);

        if (temp > 255)
        {
            temp = 255;
        }

        pixel.red = (unsigned char)temp;


        newP.push_back(pixel);
    }

    Write("output/part7.tga", headerObject, newP);

    if (Test("output/part7.tga", "examples/EXAMPLE_part7.tga"))
    {
        cout << "Test #7...... Passed!" << endl;
    }
    else
    {
        cout << "Test #7...... Failed!" << endl;
    }
}
void PartEightBLue()
{
    Header headerObject;
    vector<Pixel> p;
    Read("input/car.tga", headerObject, p);

    vector<Pixel> newP;

    for (int i = 0; i < p.size(); i++)
    {
        Pixel pixel;

        pixel.blue = p[i].blue;

        pixel.green = p[i].blue;

        pixel.red = p[i].blue;

        newP.push_back(pixel);
    }

    Write("output/part8_b.tga", headerObject, newP);

    if (Test("output/part8_b.tga", "examples/EXAMPLE_part8_b.tga"))
    {
        cout << "Test #8b...... Passed!" << endl;
    }
    else
    {
        cout << "Test #8b...... Failed!" << endl;
    }
}
void PartEightGreen()
{
    Header headerObject;
    vector<Pixel> p;
    Read("input/car.tga", headerObject, p);

    vector<Pixel> newP;

    for (int i = 0; i < p.size(); i++)
    {
        Pixel pixel;

        pixel.blue = p[i].green;

        pixel.green = p[i].green;

        pixel.red = p[i].green;

        newP.push_back(pixel);
    }

    Write("output/part8_g.tga", headerObject, newP);

    if (Test("output/part8_g.tga", "examples/EXAMPLE_part8_g.tga"))
    {
        cout << "Test #8g...... Passed!" << endl;
    }
    else
    {
        cout << "Test #8g...... Failed!" << endl;
    }
}
void PartEightRed()
{
    Header headerObject;
    vector<Pixel> p;
    Read("input/car.tga", headerObject, p);

    vector<Pixel> newP;

    for (int i = 0; i < p.size(); i++)
    {
        Pixel pixel;

        pixel.blue = p[i].red;

        pixel.green = p[i].red;

        pixel.red = p[i].red;

        newP.push_back(pixel);
    }

    Write("output/part8_r.tga", headerObject, newP);

    if (Test("output/part8_r.tga", "examples/EXAMPLE_part8_r.tga"))
    {
        cout << "Test #8r...... Passed!" << endl;
    }
    else
    {
        cout << "Test #8r...... Failed!" << endl;
    }
}
void PartNine()
{
    Header headerObject;
    vector<Pixel> p;
    Read("input/layer_red.tga", headerObject, p);


    vector<Pixel> p2;
    Read("input/layer_green.tga", headerObject, p2);


    vector<Pixel> p3;
    Read("input/layer_blue.tga", headerObject, p3);

    vector<Pixel> newP;

    for (int i = 0; i < p.size(); i++)
    {
        Pixel pixel;

        pixel.blue = p3[i].blue;
        pixel.green = p2[i].green;
        pixel.red = p[i].red;

        newP.push_back(pixel);
    }

    Write("output/part9.tga", headerObject, newP);

    if (Test("output/part9.tga", "examples/EXAMPLE_part9.tga"))
    {
        cout << "Test #9...... Passed!" << endl;;
    }
    else
    {
        cout << "Test #9...... Failed!" << endl;;
    }
}
void PartTen()
{
    Header headerObject;
    vector<Pixel> p;
    Read("input/text2.tga", headerObject, p);

    vector<Pixel> newP;

    for (int i = p.size() - 1; i >= 0; i--)
    {
        Pixel pixel;

        pixel.blue = p[i].blue;
        pixel.green = p[i].green;
        pixel.red = p[i].red;

        newP.push_back(pixel);

    }

    Write("output/part10.tga", headerObject, newP);

    if (Test("output/part10.tga", "examples/EXAMPLE_part10.tga"))
    {
        cout << "Test #10...... Passed!" << endl;
    }
    else
    {
        cout << "Test #10...... Failed!" << endl;;
    }
}

//Main
int main()
{

    //Part1
    PartOne();

    //Part2
    PartTwo();

    //Part3
    PartThree();
    
    //Part4
    PartFour();

    //Part5
    PartFive();

    //Part6
    PartSix();

    //Part7
    PartSeven();

    //Part8
    PartEightBLue();
    PartEightGreen();
    PartEightRed();

    //Part9
    PartNine();

    //Part10
    PartTen();

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
