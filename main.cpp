#include <iostream>
#include <vector>
#include <string>
#include "bitmap.h"

using namespace std;
const int MAXNUM = 10;
/*
take in the files and check wether they are all valid and eclude the unvalid ones
have a list of bitmaps
go throut  each row and collum of each bitmap at the same time and assign an average value on a new grid
ave an output a bmp file*/

// recive #of row and collum and output progress in % complete
void progress(double, double);
// recive the refrence of the bitmap first bitmap and compares to the rest of the imputs
bool isValid(Bitmap &, Bitmap &);

int main()
{
    string pic;
    Bitmap bmp1;
    vector < vector < vector <Pixel> > > work;
    for(int i=0; i< MAXNUM ; i++)
    {
        Bitmap bmp;
        cout << "Please enter a valid bmp image.";
        if( i > 1) 
        {
            cout << "or enter done if you want to stop."; 
        }
        cin >> pic;
        if(pic !="done" && pic !="Done")
        {
            bmp.open(pic);
            if(bmp.isImage())
            {
                if(i==0)
                {
                    bmp1.open(pic);
                    work.resize(i+1);
                    vector < vector < Pixel > > test;
                    test = bmp.toPixelMatrix();
                    work[i].resize(test.size());
                    for(int x=0; x < test.size(); x++)
                    {
                        work[i][x].resize(test[0].size());
                        for( int y=0; y < test[0].size(); y++)
                        {
                            work[i][x][y] = test[x][y];
                        }
                    }
                }
                else if( isValid( bmp1 , bmp))
                {
                    work.resize(i+1);
                    vector < vector < Pixel > > test;
                    test = bmp.toPixelMatrix();
                    work[i].resize(test.size());
                    for(int x=0; x < test.size(); x++)
                    {
                        work[i][x].resize(test[0].size());
                        for( int y=0; y < test[0].size(); y++)
                        {
                            work[i][x][y] = test[x][y];
                        }
                    }
                }
                else
                {
                    i--;
                }
            }
            else
            {
                i--;
            }
        }
        else
        {
            break;
        }
    }
    int temp1 = work.size();
    int temp2 = work[0].size();
    vector < vector < Pixel > > avg;
    avg.resize(temp1);
    for( int i = 0; i < work.size(); i++)
    {
        avg[i].resize(temp2);
        double averager = 0;
        double averageg = 0;
        double averageb = 0;
        Pixel rgb;
        for( int x = 0; x < work[i].size(); x++)
        {   
            for( int y = 0; y < work[i][x].size(); y++)
            {
                rgb = work[i][x][y];
                averager += rgb.red;
                averageg += rgb.green;
                averageb += rgb.blue;


            }
            averager = averager / work[0][0].size()-1;
            averageg = averageg / work[0][0].size()-1;
            averageb = averageb / work[0][0].size()-1;
            rgb.red = averager;
            rgb.green = averageg;
            rgb.blue = averageb;
            avg[i][x]= rgb;
            progress((i+1)/work.size() , (x+1)/work[0].size());

        }


    }
    Bitmap end;
    end.fromPixelMatrix(avg);
    end.save("Composite-jwest27.bmp");
}

void progress( double row, double col)
{
    cout << row * col << "% " << "Compleate.\n";
}





bool isValid( Bitmap & bmp1, Bitmap & bmp)
{
    vector <vector <Pixel> > control =bmp1.toPixelMatrix();
    vector <vector <Pixel> > test =bmp.toPixelMatrix();
    if(control.size() == test.size())
    {
        if( control[0].size() == test[0].size())
        {
            return true;
        }
        else
        {
            return false;
        }

    }
    else
    {
        return false;
    }
}

