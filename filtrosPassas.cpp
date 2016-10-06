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
	Form3->Color = clWhite;
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
	Graphics::TBitmap *passaAltas = new Graphics::TBitmap();
	passaAltas->LoadFromFile("cg.bmp");
	RGBTRIPLE *r;
	int luminosidade, posicao;
	float valor1, valor2;
	for (int y = 0; y < Image1->Height; y++) {
		r = (RGBTRIPLE*)passaAltas->ScanLine[y];
		for (int x = 0; x < Image1->Width; x++) {
			luminosidade = CalcularCor(r);
			luminosidade = luminosidade + posicao;
			if (luminosidade > 255){
				luminosidade = 255;
			}
			if (luminosidade < 0){
				luminosidade = 0;
			}
			r->rgbtRed = luminosidade;
			r->rgbtGreen = luminosidade;
			r->rgbtBlue = luminosidade;
			r++;
		}
	}
	for(int j = 0; j < Image1->Height; j++){
		r = (RGBTRIPLE*)passaAltas->ScanLine[j];   //Scanline retorna memoria do Bitmap
		for(int i = 0; i < Image1->Width; i++){
			//r = abs(r*3-c1-c2-c3)/4
			valor1 = GetRValue(Image1->Canvas->Pixels[i-1][j]) - GetRValue(Image1->Canvas->Pixels[i+1][j]) - GetRValue(Image1->Canvas->Pixels[i-1][j+1])
			- GetRValue(Image1->Canvas->Pixels[i+1][j+1]) - GetRValue(Image1->Canvas->Pixels[i+1][j-1]) - GetRValue(Image1->Canvas->Pixels[i-1][j-1]);
			valor1 = valor1/4;

			valor2 = GetRValue(Image1->Canvas->Pixels[i][j+1]) - GetRValue(Image1->Canvas->Pixels[i][j-1]) - GetRValue(Image1->Canvas->Pixels[i-1][j+1]) -
			GetRValue(Image1->Canvas->Pixels[i+1][j+1]) - GetRValue(Image1->Canvas->Pixels[i+1][j-1]) - GetRValue(Image1->Canvas->Pixels[i-1][j-1]);
			valor2 = valor2/4;

			//Obt�m a magnitude do gradiente.
			float valorGradiente = sqrt(pow(valor1, 2) + pow(valor2, 2));

			r->rgbtRed = valorGradiente;
			r->rgbtGreen = valorGradiente;
			r->rgbtBlue = valorGradiente;
			r++;
		}
	}
	Image1->Picture->Assign(passaAltas);
}
//---------------------------------------------------------------------------
void __fastcall TForm3::SpeedButton2Click(TObject *Sender)
{
	Graphics::TBitmap *passaBaixa = new Graphics::TBitmap();
	passaBaixa->LoadFromFile("cg.bmp");
	RGBTRIPLE *resultado;
	int vermelho, verde, azul;

	for(int j = 0; j < Image1->Height; j++)
	{
		resultado = (RGBTRIPLE*)passaBaixa->ScanLine[j];
		for(int i = 0; i < Image1->Width; i++)
		{
			vermelho = GetRValue(Image1->Canvas->Pixels[i][j]) + GetRValue(Image1->Canvas->Pixels[i][j-1]) + GetRValue(Image1->Canvas->Pixels[i][j+1]) +
					   GetRValue(Image1->Canvas->Pixels[i-1][j]) + GetRValue(Image1->Canvas->Pixels[i+1][j]) + GetRValue(Image1->Canvas->Pixels[i-1][j+1]) +
					   GetRValue(Image1->Canvas->Pixels[i+1][j+1]) + GetRValue(Image1->Canvas->Pixels[i+1][j-1]) + GetRValue(Image1->Canvas->Pixels[i-1][j-1]);
			vermelho = (int)(vermelho/9);

			verde = GetGValue(Image1->Canvas->Pixels[i][j])+ GetGValue(Image1->Canvas->Pixels[i][j-1]) + GetGValue(Image1->Canvas->Pixels[i][j+1])+
					GetGValue(Image1->Canvas->Pixels[i-1][j])+ GetGValue(Image1->Canvas->Pixels[i+1][j]) + GetGValue(Image1->Canvas->Pixels[i-1][j+1])+
					GetGValue(Image1->Canvas->Pixels[i+1][j+1])+ GetGValue(Image1->Canvas->Pixels[i+1][j-1]) + GetGValue(Image1->Canvas->Pixels[i-1][j-1]);
			verde = (int)(verde/9);

			azul = GetBValue(Image1->Canvas->Pixels[i][j])+ GetBValue(Image1->Canvas->Pixels[i][j-1]) + GetBValue(Image1->Canvas->Pixels[i][j+1])+
				   GetBValue(Image1->Canvas->Pixels[i-1][j])+ GetBValue(Image1->Canvas->Pixels[i+1][j]) + GetBValue(Image1->Canvas->Pixels[i-1][j+1])+
				   GetBValue(Image1->Canvas->Pixels[i+1][j+1])+ GetBValue(Image1->Canvas->Pixels[i+1][j-1]) + GetBValue(Image1->Canvas->Pixels[i-1][j-1]);
			azul = (int)(azul/9);

			resultado->rgbtRed = vermelho;
			resultado->rgbtGreen = verde;
			resultado->rgbtBlue = azul;
			resultado++;
		}
	}

	Image1->Picture->Assign(passaBaixa);  //Atribui a c�pia da imagem
}
//---------------------------------------------------------------------------
