#include "../include/headers.h"

void TGEtoCanvas(TCanvas* c, TString FileName, TString TGEName, TLegend* leg, TString LegName, int color, TString title = "", int style = 20)
{
        static int ntimes = 0;

        TFile *inputFile = new TFile(FileName, "read");
        TGraphErrors *gre = (TGraphErrors *)inputFile->Get(TGEName);
        gre->SetTitle(title);
        gre->SetMarkerColor(color);
        gre->SetLineColor(color);
        gre->SetMarkerStyle(style);
        gre->SetMarkerSize(1.5);
        /*
        if(ntimes == 0)
        	gre->GetYaxis()->SetRangeUser(-0.3, 0.1);
        if(ntimes == 4)
                gre->GetYaxis()->SetRangeUser(-0.05, 0.1);
        if(ntimes == 8)
                gre->GetYaxis()->SetRangeUser(-0.035, 0.010);
        */
        leg->AddEntry(gre, LegName);
        c->cd();

        static bool isFirstCall = true;
        ntimes++;
        if (isFirstCall)
        {
                isFirstCall = false;
                //gre->GetXaxis()->SetRangeUser(75, 110);
                gre->Draw("ap");
        }
        else
                gre->Draw("p");
        //if(ntimes % 4 == 0)
        //        isFirstCall = true;
}
