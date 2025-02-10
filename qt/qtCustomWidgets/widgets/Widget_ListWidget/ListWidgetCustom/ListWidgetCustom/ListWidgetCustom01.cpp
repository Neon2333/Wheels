#include "ListWidgetCustom01.h"

ListWidgetCustom01::ListWidgetCustom01(QWidget* parent, bool isView)
	: QWidget(parent)
{
	ui.setupUi(this);

    m_font.setFamily("Microsoft Yahei");
    m_font.setPixelSize(20);
    m_fontHover.setFamily("Microsoft Yahei");
    m_fontHover.setPixelSize(17);
    m_fontSelected.setFamily("Microsoft Yahei");
    m_fontSelected.setPixelSize(20);

    m_isView = isView;
    //m_model = new QStandardItemModel;

    this->setContentsMargins(0, 0, 0, 0);
    this->setStyleSheet("QScrollBar{background: transparent}");
    QHBoxLayout* hlay = new QHBoxLayout;

    slider = new ScrollBarCustom01(this);
    slider->setContentsMargins(0, 0, 0, 0);
    slider->setMaximum(100);
    slider->setSingleStep(1);

    if (m_isView)
    {
        m_model = new QStandardItemModel;

        listview = new QListView(this);
        listview->setMouseTracking(true);
        listview->setModel(m_model);
        listview->setEditTriggers(QAbstractItemView::DoubleClicked);   //view˫���༭�༭
        listview->setIconSize(QSize(50, 50)); //view�趨ͼ���С
        listview->setViewMode(QListView::ListMode); // ����Ϊ�б�ģʽ
        listview->setSelectionMode(QAbstractItemView::SingleSelection); // ����Ϊ��ѡ
        listview->setSelectionBehavior(QAbstractItemView::SelectRows); // ѡ������
        listview->setResizeMode(QListView::Adjust); // ������ͼ��С����Ӧ����
        listview->setSpacing(0); // ������֮��ļ��Ϊ10����c
        listview->setVerticalScrollBar(slider);
        listview->setStyleSheet(qssStyleView);

        hlay->addWidget(listview);

        //����¼�������ͼ�꣨ÿ��item�����Լ��ģ�
        QObject::connect(listview, &QListView::clicked, listview, [this]() {
            if (!selItemsIndexs.isEmpty())
            {
                for (int i = 0; i < selItemsIndexs.size(); i++)
                {
                    if (selItemsIndexs.at(i) == true)
                    {
                        QStandardItem* item = m_model->item(i);
                        item->setIcon(m_icons.at(i));
                        item->setFont(m_font);
                        selItemsIndexs[i] = false;
                    }
                }
            }
            
            QItemSelectionModel* selectedModel = listview->selectionModel();
            if (selectedModel->hasSelection())
            {
                QModelIndexList selIndexs = selectedModel->selectedIndexes();    //QModelIndex�ļ���
                for (const QModelIndex& index : selIndexs)
                {
                    QStandardItem* item = m_model->itemFromIndex(index);
                    int rowIndex = index.row();
                    item->setIcon(m_iconsClicked.at(rowIndex));
                    item->setFont(m_fontSelected);
                    selItemsIndexs[rowIndex] = true;
                }
            }
            });

        listview->installEventFilter(this);
    }
    else
    {
        listwidget = new QListWidget(this);
        listwidget->setMouseTracking(true); //ȷ�����������׷�٣��Ա��ܹ�������İ��º��ͷ��¼�
        listwidget->setSelectionMode(QAbstractItemView::SingleSelection); // ����Ϊ��ѡ
        listwidget->setSelectionBehavior(QAbstractItemView::SelectRows); // ѡ������
        listwidget->setResizeMode(QListView::Adjust); // ������ͼ��С����Ӧ����
        listwidget->setSpacing(0); // ������֮��ļ��Ϊ10����
        listwidget->setVerticalScrollBar(slider);
        listwidget->setStyleSheet(qssStyleWidget);
        listwidget->installEventFilter(this);

        hlay->addWidget(listwidget);

        //����¼�������ͼ�꣨ÿ��item�����Լ��ģ�
        QObject::connect(listwidget, &QListWidget::itemClicked, listwidget, [this]() {
            if (!selItemsIndexs.isEmpty())
            {
                for (int i = 0; i < selItemsIndexs.size(); i++)
                {
                    if (selItemsIndexs.at(i) == true)
                    {
                        QListWidgetItem* item = listwidget->item(i);
                        item->setIcon(m_icons.at(i));
                        item->setFont(m_font);
                        selItemsIndexs[i] = false;
                    }
                }
            }

            QList<QListWidgetItem*> selItems = listwidget->selectedItems();
            for (auto item : selItems)
            {
                int index = listwidget->row(item);
                item->setIcon(m_iconsClicked.at(index));
                item->setFont(m_fontSelected);
                int rowIndex = listwidget->row(item);
                selItemsIndexs[rowIndex] = true;
            }
            });
        listwidget->installEventFilter(this);
    }
    this->setLayout(hlay);

    /*  connect(listview->verticalScrollBar(), &QScrollBar::valueChanged, this, [=]() {

          slider->setMaximum(listview->verticalScrollBar()->maximum());
          slider->setValue(listview->verticalScrollBar()->value());
          });

      connect(slider, &ScrollBarCustom01::valueChanged, this, [=](int val) {
          listview->verticalScrollBar()->setSliderPosition(val);
          });*/
}

ListWidgetCustom01::~ListWidgetCustom01()
{}

QIcon ListWidgetCustom01::changeIconColor(QIcon icon, QColor newColor)
{
    QPixmap pixmap = icon.pixmap(QSize(64, 64));
    QPainter painter(&pixmap);
    painter.setCompositionMode(QPainter::CompositionMode_SourceAtop);
    painter.setBrush(newColor);
    painter.drawRect(pixmap.rect());
    QIcon icon_ = QIcon(pixmap);
    return icon_;
}

void ListWidgetCustom01::addItem(QString item, QIcon icon, QIcon iconClicked, QIcon iconHover)
{
    if (m_isView)    return;

    QListWidgetItem* row = new QListWidgetItem(icon, item);
    row->setTextAlignment(Qt::AlignCenter);
    listwidget->addItem(row);
    ++itemCount;
    m_icons.append(icon);
    m_iconsClicked.append(iconClicked);
    m_iconsHover.append(iconHover);
    selItemsIndexs.append(false);
}

void ListWidgetCustom01::insertItem(QString item, int index, QIcon icon, QIcon iconClicked, QIcon iconHover)
{
    if (m_isView)    return;

    QListWidgetItem* row = new QListWidgetItem(icon, item);
    row->setTextAlignment(Qt::AlignCenter);
    listwidget->insertItem(index, row);
    ++itemCount;
    m_icons.insert(index, icon);
    m_iconsClicked.insert(index, iconClicked);
    m_iconsHover.insert(index, iconHover);
    selItemsIndexs.insert(index, false);
}


void ListWidgetCustom01::addItem(QListWidgetItem* item, QIcon iconClicked, QIcon iconHover)
{
    if (m_isView)   return;

    listwidget->addItem(item);
    ++itemCount;
    QIcon icon = item->icon();

    m_icons.append(item->icon());
    m_iconsClicked.append(iconClicked);
    m_iconsHover.append(iconHover);
    selItemsIndexs.append(false);

}


void ListWidgetCustom01::insertItem(QListWidgetItem* item, int index, QIcon iconClicked, QIcon iconHover)
{
    if (m_isView)   return;

    listwidget->addItem(item);
    ++itemCount;
    m_icons.insert(index, item->icon());
    m_iconsClicked.insert(index, iconClicked);
    m_iconsHover.insert(index, iconHover);
    selItemsIndexs.insert(index, false);

}

void ListWidgetCustom01::addWidgetToItem(QListWidgetItem* item, QWidget* w)
{
    if (m_isView)   return;

    listwidget->setItemWidget(item, w);
}

QListWidgetItem* ListWidgetCustom01::takeItem(int index)
{
    if (m_isView)    return nullptr;

    QListWidgetItem* item = listwidget->takeItem(index);
    if (item == nullptr)    return nullptr;


    //���ɾ������lastHover��selected��ɾ�������м�¼
    if (item == lastHover) lastHover = nullptr;     //��ֹɾ����item����hover�¼��б��޸�iconHover
    selItemsIndexs.removeAt(index);

    
    if(itemCount > 0)   --itemCount;
    if (!m_icons.isEmpty())   m_icons.removeAt(index);
    if (!m_iconsClicked.isEmpty()) m_iconsClicked.removeAt(index);
    if (!m_iconsHover.isEmpty()) m_iconsHover.removeAt(index);
    return item;
}

void ListWidgetCustom01::addItemView(QString item, QIcon icon, QIcon iconClicked, QIcon iconHover)
{
    if (!m_isView)    return;

    QStandardItem* row = new QStandardItem(icon, item);
    row->setTextAlignment(Qt::AlignCenter);
    m_model->appendRow(row);
    ++itemCount;
    //��ӿյ�icon
    m_icons.append(icon);
    m_iconsClicked.append(iconClicked);
    m_iconsHover.append(iconHover);
    selItemsIndexs.append(false);
}

void ListWidgetCustom01::insertItemView(QString item, int index, QIcon icon, QIcon iconClicked, QIcon iconHover)
{
    if (!m_isView)    return;

    QStandardItem* row = new QStandardItem(icon, item);
    row->setTextAlignment(Qt::AlignCenter);
    m_model->insertRow(index, row);
    ++itemCount;
    //��ӿյ�icon
    m_icons.insert(index, icon);
    m_iconsClicked.insert(index, iconClicked);
    m_iconsHover.insert(index, iconHover);
    selItemsIndexs.insert(index, false);
}

void ListWidgetCustom01::addItemView(QStandardItem* item, QIcon iconClicked, QIcon iconHover)
{
    if (!m_isView)   return;

    item->setTextAlignment(Qt::AlignCenter);
    m_model->appendRow(item);
    ++itemCount;
    m_icons.append(item->icon());
    m_iconsClicked.append(iconClicked);
    m_iconsHover.append(iconHover);
    selItemsIndexs.append(false);

}

void ListWidgetCustom01::insertItemView(QStandardItem* item, int index, QIcon iconClicked, QIcon iconHover)
{
    if (!m_isView)   return;

    item->setTextAlignment(Qt::AlignCenter);
    m_model->insertRow(index, item);
    ++itemCount;
    m_icons.insert(index, item->icon());
    m_iconsClicked.insert(index, iconClicked);
    m_iconsHover.insert(index, iconHover);
    selItemsIndexs.insert(index, false);

}

QStandardItem* ListWidgetCustom01::takeItemView(int index)
{
    if (!m_isView)    return nullptr;

    if (!m_model->hasIndex(index, 0))   return nullptr;

    QStandardItem* item = m_model->takeItem(index);
    return item;
}

bool ListWidgetCustom01::removeItemFromModelView(int index)
{
    QStandardItem* delItem = takeItemView(index);

    if (delItem == nullptr) return false;

    
    //���ɾ������lastHover��selected��ɾ�������м�¼
    if (delItem == lastHoverView) lastHoverView = nullptr;
    selItemsIndexs.removeAt(index);


    m_model->removeRow(index);
    delete delItem;
    delItem = nullptr;

    if (itemCount > 0)   --itemCount;
    if (!m_icons.isEmpty())   m_icons.removeAt(index);
    if (!m_iconsClicked.isEmpty()) m_iconsClicked.removeAt(index);
    if (!m_iconsHover.isEmpty()) m_iconsHover.removeAt(index);
    return true;
}

bool ListWidgetCustom01::eventFilter(QObject* watched, QEvent* event)
{
    if (watched == listwidget && event->type() == QEvent::HoverMove) 
    {
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
        QListWidgetItem* item = listwidget->itemAt(mouseEvent->pos());
        int index = listwidget->row(item);
        int indexLastHover = 0;

        if (lastHover != nullptr)
        {
            indexLastHover = listwidget->row(lastHover);
        }
        
        if (item)
        {
            
            if (item != lastHover)
            {
                //��һ���ָ�
                if (lastHover != nullptr && selItemsIndexs.at(indexLastHover) == false)
                {
                    lastHover->setIcon(m_icons.at(indexLastHover)); 
                    lastHover->setFont(m_font);
                }
                //��ǰ�ı�
                if (selItemsIndexs.at(index) == false)
                {
                    item->setIcon(m_iconsHover.at(index)); 
                    item->setFont(m_fontHover);
                }
                emit hoverItemChanged(item, lastHover);
                lastHover = item;
                return false;
            }
        }
        else
        {
            //����Ƶ��հ�����item==nullptrʱҪ�ָ���һ��hover
            if (lastHover != nullptr && selItemsIndexs.at(indexLastHover) == false)
            {
                lastHover->setIcon(m_icons.at(indexLastHover));
                lastHover->setFont(m_font);
                emit hoverItemChanged(item, lastHover);
            }
        }
    }

    if (watched == listview && event->type() == QEvent::HoverMove)
    {
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
        QModelIndex index = listview->indexAt(mouseEvent->pos());
        QStandardItem* item = m_model->itemFromIndex(index);    //����ƶ���item�ⲿʱ������0
        
        int rowIndex = index.row();
        int rowIndexLastHover = 0;
        if (lastHoverView != nullptr)
        {
            rowIndexLastHover = m_model->indexFromItem(lastHoverView).row();
        }

        if (item)
        {
            if (item != lastHoverView)
            {
                if (lastHoverView != nullptr && selItemsIndexs.at(rowIndexLastHover) == false) 
                {
                    lastHoverView->setIcon(m_icons.at(rowIndexLastHover)); //��һ���ָ�
                    lastHoverView->setFont(m_font);
                }
                if (selItemsIndexs.at(rowIndex) == false)
                {
                    item->setIcon(m_iconsHover.at(rowIndex)); //��ǰ�ı�
                    item->setFont(m_fontHover);
                }
                emit hoverItemChangedView(item, lastHoverView);

                lastHoverView = item;
                return false;
            }
        }
        else
        {
            if (lastHoverView != nullptr && selItemsIndexs.at(rowIndexLastHover) == false)
            {
                lastHoverView->setIcon(m_icons[rowIndexLastHover]); //��һ���ָ�
            }
            emit hoverItemChangedView(item, lastHoverView);
            lastHoverView = item;
            return false;
        }

    }

    return QObject::eventFilter(watched, event);
}


