#include "dataPlotter.h"

DataPlotter::DataPlotter()
{

}

void DataPlotter::plotFunction(QCustomPlot *plotWidget, DiscreteData &data) {
    double size = data.getData().size();
    double max = *std::max_element(data.getData().begin(), data.getData().end());
    double min = *std::min_element(data.getData().begin(), data.getData().end());
    double range = max - min;
    QVector<double> xs(size);
    for (int i = 0; i < size; ++i) {
        xs[i] = data.getFirstXValue() + i * data.getDiscreteStep();
    }
    plotWidget->xAxis->setRange(data.getFirstXValue(), data.getFirstXValue() + size * data.getDiscreteStep());
    plotWidget->yAxis->setRange(min - range / 3, max + range / 3);
    if (plotWidget->graph() == 0) {
        plotWidget->addGraph();
    }
    plotWidget->graph(0)->setData(xs, data.getData());
    plotWidget->replot();
}

//void GraphPlotter::setAxisRange(QCustomPlot *plotWidget,
//                                double xRange1, double xRange2,
//                                double yRange1, double yRange2) {
//    plotWidget->xAxis->setRange(xRange1, xRange2);
//    plotWidget->yAxis->setRange(yRange1, yRange2);
//}

//void GraphPlotter::plotFunction(QCustomPlot *plotWidget,
//                                const QVector<double> &xValues,
//                                const QVector<double> &yValues
//                                ) {

//    if (plotWidget->graph() == 0) {
//        plotWidget->addGraph();
//    }
//    plotWidget->graph(0)->setData(xValues, yValues);
//    plotWidget->replot();
//}
