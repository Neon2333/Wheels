#include "TubeGradiantCircle.h"


TubeGradiantCircle::TubeGradiantCircle(QWidget* parent) : LoadingWidget(parent)
{
	m_color = QColor("#3BB6FE");
	m_font = QFont("Microsoft YaHei", 4, 4);
}

void TubeGradiantCircle::paintEvent(QPaintEvent* event)
{
	//根据QPaintPath画出渐变色的圆弧
	int width = this->width();
	int height = this->height();
	int side = qMin(width, height);

	QPainter painter(this);
	painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
	painter.translate(width / 2, height / 2);
	painter.scale(side / 200.0, side / 200.0);	//scale() 函数用于对当前的变换矩阵应用缩放变换

	QConicalGradient gra(QPoint(0, 0), 0);	//用于创建圆锥渐变效果的类
	gra.setColorAt(0, m_color);
	gra.setColorAt(1, QColor("#FFFFFF"));
	QBrush brush(gra);

	int radis = 40;
	int sider = 10;
	QRect rrect(-radis, -radis, radis * 2, radis * 2);
	QPainterPath path;
	path.arcTo(rrect, 0, 270);

	QPainterPath subPath;
	subPath.addEllipse(rrect.adjusted(sider, sider, -sider, -sider));
	qreal ang = m_angle;
	path = path - subPath;
	
	painter.setBrush(brush);
	painter.setPen(Qt::NoPen);
	painter.rotate(ang);
	painter.drawPath(path);
	painter.resetTransform();	//重置坐标变换

	if (m_text == "")	return;
	//painter.setBrush(QBrush(m_textColor));
	//painter.setFont(m_font);
	//QFontMetrics fm(m_font);
	//const QString text(m_text);
	//qreal textw = fm.horizontalAdvance(text);
	//qreal texth = fm.height();
	//QPainterPath path_text;
	//path_text.addText(QPointF((x - textw) / 2, 0.5 * y + texth / 4), m_font, text);
	////painter.setClipPath(path1);
	////painter.drawRect(rect());
	//painter.drawPath(path_text);

	QFontMetrics fm(m_font);
	qreal textw = fm.horizontalAdvance(m_text);
	qreal texth = fm.height();
	painter.setPen(m_textColor);
	painter.setFont(m_font);
	painter.drawText(QPointF((width - textw) / 2, 0.5 * height + texth / 4), m_text);

}
