#include "TH1DtoCanvas.C"

void Statistics()
{
        TCanvas *c = new TCanvas("c", "", 0, 0, 800, 600);
        TLegend *leg = new TLegend(.6, .6, .8, .8, "");
        TH1DtoCanvas(c, "../Dokumente/output_run2_parkersbin.root", "hJet_Pass", leg, "Run2", kBlack);
        TH1DtoCanvas(c, "../Dokumente/ana_run3_allNch_2022.root", "hJet_Pass", leg, "2022", 2);
        TH1DtoCanvas(c, "../Dokumente/ana_run3_allNch_2023.root", "hJet_Pass", leg, "2023", 3);
        TH1DtoCanvas(c, "../Dokumente/ana_run3_allNch_2024CDEFG.root", "hJet_Pass", leg, "2024", 4);
        leg->Draw("same");
        c->SaveAs("../Figuren/Statistics.png");
}