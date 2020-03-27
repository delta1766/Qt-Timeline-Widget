#ifndef TIMELINEBUCKET_H
#define TIMELINEBUCKET_H

#include <QObject>
#include <QWidget>
#include <QHBoxLayout>
#include <QDebug>
#include <QMimeData>
#include <QDrag>
#include <QPropertyAnimation>
#include "timelinetimelabel.h"
#include "timelinetextlabel.h"
#include "timelineleadingdot.h"

#define TIMELINE_BUCKET_MIME_KEY "TIMELINE_BUCKET_WIDGET"

class TimelineBucket : public QWidget
{
    Q_OBJECT
public:
    TimelineBucket(QWidget *parent = nullptr);
    void initView();

    void setVerticalIndex(int index);
    void setTime(QString time);
    void setText(int index, QString text);
    void setText(QString text);
    void setText(QStringList texts);
    QString getText(int index);

    void clearText();

    QString toString(QString time_format = "【%1】", QString para_split = "\n");

    void setTimeLabelWidth(int w);
    void adjustWidgetsSize();
    void adjustBucketSize();
    QSize getSuitableSize();
    void adjustWidgetsPositions(int start = 0);
    void adjustWidgetsPositionWithAnimation(int start = 0, int end = -1);

    bool isSelected();
    void setSelected(bool select);

protected:
    void showEvent(QShowEvent* event) override;
    void paintEvent(QPaintEvent *event) override;
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dragLeaveEvent(QDragLeaveEvent *event) override;
    void dropEvent(QDropEvent *event) override;

private:
    void addTextWidget(QString text = "");
    void connectWidgetEvent(TimelineTextLabel* label);
    bool canDropMimeData(QDropEvent* event);

signals:
    void signalSizeHintChanged(QSize size);
    void signalBucketWidgetClicked();
    void signalTimeWidgetClicked(TimelineTimeLabel* label);
    void signalTextWidgetClicked(TimelineTextLabel* label);
    void signalTimeWidgetDoubleClicked(TimelineTimeLabel* label);
    void signalTextWidgetDoubleClicked(TimelineTextLabel* label);
    void signalDroppedAndMoved(TimelineBucket* bucket); // 被拖拽到外面去，从现在这里删掉

public slots:
    void actionInsertLeft(TimelineTextLabel* label);
    void actionInsertRight(TimelineTextLabel* label);
    void actionDelete(TimelineTextLabel* label);
    void actionMoveTextLabel(int from, int to);

private:
    TimelineLeadingDot* leading_dot; // 开头的小点
    TimelineTimeLabel* time_widget; // 时间点的线
    QList<TimelineTextLabel*> text_widgets; // 这个时间点的text控件列表

    int vertical_index; // 在整个时间轴里面的下标

    int padding_left = 10; // 最左边开始的位置
    int leading_dot_radius = 5; // 开头小圆点的半径
    int dot_time_spacing  = 30; // 时间和小圆点的距离
    int horizone_spacing = 30; // 每个text之间的间隔
    int vertical_spacing = 20; // 竖向两个时间段的固定距离

    QPoint press_pos;
    bool selecting;
};

#endif // TIMELINEBUCKET_H
