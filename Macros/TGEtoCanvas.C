#include "../include/headers.h"

void TGEtoCanvas(TCanvas* c, TString FileName, TString TGEName, TLegend* leg, TString LegName, int color, TString title = "")
{
        static int ntimes = 0;

        TFile *inputFile = new TFile(FileName, "read");
        TGraphErrors *gre = (TGraphErrors *)inputFile->Get(TGEName);
        gre->SetTitle(title);
        gre->SetMarkerColor(color);
        gre->SetLineColor(color);
        if(ntimes == 7)
                gre->GetYaxis()->SetRangeUser(-0.05, 0.1);
        leg->AddEntry(gre, LegName);
        c->cd();

        static bool isFirstCall = true;
        ntimes++;
        if (isFirstCall)
        {
                isFirstCall = false;
                gre->Draw("ap");
        }
        else
                gre->Draw("p");
        if(ntimes % 7 == 0)
                isFirstCall = true;
}
