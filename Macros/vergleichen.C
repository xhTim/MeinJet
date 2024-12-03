#include <TCanvas.h>
#include <TGraphErrors.h>
#include <TLegend.h>

void vergleichen() {
    // 第一组数据
    const int nPoints = 9;
    double Nch[nPoints] = {16.2114, 29.8938, 41.268, 52.6482, 63.7864, 73.5483, 82.5317, 93.4031, 103.063};
    double v2_03[nPoints] = {0.268709, 0.264579, 0.23065, 0.192245, 0.156827, 0.136354, 0.105876, 0.109153, 0.146663};
    double v2_03_stat_err[nPoints] = {7.6668e-05, 5.91096e-05, 8.720716e-05, 1.85042e-04, 4.93161e-04,
                                      1.30156e-03, 2.93834e-03, 8.0761e-03, 1.06229e-02};

    // 第二组数据
    double mAve[nPoints] = {16.211, 29.8929, 41.2667, 52.6465, 63.7844, 73.5464, 82.5302, 93.4003, 103.058};
    double v2_07[nPoints] = {0.268632, 0.264612, 0.230538, 0.192195, 0.156122, 0.135721, 0.104987, 0.116866, 0.139505};
    double v2_07_stat_err[nPoints] = {7.664e-05, 5.90548e-05, 8.71866e-05, 1.84914e-04, 4.95013e-04,
                                      1.30575e-03, 2.96041e-03, 7.52823e-03, 1.10841e-02}; //My resylt
    //double v2_05[nPoints] = {0.272076, 0.267498, 0.232329, 0.193129, 0.157223, 0.136466, 0.105204, 0.1104, 0.140019};
    //double v2_05_stat_err[nPoints] = {7.64742e-05, 5.90546e-05, 8.72149e-05, 0.000185138, 0.000493728,
    //                                  0.00130453, 0.00292565, 0.00791499, 0.0109802}; fit 5 terms
    double v2_05[nPoints] = {0.26873, 0.264593, 0.230656, 0.192248, 0.156828, 0.136367, 0.105022, 0.108738, 0.138142};
    double v2_05_stat_err[nPoints] = {7.66715e-05, 5.91106e-05, 8.72078e-05, 0.000185042, 0.000493167,
                                      0.00130144, 0.00292359, 0.0080172, 0.0110898};

    // 创建 TGraphErrors 对象
    TGraphErrors *graph1 = new TGraphErrors(nPoints, Nch, v2_03, nullptr, v2_03_stat_err);
    TGraphErrors *graph2 = new TGraphErrors(nPoints, Nch, v2_05, nullptr, v2_05_stat_err);
    TGraphErrors *graph3 = new TGraphErrors(nPoints, mAve, v2_07, nullptr, v2_07_stat_err);

    // 设置样式
    graph1->SetLineColor(kRed);
    graph1->SetMarkerColor(kRed);
    graph1->SetMarkerStyle(20); // 圆点样式

    graph2->SetLineColor(kBlack);
    graph2->SetMarkerColor(kBlack);
    graph2->SetMarkerStyle(21); // 方点样式
    
    graph3->SetLineColor(7);
    graph3->SetMarkerColor(7);
    graph3->SetMarkerStyle(21); // 方点样式

    // 创建画布
    TCanvas *c = new TCanvas("c", "Two TGraphErrors Example", 800, 600);

    // 绘制第一个图
    graph1->Draw("AP"); // "A"表示绘制坐标轴，"P"表示绘制点
    graph1->GetXaxis()->SetTitle("N_{ch}"); // 设置横轴标题
    graph1->GetYaxis()->SetTitle("v_{2}");  // 设置纵轴标题

    // 绘制第二个图
    graph2->Draw("P same"); // "P same"表示在同一画布上叠加绘制
    graph3->Draw("P same");

    // 创建图例
    TLegend *legend = new TLegend(0.7, 0.7, 0.9, 0.9); // 设置图例位置
    legend->AddEntry(graph1, "paper", "P");
    legend->AddEntry(graph2, "file", "P");
    legend->AddEntry(graph3, "new", "P");
    legend->Draw();

    // 显示画布
    c->Update();
    c->SaveAs("../Figuren/vergleichen_3.png");
}

