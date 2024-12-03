#include "TH1DtoCanvas.C"

void Statistics()
{
        TCanvas *c = new TCanvas("c", "", 0, 0, 800, 600);
        c->SetLogy();
        TLegend *leg = new TLegend(.6, .6, .8, .8, "");
        /*
        TH1DtoCanvas(c, "../Dokumente/output_run2_parkersbin.root", "hJet_Pass", leg, "Run2", kBlack, ";;Statistics");
        TH1DtoCanvas(c, "../Dokumente/ana_run3_allNch_2022.root", "hJet_Pass", leg, "2022", 2, ";;Statistics");
        TH1DtoCanvas(c, "../Dokumente/ana_run3_allNch_2023.root", "hJet_Pass", leg, "2023", 3, ";;Statistics");
        TH1DtoCanvas(c, "../Dokumente/ana_run3_allNch_2024CDEFG.root", "hJet_Pass", leg, "2024", 4, ";;Statistics");
        TH1DtoCanvas(c, "../Dokumente/ana_run3_allNch_2024_Jet275.root", "hJet_Pass", leg, "new trigger", 6, ";;Statistics");
        */
        TH1DtoCanvas(c, "../Dokumente/ana_Run2_83bin.root", "hJet_Pass", leg, "new", kBlack, ";;Statistics");
        TH1DtoCanvas(c, "../Dokumente/new_default_complete_vn.root", "hJet_Pass", leg, "parker", 2, ";;Statistics");
        leg->Draw("same");
        c->SaveAs("../Figuren/Statistics_ip.png");
}
