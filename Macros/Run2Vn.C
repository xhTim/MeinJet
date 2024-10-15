#include "TGEtoCanvas.C"

void Run2Vn()
{
        TCanvas *c = new TCanvas("c", "", 0, 0, 800, 600);
        TLegend *leg1 = new TLegend(.55, .2, .75, .5, "");
        TLegend *leg2 = new TLegend(.7, .2, .85, .5, "");
        TText *text = new TText();
	text->SetTextSize(0.05);
        TLine *l0 = new TLine(9.0, 0.0, 110.0, 0.0);
        TGEtoCanvas(c, "../Results/Vn/Vn_vs_Nch_202MC.root", "V1", leg1, "n=1", 632, ";N_{ch}^{j};V^{*}_{n#Delta}{2,|#Delta#eta^{*}|>2}");
        TGEtoCanvas(c, "../Results/Vn/Vn_vs_Nch_202MC.root", "V2", leg1, "n=2", 419, ";N_{ch}^{j};V^{*}_{n#Delta}{2,|#Delta#eta^{*}|>2}");
        TGEtoCanvas(c, "../Results/Vn/Vn_vs_Nch_202MC.root", "V3", leg1, "n=3", 600, ";N_{ch}^{j};V^{*}_{n#Delta}{2,|#Delta#eta^{*}|>2}");

        TGEtoCanvas(c, "../Results/Vn/Vn_vs_Nch_20run2.root", "V1", leg2, "n=1", 632, ";N_{ch}^{j};V^{*}_{n#Delta}{2,|#Delta#eta^{*}|>2}", 29);
        TGEtoCanvas(c, "../Results/Vn/Vn_vs_Nch_20run2.root", "V2", leg2, "n=2", 419, ";N_{ch}^{j};V^{*}_{n#Delta}{2,|#Delta#eta^{*}|>2}", 29);
        TGEtoCanvas(c, "../Results/Vn/Vn_vs_Nch_20run2.root", "V3", leg2, "n=3", 600, ";N_{ch}^{j};V^{*}_{n#Delta}{2,|#Delta#eta^{*}|>2}", 29);
        leg1->Draw("same");
        leg2->Draw("same");
        text->DrawText(87, -0.12, "uncor.");
	text->DrawText(70, -0.12, "cor.");
        l0->Draw("same");
        c->SaveAs("../Figuren/Vn/Run2Vn.png");
}