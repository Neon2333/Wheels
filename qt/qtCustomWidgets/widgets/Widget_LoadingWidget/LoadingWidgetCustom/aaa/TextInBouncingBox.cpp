#include "TextInBouncingBox.h"
#include <QRgb>

TextInBouncingBox::TextInBouncingBox(QWidget* parent, const QString& str):LoadingWidget(parent)
{
	m_colorList = QList<QColor>{ "#0839F8", "#13DDFB", "#13FE7C", "#5AFF09", "#FDFE0A", "#F05C08", "#EC0238", "#ED01DE", "#88057F"};
	m_textColor = QColor("white");
	m_text = str;
	m_font = QFont("Microsoft YaHei", 6, 2);
}


void TextInBouncingBox::paintEvent(QPaintEvent*)
{
	const int len = m_text.size();
	if (len <= 0) return;
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);

	QFontMetrics fm(m_font);
	const int txtH = fm.height();
	const int rectH = txtH + 4;
	const int rectW = fm.horizontalAdvance("w") + 4;
	const qreal x = width();
	const qreal y = height();
	painter.translate(0.1 * x, 0.6 * y);

	const qreal amplitude = rectH * 0.6;
	const qreal offset = M_PI / len / 2;
	if (m_colorList.size() < len)
	{
		for (int i = 0; i < len; ++i)
		{
			//qSin 是 Qt 框架中的一个函数，定义在 <QtMath> 头文件中，它用于计算正弦值
			QRectF rct(i * rectW, -rectH - amplitude * qSin(-2 * M_PI / 360 * m_angle + offset * i), rectW, rectH);
			painter.setBrush(QBrush(m_colorList[0]));
			painter.setPen(Qt::NoPen);
			painter.drawRect(rct);  //画一个小盒子
			painter.setPen(m_textColor);
			painter.drawText(rct, Qt::AlignCenter, QString(m_text[i])); //画一个字符
		}
	}
	else
	{
		for (int i = 0; i < len; ++i)
		{
			//qSin 是 Qt 框架中的一个函数，定义在 <QtMath> 头文件中，它用于计算正弦值
			QRectF rct(i * rectW, -rectH - amplitude * qSin(-2 * M_PI / 360 * m_angle + offset * i), rectW, rectH);
			painter.setBrush(QBrush(m_colorList[i]));
			painter.setPen(Qt::NoPen);
			painter.setFont(m_font);
			painter.drawRect(rct);  //画一个小盒子
			painter.setPen(m_textColor);
			painter.drawText(rct, Qt::AlignCenter, QString(m_text[i])); //画一个字符
		}
	}
	
}
