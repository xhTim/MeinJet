#include "../include/headers.h"

void TGEtoCanvas(TCanvas* c, TString FileName, TString TGEName, TLegend* leg, TString LegName, int color, TString title = "")
{
        TFile *inputFile = new TFile(FileName, "read");
        TGraphErrors *gre = (TGraphErrors *)inputFile->Get(TGEName);
        gre->SetTitle(title);
        gre->SetMarkerColor(color);
        gre->SetLineColor(color);
        leg->AddEntry(gre, LegName);
        c->cd();

        static bool isFirstCall = true;
        static int ntimes = 0;
        ntimes++;
        if (isFirstCall)
        {
                isFirstCall = false;
                gre->Draw("ap");
        }
        else
                gre->Draw("p");
        if(ntimes % 5 == 0)
                isFirstCall = true;
}