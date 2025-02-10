#include "TextPoint.h"

TextPoint::TextPoint(QWidget* parent, const QString& str) : LoadingWidget(parent)
{
	m_text = str;
	m_font = QFont("Microsoft YaHei", 6, 2);
}

TextPoint::~TextPoint()
{}

void TextPoint::paintEvent(QPaintEvent*)
{
	const int len = m_text.size();
	if (len <= 0) return;
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setPen(m_textColor);

	QFontMetrics fm(m_font);
	const int txtH = fm.height();
	const int rectH = txtH + 4;
	const int rectW = fm.horizontalAdvance("w") + 4;
	const qreal x = width();
	const qreal y = height();

	for (int i = 0; i < len; ++i)
	{
		QRectF rct(i * rectW, 0.1*y, rectW, rectH);
		painter.drawText(rct, Qt::AlignCenter, QString(m_text[i])); //画一个字符
	}
	if (m_angle > 90)
	{
		QRectF rct(len * rectW, 0.1 * y, rectW, rectH);
		painter.drawText(rct, Qt::AlignCenter, QString(".")); //画一个字符
	}
	if (m_angle >= 180 )
	{
		QRectF rct((len+1) * rectW, 0.1 * y, rectW, rectH);
		painter.drawText(rct, Qt::AlignCenter, QString(".")); //画一个字符
	}
	if (m_angle >= 270 )
	{
		QRectF rct((len + 2) * rectW, 0.1 * y, rectW, rectH);
		painter.drawText(rct, Qt::AlignCenter, QString(".")); //画一个字符
	}
}
