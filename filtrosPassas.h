//---------------------------------------------------------------------------

#ifndef filtrosPassasH
#define filtrosPassasH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Graphics.hpp>
//---------------------------------------------------------------------------
class TForm3 : public TForm
{
__published:	// IDE-managed Components
	TImage *Image1;
	TSpeedButton *SpeedButton1;
	TSpeedButton *SpeedButton2;
	TSpeedButton *SpeedButton3;
	TImage *Image2;
	TLabel *Label15;
	TLabel *Label16;
	TLabel *Label17;
	TLabel *Label4;
	void __fastcall SpeedButton3Click(TObject *Sender);
	void __fastcall SpeedButton1Click(TObject *Sender);
	void __fastcall SpeedButton2Click(TObject *Sender);

private:	// User declarations
	int tonalidade;
public:		// User declarations
	__fastcall TForm3(TComponent* Owner);
	int TForm3::CalcularCor2(RGBTRIPLE* pixel);
	int TForm3::CalcularCor(RGBTRIPLE* pixel);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm3 *Form3;
//---------------------------------------------------------------------------
#endif
