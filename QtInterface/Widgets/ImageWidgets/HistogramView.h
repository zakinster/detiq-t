#ifndef HISTOGRAMVIEW_H
#define HISTOGRAMVIEW_H

#include <QMouseEvent>
#include <QPainter>
#include <QPen>
#include <QString>
#include <QFontMetrics>
#include <QPointF>
#include <QBrush>

#include <qpen.h>
#include <qwt_plot.h>
#include <qwt_plot_layout.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_histogram.h>
#include <qwt_legend.h>
#include <qwt_legend_item.h>
#include <qwt_column_symbol.h>
#include <qwt_series_data.h>
#include <stdlib.h>

#include <Image.h>
#include <Rectangle.h>
#include <Histogram.h>

#include "GraphicalHistogram.h"
#include "AlternativeImageView.h"


using namespace imagein;

namespace genericinterface
{
    class HistogramView : public AlternativeImageView
    {
		Q_OBJECT
	private:
		imagein::Histogram* _histogram;
		QwtPlot* _qwtPlot;
		
		void init();
		void populate();
        void mousePressEvent(QMouseEvent* event);
        void mouseMoveEvent(QMouseEvent* event);
	
    public:
		HistogramView();
		HistogramView(Image* image, imagein::Histogram* histogram);
        int getMemorisedValue(int i);
        void setMemorisedValue(int i, int value);
        QwtPlot* getHistogram();
		
	signals:
		void valueClickedLeft(int value);
		void valueClickedRight(int value);
		void valueHovered(int value);
    };
}

#endif // HISTOGRAMVIEW_H