#include "../include/headers.h"

void TH1DtoCanvas(TCanvas* c, TString FileName, TString HistoName, TLegend* leg, TString LegName, int color, TString title = "")
{
        TFile *inputFile = new TFile(FileName, "read");
        TH1D *hist = (TH1D *)inputFile->Get(HistoName);
        hist->SetTitle(title);
        hist->SetLineColor(color);
        leg->AddEntry(hist, LegName);
        c->cd();
        hist->Draw("samehist");
}