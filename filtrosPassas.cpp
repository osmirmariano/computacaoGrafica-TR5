//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "filtrosPassas.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm3 *Form3;
//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm3::SpeedButton3Click(TObject *Sender)
{
	Image1->Picture->LoadFromFile("cg.bmp"); // Carregando imagem
	Image1->Stretch = true; //redimensiona
	Image1->Refresh(); //atualiza
}
//---------------------------------------------------------------------------

int TForm3::CalcularCor2(RGBTRIPLE* pixel){
 int R = pixel->rgbtRed;
 int G = pixel->rgbtGreen;
 int B = pixel->rgbtBlue;

  return (R+G+B/3);

}

int TForm3::CalcularCor(RGBTRIPLE* pixel){
 int R = pixel->rgbtRed;
 int G = pixel->rgbtGreen;
 int B = pixel->rgbtBlue;

  return ((R*0.21)+(G*0.72)+(B*0.07));

}
void __fastcall TForm3::SpeedButton1Click(TObject *Sender)
{
	Graphics::TBitmap * copia = new Graphics::TBitmap();
	copia->LoadFromFile("cg.bmp");
	 RGBTRIPLE *r;
	 int tb, tt;
	 for (int y = 0; y < Image1->Height; y++) {
				r = (RGBTRIPLE*)copia->ScanLine[y];
				for (int x = 0; x < Image1->Width; x++) {
				tt = CalcularCor(r);
				tt =tt+(tb);
				if (tt>255){tt= 255;}
				if (tt<0){tt=0;}
				r->rgbtRed = tt;
				r->rgbtGreen = tt;
				r->rgbtBlue = tt;
				r++;
				}
			 }


			 for(int j = 1; j < H-2; j++)
			  {
			  r = (RGBTRIPLE*)copia->ScanLine[j];
			for(int i = 1; i < W-2; i++)
			 {

				float xDirection = 2*GetRValue(Image1->Canvas->Pixels[i-1][j]) - 2*GetRValue(Image1->Canvas->Pixels[i+1][j]) + GetRValue(Image1->Canvas->Pixels[i-1][j+1])
						  - GetRValue(Image1->Canvas->Pixels[i+1][j+1]) - GetRValue(Image1->Canvas->Pixels[i+1][j-1]) + GetRValue(Image1->Canvas->Pixels[i-1][j-1]);

				xDirection = xDirection / 4;

				float yDirection = 2*GetRValue(Image1->Canvas->Pixels[i][j+1]) - 2*GetRValue(Image1->Canvas->Pixels[i][j-1]) + GetRValue(Image1->Canvas->Pixels[i-1][j+1]) +
						  GetRValue(Image1->Canvas->Pixels[i+1][j+1]) - GetRValue(Image1->Canvas->Pixels[i+1][j-1]) - GetRValue(Image1->Canvas->Pixels[i-1][j-1]);

				yDirection = yDirection / 4;


				//Obt�m a magnitude do gradiente.
				float gradientValue = sqrt(pow(xDirection, 2) + pow(yDirection, 2));

				r->rgbtRed = gradientValue;
				r->rgbtGreen = gradientValue;
				r->rgbtBlue = gradientValue;
				r++;
			}
		}
		Image1->Picture->Assign(copia);
}
//---------------------------------------------------------------------------
void __fastcall TForm3::SpeedButton2Click(TObject *Sender)
{
	Graphics::TBitmap * copia = new Graphics::TBitmap();
	//copia->Assign(pict);
	copia->LoadFromFile("cg.bmp");
	RGBTRIPLE *r;
	int H = Image1->Height, W = Image1->Width, tb, tt;

	for(int j = 1; j < H-2; j++)
	{
		r = (RGBTRIPLE*)copia->ScanLine[j];
		for(int i = 1; i < W-2; i++)
		{
			int red = 4*GetRValue(Image1->Canvas->Pixels[i][j])+
					  2*(GetRValue(Image1->Canvas->Pixels[i][j-1])+ GetRValue(Image1->Canvas->Pixels[i][j+1])+ GetRValue(Image1->Canvas->Pixels[i-1][j])+ GetRValue(Image1->Canvas->Pixels[i+1][j]))+
					  1*(GetRValue(Image1->Canvas->Pixels[i-1][j+1])+ GetRValue(Image1->Canvas->Pixels[i+1][j+1])+ GetRValue(Image1->Canvas->Pixels[i+1][j-1]) + GetRValue(Image1->Canvas->Pixels[i-1][j-1]));

			red = (int)(red/16);

			int green = 4*GetGValue(Image1->Canvas->Pixels[i][j])+
					  2*( GetGValue(Image1->Canvas->Pixels[i][j-1])+ GetGValue(Image1->Canvas->Pixels[i][j+1])+ GetGValue(Image1->Canvas->Pixels[i-1][j])+ GetGValue(Image1->Canvas->Pixels[i+1][j])) +
					  1*( GetGValue(Image1->Canvas->Pixels[i-1][j+1])+ GetGValue(Image1->Canvas->Pixels[i+1][j+1])+ GetGValue(Image1->Canvas->Pixels[i+1][j-1])+ GetGValue(Image1->Canvas->Pixels[i-1][j-1]));

			green = (int)(green/16);

			int blue = 4*GetBValue(Image1->Canvas->Pixels[i][j])+
					  2*( GetBValue(Image1->Canvas->Pixels[i][j-1])+ GetBValue(Image1->Canvas->Pixels[i][j+1])+ GetBValue(Image1->Canvas->Pixels[i-1][j])+ GetBValue(Image1->Canvas->Pixels[i+1][j])) +
					  1*( GetBValue(Image1->Canvas->Pixels[i-1][j+1])+ GetBValue(Image1->Canvas->Pixels[i+1][j+1])+ GetBValue(Image1->Canvas->Pixels[i+1][j-1])+ GetBValue(Image1->Canvas->Pixels[i-1][j-1]));

			blue = (int)(blue/16);

			r->rgbtRed = red;
			r->rgbtGreen = green;
			r->rgbtBlue = blue;
			r++;

		}
	}
	Image1->Picture->Assign(copia);
}
//---------------------------------------------------------------------------
