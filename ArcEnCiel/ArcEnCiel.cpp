// ArcEnCiel.cpp : main project file.


#include "stdafx.h"
#include "Form1.h"
#include <stdio.h>
#include <math.h>



using namespace ArcEnCiel;

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;



System::Drawing::Color ColorByLeft( int valMax, int valSurMille, System::Drawing::Color^ pColor)
{
    float   fParamUn;
    int     paramUn;
    int     section     = (valSurMille * 6) / valMax;
    float   fParamDeux  = (float )((float )valMax / 6.0f);
    int     algo        = 1;

    switch (algo)
    {
        default:
        case 1:
            /* degradé couleur */
            fParamUn        = fmod((float )valSurMille, fParamDeux);
            valSurMille     = (int )floor( fParamUn * 255.0f * (6.0f / valMax));
            break;
        case 2:
            /* barre de couleur */
            paramUn         = (int )valSurMille % (int )fParamDeux;
            valSurMille     = (int )( paramUn * 255 * (int )(6.0f / valMax));
            break;
    }

    switch (section)
    {
        //                         R                    G                   B
        case 0:  return pColor->FromArgb( 255,                 0,                  valSurMille);           break;
        case 1:  return pColor->FromArgb( 255 - valSurMille,   0,                  255);                   break;
        case 2:  return pColor->FromArgb( 0,                   valSurMille,        255);                   break;
        case 3:  return pColor->FromArgb( 0,                   255,                255 - valSurMille);     break;
        case 4:  return pColor->FromArgb( valSurMille,         255,                0);                     break;
        case 5:  return pColor->FromArgb( 255,                 255 - valSurMille,  0);                     break;
        default: return pColor->Black;                                                                     break;
    }
}


[STAThreadAttribute]
int main( array<System::String ^> ^args)
{
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

    Form1^ cMainWindows = gcnew Form1;

    cMainWindows->Show();

    System::Drawing::Graphics^  pFormGraphics;
    System::Drawing::Color^     pColor = gcnew System::Drawing::Color;
    System::Drawing::Color      aColor;

    pFormGraphics = cMainWindows->CreateGraphics();

    // Draw a string on the PictureBox.
    pFormGraphics->DrawString( "This is a spectral colors drawn on the windows",
         gcnew System::Drawing::Font( "Arial",14 ), System::Drawing::Brushes::Black, Point( 30, 30) );

    // Draw a line in the PictureBox.
//    pFormGraphics->DrawLine( System::Drawing::Pens::Red, pictureBox1->Left, pictureBox1->Top, pictureBox1->Right, pictureBox1->Bottom );

/*
    // draw vertical line
    for (int index = 0; index < 480; index++)
    {
        aColor = ColorByLeft( 480, index, pColor);

        System::Drawing::Pen^ myPen = gcnew System::Drawing::Pen( aColor);
        pFormGraphics->DrawLine( myPen, index, 0, index, 272);
        delete myPen;
    }
*/
/*
    // draw diagonal line wtih double step
    for (int index = 0; index < 480; index++)
    {
        aColor = ColorByLeft( 480, index, pColor);

        System::Drawing::Pen^ myPen = gcnew System::Drawing::Pen( aColor);
        pFormGraphics->DrawLine( myPen, 0, 0, index, 272);
        delete myPen;
    }
    for (int index = 272; index >= 0; index--)
    {
        aColor = ColorByLeft( 272, index, pColor);

        System::Drawing::Pen^ myPen = gcnew System::Drawing::Pen( aColor);
        pFormGraphics->DrawLine( myPen, 0, 0, 480, index);
        delete myPen;
    }
*/
    // draw diagonal line on one step
    int offset = 0;
    for (int index = 0; index < 272; index++)
    {
        aColor = ColorByLeft( 480+272, offset, pColor);

        System::Drawing::Pen^ myPen = gcnew System::Drawing::Pen( aColor);
        pFormGraphics->DrawLine( myPen, 0, 0, 480, index);
        delete myPen;
        offset++;
    }
    for (int index = 480; index >= 0; index--)
    {
        aColor = ColorByLeft( 272+480, offset, pColor);

        System::Drawing::Pen^ myPen = gcnew System::Drawing::Pen( aColor);
        pFormGraphics->DrawLine( myPen, 0, 0, index, 272);
        delete myPen;
        offset++;
    }


    pFormGraphics->DrawString( "This is a results",
         gcnew System::Drawing::Font( "Arial",14 ), System::Drawing::Brushes::Black, Point( 240, 174) );

    delete pColor;
    delete pFormGraphics;

	// Create the main window and run it
	Application::Run( cMainWindows);
	return 0;
}
