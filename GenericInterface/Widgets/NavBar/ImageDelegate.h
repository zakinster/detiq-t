#ifndef QTINTERFACE_WIDGET_IMAGEDELEGATE_H
#define QTINTERFACE_WIDGET_IMAGEDELEGATE_H

#include <QItemDelegate>
#include <QPainter>
#include <QRectF>

namespace genericinterface
{
  class ImageDelegate : public QItemDelegate
  {
    Q_OBJECT
    public:
    ImageDelegate(int width);
    /**
	 * @brief Redefinition of paint() from QItemDelegate to change de display in the navigation bar.
	 //TODO parameters
	 * @param painter xxx
	 * @param option xxx
	 * @param index xxx
	 */
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    
    /**
	 * @brief Redefinition of sizeHint) from QItemDelegate.
	 //TODO parameters
	 * @param option xxx
	 * @param index xxx
	 */
    QSize sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const;
    
    public slots:
    bool helpEvent ( QHelpEvent * event, QAbstractItemView * view, const QStyleOptionViewItem & option, const QModelIndex & index );
    
    private:
        int _width;
  };
}

#endif
