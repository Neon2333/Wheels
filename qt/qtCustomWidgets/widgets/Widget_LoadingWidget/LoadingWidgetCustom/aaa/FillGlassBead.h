#ifndef FILLGLASSBEAD_H
#define FILLGLASSBEAD_H
#include "LoadingWidget.h"
class FillGlassBead :public LoadingWidget
{
public:
    FillGlassBead(QWidget* parent = nullptr);
    enum class WaveType 
    {
        PeacefulWater /*ƽ����ˮ��*/, SwayingWater /*���һζ���ˮ��*/
    };
    void setWaveType(WaveType t);
protected:
    void paintEvent(QPaintEvent*);
private:
    WaveType m_waveType;
};

#endif // !FILLGLASSBEAD_H